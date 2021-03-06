#include <openrave-core.h>
#include <vector>
#include <cstring>
#include <sstream>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "csv.h"

#include <boost/typeof/std/string.hpp>
#include <boost/typeof/std/vector.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/map.hpp>
#include <boost/typeof/std/set.hpp>
#include <boost/typeof/std/string.hpp>
#include <signal.h>

#include <azmq\actor.hpp>
#include <boost/utility/string_ref.hpp>
#include "asio_server.h"

#include "Indriya\Msgs\MessageTypes.h"
#include <zmq.hpp>
#include <zhelpers.hpp>
#include <boost/atomic.hpp>
#include "KinectBodyHelper.h"

#include <boost\program_options.hpp>
#include <Indriya\Common\ParameterClient.h>
#include <Indriya\Common\ParameterHelper.h>
#include <Indriya\Common\CallbackBase.h>
#include <Indriya\Common\MessageSubscriber.h>
#include <Indriya\Common\MessagePublisher.h>

#include <boost\signals2.hpp>

boost::atomic<bool> done(false);

using namespace OpenRAVE;
using namespace std;
using namespace boost;

void SetViewer(EnvironmentBasePtr penv, const string& viewername)
{
    ViewerBasePtr viewer = RaveCreateViewer(penv,viewername);
    BOOST_ASSERT(!!viewer);

    // attach it to the environment:
    penv->Add(viewer);

    // finally call the viewer's infinite loop (this is why a separate thread is needed)
    bool showgui = true;
    viewer->main(showgui);
}

bool orRobotSetActiveDOFs(RobotBasePtr probot, vector<double> jointVals)
{
	if (!probot) {
		return false;
	}
	int numindices = jointVals.size();
	if (numindices < 0) {
		return false;
	}
	int activeDOF = probot->GetActiveDOF();
	if (activeDOF != numindices){
		std::cout << "Actual DOF: " << activeDOF << ", Requested DOF: " << numindices << std::endl;
	}
	else{
		probot->SetActiveDOFValues(jointVals, false);
	}
	return true;
}

RobotBasePtr orMacroGetRobot(EnvironmentBasePtr penv, int index)
{
	if (!index) {
		return RobotBasePtr();
	}
	KinBodyPtr pbody = penv->GetBodyFromEnvironmentId(index);
	if (!pbody || !pbody->IsRobot()) {
		return RobotBasePtr();
	}
	return RaveInterfaceCast<RobotBase>(pbody);
}

void orDispRobots(EnvironmentBasePtr penv)
{
	vector<RobotBasePtr> robots;
	penv->GetRobots(robots);
	FOREACH(it, robots){
		cout << (*it)->GetName() << std::endl;
		FOREACHC(jit, (*it)->GetJoints())
		{
			cout << (*jit)->GetName() << std::endl;
		}
	}
}

OpenRAVE::GraphHandlePtr kinectModel;

void orInitEnvironment(EnvironmentBasePtr penv, std::string& scenefilename, std::vector<string>& modelFiles)
{
	penv->Load(scenefilename); // load the scene

	Transform defTransform(Vector(0.53522962205139013, 0.517639095032381, -0.46421923037403362, 0.47966605583856331), Vector(0.084682732203775871, -0.043060926653530942, 1.139326178779198));
	
	vector<RobotBasePtr> robots;
	penv->GetRobots(robots);
	FOREACH(it, robots){
		cout << (*it)->GetName() << std::endl;
		(*it)->SetTransform(defTransform);
		break;
	}
	FOREACH(it, modelFiles){
		OpenRAVE::KinBodyPtr pModel = penv->ReadKinBodyXMLFile(*it);
		penv->Add(pModel);
	}
}

