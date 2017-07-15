/*
CPSC 323 Summer 2017
Project 1
Group Members: Abraham Ludlam, Qiyuan Liu, Elizabeth Nguyen
*/
#ifndef INIFILE_H_
#define INIFILE_H_
#include <string>

using namespace std;

class IniFile
{
    public:
	IniFile(string filename);
	string GetProfileString(string section, string property_name);
	void printMap();
    private:
	map<string, map<string, string>> mapIniFile;
};

#endif //INIFILE_H_
	
