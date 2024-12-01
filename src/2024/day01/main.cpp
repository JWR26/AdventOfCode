// STL includes
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

// custom includes 


// input file
const std::string INPUT_FILE{ "input.txt" };
const std::string TEST_FILE{ "test.txt" };

// forward declarations
std::pair<std::vector<int>, std::vector<int>> parse_lists(std::ifstream& file);

int main()
{
    // read file to pair of lists
    std::ifstream file{ INPUT_FILE };
    auto [list_one, list_two] = parse_lists(file);

    // sort lists ascending
    std::sort(list_one.begin(), list_one.end());
    std::sort(list_two.begin(), list_two.end());

    // calculate the differences    
    auto abs_diff = [](const int& a, const int& b) -> int {
        return abs(a -b);
        };

    std::vector<int> differences(list_one);

    std::transform(differences.begin(), differences.end(), list_two.begin(), differences.begin(), abs_diff);

    // accumulate the difference
    int sum = std::accumulate(differences.begin(), differences.end(), 0);
    
    std::cout << sum << '\n';

    std::vector<int> similarity(list_one);

    auto increase = [&list_two](int& i) -> void {
        i *= std::count(list_two.begin(), list_two.end(), i);
        };

    std::for_each(similarity.begin(), similarity.end(), increase);

    int score = std::accumulate(similarity.begin(), similarity.end(), 0);

    std::cout << score;
}

std::pair<std::vector<int>, std::vector<int>> parse_lists(std::ifstream& file) {
    std::pair<std::vector<int>, std::vector<int>> lists;

    file >> std::noskipws;

    char c;
    int number{0};

    while (file >> c) {
        if (c == ' ') {
            if (number == 0) {
                continue;
            }
            lists.first.push_back(number);
            number = 0;
            continue;
        }
        if (c == '\n') {
            lists.second.push_back(number);
            number = 0;
            continue;
        }

        number *= 10;
        number += c - '0';
    }

    return lists;
}