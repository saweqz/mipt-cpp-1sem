#include "Inventory.hpp"
#include <ostream>

// формат строки: "<id> <name>", как в примере из задания
std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    return os << item.inventoryId() << ' ' << item.name();
}

// порядок по инвентарному номеру (для list)
bool operator<(const InventoryItem& a, const InventoryItem& b) {
    return a.inventoryId() < b.inventoryId();
}
