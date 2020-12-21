#ifndef VK_INSTANCE_HXX
#define VK_INSTANCE_HXX

#include "types.hxx"

#include <vector>
#include <vulkan/vulkan.h>

class vk_instance {

public:
    vk_instance(const char **win_extensions, u32 num_win_extensions);
    ~vk_instance();

    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;

private:
    bool create_instance();
    bool check_extension_support();
    bool check_validation_layer_support();
    VkResult setup_debug_messenger();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
            VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
            VkDebugUtilsMessageSeverityFlagsEXT message_type,
            const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
            void *p_user_data
    );

    static const bool enable_validation_layer;
    static const std::vector<const char *> required_layers;
    std::vector<const char *> required_extensions;
    std::vector<VkExtensionProperties> available_extensions;
};

#endif
