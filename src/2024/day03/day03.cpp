#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <functional>
#include <regex>
#include <vector>

// custom includes 
#include "computer.h"

// input file
const std::string INPUT_FILE{ "input.txt" };
const std::string TEST_FILE{ "test.txt" };


// forward declarations
std::string get_file_as_string(const std::ifstream& file);

int sum_multiples(const computer::Instructions& instructions);

int handle_instructions(const computer::Instructions& instructions);


int main()
{
    std::ifstream file{ INPUT_FILE };

    std::string programme{ get_file_as_string(file) };

    computer::Instructions instructions = computer::parse(programme);

    int part_1 = sum_multiples(instructions);

    std::cout << part_1 << '\n';

    int part_2 = handle_instructions(instructions);

    std::cout << part_2;
}


std::string get_file_as_string(const std::ifstream& file) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


int sum_multiples(const computer::Instructions& instructions) {
    computer::Computer_ptr computer = std::make_shared<computer::Computer>();

    for (const computer::Instruction_ptr& i : instructions) {
        if (i->type == computer::Type::MULTIPLY) {
            i->visit(computer);
        }       
    }

    return computer->sum;
}

int handle_instructions(const computer::Instructions& instructions) {
    computer::Computer_ptr computer = std::make_shared<computer::Computer>();

    for (const computer::Instruction_ptr& i : instructions) {
        i->visit(computer);
    }

    return computer->sum;
}
