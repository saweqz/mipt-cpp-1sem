# ФизКат — консольный учёт парка

ДЗ-2 по программированию на C++.

## Сборка и запуск

```sh
cmake -S . -B build
cmake --build build --config Release
```

В Windows с MinGW укажи генератор при настройке: `cmake -S . -B build -G "MinGW Makefiles"`.

Для запуска из этой папки используй команду своей системы.

- Linux, macOS: `./build/fleet`
- Windows с Visual Studio: `.\build\Release\fleet.exe`
- Windows с MinGW Makefiles: `.\build\fleet.exe`

Сборка напрямую через GCC:

```sh
g++ -std=c++17 -Wall -Wextra main.cpp Inventory.cpp Transport.cpp Things.cpp ServiceCenter.cpp Fleet.cpp -o fleet
```

## Файлы

- `Errors.hpp`: исключения и проверка пустых строк.
- [Inventory.hpp](Inventory.hpp) и [Inventory.cpp](Inventory.cpp) содержат абстрактные базы `InventoryItem` и `EnergyConsumer`, а также `operator<<` и `operator<`.
- [Transport.hpp](Transport.hpp) и [Transport.cpp](Transport.cpp) содержат классы транспорта.
- `Things.hpp/.cpp`: вещи (`Helmet`, `DockStation`).
- `ServiceCenter.hpp/.cpp`: техосмотр и журнал отказов.
- `Registry.hpp`: шаблоны.
- `Fleet.hpp/.cpp`: парк и витрина.
- [main.cpp](main.cpp) разбирает команды и печатает ошибки.

## Команды

| Команда | Что делает |
|---|---|
| `add scooter id name energy score` | электросамокат (через техосмотр) |
| `add bike id name score` | велосипед, энергию не потребляет (через техосмотр) |
| `add ebike id name energy score` | электровелосипед (через техосмотр) |
| `add skate id name energy score` | креатив: электроскейт (через техосмотр) |
| `add helmet id name` | шлем |
| `add dock id name energy` | док-станция |
| `list` | все позиции по возрастанию id, формат `id name` |
| `novice` | прокат с простотой >= 6, в порядке добавления |
| `energy` | суммарная суточная энергия, один знак после запятой |
| `count` | число единиц на балансе |
| `focus id` / `show_focus` | витрина (weak_ptr) |
| `remove id` | убрать позицию из парка |
| `max_energy` | креатив: самая прожорливая позиция и её расход, или `none` |
| `info id` | подробное описание (`describe()`) |
| `rejected` | последние 5 отказов техосмотра (журнал на шаблоне) |
| `quit` | выход |

Ошибки печатаются в `main` в виде `error: <what()>` и парк не меняют.

## Схема наследования

```
EnergyConsumer (абстрактный, dailyEnergy())

InventoryItem (абстрактный: inventoryId, name, describe)
 |
 +-- Transport (абстрактный)
 |    |
 |    +-- Bike
 |    |
 |    +-- ElectricTransport : Transport, EnergyConsumer   <- множественное
 |         +-- ElectricScooter
 |         +-- ElectricBike
 |         +-- ElectricSkate   (креатив)
 |
 +-- Thing (абстрактный: хранит id и имя)
      |
      +-- Helmet
      |
      +-- DockStation : Thing, EnergyConsumer            <- множественное
```

Множественное наследование: `ElectricTransport` и `DockStation`. Ромба нет: у `EnergyConsumer` и `InventoryItem` нет общего предка, поэтому `virtual public` не понадобился.

`list`, `energy` и `novice` работают через виртуальные методы `InventoryItem` и `EnergyConsumer`. Порог для новичков задаёт `Transport::kNoviceMin`.

## Умные указатели

