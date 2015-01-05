// Read all files in directory A, and find all files that contained string "xxx", then, 
//copy thoese files to directory B


//FIXME: 图简单，函数名没有起好，有个函数还干了多件事（原则上每个函数只干一件事）， 后面完善


#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#ifdef __cplusplus
}
#endif
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
using namespace std;


// 递归方式读取文件的一种方式
// void ReadDir(const char* dir)
// {
// 	DIR* pDir = NULL;
// 	struct dirent* pDirent = NULL;
	
// 	char base[256];
// 	char filePath[256];
	
// 	pDir = opendir(dir);
// 	if (!pDir) {
// 		printf("Open Dir Error");
// 		return;
		
// 	} else {
// 		#ifdef _DEBUG
// 		printf("Open Dir\n");
// 		#endif
// 	}

// 	while ((pDirent = readdir(pDir)) != NULL) {
// 		if (strcmp(pDirent->d_name, ".") == 0 ||
// 			strcmp(pDirent->d_name, "..") == 0) {
// 			continue;
// 		}

// 		if (pDirent->d_type == DT_REG) {
// 				strcpy(filePath, dir);
// 				strcat(filePath, "/");
// 				strcat(filePath, pDirent->d_name);
// 			}
// 		}

// 		if (pDirent->d_type == DT_DIR) {
// 			memset(base, '\0', sizeof(base)*sizeof(base[0]));
// 				// strcpy strcat are dangerous
// 			strcpy(base, dir);
// 			strcat(base, "/");
// 			strcat(base, pDirent->d_name);
// 			readDir(base);
// 		}
// 	}

// 	closedir(pDir);
// }

bool IsThisFileContainedString(const string& file, const string& theString)
{
	ifstream input(file.c_str());
	if (!input) {
		cerr << "open file failed." << endl;
		input.clear();
		assert(!input);
	}
	string line("");
	while (getline(input, line)) {
		if (line.find(theString) != string::npos) {
			input.close();
			return true;
		}
	}
	input.close();
	 
	return false;
}

void CopyFileToDirectory(const string& filepath, const string& dstdir, const std::string& filename)
{
	ifstream src(filepath.c_str(), std::ios::binary);
	string dstfile = dstdir + "/" + filename;
	ofstream dst(dstfile.c_str(), std::ios::binary);
	dst << src.rdbuf();
}



void DoProcess(const std::string& filepath, const std::string& dstdir, const std::string& filename, const string theString)
{
	
	cout << filepath << endl;
	if (IsThisFileContainedString(filepath, theString)){
		CopyFileToDirectory(filepath, dstdir, filename);
	}
	
}


void ReadDir2(const string dir_)
{
	DIR* dir = NULL;
	struct dirent* dirent = NULL;
	stack<string> dirs;  //FIXME: due to too many files, dirs in heap is better
	dirs.push(dir_);
	while (!dirs.empty()) {
		const string currentDir = dirs.top();
		dirs.pop();
		dir = opendir(currentDir.c_str());
		assert(dir);
			//因为文件比较多，最好用多线程对每个子目录进行处理
			if (strcmp(dirent->d_name, ".") == 0 ||
				strcmp(dirent->d_name, "..") == 0) continue;
			if (dirent->d_type == DT_REG) {
				string filename = dirent->d_name;
				string filepath = currentDir + "/" + filename;
				DoProcess(filepath, "/home/ken/Desktop", filename, "zhang yunfeng");//left stuff done in this function
			}
			if (dirent->d_type == DT_DIR) {
				string dirname = dirent->d_name;
				string dirpath = currentDir + "/" + dirname;
				dirs.push(dirpath);
			}
		}
		closedir(dir);
	}
}



int main(void)
{
	string thisdir("/home/ken/Desktop/testdir");
	
	ReadDir2(thisdir);
	
	return 0;
}
