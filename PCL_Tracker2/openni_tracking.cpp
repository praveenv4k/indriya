
#include <pcl/tracking/tracking.h>
#include <pcl/tracking/particle_filter.h>
#include <pcl/tracking/kld_adaptive_particle_filter_omp.h>
#include <pcl/tracking/particle_filter_omp.h>

#include <pcl/tracking/coherence.h>
#include <pcl/tracking/distance_coherence.h>
#include <pcl/tracking/hsv_color_coherence.h>
#include <pcl/tracking/normal_coherence.h>

#include <pcl/tracking/approx_nearest_pair_point_cloud_coherence.h>
#include <pcl/tracking/nearest_pair_point_cloud_coherence.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//#include <pcl/io/openni_grabber.h>
#include <pcl/io/openni2_grabber.h>
#include <pcl/console/parse.h>
#include <pcl/common/time.h>
#include <pcl/common/centroid.h>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/io/pcd_io.h>

#include <pcl/filters/passthrough.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/filters/extract_indices.h>

#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/integral_image_normal.h>

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>

#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_polygonal_prism_data.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl/surface/convex_hull.h>

#include <pcl/search/pcl_search.h>
#include <pcl/common/transforms.h>

#include <boost/format.hpp>

// Local libs
#include "template_alignment.h"
#include "cluster_segmentor.h"


#define FPS_CALC_BEGIN                          \
    static double duration = 0;                 \
    double start_time = pcl::getTime ();        \

#define FPS_CALC_END(_WHAT_)                    \
  {                                             \
    double end_time = pcl::getTime ();          \
    static unsigned count = 0;                  \
    if (++count == 10)                          \
    {                                           \
      std::cout << "Average framerate("<< _WHAT_ << "): " << double(count)/double(duration) << " Hz" <<  std::endl; \
      count = 0;                                                        \
      duration = 0.0;                                                   \
    }                                           \
    else                                        \
    {                                           \
      duration += end_time - start_time;        \
    }                                           \
  }

using namespace pcl::tracking;

template<typename PointType>
class OpenNISegmentTracking
{
  public:
    typedef ParticleXYZRPY ParticleT;
    typedef pcl::PointCloud<PointType> Cloud;
    typedef pcl::PointCloud<PointType> RefCloud;
    typedef typename RefCloud::Ptr RefCloudPtr;
    typedef typename RefCloud::ConstPtr RefCloudConstPtr;
    typedef typename Cloud::Ptr CloudPtr;
    typedef typename Cloud::ConstPtr CloudConstPtr;
    typedef ParticleFilterTracker<PointType, ParticleT> ParticleFilter;
    typedef typename ParticleFilter::CoherencePtr CoherencePtr;
    typedef typename pcl::search::KdTree<PointType> KdTree;
    typedef typename KdTree::Ptr KdTreePtr;

