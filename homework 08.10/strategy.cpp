#include <functional>
#include <iostream>

int calc_delivery_cost(int weight, std::function<int(int)> strategy)
{
    return strategy(weight);
}

int main()
{
    std::function<int(int)> pickup = [](int weight)
    {
        return 0;
    };

    std::function<int(int)> courier = [](int weight)
    {
        return weight * 30 + 150;
    };
ч
    std::function<int(int)> post = [](int weight)
    {
        return weight * 15 + 50;
    };

    int weight = 3;

    std::cout << "Самовывоз: " << calc_delivery_cost(weight, pickup) << '\n';
    std::cout << "Курьер: " << calc_delivery_cost(weight, courier) << '\n';
    std::cout << "Почта: " << calc_delivery_cost(weight, post) << '\n';

    return 0;
}