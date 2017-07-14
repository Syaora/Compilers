#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "inifile.h"
#include <map>

using namespace std;


IniFile::IniFile(string filename)
{
    ifstream inp;
    string line, current;

    regex section_test("\\[(.*?)\\]");
    regex value_test("(\\w+)=([^\\+]+(?!\\+{3}))");
	
    inp.open(filename.c_str(), ios::in);
    if (inp.is_open())
    {
	while(getline(inp,line))
	{
	    if (line.length() > 0) //Ignore empty lines
	    {
		smatch result;
		if (regex_search(line, result, section_test))
		{
		    current = result[1]; //adds new section
		} else if (regex_search(line, result, value_test)) {
		    mapIniFile[current][result[1]] = result[2]; //adds properties under section
		}
	    }
		  
	}
     }
     inp.close();

}

string IniFile::GetProfileString(string section, string property_name)
{
    for (auto const &sectionMap : mapIniFile) //Loops through section map
    {
	if (sectionMap.first == section)  //If section matches look through property map
	{
	    auto const &innerMap = sectionMap.second;
	    for (auto const &propertyMap : innerMap)
	    {
		if (propertyMap.first == property_name)  //If property matches, return property value
		{ return propertyMap.second; }  
	    }
	}
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
     return 0;
}
