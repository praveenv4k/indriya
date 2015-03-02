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

#include "KinectVideoCapture.h"
#include "Kinect.h"

#include <sstream>

KinectVideoCapture::KinectVideoCapture()
	: VideoCapture()
    , mMatrix()
    , mImage()
{
	mXResolution = cColorWidth;
	mYResolution = cColorHeight;
	//mXResolution = 640;
	//mYResolution = 480;
	m_bPrevFrame = false;
	m_bCapturing = false;
	m_bGrabbed = false;
	start();
}

KinectVideoCapture::KinectVideoCapture(const std::string& filename)
	: KinectVideoCapture()
{
}

KinectVideoCapture::KinectVideoCapture(int device)
	:KinectVideoCapture()
{
}

KinectVideoCapture::~KinectVideoCapture()
{
    stop();
}

bool KinectVideoCapture::isCapturing() const{
	return m_bCapturing;
}

bool KinectVideoCapture::start()
{
	printf("Starting...");
    if (isCapturing()) {
        return isCapturing();
    }

    
 	HRESULT hr = initializeDefaultSensor();
	if (SUCCEEDED(hr)){
		m_bCapturing = true;
	}

	// Initialize the matrix with zeros
	mMatrix = cv::Mat::zeros(cv::Size(cColorWidth, cColorHeight), CV_8UC4);

    return isCapturing();
}

void KinectVideoCapture::stop()
{
	printf("Stopping...");
    if (isCapturing()) {
		cleanUp();
		m_bCapturing = false;
    }
}

void KinectVideoCapture::cleanUp(){
	printf("Cleaning Up..."); 
	if (m_pColorRGBX)
	{
		delete[] m_pColorRGBX;
		m_pColorRGBX = NULL;
	}
	// done with color frame reader
	SafeRelease(m_pColorFrameReader);
	// close the Kinect Sensor
	if (m_pKinectSensor)
	{
		m_pKinectSensor->Close();
	}
	SafeRelease(m_pKinectSensor);
}

IplImage *KinectVideoCapture::captureImage()
{
	if (!isCapturing()) {
		return NULL;
	}
	update();
	if (mXResolution != cColorWidth && mYResolution != cColorHeight){
		cv::resize(mMatrix, mResizeMatrix, cv::Size(mXResolution, mYResolution));
		mImage = mResizeMatrix;
	}
	else{
		mImage = mMatrix;
	}
	return &mImage;
}

bool KinectVideoCapture::showSettingsDialog()
{
    // TODO: implement this method
    return false;
}

std::string KinectVideoCapture::SerializeId()
{
    return "KinectVideoCapture";
}

/// <summary>
/// Main processing function
/// </summary>
bool KinectVideoCapture::update()
{
	//printf("Updating...\n");
	if (!m_pColorFrameReader)
	{
		return false;
	}

	IColorFrame* pColorFrame = NULL;

	//printf("About to acquire latest frame...\n");
	HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);

	if (SUCCEEDED(hr))
	{
		//printf("Acquired last frame...\n");
		INT64 nTime = 0;
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		ColorImageFormat imageFormat = ColorImageFormat_None;
		UINT nBufferSize = 0;
		RGBQUAD *pBuffer = NULL;

		hr = pColorFrame->get_RelativeTime(&nTime);

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_RawColorImageFormat(&imageFormat);
		}

		if (SUCCEEDED(hr))
		{
			if (imageFormat == ColorImageFormat_Bgra)
			{
				hr = pColorFrame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&pBuffer));
			}
			else if (m_pColorRGBX)
			{
				pBuffer = m_pColorRGBX;
				nBufferSize = cColorWidth * cColorHeight * sizeof(RGBQUAD);
				hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(pBuffer), ColorImageFormat_Bgra);
			}
			else
			{
				hr = E_FAIL;
			}
		}

		if (SUCCEEDED(hr))
		{
			if (processColor(nTime, pBuffer, nWidth, nHeight)){
				m_bPrevFrame = true;
				m_bGrabbed = true;
			}
		}

		SafeRelease(pFrameDescription);
	}
	else{
		if (!m_bPrevFrame){
			printf("RGB data not yet available from Kinect...\n");
		}
	}

	SafeRelease(pColorFrame);
	return SUCCEEDED(hr);
}

bool KinectVideoCapture::retrieve(cv::Mat& image, int channel){
	IplImage* _img = captureImage();
	if (!_img)
	{
		image.release();
		return false;
	}
	if (_img->origin == IPL_ORIGIN_TL)
		cv::Mat(_img).copyTo(image);
	else
	{
		cv::Mat temp(_img);
		cv::flip(temp, image, 0);
	}
	return true;

	//if (mXResolution != cColorWidth && mYResolution != cColorHeight){
	//	cv::resize(mMatrix, mResizeMatrix, cv::Size(mXResolution, mYResolution));
	//	mResizeMatrix.copyTo(image);
	//}
	//else{
	//	mMatrix.copyTo(image);
	//}
	//return true;
}

/// <summary>
/// Initializes the default Kinect sensor
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT KinectVideoCapture::initializeDefaultSensor()
{
	HRESULT hr;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		printf("Default sensor successful...\n");
		// Initialize the Kinect and get the color reader
		IColorFrameSource* pColorFrameSource = NULL;

		hr = m_pKinectSensor->Open();
		printf("Sensor open successful...\n");
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
			printf("Obtained Color frame source...\n");
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
			printf("Obtained Color frame reader...\n");
		}

		SafeRelease(pColorFrameSource);
		
	}

	if (!m_pKinectSensor || FAILED(hr))
	{
		//SetStatusMessage(L"No ready Kinect found!", 10000, true);
		return E_FAIL;
	}

	// create heap storage for color pixel data in RGBX format
	m_pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];

	return hr;
}

/// <summary>
/// Handle new color data
/// <param name="nTime">timestamp of frame</param>
/// <param name="pBuffer">pointer to frame data</param>
/// <param name="nWidth">width (in pixels) of input image data</param>
/// <param name="nHeight">height (in pixels) of input image data</param>
/// </summary>
bool KinectVideoCapture::processColor(INT64 nTime, RGBQUAD* pBuffer, int nWidth, int nHeight)
{
	bool ret = false;
	// Make sure we've received valid data
	if (pBuffer && (nWidth == cColorWidth) && (nHeight == cColorHeight))
	{
		cv::Mat bufMat(nHeight, nWidth, CV_8UC4, pBuffer);
		bufMat.copyTo(mMatrix);
		//printf("Size: %d,%d\n", mMatrix.cols, mMatrix.rows);
		ret = true;
	}
	return ret;
}