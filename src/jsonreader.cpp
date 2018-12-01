#include "include/jsonreader.h"

JSONReader::JSONReader() {

}

void JSONReader::readFile(std::string fname) {
	/*PLAN:
	1. get the needed strings by 
		string::size_type position = text.find ("keyword");
		string fragment = text.substr (6, 5);
    		// start at 6, take 5 characters
    		text.erase(5, 5);
    		text.replace(5, 2, "blah");
	*/
	filename = fname;
	infile = std::ifstream(fname);
	std::string line;
	std::string jsonString = "";
	if (infile.is_open()) {
		//first line has a '{' that we dont want
		if(getline(infile,line)) {
			jsonString += line;
			addAttribute(line.substr(1,line.length()-1));
		}
		while (getline(infile,line)) {
			//concat to the json string
			jsonString += line;
			//DEBUG LINE
			//check for attribute
			if(!line.substr(0,2).compare(" \"")) {
				addAttribute(line);
			}
		}
		infile.close();
	}
	//now we gotta go back to map_flags and get those strings
	for( auto key : map_flags) {
		std::string::size_type start = jsonString.find(key);
		std::string::size_type val_start = jsonString.find("[", start);
		std::string::size_type val_end;
		int level = 0;
		for(std::string::size_type i=start;i<jsonString.length();i++) {
			if(isOpener(jsonString.at(i))) {
				level++;
			}
			else if(isCloser(jsonString.at(i))) {
				level--;
				if(level == 0) {
					val_end = i;
					break;
				}
			}
		}
		std::string val = jsonString.substr(val_start, val_end - val_start + 1);
		attributes[key] = val;
	}
	
}

/*void JSONReader::readLayers(std::string::size_type pos) {

}

void JSONReader::readTilesets(std::string::size_type pos) {
	
}*/

void JSONReader::addAttribute(std::string line) {
	//find the : and get whats on either side
	//if its a [ flag the key string
	std::string::size_type col_pos = line.find(":");
	std::string::size_type key_pos = line.find("\"") + 1;
	std::string::size_type key_len = col_pos - 1 - key_pos;
	std::string key =  line.substr(key_pos, key_len);
	/*
		right side could be a:
		string
		int
		float
		bool
		vector of ints
	*/
	//for now lets just get it as a string
	std::string::size_type val_len = line.length() - col_pos;
	std::string val = line.substr(col_pos + 1, val_len);
	if(!val.substr(val_len -2, 1).compare(",")) {
		val.erase(val_len -2, 1);
	}
	attributes[key] = val;
	if(!val.compare("[")) {
		map_flags.push_back(key);
	}
}



std::unordered_map<std::string,std::string> JSONReader::getAttributes() {
	return attributes;
}

int JSONReader::parseInt(std::string val) {
	//std::cout << val << std::endl;
	return std::stoi(val);
}

std::string JSONReader::parseString(std::string val) {
	std::string trimmed = val.erase(0,1);
	trimmed = trimmed.erase(trimmed.length() -1, 1);
	return trimmed;
}

std::string JSONReader::parseFilename(std::string val) {
	std::string::size_type start = val.find_last_of("/\\") + 1;
	std::string::size_type len = val.length() - start;
	return val.substr(start, len-1);
}

double JSONReader::parseFloat(std::string val) {
	return std::stof(val);
}

bool JSONReader::parseBool(std::string val) {
	if(!val.compare("true")) return true;
	else if(!val.compare("false")) return false;
	else {
		std::cout << "NOT A BOOL" << std::endl;
		return false;
	}
}

std::vector<int> JSONReader::parseIntVec(std::string val) {
	if(val.length() == 0) {
		std::cout << "empty string!" << std::endl;
	}
	std::vector<int> ret;
	/*std::stringstream ss;

	ss << val.substr(1, val.length()-2);
	std::string temp;
	int found;
	while(!ss.eof()) {
		ss >> temp;
		if(std::stringstream(temp) >> found) {
			ret.push_back(found);
		}
		temp = "";
	}
	return ret;*/
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	std::string numeric = "1234567890";
	while(val.at(end) != ']') {
		start = val.find_first_of(numeric, end);
		end = val.find_first_not_of(numeric, start);
		int myint = parseInt(val.substr(start, end - start));
		ret.push_back(myint);
	}
	return ret;
}

std::vector<std::unordered_map<std::string, std::string>> JSONReader::parseMapVec(std::string input) {
	std::vector<std::unordered_map<std::string, std::string>> ret;

	std::vector<std::string::size_type> starts;
	std::vector<std::string::size_type> ends;
	int num_maps = 0;
	int level = 0;
	//iterate over string and count maps
	for(std::string::size_type i=0;i<input.length();i++) {
		//std::cout << val.at(i) << std::endl;
		if(isOpener(input.at(i))) {
			//std::cout << val.at(i) << std::endl;
			level++;
			if(level == 2) {
				num_maps++;
				starts.push_back(i);
			}
		}
		else if(isCloser(input.at(i))) {
			//std::cout << val.at(i) << std::endl;
			if(level == 2) {
				ends.push_back(i);	
				//std::cout << ":" << i << std::endl;
			}
			level--;
		}
	}

	//now go through each map and get the string representing the key and value
	
	for(int i=0;i<starts.size();i++) {
		level = 0;
		std::vector<std::string::size_type> atts;
		std::string map_string = input.substr(starts[i], ends[i] - starts[i] + 1);
		//gotta iterate some more
		for(std::string::size_type i = 0;i < map_string.length();i++) {
			if(isOpener(map_string.at(i))) {
				level++;
			}
			else if(isCloser(map_string.at(i))) {
				level--;
			}
			else if(isColon(map_string.at(i)) && level == 1) {
				atts.push_back(i);
			}
		}
		std::unordered_map<std::string,std::string> part;
		//std::unordered_map<std::string,std::string> &part_ref = part;
		for(auto index : atts) {
			//addAttribute(i, map_string, &part);
			//get key
			std::string::size_type key_end = index - 2;
			std::string key_str = map_string.substr(0, key_end + 1);					//WRONG
			std::string::size_type key_start = key_str.find_last_of("\"") + 1;
			

			std::string key = key_str.substr(key_start, key_end - key_start + 1);

			//get val

			std::string val;
			std::string::size_type val_start = index +1;
			std::string::size_type val_end;


			if(map_string.at(val_start) == '\"') {
				val_end = map_string.find("\"", val_start + 1);
			}
			else if(map_string.at(val_start) == '[') {
				int level = 0;
				for(std::string::size_type i=val_start;i<map_string.length();i++) {
					if(isOpener(map_string.at(i))) {
						level++;
					}
					else if(isCloser(map_string.at(i))) {
						level--;
						if(level == 0) {

							val_end = i;
							break;
						}
					}
				}
			}
			else {
				val_end = map_string.find_first_of(", ", val_start);
			}
			val = map_string.substr(val_start, val_end - val_start + 1);
			if(!val.substr(val.length() -2, 1).compare(",")) {
				val.erase(val.length() -2, 1);
			}
			//std::cout << key << std::endl;
			//std::cout << val << std::endl;
			part[key] = val;
		}
		ret.push_back(part);
	}
	return ret;
}


bool JSONReader::isOpener(char c) {
	if(c == '{' || c == '[') return true;
	else return false;
}

bool JSONReader::isCloser(char c) {
	if(c == '}' || c == ']') return true;
	else return false;
}

bool JSONReader::isColon(char c) {
	if(c == ':') return true;
	else return false;
}