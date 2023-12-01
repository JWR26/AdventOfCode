#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace parser {
	
	std::vector<std::string> get_lines(const std::string& file_path);

	std::string read_to_string(const std::string& file_path);
}


