#include "ServiceCenter.hpp"
#include <algorithm>
#include <cctype>
#include "Errors.hpp"

namespace {
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}
}  // namespace

// учебное правило: в имени есть "broken" (регистр не важен), значит отказ
void ServiceCenter::inspect(const Transport& t) {
    if (toLower(t.name()).find("broken") != std::string::npos) {
        rejected_.add(t.inventoryId() + " " + t.name());
        throw InspectionRejected();
    }
}
