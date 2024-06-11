#include "vulkan++.hpp"

#include <stdexcept>
#include <set>

using namespace vk;

Buffer vk::createBuffer(
        const Device                       &device,
        const DeviceSize                   &size,
        const VkBufferUsageFlags           &usage,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createBufferCreateInfo(
                size, usage, pCreateInfoNext
        );

        Buffer buffer{};
        Result result = vkCreateBuffer(device, &createInfo, pAllocator, &buffer);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create buffer!");

        return buffer;
}

BufferView vk::createBufferView(
        const Device                       &device,
        const Buffer                       &buffer,
        const Format                       &format,
        const DeviceSize                   &offset,
        const DeviceSize                   &range,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createBufferViewCreateInfo(
                buffer, format, offset, range, pCreateInfoNext
        );

        BufferView bufferView{};
        Result result = vkCreateBufferView(device, &createInfo, pAllocator, &bufferView);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate command buffer view!");

        return bufferView;
}

CommandBuffer vk::createCommandBuffer(
        const CommandPool          &commandPool,
        const Device               &device,
        const void                 *pAllocInfoNext
) {
        auto allocateInfo = vk::createCommandBufferAllocateInfo(
                commandPool, pAllocInfoNext
        );

        CommandBuffer commandBuffer{};
        Result result = vkAllocateCommandBuffers(
                device, &allocateInfo, &commandBuffer
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate command buffer!");

        return commandBuffer;
}

CommandPool vk::createCommandPool(
        const uint32_t                     &queueFamilyIndex,
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createCommandPoolCreateInfo(
                queueFamilyIndex, pCreateInfoNext
        );

        CommandPool commandPool{};
        Result result = vkCreateCommandPool(device, &createInfo, pAllocator, &commandPool);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create command pool!");

        return commandPool;
}

DescriptorPool vk::createDescriptorPool(
        const Device                                   &device,
        const uint32_t                                 &descriptorCount,
        const std::vector<VkDescriptorPoolSize>        &poolSizes,
        const VkAllocationCallbacks                    *pAllocator,
        const void                                     *pCreateInfoNext
) {
        auto createInfo = vk::createDescriptorPoolCreateInfo(
                descriptorCount, poolSizes, pCreateInfoNext
        );

        DescriptorPool descriptorPool;
        Result result = vkCreateDescriptorPool(
                device, &createInfo,
                pAllocator, &descriptorPool
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create descriptor pool!");

        return descriptorPool;
}

std::vector<DescriptorSet> vk::createDescriptorSets(
        const Device                                    &device,
        const VkDescriptorPool                          &pool,
        const std::vector<VkDescriptorSetLayout>        &descriptorSetLayouts,
        const void                                      *pAllocInfoNext
) {
        auto allocateInfo = vk::createDescriptorSetAllocateInfo(
                pool, descriptorSetLayouts, pAllocInfoNext
        );

        std::vector<DescriptorSet> descriptorSets(descriptorSetLayouts.size());
        Result result = vkAllocateDescriptorSets(
                device, &allocateInfo, descriptorSets.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate descriptor sets!");

        return descriptorSets;
}

DescriptorSetLayout vk::createDescriptorSetLayout(
        const VkDevice                                         &device,
        const std::vector<VkDescriptorSetLayoutBinding>        &bindings,
        const VkAllocationCallbacks                            *pAllocator,
        const void                                             *pCreateInfoNext
) {
        auto createInfo = vk::createDescriptorSetLayoutCreateInfo(
                bindings, pCreateInfoNext
        );

        DescriptorSetLayout descriptorSetLayout;
        Result result = vkCreateDescriptorSetLayout(
                device, &createInfo,
                pAllocator, &descriptorSetLayout
        );

        if (result != VK_SUCCESS) {
                throw std::runtime_error("Could not create descriptor set layout!");
        }

        return descriptorSetLayout;
}

Device vk::createDevice(
        const PhysicalDevice                   &physicalDevice,
        const std::vector<uint32_t>            &queueFamilyIndices,
        const std::vector<const char *>        &enabledExtensionNames,
        const VkPhysicalDeviceFeatures         *pEnabledFeatures,
        const VkAllocationCallbacks            *pAllocator,
        const void                             *pCreateInfoNext
) {
        float queuePriority = 1.0f;

        std::set<uint32_t> tmp(queueFamilyIndices.begin(), queueFamilyIndices.end());
        std::vector<uint32_t> fixedIndices(tmp.begin(), tmp.end());

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        for (const uint32_t &familyIndex : fixedIndices)
                queueCreateInfos.push_back(vk::createDeviceQueueCreateInfo(
                        familyIndex, &queuePriority
                ));

        auto createInfo = vk::createDeviceCreateInfo(
                queueCreateInfos, enabledExtensionNames, pEnabledFeatures, pCreateInfoNext
        );

        Device device{};
        Result result = vkCreateDevice(
                physicalDevice, &createInfo,
                pAllocator, &device
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create logical device!");

        return device;
}

Fence vk::createFence(
        const Device                       &device,
        const bool                         &signaled,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createFenceCreateInfo(
                signaled, pCreateInfoNext
        );

        Fence fence{};
        Result result = vkCreateFence(
                device, &createInfo,
                pAllocator, &fence
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create fence!");

        return fence;
}

Framebuffer vk::createFramebuffer(
        const RenderPass                      &renderPass,
        const VkExtent2D                      &extent,
        const std::vector<VkImageView>        &imageViews,
        const Device                          &device,
        const VkAllocationCallbacks           *pAllocator,
        const void                            *pCreateInfoNext
) {
        auto createInfo = vk::createFramebufferCreateInfo(
                renderPass, extent, imageViews, pCreateInfoNext
        );

        Framebuffer framebuffer{};
        Result result = vkCreateFramebuffer(
                device, &createInfo,
                pAllocator, &framebuffer
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create frame buffer!");

        return framebuffer;
}

Image vk::createImage(
        const Device                       &device,
        const VkImageType                  &imageType,
        const Format                       &format,
        const Extent3D                     &extent,
        const VkImageUsageFlags            &usage,
        const std::vector<uint32_t>        &queueFamilyIndices,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createImageCreateInfo(
                imageType, format, extent, usage,
                queueFamilyIndices, pCreateInfoNext
        );

        Image image{};
        Result result = vkCreateImage(device, &createInfo, pAllocator, &image);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create image!");

        return image;
}

ImageView vk::createImageView(
        const Image                        &image,
        const Format                       &format,
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createImageViewCreateInfo(
                image, format, pCreateInfoNext
        );

        ImageView imageView{};
        Result result = vkCreateImageView(
                device, &createInfo,
                pAllocator, &imageView
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create image view!");

        return imageView;
}

Instance vk::createInstance(
        const char                             *name,
        const uint32_t                         &version,
        const std::vector<const char *>        &enabledLayerNames,
        const std::vector<const char *>        &enabledExtensionNames,
        const VkAllocationCallbacks            *pAllocator,
        const void                             *pCreateInfoNext
) {
        uint32_t apiVersion = 0;
        Result result = vkEnumerateInstanceVersion(&apiVersion);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get api version!");

        auto applicationInfo = vk::createApplicationInfo(
                name, version, apiVersion
        );

        auto createInfo = vk::createInstanceCreateInfo(
                applicationInfo, enabledLayerNames,
                enabledExtensionNames, pCreateInfoNext
        );

        Instance instance{};
        result = vkCreateInstance(&createInfo, pAllocator, &instance);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create vulkan instance!");

        return instance;
}

std::vector<PhysicalDevice> vk::getPhysicalDevices(
        const Instance        &instance
) {
        uint32_t physicalDevicesCount = 0;
        Result result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr);

        if (result != VK_SUCCESS && result != VK_INCOMPLETE)
                throw std::runtime_error("Could not get physical devices count!");

        std::vector<PhysicalDevice> physicalDevices(physicalDevicesCount);
        result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get physical devices!");

        return physicalDevices;
}

Pipeline vk::createPipeline(
        const Device                                              &device,
        const RenderPass                                          &renderPass,
        const std::vector<Viewport>                               &viewports,
        const std::vector<Rect2D>                                 &scissors,
        const PipelineLayout                                      &layout,
        const std::vector<PipelineShaderStageCreateInfo>          &shaderStages,
        const std::vector<VertexInputBindingDescription>          &bindingDescriptions,
        const std::vector<VertexInputAttributeDescription>        &attributeDescriptions,
        const VkAllocationCallbacks                               *pAllocator,
        const void                                                *pCreateInfoNext
) {
        auto vertexInputStateCreateInfo = vk::createPipelineVertexInputStateCreateInfo(
                bindingDescriptions, attributeDescriptions
        );

        auto inputAssemblyStateCreateInfo = vk::createPipelineInputAssemblyStateCreateInfo();

        auto viewportStateCreateInfo = vk::createPipelineViewportStateCreateInfo(
                viewports, scissors
        );

        auto rasterizationStateCreateInfo = vk::createPipelineRasterizationStateCreateInfo();

        auto multisampleStateCreateInfo = vk::createPipelineMultisampleStateCreateInfo();

        auto colorBlendAttachmentState = vk::createPipelineColorBlendAttachmentState();

        auto colorBlendStateCreateInfo = vk::createPipelineColorBlendStateCreateInfo(
                colorBlendAttachmentState
        );

        auto createInfo = vk::createGraphicsPipelineCreateInfo(
                vertexInputStateCreateInfo, inputAssemblyStateCreateInfo, viewportStateCreateInfo,
                rasterizationStateCreateInfo, multisampleStateCreateInfo, colorBlendStateCreateInfo,
                shaderStages, layout, renderPass, pCreateInfoNext
        );

        Pipeline pipeline{};
        Result result = vkCreateGraphicsPipelines(
                device, nullptr,
                1, &createInfo,
                pAllocator, &pipeline
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create graphic pipeline!");

        return pipeline;
}

PipelineLayout vk::createPipelineLayout(
        const Device                                  &device,
        const std::vector<DescriptorSetLayout>        &setLayouts,
        const std::vector<PushConstantRange>          &pushConstantRanges,
        const VkAllocationCallbacks                   *pAllocator,
        const void                                    *pCreateInfoNext
) {
        auto createInfo = vk::createPipelineLayoutCreateInfo(
                setLayouts, pushConstantRanges, pCreateInfoNext
        );

        PipelineLayout layout{};
        Result result = vkCreatePipelineLayout(
                device, &createInfo,
                pAllocator, &layout
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create pipeline layout!");

        return layout;
}

Queue vk::getQueue(
        const Device          &device,
        const uint32_t        &queueFamilyIndex,
        const uint32_t        &queueIndex
) {
        Queue queue{};
        vkGetDeviceQueue(
                device, queueFamilyIndex,
                queueIndex, &queue
        );

        return queue;
}

RenderPass vk::createRenderPass(
        const PhysicalDevice               &physicalDevice,
        const Device                       &device,
        const SurfaceKHR                   &surface,
        const SurfaceFormatKHR             &requiredFormat,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        uint32_t formatsCount = 0;
        Result result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, nullptr
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get format count!");

        std::vector<VkSurfaceFormatKHR> formats(formatsCount);
        result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, formats.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get formats!");

        Format format = formats[0].format;
        for (const VkSurfaceFormatKHR &f : formats)
                if (f.format == requiredFormat.format && f.colorSpace == requiredFormat.colorSpace) {
                        format = f.format;
                        break;
                }

        auto attachmentDescription = vk::createAttachmentDescription(
                format
        );

        std::vector attachmentReferences { vk::createAttachmentReference(
                0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        )};
        auto subpassDescription = vk::createSubpassDescription(
                {}, attachmentReferences,
                {}, {}, {}
        );

        auto createInfo = vk::createRenderPassCreateInfo(
                attachmentDescription, subpassDescription, pCreateInfoNext
        );

        RenderPass renderPass{};
        result = vkCreateRenderPass(
                device, &createInfo,
                pAllocator, &renderPass
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create pipeline render pass!");

        return renderPass;
}

Sampler vk::createSampler(
        const Device                      &device,
        const VkFilter                    &filter,
        const VkSamplerAddressMode        &addressMode,
        const Bool32                      &anisotropyEnable,
        const float                       &maxAnisotropy,
        const Bool32                      &compareEnable,
        const VkCompareOp                 &compareOp,
        const void                        *pCreateInfoNext
) {
        auto createInfo = vk::createSamplerCreateInfo(
                filter, addressMode, anisotropyEnable,
                maxAnisotropy, compareEnable, compareOp,
                pCreateInfoNext
        );

        Sampler sampler{};
        Result result = vkCreateSampler(
                device, &createInfo,
                nullptr, &sampler
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create sampler!");

        return sampler;
}

Semaphore vk::createSemaphore(
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createSemaphoreCreateInfo(
                pCreateInfoNext
        );

        Semaphore semaphore{};
        Result result = vkCreateSemaphore(
                device, &createInfo,
                pAllocator, &semaphore
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create semaphore!");

        return semaphore;
}

ShaderModule vk::createShaderModule(
        const std::vector<uint8_t>         &code,
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        auto createInfo = vk::createShaderModuleCreateInfo(
                code, pCreateInfoNext
        );

        ShaderModule shaderModule{};
        Result result = vkCreateShaderModule(
                device, &createInfo,
                pAllocator, &shaderModule
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Failed to create shader module!");

        return shaderModule;
}

SwapchainKHR vk::createSwapchainKHR(
        const Device                             &device,
        const SurfaceKHR                         &surface,
        const std::vector<PresentModeKHR>        &presentModes,
        const SurfaceCapabilitiesKHR             &capabilities,
        const std::vector<uint32_t>              &queueFamilyIndices,
        const SurfaceFormatKHR                   &format,
        const Extent2D                           &extent,
        const VkAllocationCallbacks              *pAllocator,
        const void                               *pCreateInfoNext
) {
        uint32_t imageCount = std::min(capabilities.maxImageCount, capabilities.minImageCount + 1);
        PresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

        for (const VkPresentModeKHR p : presentModes)
                if (p == VK_PRESENT_MODE_MAILBOX_KHR) {
                        presentMode = p;
                        break;
                }

        std::set tmp(queueFamilyIndices.begin(), queueFamilyIndices.end());
        std::vector fixedIndices(tmp.begin(), tmp.end());

        VkSharingMode sharingMode = fixedIndices.size() == 1 ?
                VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;

        auto createInfo = vk::createSwapchainCreateInfoKHR(
                capabilities, imageCount, format, extent, presentMode,
                surface, sharingMode, fixedIndices, pCreateInfoNext
        );

        SwapchainKHR swapchain{};
        Result result = vkCreateSwapchainKHR(
                device, &createInfo,
                pAllocator, &swapchain
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create swapchain.");

        return swapchain;
}

PhysicalDeviceProperties vk::getPhysicalDeviceProperties(
        const PhysicalDevice        &physicalDevice
) {
        PhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);

        return properties;
}

PhysicalDeviceMemoryProperties vk::getPhysicalDeviceMemoryProperties(
        const PhysicalDevice        &physicalDevice
) {
        PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);

        return physicalDeviceMemoryProperties;
}

SurfaceCapabilitiesKHR vk::getSurfaceCapabilitiesKHR(
        const PhysicalDevice        &physicalDevice,
        const SurfaceKHR            &surface
) {
        SurfaceCapabilitiesKHR capabilities{};
        Result result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get physical device surface capabilities!");

        return capabilities;
}

std::vector<SurfaceFormatKHR> vk::getSurfaceFormatKHRs(
        const PhysicalDevice        &physicalDevice,
        const SurfaceKHR            &surface
) {
        uint32_t formatsCount = 0;
        Result result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, nullptr
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get surface formats count!");

        std::vector<SurfaceFormatKHR> formats(formatsCount);
        result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, formats.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get surface formats.");

        return formats;
}

std::vector<PresentModeKHR> vk::getPresentModeKHR(
        const PhysicalDevice        &physicalDevice,
        const SurfaceKHR            &surface
) {
        uint32_t presentModesCount = 0;
        Result result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                physicalDevice, surface,
                &presentModesCount, nullptr
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get present mode count.");

        std::vector<PresentModeKHR> presentModes(presentModesCount);
        result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                physicalDevice, surface,
                &presentModesCount, presentModes.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get present modes.");

        return presentModes;
}

std::vector<QueueFamilyProperties> vk::getQueueFamilyProperties(
        const PhysicalDevice &physicalDevice
) {
        uint32_t propertyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &propertyCount, nullptr);

        if (propertyCount == 0)
                throw std::runtime_error("Could not get family queue property count.");

        std::vector<QueueFamilyProperties> queueFamilies(propertyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &propertyCount, queueFamilies.data());

        if (queueFamilies.empty())
                throw std::runtime_error("Could not get family queue properties.");

        return queueFamilies;
}

std::vector<ExtensionProperties> vk::getExtensionProperties(
        const PhysicalDevice &physicalDevice
) {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(
                physicalDevice, nullptr,
                &extensionCount, nullptr
        );

        std::vector<ExtensionProperties> extensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(
                physicalDevice, nullptr,
                &extensionCount, extensions.data()
        );

        return extensions;
}