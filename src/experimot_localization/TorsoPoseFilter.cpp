#include "TorsoPoseFilter.h"

#include <bullet\Bullet3Common\b3Matrix3x3.h>

using namespace MatrixWrapper;
using namespace BFL;
using namespace std;

TorsoPoseFilter::TorsoPoseFilter() :prior_(NULL),
filter_(NULL),
filter_initialized_(false),
vo_initialized_(false)
{
	// create SYSTEM MODEL
	ColumnVector sysNoise_Mu(6);  sysNoise_Mu = 0;
	SymmetricMatrix sysNoise_Cov(6); sysNoise_Cov = 0;
	for (unsigned int i = 1; i <= 6; i++) sysNoise_Cov(i, i) = pow(1000.0, 2);
	Gaussian system_Uncertainty(sysNoise_Mu, sysNoise_Cov);
	sys_pdf_ = new NonLinearAnalyticConditionalGaussianOdo(system_Uncertainty);
	sys_model_ = new AnalyticSystemModelGaussianUncertainty(sys_pdf_);

	// create MEASUREMENT MODEL VO
	ColumnVector measNoiseVo_Mu(6);  measNoiseVo_Mu = 0;
	SymmetricMatrix measNoiseVo_Cov(6);  measNoiseVo_Cov = 0;
	for (unsigned int i = 1; i <= 6; i++) measNoiseVo_Cov(i, i) = 1;
	Gaussian measurement_Uncertainty_Vo(measNoiseVo_Mu, measNoiseVo_Cov);
	Matrix Hvo(6, 6);  Hvo = 0;
	Hvo(1, 1) = 1;    Hvo(2, 2) = 1;    Hvo(3, 3) = 1;    Hvo(4, 4) = 1;    Hvo(5, 5) = 1;    Hvo(6, 6) = 1;
	vo_meas_pdf_ = new LinearAnalyticConditionalGaussian(Hvo, measurement_Uncertainty_Vo);
	vo_meas_model_ = new LinearAnalyticMeasurementModelGaussianUncertainty(vo_meas_pdf_);
}

TorsoPoseFilter::~TorsoPoseFilter(){
	if (filter_) delete filter_;
	if (prior_)  delete prior_;
	delete vo_meas_model_;
	delete vo_meas_pdf_;
	delete sys_pdf_;
	delete sys_model_;
}

void PrintVector(ColumnVector vec){
	for (int i = 0; i < vec.size(); i++){
		std::cout << vec[i];
		if (i < vec.size() - 1){
			std::cout << " , ";
		}
	}
	std::cout << std::endl;
}

/** update the extended Kalman filter **/
bool TorsoPoseFilter::update(const PosixTime& filter_time){
	// only update filter when it is initialized
	if (!filter_initialized_){
		//ROS_INFO("Cannot update filter when filter was not initialized first.");
		return false;
	}

	// only update filter for time later than current filter time
	double dt = (filter_time - filter_time_old_).seconds();
	if (dt == 0) return false;
	if (dt < 0){
		//ROS_INFO("Will not update robot pose with time %f sec in the past.", dt);
		return false;
	}
	//ROS_DEBUG("Update filter at time %f with dt %f", filter_time.toSec(), dt);


	// system update filter
	// --------------------
	// for now only add system noise
	ColumnVector vel_desi(2); vel_desi = 0;
	filter_->Update(sys_model_, vel_desi);

	// process vo measurement
	// ----------------------
	if (vo_initialized_){
		// convert absolute vo measurements to relative vo measurements
		//Transform vo_rel_frame = filter_estimate_old_ * vo_meas_old_.inverse() * vo_meas_;
		Transform vo_rel_frame = filter_estimate_old_.inverse() * vo_meas_;
		ColumnVector vo_rel(6);
		decomposeTransform(vo_rel_frame, vo_rel(1), vo_rel(2), vo_rel(3), vo_rel(4), vo_rel(5), vo_rel(6));
		angleOverflowCorrect(vo_rel(6), filter_estimate_old_vec_(6));

		std::cout << "Old Estimate Frame : " << filter_estimate_old_ << std::endl;
		std::cout << "Old Measure Frame : " << vo_meas_old_ << std::endl;
		std::cout << "Current Measure Frame : " << vo_meas_old_ << std::endl;
		std::cout << "Rel Frame : " << vo_rel_frame << std::endl;
		PrintVector(vo_rel);

		SymmetricMatrix cov = vo_meas_model_->CovarianceGet(vel_desi, filter_->PostGet()->ExpectedValueGet());
		// update filter
		vo_meas_pdf_->AdditiveNoiseSigmaSet(vo_covariance_ * pow(dt, 2));
		//filter_->Update(vo_meas_model_, vo_rel, filter_->PostGet()->ExpectedValueGet());
		filter_->Update(vo_meas_model_, vo_rel);
	}
	else{
		vo_initialized_ = true;
	}

	vo_meas_old_ = vo_meas_;

	// remember last estimate
	filter_estimate_old_vec_ = filter_->PostGet()->ExpectedValueGet();

	b3Quaternion q;
	q.setEulerZYX(filter_estimate_old_vec_(6), filter_estimate_old_vec_(5), filter_estimate_old_vec_(4));

	filter_estimate_old_ = Transform(Vector(q.w, q.x, q.y, q.z),
		Vector(filter_estimate_old_vec_(1), filter_estimate_old_vec_(2), filter_estimate_old_vec_(3)));

	filter_time_old_ = filter_time;

	addMeasurement(filter_estimate_old_);

	return true;
}

