#include <iostream>
#include <boost/filesystem.hpp>
#include "copydir.h";
using namespace boost::filesystem;

	int main() {
	path source{"./repo"};
	path target{"./ptree"};

	copyDir(target, source);
	return 0;
}

