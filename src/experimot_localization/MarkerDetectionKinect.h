#ifndef __MARKER_DETECTION_KINECT_H__
#define __MARKER_DETECTION_KINECT_H__

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Marker.h"
#include "MarkerDetector.h"

#include <opencv/cv.h>

#include "TransformationHelper.h"
#include "NaoHeadTransformHelper.h"
#include "experimot\common\Common.h"
#include "KinectPcl\Kinect2_PCL.h"
#include "CallbackBase.h"
#include "RobotPoseInfo.h"
#include "Kinect_Filtering.h"

using namespace alvar;
using namespace std;

class MarkerDetectionKinect;

#define PRINT_MSG 0

#define TOP_MARKER_ID 14

typedef boost::shared_ptr<MarkerDetectionKinect> MarkerDetectionKinectPtr;
typedef boost::shared_ptr<pcl::Kinect2Grabber> Kinect2GrabberPtr;

class MarkerDetectionKinect : public CallbackBase {

public:
	typedef void (signal_markerdetection_transform)(Transform&);

	MarkerDetectionKinect(std::string& calibFile, int markerSize, int cubeSize,double newMarkerError, double trackError) :
		m_strCalibFile(calibFile), m_nMarkerSize(markerSize), m_nCubeSize(cubeSize), m_fNewMarkerError(newMarkerError), m_fTrackError(trackError)
	{
		max_error = std::numeric_limits<double>::max();
		_init();
	}

	~MarkerDetectionKinect()
	{
		m_pKinect2Grabber->stop();

		disconnect_all_slots<signal_markerdetection_transform>();
	}

	static void VisualizeMarkerPose(IplImage *image, Camera *cam, double visualize2d_points[12][2], CvScalar color) {
		// Cube
		for (int i = 0; i < 4; i++) {
			cvLine(image, cvPoint((int)visualize2d_points[i][0], (int)visualize2d_points[i][1]), cvPoint((int)visualize2d_points[(i + 1) % 4][0], (int)visualize2d_points[(i + 1) % 4][1]), color);
			cvLine(image, cvPoint((int)visualize2d_points[i][0], (int)visualize2d_points[i][1]), cvPoint((int)visualize2d_points[4 + i][0], (int)visualize2d_points[4 + i][1]), color);
			cvLine(image, cvPoint((int)visualize2d_points[4 + i][0], (int)visualize2d_points[4 + i][1]), cvPoint((int)visualize2d_points[4 + ((i + 1) % 4)][0], (int)visualize2d_points[4 + ((i + 1) % 4)][1]), color);
		}
		// Coordinates
		cvLine(image, cvPoint((int)visualize2d_points[8][0], (int)visualize2d_points[8][1]), cvPoint((int)visualize2d_points[9][0], (int)visualize2d_points[9][1]), CV_RGB(255, 0, 0));
		cvLine(image, cvPoint((int)visualize2d_points[8][0], (int)visualize2d_points[8][1]), cvPoint((int)visualize2d_points[10][0], (int)visualize2d_points[10][1]), CV_RGB(0, 255, 0));
		cvLine(image, cvPoint((int)visualize2d_points[8][0], (int)visualize2d_points[8][1]), cvPoint((int)visualize2d_points[11][0], (int)visualize2d_points[11][1]), CV_RGB(0, 0, 255));
	}

	static void Visualize(IplImage *image, Camera *cam, double edge_length, Pose& pose, CvScalar color) {
		double visualize3d_points[12][3] = {
			// cube
			{ -(edge_length / 2), -(edge_length / 2), 0 },
			{ -(edge_length / 2), (edge_length / 2), 0 },
			{ (edge_length / 2), (edge_length / 2), 0 },
			{ (edge_length / 2), -(edge_length / 2), 0 },
			{ -(edge_length / 2), -(edge_length / 2), edge_length },
			{ -(edge_length / 2), (edge_length / 2), edge_length },
			{ (edge_length / 2), (edge_length / 2), edge_length },
			{ (edge_length / 2), -(edge_length / 2), edge_length },
			//coordinates
			{ 0, 0, 0 },
			{ edge_length, 0, 0 },
			{ 0, edge_length, 0 },
			{ 0, 0, edge_length },
		};
		double visualize2d_points[12][2];
		CvMat visualize3d_points_mat;
		CvMat visualize2d_points_mat;
		cvInitMatHeader(&visualize3d_points_mat, 12, 3, CV_64F, visualize3d_points);
		cvInitMatHeader(&visualize2d_points_mat, 12, 2, CV_64F, visualize2d_points);
		cam->ProjectPoints(&visualize3d_points_mat, &pose, &visualize2d_points_mat);

		VisualizeMarkerPose(image, cam, visualize2d_points, color);
	}

	void TransformToTopFrame(std::map<int, Transform>& poseMap, Transform& outTf){
		std::vector<Transform> tfs;
		FOREACH(it, poseMap){
			if (it->first == TOP_MARKER_ID){
				//tfs.push_back(it->second*m_MarkerTransformMapping[it->first]); // 20150410
				tfs.push_back(it->second);
			}
			else{
				int factor = -1;
				Transform tf2(geometry::quatFromAxisAngle(RaveVector<dReal>(1, 0, 0), factor*((alvar::PI) / 2)), Vector(0, (double)m_nCubeSize / 2, -(double)m_nCubeSize / 2));
				tfs.push_back(it->second*tf2*m_MarkerTransformMapping[it->first]);
			}
		}
		outTf.identity();
		if (tfs.size() > 0){
			if (tfs.size() > 1){
				//TODO Error based weighting of the rotation and translation
				Transform tf1 = tfs[0];
				Transform tf2 = tfs[1];
				outTf.rot = geometry::quatSlerp(tf1.rot, tf2.rot, 0.5);
				outTf.trans = 0.5*(tf1.trans + tf2.trans);
			}
			else{
				outTf = tfs[0];
			}
#if PRINT_MSG
			Transform disp;
			TransformationHelper::PoseToTransform(poseMap.at(7), disp);
			cout << "First marker: " << disp << "; Top marker: " << outTf << std::endl;
#endif
		}
	}

	bool Videocallback(IplImage *image, Transform& out_tfm)
	{
		bool ret = false;
		static IplImage *rgba;
		bool flip_image = (image->origin ? true : false);
		if (flip_image) {
			cvFlip(image);
			image->origin = !image->origin;
		}

		static MarkerDetector<MarkerData> marker_detector;
		marker_detector.SetMarkerSize(m_nMarkerSize); // for marker ids larger than 255, set the content resolution accordingly

		marker_detector.Detect(image, &m_camera, true, true);

		double error = max_error;
		int best_marker = -1;
		std::map<int, Pose> markerPoses;
		std::map<int, Transform> markerTfs;
		if (marker_detector.markers->size() >= 1){
			for (size_t i = 0; i < marker_detector.markers->size(); i++) {
				if (i >= 32) break;

				alvar::MarkerData mData = marker_detector.markers->operator[](i);
				Pose p = mData.pose;

				markerPoses.insert(std::pair<int, Pose>(mData.GetId(), p));

				double temp_error = (*(marker_detector.markers))[i].GetError(alvar::Marker::TRACK_ERROR | alvar::Marker::DECODE_ERROR | alvar::Marker::MARGIN_ERROR);
				if (temp_error < error){
					error = temp_error;
					best_marker = i;
				}
				int id = (*(marker_detector.markers))[i].GetId();
				double r = 1.0 - double(id + 1) / 32.0;
				double g = 1.0 - double(id * 3 % 32 + 1) / 32.0;
				double b = 1.0 - double(id * 7 % 32 + 1) / 32.0;

				TransformMatrix rave;
				double gl_mat[16];

				p.GetMatrixGL(gl_mat, false);
				TransformationHelper::OpenGLToOpenRAVE(gl_mat, rave);

				markerTfs.insert(std::pair<int, Transform>(mData.GetId(), Transform(rave)));

#if PRINT_MSG
				if (id == 7){
					p.Output();
					std::cout << "Error : " << temp_error << std::endl;
				}
#endif
			}
			if (marker_detector.markers->size() > 0){
				Pose p_res;


				//TransformToTopFrame(markerPoses, out_tfm);
				TransformToTopFrame(markerTfs, out_tfm);
				TransformationHelper::TransformToPose(out_tfm, p_res);

				int id = 10;
				double r = 1.0 - double(id + 1) / 32.0;
				double g = 1.0 - double(id * 3 % 32 + 1) / 32.0;
				double b = 1.0 - double(id * 7 % 32 + 1) / 32.0;

				Visualize(image, &m_camera, m_nMarkerSize, p_res, CV_RGB(255, 0, 0));
			}
			if (flip_image) {
				cvFlip(image);
				image->origin = !image->origin;
			}
			ret = true;
		}
		return ret;
	}
	void UpdateMarkerTransform(Transform& markerTfm){
		if (signal_transform->num_slots() > 0){
			signal_transform->operator()(markerTfm);
		}
	}
private:
	bool GetMarkerPoses(IplImage *image, const ARCloud::ConstPtr &cloud, std::map<int, Transform>& poseMap) {
		bool bRet = false;
		//Detect and track the markers
		if (m_Detector.Detect(image, &m_camera, true, false, m_fNewMarkerError,
			m_fTrackError, CVSEQ, true))
		{
			printf("\n--------------------------\n\n");
			for (size_t i = 0; i < m_Detector.markers->size(); i++)
			{
				vector<cv::Point, Eigen::aligned_allocator<cv::Point> > pixels;
				Marker *m = &((*m_Detector.markers)[i]);
				int id = m->GetId();
				cout << "******* ID: " << id << endl;

				int resol = m->GetRes();
				//int ori = m->ros_orientation;

				PointDouble pt1, pt2, pt3, pt4;
				pt4 = m->experimot_marker_points_img[0];
				pt3 = m->experimot_marker_points_img[resol - 1];
				pt1 = m->experimot_marker_points_img[(resol*resol) - resol];
				pt2 = m->experimot_marker_points_img[(resol*resol) - 1];

				std::vector<pcl::PointXYZRGB> cornerPts;
				cornerPts.push_back(cloud->operator()(pt1.x, pt1.y));
				cornerPts.push_back(cloud->operator()(pt2.x, pt2.y));
				cornerPts.push_back(cloud->operator()(pt3.x, pt3.y));
				cornerPts.push_back(cloud->operator()(pt4.x, pt4.y));

#if 0
				if (ori >= 0 && ori < 4){
					if (ori != 0){
						std::rotate(m->ros_corners_3D.begin(), m->ros_corners_3D.begin() + ori, m->ros_corners_3D.end());
					}
				}
				else
					ROS_ERROR("FindMarkerBundles: Bad Orientation: %i for ID: %i", ori, id);
#endif

				//Get the 3D marker points
				BOOST_FOREACH(const PointDouble& p, m->experimot_marker_points_img)
					pixels.push_back(cv::Point(p.x, p.y));
				ARCloud::Ptr selected_points = filterCloud(cloud, pixels);

				//Use the kinect data to find a plane and pose for the marker
				Transform pose;
				int ret = PlaneFitPoseImprovement(i, cornerPts, selected_points, cloud, pose);

				if (ret == 0){
					poseMap.insert(std::pair<int, Transform>(m->GetId(), pose));
					bRet = true;
				}
			}
		}
		return bRet;
	}

