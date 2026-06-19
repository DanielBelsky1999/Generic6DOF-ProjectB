#include "Logger.h"

Logger::Logger(fs_path& filename)
{
	_file.open(filename);
}

Logger::~Logger()
{
	_file.close();
}

void Logger::Subsribe(double* logable, int num_of_states, const std::string& header)
{
	if (_header == "")
		_header += header;
	else
		_header += ("," + header);
	_logable_states.emplace_back(logable, num_of_states);
}

void Logger::FinilizeInit()
{
	_file << _header << "\n";
}

void Logger::Step()
{
	std::string row = "";
	bool first = true;
	for (auto it : _logable_states) {
		if (!first)
			row += ",";
		first = false;
		double* temp_state = std::get<0>(it);
		for (int i = 0; i < std::get<1>(it); i++) {	
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(10) << temp_state[i];
			row += oss.str();
			if (i + 1 != std::get<1>(it))
				row += ",";
		}
	}
	_file << row << "\n";
}
