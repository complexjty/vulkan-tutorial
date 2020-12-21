#ifndef GPU_HXX
#define GPU_HXX

#include <vulkan/vulkan.h>

class gpu {
public:
    gpu();

    VkPhysicalDevice physical_device;
};

#endif
