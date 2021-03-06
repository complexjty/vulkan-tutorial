#include "vk_app.hxx"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    vk_app app;

    try
    {
        app.run();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
