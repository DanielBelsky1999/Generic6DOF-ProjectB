#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>



class Logger
{
public:
	using fs_path = std::filesystem::path;
	Logger(fs_path& filename);
	~Logger();

	void Subsribe(double* logable, int num_of_states, const std::string& header);
	void FinilizeInit();
	void Step();

private:
	std::string _header = "";
	std::vector<std::tuple<double*, int>> _logable_states;
	std::ofstream _file;
};

