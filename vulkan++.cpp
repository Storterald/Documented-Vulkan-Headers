#include "vulkan++.hpp"

#include <stdexcept>
#include <set>

VkApplicationInfo vk::createVkApplicationInfo(
        const char            *pApplicationName,
        const uint32_t        &applicationVersion,
        const uint32_t        &apiVersion
) {
        return {
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pNext = nullptr,
                .pApplicationName = pApplicationName,
                .applicationVersion = applicationVersion,
                .pEngineName = "Vulkan Engine",
                .engineVersion = 1,
                .apiVersion = apiVersion
        };
}

VkPipelineVertexInputStateCreateInfo vk::createVkPipelineVertexInputStateCreateInfo(
        const std::vector<VkVertexInputBindingDescription>          &bindingDescriptions,
        const std::vector<VkVertexInputAttributeDescription>        &attributeDescriptions
) {
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineVertexInputStateCreateFlags(),
                .vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size()),
                .pVertexBindingDescriptions = bindingDescriptions.data(),
                .vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size()),
                .pVertexAttributeDescriptions = attributeDescriptions.data()
        };
}

VkPipelineInputAssemblyStateCreateInfo vk::createVkPipelineInputAssemblyStateCreateInfo()
{
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineInputAssemblyStateCreateFlags(),
                .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                .primitiveRestartEnable = VK_FALSE
        };
}

VkPipelineShaderStageCreateInfo vk::createVkPipelineShaderStageCreateInfo(
        const VkShaderStageFlagBits        &stage,
        const VkShaderModule               &module
) {
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineShaderStageCreateFlags(),
                .stage = stage,
                .module = module,
                .pName = "main",
                .pSpecializationInfo = nullptr
        };
}

VkViewport vk::createVkViewport(
        const VkExtent2D        &extent
) {
        return {
                .x = 0.0f,
                .y = 0.0f,
                .width = static_cast<float>(extent.width),
                .height = static_cast<float>(extent.height),
                .minDepth = 0.0f,
                .maxDepth = 1.0f
        };
}

VkRect2D vk::createVkRect2D(
        const VkExtent2D        &extent
) {
        return {
                .offset = {.x = 0, .y = 0},
                .extent = extent
        };
}

VkPipelineViewportStateCreateInfo vk::createVkPipelineViewportStateCreateInfo(
        const std::vector<VkViewport>        &viewports,
        const std::vector<VkRect2D>          &scissors
) {
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineViewportStateCreateFlags(),
                .viewportCount = static_cast<uint32_t>(viewports.size()),
                .pViewports = viewports.data(),
                .scissorCount = static_cast<uint32_t>(scissors.size()),
                .pScissors = scissors.data()
        };
}

VkPipelineRasterizationStateCreateInfo vk::createVkPipelineRasterizationStateCreateInfo()
{
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineRasterizationStateCreateFlags(),
                .depthClampEnable = VK_FALSE,
                .rasterizerDiscardEnable = VK_FALSE,
                .polygonMode = VK_POLYGON_MODE_FILL,
                .cullMode = VK_CULL_MODE_BACK_BIT,
                .frontFace = VK_FRONT_FACE_CLOCKWISE,
                .depthBiasEnable = VK_FALSE,
                .depthBiasConstantFactor = 0.0f,
                .depthBiasClamp = 0.0f,
                .depthBiasSlopeFactor = 0.0f,
                .lineWidth = 1.0f
        };
}

VkPipelineMultisampleStateCreateInfo vk::createVkPipelineMultisampleStateCreateInfo()
{
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineMultisampleStateCreateFlags(),
                .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
                .sampleShadingEnable = VK_FALSE,
                .minSampleShading = 0.0f,
                .pSampleMask = nullptr,
                .alphaToCoverageEnable = VK_FALSE,
                .alphaToOneEnable = VK_FALSE
        };
}

VkPipelineColorBlendAttachmentState vk::createVkPipelineColorBlendAttachmentState()
{
        return {
                .blendEnable = VK_FALSE,
                .srcColorBlendFactor = VK_BLEND_FACTOR_ZERO,
                .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
                .colorBlendOp = VK_BLEND_OP_ADD,
                .srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                .alphaBlendOp = VK_BLEND_OP_ADD,
                .colorWriteMask = 0xF
        };
}

