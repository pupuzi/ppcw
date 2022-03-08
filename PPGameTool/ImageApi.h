#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

//��ȡȫ��Ļ
cv::Mat ScreenShot()
{
	// ��ȡ���ڵ�ǰ��ʾ�ļ�����
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// ��ȡ�������߼����
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfo(hMonitor, &monitorInfo);
	int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);

	// ��ȡ������������
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;

	double dZoom = cxPhysical * 1.0 / cxLogical;
	double dWidth = GetSystemMetrics(SM_CXSCREEN) * dZoom;
	double dHeight = GetSystemMetrics(SM_CYSCREEN) * dZoom;
	char* screenshotData = new char[dWidth * dHeight * 4];
	memset(screenshotData, 0, dWidth);

	// ��ȡ��Ļ DC
	HDC hScreenDC = GetDC(NULL);
	HDC hCompatibleDC = CreateCompatibleDC(hScreenDC);

	// ����λͼ
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, dWidth, dHeight);
	SelectObject(hCompatibleDC, hBitmap);

	BitBlt(hCompatibleDC, 0, 0, dWidth, dHeight, hScreenDC, 0, 0, SRCCOPY);
	GetBitmapBits(hBitmap, dWidth * dHeight * 4, screenshotData);

	// ����ͼ��
	return cv::Mat(dHeight, dWidth, CV_8UC4, screenshotData);
}

//������ԭͼ�в���ģ��ͼ���λ��,���ҷ�ʽ:TM_SQDIFF
//image1:ԭͼ;image2:ģ��;bIsGray:�Ƿ�ʹ�ûҶ�ͼ
cv::Point MatchImage(cv::Mat& image1, cv::Mat& image2, bool bIsGray = false)
{
	if (bIsGray)
	{
		cvtColor(image1, image1, CV_RGB2GRAY);
		cvtColor(image2, image2, CV_RGB2GRAY);
	}

	cv::Mat imageTemp;
	long nRows = image1.rows - image2.rows + 1;
	long nCols = image1.cols - image2.cols + 1;
	imageTemp.create(nRows, nCols, CV_32FC1);
	matchTemplate(image1, image2, imageTemp, cv::TM_SQDIFF);

	double dMinValue;
	double dMaxValue;
	cv::Point ptMinLocation;
	cv::Point ptMaxLocation;
	cv::Point ptMatchLocation;
	minMaxLoc(imageTemp, &dMinValue, &dMaxValue, &ptMinLocation, &ptMaxLocation, cv::Mat());
	ptMatchLocation = ptMinLocation;
	return ptMatchLocation;
}

#endif//!IMAGEAPI_H