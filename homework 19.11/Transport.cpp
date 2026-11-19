#include "Transport.hpp"
#include <utility>
#include "Errors.hpp"
#include "Registry.hpp"

Transport::Transport(std::string id, std::string name, int score)
    : id_(std::move(id)), name_(std::move(name)), score_(score) {
    requireText(id_, "id");
    requireText(name_, "name");
    if (score_ < 1 || score_ > 10) {
        throw CommandError("score must be in 1..10");
    }
}

std::string Transport::describe() const {
    return kind() + " " + id_ + " " + name_ + ", novice score " + std::to_string(score_);
}

ElectricTransport::ElectricTransport(std::string id, std::string name, double energy, int score)
    : Transport(std::move(id), std::move(name), score), energy_(energy) {
    requireEnergy(energy_);
}

std::string ElectricTransport::describe() const {
    return Transport::describe() + ", " + formatValue(energy_) + " kWh/day";
}

