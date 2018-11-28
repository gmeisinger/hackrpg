
#ifndef HACKER_JSONREADER_H_
#define HACKER_JSONREADER_H_

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

class JSONReader
{
private:
	std::unordered_map<std::string, std::string> attributes;
	std::string filename;
	std::ifstream infile;
	std::string jsonString;
	std::vector<std::string> map_flags;
	//active section
	//active attribute

public:
	JSONReader();
	void readFile(std::string fname);
	//void ReadLayers(std::string::size_type pos);
	//void ReadTilesets(std::string::size_type pos);
	void addAttribute(std::string line);
	std::unordered_map<std::string,std::string> getAttributes();
	std::string parseString(std::string val);
	std::string parseFilename(std::string val);
	int parseInt(std::string val);
	double parseFloat(std::string val);
	bool parseBool(std::string val);
	std::vector<int> parseIntVec(std::string val);
	std::vector<std::unordered_map<std::string,std::string>> parseMapVec(std::string val);
	bool isOpener(char c);
	bool isCloser(char c);
	bool isColon(char c);
};

#endif	//	HACKER_JSONREADER_H_