VkPipelineColorBlendStateCreateInfo vk::createVkPipelineColorBlendStateCreateInfo(
        const VkPipelineColorBlendAttachmentState        &colorBlendAttachmentState
) {
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineColorBlendStateCreateFlags(),
                .logicOpEnable = VK_FALSE,
                .logicOp = VK_LOGIC_OP_COPY,
                .attachmentCount = 1,
                .pAttachments = &colorBlendAttachmentState,
                .blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}
        };
}

VkAttachmentDescription vk::createVkAttachmentDescription(
        const VkFormat        &format
) {
        return {
                .flags = VkAttachmentDescriptionFlags(),
                .format = format,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
        };
}

VkAttachmentReference vk::createVkAttachmentReference(
        const uint32_t             &attachment,
        const VkImageLayout        &layout
) {
        return {
                .attachment = attachment,
                .layout = layout
        };
}

VkSubpassDescription vk::createVkSubpassDescription(
        const std::vector<VkAttachmentReference>        &inputAttachments,
        const std::vector<VkAttachmentReference>        &colorAttachments,
        const std::vector<VkAttachmentReference>        &resolveAttachments,
        const std::vector<VkAttachmentReference>        &depthStencilAttachment,
        const std::vector<uint32_t>                     &preserveAttachments
) {
        return {
                .flags = VkSubpassDescriptionFlags(),
                .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                .inputAttachmentCount = static_cast<uint32_t>(inputAttachments.size()),
                .pInputAttachments = inputAttachments.data(),
                .colorAttachmentCount = static_cast<uint32_t>(colorAttachments.size()),
                .pColorAttachments = colorAttachments.data(),
                .pResolveAttachments = resolveAttachments.data(),
                .pDepthStencilAttachment = depthStencilAttachment.data(),
                .preserveAttachmentCount = static_cast<uint32_t>(preserveAttachments.size()),
                .pPreserveAttachments = preserveAttachments.data()
        };
}

VkCommandBufferBeginInfo vk::createVkCommandBufferBeginInfo(
        const VkCommandBufferUsageFlags        &flags
) {
        return {
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                .pNext = nullptr,
                .flags = flags,
                .pInheritanceInfo = nullptr
        };
}

VkRenderPassBeginInfo vk::createVkRenderPassBeginInfo(
        const VkRenderPass                     &renderPass,
        const VkFramebuffer                    &framebuffer,
        const VkExtent2D                       &extent,
        const std::vector<VkClearValue>        &clearValues
) {
        return {
                .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                .pNext = nullptr,
                .renderPass = renderPass,
                .framebuffer = framebuffer,
                .renderArea = {
                        .offset = {0, 0},
                        .extent = extent
                },
                .clearValueCount = static_cast<uint32_t>(clearValues.size()),
                .pClearValues = clearValues.data()
        };
}

VkSubmitInfo vk::createVkSubmitInfo(
        const std::vector<VkSemaphore>            &waitSemaphores,
        const VkPipelineStageFlags                *pWaitDstStageMask,
        const std::vector<VkCommandBuffer>        &commandBuffers,
        const std::vector<VkSemaphore>            &signalSemaphores
) {
        return {
                .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                .pNext = nullptr,
                .waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
                .pWaitSemaphores = waitSemaphores.data(),
                .pWaitDstStageMask = pWaitDstStageMask,
                .commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
                .pCommandBuffers = commandBuffers.data(),
                .signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size()),
                .pSignalSemaphores = signalSemaphores.data()
        };
}

VkPresentInfoKHR vk::createVkPresentInfoKHR(
        const std::vector<VkSemaphore>          &waitSemaphores,
        const std::vector<VkSwapchainKHR>       &swapchains,
        const std::vector<uint32_t>             &imageIndices
) {
        return {
                .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                .pNext = nullptr,
                .waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
                .pWaitSemaphores = waitSemaphores.data(),
                .swapchainCount = static_cast<uint32_t>(swapchains.size()),
                .pSwapchains = swapchains.data(),
                .pImageIndices = imageIndices.data(),
                .pResults = nullptr
        };
}