- `unique_ptr` владеет новой позицией до передачи в парк. В [main.cpp](main.cpp) транспорт проходит техосмотр под этим указателем. При отказе объект уничтожается при раскрутке стека.
- `shared_ptr` хранит принятую позицию в `vector<shared_ptr<InventoryItem>>` в [Fleet.hpp](Fleet.hpp). `Fleet::add` передаёт владение из `unique_ptr` после проверки id.
- `weak_ptr` хранит ссылку на выбранную позицию в `Fleet::focus_`. `show_focus` получает временный доступ к позиции через `lock()`. До установки фокуса команда печатает `expired`, после удаления выбранной позиции — `removed`.

## Исключения

Иерархия в `Errors.hpp`: `FleetError : std::exception`, от него два конкретных типа.

- `InspectionRejected` (`what()` = `inspection rejected`) бросает `ServiceCenter::inspect`, когда в имени есть `broken` (регистр не важен). Это учебное правило из задания.
- `CommandError` бросается при неизвестной команде, нехватке или лишних аргументах, простоте вне 1..10, пустом id или имени, отрицательной энергии, дубликате id, несуществующем id в `focus`/`remove`/`info`.

Разбор команды и операции с парком сигнализируют об ошибках через `throw`. Печать `error: ...` выполняется в `catch` в `main`.

Парк не портится: объект сначала полностью создаётся и проверяется в конструкторе, потом проходит техосмотр, и только после этого `Fleet::add` (проверка дубликата, потом `push_back`). Исключение до `push_back` ничего не меняет. Журнал отказов лежит в `ServiceCenter`, а не в парке.

## Шаблоны (`Registry.hpp`)

- `template<typename T, int Cap> class Registry` это журнал не больше `Cap` записей (`add`, `size`, `operator[]`, `operator<<`). При переполнении вытесняется самая старая запись. Используется в `ServiceCenter`: `Registry<std::string, 5>` хранит последние отказы, смотреть командой `rejected`.
- `template<typename T> std::string formatValue(const T&)` печатает значение. Для `double` есть явная специализация с одним знаком после запятой. Её использует команда `energy` (и `max_energy`).
- `sumEnergy(container)` суммирует расход, `filterItems(container, pred)` выбирает подходящие позиции. `Fleet::totalEnergy` и `Fleet::noviceItems` передают им контейнер парка.

## Перегрузка операторов

- `operator<<(ostream&, const InventoryItem&)` печатает `id name`.
- `operator<(const InventoryItem&, const InventoryItem&)` сравнивает по инвентарному номеру. Его использует `std::sort` в `Fleet::sortedItems`.
- `EnergyTotal::operator+=` добавляет расход потребителя при подсчёте суммарной энергии в [Registry.hpp](Registry.hpp).
- В `Registry` ещё есть `operator[]` и `operator<<`.

## Креативная часть

- Новый вид транспорта: электроскейт, класс `ElectricSkate` и команда `add skate id name energy score`.
- `max_energy` показывает позицию с наибольшим суточным расходом. `Fleet::maxEnergyItem` получает расход через интерфейс `EnergyConsumer`.
- Команды `count`, `info` и `rejected` добавлены для полноты отчёта и проверки.

## Тесты

Пример из задания (вход и ожидаемый вывод):

```
add scooter S-1 ModelX 2.5 8
add bike B-1 City 4
add scooter S-2 brokenX 1.0 9
add helmet H-1 Pro
add dock D-1 Hub 10.0
list
novice
energy
quit
```

```
error: inspection rejected
B-1 City
D-1 Hub
H-1 Pro
S-1 ModelX
S-1 ModelX
12.5
```

Витрина и ошибки:

```
add scooter S-1 ModelX 2.5 8
focus S-1
show_focus
remove S-1
show_focus
add scooter S-1 Again 1.0 3
add helmet H-1 Pro
add helmet H-1 Pro2
add scooter S-9 X 1.0 11
add dock D-1 Hub -1
count
quit
```

```
S-1 ModelX
removed
error: duplicate id
error: score must be in 1..10
error: energy must be >= 0
2
```

## Использование ИИ

сперва вместе с иишкой повторили + прошли все темы, нужные для выполнения задания, после придумал архитектуру, сверился и начал писать. Во время написания кода обращался с вопросами по языку, по максимуму код писался самостоятельно. Написал README.
