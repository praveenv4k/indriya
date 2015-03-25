//#include "CvTestbed.h"
#define NOMINMAX
#include "Marker.h"
#include "MarkerDetector.h"

#include <opencv/cv.h>

#include "CvKinectCapture.h"

using namespace alvar;
using namespace std;

const int marker_size = 55; // 55 mm
const int cube_size = 64; // 55 mm

double max_error = std::numeric_limits<double>::max();
Camera cam;

void Slerp(double* q1, double* q2, double* qr, double lambda)
{
	double w1 = q1[0];
	double x1 = q1[1];
	double y1 = q1[2];
	double z1 = q1[3];

	double w2 = q2[0];
	double x2 = q2[1];
	double y2 = q2[2];
	double z2 = q2[3];

	double dotproduct = x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;
	double theta, st, sut, sout, coeff1, coeff2;

	// algorithm adapted from Shoemake's paper
	lambda = lambda / 2.0;

	theta = acos(dotproduct);
	if (theta < 0.0) theta = -theta;

	st = sin(theta);
	sut = sin(lambda*theta);
	sout = sin((1 - lambda)*theta);
	coeff1 = sout / st;
	coeff2 = sut / st;

	qr[0] = coeff1*w1 + coeff2*w2;
	qr[1] = coeff1*x1 + coeff2*x2;
	qr[2] = coeff1*y1 + coeff2*y2;
	qr[3] = coeff1*z1 + coeff2*z2;

	Rotation::QuatNorm(qr);
}

void VisualizeMarkerPose(IplImage *image, Camera *cam, double visualize2d_points[12][2], CvScalar color) {
	// Cube
	for (int i = 0; i<4; i++) {
		cvLine(image, cvPoint((int)visualize2d_points[i][0], (int)visualize2d_points[i][1]), cvPoint((int)visualize2d_points[(i + 1) % 4][0], (int)visualize2d_points[(i + 1) % 4][1]), color);
		cvLine(image, cvPoint((int)visualize2d_points[i][0], (int)visualize2d_points[i][1]), cvPoint((int)visualize2d_points[4 + i][0], (int)visualize2d_points[4 + i][1]), color);
		cvLine(image, cvPoint((int)visualize2d_points[4 + i][0], (int)visualize2d_points[4 + i][1]), cvPoint((int)visualize2d_points[4 + ((i + 1) % 4)][0], (int)visualize2d_points[4 + ((i + 1) % 4)][1]), color);
	}
	// Coordinates
	cvLine(image, cvPoint((int)visualize2d_points[8][0], (int)visualize2d_points[8][1]), cvPoint((int)visualize2d_points[9][0], (int)visualize2d_points[9][1]), CV_RGB(255, 0, 0));
	cvLine(image, cvPoint((int)visualize2d_points[8][0], (int)visualize2d_points[8][1]), cvPoint((int)visualize2d_points[10][0], (int)visualize2d_points[10][1]), CV_RGB(0, 255, 0));
	cvLine(image, cvPoint((int)visualize2d_points[8][0], (int)visualize2d_points[8][1]), cvPoint((int)visualize2d_points[11][0], (int)visualize2d_points[11][1]), CV_RGB(0, 0, 255));
}

