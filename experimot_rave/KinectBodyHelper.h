#ifndef __KINECTBODYHELPER_H__
#define __KINECTBODYHELPER_H__

#include <boost\thread.hpp>
#include <experimot\msgs\MessageTypes.h>
#include "ColorHelper.h"

using namespace experimot::msgs;
using namespace OpenRAVE;

class KinectBodyHelper;

typedef boost::shared_ptr<KinectBodyHelper> KinectBodyHelperPtr;


// Singleton Helper class
class KinectBodyHelper
{
public:
	static KinectBodyHelper* Instance();
	const std::map<KinectJoint_JointType, KinectJoint_JointType>& GetBones() const;
	int GetBoneWidth() const;
	void GetBodyColor(int index, RaveVector<float>& color);
	~KinectBodyHelper();

public:
	/// <summary>
	/// Radius of drawn hand circles
	/// </summary>
	const double HandSize = 30;

	/// <summary>
	/// Thickness of drawn joint lines
	/// </summary>
	const double JointThickness = 3;

	/// <summary>
	/// Thickness of clip edge rectangles
	/// </summary>
	const double ClipBoundsThickness = 10;

	/// <summary>
	/// Constant for clamping Z values of camera space points from being negative
	/// </summary>
	const float InferredZPositionClamp = 0.1f;

	/// <summary>
	/// Brush used for drawing hands that are currently tracked as closed
	/// </summary>
	RaveVector<float> handClosedBrush;// = new SolidColorBrush(Color.FromArgb(128, 255, 0, 0));

	/// <summary>
	/// Brush used for drawing hands that are currently tracked as opened
	/// </summary>
	RaveVector<float> handOpenBrush;// = new SolidColorBrush(Color.FromArgb(128, 0, 255, 0));

	/// <summary>
	/// Brush used for drawing hands that are currently tracked as in lasso (pointer) position
	/// </summary>
	RaveVector<float>handLassoBrush;// = new SolidColorBrush(Color.FromArgb(128, 0, 0, 255));

	/// <summary>
	/// Brush used for drawing joints that are currently tracked
	/// </summary>
	RaveVector<float>trackedJointBrush;// = new SolidColorBrush(Color.FromArgb(255, 68, 192, 68));

	/// <summary>
	/// Brush used for drawing joints that are currently inferred
	/// </summary>        
	RaveVector<float>inferredJointBrush;// = Brushes.Yellow;

	/// <summary>
	/// Pen used for drawing bones that are currently inferred
	/// </summary>        
	RaveVector<float>inferredBonePen;// = new Pen(Brushes.Gray, 1);

private:
	KinectBodyHelper();
	void _init();

private:
	static KinectBodyHelper* _instance;
	std::map<KinectJoint_JointType, KinectJoint_JointType> _bones;
	std::vector<RaveVector<float>> _bodyColors;
	int _boneWidth;
};


#endif
