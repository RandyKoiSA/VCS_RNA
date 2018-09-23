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
void nextFile(struct dirent *sd, string path);

int main(int argc, char* argv[]) {
	int choice;
	const string targetpath = "repo";					//EDIT HERE FOR DESIRED TARGET PATH
	const string sourcepath = "ptree";				//EDIT HERE TO CHANGE SOURCE PATH
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
		if ((!strcmp(sd->d_name, ".")) || (!strcmp(sd->d_name, ".."))) {}
		else cout << sd->d_name << endl;
	}
	cout << "======================================\n";

	closedir(dir);
}

void createrepo(string tp, string sp, struct dirent *sd, DIR *dir) {

	//create the folder of the targetpath
	string path;
	string originalpath;
#if defined(_WIN32)		
	originalpath = _getcwd(0, 64);
	_chdir(tp.c_str());				//go into repo folder		
	_mkdir(sp.c_str());			   //create source folder in repo folder
	path = _getcwd(0, 64);
	cout << "This is where all the file will be copied at: " << path << endl;
	_chdir(originalpath.c_str());
	path = originalpath + "\\" + sp;
	cout << "Back at : " << _getcwd(0, 64) << endl;
#else
	originalpath = getcwd(0, 64);
	chdir(tp.c_str());
	mkdir(sp.c_str());
	path = getcwd(0, 64);
	cout << "This is where all the file will be copied at: " << path << endl;
	chdir(originalpath.c_str());
	cout << "Back at : " << _getcwd(0, 64) << endl;
	path = originalpath + sp;
#endif
	/* Checks if ptree exist and have it open and ready to copy to repository */
	dir = opendir(sp.c_str());		//goes into ptree
	if (dir == NULL) cout << sp << " directory was not found.\n";
	//SOMEHOW MAKE A RECURSION FUNCTION WITH THIS
	//every readdir() should check if it's a .txt file, if so, create a copy of that file
	while ((sd = readdir(dir)) != NULL) {
		if ((!strcmp(sd->d_name, ".")) || (!strcmp(sd->d_name, ".."))) {}
		else {
			nextFile(sd, path);
		}
	}

	closedir(dir);
}

void nextFile(struct dirent *sd, string path) {
	string newPath;

	DIR *dir = opendir(path.c_str());
	if (dir == NULL) {cout << path << " could not be opened.\n"; }
	else {
		while ((sd = readdir(dir)) != NULL) {
			if ((!strcmp(sd->d_name, ".")) || (!strcmp(sd->d_name, ".."))) {}
			else {
				newPath = path + "\\" + sd->d_name;
#if defined (_WIN32)
				cout << "Making " << sd->d_name << " directory...\n";
				_mkdir(sd->d_name);
				cout << "Changing directory to: " << newPath << endl;
				_chdir(newPath.c_str());
#else
				mkdir(sd->d_name);
				chdir(newPath.c_str());
#endif
				nextFile(sd, newPath);

			}
		}
	}






}