#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

//截取全屏幕
cv::Mat ScreenShot()
{
	// 获取窗口当前显示的监视器
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// 获取监视器逻辑宽度
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfo(hMonitor, &monitorInfo);
	int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);

	// 获取监视器物理宽度
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

	// 获取屏幕 DC
	HDC hScreenDC = GetDC(NULL);
	HDC hCompatibleDC = CreateCompatibleDC(hScreenDC);

	// 创建位图
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, dWidth, dHeight);
	SelectObject(hCompatibleDC, hBitmap);

	BitBlt(hCompatibleDC, 0, 0, dWidth, dHeight, hScreenDC, 0, 0, SRCCOPY);
	GetBitmapBits(hBitmap, dWidth * dHeight * 4, screenshotData);

	// 创建图像
	return cv::Mat(dHeight, dWidth, CV_8UC4, screenshotData);
}

//用于在原图中查找模板图像的位置,查找方式:TM_SQDIFF
//image1:原图;image2:模板;bIsGray:是否使用灰度图
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