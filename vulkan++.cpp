#include "vulkan++.hpp"

#include <stdexcept>
#include <set>
#include <iostream>

#define LOG_FATAL(__MSG__)      do {                                                                            \
                                        std::cout << "\u001b[31m[FATAL ERROR]  " << __MSG__ << "\u001b[0m\n";   \
                                        throw std::runtime_error(__MSG__);                                      \
                                } while(0)

using namespace vk;

Buffer vk::createBuffer(
        Device                             device,
        DeviceSize                         size,
        VkBufferUsageFlags                 usage,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        BufferCreateInfo createInfo = vk::createBufferCreateInfo(
                size, usage, pCreateInfoNext
        );

        Buffer buffer{};
        Result result = vkCreateBuffer(device, &createInfo, pAllocator, &buffer);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create buffer!");

        return buffer;
}

BufferView vk::createBufferView(
        Device                             device,
        Buffer                             buffer,
        Format                             format,
        DeviceSize                         offset,
        DeviceSize                         range,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        BufferViewCreateInfo createInfo = vk::createBufferViewCreateInfo(
                buffer, format, offset, range, pCreateInfoNext
        );

        BufferView bufferView{};
        Result result = vkCreateBufferView(device, &createInfo, pAllocator, &bufferView);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not allocate command buffer view!");

        return bufferView;
}