    OpenNISegmentTracking (const std::string& device_id, int thread_nr,
        double downsampling_grid_size, bool use_convex_hull, bool visualize_non_downsample,
        bool visualize_particles, bool use_fixed) :
        viewer_ ("PCL OpenNI Tracking Viewer"), device_id_ (device_id), new_cloud_ (false),
            counter_ (0), use_convex_hull_ (use_convex_hull), visualize_non_downsample_ (
            visualize_non_downsample), visualize_particles_ (visualize_particles), downsampling_grid_size_ (
            downsampling_grid_size)
    {
      std::vector<double> default_step_covariance = std::vector<double> (6, 0.015 * 0.015);
      default_step_covariance[3] *= 40.0;
      default_step_covariance[4] *= 40.0;
      default_step_covariance[5] *= 40.0;

      std::vector<double> initial_noise_covariance = std::vector<double> (6, 0.00001);
      std::vector<double> default_initial_mean = std::vector<double> (6, 0.0);
      if (use_fixed)
      {
        boost::shared_ptr<ParticleFilterOMPTracker<PointType, ParticleT> > tracker (
            new ParticleFilterOMPTracker<PointType, ParticleT> (thread_nr));
        tracker_ = tracker;
      }
      else
      {
        boost::shared_ptr<KLDAdaptiveParticleFilterOMPTracker<PointType, ParticleT> > tracker (
            new KLDAdaptiveParticleFilterOMPTracker<PointType, ParticleT> (thread_nr));
        tracker->setMaximumParticleNum (500);
        tracker->setDelta (0.99);
        tracker->setEpsilon (0.2);
        ParticleT bin_size;
        bin_size.x = 0.1;
        bin_size.y = 0.1;
        bin_size.z = 0.1;
        bin_size.roll = 0.1;
        bin_size.pitch = 0.1;
        bin_size.yaw = 0.1;
        tracker->setBinSize (bin_size);
        tracker_ = tracker;
      }

      tracker_->setTrans (Eigen::Affine3f::Identity ());
      tracker_->setStepNoiseCovariance (default_step_covariance);
      tracker_->setInitialNoiseCovariance (initial_noise_covariance);
      tracker_->setInitialNoiseMean (default_initial_mean);
      tracker_->setIterationNum (1);

      tracker_->setParticleNum (400);
      tracker_->setResampleLikelihoodThr (0.00);
      tracker_->setUseNormal (false);

      // setup coherences
      typename ApproxNearestPairPointCloudCoherence<PointType>::Ptr coherence =
          typename ApproxNearestPairPointCloudCoherence<PointType>::Ptr ( new ApproxNearestPairPointCloudCoherence<PointType> () );

      boost::shared_ptr<DistanceCoherence<PointType> > distance_coherence = boost::shared_ptr<
          DistanceCoherence<PointType> > (new DistanceCoherence<PointType> ());
      coherence->addPointCoherence (distance_coherence);

      boost::shared_ptr<HSVColorCoherence<PointType> > color_coherence = boost::shared_ptr<
          HSVColorCoherence<PointType> > (new HSVColorCoherence<PointType> ());
      color_coherence->setWeight (0.1);
      coherence->addPointCoherence (color_coherence);

      boost::shared_ptr<pcl::search::Octree<PointType> > search (
          new pcl::search::Octree<PointType> (0.01));
      coherence->setSearchMethod (search);
      coherence->setMaximumDistance (0.01);
      tracker_->setCloudCoherence (coherence);

      save_reference_ = false;
      load_reference_ = false;
      reference_filename_ = "reference.pcd";
      startup_ = 0;
    }

    bool drawParticles (pcl::visualization::PCLVisualizer& viz)
    {
      typename ParticleFilter::PointCloudStatePtr particles = tracker_->getParticles ();
      if (particles)
      {
        if (visualize_particles_)
        {
          pcl::PointCloud<pcl::PointXYZ>::Ptr particle_cloud (
              new pcl::PointCloud<pcl::PointXYZ> ());
          for (size_t i = 0; i < particles->points.size (); i++)
          {
            pcl::PointXYZ point;

            point.x = particles->points[i].x;
            point.y = particles->points[i].y;
            point.z = particles->points[i].z;
            particle_cloud->points.push_back (point);
          }

          {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> blue_color (
                particle_cloud, 250, 99, 71);
            if (!viz.updatePointCloud (particle_cloud, blue_color, "particle cloud")) viz.addPointCloud (
                particle_cloud, blue_color, "particle cloud");
          }
        }
        return true;
      }
      else
      {
        PCL_WARN("no particles\n");
        return false;
      }
    }

    void drawResult (pcl::visualization::PCLVisualizer& viz)
    {
      ParticleXYZRPY result = tracker_->getResult ();
      Eigen::Affine3f transformation = tracker_->toEigenMatrix (result);
      // move a little bit for better visualization
      transformation.translation () += Eigen::Vector3f (0.0, 0.0, -0.005);
      RefCloudPtr result_cloud (new RefCloud ());

      if (!visualize_non_downsample_) pcl::transformPointCloud<PointType> (
          *(tracker_->getReferenceCloud ()), *result_cloud, transformation);
      else pcl::transformPointCloud<PointType> (*reference_, *result_cloud, transformation);

      {
        pcl::visualization::PointCloudColorHandlerCustom<PointType> red_color (result_cloud, 0,
            0, 255);
        if (!viz.updatePointCloud (result_cloud, red_color, "resultcloud")) viz.addPointCloud (
            result_cloud, red_color, "resultcloud");
      }

    }

