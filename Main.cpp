#include <iostream>

#include "Application.hpp"

int main()
try
{
    Application app{};

    app.run();

    return EXIT_SUCCESS;
}
catch (const std::exception &e)
{
    std::cerr << e.what();
}