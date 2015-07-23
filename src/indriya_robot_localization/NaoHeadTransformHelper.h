#ifndef __NAOHEAD_TRANSFORM_HELPER_H__
#define __NAOHEAD_TRANSFORM_HELPER_H__

#include "Indriya\Common\Common.h"

using namespace OpenRAVE;
using namespace std;

#define DEG_TO_RADIAN(x) (x/180.0)*OpenRAVE::PI

typedef struct tagFkParams{
	Transform rot_x_alpha;
	Transform trans_x_d;
	Transform trans_z_r;
}FkParams;

class NaoHeadTransformHelper{
private:
	// alpha,d,r
	std::vector<std::tuple<dReal, dReal, dReal>> _params;
	std::vector<FkParams> _fParams;
	Transform _eefTransform;
	NaoHeadTransformHelper(std::vector<std::tuple<dReal, dReal, dReal>>& dhParams, Transform& eefTransform){
		_params = dhParams;
		_eefTransform = eefTransform;
		Vector rot_x(1, 0, 0);
		Vector rot_z(0, 0, 1);
		FOREACH(it, dhParams){
			FkParams j1;

			j1.rot_x_alpha = geometry::matrixFromAxisAngle(rot_x, std::get<0>(*it));

			j1.trans_x_d = Transform();
			j1.trans_x_d.trans.x = std::get<1>(*it);

			j1.trans_z_r = Transform();
			j1.trans_z_r.trans.z = std::get<2>(*it);

			_fParams.push_back(j1);
		}
	}
	static NaoHeadTransformHelper* _instance;
public:
	static NaoHeadTransformHelper* instance(){
		if (_instance == NULL){
			vector<tuple<dReal, dReal, dReal>> params;

#if 1
			params.push_back(tuple<dReal, dReal, dReal>(0, 0, 126.50));
			params.push_back(tuple<dReal, dReal, dReal>(-OpenRAVE::PI/2, 0, 0));
			params.push_back(tuple<dReal, dReal, dReal>(OpenRAVE::PI / 2, 0, 110.0 + 64.0));
#else
			params.push_back(tuple<dReal, dReal, dReal>(-OpenRAVE::PI / 2, 0, 126.50));
			params.push_back(tuple<dReal, dReal, dReal>(OpenRAVE::PI/2, 0, 0));
			params.push_back(tuple<dReal, dReal, dReal>(0, 0, 110.0 + 64.0));
#endif

			Transform eefTransform;
			eefTransform.identity();
			eefTransform.trans.z = 110;

			_instance = new NaoHeadTransformHelper(params, eefTransform);
		}
		return _instance;
	}

	~NaoHeadTransformHelper(){
		if (_instance != NULL){
			delete _instance;
			_instance = NULL;
		}
	}

	void GetEndEffectorTransform(vector<dReal> q, Transform& transform) const{
		assert(q.size() == _fParams.size());
		Vector rot_x(1, 0, 0);
		Vector rot_z(0, 0, 1);
		Transform eefTransform;
		for (size_t i = 0; i < q.size(); i++){
			Transform rot_z_t = geometry::matrixFromAxisAngle(rot_z, q[i]);
			eefTransform = eefTransform * _fParams[i].rot_x_alpha * _fParams[i].trans_x_d * rot_z_t * _fParams[i].trans_z_r;
		}

		bool test = false;

		dReal alpha = std::get<0>(_params[0]);
		dReal d = std::get<1>(_params[0]);
		dReal theta = q[0];
		dReal r = std::get<2>(_params[0]);

		//std::cout << "Link1: " << alpha << ", " << d << ", " << theta << ", " << r << std::endl;

		Transform link1; link1.identity();
		if (test){
			link1 = computeTransformMatrix(alpha, d, theta, r);
		}
		else{
			link1 = Transform(geometry::quatFromAxisAngle(rot_x, alpha), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(d, 0, 0))*
				Transform(geometry::quatFromAxisAngle(rot_z, theta), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(0, 0, r));
		}

		alpha = std::get<0>(_params[1]);
		d = std::get<1>(_params[1]);
		theta = q[1];
		r = std::get<2>(_params[1]);

		//std::cout << "Link2: " << alpha << ", " << d << ", " << theta << ", " << r << std::endl;

		Transform link2; link2.identity();
		if (test){
			link2 = computeTransformMatrix(alpha, d, theta, r);
		}
		else{
			link2 = Transform(geometry::quatFromAxisAngle(rot_x, alpha), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(d, 0, 0))*
				Transform(geometry::quatFromAxisAngle(rot_z, theta), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(0, 0, r));
		}

		/*alpha = OpenRAVE::PI / 2;
		d = 0;
		theta = 0;
		r = 110.0 + 64.0;*/

		alpha = std::get<0>(_params[2]);
		d = std::get<1>(_params[2]);
		theta = 0;
		r = std::get<2>(_params[2]);

		//std::cout << "Link3: " << alpha << ", " << d << ", " << theta << ", " << r << std::endl;

		Transform eef; eef.identity();
		if (test){
			eef = computeTransformMatrix(alpha, d, theta, r);
		}
		else{
			eef = Transform(geometry::quatFromAxisAngle(rot_x, alpha), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(d, 0, 0))*
				Transform(geometry::quatFromAxisAngle(rot_z, theta), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(0, 0, r));
		}

		//transform = eefTransform*_eefTransform;
		transform = link1*link2*eef;
	}

