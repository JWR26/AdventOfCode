#include "computer.h"

namespace computer {

    void Conditional::print() const {
        std::cout << lexeme << '\n';
    }

    void Conditional::visit(std::shared_ptr<Computer>& computer) const {
        computer->visit_conditional(std::make_shared<Conditional>(this));
    }

    void Binary::print() const {
        std::cout << lexeme << '\n';
    }
    
    void Binary::visit(std::shared_ptr<Computer>& computer) const {
        computer->visit_binary(std::make_shared<Binary>(this));
    }

    void Computer::visit_binary(const std::shared_ptr<Binary>& binary) {
        if (enabled) {
            binary->op(binary->left, binary->right);
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
                instructions.emplace_back(std::make_shared<Conditional>(true, instruction_type, lexeme));
                break;
            }
            case Type::DONT:
            {
                instructions.emplace_back(std::make_shared<Conditional>(false, instruction_type, lexeme));
                break;
            }
            case Type::MULTIPLY:
            {
                instructions.emplace_back(std::make_shared<Binary>(std::multiplies<int>(), std::stoi(sm[1].str()), std::stoi(sm[2].str()), instruction_type, lexeme));
                break;
            }
            default:
                break;
            }

            start = sm[0].second;
        }

        return instructions;
    }

}


