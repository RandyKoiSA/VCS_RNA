//Core program functionalities and properties.
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

const int multiplier[] = {1, 3, 7, 11, 17};

const string cmdList[] = {"Exit", "View Project Source Directory", "View Project Repo Directory",
                          "Create Project Repository", "Project Check-Out", "Project Check-In"};

ptime invalidTime = time_from_string("1900-01-01 08:00:00");

/*
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
string makeID(stringstream&);

/*
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
        copy_file(args.manifestPath, REPO_PATH.string() + "/Manifest.txt",
                  boost::filesystem::detail::overwrite_if_exists);
        break;
      case 4:
        args.manifestPath = REPO_PATH.string() + "/Manifest.txt";
        updateManifest(args);
        createRepo(REPO_PATH, REPO_PATH /".."/ "VCS_Proj_Fork" += to_string(forks += 1), args);
        break;
    }
  } while (choice != 0);
  return 0;
} // End of Main()

/*
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

/*
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
    fileOp << "Command » " << cmdList[args.cmd] << " @ "<< args.cmdTime << "\n";
    args.repoTime = invalidTime;
  }
  else {
    cout << "desc: " << args.desc << endl;
    if (!fileOp.is_open()) {
      cout << "not open\n";
      cout << "args.path: " << args.filePath << endl;
    }
    fileOp << "   File » " << args.desc << " @ path = " << args.filePath << "\n";
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

//  if (invalidTime != args.cmdTime) { cout << "set args.cmdtime to invalid\n"; args.cmdTime = invalidTime; }
  
  if (".dylib" != target.extension()
      && "Manifest.txt" != target.filename() && "main" != target.filename())
  {
    string desc;
    
    fileOp.open(target, ios::in);
    
    if (!fileOp.is_open()) { cout << "Failed to open file!\n"; }
    
    while(fileOp >> strStream.rdbuf());
    
    getline(strStream, desc);
    args.desc = target.filename().string() + ": " + desc;
    
    fileOp.close();
  }
  return strStream;
} // End of fileReader(..)


/*
 makeID
 @param stringstream &stream
*/
string makeID(stringstream& stream)
{
  int ckSum = 0, counter = 0;
  for (int ix = 0; ix != stream.str().size(); ++ix)
  {
    ckSum += int(stream.str()[ix]) * multiplier[counter];
    ++counter;
    if (5 == counter) { counter = 0; }
  }
  string id = to_string(ckSum) + "-L" + to_string(stream.str().size());
  // <Missing: modulus operation on over sized cksum>
  return id;
} // End of makeID(.)


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
      path relative;
      cout << "is file, path: " << target / entry.path().filename() << endl;
      
      if (invalidTime != args.cmdTime)
      {
        cout << "set args.cmdtime to invalid\n";
        args.cmdTime = invalidTime;
      }
      if (".cpp" == entry.path().filename().extension() || "README.txt" == entry.path().filename())
      {
        stringstream strStream;
        string id;
        switch (args.cmd) {
          case 4:
            copy_file(entry, target / entry.path().filename());
            break;
          case 3:
          case 5:
            strStream = fileReader(entry, args);
            //strStream = fileReader(target / entry.path().filename(), args);
            id = makeID(strStream);
            id += entry.path().extension().string();
            cout << "id w/ ext.: " << id << endl;
            path leave = target / entry.path().filename();
            create_directory(leave);
            fileOp.open(leave.string() / id, ios::out | ios::app);
            fileOp << strStream.rdbuf();
            fileOp.close();
            break;
        }
      }
      else
      {
        copy_file(entry, target / entry.path().filename());
        args.desc = entry.path().filename().string();
      }
      relative = boost::filesystem::relative(target / entry.path().filename(), "../");
      args.filePath = relative.string();
      updateManifest(args);
    }
    
  }
} // End of createRepo(...)
