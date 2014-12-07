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

    '''
    header_list = []
    source_list = []
    for item in file_list:
        
class MakefileGenerator:
    def __init__(self，compiler, option, outfile, libs):
        self.compiler = compiler
        self.option = option
        self.outfile = outfile
        self.makefile = ""
        self.libs = libs

    def SetSourceFiles(self, headers, srcs):
        self.header_list = headers
        self.srcs_list = srcs

    def GenerateMakefile(self):
        makefile = "Compiler := g++\n"
        makefile = makefile + "CPPFLAGS := " + option + " \n"
        makefile = makefile + "$LIBS := " + libs + " \n"
        makefile = makefile + "HEADERS := \\\n"
        for header_item in header_list:
            makefile = makefile + header_item + " \\\n"
        makefile = makefile + "SRC := \\\n"
        for src_item in srcs_list:
            makefile = makefile + src_item + " \\\n"
        makefile = makefile + "\n\n"
        makefile = makefile + outfile + ":" + "$HEADERS," + "$SRC\n"
        makefile = makefile + " " + "$Compiler $CPPFLAGS -o $@ $(HEADERS) $(SRC) $(LIBS) \n\n"
        makefile = makefile + ".PHONY:clean\n"
        makefile = makefile + "clean:\n"
        makefile = makefile + "rm *~ " + outfile



if __name__ == '__main__':
    dirs, files = GetAllFilesInDir("/home/ken/CodeRom/workspace/GameEngine")
