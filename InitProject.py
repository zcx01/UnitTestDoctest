#!/usr/bin/python3
import os
import sys
import json
import argparse


BUILDINGBLOCKSBEGIN='#[begin]'
BUILDINGBLOCKEND='#[end]'
def wirteFileDicts(file,data,replace=False):
    cr = open(file, "w")
    if replace:
        for d in data:
            cr.write(str(d).replace("\'","\"")+"\n")
    else:
        cr.writelines('\n'.join(data))
    cr.close()

#-------------------------------文本相关操作-------------------------------
def readFileLines(file):
    with open(file, "r") as cr:
        return cr.read().splitlines()
#在lines关键字behind后面添加content, number:第几个,-1表示末尾
def behindStr(lines,behind,content,number=-1):
    index = 0
    behinds=[]
    row=0
    numberIndex=0
    while index < len(lines):
        if behind in lines[index]:
            behinds.append(lines[index])
            row = index+1
            if numberIndex == number:
                break
            numberIndex+=1
        index+=1
    if type(content) == str:
        if content not in behinds:
            lines.insert(row,content)
    elif type(content) == list:
        behindIndex(lines,row,content)

#在指定行后面添加contents
def behindIndex(lines,pos,contents):
    assert isinstance(lines,list)
    temp=lines.copy()
    lines.clear()
    lines.extend(temp[0:pos])
    lines.extend(contents)
    lines.extend(temp[pos:len(temp)])
    return lines
'''
移除文本块
lineTexts:文本
beginStr:开始标志
endStr:结束标志
返回一处后的文本，和是否存在可以移除的文本
'''
def RemoveBlock(lineTexts,beginStr,endStr):
    assert isinstance(lineTexts,list)
    tmp=[]
    isRemove = False
    isExistence = False
    for lineText in lineTexts:
        if beginStr in lineText:
            tmp.append(lineText)
            isRemove = True
            isExistence = True
        elif endStr in lineText:
            isRemove = False
        if not isRemove:
            tmp.append(lineText)
    return tmp, isExistence

def createInitProject():
    vehicle_name_hpp = '''#pragma once
#include <string>
#define ECU_TABLE_USER_POWER_MODE 0
#define ECU_TABLE_USER_C385_VEHICLE_TYPE 1
#define ECU_TABLE_USER_DA_SOLUTION  2

class VehicleName 
{
public:

    static int getEcuConfig(uint32_t id);
};'''

    vehicle_name_cpp = '''#include "VehicleName.hpp"

int VehicleName::getEcuConfig(uint32_t id)
{
    return 0;
}'''

    fds_can_main_entry_hpp = '''#pragma once

#include "parser_typedef.h"

#ifdef __cplusplus
extern "C"
{
#endif
    extern void init_signal_process();
#ifdef __cplusplus
}
#endif'''

    fds_can_main_entry_cpp = '''#include "fds_can_main_entry.hpp"
#include "init_fds_can_main_entry.hpp"
#include <map>

std::map<struct veh_signal *, std::set<std::shared_ptr<BaseFdsModule>>> signal_modules_map;
void init_signal_process()
{
    init_signal_process_up();
    init_signal_process_down();
}'''

    maintest_hpp = '''#pragma once
#include "icdoctest.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void test_main();

#ifdef __cplusplus
}
#endif'''

    maintest_cpp ='''#include "maintest.hpp"
#include "can_api.h"
#include "icdoctest.h"
#include "project/fds_can_main_entry.hpp"

void test_main()
{
    init_signal_process();
}'''

    wirteFileDicts(vehicle_name_hpp, "./project/vehicle_name.hpp")
    wirteFileDicts(vehicle_name_cpp, "./project/vehicle_name.cpp")

    wirteFileDicts(fds_can_main_entry_hpp, "./project/fds_can_main_entry.hpp")
    wirteFileDicts(fds_can_main_entry_cpp, "./project/fds_can_main_entry.cpp")

    wirteFileDicts(maintest_hpp, "./test/maintest.hpp")
    wirteFileDicts(maintest_cpp, "./test/maintest.cpp")

def get_relative_subdirectories(path,CMakeLineContent):
    """
    递归获取指定目录下所有子目录的相对路径。
    
    :param path: 目录路径
    :return: 子目录相对路径生成器
    """
    for root, dirs, files in os.walk(path):
        # 计算相对路径
        relative_root = os.path.relpath(root, start=path)
        for dir in dirs:
            # 构造完整的相对路径
            relative_path = os.path.join(relative_root, dir)
            yield relative_path

def modifyCMakeLists():
    CMakeLineContent = readFileLines("./CMakeLists.txt")
    CMakeLineContent,isExist = RemoveBlock(CMakeLineContent,BUILDINGBLOCKSBEGIN,BUILDINGBLOCKEND) 
    relative_sub_dirs = list(get_relative_subdirectories("./project"))
    behindStr(CMakeLineContent,BUILDINGBLOCKSBEGIN,relative_sub_dirs,0)
    relative_sub_dirs = list(get_relative_subdirectories("./test"))
    behindStr(CMakeLineContent,BUILDINGBLOCKSBEGIN,relative_sub_dirs,0)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Initialize a new project')
    parser.add_argument('-p','--srcPath', help='测试依赖代码路径')
    parser.add_argument('-t','--testSrcPath', help='测试代码路径')
    parser.add_argument('-c','--clearAll', help='清楚项目所有的配置,恢复为初始状态')
    args = parser.parse_args()

    srcPath = args.srcPath
    testSrcPath = args.testSrcPath

    if "-c" in sys.argv:
        os.system("rm -rf ./project/*")
        os.system("rm -rf ./test/*")
        createInitProject()
    else:
        os.system(f"ln -s {srcPath} ./project")
        os.system(f"ln -s {testSrcPath} ./test")
    modifyCMakeLists()
        