	void GetTorsoTransform(const vector<dReal> q, const Transform& markerTransform, Transform& torsoTransform) const{
		Vector rot_x(1, 0, 0);
		Vector rot_z(0, 0, 1);

		bool test = true;

		/*Transform tf1 = markerTransform * Transform(geometry::quatFromAxisAngle(rot_z, OpenRAVE::PI / 2), Vector(0, 0, 0));
		tf1 = tf1 * Transform(geometry::quatFromAxisAngle(rot_x, OpenRAVE::PI / 2), Vector(0, 0, 0));
		
		tf1 = markerTransform;
		tf1.trans = tf1.rotate(markerTransform.trans);*/
		//torsoTransform = markerTransform;

		//dReal alpha = OpenRAVE::PI / 2;
		dReal alpha = 0;
		dReal d = 0;
		dReal theta = q[1];
		dReal r = -(110.0 + 64.0);

		Transform link1; link1.identity();
		if (test){
			link1 = computeTransformMatrix(alpha, d, theta, r);
		}
		else{
			link1 = Transform(geometry::quatFromAxisAngle(rot_x, alpha), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(d, 0, 0))*
				Transform(geometry::quatFromAxisAngle(rot_z, theta), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(0, 0, r));
		}

		alpha = -OpenRAVE::PI / 2;
		d = 0;
		theta = q[0];
		r = 0;

		Transform link2; link2.identity();
		if (test){
			link2 = computeTransformMatrix(alpha, d, theta, r);
		}
		else{
			link2 = Transform(geometry::quatFromAxisAngle(rot_x, alpha), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(d, 0, 0))*
				Transform(geometry::quatFromAxisAngle(rot_z, theta), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(0, 0, r));
		}

		//alpha = 0;
		alpha = OpenRAVE::PI / 2;;
		d = 0;
		theta = 0;
		r = -126.50;

		Transform eef; eef.identity();
		if (test){
			eef = computeTransformMatrix(alpha, d, theta, r);
		}
		else{
			eef = Transform(geometry::quatFromAxisAngle(rot_x, alpha), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(d, 0, 0))*
				Transform(geometry::quatFromAxisAngle(rot_z, theta), Vector(0, 0, 0))*
				Transform(Vector(1, 0, 0, 0), Vector(0, 0, r));
		}

		torsoTransform = markerTransform*link1*link2*eef;
	}

	Transform computeTransformMatrix(dReal alpha, dReal d, dReal theta, dReal r) const {
		dReal c_theta = cos(theta);
		dReal s_theta = sin(theta);
		dReal c_alpha = cos(alpha);
		dReal s_alpha = sin(alpha);

		dReal r11 = c_theta;
		dReal r12 = -s_theta;
		dReal r13 = 0;
		dReal r14 = d;

		dReal r21 = c_alpha * s_theta;
		dReal r22 = c_alpha * c_theta;
		dReal r23 = -s_alpha;
		dReal r24 = -r*s_alpha;

		dReal r31 = s_alpha*s_theta;
		dReal r32 = s_alpha*c_theta;
		dReal r33 = c_alpha;
		dReal r34 = r*c_alpha;

		//r11, r12, r13, r14
		//r21, r22, r23, r24
		//r31, r32, r33, r34
		// 0,   0 ,  0 , 1

		//Openrave Matrix indices format
		//row 0: 0, 1, 2, 3
		//row 1: 4, 5, 6, 7
		//row 2: 8, 9, 10, 11
		//trans.x, trans.y, trans.z, trans.w

		TransformMatrix mat;
		mat.rotfrommat(r11, r12, r13, r21, r22, r23, r31, r32, r33);
		//mat.rotfrommat(r11, r21, r31, r12, r22, r32, r13, r23, r33);
		mat.trans.x = r14;
		mat.trans.y = r24;
		mat.trans.z = r34;

		return Transform(mat);
	}
};

NaoHeadTransformHelper* NaoHeadTransformHelper::_instance = NULL;

#endif