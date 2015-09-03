#ifndef CONFIG_H
#define CONFIG_H
/*
Create by Thomas Fallwell 3/25/2015
For writing global calibration points
to config file.
*/
#include <string>

class Config {
public:
	static bool getConfig(char*);
	static bool setConfig(char*);
private:
	static bool writeToFile(char*, std::string);
};

#endif