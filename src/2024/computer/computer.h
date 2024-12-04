#ifndef COMPUTER
#define COMPUTER

#include <functional>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>


namespace computer {

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

        virtual void visit(std::shared_ptr<Computer>& computer) const = 0;
    };

    struct Conditional : Instruction {
        bool value;

        Conditional(const bool& b, const Type& t, const std::string& l) : value(b), Instruction(t, l) {}

        void print() const override;
        void visit(std::shared_ptr<Computer>& computer) const override;
    };

    struct Binary : Instruction {
        std::function<int(int, int)> op;
        int left;
        int right;

        explicit Binary(const std::function<int(int, int)>& _op, const int& _left, const int& _right, const Type& t, const std::string& l) : op(_op), left(_left), right(_right) , Instruction(t, l) {}

        void print() const override;
        void visit(std::shared_ptr<Computer>& computer) const override;
    };

    struct Computer {
        bool enabled{ true };
        int sum{ 0 };

        Computer() {}

        Computer(const bool& b, const int& i) : enabled(b), sum(i) {}

        void visit_binary(const std::shared_ptr<Binary>& binary);
        void visit_conditional(const std::shared_ptr<Conditional>& conditional);
    };

    using Instruction_ptr = std::shared_ptr<Instruction>;
    using Instructions = std::vector<std::shared_ptr<Instruction>>;
    using Computer_ptr = std::shared_ptr<Computer>;

    Type get_type(const std::string& string);

    Instructions parse(const std::string& str);
}

#endif // !COMPUTER

