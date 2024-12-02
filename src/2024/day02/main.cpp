// STL includes
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

// custom includes 


// input file
const std::string INPUT_FILE{ "input.txt" };
const std::string TEST_FILE{ "test.txt" };

// forward declarations

std::vector<std::vector<int>> parse_reports(std::ifstream& file);

bool is_safe(const std::vector<int>& report);

int count_safe(const std::vector<std::vector<int>>& reports);

int main()
{
    std::ifstream file{ INPUT_FILE };
    
    std::vector<std::vector<int>> reports{ parse_reports(file) };

    int part_1 = count_safe(reports);

    std::cout << part_1 << '\n';
}


std::vector<std::vector<int>> parse_reports(std::ifstream& file) {
    std::vector<std::vector<int>> reports;
    
    std::vector<int> report;

    file >> std::noskipws;
    
    char c;
    int level{};

    while (file >> c) {
        if (c == ' ') {
            report.push_back(level);
            level = 0;
            continue;
        }

        if (c == '\n') {
            report.push_back(level);
            level = 0;
            reports.push_back(report);
            report.clear();
            continue;
        }

        level *= 10;
        level += c - '0';
    }

    return reports;
}


bool is_safe(const std::vector<int>& report) {
    // sliding window to compute the differences
    std::vector<int>::const_iterator left = report.begin();
    std::vector<int>::const_iterator right = report.begin() + 1;

    int diff{ *right - *left };
    bool positive{ diff > 0 };

    while (right != report.end()){
        diff = *right - *left;
        
        if (abs(diff) > 3 || abs(diff) < 1) {
            return false;
        }

        if (positive && diff < 0) {
            return false;
        }

        ++right;
        ++left;
    }

    return true;
}


int count_safe(const std::vector<std::vector<int>>& reports) {
    return std::count_if(reports.begin(), reports.end(), is_safe);
}