VkPushConstantRange vk::createVkPushConstantRange(
        const VkShaderStageFlags        &stageFlags,
        const uint32_t                  &offset,
        const uint32_t                  &size
) {
        return {
                .stageFlags = stageFlags,
                .offset = offset,
                .size = size
        };
}

VkVertexInputBindingDescription vk::createVkVertexInputBindingDescription(
        const uint32_t                 &binding,
        const uint32_t                 &size,
        const VkVertexInputRate        &inputRate
) {
        return {
                .binding = binding,
                .stride = size,
                .inputRate = inputRate
        };
}

VkVertexInputAttributeDescription vk::createVkVertexInputAttributeDescription(
        const uint32_t        &location,
        const uint32_t        &binding,
        const VkFormat        &format,
        const uint32_t        &offset
) {
        return {
                .location = location,
                .binding = binding,
                .format = format,
                .offset = offset
        };
}

VkMemoryAllocateInfo vk::createVkMemoryAllocateInfo(
        const uint64_t        &allocationSize,
        const uint32_t        &memoryTypeIndex
) {
        return {
                .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .pNext = nullptr,
                .allocationSize = allocationSize,
                .memoryTypeIndex = memoryTypeIndex
        };
}

VkExtent2D vk::createVkExtent2D(
        const uint32_t        &width,
        const uint32_t        &height
) {
        return {
                .width = width,
                .height = height
        };
}

VkBufferCopy vk::createVkBufferCopy(
        const size_t        &size
) {
        return {
                .srcOffset = 0,
                .dstOffset = 0,
                .size = size
        };
}

VkBufferCreateInfo vk::createVkBufferCreateInfo(
        const VkDeviceSize              &size,
        const VkBufferUsageFlags        &usage
) {
        return {
                .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkBufferCreateFlags(),
                .size = size,
                .usage = usage,
                .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .queueFamilyIndexCount = 0,
                .pQueueFamilyIndices = nullptr
        };
}

VkCommandBufferAllocateInfo vk::createVkCommandBufferAllocateInfo(
        const VkCommandPool        &commandPool
) {
        return {
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                .pNext = nullptr,
                .commandPool = commandPool,
                .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                .commandBufferCount = 1
        };
}

VkCommandPoolCreateInfo vk::createVkCommandPoolCreateInfo(
        const uint32_t        &queueFamilyIndex
) {
        return {
                .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                .pNext = nullptr,
                .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                .queueFamilyIndex = queueFamilyIndex
        };
}

VkDeviceQueueCreateInfo vk::createVkDeviceQueueCreateInfo(
        const uint32_t        &queueFamilyIndex,
        const float           *queuePriority
) {
        return {
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkDeviceQueueCreateFlags(),
                .queueFamilyIndex = queueFamilyIndex,
                .queueCount = 1,
                .pQueuePriorities = queuePriority
        };
}

VkDeviceCreateInfo vk::createVkDeviceCreateInfo(
        const std::vector<VkDeviceQueueCreateInfo>        &queueCreateInfos,
        const std::vector<const char *>                   &enabledExtensionNames
) {
        return {
                .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkDeviceCreateFlags(),
                .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
                .pQueueCreateInfos = queueCreateInfos.data(),
                .enabledLayerCount = 0,                /* Deprecated */
                .ppEnabledLayerNames = nullptr,        /* Deprecated */
                .enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size()),
                .ppEnabledExtensionNames = enabledExtensionNames.data(),
                .pEnabledFeatures = nullptr
        };
}

VkFenceCreateInfo vk::createVkFenceCreateInfo()
{
        return {
                .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VK_FENCE_CREATE_SIGNALED_BIT
        };
}

VkFramebufferCreateInfo vk::createVkFramebufferCreateInfo(
        const VkRenderPass                     &renderPass,
        const VkExtent2D                       &extent,
        const std::vector<VkImageView>         &imageViews
) {
        return {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkFramebufferCreateFlags(),
                .renderPass = renderPass,
                .attachmentCount = static_cast<uint32_t>(imageViews.size()),
                .pAttachments = imageViews.data(),
                .width = extent.width,
                .height = extent.height,
                .layers = 1
        };
}

