#include "BoolValues.h"

bool_values::bool_values(char arg_1, const std::string& arg_2, const std::string& description) {
    short_argument_ = arg_1;
    full_argument_ = arg_2;
    this->description_ = description;

    value_ = false;
    value_ptr_ = nullptr;
    storeValue_ = false;
    default_ = false;
    used_ = false;
}

bool_values::bool_values(const std::string& arg_1, const std::string& arg_2, const std::string& description) {
    short_argument_ = arg_1;
    full_argument_ = arg_2;
    this->description_ = description;

    value_ = false;
    value_ptr_ = nullptr;
    storeValue_ = false;
    default_ = false;
    used_ = false;
}

std::pair<std::string, std::string> bool_values::get_arguments() const {
    return {full_argument_, short_argument_};
}

std::string bool_values::argumentName() const {
    return full_argument_.empty() ? short_argument_ : full_argument_;
}

bool bool_values::get_value() const {
    if (!used_) {
        throw std::invalid_argument("There's no value in value_ : " + argumentName());
    }

    return value_;
}

bool bool_values::isUsed() const {
    return used_;
}

void bool_values::add(bool x) {
    if (used_ && !default_) {
        throw std::logic_error("Flag : " + argumentName() + " has already had a value");
    }

    if (storeValue_ && value_ptr_ == nullptr) {
        throw std::invalid_argument("There's no initialized variable for StoreValue");
    }

    if (storeValue_) {
        *value_ptr_ = x;
    } else {
        value_ = x;
    }
    used_ = true;
}

bool_values& bool_values::StoreValue(bool& ptr) {
    value_ptr_ = &ptr;
    storeValue_ = true;
    return *this;
}

bool_values& bool_values::Default(bool v) {
    if (storeValue_ && value_ptr_ == nullptr) {
        throw std::invalid_argument("There's no pointer to the variable in the value_ : " + argumentName());
    }

    if (storeValue_) {
        *value_ptr_ = v;
        default_ = true;
        used_ = true;
    } else {
        value_ = v;
        default_ = true;
        used_ = true;
    }

    return *this;
}
