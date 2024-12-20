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

        virtual void visit(std::shared_ptr<Computer>& computer) = 0;
    };

    struct Conditional : Instruction, std::enable_shared_from_this<Conditional> {
        bool value;

        Conditional(const Type& t, const std::string& l, const bool& b) : Instruction{ t, l }, value(b) {}

        void print() const override;
        void visit(std::shared_ptr<Computer>& computer) override;
    };

    struct Binary : Instruction, std::enable_shared_from_this<Binary> {
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

