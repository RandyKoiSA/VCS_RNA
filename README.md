# VCS_RNA

## Class Number
CPSC 362: Software Engineering

## About
	A Version Control System using Boost C++ Libraries for CPSC 362: Software Engineering Class using UNIX.
	This version control system will create a repository from an existing project folder. 
	We then implemented a feature called "check-out" which forks the created repository.
	We also have the "check-in" feature which merges the check-out repository to the created repository.
	We have extra features, such as printing working directory and listing files from the working directory.
	
	
	
## Team RNA members
Randy Le: 97Randy.le@gmail.com

Alex Liao: ycl@csu.fullerton.edu

Nathan: nathrich23@csu.fullerton.edu

Dom Feeley: feeley.dominik@csu.fullerton.edu

## External Requirements
	- required to have g++ that support and compile c++17.
	- required to have boost c++ libraries: date_time, filesystem, and system.

## Features
	-View current working directory
	-List out files in current working directory
	-Create a repository of "ptree"
	-Check-in
	-Check-out
## Contents
	main.cpp
	ptree (folder)
	libboost_date_time.dylib 	(MAC OS library)
	libboost_filesystem.dylib 	(MAC OS library)
	libboost_system.dylib 		(MAC OS library)
	libboost_date_time.so.1.67.0 	(LINUX OS library)
	libboost_filesystem.so.1.67.0 	(LINUX OS library)
	libboost_system.so.1.67.0 	(LINUX OS library)
	README.txt
	README.md

## Setup and Installation for UNIX
	- Make sure the boost file is at its default directory.
		(usually 	/usr/local/boost-1.67.0)
	- Make sure to know where the boost libraries are.

Run the command:
```
	$ g++ -std=c++17 -I /usr/local/boost_1_67_0/ -L /usr/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
```
Usually the libraries is either in [boostdirectory]/stage/lib or [/usr/lib].

If your boost file is located somewhere else then use the following as a format. Change the INCLUDE file destination (-I) and LIBRARY file destination (-L):
```
	$ g++ -std=c++17 -I [boostdir] -L /usr/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
```
where [boostdir] is your boost directory location.

After successfully running the command, you will have a new executable file in the folder called "main". Run the command:
```
	$ ./main
```

## Setup and Installation for Mac OS
	- Make sure the boost file is at its default directory.
		(usually [])
	- Make sure to know where the boost libraries are.
Run the command:
```
	$ g++ -std=c++17 -l/usr/local/boost-1.67.0/include -L /usr/local/boost-1.67.0/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
```
After successfully running the command, you will have a new executable file in the folder called "main". Run the command:
```
	$ ./main
```
## Bugs	
