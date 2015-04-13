#ifndef __MARKER_DETECTION_H__
#define __MARKER_DETECTION_H__

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Marker.h"
#include "MarkerDetector.h"

#include <opencv/cv.h>

#include "TransformationHelper.h"
#include "NaoHeadTransformHelper.h"
#include "experimot\common\Common.h"

using namespace alvar;
using namespace std;

class MarkerDetectionKinect;

#define PRINT_MSG 0

#define TOP_MARKER_ID 14

typedef boost::shared_ptr<MarkerDetectionKinect> MarkerDetectionKinectPtr;

class MarkerDetectionKinect{

public:
	MarkerDetectionKinect(std::string& calibFile, int markerSize, int cubeSize) :m_strCalibFile(calibFile), m_nMarkerSize(markerSize), m_nCubeSize(cubeSize)
	{
		max_error = std::numeric_limits<double>::max();
		_init();
	}

	~MarkerDetectionKinect(){}

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
		if (tfs.size()>0){
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

	bool Videocallback(IplImage *image, Transform& localTfm, Transform& out_tfm, std::vector<double>& q, bool drawTorso = false)
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

				if (drawTorso){
					Pose p_out;
					Transform torso_tfm;
					Visualize(image, &m_camera, m_nMarkerSize, p_out, CV_RGB(0, 0, 255));
				}

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

private:
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

		return ret;
	}
private:
	std::string m_strCalibFile;
	int m_nMarkerSize;
	int m_nCubeSize;
	Camera m_camera;
	double max_error;
	std::map<int, Transform> m_MarkerTransformMapping;
};

#endif