/** initialize the extended Kalman filter **/
void TorsoPoseFilter::initialize(const OpenRAVE::Transform& prior, const PosixTime& time){
	// set prior of filter
	ColumnVector prior_Mu(6);
	decomposeTransform(prior, prior_Mu(1), prior_Mu(2), prior_Mu(3), prior_Mu(4), prior_Mu(5), prior_Mu(6));
	SymmetricMatrix prior_Cov(6);
	for (unsigned int i = 1; i <= 6; i++) {
		for (unsigned int j = 1; j <= 6; j++){
			if (i == j) {
				prior_Cov(i, j) = pow(0.001, 2);
			}
			else{
				prior_Cov(i, j) = 0;
			}
		}
	}
	prior_ = new Gaussian(prior_Mu, prior_Cov);
	filter_ = new ExtendedKalmanFilter(prior_);

	// remember prior
	addMeasurement(prior);

	filter_estimate_old_vec_ = prior_Mu;
	filter_estimate_old_ = prior;
	filter_time_old_ = time;

	// filter initialized
	filter_initialized_ = true;
}

/** get the filter posterior **/
void TorsoPoseFilter::getEstimate(MatrixWrapper::ColumnVector& estimate){
	estimate = filter_estimate_old_vec_;
}

/** get the filter posterior **/
void TorsoPoseFilter::getEstimate(OpenRAVE::Transform& estimate){
	estimate = filter_estimate_old_;
}

/** Add a sensor measurement to the measurement buffer **/
void TorsoPoseFilter::addMeasurement(const OpenRAVE::Transform& meas){
	vo_meas_ = meas;
}

/** Add a sensor measurement to the measurement buffer **/
void TorsoPoseFilter::addMeasurement(const OpenRAVE::Transform& meas, const MatrixWrapper::SymmetricMatrix& covar){
	// check covariance
	for (unsigned int i = 0; i<covar.rows(); i++){
		if (covar(i + 1, i + 1) == 0){
			//ROS_ERROR("Covariance specified for measurement on topic %s is zero", meas.child_frame_id_.c_str());
			return;
		}
	}
	// add measurements
	addMeasurement(meas);
	vo_covariance_ = covar;
	//else ROS_ERROR("Adding a measurement for an unknown sensor %s", meas.child_frame_id_.c_str());
}

/// correct for angle overflow
void TorsoPoseFilter::angleOverflowCorrect(double& a, double ref){
	while ((a - ref) >  M_PI) a -= 2 * M_PI;
	while ((a - ref) < -M_PI) a += 2 * M_PI;
}

// decompose Transform into x,y,z,Rx,Ry,Rz
void TorsoPoseFilter::decomposeTransform(const OpenRAVE::Transform& trans,
	double& x, double& y, double&z, double&Rx, double& Ry, double& Rz){
	Vector quat = trans.rot;
	b3Quaternion b3quat(quat[1], quat[2], quat[3], quat[0]);
	x = trans.trans.x;
	y = trans.trans.y;
	z = trans.trans.z;
	b3Matrix3x3 b3Mat(b3quat);
	float roll, pitch, yaw;
	b3Mat.getEulerYPR(yaw, pitch, roll);
	Rx = roll; Ry = pitch; Rz = yaw;
}