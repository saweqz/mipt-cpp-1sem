#pragma once
#include <string>
#include "Registry.hpp"
#include "Transport.hpp"

class ServiceCenter {
public:
    static constexpr int kJournalSize = 5;

    // Если техника не прошла осмотр, бросает InspectionRejected.
    // Парк эта функция вообще не трогает.
    void inspect(const Transport& t);

    const Registry<std::string, kJournalSize>& rejectedLog() const { return rejected_; }

private:
    Registry<std::string, kJournalSize> rejected_;  // последние отказы
};
