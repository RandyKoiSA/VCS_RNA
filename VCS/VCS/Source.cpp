#define WINDOWS				/*uncomment this line to use it for windows*/
#ifdef WINDOWS
#include "dirent.h"
#include <direct.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include <sys/types.h>		//required to make files
#include <sys/stat.h>		//required to make files
#include <iostream>
#include <string>
#include <stdlib.h>  
#include <stdio.h> 

using namespace std;

void menu();
void viewptree(struct dirent *sd, DIR *dir);
void createrepo(string tp);

int main(int argc, char* argv[]) {
	int choice;
	const string targetpath = "./repo";					//EDIT HERE FOR DESIRED TARGET PATH
	const string sourcepath = "./ptree";				//EDIT HERE TO CHANGE SOURCE PATH
	struct dirent *sd = NULL;
	DIR *dir = opendir(sourcepath.c_str());

	do {
		menu();
		cin >> choice;
		switch (choice) {
		case 1:
			createrepo(targetpath);
			break;
		case 2:
			viewptree(sd, dir);
			break;
		case 3:
			break;
		case 0:
			exit;
			break;
		}
	} while (choice != 0);

	return 0;
}

void menu() {
	cout << "===============VCS CLI===============\n";
	cout << "\t1.Create repository\n";
	cout << "\t2.View project tree\n";
	cout << "\t0.Exit\n";
}

void viewptree(struct dirent *sd, DIR *dir) { 
	dir = opendir("./ptree");
	cout << "======================================\n";
	if (dir == NULL) cout << "file does not exist\n";

	while ((sd = readdir(dir)) != NULL) {
		cout << sd->d_name << endl;
	}
	cout << "======================================\n";

	closedir(dir);
}

void createrepo(string tp) {
#if defined(_WIN32)
	_mkdir(tp.c_str());
#else
	mkdir(tp.c_str());
#endif
}
