#ifndef __TRANSFORMATION_HELPER_H__
#define __TRANSFORMATION_HELPER_H__

#include "Pose.h"
#include <openrave-core.h>

using namespace alvar;
using namespace OpenRAVE;

class TransformationHelper{
public:
	TransformationHelper(){

	}

	~TransformationHelper(){

	}

	static void computeTorsoFrame(Pose& worldPose, OpenRAVE::Transform& localTfmRave, Pose& torsoPose){
		OpenRAVE::Transform worldTfm;
		PoseToTransform(worldPose, worldTfm);

		// For rotating alvar frame -> Openrave - Z_UP, X_FRONT, Y_RIGHT
		RaveVector<dReal> rot_z(0, 0, 1);
		Transform tf1(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_z, -(alvar::PI / 2)));
		worldTfm = worldTfm*tf1;

		OpenRAVE::Transform localTfm;
#if 0
		OpenRAVEToAlvar(localTfmRave, localTfm);
#else
		localTfm = localTfmRave;
#endif
		OpenRAVE::Transform localInv = localTfm.inverse();


		OpenRAVE::Transform torsoTfm = worldTfm*localInv;

		TransformToPose(torsoTfm, torsoPose);
	}

	static void PoseToTransform(Pose& pose, Transform& tfm){
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

	static void OpenRAVEToAlvar(Transform& rave, Transform& alvar)
	{
		RaveVector<dReal> rot_x(1, 0, 0);
		RaveVector<dReal> rot_y(0, 1, 0);

		Transform tf1(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_x, alvar::PI / 2));
		Transform tf2(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(rot_y, alvar::PI / 2));

		Transform temp = rave * tf1;
		alvar = temp * tf2;

	}

	static void TransformToPose(Transform& tfm, Pose& pose){

		double rot[4] = { tfm.rot[0], tfm.rot[1], tfm.rot[2], tfm.rot[3] };
		double trans[3] = { tfm.trans.x, tfm.trans.y, tfm.trans.z };

		pose.SetQuaternion(rot);
		pose.SetTranslation(trans);
	}

	static void Rotate(Pose& input, RaveVector<dReal>& axis, dReal angle, Pose& output){
		OpenRAVE::Transform tfm;
		PoseToTransform(input, tfm);
		Transform rotTfm(OpenRAVE::geometry::matrixFromAxisAngle<dReal>(axis, angle));

		Transform out = tfm*rotTfm;

		TransformToPose(out, output);
	}
};

#endif