class RobotStateListener{
public:
	//  Prepare our context and subscriber
	RobotStateListener(){
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect("tcp://localhost:5563");
		m_strSubsribeTo = std::string("RSP");
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	RobotStateListener(const string host, int port, const string topic){
		std::stringstream ss;
		ss << host << ":" << port;
		string strAddr = ss.str();

		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect(strAddr.c_str());
		m_strSubsribeTo = topic;
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	void Listen(EnvironmentBasePtr penv){
		while (!done) {
			zmq::message_t address;
			m_pSocket->recv(&address);

			zmq::message_t data;
			m_pSocket->recv(&data);

			{
				Indriya::Core::Msgs::JointValueVector jVector;
				if (jVector.ParseFromArray(data.data(), data.size())){
					//jVector.PrintDebugString();
					//std::cout << "Size: " << jvMap.map_field_size() << std::endl;
					std::vector<double> jointValues;
					jointValues.resize(jVector.jointvalues_size());
					for (google::protobuf::int32 i = 0; i < jVector.jointvalues_size(); i++){
						const Indriya::Core::Msgs::JointValue& jVal = jVector.jointvalues(i);
						jointValues[jVal.id()] = jVal.value();
					}

					EnvironmentMutex::scoped_lock lock(penv->GetMutex());
					RobotBasePtr probot = orMacroGetRobot(penv, 1);
					if (probot){
						probot->SetDOFValues(jointValues, false);
					}
				}

			}
		}
	}
private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
};

class TorsoPoseListener{
public:
	//  Prepare our context and subscriber
	TorsoPoseListener(){
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect("tcp://localhost:5566");
		m_strSubsribeTo = std::string("TPP");
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	TorsoPoseListener(const string host, int port, const string topic){
		std::stringstream ss;
		ss << host << ":" << port;
		string strAddr = ss.str();

		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect(strAddr.c_str());
		m_strSubsribeTo = topic;
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	static void ProtoToRave(const Indriya::Core::Msgs::Pose& pose, OpenRAVE::Transform& tfm){
		// Set Position
		tfm.trans[0] = pose.position().x() / 1000;
		tfm.trans[1] = pose.position().y() / 1000;
		tfm.trans[2] = pose.position().z() / 1000;
		// Set Orientation
		
		tfm.rot[0] = pose.orientation().w();
		tfm.rot[1] = pose.orientation().x();
		tfm.rot[2] = pose.orientation().y();
		tfm.rot[3] = pose.orientation().z();
	}

	static void ProtoToRave(const Indriya::Core::Msgs::Pose_V& poses, const std::string& frameName, OpenRAVE::Transform& tfm){
		// Set Position
		for (int i = 0; i < poses.pose_size(); i++){
			if (poses.pose(i).name() == frameName){
				const Indriya::Core::Msgs::Pose pose = poses.pose(i);
				tfm.trans[0] = pose.position().x() / 1000;
				tfm.trans[1] = pose.position().y() / 1000;
				tfm.trans[2] = pose.position().z() / 1000;
				// Set Orientation

				tfm.rot[0] = pose.orientation().w();
				tfm.rot[1] = pose.orientation().x();
				tfm.rot[2] = pose.orientation().y();
				tfm.rot[3] = pose.orientation().z();
			}
		}
	}

	void Listen(EnvironmentBasePtr penv){
		while (!done) {
			zmq::message_t address;
			m_pSocket->recv(&address);

			zmq::message_t data;
			m_pSocket->recv(&data);

			{
				Indriya::Core::Msgs::Pose_V pose;
				if (pose.ParseFromArray(data.data(), data.size())){
					Transform tfm;
					ProtoToRave(pose, "torso_frame_kinect", tfm);
					{
						EnvironmentMutex::scoped_lock lock(penv->GetMutex());
						RobotBasePtr probot = orMacroGetRobot(penv, 1);
						if (probot){
							probot->SetTransform(tfm);
						}
					}
				}
			}
		}
	}
private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
};

class KinectStateListener{
public:
	//  Prepare our context and subscriber
	KinectStateListener(){
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect("tcp://localhost:5564");
		m_strSubsribeTo = std::string("KSP");
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	KinectStateListener(const string host, int port, const string topic){
		std::stringstream ss;
		ss << host << ":" << port;
		string strAddr = ss.str();

		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect(strAddr.c_str());
		m_strSubsribeTo = topic;
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	void KinectPointsProcess(const Indriya::Core::Msgs::Vector3d& p0, RaveVector<float>& p0_out){
#if 1
		//p0_out = RaveVector<float>(p0.z(), p0.x(), p0.y());
		p0_out = RaveVector<float>(p0.x(), p0.y(), p0.z());
#else
		RaveVector<float> jp0(p0.x(), p0.y(), p0.z());
		RaveTransform<float> tf(RaveVector<float>(1, 0, 0, 0), jp0);
		RaveTransform<float> rot_x(geometry::quatFromAxisAngle(RaveVector<float>(1, 0, 0), (float)(-OpenRAVE::PI / 2)), RaveVector<float>(0, 0, 0));
		RaveTransform<float> rot_z(geometry::quatFromAxisAngle(RaveVector<float>(0, 0, 1), (float)(-OpenRAVE::PI / 2)), RaveVector<float>(0, 0, 0));
		RaveTransform<float> out = tf*rot_x*rot_z;
		p0_out = out.trans;
#endif
	}

	void Listen(EnvironmentBasePtr penv){
		list<GraphHandlePtr> listgraphs;
		while (!done) {
			zmq::message_t address;
			m_pSocket->recv(&address);

			zmq::message_t data;
			m_pSocket->recv(&data);

			{
				Indriya::Core::Msgs::KinectBodies kBodies;
				if (kBodies.ParseFromArray(data.data(), data.size())){
					//kBodies.PrintDebugString();
					EnvironmentMutex::scoped_lock lock(penv->GetMutex()); // lock environment
					listgraphs.clear();
					int bone_width = KinectBodyHelper::Instance()->GetBoneWidth();
					int no_conf_width = 2;
					if (kBodies.body_size() <= 0){
						//std::cout << "There is no body information" << std::endl;
					}
					else{
						for (google::protobuf::int32 i = 0; i < kBodies.body_size(); i++){
							const Indriya::Core::Msgs::KinectBody& kBody = kBodies.body(i);
							RaveVector<float> bColor;
							KinectBodyHelper::Instance()->GetBodyColor(kBody.trackingid(), bColor);
							const std::vector<std::tuple<KinectJoint_JointType, KinectJoint_JointType>>& boneMap = KinectBodyHelper::Instance()->GetBones();
							FOREACHC(it, boneMap){
								KinectJoint_JointType item1 = std::get<0>(*it);
								KinectJoint_JointType item2 = std::get<1>(*it);

								const Indriya::Core::Msgs::KinectJoint& joint0 = kBody.joints(item1);
								const Indriya::Core::Msgs::KinectJoint& joint1 = kBody.joints(item2);

								// If we can't find either of these joints, exit
								if (joint0.state() == KinectJoint_TrackingState::KinectJoint_TrackingState_NotTracked ||
									joint1.state() == KinectJoint_TrackingState::KinectJoint_TrackingState_NotTracked)
								{

								}
								else{

									// We assume all drawn bones are inferred unless BOTH joints are tracked
									RaveVector<float> drawPen = KinectBodyHelper::Instance()->inferredBonePen;
									int boneW = no_conf_width;
									if ((joint0.state() == KinectJoint_TrackingState_Tracked) && (joint1.state() == KinectJoint_TrackingState_Tracked))
									{
										drawPen = bColor;
										boneW = bone_width;
									}

									const Indriya::Core::Msgs::Vector3d& jointPos0 = joint0.position();
									const Indriya::Core::Msgs::Vector3d& jointPos1 = joint1.position();
									RaveVector<float> jp0, jp1;
									KinectPointsProcess(jointPos0, jp0);
									KinectPointsProcess(jointPos1, jp1);

									vector<RaveVector<float>> vpoints;
									vpoints.push_back(jp0);
									vpoints.push_back(jp1);

									listgraphs.push_back(penv->drawlinestrip(&vpoints[0].x, vpoints.size(), sizeof(vpoints[0]), boneW, drawPen));
								}
							}
							RaveVector<float> extents(0.02, 0.02, 0.02);
							vector<RaveVector<float>> jointPoints;
							vector<RaveVector<float>> jointColors;
							for (google::protobuf::int32 i = 0; i < kBody.joints_size(); i++)
							{
								bool draw = true;
								RaveVector<float> drawBrush;
								const Indriya::Core::Msgs::KinectJoint& joint = kBody.joints(i);
								KinectJoint_TrackingState state = joint.state();

								if (state == KinectJoint_TrackingState::KinectJoint_TrackingState_Tracked)
								{
									drawBrush = KinectBodyHelper::Instance()->trackedJointBrush;
								}
								else if (state == KinectJoint_TrackingState::KinectJoint_TrackingState_Inferred)
								{
									drawBrush = KinectBodyHelper::Instance()->inferredJointBrush;
								}
								else
								{
									draw = false;
								}

								if (draw)
								{
									const Indriya::Core::Msgs::Vector3d& jointPos = joint.position();
									RaveVector<float> pos(jointPos.x(), jointPos.y(), jointPos.z());
									KinectPointsProcess(jointPos, pos);
									jointPoints.push_back(pos);
									jointColors.push_back(drawBrush);
								}
							}
							if (jointPoints.size() > 0){
								listgraphs.push_back(penv->plot3(&jointPoints[0].x, jointPoints.size(), sizeof(jointPoints[0]), KinectBodyHelper::Instance()->JointThickness, &jointColors[0].x, 1, true));
							}
						}
					}
				}
				else{
					std::cout << "Failed to parse the kinect body information" << std::endl;
				}
			}
		}
	}

	/// <summary>
	/// Draws a hand symbol if the hand is tracked: red circle = closed, green circle = opened; blue circle = lasso
	/// </summary>
	/// <param name="handState">state of the hand</param>
	/// <param name="handPosition">position of the hand</param>
	/// <param name="drawingContext">drawing context to draw to</param>
	void DrawHand(KinectBody_HandState handState, Vector3d& handPosition)
	{
		switch (handState)
		{
		case KinectBody_HandState::KinectBody_HandState_HS_Closed:
			//drawingContext.DrawEllipse(this.handClosedBrush, null, handPosition, HandSize, HandSize);
			//TODO Draw
			break;

		case KinectBody_HandState::KinectBody_HandState_HS_Open:
			//drawingContext.DrawEllipse(this.handOpenBrush, null, handPosition, HandSize, HandSize);
			break;

		case KinectBody_HandState::KinectBody_HandState_HS_Lasso:
			//drawingContext.DrawEllipse(this.handLassoBrush, null, handPosition, HandSize, HandSize);
			break;
		}
	}


private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
};

class HumanPoseListener{
public:
	//  Prepare our context and subscriber
	HumanPoseListener() {
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect("tcp://localhost:5571");
		m_strSubsribeTo = std::string("HPP");
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
		m_strHumanModel = "data/human";
	}

	HumanPoseListener(const string host, int port, const string topic, const string humanTorsoBaseModel){
		std::stringstream ss;
		ss << host << ":" << port;
		string strAddr = ss.str();
		m_strHumanModel = humanTorsoBaseModel;
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_SUB));
		m_pSocket->connect(strAddr.c_str());
		m_strSubsribeTo = topic;
		m_pSocket->setsockopt(ZMQ_SUBSCRIBE, m_strSubsribeTo.c_str(), m_strSubsribeTo.size());
	}

	void Convert(const Indriya::Core::Msgs::Vector3d& trans, const Indriya::Core::Msgs::Quaternion& rot, Transform& p0_out){
		p0_out.trans = Vector(trans.x(), trans.y(), trans.z());
		Vector quat = Vector(rot.w(), rot.x(), rot.y(), rot.z());
		quat = quat.normalize4();
		p0_out.rot = quat;
	}


	void Listen(EnvironmentBasePtr penv){
		list<KinBodyPtr> listgraphs;
		while (!done) {
			try{
				zmq::message_t address;
				m_pSocket->recv(&address);

				zmq::message_t data;
				m_pSocket->recv(&data);

				{
					Indriya::Core::Msgs::Humans humans;
					if (humans.ParseFromArray(data.data(), data.size())){
						//kBodies.PrintDebugString();
						EnvironmentMutex::scoped_lock lock(penv->GetMutex()); // lock environment
						FOREACH(it, listgraphs){
							penv->Remove(*it);
						}
						listgraphs.clear();
						if (humans.human_size() <= 0){
							//std::cout << "There is no body information" << std::endl;
						}
						else{
							continue; // For debug
							for (google::protobuf::int32 i = 0; i < humans.human_size(); i++){
								const Indriya::Core::Msgs::Human& human = humans.human(i);
								stringstream ss;
								ss << m_strHumanModel << human.id();
								std::string fileName(ss.str() + ".kinbody.xml");
								RaveVector<float> bColor;
								KinectBodyHelper::Instance()->GetBodyColor(human.id()-1, bColor);
								OpenRAVE::KinBodyPtr pModel = penv->ReadKinBodyXMLFile(fileName);
								Transform tfm;
								Convert(human.torso_position(), human.orientation(), tfm);
								pModel->SetTransform(tfm);
								penv->Add(pModel);
								OpenRAVE::KinBody::LinkPtr link = pModel->GetLink(ss.str());
								if (link != 0){
									link->GetGeometry(0)->SetDiffuseColor(bColor);
								}
								listgraphs.push_back(pModel);
							}
						}
					}
					else{
						std::cout << "Failed to parse the kinect body information" << std::endl;
					}
				}
			}
			catch (std::exception& ex){
				std::cout << "HumanPoseListener Exception: " << ex.what() << std::endl;
			}
		}
	}
private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strSubsribeTo;
	std::string m_strHumanModel;
};

class RobotStatePublisher{
public:
	typedef boost::shared_ptr<csv::io::CSVReader<25>> CsvReaderPtr;
	RobotStatePublisher(){
		//  Prepare our context and publisher
		m_pContext = ZmqContextPtr(new zmq::context_t(1));
		m_pSocket = ZmqSocketPtr(new zmq::socket_t(*m_pContext, ZMQ_PUB));
		m_pSocket->bind("tcp://*:5563");
		m_strPublisherName = std::string("RSP");
	}

	~RobotStatePublisher(){
		m_pSocket->close();
	}

	void Init(std::string& logFileName){
		CsvReaderPtr csvReaderPtr;
		if (!csvReaderPtr){
			csvReaderPtr = CsvReaderPtr(new csv::io::CSVReader<25>(logFileName.c_str()));
			csvReaderPtr->read_header(csv::io::ignore_extra_column
				, "Device/SubDeviceList/HeadPitch/Position/Sensor/Value"
				, "Device/SubDeviceList/HeadYaw/Position/Sensor/Value"
				, "Device/SubDeviceList/LAnklePitch/Position/Sensor/Value"
				, "Device/SubDeviceList/LAnkleRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/LElbowRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/LElbowYaw/Position/Sensor/Value"
				, "Device/SubDeviceList/LHand/Position/Sensor/Value"
				, "Device/SubDeviceList/LHipPitch/Position/Sensor/Value"
				, "Device/SubDeviceList/LHipRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/LHipYawPitch/Position/Sensor/Value"
				, "Device/SubDeviceList/LKneePitch/Position/Sensor/Value"
				, "Device/SubDeviceList/LShoulderPitch/Position/Sensor/Value"
				, "Device/SubDeviceList/LShoulderRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/LWristYaw/Position/Sensor/Value"
				, "Device/SubDeviceList/RAnklePitch/Position/Sensor/Value"
				, "Device/SubDeviceList/RAnkleRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/RElbowRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/RElbowYaw/Position/Sensor/Value"
				, "Device/SubDeviceList/RHand/Position/Sensor/Value"
				, "Device/SubDeviceList/RHipPitch/Position/Sensor/Value"
				, "Device/SubDeviceList/RHipRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/RKneePitch/Position/Sensor/Value"
				, "Device/SubDeviceList/RShoulderPitch/Position/Sensor/Value"
				, "Device/SubDeviceList/RShoulderRoll/Position/Sensor/Value"
				, "Device/SubDeviceList/RWristYaw/Position/Sensor/Value");

			map<int, int> jointMap;
			jointMap.insert(std::pair<int, int>(0, 1));
			jointMap.insert(std::pair<int, int>(1, 0));
			jointMap.insert(std::pair<int, int>(2, 9));
			jointMap.insert(std::pair<int, int>(3, 8));
			jointMap.insert(std::pair<int, int>(4, 7));
			jointMap.insert(std::pair<int, int>(5, 10));
			jointMap.insert(std::pair<int, int>(6, 2));
			jointMap.insert(std::pair<int, int>(7, 3));
			jointMap.insert(std::pair<int, int>(8, 11));
			jointMap.insert(std::pair<int, int>(9, 12));
			jointMap.insert(std::pair<int, int>(10, 5));
			jointMap.insert(std::pair<int, int>(11, 4));
			jointMap.insert(std::pair<int, int>(12, 13));
			jointMap.insert(std::pair<int, int>(13, 6));
			jointMap.insert(std::pair<int, int>(14, 20));
			jointMap.insert(std::pair<int, int>(15, 19));
			jointMap.insert(std::pair<int, int>(16, 21));
			jointMap.insert(std::pair<int, int>(17, 14));
			jointMap.insert(std::pair<int, int>(18, 15));
			jointMap.insert(std::pair<int, int>(19, 22));
			jointMap.insert(std::pair<int, int>(20, 23));
			jointMap.insert(std::pair<int, int>(21, 17));
			jointMap.insert(std::pair<int, int>(22, 16));
			jointMap.insert(std::pair<int, int>(23, 24));
			jointMap.insert(std::pair<int, int>(24, 18));

			vector<double> vals;
			vals.resize(25);
			while (csvReaderPtr->read_row(vals[0], vals[1], vals[2], vals[3],
				vals[4], vals[5], vals[6], vals[7],
				vals[8], vals[9], vals[10], vals[11],
				vals[12], vals[13], vals[14], vals[15],
				vals[16], vals[17], vals[18], vals[19],
				vals[20], vals[21], vals[22], vals[23], vals[24]
				))
			{
				{
					//Indriya::Core::Msgs::JointValueMapPtr jointValMapPtr = Indriya::Core::Msgs::JointValueMapPtr(new Indriya::Core::Msgs::JointValueMap);
					Indriya::Core::Msgs::JointValueVector jVector;
					vector<double> jointVals;
					for (google::protobuf::int32 id = 0; id < vals.size(); id++){
						Indriya::Core::Msgs::JointValue* pJoint = jVector.add_jointvalues();
						pJoint->set_id(id);
						pJoint->set_value(vals[jointMap[id]]);
					}
					jVector.PrintDebugString();
					m_pJointValueVector.push_back(jVector);
				}
			}
		}
	}

	void PublishJointValues(){
		FOREACH(it, m_pJointValueVector) {
			std::cout << "Publishing the joint values" << std::endl;
			std::string str;
			it->SerializeToString(&str);
			it->PrintDebugString();
			if (s_sendmore(*m_pSocket, m_strPublisherName)){
				s_send(*m_pSocket, str);
			}
			Sleep(100);
		}
		std::cout << "Finished publishing the joint values" << std::endl;
	}

private:
	ZmqContextPtr m_pContext;
	ZmqSocketPtr m_pSocket;
	std::string m_strPublisherName;
	std::vector<Indriya::Core::Msgs::JointValueVector> m_pJointValueVector;
};

Indriya::Core::Msgs::NodePtr AcquireParameters(int argc, char** argv){
	Indriya::Core::Msgs::NodePtr pInfo;
	if (argv != NULL){
		if (argc > 2){
			std::cout
				<< "Parsing command line option " << std::endl;
			namespace po = boost::program_options;
			po::options_description desc("Options");
			desc.add_options()
				("help,h", "Print help messages")
				("name,n", po::value<std::string>(), "name of the node")
				("param,p", po::value<std::string>(), "parameter server address");

			po::variables_map vm;
			try
			{
				po::store(po::parse_command_line(argc, argv, desc),
					vm); // can throw 

				/** --help option
				*/
				if (vm.count("help"))
				{
					std::cout << "Basic Command Line Parameter App" << std::endl
						<< desc << std::endl;
					return 0;
				}
				std::string name;
				std::string param;
				if (vm.count("name")){
					name = vm["name"].as<std::string>();
					std::cout << "Name of node: " << std::endl
						<< vm["name"].as<std::string>() << std::endl;
				}
				if (vm.count("param")){
					param = vm["param"].as<std::string>();
					std::cout << "Parameter server : " << std::endl
						<< vm["param"].as<std::string>() << std::endl;
				}
				po::notify(vm); // throws on error, so do after help in case 
				// there are any problems 

				if (!name.empty() && !param.empty()){
					pInfo = Indriya::Core::Msgs::NodePtr(new Indriya::Core::Msgs::Node());
					if (ParameterClient::Get(param, name, pInfo, 1000)){
						pInfo->PrintDebugString();
					}
				}
			}
			catch (po::error& e)
			{
				std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
				std::cerr << desc << std::endl;
			}
		}
	}
	return pInfo;
}

typedef boost::shared_ptr<RobotStateListener> RobotStateListenerPtr;
typedef boost::shared_ptr<KinectStateListener> KinectStateListenerPtr;
typedef boost::shared_ptr<TorsoPoseListener> TorsoPoseListenerPtr;
typedef boost::shared_ptr<HumanPoseListener> HumanPoseListenerPtr;
typedef boost::shared_ptr<MessageSubscriber<Indriya::Core::Msgs::KinectBodies>> MessageSubscriberPtr;

void dummyFn(const Indriya::Core::Msgs::KinectBodies& bodies)
{
	if (bodies.body_size() > 0){
		std::cout << "Invoked from callback" << std::endl;
	}
}

int main(int argc, char ** argv)
{
	try{
		RobotStateListenerPtr pRobotListener;
		KinectStateListenerPtr pKinectListener;
		TorsoPoseListenerPtr pTorsoPoseListener;
		HumanPoseListenerPtr pHumanPoseListener;
		MessageSubscriberPtr pMessageSubscriber;

		string scenefilename = "data/nao.dae";
		string viewername = "qtcoin";
		string kinectModel = "data/kinect.kinbody.xml";
		string humanTorsoBaseModel = "data/human";

		Indriya::Core::Msgs::NodePtr pInfo = AcquireParameters(argc, argv);

		if (pInfo != 0){
			scenefilename = ParameterHelper::GetParam(pInfo->param(), "scenefilename", scenefilename);
			viewername = ParameterHelper::GetParam(pInfo->param(), "viewername", viewername);
			kinectModel = ParameterHelper::GetParam(pInfo->param(), "kinect_model", kinectModel);
			humanTorsoBaseModel = ParameterHelper::GetParam(pInfo->param(), "human_torso_base_model", humanTorsoBaseModel);

			for (int i = 0; i < pInfo->subscriber_size(); i++){
				auto& sub = pInfo->subscriber(i);
				if (sub.msg_type() == "JointValueVector"){
					pRobotListener = RobotStateListenerPtr(new RobotStateListener(sub.host(), sub.port(), sub.topic()));
				}
				if (sub.msg_type() == "Pose_V"){
					pTorsoPoseListener = TorsoPoseListenerPtr(new TorsoPoseListener(sub.host(), sub.port(), sub.topic()));
				}
				if (sub.msg_type() == "KinectBodies"){
					pKinectListener = KinectStateListenerPtr(new KinectStateListener(sub.host(), sub.port(), sub.topic()));
					pMessageSubscriber = MessageSubscriberPtr(new MessageSubscriber<Indriya::Core::Msgs::KinectBodies>(sub.host(), sub.port(), sub.topic()));
				}
				if (sub.msg_type() == "Humans"){
					pHumanPoseListener = HumanPoseListenerPtr(new HumanPoseListener(sub.host(), sub.port(), sub.topic(), humanTorsoBaseModel));
				}
			}
			std::cout << "Initialized node from configuration file " << std::endl;
		}
		else{
			pRobotListener = RobotStateListenerPtr(new RobotStateListener());
			pTorsoPoseListener = TorsoPoseListenerPtr(new TorsoPoseListener());
			pKinectListener = KinectStateListenerPtr(new KinectStateListener());
			pHumanPoseListener = HumanPoseListenerPtr(new HumanPoseListener());
		}
		RaveInitialize(true); // start openrave core
		EnvironmentBasePtr penv = RaveCreateEnvironment(); // create the main environment
		RaveSetDebugLevel(Level_Info);

		boost::thread thviewer(boost::bind(SetViewer, penv, viewername));

#if 0
		orDispRobots(penv);
#endif


		std::vector<string> modelFiles;
		modelFiles.push_back(kinectModel);
		orInitEnvironment(penv, scenefilename, modelFiles);

		Sleep(1000);
		//boost::thread thPublisher(boost::bind(&RobotStatePublisher::PublishJointValues, &publisher));
		boost::thread thRobotSubscriber(boost::bind(&RobotStateListener::Listen, pRobotListener, penv));
		boost::thread thKinectSubscriber(boost::bind(&KinectStateListener::Listen, pKinectListener, penv));
		boost::thread thTorsoSubscriber(boost::bind(&TorsoPoseListener::Listen, pTorsoPoseListener, penv));
		boost::thread thHumanSubscriber(boost::bind(&HumanPoseListener::Listen, pHumanPoseListener, penv));

		boost::function<void(const Indriya::Core::Msgs::KinectBodies&)> fn2(boost::bind(dummyFn, _1));
		pMessageSubscriber->Initialize();
		pMessageSubscriber->registerCallback(fn2);
		pMessageSubscriber->Run(100, 100);

		thviewer.join(); // wait for the viewer thread to exit

		done = true;

		//pMessageSubscriber->Stop();
		thRobotSubscriber.join();
		thKinectSubscriber.join();
		thTorsoSubscriber.join();
		thHumanSubscriber.join();

		penv->Destroy(); // destroy
	}
	catch (std::exception& ex){
		std::cout << ex.what() << std::endl;
	}
	return 0;
}