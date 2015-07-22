#ifndef __PARTICLE_FILTER_H__
#define __PARTICLE_FILTER_H__

#include <bfl/filter/bootstrapfilter.h>
#include "nonlinearSystemPdf.h"
#include "nonlinearMeasurementPdf.h"
#include <bfl/pdf/gaussian.h>
#include <bfl/model/analyticsystemmodel_gaussianuncertainty.h>
#include <bfl/model/linearanalyticmeasurementmodel_gaussianuncertainty.h>
#include <boost\shared_ptr.hpp>

#include <iostream>
#include <fstream>
#include <math.h>

#define STATE_SIZE 6
#define MEAS_SIZE 6

// System Noise
#define MU_SYSTEM_NOISE_X 0.0 
#define MU_SYSTEM_NOISE_Y 0.0 
#define MU_SYSTEM_NOISE_Z 0.0 
#define MU_SYSTEM_NOISE_ROLL 0.0
#define MU_SYSTEM_NOISE_PITCH 0.0
#define MU_SYSTEM_NOISE_YAW 0.0

#define SIGMA_SYSTEM_NOISE_X pow(2,2)
#define SIGMA_SYSTEM_NOISE_Y pow(2,2)
#define SIGMA_SYSTEM_NOISE_Z pow(2,2)
#define SIGMA_SYSTEM_NOISE_ROLL pow(2*M_PI/180,2)
#define SIGMA_SYSTEM_NOISE_PITCH pow(2*M_PI/180,2)
#define SIGMA_SYSTEM_NOISE_YAW pow(2*M_PI/180,2)

// Measurement noise
#define SIGMA_MEAS_NOISE_POS pow(2,2)
#define SIGMA_MEAS_NOISE_ORIENT pow(2*M_PI/180,2)
#define MU_MEAS_NOISE 0.0

// Prior:
// Initial estimate of position and orientation
#define PRIOR_MU_X -100
#define PRIOR_MU_Y -100
#define PRIOR_MU_Z 1000
#define PRIOR_MU_ROLL 0	//M_PI/4
#define PRIOR_MU_PITCH 0	//M_PI/4
#define PRIOR_MU_YAW M_PI/4	//M_PI/4

// Initial covariances of position and orientation
#define PRIOR_COV_X pow(5,2)
#define PRIOR_COV_Y pow(5,2)
#define PRIOR_COV_Z pow(5,2)
#define PRIOR_COV_ROLL pow(M_PI/16,2)
#define PRIOR_COV_PITCH pow(M_PI/16,2)
#define PRIOR_COV_YAW pow(M_PI/8,2)

// Sample size
#define NUM_SAMPLES 100

using namespace MatrixWrapper;
using namespace BFL;
using namespace std;

typedef boost::recursive_try_mutex MarkerParticleFilterMutex;

class MarkerParticleFilter{
public:
	MarkerParticleFilter() :sys_noise_Mu(STATE_SIZE), sys_noise_Cov(STATE_SIZE), meas_noise_Mu(MEAS_SIZE), meas_noise_Cov(MEAS_SIZE), H(MEAS_SIZE, STATE_SIZE), prior_Mu(STATE_SIZE),
		prior_discr(NUM_SAMPLES, STATE_SIZE), prior_Cov(STATE_SIZE)
	{
		prior_samples.resize(NUM_SAMPLES);
		init = false;
	}

