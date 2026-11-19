#pragma once
#include <string>
#include "Inventory.hpp"

class Transport : public InventoryItem {
public:
    static constexpr int kNoviceMin = 6;

    Transport(std::string id, std::string name, int score);

    const std::string& inventoryId() const override { return id_; }
    const std::string& name() const override { return name_; }
    bool suitableForNovice() const override { return score_ >= kNoviceMin; }
    std::string describe() const override;

    virtual std::string kind() const = 0;

private:
    std::string id_;
    std::string name_;
    int score_;
};

class Bike : public Transport {
public:
    using Transport::Transport;
    std::string kind() const override { return "bike"; }
};

class ElectricTransport : public Transport, public EnergyConsumer {
public:
    ElectricTransport(std::string id, std::string name, double energy, int score);

    double dailyEnergy() const override { return energy_; }
    const EnergyConsumer* energyConsumer() const override { return this; }
    std::string describe() const override;

private:
    double energy_;
};

class ElectricScooter : public ElectricTransport {
public:
    using ElectricTransport::ElectricTransport;
    std::string kind() const override { return "scooter"; }
};

class ElectricBike : public ElectricTransport {
public:
    using ElectricTransport::ElectricTransport;
    std::string kind() const override { return "ebike"; }
};

class ElectricSkate : public ElectricTransport {
public:
    using ElectricTransport::ElectricTransport;
    std::string kind() const override { return "skate"; }
};
