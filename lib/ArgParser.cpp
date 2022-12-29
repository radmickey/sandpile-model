#include "ArgParser.h"


using argument = std::variant<int_values, string_values, bool_values>;

template <typename T>
bool isType(const argument& arg) {
    return std::holds_alternative<T>(arg);
}

bool isNumeric(const std::string& value) {

    if (value.empty()) {
        return true;
    } else if (value[0] == '-' || isdigit(value[0])) {
        for (int i = 1; i < value.size(); i++) {
            if (!isdigit(value[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool eqArgument(const std::string& parameter, argument& x) {
    std::pair<std::string, std::string> args;
    if (isType<int_values>(x)) {
        args = reinterpret_cast<int_values&>(x).get_arguments();
    } else if (isType<string_values>(x)) {
        args = reinterpret_cast<string_values&>(x).get_arguments();
    } else {
        args = reinterpret_cast<bool_values&>(x).get_arguments();
    }

    return parameter == args.first || parameter == args.second;
}

bool eqArgument(char parameter, argument x) {
    return eqArgument(std::string(1, parameter), x);
}

void addPositional(std::vector<argument>& args, const std::string& value) {
    static argument* arg;

    if (arg == nullptr) {
        for (argument& i: args) {
            bool flag1 = isType<int_values>(i) && reinterpret_cast<int_values&>(i).isPositional();
            bool flag2 = isType<string_values>(i) && reinterpret_cast<string_values&>(i).isPositional();
            if (flag1 || flag2) {
                arg = &i;
                break;
            }
        }

        if (arg == nullptr) {
            throw std::logic_error("No positional_ argument was given but the value : " + value);
        }

        if (isType<string_values>(*arg)) {
            reinterpret_cast<string_values&>(*arg).add(value);
        } else {
            if (!isNumeric(value)) {
                throw std::invalid_argument("The value is not an integer, but the parameter is only for integers");
            }

            reinterpret_cast<int_values&>(*arg).add(std::stoi(value));
        }

    } else {
        if (isType<string_values>(*arg)) {
            reinterpret_cast<string_values&>(*arg).add(value);
        } else {
            if (!isNumeric(value)) {
                throw std::invalid_argument("The value is not an integer, but the parameter is only for integers");
            }

            reinterpret_cast<int_values&>(*arg).add(std::stoi(value));
        }
    }
}

ArgumentParser::ArgParser::ArgParser() {
    name_ = "Parser";
}

ArgumentParser::ArgParser::ArgParser(const std::string& name, const std::string& description) {
    this->name_ = name;
    this->description_ = description;
}

string_values& ArgumentParser::ArgParser::AddStringArgument(const std::string& arg_s) {
    string_values a(arg_s);
    args.emplace_back(a);
    return reinterpret_cast<string_values&>(args.back());
}

string_values& ArgumentParser::ArgParser::AddStringArgument(char arg_c, const std::string& arg_s, const std::string& description) {
    string_values a(arg_c, arg_s, description);
    args.emplace_back(a);
    return reinterpret_cast<string_values&>(args.back());
}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& ps) const {
    for (auto x : args) {
        if (isType<string_values>(x) && eqArgument(ps, x)) {
            return reinterpret_cast<string_values&>(x).get_value();
        }
    }

    throw std::invalid_argument("No value in the argument : " + ps);
}

int_values& ArgumentParser::ArgParser::AddIntArgument(char arg_c, const std::string& arg_s, const std::string& description) {
    int_values a(arg_c, arg_s, description);
    args.emplace_back(a);

    return reinterpret_cast<int_values&>(args.back());
}

int_values& ArgumentParser::ArgParser::AddIntArgument(const std::string& arg_s, const std::string& description) {
    int_values a(arg_s, description);
    args.emplace_back(a);
    return reinterpret_cast<int_values&>(args.back());
}

int ArgumentParser::ArgParser::GetIntValue(const std::string& ps, size_t ind) const {
    for (auto x : args) {
        if (isType<int_values>(x) && eqArgument(ps, x)) {
            return reinterpret_cast<int_values&>(x).get_value(ind);
        }
    }

    throw std::invalid_argument("No value in the argument : " + ps);
}

bool_values& ArgumentParser::ArgParser::AddFlag(char arg, const std::string& full_arg, const std::string& description) {
    bool_values a(arg, full_arg, description);
    args.emplace_back(a);
    return reinterpret_cast<bool_values&>(args.back());
}

bool_values& ArgumentParser::ArgParser::AddFlag(const std::string& arg, const std::string& full_arg, const std::string& description) {
    bool_values a(arg, full_arg, description);
    args.emplace_back(a);
    return reinterpret_cast<bool_values&>(args.back());
}

bool ArgumentParser::ArgParser::GetFlag(const std::string& ps) const{
    for (std::variant<int_values, string_values, bool_values> x : args) {
        if (isType<bool_values>(x) && eqArgument(ps, x)) {
            return reinterpret_cast<bool_values&>(x).get_value();
        }
    }

    throw std::invalid_argument("The value_ " + ps + " wasn't given");
}

bool ArgumentParser::ArgParser::Parse(int argc, char** argv) {
    static std::vector<std::string> arr_tmp;
    arr_tmp.reserve(argc);
    for (int i = 0; i < argc; i++) {
        arr_tmp.emplace_back(argv[i]);
    }
    return Parse(arr_tmp);
}

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& arr) {

    for (int i = 1; i < arr.size(); i++) {
        bool isArgumentCorrect = false;
        if (arr[i][0] == '-') {
            if (arr[i][1] == '-') {
                std::string parameter = arr[i].substr(2, arr[i].find('=') - 2);

                if (arr[i].find('=') != std::string::npos){
                    std::string value = arr[i].substr(arr[i].find('=') + 1, arr[i].size() - arr[i].find('=') - 1);

                    for (auto& arg : args) {
                        if (isType<bool_values>(arg) && eqArgument(parameter, arg)) {
                            throw std::invalid_argument("Flag can't has any value, ");
                        }

                        if (isType<string_values>(arg) && eqArgument(parameter, arg)) {
                            isArgumentCorrect = true;
                            reinterpret_cast<string_values&>(arg).add(value);
                            break;

                        } else if (isType<int_values>(arg) && eqArgument(parameter, arg)) {
                            if (!isNumeric(value)) {
                                throw std::invalid_argument("The value is not an integer, but the parameter is only for integers");
                            }

                            isArgumentCorrect = true;
                            reinterpret_cast<int_values&>(arg).add(std::stoi(value));
                            break;
                        }
                    }
                } else {
                    for (auto& arg : args) {
                        if (std::holds_alternative<bool_values>(arg)) {
                            std::pair<std::string, std::string> arguments = reinterpret_cast<bool_values&>(arg).get_arguments();
                            if (arguments.first == parameter || arguments.second == parameter) {
                                reinterpret_cast<bool_values&>(arg).add(true);
                                isArgumentCorrect = true;
                                break;
                            }
                        }
                    }
                }

                if (!isArgumentCorrect) {
                    throw std::invalid_argument("No such argument was given : " + parameter);
                }

            } else {
                std::string parameter = arr[i].substr(1, arr[i].find('=') - 1);

                if (arr[i].find('=') != std::string::npos){
                    std::string value = arr[i].substr(arr[i].find_first_of('=') + 1, arr[i].size() - arr[i].find_first_of('=') - 1);

                    for (auto& arg : args) {
                        if (isType<string_values>(arg) && eqArgument(parameter, arg)) {
                            isArgumentCorrect = true;
                            reinterpret_cast<string_values&>(arg).add(value);
                            break;
                        } else if (isType<int_values>(arg) && eqArgument(parameter, arg)) {
                            if (!isNumeric(value)) {
                                throw std::invalid_argument("The value is not an integer, but the parameter is only for integers");
                            }

                            isArgumentCorrect = true;
                            reinterpret_cast<int_values&>(arg).add(std::stoi(value));
                            break;
                        }
                    }
                } else {
                    if (isNumeric(arr[i])) {
                        addPositional(args, arr[i]);
                    } else {
                        for (int j = 1; j < arr[i].size(); j++) {
                            bool correct_argument = false;
                            for (auto& arg: args) {
                                if (isType<bool_values>(arg) && eqArgument(arr[i][j], arg)) {
                                    correct_argument = true;
                                    reinterpret_cast<bool_values&>(arg).add(true);
                                    isArgumentCorrect = true;
                                    break;
                                }
                            }

                            if (!correct_argument) {
                                throw std::invalid_argument("The argument : " + std::string(1, arr[i][j]) + " was given");
                            }
                        }
                    }
                }

                if (!isArgumentCorrect) {
                    throw std::invalid_argument("No such argument was given : " + arr[i]);
                }

            }
        } else {
            addPositional(args, arr[i]);
        }
    }

    bool correct_parse = true;
    for (auto arg : args) {
        if (isType<bool_values>(arg)) {
            correct_parse &= reinterpret_cast<bool_values&>(arg).isUsed();
        } else if (isType<int_values>(arg)) {
            correct_parse &= reinterpret_cast<int_values&>(arg).isUsed();
            correct_parse &= reinterpret_cast<int_values&>(arg).isMultiValueFull();
        } else {
            correct_parse &= reinterpret_cast<string_values&>(arg).isUsed();
            correct_parse &= reinterpret_cast<string_values&>(arg).isMultiValueFull();
        }
    }
    return correct_parse;
}
