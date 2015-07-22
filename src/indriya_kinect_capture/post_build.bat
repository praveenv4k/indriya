REM Writing list of header files in CvKinectCapture.h
@echo off
@echo // Automatically generated! DO NOT EDIT!!! > CvKinectCapture.h
@echo // Experimot Message Header Files >> CvKinectCapture.h
@echo // Created on  >> CvKinectCapture.h
@echo // %date% %time%  >> CvKinectCapture.h
for /r %%i in (*.hpp) do @echo #include "%%~nxi" >> CvKinectCapture.h 
xcopy /i/f/s/y %1\*.h* %2include\CvKinectCapture\
xcopy /i/f/s/y %3 %2lib\%4 