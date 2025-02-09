#ifndef POMEGRANATEENGINE_CORE_H
#define POMEGRANATEENGINE_CORE_H
#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_beta.h>
#elif __linux__
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_beta.h>
#elif __APPLE__
#define VK_USE_PLATFORM_MACOS_MVK
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_beta.h>

#endif

#include <core/core.h>
#include <optional>
#include <set>
#include "enumerations.h"

struct Window;
struct ShaderBase;

template<BufferType Type>
class BufferBase;

template<typename T, BufferType BufferType>
class Buffer;

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool complete();
};

class Graphics {
public:
    struct GraphicsPipelineGroup {
        VkPipelineLayout layout;
        VkPipeline pipeline;
    };

    struct Queues {
        VkQueue graphicsQueue;
        VkQueue presentQueue;
    };

    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;
    VkPhysicalDevice _physicalDevice;
    VkDevice _logicalDevice;
    Queues _queues;
    std::vector<const char*> validationLayers;

    std::vector<const char*> deviceExtensions;

    std::vector<Window*> _windows;
    std::vector<ShaderBase*> _shaders;


    VkCommandPool _commandPool;

    void createInstance();

    void setupDebugMessenger();

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks* pAllocator);

    void createPhysicalDevice();

    void createLogicalDevice();

    void createCommandPool();

    bool hasValidationLayerSupport();

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool hasDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);

    SwapChainSupportDetails getSwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR* surface = nullptr);

    VkSurfaceFormatKHR getSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

    uint32_t getMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


    static Graphics _graphicsInstance;
public:
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    static const int MAX_FRAMES_IN_FLIGHT;

    void createRenderPass(Window* window);

    GraphicsPipelineGroup createGraphicsPipeline(ShaderBase* shader, Window* window, RenderInfo renderInfo,
                                                 VkVertexInputBindingDescription bindingDescription,
                                                 std::vector<VkVertexInputAttributeDescription> attributeDescriptions);

    void createSyncObjects();

    static bool enableValidationLayers;

    Graphics();

    ~Graphics();

    static Graphics* getInstance();

    friend class Window;

    friend class ShaderBase;
};


#endif //POMEGRANATEENGINE_CORE_H
