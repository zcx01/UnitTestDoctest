#!/usr/bin/python3
import os
import sys
import json
import argparse


BUILDINGBLOCKSBEGIN='#[begin]'
BUILDINGBLOCKEND='#[end]'
def wirteFileDicts(data,file,replace=True):
    cr = open(file, "w")
    if replace:
        cr.write(str(data))
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
    os.system("cp -rf ./template/* ./")

def get_relative_subdirectories(path,isAddSelf):
    """
    递归获取指定目录下所有子目录的相对路径。
    :param path: 目录路径
    :return: 子目录相对路径生成器
    """
    relative_paths = []

    # for (dirpath,dirnames,filenames) in os.walk(os.path.abspath(path)):
    #         for dir in dirnames:
    #             print(dirpath+'/'+dir)
    for dirpath,dirnames,filenames in os.walk(path):
        # 计算相对路径
        relative_root = os.path.relpath(dirpath, start="./")
        for dir in dirnames:
            # 构造完整的相对路径
            relative_path = os.path.join(relative_root, dir)
            relative_paths.append("                    ./"+relative_path)
        os.path.relpath("./", start=dirpath)
    is_relative_path = 0
    if (len(relative_paths) !=0 and isAddSelf == 1) or (isAddSelf == 2):
        is_relative_path = 1
        relative_paths.append("                    "+path)
    return relative_paths,is_relative_path

def modifyCMakeLists():
    CMakeLineContent = readFileLines("./CMakeLists.txt")
    CMakeLineContent,isExist = RemoveBlock(CMakeLineContent,BUILDINGBLOCKSBEGIN,BUILDINGBLOCKEND)
    test_relative_paths,test_is_relative_path=get_relative_subdirectories("./test",2)
    project_relative_paths,project_is_relative_path=get_relative_subdirectories("./project",test_is_relative_path)
    behindStr(CMakeLineContent,BUILDINGBLOCKSBEGIN,test_relative_paths,0)
    behindStr(CMakeLineContent,BUILDINGBLOCKSBEGIN,project_relative_paths,0)
    wirteFileDicts(CMakeLineContent,"./CMakeLists.txt",replace=False)


def modifyMainConent(MainLineContent,flgs,isClear):
    if isClear:
        if MainLineContent.startswith(flgs):
            MainLineContent = MainLineContent.replace(flgs,"//"+flgs)
    else:
        if MainLineContent.startswith("//"+flgs):
            MainLineContent = MainLineContent.replace("//"+flgs,flgs)
    return MainLineContent
def modifyMain(isClear=False):
    MainLineContents = readFileLines("./main.cpp")
    newMainLineContents = []
    for MainLineContent in MainLineContents:
        MainLineContent = MainLineContent.strip()
        MainLineContent = modifyMainConent(MainLineContent,"test_main()",isClear)
        MainLineContent = modifyMainConent(MainLineContent,'''#include "test/maintest.hpp"''',isClear)
        newMainLineContents.append(MainLineContent)

            
    wirteFileDicts(newMainLineContents,"./main.cpp",replace=False)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Initialize a new project')
    parser.add_argument('-p','--srcPath', help='测试依赖代码路径',default=[],nargs="*")
    parser.add_argument('-t','--testSrcPath', help='测试代码路径',default=[],nargs="*")
    parser.add_argument('-c','--clearAll', help='清除项目所有的配置,恢复为初始状态',nargs="?")
    args = parser.parse_args()

    srcPaths = args.srcPath
    testSrcPaths = args.testSrcPath

    if "-c" in sys.argv:
        os.system("rm -rf ./project/*")
        os.system("rm -rf ./test/*")
        createInitProject()
        modifyMain(True)
    else:
        if not os.path.exists("./project"):
            createInitProject()
        if srcPaths!=None and len(srcPaths) != 0:
            for srcPath in srcPaths:
                print(srcPath)
                os.system(f"ln -s {srcPath}/* ./project")
        if testSrcPaths!=None and len(testSrcPaths) != 0:
            for testSrcPath in testSrcPaths:
                os.system(f"ln -s {testSrcPath}/* ./test")
        modifyMain(False)
    modifyCMakeLists()
        