    void viz_cb (pcl::visualization::PCLVisualizer& viz)
    {
      boost::mutex::scoped_lock lock (mtx_);

      if (!cloud_pass_)
      {
        boost::this_thread::sleep (boost::posix_time::seconds (1));
        return;
      }

      if (new_cloud_ && cloud_pass_downsampled_)
      {
        CloudPtr cloud_pass;
        if (!visualize_non_downsample_) cloud_pass = cloud_pass_downsampled_;
        else cloud_pass = cloud_pass_;

        if (!viz.updatePointCloud (cloud_pass, "cloudpass"))
        {
          viz.addPointCloud (cloud_pass, "cloudpass");
          viz.resetCameraViewpoint ("cloudpass");
        }
      }

      if (new_cloud_ && reference_)
      {
        bool ret = drawParticles (viz);
        if (ret)
        {
          drawResult (viz);

          // draw some texts
          viz.removeShape ("N");
          viz.addText (
              (boost::format ("number of Reference PointClouds: %d")
                  % tracker_->getReferenceCloud ()->points.size ()).str (), 10, 20, 20, 1.0, 1.0,
              1.0, "N");

          viz.removeShape ("M");
          viz.addText (
              (boost::format ("number of Measured PointClouds:  %d")
                  % cloud_pass_downsampled_->points.size ()).str (), 10, 40, 20, 1.0, 1.0, 1.0,
              "M");

          viz.removeShape ("tracking");
          viz.addText ((boost::format ("tracking:        %f fps") % (1.0 / tracking_time_)).str (),
              10, 60, 20, 1.0, 1.0, 1.0, "tracking");

          viz.removeShape ("downsampling");
          viz.addText (
              (boost::format ("downsampling:    %f fps") % (1.0 / downsampling_time_)).str (), 10,
              80, 20, 1.0, 1.0, 1.0, "downsampling");

          viz.removeShape ("computation");
          viz.addText (
              (boost::format ("computation:     %f fps") % (1.0 / computation_time_)).str (), 10,
              100, 20, 1.0, 1.0, 1.0, "computation");

          viz.removeShape ("particles");
          viz.addText (
              (boost::format ("particles:     %d") % tracker_->getParticles ()->points.size ()).str (),
              10, 120, 20, 1.0, 1.0, 1.0, "particles");

        }
      }
      new_cloud_ = false;
    }

    void filterPassThrough (const CloudConstPtr &cloud, Cloud &result)
    {
      FPS_CALC_BEGIN;
      pcl::PassThrough<PointType> pass;
      pass.setFilterFieldName ("z");
      pass.setFilterLimits (0.0, 10.0);
      pass.setKeepOrganized (false);
      pass.setInputCloud (cloud);
      pass.filter (result);
      FPS_CALC_END("filterPassThrough");
    }

    void gridSample (const CloudConstPtr &cloud, Cloud &result, double leaf_size = 0.01)
    {
      FPS_CALC_BEGIN;
      double start = pcl::getTime ();
      pcl::VoxelGrid<PointType> grid;
      grid.setLeafSize (leaf_size, leaf_size, leaf_size);
      grid.setInputCloud (cloud);
      grid.filter (result);
      double end = pcl::getTime ();
      downsampling_time_ = end - start;
      FPS_CALC_END("gridSample");
    }

    void gridSampleApprox (const CloudConstPtr &cloud, Cloud &result, double leaf_size = 0.01)
    {
      FPS_CALC_BEGIN;
      double start = pcl::getTime ();
      pcl::ApproximateVoxelGrid<PointType> grid;
      grid.setLeafSize (leaf_size, leaf_size, leaf_size);
      grid.setInputCloud (cloud);
      grid.filter (result);
      double end = pcl::getTime ();
      downsampling_time_ = end - start;
      FPS_CALC_END("gridSample");
    }

    void tracking (const RefCloudConstPtr &cloud)
    {
      double start = pcl::getTime ();
      FPS_CALC_BEGIN;
      tracker_->setInputCloud (cloud);
      tracker_->compute ();
      double end = pcl::getTime ();
      FPS_CALC_END("tracking");
      tracking_time_ = end - start;
    }

