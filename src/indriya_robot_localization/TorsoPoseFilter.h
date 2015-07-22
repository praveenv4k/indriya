#ifndef __TORSO_POSE_FILTER_H__
#define __TORSO_POSE_FILTER_H__

#include <bfl\filter\extendedkalmanfilter.h>
#include <bfl/wrappers/matrix/matrix_wrapper.h>
#include <bfl/model/linearanalyticsystemmodel_gaussianuncertainty.h>
#include <bfl/model/linearanalyticmeasurementmodel_gaussianuncertainty.h>
#include <bfl/pdf/analyticconditionalgaussian.h>
#include <bfl/pdf/linearanalyticconditionalgaussian.h>
#include "nonlinearanalyticconditionalgaussianodo.h"

#include <openrave-core.h>

typedef boost::posix_time::ptime PosixTime;
typedef boost::posix_time::time_duration PosixDuration;

using namespace OpenRAVE;
using namespace MatrixWrapper;
using namespace BFL;
using namespace std;

class TorsoPoseFilter
{
public:
	TorsoPoseFilter();
	~TorsoPoseFilter();

	/** update the extended Kalman filter
	* \param odom_active specifies if the odometry sensor is active or not
	* \param imu_active specifies if the imu sensor is active or not
	* \param gps_active specifies if the gps sensor is active or not
	* \param vo_active specifies if the vo sensor is active or not
	* \param filter_time update the ekf up to this time
	* \param diagnostics_res returns false if the diagnostics found that the sensor measurements are inconsistent
	* returns true on successfull update
	*/
	//bool update(bool odom_active, bool imu_active, bool gps_active, bool vo_active, const PosixTime& filter_time, bool& diagnostics_res);
	bool update(const PosixTime& filter_time);

	/** initialize the extended Kalman filter
	* \param prior the prior robot pose
	* \param time the initial time of the ekf
	*/
	void initialize(const OpenRAVE::Transform& prior, const PosixTime& time);

	/** check if the filter is initialized
	* returns true if the ekf has been initialized already
	*/
	bool isInitialized() { return filter_initialized_; };

	/** get the filter posterior
	* \param estimate the filter posterior as a columnvector
	*/
	void getEstimate(MatrixWrapper::ColumnVector& estimate);

	/** get the filter posterior
	* \param estimate the filter posterior as a pose with covariance
	*/
	void getEstimate(OpenRAVE::Transform& estimate);

	/** Add a sensor measurement to the measurement buffer
	* \param meas the measurement to add
	*/
	void addMeasurement(const OpenRAVE::Transform& meas);

	/** Add a sensor measurement to the measurement buffer
	* \param meas the measurement to add
	* \param covar the 6x6 covariance matrix of this measurement, as defined in the PoseWithCovariance message
	*/
	void addMeasurement(const OpenRAVE::Transform& meas, const MatrixWrapper::SymmetricMatrix& covar);

	/** set the output frame used by tf
	* \param output_frame the desired output frame published on /tf (e.g., odom_combined)
	*/
	void setOutputFrame(const std::string& output_frame);

	/** set the base_footprint frame of the robot used by tf
	* \param base_frame the desired base frame from which to transform when publishing the combined odometry frame (e.g., base_footprint)
	*/
	void setBaseFootprintFrame(const std::string& base_frame);

private:
	/// correct for angle overflow
	void angleOverflowCorrect(double& a, double ref);

	// decompose Transform into x,y,z,Rx,Ry,Rz
	void decomposeTransform(const OpenRAVE::Transform& trans,
		double& x, double& y, double&z, double&Rx, double& Ry, double& Rz);

private:
	// pdf / model / filter
	BFL::AnalyticSystemModelGaussianUncertainty*            sys_model_;
	BFL::NonLinearAnalyticConditionalGaussianOdo*           sys_pdf_;
	BFL::LinearAnalyticConditionalGaussian*                 vo_meas_pdf_;
	BFL::LinearAnalyticMeasurementModelGaussianUncertainty* vo_meas_model_;
	BFL::Gaussian*                                          prior_;
	BFL::ExtendedKalmanFilter*                              filter_;
	MatrixWrapper::SymmetricMatrix                          vo_covariance_;

	// vars
	MatrixWrapper::ColumnVector vel_desi_, filter_estimate_old_vec_;
	OpenRAVE::Transform filter_estimate_old_;
	OpenRAVE::Transform vo_meas_, vo_meas_old_;
	PosixTime filter_time_old_;
	bool filter_initialized_, vo_initialized_;

	ColumnVector sysNoise_Mu;
	SymmetricMatrix sysNoise_Cov;
	ColumnVector measNoiseVo_Mu;
	SymmetricMatrix measNoiseVo_Cov;

	Gaussian* system_Uncertainty;
	Gaussian* measurement_Uncertainty_Vo;
	Matrix Hvo;
};

#endif