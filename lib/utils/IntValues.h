#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class int_values {
private:
    bool one_value_;
    bool positional_;
    bool store_value_;
    bool default_;
    bool used_;
    bool multi_value_full_;
    std::string full_argument_;
    std::string short_argument_;
    std::string description_;
    std::vector<int64_t> value_;
    std::vector<int64_t>* value_ptr_;
    int64_t value_int_;
    int64_t* value_int_ptr_;

    size_t min_args_count_;


public:

    explicit int_values(const std::string& ps, const std::string& pf = "");

    explicit int_values(char& pc, const std::string& ps = "", const std::string& descript = "");

    [[nodiscard]] bool isPositional() const;

    [[nodiscard]] bool isUsed() const;

    [[nodiscard]] bool isMultiValueFull() const;

    [[nodiscard]] std::pair<std::string, std::string> get_arguments() const;

    [[nodiscard]] std::string argumentName() const;

    [[nodiscard]] int get_value(size_t ind = -1) const;

    void add(int x);

    int_values& MultiValue();

    int_values& MultiValue(size_t i);

    int_values& StoreValue(int64_t& variable);

    int_values& StoreValues(std::vector<int64_t>& variable);

    int_values& Positional();

    int_values& Default(int64_t value);
};
