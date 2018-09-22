#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>  
#include <stdlib.h>  
#include <stdio.h> 

using namespace std;


int main(int argc, char* argv[]) {
	const string targetpath = "./repo";					//EDIT HERE FOR DESIRED TARGET PATH
	const string sourcepath = "./ptree";				//EDIT HERE TO CHANGE SOURCE PATH
	//We make the assumption that we know what files are in p tree;
	ofstream file1("./ptree/mypt/hx.txt");
	ofstream file2("hx.txt");

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