VkImageViewCreateInfo vk::createVkImageViewCreateInfo(
        const VkImage         &image,
        const VkFormat        &format
) {
        return {
                .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkImageViewCreateFlags(),
                .image = image,
                .viewType = VK_IMAGE_VIEW_TYPE_2D,
                .format = format,
                .components = {
                        .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                        .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                        .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                        .a = VK_COMPONENT_SWIZZLE_IDENTITY
                },
                .subresourceRange = {
                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                        .baseMipLevel = 0,
                        .levelCount = 1,
                        .baseArrayLayer = 0,
                        .layerCount = 1
                },
        };
}

VkInstanceCreateInfo vk::createVkInstanceCreateInfo(
        const VkApplicationInfo                &applicationInfo,
        const std::vector<const char *>        &enabledLayerNames,
        const std::vector<const char *>        &enabledExtensionNames
) {
        return {
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkInstanceCreateFlags(),
                .pApplicationInfo = &applicationInfo,
                .enabledLayerCount = static_cast<uint32_t>(enabledLayerNames.size()),
                .ppEnabledLayerNames = enabledLayerNames.data(),
                .enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size()),
                .ppEnabledExtensionNames = enabledExtensionNames.data()
        };
}

VkGraphicsPipelineCreateInfo vk::createVkGraphicsPipelineCreateInfo(
        const VkPipelineVertexInputStateCreateInfo                &vertexInputStateCreateInfo,
        const VkPipelineInputAssemblyStateCreateInfo              &inputAssemblyStateCreateInfo,
        const VkPipelineViewportStateCreateInfo                   &viewportStateCreateInfo,
        const VkPipelineRasterizationStateCreateInfo              &rasterizationStateCreateInfo,
        const VkPipelineMultisampleStateCreateInfo                &multisampleStateCreateInfo,
        const VkPipelineColorBlendStateCreateInfo                 &colorBlendStateCreateInfo,
        const std::vector<VkPipelineShaderStageCreateInfo>        &shaderStages,
        const VkPipelineLayout                                    &layout,
        const VkRenderPass                                        &renderPass
) {
        return {
                .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineCreateFlags(),
                .stageCount = static_cast<uint32_t>(shaderStages.size()),
                .pStages = shaderStages.data(),
                .pVertexInputState = &vertexInputStateCreateInfo,
                .pInputAssemblyState = &inputAssemblyStateCreateInfo,
                .pTessellationState = nullptr,
                .pViewportState = &viewportStateCreateInfo,
                .pRasterizationState = &rasterizationStateCreateInfo,
                .pMultisampleState = &multisampleStateCreateInfo,
                .pDepthStencilState = nullptr,
                .pColorBlendState = &colorBlendStateCreateInfo,
                .pDynamicState = nullptr,
                .layout = layout,
                .renderPass = renderPass,
                .subpass = 0,
                .basePipelineHandle = nullptr,
                .basePipelineIndex = -1,
        };
}

VkPipelineLayoutCreateInfo vk::createVkPipelineLayoutCreateInfo(
        const std::vector<VkDescriptorSetLayout>        &setLayouts,
        const std::vector<VkPushConstantRange>          &pushConstantRanges
) {
        return {
                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkPipelineLayoutCreateFlags(),
                .setLayoutCount = static_cast<uint32_t>(setLayouts.size()),
                .pSetLayouts = setLayouts.data(),
                .pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size()),
                .pPushConstantRanges = pushConstantRanges.data()
        };
}

VkRenderPassCreateInfo vk::createVkRenderPassCreateInfo(
        const VkAttachmentDescription        &attachmentDescription,
        const VkSubpassDescription           &subpassDescription
) {
        return {
                .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkRenderPassCreateFlags(),
                .attachmentCount = 1,
                .pAttachments = &attachmentDescription,
                .subpassCount = 1,
                .pSubpasses = &subpassDescription,
                .dependencyCount = 0,
                .pDependencies = nullptr
        };
}

VkSemaphoreCreateInfo vk::createVkSemaphoreCreateInfo()
{
        return {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkSemaphoreCreateFlags()
        };
}

VkShaderModuleCreateInfo vk::createVkShaderModuleCreateInfo(
        const std::vector<uint8_t>        &code
) {
        return {
                .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkShaderModuleCreateFlags(),
                .codeSize = static_cast<uint32_t>(code.size()),
                .pCode = reinterpret_cast<const uint32_t *>(code.data())
        };
}