	void Init(){
		if (init)
		{
			return;
		}
		try{
			/****************************
			* NonLinear system model      *
			***************************/

			// create gaussian
			sys_noise_Mu(1) = MU_SYSTEM_NOISE_X;
			sys_noise_Mu(2) = MU_SYSTEM_NOISE_Y;
			sys_noise_Mu(3) = MU_SYSTEM_NOISE_Z;
			sys_noise_Mu(4) = MU_SYSTEM_NOISE_ROLL;
			sys_noise_Mu(5) = MU_SYSTEM_NOISE_PITCH;
			sys_noise_Mu(6) = MU_SYSTEM_NOISE_YAW;

			sys_noise_Cov = 0.0;
			double noise[STATE_SIZE] = { SIGMA_SYSTEM_NOISE_X, SIGMA_SYSTEM_NOISE_Y, SIGMA_SYSTEM_NOISE_Z, SIGMA_SYSTEM_NOISE_ROLL, SIGMA_SYSTEM_NOISE_PITCH, SIGMA_SYSTEM_NOISE_YAW };
			for (int i = 1; i <= STATE_SIZE; i++){
				for (int j = 1; j <= STATE_SIZE; j++){
					if (i == j){
						sys_noise_Cov(i, j) = noise[i - 1];
					}
					else{
						sys_noise_Cov(i, j) = 0.0;
					}
				}
			}

			system_Uncertainty = boost::shared_ptr<Gaussian>(new Gaussian(sys_noise_Mu, sys_noise_Cov));

			// create the nonlinear system model
			sys_pdf = boost::shared_ptr<NonlinearSystemPdf>(new NonlinearSystemPdf(*(system_Uncertainty)));

			/*SystemModel<ColumnVector> sys_model(&sys_pdf);*/
			sys_model = boost::shared_ptr<SystemModel<ColumnVector>>(new SystemModel<ColumnVector>(sys_pdf.get()));

			/*********************************
			* NonLinear Measurement model   *
			********************************/

			// create matrix H for linear measurement model
			//double wall_ct = 2 / (sqrt(pow(RICO_WALL, 2.0) + 1));
			H = 0.0;
			for (int i = 1; i <= MEAS_SIZE; i++){
				for (int j = 1; j <= STATE_SIZE; j++){
					if (i == j){
						H(i, j) = 1;
					}
				}
			}

			// Construct the measurement noise (a scalar in this case)
			for (int i = 1; i <= MEAS_SIZE; i++){
				meas_noise_Mu(i) = MU_MEAS_NOISE;
			}

			double meas_noise[MEAS_SIZE] = { SIGMA_MEAS_NOISE_POS, SIGMA_MEAS_NOISE_POS, SIGMA_MEAS_NOISE_POS, SIGMA_MEAS_NOISE_ORIENT, SIGMA_MEAS_NOISE_ORIENT, SIGMA_MEAS_NOISE_ORIENT };

			for (int i = 1; i <= MEAS_SIZE; i++){
				for (int j = 1; j <= MEAS_SIZE; j++){
					if (i == j){
						meas_noise_Cov(i, j) = meas_noise[i - 1];
					}
					else{
						meas_noise_Cov(i, j) = 0.0;
					}
				}
			}

			/*Gaussian measurement_Uncertainty(meas_noise_Mu, meas_noise_Cov);*/
			measurement_Uncertainty = boost::shared_ptr<Gaussian>(new Gaussian(meas_noise_Mu, meas_noise_Cov));

			// create the measurement model
			/*LinearAnalyticConditionalGaussian meas_pdf(H, measurement_Uncertainty);*/
			meas_pdf = boost::shared_ptr<LinearAnalyticConditionalGaussian>(new LinearAnalyticConditionalGaussian(H, *(measurement_Uncertainty)));
			meas_model = boost::shared_ptr<LinearAnalyticMeasurementModelGaussianUncertainty>(new LinearAnalyticMeasurementModelGaussianUncertainty(meas_pdf.get()));

			/****************************
			* Linear prior DENSITY     *
			***************************/
			// Continuous Gaussian prior (for Kalman filters)

			prior_Mu(1) = PRIOR_MU_X;
			prior_Mu(2) = PRIOR_MU_Y;
			prior_Mu(3) = PRIOR_MU_Z;
			prior_Mu(4) = PRIOR_MU_ROLL;
			prior_Mu(5) = PRIOR_MU_PITCH;
			prior_Mu(6) = PRIOR_MU_YAW;

			
			double prior_cov_noise[STATE_SIZE] = { PRIOR_COV_X, PRIOR_COV_Y, PRIOR_COV_Z, PRIOR_COV_ROLL, PRIOR_COV_PITCH, PRIOR_COV_YAW };

			for (int i = 1; i <= STATE_SIZE; i++){
				for (int j = 1; j <= STATE_SIZE; j++){
					if (i == j){
						prior_Cov(i, j) = prior_cov_noise[i - 1];
					}
					else{
						prior_Cov(i, j) = 0.0;
					}
				}
			}

			
			prior_cont = boost::shared_ptr<Gaussian>(new Gaussian(prior_Mu, prior_Cov));
			// Discrete prior for Particle filter (using the continuous Gaussian prior)
			prior_cont->SampleFrom(prior_samples, NUM_SAMPLES, CHOLESKY, NULL);
			
			std::cout << "Particle samples : " << prior_samples.size() << std::endl;

			prior_discr.ListOfSamplesSet(prior_samples);

			for (int i = 0; i < NUM_SAMPLES; i++){
				ColumnVector& col = prior_samples.at(i).ValueGet();
				PrintColumnVector(col);
				//PrintColumnVector(prior_samples[i].ValueGet());
			}

			/******************************
			* Construction of the Filter *
			******************************/
			filter = boost::shared_ptr<BootstrapFilter<ColumnVector, ColumnVector>>(new BootstrapFilter<ColumnVector, ColumnVector>(&prior_discr, 0, NUM_SAMPLES / 4.0));

			init = true;
		}
		catch (std::exception& ex){
			std::cout << "Exception: Filiter Initialization: " << ex.what() << std::endl;
		}
	}

