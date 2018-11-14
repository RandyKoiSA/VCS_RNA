+==============+================================================================+
|PROJECT       |	Version Control System (VCS)				|
|CLASS NUMBER  |	CPSC 362: Software Engineering	        		|
+===============================================================================+

+===============================================================================+
|ABOUT										|
|A Version Control System using Boost C++ Libraries for CPSC 362: 		|
|Software Engineering Class using UNIX. This version control system will	|
|create a repository from an existing project folder. We then implemented	|
|a feature called "check-out" which forks the created repository. We also	|
|have the "check-in" feature which merges the check-out repository to the	|
|created repository. We have extra features, such as printing working    	|
|directory and listing files from the working directory.		 	|
+===============================================================================+
	
+===============================================================================+	
|GROUP-NAME: 	RNA							 	|
|TEAM-MEMBERS:									|
|	Randy Le:	97Randy.le@gmail.com			 		|
|	Alex Liao: 	ycl@csu.fullerton.edu			 		|
|	Nathan: 	nathrich@csu.fullerton.edu			 	|
|	Dom Feeley: 	feeley.dominik@csu.fullerton.edu		 	|
+===============================================================================+

+===============================================================================+
|EXTERNAL REQUIREMENTS							|
|	-Required to have g++ that supports c++17		 	 	|
|	-Required to have boost c++ libraries: date_time, filesystem, 	 	|
|	 and system.							 	|
+===============================================================================+

+===============================================================================+
|FEATURES									|
|		-View current working directory					|
|		-List out files in current working directory			|
|		-Create a repository of "ptree"					|
|		-Check-in							|
|		-Check-out							|
+===============================================================================+

+===============================================================================+
|CONTENTS									|
|	main.cpp								|
|	ptree (folder)								|
|	libboost_date_time.dylib 	(MAC OS library)			|
|	libboost_filesystem.dylib 	(MAC OS library)			|
|	libboost_system.dylib 		(MAC OS library)			|
|	libboost_date_time.so.1.67.0 	(LINUX OS library)			|
|	libboost_filesystem.so.1.67.0 	(LINUX OS library)			|
|	libboost_system.so.1.67.0 	(LINUX OS library)			|
|	README.txt								|
|	README.md								|
+===============================================================================+

+===============================================================================+
|SETUP AND INSTALLATION FOR UNIX						|
+-------------------------------------------------------------------------------+
| Make sure the boost file is at its default directory				|
| (usually 	/usr/local/boost-1.67.0)					|
+===============================================================================+

+===============================================================================+
| Run the command: Replace x.xx.x or x_xx_x with your Boost version.		|
+-------------------------------------------------------------------------------+
Linux:
$ g++ -std=c++17 -I /usr/local/boost_x_xx_x/ -L /usr/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
or
$ g++ -std=c++17 -I /usr/local/boost_x_xx_x/ -L ./ main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
+===============================================================================+

+===============================================================================+
| If your boost file is located somewhere else then use the following as a	|
| format. Change the INCLUDE file destination (-I)				|
| and LIBRARY file destination (-L):						|
+-------------------------------------------------------------------------------+
	$ g++ -std=c++17 -I [boostdir] -L /usr/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
|                                                                                                               
| where [boostdir] is your boost directory location.				|
+===============================================================================+

+===============================================================================+
|After successfully running the command, you will have a new executable		|
|file in the folder called "main". Run the command:				|
+-------------------------------------------------------------------------------+
	$ ./main                                                 
+===============================================================================+

+===============================================================================+
|SETUP AND INSTALLATION FOR Mac OS						|	
+-------------------------------------------------------------------------------+	
|Make sure the boost file is at its default directory.				|	
|Make sure to know where the boost libraries are.				|	
+===============================================================================+	

+==============================================================================+	
|Run the command: Replace x.xx.x or x_xx_x with your Boost version.		|	
+-------------------------------------------------------------------------------+	
MacOS:
	$ g++ -std=c++17 -I /usr/local/boost-x.xx.x/include -L /usr/local/boost-x.xx.x/lib main.cpp -o main -lboost_system -lboost_filesystem -lboost_date_time
										|
+===============================================================================+	

+===============================================================================+	
|After successfully running the command, you will have a new executable		|	
|file in the folder called "main". Run the command:				|	
+-------------------------------------------------------------------------------+	
	$ ./main	
+===============================================================================+	

+===============================================================================+
|BUGS										|
+===============================================================================+
|When initially starting the program, make sure that the command are executed	|
|in order. So create repo, check-out, then check-in would be the order to	|
|execute the program.								|
+===============================================================================+