VkSwapchainCreateInfoKHR vk::createVkSwapchainCreateInfoKHR(
        const VkSurfaceCapabilitiesKHR        &capabilities,
        const uint32_t                        &minImageCount,
        const VkSurfaceFormatKHR              &format,
        const VkExtent2D                      &extent,
        const VkPresentModeKHR                &presentMode,
        const VkSurfaceKHR                    &surface,
        const VkSharingMode                   &sharingMode,
        const std::vector<uint32_t>           &queueFamilyIndices
) {

        return {
                .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                .pNext = nullptr,
                .flags = VkSwapchainCreateFlagsKHR(),
                .surface = surface,
                .minImageCount = minImageCount,
                .imageFormat = format.format,
                .imageColorSpace = format.colorSpace,
                .imageExtent = extent,
                .imageArrayLayers = 1,
                .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                .imageSharingMode = sharingMode,
                .queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size()),
                .pQueueFamilyIndices = queueFamilyIndices.data(),
                .preTransform = capabilities.currentTransform,
                .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                .presentMode = presentMode,
                .clipped = VK_TRUE,
                .oldSwapchain = nullptr
        };
}

VkDescriptorSetLayoutBinding vk::createVkDescriptorSetLayoutBinding(
        const uint32_t                  &binding,
        const VkDescriptorType          &descriptorType,
        const uint32_t                  &descriptorCount,
        const VkShaderStageFlags        &stageFlags,
        const VkSampler                 *pImmutableSamplers
) {
        return {
                .binding = binding,
                .descriptorType = descriptorType,
                .descriptorCount = descriptorCount,
                .stageFlags = stageFlags,
                .pImmutableSamplers = pImmutableSamplers
        };
}

VkDescriptorSetLayoutCreateInfo vk::createVkDescriptorSetLayoutCreateInfo(
        const std::vector<VkDescriptorSetLayoutBinding>        &bindings
) {
        return {
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkDescriptorSetLayoutCreateFlags(),
                .bindingCount = static_cast<uint32_t>(bindings.size()),
                .pBindings = bindings.data()
        };
}

VkDescriptorPoolSize vk::createVkDescriptorPoolSize(
        const VkDescriptorType        &type,
        const uint32_t                &descriptorCount
) {
        return {
                .type = type,
                .descriptorCount = descriptorCount
        };
}

VkDescriptorPoolCreateInfo vk::createVkDescriptorPoolCreateInfo(
        const uint32_t                                 &maxSets,
        const std::vector<VkDescriptorPoolSize>        &poolSizes
) {
        return {
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkDescriptorPoolCreateFlags(),
                .maxSets = maxSets,
                .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
                .pPoolSizes = poolSizes.data()
        };
}

VkDescriptorSetAllocateInfo vk::createVkDescriptorSetAllocateInfo(
        const VkDescriptorPool                          &descriptorPool,
        const std::vector<VkDescriptorSetLayout>        &setLayouts
) {
        return {
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                .pNext = nullptr,
                .descriptorPool = descriptorPool,
                .descriptorSetCount = static_cast<uint32_t>(setLayouts.size()),
                .pSetLayouts = setLayouts.data()
        };
}

VkDescriptorBufferInfo vk::createVkDescriptorBufferInfo(
        const VkBuffer            &buffer,
        const VkDeviceSize        &offset,
        const VkDeviceSize        &range
) {
        return {
                .buffer = buffer,
                .offset = offset,
                .range = range
        };
}

VkWriteDescriptorSet vk::createVkWriteDescriptorSet(
        const VkDescriptorSet               &dstSet,
        const uint32_t                      &dstBinding,
        const uint32_t                      &dstArrayElement,
        const uint32_t                      &descriptorCount,
        const VkDescriptorType              &descriptorType,
        const VkDescriptorImageInfo         *pImageInfo,
        const VkDescriptorBufferInfo        *pBufferInfo,
        const VkBufferView                  *pTexelBufferView
) {
        return {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext = nullptr,
                .dstSet = dstSet,
                .dstBinding = dstBinding,
                .dstArrayElement = dstArrayElement,
                .descriptorCount = descriptorCount,
                .descriptorType = descriptorType,
                .pImageInfo = pImageInfo,
                .pBufferInfo = pBufferInfo,
                .pTexelBufferView = pTexelBufferView
        };
}