	bool _init(){
		int width = 1980;
		int height = 1080;
		bool ret = false;
		cout << "Loading calibration: " << m_strCalibFile;
		if (m_camera.SetCalib(m_strCalibFile.c_str(), width, height)) {
			cout << " [Ok]" << endl;
			ret = true;
		}
		else {
			m_camera.SetRes(width, height);
			cout << " [Fail]" << endl;
		}

		Vector rot_z(0, 0, 1);

		m_MarkerTransformMapping.insert(std::pair<int, Transform>(7, Transform(geometry::quatFromAxisAngle(rot_z, -(alvar::PI / 2)), Vector())));
		m_MarkerTransformMapping.insert(std::pair<int, Transform>(0, Transform(geometry::quatFromAxisAngle(rot_z, 0.0), Vector())));
		m_MarkerTransformMapping.insert(std::pair<int, Transform>(13, Transform(geometry::quatFromAxisAngle(rot_z, alvar::PI), Vector())));
		m_MarkerTransformMapping.insert(std::pair<int, Transform>(10, Transform(geometry::quatFromAxisAngle(rot_z, (alvar::PI / 2)), Vector())));
		m_MarkerTransformMapping.insert(std::pair<int, Transform>(14, Transform(geometry::quatFromAxisAngle(rot_z, (alvar::PI)), Vector())));

		signal_transform = createSignal<signal_markerdetection_transform>();

		m_pKinect2Grabber = Kinect2GrabberPtr(new pcl::Kinect2Grabber());

		// Callback Function to be called when Updating Data
		boost::function<void(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr&, const CvMatPtr&)> function =
			[this](const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &cloud, const CvMatPtr& img){
			if (img != NULL){
				IplImage raw = *img;

				std::map<int, Transform> markerMap;
				if (GetMarkerPoses(&raw, cloud, markerMap)){
					Transform markerTfm;
					TransformToTopFrame(markerMap, markerTfm);
					UpdateMarkerTransform(markerTfm);
				}
				/*if (Videocallback(&raw, markerTfm)){
					UpdateMarkerTransform(markerTfm);
				}*/
			}
		};

		m_pKinect2Grabber->registerCallback(function);

		m_pKinect2Grabber->start();

		return ret;
	}

