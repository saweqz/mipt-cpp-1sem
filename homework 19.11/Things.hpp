#pragma once
#include <string>
#include "Inventory.hpp"

// Вещь на балансе: хранит id и имя, describe() оставляет наследникам
class Thing : public InventoryItem {
public:
    Thing(std::string id, std::string name);

    const std::string& inventoryId() const override { return id_; }
    const std::string& name() const override { return name_; }

private:
    std::string id_;
    std::string name_;
};

// шлем: без энергии и без "новичка"
class Helmet : public Thing {
public:
    using Thing::Thing;
    std::string describe() const override;
};

// док-станция: вещь, которая потребляет энергию (тоже множественное наследование)
class DockStation : public Thing, public EnergyConsumer {
public:
    DockStation(std::string id, std::string name, double energy);

    double dailyEnergy() const override { return energy_; }
    const EnergyConsumer* energyConsumer() const override { return this; }
    std::string describe() const override;

private:
    double energy_;
};