CommandBuffer vk::createCommandBuffer(
        CommandPool        commandPool,
        Device             device,
        const void         *pAllocInfoNext
) {
        CommandBufferAllocateInfo allocateInfo = vk::createCommandBufferAllocateInfo(
                commandPool, pAllocInfoNext
        );

        CommandBuffer commandBuffer{};
        Result result = vkAllocateCommandBuffers(
                device, &allocateInfo, &commandBuffer
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not allocate command buffer!");

        return commandBuffer;
}

CommandPool vk::createCommandPool(
        uint32_t                           queueFamilyIndex,
        Device                             device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        CommandPoolCreateInfo createInfo = vk::createCommandPoolCreateInfo(
                queueFamilyIndex, pCreateInfoNext
        );

        CommandPool commandPool{};
        Result result = vkCreateCommandPool(device, &createInfo, pAllocator, &commandPool);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create command pool!");

        return commandPool;
}

DescriptorPool vk::createDescriptorPool(
        Device                                       device,
        uint32_t                                     descriptorCount,
        const std::vector<DescriptorPoolSize>        &poolSizes,
        const VkAllocationCallbacks                  *pAllocator,
        const void                                   *pCreateInfoNext
) {
        DescriptorPoolCreateInfo createInfo = vk::createDescriptorPoolCreateInfo(
                descriptorCount, poolSizes, pCreateInfoNext
        );

        DescriptorPool descriptorPool;
        Result result = vkCreateDescriptorPool(
                device, &createInfo,
                pAllocator, &descriptorPool
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create descriptor pool!");

        return descriptorPool;
}

std::vector<DescriptorSet> vk::createDescriptorSets(
        Device                                        device,
        DescriptorPool                                pool,
        const std::vector<DescriptorSetLayout>        &descriptorSetLayouts,
        const void                                    *pAllocInfoNext
) {
        DescriptorSetAllocateInfo allocateInfo = vk::createDescriptorSetAllocateInfo(
                pool, descriptorSetLayouts, pAllocInfoNext
        );

        std::vector<DescriptorSet> descriptorSets(descriptorSetLayouts.size());
        Result result = vkAllocateDescriptorSets(
                device, &allocateInfo, descriptorSets.data()
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not allocate descriptor sets!");

        return descriptorSets;
}

DescriptorSetLayout vk::createDescriptorSetLayout(
        Device                                                 device,
        const std::vector<VkDescriptorSetLayoutBinding>        &bindings,
        const VkAllocationCallbacks                            *pAllocator,
        const void                                             *pCreateInfoNext
) {
        DescriptorSetLayoutCreateInfo createInfo = vk::createDescriptorSetLayoutCreateInfo(
                bindings, pCreateInfoNext
        );

        DescriptorSetLayout descriptorSetLayout;
        Result result = vkCreateDescriptorSetLayout(
                device, &createInfo,
                pAllocator, &descriptorSetLayout
        );

        if (result != VK_SUCCESS) {
                LOG_FATAL("Could not create descriptor set layout!");
        }

        return descriptorSetLayout;
}

Device vk::createDevice(
        PhysicalDevice                         physicalDevice,
        const std::vector<uint32_t>            &queueFamilyIndices,
        const std::vector<const char *>        &enabledExtensionNames,
        const PhysicalDeviceFeatures           *pEnabledFeatures,
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

        DeviceCreateInfo createInfo = vk::createDeviceCreateInfo(
                queueCreateInfos, enabledExtensionNames, pEnabledFeatures, pCreateInfoNext
        );

        Device device{};
        Result result = vkCreateDevice(
                physicalDevice, &createInfo,
                pAllocator, &device
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create logical device!");

        return device;
}

Fence vk::createFence(
        Device                             device,
        bool                               signaled,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        FenceCreateInfo createInfo = vk::createFenceCreateInfo(
                signaled, pCreateInfoNext
        );

        Fence fence{};
        Result result = vkCreateFence(
                device, &createInfo,
                pAllocator, &fence
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create fence!");

        return fence;
}

Framebuffer vk::createFramebuffer(
        RenderPass                          renderPass,
        Extent2D                            extent,
        const std::vector<ImageView>        &attachments,
        Device                              device,
        const VkAllocationCallbacks         *pAllocator,
        const void                          *pCreateInfoNext
) {
        FramebufferCreateInfo createInfo = vk::createFramebufferCreateInfo(
                renderPass, extent, attachments, pCreateInfoNext
        );

        Framebuffer framebuffer{};
        Result result = vkCreateFramebuffer(
                device, &createInfo,
                pAllocator, &framebuffer
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create frame buffer!");

        return framebuffer;
}

Image vk::createImage(
        Device                             device,
        VkImageType                        imageType,
        Format                             format,
        const Extent3D                     &extent,
        VkImageUsageFlags                  usage,
        VkImageTiling                      tiling,
        const std::vector<uint32_t>        &queueFamilyIndices,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        ImageCreateInfo createInfo = vk::createImageCreateInfo(
                imageType, format, extent, usage, tiling,
                queueFamilyIndices, pCreateInfoNext
        );

        Image image{};
        Result result = vkCreateImage(device, &createInfo, pAllocator, &image);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create image!");

        return image;
}

ImageView vk::createImageView(
        Image                              image,
        VkImageAspectFlags                 aspectMask,
        Format                             format,
        Device                             device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        ImageViewCreateInfo createInfo = vk::createImageViewCreateInfo(
                image, format, aspectMask, pCreateInfoNext
        );

        ImageView imageView{};
        Result result = vkCreateImageView(
                device, &createInfo,
                pAllocator, &imageView
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create image view!");

        return imageView;
}

Instance vk::createInstance(
        const char                             *name,
        uint32_t                               version,
        const std::vector<const char *>        &enabledLayerNames,
        const std::vector<const char *>        &enabledExtensionNames,
        const VkAllocationCallbacks            *pAllocator,
        const void                             *pCreateInfoNext
) {
        uint32_t apiVersion = 0;
        Result result = vkEnumerateInstanceVersion(&apiVersion);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get api version!");

        ApplicationInfo applicationInfo = vk::createApplicationInfo(
                name, version, apiVersion
        );

        InstanceCreateInfo createInfo = vk::createInstanceCreateInfo(
                applicationInfo, enabledLayerNames,
                enabledExtensionNames, pCreateInfoNext
        );

        Instance instance{};
        result = vkCreateInstance(&createInfo, pAllocator, &instance);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create vulkan instance!");

        return instance;
}

std::vector<PhysicalDevice> vk::getPhysicalDevices(
        Instance        instance
) {
        uint32_t physicalDevicesCount = 0;
        Result result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr);

        if (result != VK_SUCCESS && result != VK_INCOMPLETE)
                LOG_FATAL("Could not get physical devices count!");

        std::vector<PhysicalDevice> physicalDevices(physicalDevicesCount);
        result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get physical devices!");

        return physicalDevices;
}

Pipeline vk::createGraphicPipeline(
        Device                                                  device,
        RenderPass                                              renderPass,
        PipelineLayout                                          layout,
        VkPrimitiveTopology                                     primitiveTopology,
        const std::vector<PipelineShaderStageCreateInfo>        &shaderStages,
        const PipelineVertexInputStateCreateInfo                *pVertexInputState,
        const PipelineDepthStencilStateCreateInfo               *pDepthStencilState,
        PipelineCache                                           pipelineCache,
        const VkAllocationCallbacks                             *pAllocator,
        const void                                              *pCreateInfoNext
) {
        PipelineInputAssemblyStateCreateInfo inputAssemblyState = vk::createPipelineInputAssemblyStateCreateInfo(primitiveTopology);
        PipelineRasterizationStateCreateInfo rasterizationState = vk::createPipelineRasterizationStateCreateInfo();
        PipelineMultisampleStateCreateInfo multisampleState = vk::createPipelineMultisampleStateCreateInfo();
        PipelineColorBlendAttachmentState colorBlendAttachmentState = vk::createPipelineColorBlendAttachmentState();
        PipelineColorBlendStateCreateInfo colorBlendState = vk::createPipelineColorBlendStateCreateInfo(
                { colorBlendAttachmentState }
        );

        PipelineViewportStateCreateInfo viewportState = vk::createPipelineViewportStateCreateInfo(
                {Viewport()}, {Rect2D()}
        );

        std::vector<VkDynamicState> dynamicStates {
                VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR
        };
        PipelineDynamicStateCreateInfo dynamicState = vk::createPipelineDynamicStateCreateInfo(
                dynamicStates
        );

        GraphicsPipelineCreateInfo createInfo = vk::createGraphicsPipelineCreateInfo(
                pVertexInputState, &inputAssemblyState, &viewportState,
                &rasterizationState, &multisampleState, pDepthStencilState,
                &colorBlendState, shaderStages, &dynamicState,
                layout, renderPass, pCreateInfoNext
        );

        Pipeline pipeline{};
        Result result = vkCreateGraphicsPipelines(
                device, pipelineCache,
                1, &createInfo,
                pAllocator, &pipeline
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create graphic pipeline!");

        return pipeline;
}

PipelineLayout vk::createPipelineLayout(
        Device                                        device,
        const std::vector<DescriptorSetLayout>        &setLayouts,
        const std::vector<PushConstantRange>          &pushConstantRanges,
        const VkAllocationCallbacks                   *pAllocator,
        const void                                    *pCreateInfoNext
) {
        PipelineLayoutCreateInfo createInfo = vk::createPipelineLayoutCreateInfo(
                setLayouts, pushConstantRanges, pCreateInfoNext
        );

        PipelineLayout layout{};
        Result result = vkCreatePipelineLayout(
                device, &createInfo,
                pAllocator, &layout
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create pipeline layout!");

        return layout;
}

Queue vk::getQueue(
        Device          device,
        uint32_t        queueFamilyIndex,
        uint32_t        queueIndex
) {
        Queue queue{};
        vkGetDeviceQueue(
                device, queueFamilyIndex,
                queueIndex, &queue
        );

        return queue;
}

RenderPass vk::createRenderPass(
        Device                                          device,
        const std::vector<SubpassDescription>           &subpassDescriptions,
        const std::vector<AttachmentDescription>        &attachmentDescriptions,
        const std::vector<SubpassDependency>            &dependencies,
        const VkAllocationCallbacks                     *pAllocator,
        const void                                      *pCreateInfoNext
) {
        RenderPassCreateInfo createInfo = vk::createRenderPassCreateInfo(
                attachmentDescriptions, subpassDescriptions, dependencies,  pCreateInfoNext
        );

        RenderPass renderPass{};
        Result result = vkCreateRenderPass(
                device, &createInfo,
                pAllocator, &renderPass
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create render pass!");

        return renderPass;
}

Sampler vk::createSampler(
        Device                      device,
        VkFilter                    filter,
        VkSamplerAddressMode        addressMode,
        Bool32                      anisotropyEnable,
        float                       maxAnisotropy,
        Bool32                      compareEnable,
        VkCompareOp                 compareOp,
        const void                  *pCreateInfoNext
) {
        SamplerCreateInfo createInfo = vk::createSamplerCreateInfo(
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
                LOG_FATAL("Could not create sampler!");

        return sampler;
}

Semaphore vk::createSemaphore(
        Device                             device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        SemaphoreCreateInfo createInfo = vk::createSemaphoreCreateInfo(
                pCreateInfoNext
        );

        Semaphore semaphore{};
        Result result = vkCreateSemaphore(
                device, &createInfo,
                pAllocator, &semaphore
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create semaphore!");

        return semaphore;
}

ShaderModule vk::createShaderModule(
        const std::vector<uint8_t>         &code,
        Device                             device,
        const VkAllocationCallbacks        *pAllocator,
        const void                         *pCreateInfoNext
) {
        ShaderModuleCreateInfo createInfo = vk::createShaderModuleCreateInfo(
                code, pCreateInfoNext
        );

        ShaderModule shaderModule{};
        Result result = vkCreateShaderModule(
                device, &createInfo,
                pAllocator, &shaderModule
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Failed to create shader module!");

        return shaderModule;
}

SwapchainKHR vk::createSwapchainKHR(
        Device                                   device,
        SurfaceKHR                               surface,
        const std::vector<PresentModeKHR>        &presentModes,
        SurfaceCapabilitiesKHR                   capabilities,
        const std::vector<uint32_t>              &queueFamilyIndices,
        SurfaceFormatKHR                         format,
        Extent2D                                 extent,
        SwapchainKHR                             oldSwapchain,
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

        std::set<uint32_t> tmp(queueFamilyIndices.begin(), queueFamilyIndices.end());
        std::vector<uint32_t> fixedIndices(tmp.begin(), tmp.end());

        SwapchainCreateInfoKHR createInfo = vk::createSwapchainCreateInfoKHR(
                capabilities, imageCount, format, extent, presentMode,
                surface, fixedIndices, oldSwapchain, pCreateInfoNext
        );

        SwapchainKHR swapchain{};
        Result result = vkCreateSwapchainKHR(
                device, &createInfo,
                pAllocator, &swapchain
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create swapchain!");

        return swapchain;
}

PhysicalDeviceProperties vk::getPhysicalDeviceProperties(
        PhysicalDevice        physicalDevice
) {
        PhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);

        return properties;
}

PhysicalDeviceMemoryProperties vk::getPhysicalDeviceMemoryProperties(
        PhysicalDevice        physicalDevice
) {
        PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);

        return physicalDeviceMemoryProperties;
}

SurfaceCapabilitiesKHR vk::getSurfaceCapabilitiesKHR(
        PhysicalDevice        physicalDevice,
        SurfaceKHR            surface
) {
        SurfaceCapabilitiesKHR capabilities{};
        Result result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get physical device surface capabilities!");

        return capabilities;
}

std::vector<SurfaceFormatKHR> vk::getSurfaceFormatKHRs(
        PhysicalDevice        physicalDevice,
        SurfaceKHR            surface
) {
        uint32_t formatsCount = 0;
        Result result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, nullptr
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get surface formats count!");

        std::vector<SurfaceFormatKHR> formats(formatsCount);
        result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, formats.data()
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get surface formats!");

        return formats;
}

std::vector<PresentModeKHR> vk::getPresentModeKHR(
        PhysicalDevice        physicalDevice,
        SurfaceKHR            surface
) {
        uint32_t presentModesCount = 0;
        Result result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                physicalDevice, surface,
                &presentModesCount, nullptr
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get present mode count!");

        std::vector<PresentModeKHR> presentModes(presentModesCount);
        result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                physicalDevice, surface,
                &presentModesCount, presentModes.data()
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not get present modes!");

        return presentModes;
}

std::vector<QueueFamilyProperties> vk::getQueueFamilyProperties(
        PhysicalDevice        physicalDevice
) {
        uint32_t propertyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &propertyCount, nullptr);

        if (propertyCount == 0)
                LOG_FATAL("Could not get family queue property count!");

        std::vector<QueueFamilyProperties> queueFamilies(propertyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &propertyCount, queueFamilies.data());

        if (queueFamilies.empty())
                LOG_FATAL("Could not get family queue properties!");

        return queueFamilies;
}

std::vector<ExtensionProperties> vk::getExtensionProperties(
        PhysicalDevice        physicalDevice
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

DescriptorUpdateTemplate vk::createDescriptorUpdateTemplate(
        Device                                                   device,
        const std::vector<DescriptorUpdateTemplateEntry>         &descriptorUpdateEntries,
        VkDescriptorUpdateTemplateType                           templateType,
        DescriptorSetLayout                                      descriptorSetLayout,
        VkPipelineBindPoint                                      pipelineBindPoint,
        PipelineLayout                                           pipelineLayout,
        uint32_t                                                 set,
        const VkAllocationCallbacks                              *pAllocator,
        const void                                               *pCreateInfoNext
) {
        DescriptorUpdateTemplateCreateInfo createInfo = createDescriptorUpdateTemplateCreateInfo(
                descriptorUpdateEntries, templateType, descriptorSetLayout,
                pipelineBindPoint, pipelineLayout, set, pCreateInfoNext
        );

        DescriptorUpdateTemplate descriptorUpdateTemplate{};
        Result result = vkCreateDescriptorUpdateTemplate(
                device, &createInfo,
                pAllocator, &descriptorUpdateTemplate
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create descriptor update template!");

        return descriptorUpdateTemplate;
}

Pipeline vk::createComputePipeline(
        Device                                     device,
        PipelineCache                              pipelineCache,
        const PipelineShaderStageCreateInfo        &stage,
        PipelineLayout                             layout,
        Pipeline                                   basePipelineHandle,
        int32_t                                    basePipelineIndex,
        const VkAllocationCallbacks                *pAllocator,
        const void                                 *pCreateInfoNext
) {
        ComputePipelineCreateInfo createInfo = createComputePipelineCreateInfo(
                stage, layout, basePipelineHandle, basePipelineIndex, pCreateInfoNext
        );

        Pipeline pipeline{};
        Result result = vkCreateComputePipelines(
                device, pipelineCache, 1, &createInfo, pAllocator, &pipeline
        );

        if (result != VK_SUCCESS)
                LOG_FATAL("Could not create compute pipeline!");

        return pipeline;
}