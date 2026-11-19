#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include "Errors.hpp"
#include "Fleet.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"

namespace {

template <typename T>
T readArg(std::istringstream& in, const char* what) {
    std::string token;
    if (in >> token) {
        std::istringstream arg(token);
        T value{};
        if ((arg >> value) && arg.eof()) {
            return value;
        }
    }
    throw CommandError(std::string("missing or bad argument: ") + what);
}

void expectEnd(std::istringstream& in) {
    std::string extra;
    if (in >> extra) {
        throw CommandError("too many arguments");
    }
}

void addTransport(std::unique_ptr<Transport> t, Fleet& fleet, ServiceCenter& center) {
    center.inspect(*t);
    fleet.add(std::move(t));
}

template <typename T>
void addElectric(std::istringstream& in, const std::string& id, const std::string& name,
                 Fleet& fleet, ServiceCenter& center) {
    double energy = readArg<double>(in, "energy");
    int score = readArg<int>(in, "score");
    expectEnd(in);
    addTransport(std::make_unique<T>(id, name, energy, score), fleet, center);
}

void handleAdd(std::istringstream& in, Fleet& fleet, ServiceCenter& center) {
    std::string kind = readArg<std::string>(in, "kind");
    std::string id = readArg<std::string>(in, "id");
    std::string name = readArg<std::string>(in, "name");

    if (kind == "scooter") {
        addElectric<ElectricScooter>(in, id, name, fleet, center);
    } else if (kind == "ebike") {
        addElectric<ElectricBike>(in, id, name, fleet, center);
    } else if (kind == "skate") {
        addElectric<ElectricSkate>(in, id, name, fleet, center);
    } else if (kind == "bike") {
        int score = readArg<int>(in, "score");
        expectEnd(in);
        addTransport(std::make_unique<Bike>(id, name, score), fleet, center);
    } else if (kind == "helmet") {
        expectEnd(in);
        fleet.add(std::make_unique<Helmet>(id, name));
    } else if (kind == "dock") {
        double energy = readArg<double>(in, "energy");
        expectEnd(in);
        fleet.add(std::make_unique<DockStation>(id, name, energy));
    } else {
        throw CommandError("unknown item kind");
    }
}

// false значит quit
bool execute(const std::string& line, Fleet& fleet, ServiceCenter& center) {
    std::istringstream in(line);
    std::string cmd;
    if (!(in >> cmd)) {
        return true;  // пустая строка
    }

    if (cmd == "add") {
        handleAdd(in, fleet, center);
    } else if (cmd == "list") {
        expectEnd(in);
        for (const InventoryItem* p : fleet.sortedItems()) {
            std::cout << *p << '\n';
        }
    } else if (cmd == "novice") {
        expectEnd(in);
        for (const InventoryItem* p : fleet.noviceItems()) {
            std::cout << *p << '\n';
        }
    } else if (cmd == "energy") {
        expectEnd(in);
        std::cout << formatValue(fleet.totalEnergy()) << '\n';
    } else if (cmd == "count") {
        expectEnd(in);
        std::cout << fleet.size() << '\n';
    } else if (cmd == "focus") {
        std::string id = readArg<std::string>(in, "id");
        expectEnd(in);
        fleet.focus(id);
    } else if (cmd == "show_focus") {
        expectEnd(in);
        std::cout << fleet.showFocus() << '\n';
    } else if (cmd == "remove") {
        std::string id = readArg<std::string>(in, "id");
        expectEnd(in);
        fleet.remove(id);
    } else if (cmd == "info") {
        std::string id = readArg<std::string>(in, "id");
        expectEnd(in);
        std::cout << fleet.at(id).describe() << '\n';
    } else if (cmd == "max_energy") {
        expectEnd(in);
        const InventoryItem* best = fleet.maxEnergyItem();
        if (best == nullptr) {
            std::cout << "none\n";
        } else {
            std::cout << *best << ' ' << formatValue(best->energyConsumer()->dailyEnergy()) << '\n';
        }
    } else if (cmd == "rejected") {
        expectEnd(in);
        std::cout << center.rejectedLog();
    } else if (cmd == "quit") {
        expectEnd(in);
        return false;
    } else {
        throw CommandError("unknown command");
    }
    return true;
}

}  // namespace

int main() {
    Fleet fleet;
    ServiceCenter center;

    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            if (!execute(line, fleet, center)) {
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }
    return 0;
}
