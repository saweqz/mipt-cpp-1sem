#pragma once
#include <cmath>
#include <exception>
#include <string>
#include <utility>

// общий базис всех наших исключений
class FleetError : public std::exception {
public:
    explicit FleetError(std::string msg) : msg_(std::move(msg)) {}
    const char* what() const noexcept override { return msg_.c_str(); }

private:
    std::string msg_;
};

// техосмотр не пройден (штатная ситуация)
class InspectionRejected : public FleetError {
public:
    InspectionRejected() : FleetError("inspection rejected") {}
};

// кривая команда или кривые аргументы (в том числе валидация в конструкторах)
class CommandError : public FleetError {
public:
    explicit CommandError(const std::string& msg) : FleetError(msg) {}
};

inline void requireText(const std::string& value, const char* field) {
    if (value.empty()) {
        throw CommandError(std::string("empty ") + field);
    }
}

inline void requireEnergy(double energy) {
    if (!std::isfinite(energy) || energy < 0.0) {
        throw CommandError("energy must be >= 0");
    }
}
