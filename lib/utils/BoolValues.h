#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class bool_values {
private:
    bool value_;
    bool storeValue_;
    bool default_;
    bool used_;
    bool* value_ptr_;
    std::string full_argument_;
    std::string short_argument_;
    std::string description_;
public:

    bool_values(char arg_1, const std::string& arg_2, const std::string& description = "");

    bool_values(const std::string& arg_1, const std::string& arg_2, const std::string& description = "");

    [[nodiscard]] std::pair<std::string, std::string> get_arguments() const;

    [[nodiscard]] bool get_value() const;

    [[nodiscard]] std::string argumentName() const;

    [[nodiscard]] bool isUsed() const;

    void add(bool x);

    bool_values& StoreValue(bool& ptr);

    bool_values& Default(bool v);
};