VkBuffer vk::createVkBuffer(
        const VkDevice                     &device,
        const VkDeviceSize                 &size,
        const VkBufferUsageFlags           &usage,
        const VkAllocationCallbacks        *pAllocator
) {
        auto bufferCreateInfo = vk::createVkBufferCreateInfo(size, usage);

        VkBuffer buffer{};
        VkResult result = vkCreateBuffer(device, &bufferCreateInfo, pAllocator, &buffer);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create buffer!");

        return buffer;
}

VkCommandBuffer vk::createVkCommandBuffer(
        const VkCommandPool        &commandPool,
        const VkDevice             &device
) {
        auto commandBufferAllocateInfo = vk::createVkCommandBufferAllocateInfo(commandPool);

        VkCommandBuffer commandBuffer{};
        VkResult result = vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, &commandBuffer);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate command buffer!");

        return commandBuffer;
}

VkCommandPool vk::createVkCommandPool(
        const uint32_t                     &queueFamilyIndex,
        const VkDevice                     &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto commandPoolCreateInfo = vk::createVkCommandPoolCreateInfo(
                queueFamilyIndex
        );

        VkCommandPool commandPool{};
        VkResult result = vkCreateCommandPool(device, &commandPoolCreateInfo, pAllocator, &commandPool);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create command pool!");

        return commandPool;
}

