/*
Create by Thomas Fallwell 3/25/2015
This serves as a controller for reading and writing
calibration parameters to a config file.
*/
#include <string>
#include "config.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include "globals.h"
#include <sstream>
using namespace std;
extern Gaze gaze;

//read from config file
bool Config::getConfig(char* path) {

	std::ifstream t(path); //path to config file
	//read in whole files as one string
	std::string config((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	//pull out values from each tag
	string tags[] = {"max_x", "min_x", "max_y", "min_y"};
	try {
		for each (string tag in tags) {

			size_t begin = config.find(tag);
			string s = config.substr(begin);
			begin = s.find_first_of("="); //first index of substring
			size_t close = s.find(";");

			if (begin++ == -1 || close == -1) {
				break;
			}
			int end = close - begin; //number of characters to get
			string setting = s.substr(begin, end); //only pull between '=' and ';'
			if (tag == "max_x")
				::gaze.MAX_X = std::stoi(setting);
			else if (tag == "min_x")
				::gaze.MIN_X = std::stoi(setting);
			else if (tag == "max_y")
				::gaze.MAX_Y = std::stoi(setting);
			else if (tag == "min_y")
				::gaze.MIN_Y = std::stoi(setting);

		}
	}
	catch (exception e) {
		writeToFile(path, "max_x=-1;min_x = -1;max_y = -1;min_y = -1;");
		return false;
	}

	if (::gaze.MAX_X < 0 || ::gaze.MIN_X < 0 || ::gaze.MAX_Y < 0 || ::gaze.MIN_Y < 0) {
		writeToFile(path, "max_x=-1;min_x = -1;max_y = -1;min_y = -1;");
		return false;
	}

	return true;
}

bool Config::writeToFile(char* path, string stream) {

	try {
		ofstream myfile;
		myfile.open(path, std::ios::trunc);
		myfile << stream;
		myfile.close();
	}
	catch (exception e) {
		return false;
	}
	return true;
}
//write to config file
bool Config::setConfig(char* path) {

	std::stringstream str;
	str << "max_x=" << ::gaze.MAX_X << ";\nmin_x=" << ::gaze.MIN_X
		<< ";\nmax_y=" << ::gaze.MAX_Y << ";\nmin_y=" << ::gaze.MIN_Y << ";";
	string stream = str.str();

	if (writeToFile(path, stream))
		return true;

	return false;
}