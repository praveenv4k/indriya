#ifndef __KINECTBODYHELPER_H__
#define __KINECTBODYHELPER_H__

#include <boost\thread.hpp>
#include <experimot\msgs\MessageTypes.h>
#include "ColorHelper.h"

using namespace experimot::msgs;

class KinectBodyHelper;

typedef boost::shared_ptr<KinectBodyHelper> KinectBodyHelperPtr;

class KinectBodyHelper
{
public:
	KinectBodyHelperPtr Instance(){
		if (!_instance){
			_instance = KinectBodyHelperPtr(new KinectBodyHelper);
		}
		return _instance;
	}

private:
	static KinectBodyHelperPtr _instance;
	static std::map<KinectJoint_JointType, KinectJoint_JointType> _bones;
	static std::vector<Color> _bodyColors;
	static int _boneWidth;
	KinectBodyHelper()
	{
		_init();
	}
	void _init(){

		// Initialize vars
		_boneWidth = 6;

		// Initialize Bones

		// Torso
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_Head, KinectJoint_JointType::KinectJoint_JointType_Neck));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_Neck, KinectJoint_JointType::KinectJoint_JointType_SpineShoulder));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_SpineShoulder, KinectJoint_JointType::KinectJoint_JointType_SpineMid));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_SpineMid, KinectJoint_JointType::KinectJoint_JointType_SpineBase));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_SpineShoulder, KinectJoint_JointType::KinectJoint_JointType_ShoulderRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_SpineShoulder, KinectJoint_JointType::KinectJoint_JointType_ShoulderLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_SpineBase, KinectJoint_JointType::KinectJoint_JointType_HipRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_SpineBase, KinectJoint_JointType::KinectJoint_JointType_HipLeft));

		// Right Arm
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_ShoulderRight, KinectJoint_JointType::KinectJoint_JointType_ElbowRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_ElbowRight, KinectJoint_JointType::KinectJoint_JointType_WristRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_WristRight, KinectJoint_JointType::KinectJoint_JointType_HandRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_HandRight, KinectJoint_JointType::KinectJoint_JointType_HandTipRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_WristRight, KinectJoint_JointType::KinectJoint_JointType_ThumbRight));

		// Left Arm
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_ShoulderLeft, KinectJoint_JointType::KinectJoint_JointType_ElbowLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_ElbowLeft, KinectJoint_JointType::KinectJoint_JointType_WristLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_WristLeft, KinectJoint_JointType::KinectJoint_JointType_HandLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_HandLeft, KinectJoint_JointType::KinectJoint_JointType_HandTipLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_WristLeft, KinectJoint_JointType::KinectJoint_JointType_ThumbLeft));

		// Right Leg
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_HipRight, KinectJoint_JointType::KinectJoint_JointType_KneeRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_KneeRight, KinectJoint_JointType::KinectJoint_JointType_AnkleRight));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_AnkleRight, KinectJoint_JointType::KinectJoint_JointType_FootRight));

		// Left Leg
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_HipLeft, KinectJoint_JointType::KinectJoint_JointType_KneeLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_KneeLeft, KinectJoint_JointType::KinectJoint_JointType_AnkleLeft));
		_bones.insert(std::pair<KinectJoint_JointType, KinectJoint_JointType>(KinectJoint_JointType::KinectJoint_JointType_AnkleLeft, KinectJoint_JointType::KinectJoint_JointType_FootLeft));


		// Initialize Body Colors

		// populate body colors, one for each BodyIndex
		Color color;
		ColorHelper::HexToRgb(RED1, color);
		_bodyColors.push_back(color);
		ColorHelper::HexToRgb(ORANGE, color);
		_bodyColors.push_back(color);
		ColorHelper::HexToRgb(GREEN, color);
		_bodyColors.push_back(color);
		ColorHelper::HexToRgb(BLUE, color);
		_bodyColors.push_back(color);
		ColorHelper::HexToRgb(INDIGO, color);
		_bodyColors.push_back(color);
		ColorHelper::HexToRgb(VIOLET, color);
		_bodyColors.push_back(color);
	}

	~KinectBodyHelper()
	{
	}
};


#endif