VkDescriptorPool vk::createVkDescriptorPool(
        const VkDevice                                 &device,
        const uint32_t                                 &descriptorCount,
        const std::vector<VkDescriptorPoolSize>        &poolSizes,
        const VkAllocationCallbacks                    *pAllocator
) {
        auto poolInfo = vk::createVkDescriptorPoolCreateInfo(
                descriptorCount, poolSizes
        );

        VkDescriptorPool descriptorPool;
        VkResult result = vkCreateDescriptorPool(
                device, &poolInfo,
                pAllocator, &descriptorPool
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create descriptor pool!");

        return descriptorPool;
}

std::vector<VkDescriptorSet> vk::createVkDescriptorSets(
        const VkDevice                                  &device,
        const VkDescriptorPool                          &pool,
        const std::vector<VkDescriptorSetLayout>        &descriptorSetLayouts
) {
        auto allocateInfo = vk::createVkDescriptorSetAllocateInfo(
                pool, descriptorSetLayouts
        );

        std::vector<VkDescriptorSet> descriptorSets(descriptorSetLayouts.size());
        VkResult result = vkAllocateDescriptorSets(
                device, &allocateInfo, descriptorSets.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate descriptor sets!");

        return descriptorSets;
}

VkDescriptorSetLayout vk::createVkDescriptorSetLayout(
        const VkDevice                                         &device,
        const std::vector<VkDescriptorSetLayoutBinding>        &bindings,
        const VkAllocationCallbacks                            *pAllocator
) {
        auto setLayoutCreateInfo = vk::createVkDescriptorSetLayoutCreateInfo(
                bindings
        );

        VkDescriptorSetLayout descriptorSetLayout;
        VkResult result = vkCreateDescriptorSetLayout(
                device, &setLayoutCreateInfo,
                pAllocator, &descriptorSetLayout
        );

        if (result != VK_SUCCESS) {
                throw std::runtime_error("Could not create descriptor set layout!");
        }

        return descriptorSetLayout;
}

VkDevice vk::createVkDevice(
        const VkPhysicalDevice                 &physicalDevice,
        const std::vector<uint32_t>            &queueFamilyIndices,
        const std::vector<const char *>        &enabledExtensionNames,
        const VkAllocationCallbacks            *pAllocator
) {
        float queuePriority = 1.0f;

        std::set<uint32_t> tmp(queueFamilyIndices.begin(), queueFamilyIndices.end());
        std::vector<uint32_t> fixedIndices(tmp.begin(), tmp.end());

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        for (const uint32_t &familyIndex : fixedIndices)
                queueCreateInfos.push_back(vk::createVkDeviceQueueCreateInfo(
                        familyIndex, &queuePriority
                ));

        auto deviceCreateInfo = vk::createVkDeviceCreateInfo(
                queueCreateInfos, enabledExtensionNames
        );

        VkDevice device{};
        VkResult result = vkCreateDevice(
                physicalDevice, &deviceCreateInfo,
                pAllocator, &device
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create logical device!");

        return device;
}

VkFence vk::createVkFence(
        const VkDevice                     &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto fenceCreateInfo = vk::createVkFenceCreateInfo();

        VkFence fence{};
        VkResult result = vkCreateFence(
                device, &fenceCreateInfo,
                pAllocator, &fence
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create fence!");

        return fence;
}

VkFramebuffer vk::createVkFramebuffer(
        const VkRenderPass                     &renderPass,
        const VkExtent2D                       &extent,
        const std::vector<VkImageView>         &imageViews,
        const VkDevice                         &device,
        const VkAllocationCallbacks            *pAllocator
) {
        auto framebufferCreateInfo = vk::createVkFramebufferCreateInfo(
                renderPass, extent, imageViews
        );

        VkFramebuffer framebuffer{};
        VkResult result = vkCreateFramebuffer(
                device, &framebufferCreateInfo,
                pAllocator, &framebuffer
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create frame buffer!");

        return framebuffer;
}

VkImageView vk::createVkImageView(
        const VkImage                      &image,
        const VkFormat                     &format,
        const VkDevice                     &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto imageCreateInfo = vk::createVkImageViewCreateInfo(
                image, format
        );

        VkImageView imageView{};
        VkResult result = vkCreateImageView(
                device, &imageCreateInfo,
                pAllocator, &imageView
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create image view!");

        return imageView;
}

VkInstance vk::createVkInstance(
        const char                             *name,
        const uint32_t                         &version,
        const std::vector<const char *>        &enabledLayerNames,
        const std::vector<const char *>        &enabledExtensionNames,
        const VkAllocationCallbacks            *pAllocator
) {
        uint32_t apiVersion = 0;
        VkResult result = vkEnumerateInstanceVersion(&apiVersion);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get api version!");

        VkApplicationInfo appInfo = vk::createVkApplicationInfo(
                name, version, apiVersion
        );

        VkInstanceCreateInfo instanceInfo = vk::createVkInstanceCreateInfo(
                appInfo, enabledLayerNames, enabledExtensionNames
        );

        VkInstance instance{};
        result = vkCreateInstance(&instanceInfo, pAllocator, &instance);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create vulkan instance!");

        return instance;
}

VkPipeline vk::createVkPipeline(
        const VkDevice                                              &device,
        const VkRenderPass                                          &renderPass,
        const std::vector<VkViewport>                               &viewports,
        const std::vector<VkRect2D>                                 &scissors,
        const VkPipelineLayout                                      &layout,
        const std::vector<VkPipelineShaderStageCreateInfo>          &shaderStages,
        const std::vector<VkVertexInputBindingDescription>          &bindingDescriptions,
        const std::vector<VkVertexInputAttributeDescription>        &attributeDescriptions,
        const VkAllocationCallbacks                                 *pAllocator
) {
        auto vertexInputStateCreateInfo = vk::createVkPipelineVertexInputStateCreateInfo(
                bindingDescriptions, attributeDescriptions
        );

        auto inputAssemblyStateCreateInfo = vk::createVkPipelineInputAssemblyStateCreateInfo();

        auto viewportStateCreateInfo = vk::createVkPipelineViewportStateCreateInfo(
                viewports, scissors
        );

        auto rasterizationStateCreateInfo = vk::createVkPipelineRasterizationStateCreateInfo();

        auto multisampleStateCreateInfo = vk::createVkPipelineMultisampleStateCreateInfo();

        auto colorBlendAttachmentState = vk::createVkPipelineColorBlendAttachmentState();

        auto colorBlendStateCreateInfo = vk::createVkPipelineColorBlendStateCreateInfo(
                colorBlendAttachmentState
        );

        VkGraphicsPipelineCreateInfo pipelineCreateInfo = vk::createVkGraphicsPipelineCreateInfo(
                vertexInputStateCreateInfo, inputAssemblyStateCreateInfo,
                viewportStateCreateInfo, rasterizationStateCreateInfo,
                multisampleStateCreateInfo, colorBlendStateCreateInfo,
                shaderStages, layout, renderPass
        );

        VkPipeline pipeline{};
        VkResult result = vkCreateGraphicsPipelines(
                device, nullptr,
                1, &pipelineCreateInfo,
                pAllocator, &pipeline
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create graphic pipeline!");

        return pipeline;
}

VkPipelineLayout vk::createVkPipelineLayout(
        const VkDevice                                  &device,
        const std::vector<VkDescriptorSetLayout>        &setLayouts,
        const std::vector<VkPushConstantRange>          &pushConstantRanges,
        const VkAllocationCallbacks                     *pAllocator
) {
        auto layoutCreateInfo = vk::createVkPipelineLayoutCreateInfo(
                setLayouts, pushConstantRanges
        );

        VkPipelineLayout layout{};
        VkResult result = vkCreatePipelineLayout(
                device, &layoutCreateInfo,
                pAllocator, &layout
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create pipeline layout!");

        return layout;
}

VkRenderPass vk::createVkRenderPass(
        const VkPhysicalDevice             &physicalDevice,
        const VkDevice                     &device,
        const VkSurfaceKHR                 &surface,
        const VkAllocationCallbacks        *pAllocator
) {
        uint32_t formatsCount = 0;
        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(
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

        VkFormat format = formats[0].format;
        for (const VkSurfaceFormatKHR &f : formats)
                if (f.format == VK_FORMAT_R8G8B8A8_UNORM && f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                        format = f.format;
                        break;
                }

        auto attachmentDescription = vk::createVkAttachmentDescription(
                format
        );

        std::vector attachmentReferences { vk::createVkAttachmentReference(
                0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        )};
        auto subpassDescription = vk::createVkSubpassDescription(
                {}, attachmentReferences,
                {}, {}, {}
        );
        auto renderPassCreateInfo = vk::createVkRenderPassCreateInfo(
                attachmentDescription, subpassDescription
        );

        VkRenderPass renderPass{};
        result = vkCreateRenderPass(
                device, &renderPassCreateInfo,
                pAllocator, &renderPass
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create pipeline render pass!");

        return renderPass;
}

VkSemaphore vk::createVkSemaphore(
        const VkDevice                     &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto semaphoreCreateInfo = vk::createVkSemaphoreCreateInfo();

        VkSemaphore semaphore{};
        VkResult result = vkCreateSemaphore(
                device, &semaphoreCreateInfo,
                pAllocator, &semaphore
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create semaphore!");

        return semaphore;
}

VkShaderModule vk::createVkShaderModule(
        const std::vector<uint8_t>         &code,
        const VkDevice                     &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto shaderModuleCreateInfo = vk::createVkShaderModuleCreateInfo(
                code
        );

        VkShaderModule shaderModule{};
        VkResult result = vkCreateShaderModule(
                device, &shaderModuleCreateInfo,
                pAllocator, &shaderModule
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Failed to create shader module!");

        return shaderModule;
}

VkSwapchainKHR vk::createVkSwapchainKHR(
        const VkDevice                             &device,
        const VkSurfaceKHR                         &surface,
        const std::vector<VkPresentModeKHR>        &presentModes,
        const VkSurfaceCapabilitiesKHR             &capabilities,
        const std::vector<uint32_t>                &queueFamilyIndices,
        const VkSurfaceFormatKHR                   &format,
        const VkExtent2D                           &extent,
        const VkAllocationCallbacks                *pAllocator
) {
        uint32_t imageCount = std::min(capabilities.maxImageCount, capabilities.minImageCount + 1);
        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

        for (const VkPresentModeKHR p : presentModes)
                if (p == VK_PRESENT_MODE_MAILBOX_KHR) {
                        presentMode = p;
                        break;
                }

        std::set tmp(queueFamilyIndices.begin(), queueFamilyIndices.end());
        std::vector fixedIndices(tmp.begin(), tmp.end());

        VkSharingMode sharingMode = fixedIndices.size() == 1 ?
                VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;

        VkSwapchainCreateInfoKHR createInfo = vk::createVkSwapchainCreateInfoKHR(
                capabilities, imageCount,
                format, extent, presentMode,
                surface, sharingMode, fixedIndices
        );

        VkSwapchainKHR swapchain{};
        VkResult result = vkCreateSwapchainKHR(
                device, &createInfo,
                pAllocator, &swapchain
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create swapchain.");

        return swapchain;
}