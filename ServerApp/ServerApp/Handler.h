#pragma once
#include <iostream>
#include <vector>
class Handler
{
private:
	Handler() {};
	Handler(const Handler&) {};
	~Handler() {};
public:
	static std::pair<int, std::vector<std::string>> proceseaza(std::string);
	static void interpreteazaMesaj(std::pair<int, std::vector<std::string>>);
};

