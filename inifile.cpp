/*
CPSC 323 Summer 2017
Project 1
Group Members: Abraham Ludlam, Qiyuan Liu, Elizabeth Nguyen
*/
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "inifile.h"
#include <map>
#include <algorithm>

using namespace std;


IniFile::IniFile(string filename)
{
    ifstream inp;
    string line, current;

    regex section_test("\\[(.*?)\\]");
    regex value_test("(\\w+)=([^\\+]+(?!\\+{3}))");
    regex comments("(;|#).*$");
	
    inp.open(filename.c_str(), ios::in);
    if (inp.is_open())
    {
	while(getline(inp,line)) 
	{
	    line = regex_replace(line, comments, ""); //removes comments
	    if (line.length() > 0) //Ignore empty lines
	    {
		smatch result;
		if (regex_search(line, result, section_test))
		{
		   current = result[1];  //adds new section 
		   transform(current.begin(), current.end(), current.begin(), ::tolower); //make section lowercase
		} else if (regex_search(line, result, value_test)) {
		   if (current == "") { current = "Global"; }
		   string hold = result[1];
		   transform(hold.begin(), hold.end(), hold.begin(), ::tolower); //makes property lowercase
		   mapIniFile[current][hold] = result[2]; //adds properties under section
		}
	    }	  
	}
     }
     inp.close();

}

string IniFile::GetProfileString(string section, string property_name)
{
    map<string, map<string, string>>::iterator iter = mapIniFile.find(section);
    if (iter != mapIniFile.end()) //if section is found, look for property
    {
	map<string, string>::iterator innerIter = iter->second.find(property_name);
	if (innerIter != iter->second.end()) //if property is found, return value
	{ return innerIter->second; }
    }
    return "Does not exist";
}

void IniFile::printMap()
{
     for(auto const &sectionMap : mapIniFile) //Prints the section and the properties associated with it
     {
	 cout << "SECTION " << sectionMap.first << endl;
	 auto const &inner_map = sectionMap.second;
	 for(auto const &propertyMap : inner_map) {
	    cout << "PROPERTY " << propertyMap.first << endl;
	    cout << "VALUE " << propertyMap.second << endl;
	  }
	  cout << endl;
     }
}

int main()
{

     IniFile test("text.ini");
     test.printMap();
     
     string sec, prop;
     bool con = true;
     while (con)
     {
     cout << "Please enter section and property name: " << endl;
     cin >> sec >> prop;
     cout << endl << test.GetProfileString(sec, prop) << endl;
     cout << "Continue? (y/n)" << endl;
     cin >> sec;
     if (sec == "n" || sec == "N")
 	{ con = false; }
     }
     return 0;
}
