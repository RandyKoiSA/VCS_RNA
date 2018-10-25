//  Core program functionalities and properties.
//  Modify above line of description for every file modification.
//  main.cpp
//  Created by Alex Liao, Randy Le, Nathan, and Dom Feeley on 2018/9/26.
//
//

#include <string>
#include <sstream>
#include <iostream>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::filesystem;

boost::filesystem::fstream fileOp;

const string cmdList[] = {"Exit", "View Project Source Directory", "View Project Repo Directory",
                          "Create Project Repository", "Project Check-Out", "Project Check-In"};

ptime invalidTime = time_from_string("1900-01-01 08:00:00");

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
   path TARGET_PATH("../Project_Repo");
  
  do {
    menu();
    cin >> choice;
    // Get current date & time
    cmdTime = second_clock::local_time();
    args.cmdTime = cmdTime;
    args.cmd = choice;
    args.manifestPath = projectPath.string() + "/Manifest.txt";
    switch (choice) {
      case 1:
        viewDirectory(projectPath);   // View source
        break;
      case 2:
        viewDirectory(TARGET_PATH);   // View repo
        break;
      case 3:
        if (invalidTime != args.repoTime) {
          updateManifest(args);
        }
        createRepo(projectPath, TARGET_PATH, args);
        copy_file(args.manifestPath, TARGET_PATH.string() + "/Manifest.txt", boost::filesystem::detail::overwrite_if_exists);
        break;
    }
  } while (choice != 0);
  return 0;
} // End of Main()


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
} // End of menu()


void viewDirectory(path path)
{
  // Print the content of the directory
  for(auto &entry : recursive_directory_iterator(path))
  {
    cout << entry << endl;
  }
} // End of viewDirectory(..)


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
} // End of updateManifest(..)


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

void createRepo(path src, path target, ArgList& args)
{
  if (exists(target))
  {
    cout << "The file/ folder already exists! Command not logged!" << endl;
    return;
  } else {
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
      copy_file(entry, target / entry.path().filename());
      stringstream strStream = fileReader(target / entry.path().filename(), args);
    }
  }
} // End createRepo(..)
