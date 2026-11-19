#pragma once
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "Inventory.hpp"

class Fleet {
public:
    void add(std::unique_ptr<InventoryItem> item);
    void remove(const std::string& id);
    const InventoryItem& at(const std::string& id) const;

    std::size_t size() const { return items_.size(); }
    double totalEnergy() const;

    std::vector<const InventoryItem*> sortedItems() const;  // по id
    std::vector<const InventoryItem*> noviceItems() const;  // в порядке добавления
    const InventoryItem* maxEnergyItem() const;             // nullptr, если потребителей нет

    void focus(const std::string& id);
    std::string showFocus() const;

private:
    using Items = std::vector<std::shared_ptr<InventoryItem>>;
    Items::const_iterator find(const std::string& id) const;

    Items items_;
    std::weak_ptr<const InventoryItem> focus_;
    bool focusSet_ = false;
};
