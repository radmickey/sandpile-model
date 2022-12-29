#pragma once
#include "utils/IntValues.h"
#include "utils/StringValues.h"
#include "utils/BoolValues.h"

#include <string>
#include <variant>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace ArgumentParser {
    class ArgParser {
    private:
        std::string name_;
        std::string description_;

        std::vector<std::variant<int_values, string_values, bool_values>> args;

    public:
        ArgParser();

        explicit ArgParser(const std::string& name, const std::string& description = "");

        string_values& AddStringArgument(const std::string& arg_s);

        string_values& AddStringArgument(char arg_c, const std::string& arg_s, const std::string& description = "");

        [[nodiscard]] std::string GetStringValue(const std::string& ps) const;

        int_values& AddIntArgument(char arg_c, const std::string& arg_s, const std::string& description = "");

        int_values& AddIntArgument(const std::string& arg_s, const std::string& description = "");

        [[nodiscard]] int GetIntValue(const std::string& ps, size_t ind = -1) const;

        bool_values& AddFlag(char arg, const std::string& full_arg, const std::string& description = "");

        bool_values& AddFlag(const std::string& arg, const std::string& full_arg, const std::string& description = "");

        [[nodiscard]] bool GetFlag(const std::string& ps) const;

        bool Parse(int argc, char** argv);

        bool Parse(const std::vector<std::string>& arr);
    };
}
