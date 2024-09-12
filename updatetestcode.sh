#!/usr/bin/bash
testcode=~/UnitTestDoctest/
if [ $# -ne 1 ]; then
     echo "use default path: $testcode"
else
    testcode=$1
fi

update_files_and_dirs() {
    rm -rf $2
    cp -rf $1/$2 ./
}

gitDir=.git
if [ ! -d $gitDir ]; then
    rm -rf $gitDir
fi

update_files_and_dirs $testcode ./common
update_files_and_dirs $testcode ./template
update_files_and_dirs $testcode ./build.sh
update_files_and_dirs $testcode ./CMakeLists.txt
update_files_and_dirs $testcode ./InitProject.py
update_files_and_dirs $testcode ./InitProject.sh
update_files_and_dirs $testcode ./main.cpp
update_files_and_dirs $testcode ./updatetestcode.sh
cp -rf ./template/* ./
rm -rf ./template