	void PrintColumnVector(ColumnVector& colVector){
		for (int i = 0; i < colVector.size(); i++){
			cout << colVector(i + 1);
			if (i != colVector.size() - 1){
				cout << "\t";
			}
		}
		cout << std::endl;
	}

	void Update(ColumnVector& measurement){
		ColumnVector input(6);
		input = 0.01;

		try{
			if (init){
				if (filter != 0 && sys_model != 0 && meas_model != 0){
					if (!filter->Update(sys_model.get(), input, meas_model.get(), measurement)){
					//if (!filter->Update(NULL, input, meas_model.get(), measurement)){
						std::cout << "Unable to update the filter" << std::endl;
					}
				}
				else{
					std::cout << "Invalid pointer" << std::endl;
				}
			}
			else{
				std::cout << "Filter not initialized" << std::endl;
			}
		}
		catch (std::exception& ex){
			std::cout << "Exception: Filiter Update: " << ex.what() << std::endl;
		}
	}

	bool GetPose(ColumnVector& pose){
		try{
			if (init){
				if (filter != 0){
					Pdf<ColumnVector> * posterior = filter->PostGet();
					pose = posterior->ExpectedValueGet();
					return true;
				}
			}
			else{
				std::cout << "Filter not initialized" << std::endl;
			}
		}
		catch (std::exception& ex){
			std::cout << "Exception: Get pose: " << ex.what() << std::endl;
		}
		return false;
	}

	bool IsInit() const{
		return init;
	}

	MarkerParticleFilterMutex& GetMutex() {
		return _mutex;
	}
private:
	mutable MarkerParticleFilterMutex _mutex;
	ColumnVector sys_noise_Mu;
	SymmetricMatrix sys_noise_Cov;
	ColumnVector meas_noise_Mu;
	SymmetricMatrix meas_noise_Cov;
	ColumnVector prior_Mu;
	SymmetricMatrix prior_Cov;
	vector<Sample<ColumnVector> > prior_samples;
	MCPdf<ColumnVector> prior_discr;
	boost::shared_ptr<SystemModel<ColumnVector>> sys_model;
	boost::shared_ptr<LinearAnalyticMeasurementModelGaussianUncertainty> meas_model;
	boost::shared_ptr<BootstrapFilter<ColumnVector, ColumnVector>> filter;
	boost::shared_ptr<Gaussian> system_Uncertainty;
	boost::shared_ptr<NonlinearSystemPdf> sys_pdf;
	boost::shared_ptr<Gaussian> measurement_Uncertainty;
	boost::shared_ptr<LinearAnalyticConditionalGaussian> meas_pdf;
	boost::shared_ptr<Gaussian> prior_cont;
	Matrix H;
	bool init;
};

#endif