    void segment ()
    {
      // Find the nearest cluster and track it
      // If this fails we get an empty ref_cloud
      CloudPtr ref_cloud (new Cloud);
      std::vector<CloudPtr> clusters;
      ClusterSegmentor<PointType> cluster_segmentor;
      cluster_segmentor.setInputCloud(cloud_pass_);
      cluster_segmentor.extractByDistance(clusters);

      for (size_t i = 0; i < clusters.size(); ++i)
      {
        std::stringstream fname;
        fname << "segment_bydistance_" << i << ".pcd";
        pcl::io::savePCDFileASCII(fname.str(), *(clusters[i]));
      }

      if (clusters.size() > 0)
        ref_cloud = clusters[0];

      std::cout << "ref_cloud: "
          << " points: " << ref_cloud->points.size()
          << " wh:" << ref_cloud->width << "x" << ref_cloud->height
          << " is_dense: " << (ref_cloud->is_dense ? "Yes" : "No")
          << std::endl;

      if (save_reference_) {
        PCL_INFO (("saving ref cloud: " + reference_filename_ + "\n").c_str());
        pcl::io::savePCDFileASCII(reference_filename_, *ref_cloud);
      }

      trackCloud(ref_cloud);
    }

    void trackCloud (const RefCloudConstPtr &ref_cloud)
    {
        PCL_INFO("calculating cog\n");

        Eigen::Vector4f c;
        RefCloudPtr transed_ref (new RefCloud);
        pcl::compute3DCentroid<PointType> (*ref_cloud, c);
        Eigen::Affine3f trans = Eigen::Affine3f::Identity ();
        trans.translation () = Eigen::Vector3f (c[0], c[1], c[2]);
        pcl::transformPointCloud<PointType> (*ref_cloud, *transed_ref, trans.inverse ());
        CloudPtr transed_ref_downsampled (new Cloud);
        gridSample (transed_ref, *transed_ref_downsampled, downsampling_grid_size_);
        tracker_->setReferenceCloud (transed_ref_downsampled);
        tracker_->setTrans (trans);
        reference_ = transed_ref;
        tracker_->setMinIndices (ref_cloud->points.size () / 2);
    }

    void loadTrackCloud() { loadTrackCloud(reference_filename_); }
    void loadTrackCloud(const std::string &filename)
    {
      PCL_INFO (("loading ref cloud:" + filename + "\n").c_str());
      RefCloudPtr ref_cloud (new RefCloud);
      RefCloudPtr load_cloud (new RefCloud);
      if ( pcl::io::loadPCDFile<PointType>(filename, *load_cloud) == -1) {
        std::string msg = "Failed to read file: " + filename + "\n";
        PCL_ERROR(msg.c_str());
        return;
      }
      pcl::io::savePCDFileASCII("load_cloud.pcd", *load_cloud);
      pcl::io::savePCDFileASCII("load_cloud_pass.pcd", *cloud_pass_);
      findCloud(load_cloud, ref_cloud);
      pcl::io::savePCDFileASCII("load_transformed_cloud.pcd", *ref_cloud);
      trackCloud(ref_cloud);
    }

    // http://answers.ros.org/question/9515/how-to-convert-between-different-point-cloud-types-using-pcl/
    void copyPointCloud(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr src,
                          pcl::PointCloud<pcl::PointXYZ>::Ptr dst)
    {
      dst->resize (src->size());
      dst->width = src->width;
      dst->height = src->height;
      dst->is_dense = src->is_dense;
      for (size_t i = 0; i < src->size(); ++i )
      {
        dst->points[i].x = src->points[i].x;
        dst->points[i].y = src->points[i].y;
        dst->points[i].z = src->points[i].z;
      }
    }

