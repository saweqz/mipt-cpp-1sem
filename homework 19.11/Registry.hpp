#pragma once
#include <cstddef>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Inventory.hpp"

template <typename T>
std::string formatValue(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

template <>
inline std::string formatValue<double>(const double& value) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << value;
    return os.str();
}

// При переполнении журнала вытесняется самая старая запись.
template <typename T, int Cap>
class Registry {
    static_assert(Cap > 0, "Cap must be positive");

public:
    void add(const T& value) {
        items_.push_back(value);
        if (items_.size() > static_cast<std::size_t>(Cap)) {
            items_.erase(items_.begin());
        }
    }

    std::size_t size() const { return items_.size(); }

    const T& operator[](std::size_t i) const {
        if (i >= items_.size()) {
            throw std::out_of_range("Registry index out of range");
        }
        return items_[i];
    }

    friend std::ostream& operator<<(std::ostream& os, const Registry& r) {
        for (const T& x : r.items_) {
            os << formatValue(x) << '\n';
        }
        return os;
    }

private:
    std::vector<T> items_;
};

class EnergyTotal {
public:
    EnergyTotal& operator+=(const EnergyConsumer& consumer) {
        value_ += consumer.dailyEnergy();
        return *this;
    }

    double value() const { return value_; }

private:
    double value_ = 0.0;
};

template <typename Container>
double sumEnergy(const Container& items) {
    EnergyTotal total;
    for (const auto& p : items) {
        if (const EnergyConsumer* c = p->energyConsumer()) {
            total += *c;
        }
    }
    return total.value();
}

template <typename Container, typename Pred>
std::vector<const InventoryItem*> filterItems(const Container& items, Pred pred) {
    std::vector<const InventoryItem*> result;
    for (const auto& p : items) {
        if (pred(*p)) {
            result.push_back(p.get());
        }
    }
    return result;
}
