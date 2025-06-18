#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
using namespace std;

string sha256(const string &input)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);

  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

  return ss.str();
}
bool exists(const string &folder)
{
  struct stat buffer;
  return (stat(folder.c_str(), &buffer) == 0);
}
bool folderExists(const string &folder)
{
  struct stat buffer;
  return (stat(folder.c_str(), &buffer) == 0);
}

string Starting()
{
  cout << "Making a new Folder, Enter the name: \n";
  string name;
  getline(cin, name);

  if (!folderExists(name))
  {
    string command = "mkdir \"" + name + "\"";
    system(command.c_str());
  }

  return name;
}

int main()
{
  string fileName = Starting();
  string userPassword;
  string savedPassword;

  ifstream infile(fileName + "/lockInfo.txt");
  bool exist = infile.is_open();
  if (exist)
  {
    getline(infile, savedPassword);
  }
  infile.close();

  cout << "Currently the folder is unlockled" << endl;
  cout << "Setup Password" << endl
       << "New Password : ";
  getline(cin, userPassword);

  ofstream outfile(fileName + "/lockInfo.txt");
  outfile << sha256(userPassword);
  outfile.close();
  system(("attrib +h +s " + fileName).c_str());
  cout << "Password set sucessfully";
}