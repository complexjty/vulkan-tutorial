#include "vk_instance.hxx"

#include "types.hxx"

#include <vector>
#include <cstring>
#include <iostream>
#include <stdexcept>

#ifdef NDEBUG
    const bool vk_instance::enable_validation_layer = false;
#else
    const bool vk_instance::enable_validation_layer = true;
#endif

const std::vector<const char *> vk_instance::required_layers = {
    "VK_LAYER_KHRONOS_validation"
};

vk_instance::vk_instance(const char **win_extensions, u32 num_win_extensions)
{
    if(enable_validation_layer && !check_validation_layer_support())
        throw std::runtime_error("vk_instace::vk_instance: validation layers requested but not available");

    if(enable_validation_layer)
        required_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    for(u32 i = 0; i < num_win_extensions; ++i)
        required_extensions.push_back(win_extensions[i]);

    if(!check_extension_support())
        throw std::runtime_error("vk_instace::vk_instance: extensions requested but not available");

    if(!create_instance())
        throw std::runtime_error("vk_instace::vk_instance: failed to create instance");

    if(enable_validation_layer)
    {
        if(setup_debug_messenger() != VK_SUCCESS)
            throw std::runtime_error("vk_instance::vk_instance: failed to set up debug messenger");
    }
}

vk_instance::~vk_instance()
{
    if(enable_validation_layer)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if(func != nullptr)
            func(instance, debug_messenger, nullptr);
    }

    vkDestroyInstance(instance, nullptr);
}

/* =========================================================================
 * PRIVATE FUNCTIONS
 * =======================================================================*/

bool vk_instance::create_instance()
{
    VkApplicationInfo app_info{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "vulkan tutorial",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
        .pEngineName = "no engine",
        .engineVersion = VK_MAKE_VERSION(0, 0, 1),
        .apiVersion = VK_API_VERSION_1_0
    };

    VkInstanceCreateInfo create_info{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = static_cast<u32>(required_extensions.size()),
        .ppEnabledExtensionNames = required_extensions.data()
    };

    if(enable_validation_layer)
    {
        create_info.enabledLayerCount = static_cast<u32>(required_layers.size());
        create_info.ppEnabledLayerNames = required_layers.data();
    }

    VkResult result = vkCreateInstance(&create_info, nullptr, &instance);

    if(result != VK_SUCCESS)
        return false;
    else
        return true;
}

bool vk_instance::check_extension_support()
{
    u32 num_available_extensions = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &num_available_extensions, nullptr);
    available_extensions.resize(num_available_extensions);
    vkEnumerateInstanceExtensionProperties(nullptr, &num_available_extensions, available_extensions.data());

    for(const auto &extension_name : required_extensions)
    {
        bool extension_found = false;
        for(const auto &extension_properties : available_extensions)
        {
            if(strcmp(extension_name, extension_properties.extensionName) == 0)
            {
                extension_found = true;
                break;
            }
        }

        if(!extension_found)
            return false;
    }

    return true;
}

bool vk_instance::check_validation_layer_support()
{
    u32 layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    for(const auto &layer_name : required_layers)
    {
        bool layer_found = false;
        for(const auto &layer_properties : available_layers)
        {
            if(strcmp(layer_name, layer_properties.layerName) == 0)
            {
                layer_found = true;
                break;
            }
        }

        if(!layer_found)
            return false;
    }

    return true;
}

VkResult vk_instance::setup_debug_messenger()
{
    VkDebugUtilsMessengerCreateInfoEXT create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT    |
                              VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    create_info.pfnUserCallback = debug_callback;
    create_info.pUserData = nullptr;

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr)
        return func(instance, &create_info, nullptr, &debug_messenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

VKAPI_ATTR VkBool32 VKAPI_CALL vk_instance::debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
        VkDebugUtilsMessageSeverityFlagsEXT message_type,
        const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
        void *p_user_data)
{
    std::cerr << "validation lyaer: " << p_callback_data->pMessage << std::endl;
    return VK_FALSE;
}
