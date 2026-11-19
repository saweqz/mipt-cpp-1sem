#include "Fleet.hpp"
#include <algorithm>
#include <sstream>
#include <utility>
#include "Errors.hpp"
#include "Registry.hpp"

Fleet::Items::const_iterator Fleet::find(const std::string& id) const {
    return std::find_if(items_.cbegin(), items_.cend(),
                        [&id](const auto& p) {
                            return p->inventoryId() == id;
                        });
}

void Fleet::add(std::unique_ptr<InventoryItem> item) {
    if (!item) {
        throw CommandError("empty item");
    }
    if (find(item->inventoryId()) != items_.cend()) {
        throw CommandError("duplicate id");
    }
    items_.emplace_back(std::move(item));
}

void Fleet::remove(const std::string& id) {
    auto it = find(id);
    if (it == items_.cend()) {
        throw CommandError("no such id");
    }
    items_.erase(it);
}

const InventoryItem& Fleet::at(const std::string& id) const {
    auto it = find(id);
    if (it == items_.cend()) {
        throw CommandError("no such id");
    }
    return **it;
}

double Fleet::totalEnergy() const {
    return sumEnergy(items_);
}

std::vector<const InventoryItem*> Fleet::sortedItems() const {
    std::vector<const InventoryItem*> result;
    result.reserve(items_.size());
    for (const auto& p : items_) {
        result.push_back(p.get());
    }
    std::sort(result.begin(), result.end(),
              [](const InventoryItem* a, const InventoryItem* b) { return *a < *b; });
    return result;
}

std::vector<const InventoryItem*> Fleet::noviceItems() const {
    return filterItems(items_, [](const InventoryItem& i) { return i.suitableForNovice(); });
}

const InventoryItem* Fleet::maxEnergyItem() const {
    const InventoryItem* best = nullptr;
    double bestValue = 0.0;
    for (const auto& p : items_) {
        const EnergyConsumer* c = p->energyConsumer();
        if (c != nullptr && (best == nullptr || c->dailyEnergy() > bestValue)) {
            best = p.get();
            bestValue = c->dailyEnergy();
        }
    }
    return best;
}

void Fleet::focus(const std::string& id) {
    auto it = find(id);
    if (it == items_.cend()) {
        throw CommandError("no such id");
    }
    focus_ = *it;
    focusSet_ = true;
}

std::string Fleet::showFocus() const {
    if (auto item = focus_.lock()) {
        std::ostringstream os;
        os << *item;
        return os.str();
    }
    return focusSet_ ? "removed" : "expired";
}
