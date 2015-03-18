/** \example orloadviewer.cpp
    \author Rosen Diankov

    Shows how to load a robot into the openrave environment and start a viewer in a separate thread.

    Usage:
    \verbatim
    orloadviewer [--num n] [--scene filename] viewername
    \endverbatim

    - \b --num - Number of environments/viewers to create simultaneously
    - \b --scene - The filename of the scene to load.

    Example:
    \verbatim
    ./orloadviewer --scene data/lab1.env.xml qtcoin
    \endverbatim

    <b>Full Example Code:</b>
 */
#include <openrave-core.h>
#include <vector>
#include <cstring>
#include <sstream>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include "asio_server.h"

#include "csv.h"

#include <boost/typeof/std/string.hpp>
#include <boost/typeof/std/vector.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/map.hpp>
#include <boost/typeof/std/set.hpp>
#include <boost/typeof/std/string.hpp>

using namespace OpenRAVE;
using namespace std;
using namespace boost;

#define FOREACH(it, v) for(BOOST_TYPEOF(v) ::iterator it = (v).begin(), __itend__=(v).end(); it != __itend__; ++(it))
#define FOREACHC(it, v) for(BOOST_TYPEOF(v) ::const_iterator it = (v).begin(), __itend__=(v).end(); it != __itend__; ++(it))

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

void RunServer(EnvironmentBasePtr penv)
{
	boost::asio::io_service io_service;
	tcp_server server(io_service);
	io_service.run();
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

int main(int argc, char ** argv)
{
	//int num = 1;
	string scenefilename = "data/nao.dae";
	string viewername = "qtcoin";

	// parse the command line options
	int i = 1;
	while (i < argc) {
		if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "-?") == 0) || (strcmp(argv[i], "/?") == 0) || (strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-help") == 0)) {
			RAVELOG_INFO("orloadviewer [--num n] [--scene filename] viewername\n");
			return 0;
		}
		else if (strcmp(argv[i], "--scene") == 0) {
			scenefilename = argv[i + 1];
			i += 2;
		}
		else
			break;
	}
	if (i < argc) {
		viewername = argv[i++];
	}

	RaveInitialize(true); // start openrave core
	EnvironmentBasePtr penv = RaveCreateEnvironment(); // create the main environment
	RaveSetDebugLevel(Level_Debug);

	boost::thread thviewer(boost::bind(SetViewer, penv, viewername));
	//boost::thread thServer(boost::bind(RunServer, penv));

	csv::io::CSVReader<25> in("datalog.csv");

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

	in.read_header(csv::io::ignore_extra_column, "Device/SubDeviceList/HeadPitch/Position/Sensor/Value"
		, "Device/SubDeviceList/HeadYaw/Position/Sensor/Value"
		, "Device/SubDeviceList/LAnklePitch/Position/Sensor/Value"
		, "Device/SubDeviceList/LAnkleRoll/Position/Sensor/Value",
		"Device/SubDeviceList/LElbowRoll/Position/Sensor/Value",
		"Device/SubDeviceList/LElbowYaw/Position/Sensor/Value",
		"Device/SubDeviceList/LHand/Position/Sensor/Value",
		"Device/SubDeviceList/LHipPitch/Position/Sensor/Value",
		"Device/SubDeviceList/LHipRoll/Position/Sensor/Value"
		, "Device/SubDeviceList/LHipYawPitch/Position/Sensor/Value"
		, "Device/SubDeviceList/LKneePitch/Position/Sensor/Value",
		"Device/SubDeviceList/LShoulderPitch/Position/Sensor/Value"
		, "Device/SubDeviceList/LShoulderRoll/Position/Sensor/Value",
		"Device/SubDeviceList/LWristYaw/Position/Sensor/Value"
		, "Device/SubDeviceList/RAnklePitch/Position/Sensor/Value"
		, "Device/SubDeviceList/RAnkleRoll/Position/Sensor/Value",
		"Device/SubDeviceList/RElbowRoll/Position/Sensor/Value",
		"Device/SubDeviceList/RElbowYaw/Position/Sensor/Value",
		"Device/SubDeviceList/RHand/Position/Sensor/Value"
		, "Device/SubDeviceList/RHipPitch/Position/Sensor/Value",
		"Device/SubDeviceList/RHipRoll/Position/Sensor/Value",
		"Device/SubDeviceList/RKneePitch/Position/Sensor/Value"
		, "Device/SubDeviceList/RShoulderPitch/Position/Sensor/Value",
		"Device/SubDeviceList/RShoulderRoll/Position/Sensor/Value",
		"Device/SubDeviceList/RWristYaw/Position/Sensor/Value");

	penv->Load(scenefilename); // load the scene

	orDispRobots(penv);
	RobotBasePtr probot = RobotBasePtr();
	{
		EnvironmentMutex::scoped_lock lock(penv->GetMutex());
		probot = orMacroGetRobot(penv, 1);
	}
	if (probot){
		cout << "Robot exists!";
		vector<double> vals;
		vals.resize(25);
		while (in.read_row(vals[0], vals[1], vals[2], vals[3],
			vals[4], vals[5], vals[6], vals[7],
			vals[8], vals[9], vals[10], vals[11],
			vals[12], vals[13], vals[14], vals[15],
			vals[16], vals[17], vals[18], vals[19],
			vals[20], vals[21], vals[22], vals[23], vals[24]
			))
		{
			{
				vector<double> jointVals;
				for (size_t id = 0; id < vals.size(); id++){
					jointVals.push_back(vals[jointMap[id]]);
				}
				orRobotSetActiveDOFs(probot, jointVals);
				Sleep(100);
			}
		}
	}

	thviewer.join(); // wait for the viewer thread to exit
	//thServer.join();

	penv->Destroy(); // destroy
	return 0;
}
