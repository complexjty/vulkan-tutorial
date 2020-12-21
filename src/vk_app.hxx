#ifndef VK_APP_HXX
#define VK_APP_HXX

#include "glfw_window.hxx"
#include "vk_instance.hxx"

class vk_app {

public:
    vk_app();
    ~vk_app();

    void run();

private:
    void update();

    glfw_window *window;
    vk_instance *instance;
};

#endif
