@echo on
echo "Generating proto buffer files..."
for /r %%i in (*.proto) do %1 --cpp_out=%2 --plugin=protoc-gen-experimot_msgs_gen=%3 --experimot_msgs_gen_out=%2 --proto_path=%4 %%i
REM for /r %%f in (*.proto) do %1 ---cpp_out=%2 --plugin=protoc-gen-experimot_msgs_gen=%3 --experimot_msgs_gen_out=%2 --proto_path=%4 %%f