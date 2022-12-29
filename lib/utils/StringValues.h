#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class string_values {
private:
    bool one_value_; // true - one value, false - more than one value
    bool positional_;
    bool store_value_;
    bool default_;
    bool used_;
    std::string full_argument_;
    std::string short_argument_;
    std::string description_;
    std::vector<std::string> value_;
    std::vector<std::string>* value_ptr_;
    std::string value_str_;
    std::string* value_str_ptr_;

    size_t min_args_count_;
    bool multi_value_full_;
public:

    explicit string_values(const std::string& pc, const std::string& ps = "");

    string_values(char& pc, const std::string& ps, const std::string& description = "");

    [[nodiscard]] bool isPositional() const;

    [[nodiscard]] bool isUsed() const;

    [[nodiscard]] bool isMultiValueFull() const;

    [[nodiscard]] std::pair<std::string, std::string> get_arguments() const;

    [[nodiscard]] std::string argumentName() const;

    [[nodiscard]] std::string get_value(size_t ind = -1) const;

    void add(const std::string& x);

    string_values& MultiValue(size_t i);

    string_values& MultiValue();

    string_values& StoreValue(std::string& variable);

    string_values& StoreValues(std::vector<std::string>& variable);

    string_values& Positional();

    string_values& Default(const std::string& value);

};
