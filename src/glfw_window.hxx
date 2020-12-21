#ifndef GLFW_WINDOW_HXX
#define GLFW_WINDOW_HXX

#include "types.hxx"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class glfw_window {

public:
    glfw_window();
    ~glfw_window();

    void close();
    bool should_close();
    void poll_events();

    GLFWwindow *window;

    u32 width;                  /* read-only */
    u32 height;                 /* read-only */
    u32 num_extensions;         /* read-only */
    const char **extensions;    /* read-only */

private:
    static u32  num_windows;
    static bool initialized;
};

#endif
