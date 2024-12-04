#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <functional>
#include <regex>
#include <vector>

// custom includes 
//#include "computer.h"

// input file
const std::string INPUT_FILE{ "input.txt" };
const std::string TEST_FILE{ "test.txt" };


// forward declarations
std::string get_file_as_string(const std::ifstream& file);


const std::regex PATTERN{ "do\\(\\)|don't\\(\\)|mul\\((\\d*),(\\d*)\\)" };

enum Type {
    DO,
    DONT,
    MULTIPLY,
};

struct Computer;

struct Instruction {
    Type type{};
    std::string lexeme{};

    Instruction(const Type& t, const std::string& l) : type(t), lexeme(l) {}

    virtual void print() const = 0;

    virtual void visit(std::shared_ptr<Computer>& computer) = 0;
};

struct Conditional : Instruction, std::enable_shared_from_this<Conditional> {
    bool value;

    Conditional(const Type& t, const std::string& l, const bool& b) : Instruction{ t, l }, value(b) {}

    void print() const override;
    void visit(std::shared_ptr<Computer>& computer) override;
};

struct Binary : Instruction, std::enable_shared_from_this<Binary>{
    std::function<int(int, int)> op;
    int left;
    int right;

    Binary(const Type& t, const std::string& l, const std::function<int(int, int)>& _op, const int& _left, const int& _right) : Instruction{ t, l }, op(_op), left(_left), right(_right) {}

    void print() const override;
    void visit(std::shared_ptr<Computer>& computer) override;
};

struct Computer {
    bool enabled{ true };
    int sum{ 0 };

    void visit_binary(const std::shared_ptr<Binary>& binary);
    void visit_conditional(const std::shared_ptr<Conditional>& conditional);
};

using Instruction_ptr = std::shared_ptr<Instruction>;
using Instructions = std::vector<std::shared_ptr<Instruction>>;
using Computer_ptr = std::shared_ptr<Computer>;

Type get_type(const std::string& string);

Instructions parse(const std::string& str);

int sum_multiples(const Instructions& instructions);

int handle_instructions(const Instructions& instructions);


int main()
{
    std::ifstream file{ INPUT_FILE };

    std::string programme{ get_file_as_string(file) };

    Instructions instructions = parse(programme);

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


int sum_multiples(const Instructions& instructions) {
    std::shared_ptr<Computer> computer = std::make_shared<Computer>();

    for (const Instruction_ptr& i : instructions) {
        if (i->type == Type::MULTIPLY) {
            i->visit(computer);
        }       
    }

    return computer->sum;
}


int handle_instructions(const Instructions& instructions) {
    Computer_ptr computer = std::make_shared<Computer>();

    for (const Instruction_ptr& i : instructions) {
        i->visit(computer);
    }

    return computer->sum;
}

void Conditional::print() const {
    std::cout << lexeme << '\n';
}

void Conditional::visit(std::shared_ptr<Computer>& computer) {
    computer->visit_conditional(shared_from_this());
}

void Binary::print() const {
    std::cout << lexeme << '\n';
}

void Binary::visit(std::shared_ptr<Computer>& computer) {
    computer->visit_binary(shared_from_this());
}

void Computer::visit_binary(const std::shared_ptr<Binary>& binary) {
    if (enabled) {
        sum += binary->op(binary->left, binary->right);
    }
}

void Computer::visit_conditional(const std::shared_ptr<Conditional>& conditional) {
    enabled = conditional->value;
}

Type get_type(const std::string& string) {
    if (string == "do()") {
        return Type::DO;
    }
    if (string == "don't()") {
        return Type::DONT;
    }

    return Type::MULTIPLY;
}

Instructions parse(const std::string& str) {
    Instructions instructions;

    std::string::const_iterator start{ str.begin() };
    std::smatch sm;

    while (std::regex_search(start, str.end(), sm, PATTERN)) {
        std::string lexeme{ sm.str() };
        Type instruction_type{ get_type(lexeme) };

        switch (instruction_type)
        {
        case Type::DO:
        {
            instructions.emplace_back(std::make_shared<Conditional>(instruction_type, lexeme, true));
            break;
        }
        case Type::DONT:
        {
            instructions.emplace_back(std::make_shared<Conditional>(instruction_type, lexeme, false));
            break;
        }
        case Type::MULTIPLY:
        {
            instructions.emplace_back(std::make_shared<Binary>(instruction_type, lexeme, std::multiplies<int>(), std::stoi(sm[1].str()), std::stoi(sm[2].str())));
            break;
        }
        default:
            break;
        }

        start = sm[0].second;
    }

    return instructions;
}
