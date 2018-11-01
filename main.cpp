//  Core program functionalities and properties.
//  Modify above line of description for every file modification.
//  main.cpp
//  Created by Alex Liao, Randy Le, Nathan Richards, and Dom Feeley on 2018/9/26.
//
//

#include <string>
#include <sstream>
#include <iostream>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::filesystem;

boost::filesystem::fstream fileOp;

const string cmdList[] = {"Exit", "View Project Source Directory", "View Project Repo Directory",
                          "Create Project Repository", "Project Check-Out", "Project Check-In"};

ptime invalidTime = time_from_string("1900-01-01 08:00:00");

/**
 Arglist struct
 grabs detail of command executed and add it into the manifest file.
 */
struct ArgList {
  int cmd = -1;
  ptime cmdTime, repoTime;
  string filePath = "", manifestPath = "", desc = "";
};

void menu();
void viewDirectory(path);
void updateManifest(ArgList&);
stringstream fileReader(path, ArgList&);
void createRepo(path, path, ArgList&);

/**
 Main Method
 */
int main(int argc, const char * argv[])
{
  int choice, forks = 0;
  // Struct to hold arguments to be passed into function: updateManifest.
  ArgList args;
  // Time object to hold current time of the user chosen command.
  ptime cmdTime;
  // Get the current directory -> project source directory
  auto projectPath = current_path();
  // Edit for Windows directory format: ' \ '
  path REPO_PATH("../Project_Repo");
  
  do {
    menu();
    cin >> choice;
    
    // Get current date & time
    cmdTime = second_clock::local_time();
    args.cmdTime = cmdTime;
    args.cmd = choice;
    
    switch (choice) {
      case 1:
        viewDirectory(projectPath);   // View source
        break;
      case 2:
        viewDirectory(REPO_PATH);   // View repo
        break;
      case 3:
        args.manifestPath = projectPath.string() + "/Manifest.txt";
        if (invalidTime != args.repoTime) { updateManifest(args); }
        createRepo(projectPath, REPO_PATH, args);
        copy_file(args.manifestPath, REPO_PATH.string() + "/Manifest.txt", boost::filesystem::detail::overwrite_if_exists);
        break;
      case 4:
        args.manifestPath = REPO_PATH.string() + "/Manifest.txt";
        updateManifest(args);
        //create_directory(REPO_PATH/".."/ "VCS_Proj_Fork"+=to_string(forks += 1));
        createRepo(REPO_PATH, REPO_PATH/".."/ "VCS_Proj_Fork"+=to_string(forks += 1), args);
        break;
    }
  } while (choice != 0);
  return 0;
} // End of Main()

/**
 Menu Method
 */
void menu()
{
  cout << "===============VCS CLI===============\n"
  << "\t1. " << cmdList[1] << endl
  << "\t2. " << cmdList[2] << endl
  << "\t3. " << cmdList[3] << endl
  << "\t4. " << cmdList[4] << endl
  << "\t5. " << cmdList[5] << endl
  << "\t0. " << cmdList[0] << endl
  << "\tEnter choice: ";
}

/**
 viewDirectory Method
 @param   path stores the a directory path
 */
void viewDirectory(path path)
{
  // Print the content of the directory
  for(auto &entry : recursive_directory_iterator(path))
  {
    cout << entry << endl;
  }
} // End viewDirectory(.)


/*
 updateManifest Method
 
 @param args stores action executed
 */
void updateManifest(ArgList& args)
{
  fileOp.open(args.manifestPath, ios::out | ios::app);
  
  if (invalidTime != args.cmdTime)
  {
    fileOp << "*-> Command: " << cmdList[args.cmd] << " @ "<< args.cmdTime << "\n";
    args.repoTime = invalidTime;
  }
  else {
    cout << "desc: " << args.desc << endl;
    if (!fileOp.is_open()) {
      cout << "not open\n";
      cout << "args.path: " << args.filePath << endl;
    }
    fileOp << "File: " << args.desc << " @ path: " << args.filePath << "\n";
  }
  fileOp.close();
} // End of updateManifest(.)


/*
 fileReader Method
 
 @param target
 @param args
 */
stringstream fileReader(path target, ArgList& args)
{
  stringstream strStream;
  path relative;
  if (invalidTime != args.cmdTime) { cout << "set args.cmdtime to invalid\n"; args.cmdTime = invalidTime; }
  
  if (".dylib" != target.extension()
      && "Manifest.txt" != target.filename() && "main" != target.filename())
  {
    string desc;
    
    fileOp.open(target, ios::in);
    
    if (!fileOp.is_open()) { cout << "Failed to open file!\n"; }
    
    while(fileOp >> strStream.rdbuf());
    
    getline(strStream, desc);
    args.desc = target.filename().string() + ". " + desc;
    fileOp.close();
  } else {
    args.desc = target.filename().string();
  }
  relative = boost::filesystem::relative(target, "../");
  args.filePath = relative.string();
  updateManifest(args);
  return strStream;
} // End of fileReader(..)

/*
 createRepo Method
 
 @param src
 @param target
 @param args
 */
void createRepo(path src, path target, ArgList& args)
{
  if (exists(target))
  {
    cout << "The file/ folder already exists! Command not logged!" << endl;
    return;
  }
  else
  {
    cout << "target: " << target << endl;
    create_directory(target);
  }
  for(auto &entry : directory_iterator(src))
  {
    if (is_directory(entry))
    {
      createRepo(entry, target / entry.path().filename(), args);
    }
    if (is_regular_file(entry) && entry.path().filename() != ".DS_Store")
    {
      cout << "is file, path: " << target / entry.path().filename() << endl;
//      if ("main.cpp" == entry.path().filename()) {
//        create_directory(target / entry.path().filename());
//      }
      copy_file(entry, target / entry.path().filename());
      stringstream strStream = fileReader(target / entry.path().filename(), args);
    }
  }
} // End of createRepo(...)

