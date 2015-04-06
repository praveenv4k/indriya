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
const std::vector<std::tuple<KinectJoint_JointType, KinectJoint_JointType>>& KinectBodyHelper::GetBones() const{
	return _bonesList;
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
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_Head, KinectJoint_JointType::KinectJoint_JointType_Neck));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_Neck, KinectJoint_JointType::KinectJoint_JointType_SpineShoulder));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_SpineShoulder, KinectJoint_JointType::KinectJoint_JointType_SpineMid));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_SpineMid, KinectJoint_JointType::KinectJoint_JointType_SpineBase));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_SpineShoulder, KinectJoint_JointType::KinectJoint_JointType_ShoulderRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_SpineShoulder, KinectJoint_JointType::KinectJoint_JointType_ShoulderLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_SpineBase, KinectJoint_JointType::KinectJoint_JointType_HipRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_SpineBase, KinectJoint_JointType::KinectJoint_JointType_HipLeft));

	// Right Arm
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_ShoulderRight, KinectJoint_JointType::KinectJoint_JointType_ElbowRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_ElbowRight, KinectJoint_JointType::KinectJoint_JointType_WristRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_WristRight, KinectJoint_JointType::KinectJoint_JointType_HandRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_HandRight, KinectJoint_JointType::KinectJoint_JointType_HandTipRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_WristRight, KinectJoint_JointType::KinectJoint_JointType_ThumbRight));

	// Left Arm
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_ShoulderLeft, KinectJoint_JointType::KinectJoint_JointType_ElbowLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_ElbowLeft, KinectJoint_JointType::KinectJoint_JointType_WristLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_WristLeft, KinectJoint_JointType::KinectJoint_JointType_HandLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_HandLeft, KinectJoint_JointType::KinectJoint_JointType_HandTipLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_WristLeft, KinectJoint_JointType::KinectJoint_JointType_ThumbLeft));

	// Right Leg
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_HipRight, KinectJoint_JointType::KinectJoint_JointType_KneeRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_KneeRight, KinectJoint_JointType::KinectJoint_JointType_AnkleRight));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_AnkleRight, KinectJoint_JointType::KinectJoint_JointType_FootRight));

	// Left Leg
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_HipLeft, KinectJoint_JointType::KinectJoint_JointType_KneeLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_KneeLeft, KinectJoint_JointType::KinectJoint_JointType_AnkleLeft));
	_bonesList.push_back(std::make_tuple(KinectJoint_JointType::KinectJoint_JointType_AnkleLeft, KinectJoint_JointType::KinectJoint_JointType_FootLeft));
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
	ColorHelper::FromArgb(128, 255, 0, 0, handClosedBrush);
	ColorHelper::FromArgb(128, 0, 255, 0, handOpenBrush);
	ColorHelper::FromArgb(128, 0, 0, 255, handLassoBrush);
	ColorHelper::FromArgb(255, 68, 192, 68, trackedJointBrush);

	ColorHelper::HexToRgb(YELLOW1, inferredJointBrush); // = Brushes.Yellow;
	ColorHelper::HexToRgb(GRAY1, inferredBonePen);// = new Pen(Brushes.Gray, 1);
}