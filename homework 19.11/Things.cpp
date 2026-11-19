#include "Things.hpp"
#include <utility>
#include "Errors.hpp"
#include "Registry.hpp"  // formatValue

Thing::Thing(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {
    requireText(id_, "id");
    requireText(name_, "name");
}

std::string Helmet::describe() const {
    return "helmet " + inventoryId() + " " + name();
}

DockStation::DockStation(std::string id, std::string name, double energy)
    : Thing(std::move(id), std::move(name)), energy_(energy) {
    requireEnergy(energy_);
}

std::string DockStation::describe() const {
    return "dock " + inventoryId() + " " + name() + ", " + formatValue(energy_) + " kWh/day";
}
