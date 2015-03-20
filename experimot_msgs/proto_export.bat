@echo on
echo "Generating proto buffer files..."
REM for /r %%i in (.\proto\*.proto) do %1 --cpp_out=%2 --plugin=protoc-gen-experimot_msgs_gen=%3 --experimot_msgs_gen_out=%2 --proto_path=%4 %%i
REM protoc --proto_path=src --python_out=build/gen src/foo.proto src/bar/baz.proto
for /r %%i in (.\proto\*.proto) do %1 --python_out=%2\python --proto_path=%4 %%i
REM for /r %%i in (.\proto_kinect\*.proto) do %1 --cpp_out=%2 --proto_path=%4_kinect %%i
REM for /r %%f in (*.proto) do %1 ---cpp_out=%2 --plugin=protoc-gen-experimot_msgs_gen=%3 --experimot_msgs_gen_out=%2 --proto_path=%4 %%f