void Visualize(IplImage *image, Camera *cam, double edge_length, Pose& pose, CvScalar color) {
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


void videocallback(IplImage *image)
{
    static IplImage *rgba;
    bool flip_image = (image->origin?true:false);
    if (flip_image) {
        cvFlip(image);
        image->origin = !image->origin;
    }

    static MarkerDetector<MarkerData> marker_detector;
    marker_detector.SetMarkerSize(marker_size); // for marker ids larger than 255, set the content resolution accordingly
    //static MarkerDetector<MarkerArtoolkit> marker_detector;
    //marker_detector.SetMarkerSize(2.8, 3, 1.5);

    // Here we try to use RGBA just to make sure that also it works...
    //cvCvtColor(image, rgba, CV_RGB2RGBA);
    marker_detector.Detect(image, &cam, true, true);

	double error = max_error;
	int best_marker = -1;
    for (size_t i=0; i<marker_detector.markers->size(); i++) {
        if (i >= 32) break;
        
        alvar::MarkerData mData = marker_detector.markers->operator[](i);
		Pose p = mData.pose;

		double temp_error = (*(marker_detector.markers))[i].GetError(alvar::Marker::TRACK_ERROR | alvar::Marker::DECODE_ERROR | alvar::Marker::MARGIN_ERROR);
		if (temp_error < error){
			error = temp_error;
			best_marker = i;
		}
        int id = (*(marker_detector.markers))[i].GetId();
        double r = 1.0 - double(id+1)/32.0;
        double g = 1.0 - double(id*3%32+1)/32.0;
        double b = 1.0 - double(id*7%32+1)/32.0;

		p.Output();

		// TODO - Just for debug
		if(i==0){
			Pose temp(p);
			double qTemp[4]={0.73325678 ,0.67461462,  0.00777518,  0.0846709};
			double tTemp[4]={-0.531615348135546, 8.11472236117109, 1063.19537088174};
			temp.SetQuaternion(qTemp);
			temp.SetTranslation(tTemp);
			Visualize(image, &cam, marker_size, temp, CV_RGB(255, 0, 0));
		}
    }
#if 0
	if (best_marker > -1 && best_marker <= marker_detector.markers->size()){
		Marker m = (*(marker_detector.markers))[best_marker];
		Pose p = (*(marker_detector.markers))[best_marker].pose;

		double rot_x[4] = { 0.707, -0.707, 0, 0 };
		double rot_res[4] = { 1, 0, 0, 0 };
		Pose p2 = p;
		CvMat* rot = cvCreateMat(4, 1, CV_64F);
		p.GetQuaternion(rot);
		p2.translation[1] -= (double)marker_size/2;
		p2.translation[2] += (double)marker_size/2;
		Rotation::QuatMul(rot->data.db, rot_x, rot_res);
		p2.SetQuaternion(rot_res);
		cvRelease((void**)&rot);
		
		int id = 10;
		double r = 1.0 - double(id + 1) / 32.0;
		double g = 1.0 - double(id * 3 % 32 + 1) / 32.0;
		double b = 1.0 - double(id * 7 % 32 + 1) / 32.0;

		p2.GetMatrixGL(top.gl_mat);
		top.SetColor(r, g, b);
		top.SetScale(marker_size);

		GlutViewer::DrawableAdd(&top);
		p.Output();
		p2.Output();
	}
#else
	if (marker_detector.markers->size() > 0){
		double rot_x[4] = { 0.707, -0.707, 0, 0 };
		
		Pose p_res;
		if (marker_detector.markers->size() == 1){
			Marker m = (*(marker_detector.markers))[best_marker];
			Pose p = (*(marker_detector.markers))[best_marker].pose;

			double rot_res[4] = { 1, 0, 0, 0 };
			Pose p2 = p;
			CvMat* rot = cvCreateMat(4, 1, CV_64F);
			p.GetQuaternion(rot);
			p2.translation[1] -= (double)cube_size / 2;
			p2.translation[2] += (double)cube_size / 2;
			Rotation::QuatMul(rot->data.db, rot_x, rot_res);
			p2.SetQuaternion(rot_res);
			cvRelease((void**)&rot);

			p_res = p2;
		}
		else{
			Marker m1 = (*(marker_detector.markers))[0];
			Marker m2 = (*(marker_detector.markers))[1];
			Pose p1 = m1.pose;
			Pose p2 = m2.pose;

			CvMat* rot1 = cvCreateMat(4, 1, CV_64F);
			CvMat* rot2 = cvCreateMat(4, 1, CV_64F);

			double rot_res1[4] = { 1, 0, 0, 0 };
			double rot_res2[4] = { 1, 0, 0, 0 };
			double rot_res[4] = { 1, 0, 0, 0 };
			double trans_res[4] = { (p1.translation[0] + p2.translation[0]) / 2, 
				(p1.translation[1] + p2.translation[1] - cube_size) / 2,
				(p1.translation[2] + p2.translation[2] + cube_size) / 2,
									(p1.translation[3] + p2.translation[3]) / 2 };
			
			p1.GetQuaternion(rot1);
			p2.GetQuaternion(rot2);

			Rotation::QuatMul(rot1->data.db, rot_x, rot_res1);
			Rotation::QuatMul(rot2->data.db, rot_x, rot_res2);

			Slerp(rot_res1, rot_res2, rot_res, 0.01);

			cvRelease((void**)&rot1);
			cvRelease((void**)&rot2);

			Pose p;
			p.SetTranslation(trans_res);
			p.SetQuaternion(rot_res);

			p_res = p;
		}
		int id = 10;
		double r = 1.0 - double(id + 1) / 32.0;
		double g = 1.0 - double(id * 3 % 32 + 1) / 32.0;
		double b = 1.0 - double(id * 7 % 32 + 1) / 32.0;

		//p_res.Output();
		Visualize(image, &cam, marker_size, p_res, CV_RGB(255, 0, 0));
	}
#endif
    if (flip_image) {
        cvFlip(image);
        image->origin = !image->origin;
    }
}

int main(int argc, char *argv[])
{
	try {
		std::string uniqueName = "kinect_1600";
		int width = 1980;
		int height = 1080;

		std::stringstream settingsFilename;
		settingsFilename << "camera_settings_" << uniqueName << ".xml";
		std::stringstream calibrationFilename;
		calibrationFilename << "camera_calibration_" << uniqueName << ".xml";

		cout << "Loading calibration: " << calibrationFilename.str();
		if (cam.SetCalib(calibrationFilename.str().c_str(), width, height)) {
			cout << " [Ok]" << endl;
		}
		else {
			cam.SetRes(width, height);
			cout << " [Fail]" << endl;
		}

		KinectVideoCapture capture;
		capture.open(0);
		Sleep(3000);
		
		cvNamedWindow("Image View", 1);
		while (capture.isOpened()){
			cv::Mat view0;
			cv::Mat viewGray;
			capture >> view0;

			IplImage* img = cvCloneImage(&(IplImage)view0);

			if (img != NULL){
				videocallback(img);
				cv::Mat temp(img);
				cvShowImage("Image View", img);
				cvRelease((void**)&img);
			}

			int c = 0xff & cv::waitKey(1);
			if ((c & 255) == 27 || c == 'q' || c == 'Q')
				break;
		}
		return 0;
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << endl;
	}
	catch (...) {
		std::cout << "Exception: unknown" << std::endl;
	}
}
