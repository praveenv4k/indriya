#include "KinectBodyHelper.h"

KinectBodyHelper* KinectBodyHelper::_instance = NULL;

// Singleton Helper class
KinectBodyHelper* KinectBodyHelper::Instance(){
	if (!_instance){
		_instance = new KinectBodyHelper();
	}
	return _instance;
}
KinectBodyHelper::KinectBodyHelper()
{
	_init();
}
KinectBodyHelper::~KinectBodyHelper()
{
	if (_instance){
		delete _instance;
		_instance = NULL;
	}
}
const std::map<KinectJoint_JointType, KinectJoint_JointType>& KinectBodyHelper::GetBones() const{
	return _bones;
}
int KinectBodyHelper::GetBoneWidth() const{
	return _boneWidth;
}
void KinectBodyHelper::GetBodyColor(int index, RaveVector<float>& color){
	if (index >= 0 && index < _bodyColors.size())
		color = _bodyColors[index];
	else
		ColorHelper::HexToRgb(BLACK, color);
}
void KinectBodyHelper::_init(){

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
	RaveVector<float> color;
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

	// Other colors
	handClosedBrush.w = 128; handClosedBrush.x = 255; handClosedBrush.y = 0; handClosedBrush.z = 0; // = new SolidColorBrush(Color.FromArgb(128, 255, 0, 0));
	handOpenBrush.w = 128; handOpenBrush.x = 0; handOpenBrush.y = 255; handOpenBrush.z = 0; // = new SolidColorBrush(Color.FromArgb(128, 0, 255, 0));
	handLassoBrush.w = 128; handLassoBrush.x = 0; handLassoBrush.y = 0; handLassoBrush.z = 255;// = new SolidColorBrush(Color.FromArgb(128, 0, 0, 255));
	trackedJointBrush.w = 255; trackedJointBrush.x = 68; trackedJointBrush.y = 192; trackedJointBrush.z = 68; // = new SolidColorBrush(Color.FromArgb(255, 68, 192, 68));
	ColorHelper::HexToRgb(YELLOW1, inferredJointBrush); // = Brushes.Yellow;
	ColorHelper::HexToRgb(GRAY1, inferredBonePen);// = new Pen(Brushes.Gray, 1);
}