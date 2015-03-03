/*
* This file is part of ALVAR, A Library for Virtual and Augmented Reality.
*
* Copyright 2007-2012 VTT Technical Research Centre of Finland
*
* Contact: VTT Augmented Reality Team <alvar.info@vtt.fi>
*          <http://www.vtt.fi/multimedia/alvar.html>
*
* ALVAR is free software; you can redistribute it and/or modify it under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; either version 2.1 of the License, or (at your option)
* any later version.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
* for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with ALVAR; if not, see
* <http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html>.
*/

#ifndef CAPTUREPLUGINKINECT_H
#define CAPTUREPLUGINKINECT_H

/**
* \file CapturePluginKinect.h
*
* \brief This file implements a capture plugin based on Kinect.
*/

#include <opencv\highgui.h>
#include <opencv2\opencv.hpp>
#include "Kinect.h"

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

/**
* \brief Implementation of Capture interface for Kinect plugin.
*/
class KinectVideoCapture
	: public cv::VideoCapture
{
public:
	/**
	* \brief Constructor.
	*
	* \param captureDevice Information of which camera to create.
	*/
	KinectVideoCapture();
	KinectVideoCapture(const std::string& filename);
	KinectVideoCapture(int device);
	/**
	* \brief Destructor.
	*/
	virtual ~KinectVideoCapture();

	bool open(const std::string& filename){ return start(); }
	bool open(int device){ return start(); }
	bool isOpened() const { return isCapturing(); }
	void release() { stop(); }

	bool grab() { return update(); }
	bool retrieve(cv::Mat& image, int channel = 0);
	KinectVideoCapture& operator >> (cv::Mat& image){
		retrieve(image);
		return *this;
	}
	bool read(cv::Mat& image){
		return retrieve(image);
	}

	bool set(int propId, double value){ return false; }
	double get(int propId){ return 0.0; }

private:
	bool start();
	void stop();
	IplImage *captureImage();
	bool showSettingsDialog();
	std::string SerializeId();
	bool isCapturing() const;

	static const int        cColorWidth = 1920;
	static const int        cColorHeight = 1080;
	int mXResolution;
	int mYResolution;
	bool m_bCapturing;
	bool m_bGrabbed;
	bool update();
	HRESULT initializeDefaultSensor();
	void cleanUp();
	bool processColor(INT64 nTime, RGBQUAD* pBuffer, int nWidth, int nHeight);
	//cv::VideoCapture mVideoCapture;
	cv::Mat mMatrix;
	cv::Mat mResizeMatrix;
	IplImage mImage;
	// Current Kinect
	IKinectSensor*          m_pKinectSensor;
	// Color reader
	IColorFrameReader*      m_pColorFrameReader;
	// Direct2D
	RGBQUAD*                m_pColorRGBX;
	// Check if the previous frame was valid
	bool					m_bPrevFrame;
};

#endif
