A description text file of the workings of VCS project2.

CPSC 362 Software Engineering Project #2: Check-out & Check-in.

Team Name: RNA
Name: Randy Le, 97randy.le@gmail.com
      Nathan Richards, <email:>		
      Alex Liao, ycl@csu.fullerton.edu
      Dom Feeley, <email:>

Intro:
	This project is a basic Version Control System that created a new repository with the target path files. 
	We create an "artifact" file so we can have all version of the file that were changed.

Contents:
	dirent.h
	Source.cpp
	ptree
	repo
	README.txt
External Requirements:
	required to have g++ or any IDE that can compile C++ code

Setup and Installation:
For UNIX:
run the code:
	$ g++ -std=c++17 -I /usr/local/boost-1.67.0/include -L /usr/local/boost-1.67.0/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time

Sample invocation & results to see:

Features (both included and missing)
There is a feature that prints all the file in the source target.

We have not made a Manifest or metadata file yet.

Bugs (if any):
	Having trouble create all the content in the ptree -> repo
