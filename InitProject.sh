#!/usr/bin/bash
if [ $# -ne 1 ]; then
    echo "Please enter a project name!"
    exit 1
fi
python InitProject.py -p $1/src/ic_service/generated $1/src/ic_service/src/fds/base/