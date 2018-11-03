Project: 	Version Control System (VCS)
Class Number: 	CPSC 362: Software Engineering
About:
	A Version Control System using Boost C++ Libraries for CPSC 362: Software Engineering Class using UNIX. We are implementing a "create repo", "check in", and "check out" feature. 
Group-Name: 	RNA
Team-Members: 	Randy Le:	97Randy.le@gmail.com
		Alex Liao: 	ycl@csu.fullerton.edu
		Nathan: 	<email>
		Dom Feeley: 	feeley.dominik@csu.fullerton.edu
External Requirements:
		-Required to have g++ that supports c++17
		-Required to have boost c++ libraries: date_time, filesystem, and system.
Features:
		-View current working directory
		-List out files in current working directory
		-Create a repository of "ptree"
		-Check-in
		-Check-out
Contents:
	main.cpp
	ptree (folder)
	libboost_date_time.dylib 	(library)
	libboost_filesystem.dylib 	(library)
	libboost_system.dylib 		(library)
	README.txt
	README.md
Setup and Installation for UNIX:
	Make sure the boost file is at its default directory 
	(usually 	/usr/local/boost-1.67.0)

	Run the command:
		$ g++ -std=c++17 -I /usr/local/boost_1_67_0 -L /usr/local/boost_1_67_0/stage/lib main.cpp -o rnavcs -lboost_system -lboost_filesystem -lboost_date_time

	If your boost file is located somewhere else then use the following as a format. Change the INCLUDE file destination (-I) and LIBRARY file destination (-L):
		$ g++ -std=c++17 -I [boostdir] -L [boostdir]/stage/lib main.cpp -o rnavcs -lboost_system -lboost_filesystem -lboost_date_time

	where [boostdir] is your boost directory location.

	After successfully running the code, you will have a new executable code name "rnavcs". Run the command:
		$ ./rnavcs

Setup and Installation for Mac OS:
	
Bugs: