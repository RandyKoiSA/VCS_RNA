#include "dirent.h";
#include <iostream>
#include <sys/types.h>
#include <string>
#include <stdlib.h>  
#include <stdio.h> 
#include <direct.h>
using namespace std;

void menu();
void viewptree(string src);
int main(int argc, char* argv[]) {
	int choice;
	const string targetpath = "./repo";					//EDIT HERE FOR DESIRED TARGET PATH
	const string sourcepath = "./ptree";				//EDIT HERE TO CHANGE SOURCE PATH
	//do {
	//	menu();
	//	cin >> choice;
	//	switch (choice) {
	//	case 1:
	//		break;
	//	case 2:
	//		viewptree(sourcepath);
	//		break;
	//	case 3:
	//		break;
	//	case 0:
	//		exit;
	//		break;
	//	}
	//} while (choice != 0);

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
	DIR* sp = opendir(".");
	string file;
	while (sp != NULL) {
		file = readdir(sp)->d_name;
	}
	cout << file;
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

void viewptree(string src) { 

}

