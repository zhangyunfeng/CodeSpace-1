#!/usr/bin/env python
#coding:utf-8

import os
import sys


def GetAllFilesInDir(dirpath_):
    '''
    Get all files in dirpath_
    return: dirs and files
    '''
    dir_list = []
    file_list = []
    files = os.listdir(dirpath_)
    for f in files:
        absf = dirpath_ + "/" + f
        if os.path.isdir(absf):
            if f[0] == '.':
                pass
            else:
                dir_list.append(absf)
        if os.path.isfile(absf):
            ##print "file item: " , absf
            file_list.append(absf)
    for diritem in dir_list:
        a, b= GetAllFilesInDir(diritem)
        dir_list = dir_list + a
        file_list = file_list + b
    return dir_list, file_list

def GetHeaderSrcList(file_list):
    '''
    解析出所有文件中的头文件和c/cpp文件
    '''
    header_list = []
    source_list = []
    for item in file_list:
        if item.endswith(".cpp") or item.endswith(".C") or item.endswith(".cxx") or item.endswith(".c++") or item.endswith(".cc") or item.endswith(".c"):
            source_list.append(item)
        if item.endswith(".h") or item.endswith(".hpp"):
            header_list.append(item)
    return header_list, source_list

class MakefileGenerator:
    def __init__(self, compiler, option, outfile, libs):
        '''
        初始化makefile中的一些变量
        '''
        self.compiler = compiler ##指定编译器
        self.option = option ##指定编译选项
        self.outfile = outfile ##指定输出文件
        self.makefile = "" ##存储makefile内容
        self.libs = libs ##指定第三方库

    def SetSourceFiles(self, headers, srcs):
        self.header_list = headers
        self.srcs_list = srcs

    def MakeFile(self, filename_):
        '''
        生成内容为filecontent_的文件filename_
        '''
        self.GenerateMakefileContent()
        print self.makefile
        with open(filename_, "w") as fileHandle:
            fileHandle.write(self.makefile)

    def GenerateMakefileContent(self):
        '''
        组织makefile内容
        '''
        self.makefile = "Compiler := " + self.compiler + "\n"
        self.makefile = self.makefile + "CPPFLAGS := " + self.option + " \n"
        self.makefile = self.makefile + "LIBS := " + self.libs + " \n"
        self.makefile = self.makefile + "HEADERS := \\\n"
        for header_item in self.header_list:
            self.makefile = self.makefile + header_item + " \\\n"
        self.makefile = self.makefile + "\n\n"
        self.makefile = self.makefile + "SRC := \\\n"
        for src_item in self.srcs_list:
            self.makefile = self.makefile + src_item + " \\\n"
        self.makefile = self.makefile + "\n\n"
        self.makefile = self.makefile + self.outfile + ":" + "$(HEADERS)," + "$(SRC)\n"
        self.makefile = self.makefile + " " + "$(Compiler) $(CPPFLAGS) -o $@ $(HEADERS) $(SRC) $(LIBS) \n\n"
        self.makefile = self.makefile + ".PHONY:clean\n"
        self.makefile = self.makefile + "clean:\n"
        self.makefile = self.makefile + "rm *~ " + self.outfile



if __name__ == '__main__':
    dirs, files = GetAllFilesInDir("E:\KenLibrary\KenLibrary\KenLibrary")
    header_list, source_list = GetHeaderSrcList(files)

    makefilegenerator = MakefileGenerator("g++", "-Wall", "KenLibrary", "")
    makefilegenerator.SetSourceFiles(header_list, source_list)
    makefilegenerator.MakeFile("E:\KenLibrary\KenLibrary\KenLibrary\Makefile")
