#include "glfw_window.hxx"

#include <stdexcept>

u32  glfw_window::num_windows = 0;
bool glfw_window::initialized = false;

glfw_window::glfw_window() :
    width(800),
    height(600)
{
    if(!initialized && !glfwInit())
        throw std::runtime_error("glfw_window::glfw_window: failed to initialize glfw");

    initialized = true;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, "vulkan tutorial", nullptr, nullptr);

    if(!window)
        throw std::runtime_error("glfw_window::glfw_window: failed to create window");

    // populate required extensions
    extensions = glfwGetRequiredInstanceExtensions(&num_extensions);
    glfwSetWindowUserPointer(window, this);
    ++num_windows;
}

glfw_window::~glfw_window()
{
    glfwDestroyWindow(window);
    --num_windows;

    if(num_windows <= 0)
    {
        glfwTerminate();
        initialized = false;
    }
}

/** @function close
 *
 *  tells glfw window to close
 */
void glfw_window::close() { glfwSetWindowShouldClose(window, true); }

/** @function should_close
 *
 *  @return bool: true if window should close, false otherwise
 */
bool glfw_window::should_close() { return glfwWindowShouldClose(window); }

/** @function poll_events
 *
 *  polls glfw for any queued events
 */
void glfw_window::poll_events() { glfwPollEvents(); }
