A description text file of the workings of VCS project2.

CPSC 362 Software Engineering Project #2: Check-out & Check-in.

Team Name: RNA
Name: Randy Le, 97randy.le@gmail.com
      Nathan Richards, <email:>		
      Alex Liao, ycl@csu.fullerton.edu
      Dom, <email:>

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
	FOR WINDOW USERS

-make sure to uncomment "#include WINDOWS" the first line of code that defines Window:
-When compiling with windows make sure to include dirent.h

	FOR LINUX USERS

-make sure to comment out "#include WINDOWS" at the first line of code
-first we create a output file
	$g++ -o source Source.cpp
-next, we can execute the output file
	$./source

Sample invocation & results to see:

Features (both included and missing)
There is a feature that prints all the file in the source target.

We have not made a Manifest or metadata file yet.

Bugs (if any):
	Having trouble create all the content in the ptree -> repo
