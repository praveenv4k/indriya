@echo on
echo "Generating proto buffer files..."

REM C++ Files
for /r %%i in (.\proto\*.proto) do %1 --cpp_out=%2 --plugin=protoc-gen-experimot_msgs_gen=%3 --experimot_msgs_gen_out=%2 --proto_path=%4 %%i

REM Python Files
REM protoc --proto_path=src --python_out=build/gen src/foo.proto src/bar/baz.proto
for /r %%i in (.\proto\*.proto) do %1 --python_out=%2\python --proto_path=%4 %%i

REM In the python files replace syntax with #syntax (commenting that line), since Protobuf python binding doesn't support it yet
%2\tools\fnr.exe --cl --dir "%2\python" --fileMask "*.py" --find "syntax" --replace "#syntax"

REM Csharp Files
REM Descriptor File
REM for /r %%i in (proto\*.proto) do %1 --descriptor_set_out=%2descriptor\%%~nxi --proto_path=%4 %%i
for /r %%i in (proto\*.proto) do %5 -o:%2csharp\%%~ni.cs -i:%%i -ns:Experimot.Core.Msgs

REM Some random tries
REM for /r %%i in (.\proto_kinect\*.proto) do %1 --cpp_out=%2 --proto_path=%4_kinect %%i
REM for /r %%f in (*.proto) do %1 ---cpp_out=%2 --plugin=protoc-gen-experimot_msgs_gen=%3 --experimot_msgs_gen_out=%2 --proto_path=%4 %%f