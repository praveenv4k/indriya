REM Writing list of msg header files in MessageTypes.h
@echo off
@echo // Automatically generated! DO NOT EDIT!!! > MessageTypes.h
@echo // Experimot Message Header Files >> MessageTypes.h
@echo // Created on  >> MessageTypes.h
@echo // %date% %time%  >> MessageTypes.h
for /r %%i in (*.pb.h) do @echo #include "%%~nxi" >> MessageTypes.h 
xcopy /i/f/s/y %1\*.h %2include\experimot\msgs 
xcopy /i/f/s/y %3 %2lib\%4 

REM Copy the python scripts to the executable directory
xcopy /i/f/s/y %1\python\*.py %5