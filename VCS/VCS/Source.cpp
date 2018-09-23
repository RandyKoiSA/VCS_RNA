#include "dirent.h"
#include <iostream>
#include <sys/types.h>
#include <string>
#include <stdlib.h>  
#include <stdio.h> 
#include <direct.h>
using namespace std;

void menu();
void viewptree(struct dirent *sd, DIR *dir);
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

	//We make the assumption that we know what files are in p tree;
	//ofstream file1("./ptree/mypt/hx.txt");
	//ofstream file2("hx.txt");
	//TESTING IF FILES OPEN
	//if (!file1) cout << "failed to open file 1\n";
	//else cout << "opened file 1\n";
	//if (!file2) cout << "failed to open file 2\n";
	//else cout << "opened file 2\n";
	//if (file1.is_open()) {
	//	file1 << "this file works\n";
	//}
	//if (file2.is_open()) {
	//	file2 << "this file works\n";
	//}
	//file1.close();
	//file2.close();
	//

	cout << "creating repository";

	_mkdir(targetpath.c_str());
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
	if (dir == NULL) cout << "file does not exist\n";
	while ((sd = readdir(dir)) != NULL) {
		cout << sd->d_name << endl;
	}
}

