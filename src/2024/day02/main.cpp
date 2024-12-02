// STL includes
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// custom includes 


// input file
const std::string INPUT_FILE{ "input.txt" };
const std::string TEST_FILE{ "test.txt" };

// forward declarations
std::vector<std::vector<int>> parse_reports(std::ifstream& file);
std::vector<int>::const_iterator find_error_level(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last);
bool is_safe(const std::vector<int>& report);
int count_safe(const std::vector<std::vector<int>>& reports);
bool apply_problem_dampener(const std::vector<int>& report);
int count_tolerated_safe(const std::vector<std::vector<int>>& reports);

int main()
{
    std::ifstream file{ INPUT_FILE };
    
    std::vector<std::vector<int>> reports{ parse_reports(file) };

    int part_1 = count_safe(reports);

    std::cout << part_1 << '\n';

    int part_2 = count_tolerated_safe(reports);

    std::cout << part_2;
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

std::vector<int>::const_iterator find_error_level(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last) {
    std::vector<int>::const_iterator next = first + 1;

    int diff{ *next - *first };
    bool positive{ diff > 0 };

    while (next != last) {
        diff = *next - *first;

        if (abs(diff) > 3 || abs(diff) < 1) {
            return next;
        }

        if (positive && diff < 0) {
            return next;
        }

        if (!positive && diff > 0) {
            return next;
        }

        ++next;
        ++first;
    }

    return next;
}

bool is_safe(const std::vector<int>& report) {
    std::vector<int>::const_iterator error_level = find_error_level(report.begin(), report.end());

    return (error_level == report.end());
}

int count_safe(const std::vector<std::vector<int>>& reports) {
    return std::count_if(reports.begin(), reports.end(), is_safe);
}

bool apply_problem_dampener(const std::vector<int>& report) {
    std::vector<int>::const_iterator error_level = find_error_level(report.begin(), report.end());

    if (error_level == report.end()) {
        return true;
    }

    while (error_level != report.begin()){
        std::vector<int> modified(report);
        int offset = std::distance(report.begin(), error_level);
        modified.erase(modified.begin() + offset);
        if (find_error_level(modified.begin(), modified.end()) == modified.end()) {
            return true;
        }
        --error_level;
    }

    std::vector<int> modified(report);
    modified.erase(modified.begin());

    return find_error_level(modified.begin(), modified.end()) == modified.end();
}

int count_tolerated_safe(const std::vector<std::vector<int>>& reports) {
    return std::count_if(reports.begin(), reports.end(), apply_problem_dampener);
}
