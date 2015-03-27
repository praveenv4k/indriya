#ifndef __TRANSFORMATION_HELPER_H__
#define __TRANSFORMATION_HELPER_H__

#include "Pose.h"
#include <openrave-core.h>
#include "experimot\msgs\MessageTypes.h"

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
		Transform tf1(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_z, -(alvar::PI / 2)));
		Transform worldTfm = markerTfm*tf1;

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
		double rot_res[4] = { 1, 0, 0, 0 };
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

	static void RaveToProto(const OpenRAVE::Transform& tfm, experimot::msgs::Pose& pose){
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

	static void ProtoToRave(const experimot::msgs::Pose& pose, OpenRAVE::Transform& tfm){
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
};

#endif