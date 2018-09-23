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
void createrepo(string tp,string sp, struct dirent *sd, DIR *dir);

int main(int argc, char* argv[]) {
	int choice;
	const string targetpath = "./repo/";					//EDIT HERE FOR DESIRED TARGET PATH
	const string sourcepath = "./ptree";				//EDIT HERE TO CHANGE SOURCE PATH
	struct dirent *sd = NULL;							//sd is basically the current directory
	DIR *dir = opendir(sourcepath.c_str());				//dir will be the dir we plan on copying

	do {
		menu();
		cin >> choice;
		switch (choice) {
		case 1:
			createrepo(targetpath, sourcepath, sd, dir);
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
	dir = opendir("./ptree");								//JUST MAKING IS SIMPLE SINCE WE KNEW WHERE THE SOURCE PATH IS
	cout << "======================================\n";
	if (dir == NULL) cout << "file does not exist\n";

	while ((sd = readdir(dir)) != NULL) {
		cout << sd->d_name << endl;
	}
	cout << "======================================\n";

	closedir(dir);
}

void createrepo(string tp, string sp, struct dirent *sd, DIR *dir) {
	/* Checks if ptree exist and have it open and ready to copy to repository */
	dir = opendir(sp.c_str());
	if (dir == NULL) cout << sp << " directory was not found.\n";
	//create the folder of the targetpath

#if defined(_WIN32)
	_chdir(tp.c_str());
	cout << _getcwd(0, 64);
	_mkdir("ptree");			//Create source project folder name
#else
	chdir(sp.c_str());
	mkdir(tp.c_str());
#endif

	while ((sd = readdir(dir)) != NULL) {
		if (!(strcmp(sd->d_name, ".")) || !(strcmp(sd->d_name, "..")))
		{
		}
	}

	closedir(dir);
}