	int PlaneFitPoseImprovement(int id, const std::vector<pcl::PointXYZRGB> &corners_3D, pcl::PointCloud<pcl::PointXYZRGB>::Ptr selected_points, const ARCloud::ConstPtr &cloud, Transform &p){
		PlaneFitResult res = fitPlane(selected_points);

		//gm::PoseStamped pose;
		//pose.header.stamp = pcl_conversions::fromPCL(cloud.header).stamp;
		//pose.header.frame_id = cloud.header.frame_id;
		OpenRAVE::Vector position = centroid(*res.inliers);
		OpenRAVE::Vector orientation(1, 0, 0, 0);

		//draw3dPoints(selected_points, cloud.header.frame_id, 1, id, 0.005);

		//Get 2 points that point forward in marker x direction   
		int i1, i2;
		if (isnan(corners_3D[0].x) || isnan(corners_3D[0].y) || isnan(corners_3D[0].z) ||
			isnan(corners_3D[3].x) || isnan(corners_3D[3].y) || isnan(corners_3D[3].z))
		{
			if (isnan(corners_3D[1].x) || isnan(corners_3D[1].y) || isnan(corners_3D[1].z) ||
				isnan(corners_3D[2].x) || isnan(corners_3D[2].y) || isnan(corners_3D[2].z))
			{
				return -1;
			}
			else{
				i1 = 1;
				i2 = 2;
			}
		}
		else{
			i1 = 0;
			i2 = 3;
		}

		//Get 2 points the point forward in marker y direction   
		int i3, i4;
		if (isnan(corners_3D[0].x) || isnan(corners_3D[0].y) || isnan(corners_3D[0].z) ||
			isnan(corners_3D[1].x) || isnan(corners_3D[1].y) || isnan(corners_3D[1].z))
		{
			if (isnan(corners_3D[3].x) || isnan(corners_3D[3].y) || isnan(corners_3D[3].z) ||
				isnan(corners_3D[2].x) || isnan(corners_3D[2].y) || isnan(corners_3D[2].z))
			{
				return -1;
			}
			else{
				i3 = 2;
				i4 = 3;
			}
		}
		else{
			i3 = 1;
			i4 = 0;
		}

		ARCloud::Ptr orient_points(new ARCloud());
		orient_points->points.push_back(corners_3D[i1]);
		//draw3dPoints(orient_points, cloud.header.frame_id, 3, id + 1000, 0.008);

		orient_points->clear();
		orient_points->points.push_back(corners_3D[i2]);
		//draw3dPoints(orient_points, cloud.header.frame_id, 2, id + 2000, 0.008);

		int succ;
		succ = extractOrientation(res.coeffs, corners_3D[i1], corners_3D[i2], corners_3D[i3], corners_3D[i4], orientation);
		if (succ < 0) return -1;

		b3Matrix3x3 mat;
		succ = extractFrame(res.coeffs, corners_3D[i1], corners_3D[i2], corners_3D[i3], corners_3D[i4], mat);
		if (succ < 0) return -1;

		//drawArrow(pose.pose.position, mat, cloud.header.frame_id, 1, id);

		/*p.trans[0] = position.x * 100.0;
		p.trans[1] = position.y * 100.0;
		p.trans[2] = position.z * 100.0;
		p.rot[1] = orientation.x;
		p.rot[2] = orientation.y;
		p.rot[3] = orientation.z;
		p.rot[0] = orientation.w;*/

		p = Transform(orientation, position);

		return 0;
	}

	

private:
	boost::signals2::signal<signal_markerdetection_transform>* signal_transform;
	std::string m_strCalibFile;
	int m_nMarkerSize;
	int m_nCubeSize;
	Camera m_camera;
	double max_error;
	double m_fNewMarkerError;
	double m_fTrackError;
	std::map<int, Transform> m_MarkerTransformMapping;
	Kinect2GrabberPtr m_pKinect2Grabber;
	MarkerDetector<MarkerData> m_Detector;
};

#endif