    /**
     * Find the passed cloud in the current openni cloud
     */
    void findCloud(RefCloudPtr find_cloud, RefCloudPtr out_cloud)
    {
      PCL_INFO ("Searching for cloud\n");

      // Find all the clusters. We then try to match the find cloud against each cluster.
      std::vector<CloudPtr> clusters;
      ClusterSegmentor<PointType> cluster_segmentor;
      cluster_segmentor.setInputCloud(cloud_pass_);
      cluster_segmentor.extract(clusters);

      // Convert the cloud we want to find.
      // (We need PointXYZ but openni tracking is using PointXYZRGBA)
      pcl::PointCloud<pcl::PointXYZ>::Ptr object_template (new pcl::PointCloud<pcl::PointXYZ>);
      copyPointCloud (find_cloud, object_template);
      pcl::io::savePCDFileASCII("find_object_template.pcd", *object_template);

      // ... and downsampling the point cloud
//      PCL_INFO ("... and downsampling the point cloud\n");
//      const float voxel_grid_size = 0.005f;
//      pcl::VoxelGrid<pcl::PointXYZ> vox_grid;
//      vox_grid.setInputCloud (cloud);
//      vox_grid.setLeafSize (voxel_grid_size, voxel_grid_size, voxel_grid_size);
//      //vox_grid.filter (*cloud); // Please see this http://www.pcl-developers.org/Possible-problem-in-new-VoxelGrid-implementation-from-PCL-1-5-0-td5490361.html
//      pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud (new pcl::PointCloud<pcl::PointXYZ>);
//      vox_grid.filter (*tempCloud);
//      cloud = tempCloud;

      // Set the TemplateAlignment inputs
      TemplateAlignment template_align;
//      for (size_t i = 0; i < object_templates.size (); ++i)
//      {
//        template_align.addTemplateCloud (object_templates[i]);
//      }
      FeatureCloud template_cloud;
      template_cloud.setInputCloud(object_template);
      template_align.addTemplateCloud (template_cloud);

      TemplateAlignment::Result best_result;
      best_result.fitness_score = 10000;
      for (size_t i = 0; i < clusters.size (); ++i)
      {
        // Assign to the target FeatureCloud
        // We need PointXYZ but openni tracking is using PointXYZRGBA
        FeatureCloud target_cloud;
        pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud (new pcl::PointCloud<pcl::PointXYZ>);
        copyPointCloud (clusters[i], temp_cloud);
        target_cloud.setInputCloud (temp_cloud);
        template_align.setTargetCloud (target_cloud);

        // Find the best template alignment
        PCL_INFO ("... find the best template alignment\n");
        TemplateAlignment::Result best_alignment;
        int best_index = template_align.findBestAlignment (best_alignment);
        //const FeatureCloud &best_template = object_templates[best_index];
        const FeatureCloud &best_template = template_cloud;

        // Print the alignment fitness score (values less than 0.00002 are good)
        printf ("Best fitness score: %f\n", best_alignment.fitness_score);
        // Print the rotation matrix and translation vector
        Eigen::Matrix3f rotation = best_alignment.final_transformation.block<3,3>(0, 0);
        Eigen::Vector3f translation = best_alignment.final_transformation.block<3,1>(0, 3);
        printf ("\n");
        printf ("    | %6.3f %6.3f %6.3f | \n", rotation (0,0), rotation (0,1), rotation (0,2));
        printf ("R = | %6.3f %6.3f %6.3f | \n", rotation (1,0), rotation (1,1), rotation (1,2));
        printf ("    | %6.3f %6.3f %6.3f | \n", rotation (2,0), rotation (2,1), rotation (2,2));
        printf ("\n");
        printf ("t = < %0.3f, %0.3f, %0.3f >\n", translation (0), translation (1), translation (2));

        if (best_alignment.fitness_score < best_result.fitness_score)
          best_result = best_alignment;
      }

      printf ("Overall best fitness score: %f\n", best_result.fitness_score);
      pcl::transformPointCloud (*find_cloud, *out_cloud, best_result.final_transformation);
    }

