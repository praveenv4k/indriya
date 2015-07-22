REM Writing list of header files in Kinect2_PCL.h
@echo off
@echo // Automatically generated! DO NOT EDIT!!! > Kinect2_PCL.h
@echo // Experimot Message Header Files >> Kinect2_PCL.h
@echo // Created on  >> Kinect2_PCL.h
@echo // %date% %time%  >> Kinect2_PCL.h
for /r %%i in (*.hpp) do @echo #include "%%~nxi" >> Kinect2_PCL.h 
xcopy /i/f/s/y %1\*.h* %2include\KinectPcl\
xcopy /i/f/s/y %3 %2lib\%4 