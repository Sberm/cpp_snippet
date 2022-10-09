#include<iostream>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
using namespace std;

char dest[] = "/Users/zhuhaowei/Desktop/笔记/c++相关/snippets/";

bool check_exist(char* fn){
	DIR *d;
	struct dirent* a;
	if (!(d = opendir(dest))) {
		cout << "path doesn't exist!" << endl;
		exit(0);
	}
	else{
		//vector<string> file_name;
		while((a = readdir(d)) != NULL){
			if (strcmp(a->d_name,"..") != 0 && strcmp(a->d_name,".") != 0){
				if (!strcmp(a->d_name,fn)){
					return false;
				}
			}
		}
		return true;
	}
}

int main(int argc, char *argv[]){
	
	if (argc <= 1){
		cout << "require filename as parameter" << endl;
		exit(0);
	}
	// char *char_array will cause bus error
	char char_array[250];
	strcpy(char_array,argv[1]);

	char dir[250];
	strcpy(dir,dest);
	strcat(dir,char_array);
	
	if(!check_exist(char_array)){
		cout << "file already exists. moving to new location failed!" << endl;
		exit(0);
	}

	int dd = open("/Users/zhuhaowei/Desktop/笔记/c++相关/snippets/",O_RDONLY);
	int r = renameat(AT_FDCWD,char_array,0,dir);
	if (r){
		cout << "error occurred, moving file failed" << endl;
	}
	else {
		// cout << "move to " << "\"" << dest << "\"" << " succeed" << endl;
		cout << "move succeed" << endl;
	}

	return 0;
}