    void cloud_cb (const CloudConstPtr &cloud)
    {
      boost::mutex::scoped_lock lock (mtx_);
      double start = pcl::getTime ();
      FPS_CALC_BEGIN;
      cloud_pass_.reset (new Cloud);
      cloud_pass_downsampled_.reset (new Cloud);
      filterPassThrough (cloud, *cloud_pass_);

      if (counter_ < 10)
      {
        gridSample (cloud_pass_, *cloud_pass_downsampled_, downsampling_grid_size_);
      }
      else if (load_reference_)
      {
        loadTrackCloud();
        counter_ = 10; // will also get ++ at end of method
        load_reference_ = false;
      }
      else if (counter_ == 10)
      {
        // Set the reference cloud and trans on the tracker
        segment();
      }
      else
      {
        gridSampleApprox (cloud_pass_, *cloud_pass_downsampled_, downsampling_grid_size_);
        tracking (cloud_pass_downsampled_);
      }

      new_cloud_ = true;
      double end = pcl::getTime ();
      computation_time_ = end - start;
      FPS_CALC_END("computation");
      counter_++;
    }

    void run ()
    {
      pcl::Grabber* interface = new pcl::io::OpenNI2Grabber (device_id_);
      boost::function<void (const CloudConstPtr&)> f = boost::bind (
          &OpenNISegmentTracking::cloud_cb, this, _1);
      interface->registerCallback (f);

      viewer_.runOnVisualizationThread (boost::bind (&OpenNISegmentTracking::viz_cb, this, _1),
          "viz_cb");

      interface->start ();

      while (!viewer_.wasStopped ())
        boost::this_thread::sleep (boost::posix_time::seconds (1));
      interface->stop ();
    }

    pcl::visualization::CloudViewer viewer_;
    pcl::PointCloud<pcl::Normal>::Ptr normals_;
    CloudPtr cloud_pass_;
    CloudPtr cloud_pass_downsampled_;
    CloudPtr plane_cloud_;
    CloudPtr nonplane_cloud_;
    CloudPtr cloud_hull_;
    CloudPtr reference_;
    std::vector<pcl::Vertices> hull_vertices_;

    std::string device_id_;
    boost::mutex mtx_;
    bool new_cloud_;
    boost::shared_ptr<ParticleFilter> tracker_;
    int counter_;
    bool use_convex_hull_;
    bool visualize_non_downsample_;
    bool visualize_particles_;
    double tracking_time_;
    double computation_time_;
    double downsampling_time_;
    double downsampling_grid_size_;
    bool save_reference_;
    bool load_reference_;
    std::string reference_filename_;
    int startup_;
};

void usage (char** argv)
{
  std::cout << "usage: " << argv[0] << " <device_id> [-C] [-g]\n\n";
  std::cout << "  -C:  initialize the pointcloud to track without plane segmentation" << std::endl;
  std::cout << "  -D: visualizing with non-downsampled pointclouds." << std::endl;
  std::cout << "  -P: not visualizing particle cloud." << std::endl;
  std::cout << "  -fixed: use the fixed number of the particles." << std::endl;
  std::cout << "  -d <value>: specify the grid size of downsampling (defaults to 0.01)."
      << std::endl;
}

int main (int argc, char** argv)
{
  bool use_convex_hull = true;
  bool visualize_non_downsample = false;
  bool visualize_particles = true;
  bool use_fixed = false;
  bool save = false;
  bool load = false;

  double downsampling_grid_size = 0.01;

  if (pcl::console::find_argument (argc, argv, "-C") > 0) use_convex_hull = false;
  if (pcl::console::find_argument (argc, argv, "-D") > 0) visualize_non_downsample = true;
  if (pcl::console::find_argument (argc, argv, "-P") > 0) visualize_particles = false;
  if (pcl::console::find_argument (argc, argv, "-fixed") > 0) use_fixed = true;
  if (pcl::console::find_argument (argc, argv, "--load") > 0) load = true;
  if (pcl::console::find_argument (argc, argv, "--save") > 0) save = true;
  pcl::console::parse_argument (argc, argv, "-d", downsampling_grid_size);
  if (argc < 2)
  {
    usage (argv);
    exit (1);
  }

  std::string device_id = std::string (argv[1]);

  if (device_id == "--help" || device_id == "-h")
  {
    usage (argv);
    exit (1);
  }
  device_id = "";

  // open kinect
  OpenNISegmentTracking<pcl::PointXYZRGBA> v (device_id, 8, downsampling_grid_size, use_convex_hull,
      visualize_non_downsample, visualize_particles, use_fixed);
  v.save_reference_ = save;
  v.load_reference_ = load;
  v.run ();
}

