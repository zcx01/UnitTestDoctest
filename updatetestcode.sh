#!/usr/bin/bash

update_files_and_dirs() {
    rm -rf $2
    cp -rf $1/$2 ./
}


update_files_and_dirs $1 ./common
update_files_and_dirs $1 ./template
update_files_and_dirs $1 ./build.sh
update_files_and_dirs $1 ./CMakeLists.txt
update_files_and_dirs $1 ./InitProject.py
update_files_and_dirs $1 ./main.cpp
update_files_and_dirs $1 ./updatetestcode.sh