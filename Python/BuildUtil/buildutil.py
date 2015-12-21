#!/usr/bin/env python

# About the config.xml this util can handled:
####################################################################################
# All elements:
#    project: this is root element, every config.xml
#          attribute: name  project name
#should only have one project element
#
#    dir: this is a dir elemment that include some file elements as sub elements11
#         attribute: name directory name
#
#    file: this is the file element will be modified.
#         attribute: name  file name
#
#    operator: 


import shutil
import traceback
import os
from functools import wraps
import subprocess
import re

try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree


def debug(func):
    # func is function to be wrapped
    @wraps(func)
    def wrapper(*args, **kwargs):
        print func.__qualname__
        return func(*args, **kwargs)
    return wrapper

@debug
def copy_dir_recursively(src, dst):
    '''
    copy a directory from src to dst recursively
    '''
    shutil.copytree(src, dst, True)


@debug    
def delete_dir(dirname):
    shutil.rmtree(dirname)


@debug
def delete_file(filepath):
    os.remove(filepath)


@debug
def comment_blocks(filepath, linefrom, lineto, commentchar):
    with open(filepath, "r+") as filereader:
        content = ""
        lineno = 0
        for line in filereader.readlines():
            lineno = lineno + 1
            if lineno >= linefrom and lineno <= lineto:
                content = content + commentchar + line
            else:
                content = content + line
        with open(filepath, "w+") as filewriter:
            filewriter.write(content)


@debug
def uncomment_blocks(filepath, linefrom, lineto, commentchar):
    with open(filepath, "r+") as filereader:
        content = ""
        lineno = 0
        for line in filereader.readlines():
            lineno = lineno + 1
            if lineno >= linefrom and lineno <= lineto:
                pos = line.find(commentchar)
                content = content + line[pos+1:]
            else:
                content = content + line
        with open(filepath, "w+") as filewriter:
            filewriter.write(content)


@debug
def replace_string_infile(oldstr, newstr, filename):
    with open(filename, "r+") as readfile:
        content = readfile.read()
        print content
        content = content.replace(oldstr, newstr)
        print "content after replaceed: \n", content
        with open(filename, "w+") as writefile:
            writefile.write(content)


@debug
def check_and_echo(filepath, checkedstr, echotrue, echofalse):
    with open(filepath, "r+") as filereader:
        for line in filereader.readlines():
            if line.find(checkedstr) != -1:
                print echotrue
                return
        print echofalse


class ProjectXmlParser(object):
    def __init__(self, xmlfile_):
        self.xmlfile = xmlfile_
        self.dir_handling = "."
        self.file_handling = ""

    def parse_xml(self):
        self.tree = ET.parse(self.xmlfile)
        self.root_element = self.tree.getroot()
        self.handle_root_element()

    def handle_file_element(self, filenode):
        print "handle_file_element: ", filenode
        try:
            self.file_handling = filenode.attrib['name']
        except Exception as e:
            print "ERROR: filenode has no name attribute", e.message
            return
        
        if not os.path.exists(self.file_handling):
            print "ERROR: ", self.file_handling, " is not existed."
            return
        
        for node in filenode.iterfind("operator"):
            self.handle_operator_element(node)

    def handle_match_files_elements(self, filesnode):
        '''´¦Àí "files" element, support fuzzy match 
        '''
        patternstr = fileesnode.attrib['pattern']
        pattern = re.compile(pattern)
        for root, subdirs, files in os.walk(self.dir_handling):
            pos = root.find(self.dir_handling)
            subdir = root[pos + len(self.dir_handling) + 1:]
            if subdir == None or subdir == "":
                subdir = "."
            for file_ in files:
                ## to filter to get files we want
                if pattern.match(file_) != None:
                    self.file_handling = subdir + "/" + file_
                    print self.file_handling
                    ## handle operator nodes
                    for node in filesnode.iterfind("operator"):
                        self.handle_operator_element(node)

    def handle_operator_element(self, operatornode):
        print "handle_operator_element: ", operatornode
        operator = operatornode.attrib['name']
        if operator == 'delete':
            delete_file(self.dir_handling + '/' + self.file_handling)

        if operator == 'replace':
            oldstr = operatornode.attrib['oldstr']
            newstr = operatornode.attrib['newstr']
            replace_string_infile(oldstr, newstr,
                                  self.dir_handling + '/' + self.file_handling)

        if operator == 'comment':
            linefrom = int(operatornode.attrib['linefrom'])
            lineto = int(operatornode.attrib['lineto'])
            commentchar = operatornode.attrib['commentchar']
            comment_blocks(self.dir_handling + '/' + self.file_handling,
                           linefrom, lineto, commentchar)

        if operator == 'uncomment':
            linefrom = int(operatornode.attrib['linefrom'])
            lineto = int(operatornode.attrib['lineto'])
            commentchar = operatornode.attrib['commentchar']
            uncomment_blocks(self.dir_handling + '/' + self.file_handling,
                             linefrom, lineto, commentchar)

        if operator == 'check':
            includedstr = operatornode.attrib['includedstr']
            echo_true = operatornode.attrib['echo_true']
            echo_false = operatornode.attrib['echo_false']
            check_and_echo(self.dir_handling + '/' + self.file_handling,
                           includedstr, echo_true, echo_false)

    def handle_dir_element(self, dirnode):
        print "handle_dir_element: ", dirnode
        try:
            self.dir_handling = dirnode.attrib['name']
        except Exception as e:
            print "ERROR: this dirnode has no name attribute", e.message
            return
        
        if not os.path.exists(self.dir_handling):
            print "Error: dir not existed: ", self.dir_handling
            return

        for node in dirnode.iterfind("file"):
            self.handle_file_element(node)

    def handle_root_element(self):
        '''handle root element node'''
        print self.root_element.tag, self.root_element.attrib
        for node in self.root_element.iterfind("dir"):
            self.handle_dir_element(node)


def exec_command(command):
    subprocess.check_call(command)


def main():
    '''
    main test
    '''
    try:
#        copy_dir_recursively('a', './b')
#        delete_dir('./b')
       # replace_string_infile("hello", "world", "./b/a.txt")
       # pxp = ProjectXmlParser("config.xml")
       # pxp.parse_xml()
        exec_command(["ls", "-l"])
    except (IOError, OSError) as e:
        print "[FILENAME:", e.filename, "] [ERRORNO:", e.errno, "]",\
            traceback.format_exc()


if __name__ == '__main__':
    main()
