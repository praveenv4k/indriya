#ifndef __TRANSFORMATION_HELPER_H__
#define __TRANSFORMATION_HELPER_H__

#include "Pose.h"
#include <openrave-core.h>
#include "experimot\msgs\MessageTypes.h"
#include "experimot\common\Common.h"

using namespace alvar;
using namespace OpenRAVE;

class TransformationHelper{
public:
	TransformationHelper(){

	}

	~TransformationHelper(){

	}

	static void ComputeTorsoFrame(const Pose& worldPose, const OpenRAVE::Transform& localTfmRave, Pose& torsoPose){
		OpenRAVE::Transform worldTfm;
		PoseToTransform(worldPose, worldTfm);
		OpenRAVE::Transform torsoTfm;
		ComputeTorsoFrame(worldTfm, localTfmRave, torsoTfm);
		TransformToPose(torsoTfm, torsoPose);
	}

	static void ComputeTorsoFrame(const OpenRAVE::Transform& markerTfm, const OpenRAVE::Transform& localTfmRave, OpenRAVE::Transform& torsoTfm){
		// For rotating alvar frame -> Openrave - Z_UP, X_FRONT, Y_RIGHT
		RaveVector<dReal> rot_z(0, 0, 1);
		
#if 0 // Since the appropriate orientation is taken care by the marker detection module
		Transform tf1(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_z, -(alvar::PI / 2)));
		Transform worldTfm = markerTfm*tf1;
#else
		Transform worldTfm = markerTfm;
#endif
		OpenRAVE::Transform localTfm;
#if 0
		OpenRAVEToAlvar(localTfmRave, localTfm);
#else
		localTfm = localTfmRave;
#endif
		OpenRAVE::Transform localInv = localTfm.inverse();
		torsoTfm = worldTfm*localInv;
	}

	static void PoseToTransform(const Pose& pose, Transform& tfm){
		CvMat* rot = cvCreateMat(4, 1, CV_64F);
		pose.GetQuaternion(rot);

		tfm.rot[0] = rot->data.db[0];
		tfm.rot[1] = rot->data.db[1];
		tfm.rot[2] = rot->data.db[2];
		tfm.rot[3] = rot->data.db[3];

		tfm.trans.x = pose.translation[0];
		tfm.trans.y = pose.translation[1];
		tfm.trans.z = pose.translation[2];

		cvRelease((void**)&rot);
	}

	static void OpenRAVEToAlvar(const Transform& rave, Transform& alvar)
	{
		RaveVector<dReal> rot_x(1, 0, 0);
		RaveVector<dReal> rot_y(0, 1, 0);

		Transform tf1(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_x, alvar::PI / 2));
		Transform tf2(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_y, alvar::PI / 2));

		Transform temp = rave * tf1;
		alvar = temp * tf2;

	}

	static void OpenGLToOpenRAVE(double* gl_mat, TransformMatrix& mat, bool transposed = true){
		if (gl_mat != NULL){
			if (transposed){
				mat.rotfrommat(gl_mat[0], gl_mat[4], gl_mat[8], gl_mat[1], gl_mat[5], gl_mat[9], gl_mat[2], gl_mat[6], gl_mat[10]);
				mat.trans = Vector(gl_mat[12], gl_mat[13], gl_mat[14]);
			}
			else{
				mat.rotfrommat(gl_mat[0], gl_mat[1], gl_mat[2], gl_mat[4], gl_mat[5], gl_mat[6], gl_mat[8], gl_mat[9], gl_mat[10]);
				mat.trans = Vector(gl_mat[3], gl_mat[7], gl_mat[11]);
			}
		}
	}

	static void TransformToPose(const Transform& tfm, Pose& pose){

		double rot[4] = { tfm.rot[0], tfm.rot[1], tfm.rot[2], tfm.rot[3] };
		double trans[3] = { tfm.trans.x, tfm.trans.y, tfm.trans.z };

		pose.SetQuaternion(rot);
		pose.SetTranslation(trans);
	}

	static void Rotate(const Pose& input, const RaveVector<dReal>& axis, dReal angle, Pose& output){
		OpenRAVE::Transform tfm;
		PoseToTransform(input, tfm);
		Transform rotTfm(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(axis, angle));

		Transform out = tfm*rotTfm;

		TransformToPose(out, output);
	}

	static void RaveToProto(const OpenRAVE::Transform& tfm, Indriya::Core::Msgs::Pose& pose){
		// Set Position
		pose.mutable_position()->set_x(tfm.trans[0]);
		pose.mutable_position()->set_y(tfm.trans[1]);
		pose.mutable_position()->set_z(tfm.trans[2]);
		// Set Orientation
		pose.mutable_orientation()->set_w(tfm.rot[0]);
		pose.mutable_orientation()->set_x(tfm.rot[1]);
		pose.mutable_orientation()->set_y(tfm.rot[2]);
		pose.mutable_orientation()->set_z(tfm.rot[3]);
	}

	static void RaveToProto(const std::map<std::string, OpenRAVE::Transform>& tfmMap, Indriya::Core::Msgs::Pose_V& poseVector){
		FOREACHC(it, tfmMap){
			// Set Position
			if (!it->first.empty()){
				Indriya::Core::Msgs::Pose* pose = poseVector.add_pose();
				pose->set_name(it->first.c_str());
				pose->mutable_position()->set_x(it->second.trans[0]);
				pose->mutable_position()->set_y(it->second.trans[1]);
				pose->mutable_position()->set_z(it->second.trans[2]);
				// Set Orientation
				pose->mutable_orientation()->set_w(it->second.rot[0]);
				pose->mutable_orientation()->set_x(it->second.rot[1]);
				pose->mutable_orientation()->set_y(it->second.rot[2]);
				pose->mutable_orientation()->set_z(it->second.rot[3]);
			}
		}
	}

	static void ProtoToRave(const Indriya::Core::Msgs::Pose& pose, OpenRAVE::Transform& tfm){
		// Set Position
		tfm.trans[0] = pose.position().x();
		tfm.trans[1] = pose.position().y();
		tfm.trans[2] = pose.position().z();
		// Set Orientation
		tfm.rot[0] = pose.orientation().w();
		tfm.rot[1] = pose.orientation().x();
		tfm.rot[2] = pose.orientation().y();
		tfm.rot[3] = pose.orientation().z();
	}

	static void Slerp(double* q1, double* q2, double* qr, double lambda)
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

	// Converts a given Rotation Matrix to Euler angles
	static cv::Mat rot2euler(const cv::Mat & rotationMatrix)
	{
		cv::Mat euler(3, 1, CV_64F);

		double m00 = rotationMatrix.at<double>(0, 0);
		double m02 = rotationMatrix.at<double>(0, 2);
		double m10 = rotationMatrix.at<double>(1, 0);
		double m11 = rotationMatrix.at<double>(1, 1);
		double m12 = rotationMatrix.at<double>(1, 2);
		double m20 = rotationMatrix.at<double>(2, 0);
		double m22 = rotationMatrix.at<double>(2, 2);

		double x, y, z;

		// Assuming the angles are in radians.
		if (m10 > 0.998) { // singularity at north pole
			x = 0;
			y = CV_PI / 2;
			z = atan2(m02, m22);
		}
		else if (m10 < -0.998) { // singularity at south pole
			x = 0;
			y = -CV_PI / 2;
			z = atan2(m02, m22);
		}
		else
		{
			x = atan2(-m12, m11);
			y = asin(m10);
			z = atan2(-m20, m00);
		}

		euler.at<double>(0) = x;
		euler.at<double>(1) = y;
		euler.at<double>(2) = z;

		return euler;
	}

	// Converts a given Euler angles to Rotation Matrix
	static cv::Mat euler2rot(const cv::Mat & euler)
	{
		cv::Mat rotationMatrix(3, 3, CV_64F);

		double x = euler.at<double>(0);
		double y = euler.at<double>(1);
		double z = euler.at<double>(2);

		// Assuming the angles are in radians.
		double ch = cos(z);
		double sh = sin(z);
		double ca = cos(y);
		double sa = sin(y);
		double cb = cos(x);
		double sb = sin(x);

		double m00, m01, m02, m10, m11, m12, m20, m21, m22;

		m00 = ch * ca;
		m01 = sh*sb - ch*sa*cb;
		m02 = ch*sa*sb + sh*cb;
		m10 = sa;
		m11 = ca*cb;
		m12 = -ca*sb;
		m20 = -sh*ca;
		m21 = sh*sa*cb + ch*sb;
		m22 = -sh*sa*sb + ch*cb;

		rotationMatrix.at<double>(0, 0) = m00;
		rotationMatrix.at<double>(0, 1) = m01;
		rotationMatrix.at<double>(0, 2) = m02;
		rotationMatrix.at<double>(1, 0) = m10;
		rotationMatrix.at<double>(1, 1) = m11;
		rotationMatrix.at<double>(1, 2) = m12;
		rotationMatrix.at<double>(2, 0) = m20;
		rotationMatrix.at<double>(2, 1) = m21;
		rotationMatrix.at<double>(2, 2) = m22;

		return rotationMatrix;
	}

	static void RaveToCv(const OpenRAVE::Transform& tfm, cv::Mat& trans, cv::Mat& rot){
		OpenRAVE::TransformMatrix mat = OpenRAVE::geometry::matrixFromQuat(tfm.rot);

		rot.at<double>(0, 0) = (double)mat.m[0];
		rot.at<double>(0, 1) = (double)mat.m[1];
		rot.at<double>(0, 2) = (double)mat.m[2];
		rot.at<double>(1, 0) = (double)mat.m[4];
		rot.at<double>(1, 1) = (double)mat.m[5];
		rot.at<double>(1, 2) = (double)mat.m[6];
		rot.at<double>(2, 0) = (double)mat.m[8];
		rot.at<double>(2, 1) = (double)mat.m[9];
		rot.at<double>(2, 2) = (double)mat.m[10];

		trans.at<double>(0) = (double)tfm.trans.x;
		trans.at<double>(1) = (double)tfm.trans.y;
		trans.at<double>(2) = (double)tfm.trans.z;
	}

	static void CvToRave(const cv::Mat& trans, const cv::Mat& rot, OpenRAVE::Transform& tfm){
		OpenRAVE::TransformMatrix mat;
		//OpenRAVE::geometry::quatFromMatrix
		mat.m[0] = rot.at<double>(0, 0);
		mat.m[1] = rot.at<double>(0, 1);
		mat.m[2] = rot.at<double>(0, 2);
		mat.m[4] = rot.at<double>(1, 0);
		mat.m[5] = rot.at<double>(1, 1);
		mat.m[6] = rot.at<double>(1, 2);
		mat.m[8] = rot.at<double>(2, 0);
		mat.m[9] = rot.at<double>(2, 1);
		mat.m[10] = rot.at<double>(2, 2);

		tfm.trans = OpenRAVE::Vector(trans.at<double>(0), trans.at<double>(1), trans.at<double>(2));
		tfm.rot = OpenRAVE::geometry::quatFromMatrix(mat);
		/*trans.at<double>(0, 0) = (double)mat.trans.x;
		trans.at<double>(1, 0) = (double)mat.trans.y;
		trans.at<double>(2, 0) = (double)mat.trans.z;*/
	}

};

#endif