#pragma once
#include <iosfwd>
#include <string>

class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;
    virtual double dailyEnergy() const = 0;  // кВт*ч в сутки
};

class InventoryItem {
public:
    virtual ~InventoryItem() = default;

    virtual const std::string& inventoryId() const = 0;
    virtual const std::string& name() const = 0;
    virtual std::string describe() const = 0;

    virtual const EnergyConsumer* energyConsumer() const { return nullptr; }
    virtual bool suitableForNovice() const { return false; }

    InventoryItem(const InventoryItem&) = delete;
    InventoryItem& operator=(const InventoryItem&) = delete;

protected:
    InventoryItem() = default;
};

std::ostream& operator<<(std::ostream& os, const InventoryItem& item);
bool operator<(const InventoryItem& a, const InventoryItem& b);
