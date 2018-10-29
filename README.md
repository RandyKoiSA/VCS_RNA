# VCS_RNA

## Class Number
CPSC 362: Software Engineering

## About
	A Version Control System using Boost C++ Libraries for CPSC 362: Software Engineering Class using UNIX.
	We are implementing a "create repo", "check in", and "check out" feature. 
	
## Team RNA members
Randy Le: 97Randy.le@gmail.com

Alex Liao: ycl@csu.fullerton.edu

Nathan: <email>

Dom Feeley: feeley.dominik@csu.fullerton.edu

## Features

## Contents
	copydir.h 	
	main.cpp
	ptree
	README.txt

## External Requirements
	required to have g++ that support and compile c++17.
	required to have boost c++ libraries: date_time, filesystem, and system to be installed.

## Setup and Installation for UNIX
For UNIX:
Make sure the boost file is at its default directory (usually /usr/local/boost-1.67.0)

run the command:
```
	$ g++ -std=c++17 -I /usr/local/boost-1.67.0/include -L /usr/local/boost-1.67.0/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
```
	
if your boost file is located somewhere else then use this code:
```
	$ g++ -std=c++17 -I [boostdir]/include -L [boostdir]/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
```
where [boostdir] is your boost directory location.

## Bugs	
