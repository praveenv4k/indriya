REM Computing the source code statistics
@echo off
cloc-1.62 --list-file=cloc_include_list.txt --exclude-dir=bin,obj,debug,release,x86,x64 --out=cloc_code_statistics.csv --csv --ignored=cloc_ignored_list.txt --exclude-ext=*.csproj,*.vcxproj
cloc-1.62 --list-file=cloc_include_list.txt --exclude-dir=bin,obj,debug,release,x86,x64 --out=docs/Thesis/assets/cloc_code_statistics.csv --csv --exclude-ext=*.csproj,*.vcxproj