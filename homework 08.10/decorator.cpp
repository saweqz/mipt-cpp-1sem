#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <string>

std::function<std::string(std::string)> add_prefix(
    std::function<std::string(std::string)> format, std::string prefix)
{
    return [format, prefix](std::string text)
    {
        return prefix + format(text);
    };
}

std::function<std::string(std::string)> add_suffix(
    std::function<std::string(std::string)> format, std::string suffix)
{
    return [format, suffix](std::string text)
    {
        return format(text) + suffix;
    };
}

std::function<std::string(std::string)> to_upper(
    std::function<std::string(std::string)> format)
{
    return [format](std::string text)
    {
        std::string result = format(text);
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    };
}

int main()
{
    std::function<std::string(std::string)> format = [](std::string text)
    {
        return text;
    };

    format = add_prefix(format, "Hello, ");
    format = to_upper(format);
    format = add_suffix(format, "!");

    std::cout << format("anna") << '\n';

    return 0;
}