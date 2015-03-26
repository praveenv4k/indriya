#ifndef __TEST_FK_H__
#define __TEST_FK_H__

#include "NaoHeadTransformHelper.h"

class TestFk{
public:
	TestFk(){}
	Test(){
		Transform tfm;
		tfm.identity();
		RobotBasePtr probot;
		EnvironmentBasePtr penv = OpenraveInit(tfm, probot);
		NaoHeadTransformHelper* tfHelper = NaoHeadTransformHelper::instance();
		double low = -38.5;
		double high = 29.5;
		double yaw = 0;
		for (double p = low; p < high; p += 0.5){
			std::vector<double> joints;
			joints.push_back(0);
			joints.push_back(DEG_TO_RADIAN(p));

			probot->SetDOFValues(joints);
			std::cout << "Openrave: " << probot->GetManipulator(std::string("arm"))->GetEndEffectorTransform() << std::endl;

			Transform local;
			tfHelper->GetEndEffectorTransform(joints, local);
			std::cout << "Helper: " << local << std::endl;
		}
		penv->Destroy();
	}
	EnvironmentBasePtr OpenraveInit(Transform& tfm, RobotBasePtr& probot){
		RaveInitialize(true); // start openrave core
		EnvironmentBasePtr penv = RaveCreateEnvironment(); // create the main environment

		string scenefilename = "nao_torso_head.dae";
		penv->Load(scenefilename); // load the scene

		probot = orMacroGetRobot(penv, 1);

		if (probot){
			std::cout << "Robot DOF : " << probot->GetDOF() << std::endl;
			std::vector<dReal> _jointVals;

			probot->SetDOFValues(_jointVals);
			RobotBase::ManipulatorPtr pManip = probot->GetManipulator(std::string("arm"));

			if (pManip){
				tfm = pManip->GetTransform();
				// m -> mm
				tfm.trans.x *= 1000;
				tfm.trans.y *= 1000;
				tfm.trans.z *= 1000;
				std::cout << TransformMatrix(tfm) << std::endl;
				NaoHeadTransformHelper* helper = NaoHeadTransformHelper::instance();
				Transform out;
				helper->GetEndEffectorTransform(_jointVals, out);
				std::cout << TransformMatrix(out) << std::endl;
			}
			//penv->Save(std::string("nao_head_robot.xml"), EnvironmentBase::SelectionOptions::SO_Robots, probot->GetName());
		}
		//penv->Destroy();
		return penv;
	}
};

#endif