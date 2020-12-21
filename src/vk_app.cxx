#include "vk_app.hxx"

// temp to avoid laptop becoming a pit in hell
#include <chrono>
#include <thread>

vk_app::vk_app()
{
    // init
    window = new glfw_window();
    instance = new vk_instance(window->extensions, window->num_extensions);
}

vk_app::~vk_app()
{
    // cleanup
    delete window;
}

void vk_app::run()
{
    // main loop
    while(!window->should_close())
    {
        window->poll_events();
        update();
    }
}

/* =========================================================================
 * PRIVATE FUNCTIONS
 * =======================================================================*/

/** @function update
 *
 *  render loop
 */
void vk_app::update()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
