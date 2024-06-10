#include "vulkan++.hpp"

#include <stdexcept>
#include <set>

using namespace vk;

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
        const VkOffset2D        &offset,
        const VkExtent2D        &extent
) {
        return {
                .offset = offset,
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
                .renderArea = vk::createVkRect2D(
                        vk::createVkOffset2D(0, 0), extent
                ),
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
        const std::vector<const char *>                   &enabledExtensionNames,
        const VkPhysicalDeviceFeatures                    *pEnabledFeatures
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
                .pEnabledFeatures = pEnabledFeatures
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
                .components = vk::createVkComponentMapping(
                        VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                        VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY
                ),
                .subresourceRange = vk::createVkImageSubresourceRange(
                        VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1
                ),
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

VkBufferViewCreateInfo vk::createVkBufferViewCreateInfo(
        const VkBuffer            &buffer,
        const VkFormat            &format,
        const VkDeviceSize        &offset,
        const VkDeviceSize        &range
) {
        return {
                .sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkBufferViewCreateFlags(),
                .buffer = buffer,
                .format = format,
                .offset = offset,
                .range = range
        };
}

VkImageCreateInfo vk::createVkImageCreateInfo(
        const VkImageType                  &imageType,
        const VkFormat                     &format,
        const VkExtent3D                   &extent,
        const VkImageUsageFlags            &usage,
        const std::vector<uint32_t>        &queueFamilyIndices
) {
        return {
                .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkImageCreateFlags(),
                .imageType = imageType,
                .format = format,
                .extent = extent,
                .mipLevels = 1,
                .arrayLayers = 1,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .tiling = VK_IMAGE_TILING_OPTIMAL,
                .usage = usage,
                .sharingMode = queueFamilyIndices.size() == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,
                .queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size()),
                .pQueueFamilyIndices = queueFamilyIndices.data(),
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
        };
}

VkImageMemoryBarrier vk::createVkImageMemoryBarrier(
        const VkAccessFlags              &srcAccessMask,
        const VkAccessFlags              &dstAccessMask,
        const VkImageLayout              &oldLayout,
        const VkImageLayout              &newLayout,
        const uint32_t                   &srcQueueFamilyIndex,
        const uint32_t                   &dstQueueFamilyIndex,
        const VkImage                    &image
) {
        return {
                .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                .pNext = nullptr,
                .srcAccessMask = srcAccessMask,
                .dstAccessMask = dstAccessMask,
                .oldLayout = oldLayout,
                .newLayout = newLayout,
                .srcQueueFamilyIndex = srcQueueFamilyIndex,
                .dstQueueFamilyIndex = dstQueueFamilyIndex,
                .image = image,
                .subresourceRange = vk::createVkImageSubresourceRange(
                        VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1
                )
        };
}

VkImageSubresourceRange vk::createVkImageSubresourceRange(
        const VkImageAspectFlags        &aspectMask,
        const uint32_t                  &baseMipLevel,
        const uint32_t                  &levelCount,
        const uint32_t                  &baseArrayLayer,
        const uint32_t                  &layerCount
) {
        return {
                .aspectMask = aspectMask,
                .baseMipLevel = baseMipLevel,
                .levelCount = levelCount,
                .baseArrayLayer = baseArrayLayer,
                .layerCount = layerCount
        };
}

VkImageSubresourceLayers vk::createVkImageSubresourceLayers(
        const VkImageAspectFlags        &aspectMask,
        const uint32_t                  &mipLevel,
        const uint32_t                  &baseArrayLayer,
        const uint32_t                  &layerCount
) {
        return {
                .aspectMask = aspectMask,
                .mipLevel = mipLevel,
                .baseArrayLayer = baseArrayLayer,
                .layerCount = layerCount
        };
}

VkBufferImageCopy vk::createVkBufferImageCopy(
        const VkDeviceSize                    &bufferOffset,
        const uint32_t                        &bufferRowLength,
        const uint32_t                        &bufferImageHeight,
        const VkExtent3D                      &imageExtent
) {
        return {
                .bufferOffset = bufferOffset,
                .bufferRowLength = bufferRowLength,
                .bufferImageHeight = bufferImageHeight,
                .imageSubresource = vk::createVkImageSubresourceLayers(
                        VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1
                ),
                .imageOffset = vk::createVkOffset3D(0, 0, 0),
                .imageExtent = imageExtent
        };
}

VkExtent3D vk::createVkExtent3D(
        const uint32_t        &width,
        const uint32_t        &height,
        const uint32_t        &depth
) {
        return {
                .width = width,
                .height = height,
                .depth = depth
        };
}

VkOffset2D vk::createVkOffset2D(
        const int32_t &x,
        const int32_t &y
) {
        return {
                .x = x,
                .y = y
        };
}

VkOffset3D vk::createVkOffset3D(
        const int32_t &x,
        const int32_t &y,
        const int32_t &z
) {
        return {
                .x = x,
                .y = y,
                .z = z
        };
}

VkComponentMapping vk::createVkComponentMapping(
        const VkComponentSwizzle        &r,
        const VkComponentSwizzle        &g,
        const VkComponentSwizzle        &b,
        const VkComponentSwizzle        &a
) {
        return {
                .r = r,
                .g = g,
                .b = b,
                .a = a
        };
}

VkSamplerCreateInfo vk::createVkSamplerCreateInfo(
        const VkFilter                    &filter,
        const VkSamplerAddressMode        &addressMode,
        const VkBool32                    &anisotropyEnable,
        const float                       &maxAnisotropy,
        const VkBool32                    &compareEnable,
        const VkCompareOp                 &compareOp
) {
        return {
                .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                .pNext = nullptr,
                .flags = VkSamplerCreateFlags(),
                .magFilter = filter,
                .minFilter = filter,
                .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                .addressModeU = addressMode,
                .addressModeV = addressMode,
                .addressModeW = addressMode,
                .mipLodBias = 0.0f,
                .anisotropyEnable = anisotropyEnable,
                .maxAnisotropy = maxAnisotropy,
                .compareEnable = compareEnable,
                .compareOp = compareOp,
                .minLod = 0.0f,
                .maxLod = 0.0f,
                .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
                .unnormalizedCoordinates = VK_FALSE
        };
}

VkDescriptorImageInfo vk::createVkDescriptorImageInfo(
        const VkSampler            &sampler,
        const VkImageView          &imageView,
        const VkImageLayout        &imageLayout
) {
        return {
                .sampler = sampler,
                .imageView = imageView,
                .imageLayout = imageLayout
        };
}

VkAccelerationStructureCreateInfoNV vk::createVkAccelerationStructureCreateInfoNV(
        const VkDeviceSize                         &compactedSize,
        const VkAccelerationStructureInfoNV        &info
) {
        return {
                .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV,
                .pNext = nullptr,
                .compactedSize = compactedSize,
                .info = info
        };
}

VkAccelerationStructureInfoNV vk::createVkAccelerationStructureInfoNV(
        const VkAccelerationStructureTypeNV              &type,
        const uint32_t                                   &instanceCount,
        const std::vector<VkGeometryNV>                  &geometries
) {
        return {
                .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV,
                .pNext = nullptr,
                .type = type,
                .flags = VkBuildAccelerationStructureFlagsNV(),
                .instanceCount = instanceCount,
                .geometryCount = static_cast<uint32_t>(geometries.size()),
                .pGeometries = geometries.data()
        };
}

VkPhysicalDeviceProperties vk::getVkPhysicalDeviceProperties(
        const VkPhysicalDevice        &physicalDevice
) {
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);

        return properties;
}

VkPhysicalDeviceMemoryProperties vk::getVkPhysicalDeviceMemoryProperties(
        const VkPhysicalDevice        &physicalDevice
) {
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);

        return physicalDeviceMemoryProperties;
}

VkSurfaceCapabilitiesKHR vk::getVkSurfaceCapabilitiesKHR(
        const VkPhysicalDevice        &physicalDevice,
        const VkSurfaceKHR            &surface
) {
        VkSurfaceCapabilitiesKHR capabilities{};
        VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get physical device surface capabilities!");

        return capabilities;
}

std::vector<VkSurfaceFormatKHR> vk::getVkSurfaceFormatKHRs(
        const VkPhysicalDevice        &physicalDevice,
        const VkSurfaceKHR            &surface
) {
        uint32_t formatsCount = 0;
        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, nullptr
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get surface formats count!");

        std::vector<VkSurfaceFormatKHR> formats(formatsCount);
        result = vkGetPhysicalDeviceSurfaceFormatsKHR(
                physicalDevice, surface,
                &formatsCount, formats.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get surface formats.");

        return formats;
}

std::vector<VkPresentModeKHR> vk::getVkPresentModeKHR(
        const VkPhysicalDevice        &physicalDevice,
        const VkSurfaceKHR            &surface
) {
        uint32_t presentModesCount = 0;
        VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                physicalDevice, surface,
                &presentModesCount, nullptr
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get present mode count.");

        std::vector<VkPresentModeKHR> presentModes(presentModesCount);
        result = vkGetPhysicalDeviceSurfacePresentModesKHR(
                physicalDevice, surface,
                &presentModesCount, presentModes.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get present modes.");

        return presentModes;
}

Buffer vk::createVkBuffer(
        const Device                       &device,
        const VkDeviceSize                 &size,
        const VkBufferUsageFlags           &usage,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkBufferCreateInfo(size, usage);

        Buffer buffer{};
        VkResult result = vkCreateBuffer(device, &createInfo, pAllocator, &buffer);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create buffer!");

        return buffer;
}

BufferView vk::createVkBufferView(
        const Device                       &device,
        const Buffer                       &buffer,
        const VkFormat                     &format,
        const VkDeviceSize                 &offset,
        const VkDeviceSize                 &range,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkBufferViewCreateInfo(
                buffer, format, offset, range
        );

        BufferView bufferView{};
        VkResult result = vkCreateBufferView(device, &createInfo, pAllocator, &bufferView);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate command buffer view!");

        return bufferView;
}

CommandBuffer vk::createVkCommandBuffer(
        const CommandPool          &commandPool,
        const Device               &device
) {
        auto allocateInfo = vk::createVkCommandBufferAllocateInfo(commandPool);

        CommandBuffer commandBuffer{};
        VkResult result = vkAllocateCommandBuffers(
                device, &allocateInfo, &commandBuffer
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate command buffer!");

        return commandBuffer;
}

CommandPool vk::createVkCommandPool(
        const uint32_t                     &queueFamilyIndex,
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkCommandPoolCreateInfo(
                queueFamilyIndex
        );

        CommandPool commandPool{};
        VkResult result = vkCreateCommandPool(device, &createInfo, pAllocator, &commandPool);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create command pool!");

        return commandPool;
}

DescriptorPool vk::createVkDescriptorPool(
        const Device                                   &device,
        const uint32_t                                 &descriptorCount,
        const std::vector<VkDescriptorPoolSize>        &poolSizes,
        const VkAllocationCallbacks                    *pAllocator
) {
        auto createInfo = vk::createVkDescriptorPoolCreateInfo(
                descriptorCount, poolSizes
        );

        DescriptorPool descriptorPool;
        VkResult result = vkCreateDescriptorPool(
                device, &createInfo,
                pAllocator, &descriptorPool
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create descriptor pool!");

        return descriptorPool;
}

std::vector<DescriptorSet> vk::createVkDescriptorSets(
        const Device                                    &device,
        const VkDescriptorPool                          &pool,
        const std::vector<VkDescriptorSetLayout>        &descriptorSetLayouts
) {
        auto allocateInfo = vk::createVkDescriptorSetAllocateInfo(
                pool, descriptorSetLayouts
        );

        std::vector<DescriptorSet> descriptorSets(descriptorSetLayouts.size());
        VkResult result = vkAllocateDescriptorSets(
                device, &allocateInfo, descriptorSets.data()
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not allocate descriptor sets!");

        return descriptorSets;
}

DescriptorSetLayout vk::createVkDescriptorSetLayout(
        const VkDevice                                         &device,
        const std::vector<VkDescriptorSetLayoutBinding>        &bindings,
        const VkAllocationCallbacks                            *pAllocator
) {
        auto createInfo = vk::createVkDescriptorSetLayoutCreateInfo(
                bindings
        );

        DescriptorSetLayout descriptorSetLayout;
        VkResult result = vkCreateDescriptorSetLayout(
                device, &createInfo,
                pAllocator, &descriptorSetLayout
        );

        if (result != VK_SUCCESS) {
                throw std::runtime_error("Could not create descriptor set layout!");
        }

        return descriptorSetLayout;
}

Device vk::createVkDevice(
        const PhysicalDevice                   &physicalDevice,
        const std::vector<uint32_t>            &queueFamilyIndices,
        const std::vector<const char *>        &enabledExtensionNames,
        const VkPhysicalDeviceFeatures         *pEnabledFeatures,
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

        auto createInfo = vk::createVkDeviceCreateInfo(
                queueCreateInfos, enabledExtensionNames, pEnabledFeatures
        );

        Device device{};
        VkResult result = vkCreateDevice(
                physicalDevice, &createInfo,
                pAllocator, &device
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create logical device!");

        return device;
}

Fence vk::createVkFence(
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkFenceCreateInfo();

        Fence fence{};
        VkResult result = vkCreateFence(
                device, &createInfo,
                pAllocator, &fence
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create fence!");

        return fence;
}

Framebuffer vk::createVkFramebuffer(
        const RenderPass                      &renderPass,
        const VkExtent2D                      &extent,
        const std::vector<VkImageView>        &imageViews,
        const Device                          &device,
        const VkAllocationCallbacks           *pAllocator
) {
        auto createInfo = vk::createVkFramebufferCreateInfo(
                renderPass, extent, imageViews
        );

        Framebuffer framebuffer{};
        VkResult result = vkCreateFramebuffer(
                device, &createInfo,
                pAllocator, &framebuffer
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create frame buffer!");

        return framebuffer;
}

Image vk::createVkImage(
        const Device                       &device,
        const VkImageType                  &imageType,
        const VkFormat                     &format,
        const VkExtent3D                   &extent,
        const VkImageUsageFlags            &usage,
        const std::vector<uint32_t>        &queueFamilyIndices,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkImageCreateInfo(
                imageType, format, extent, usage, queueFamilyIndices
        );

        Image image{};
        VkResult result = vkCreateImage(device, &createInfo, pAllocator, &image);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create image!");

        return image;
}

ImageView vk::createVkImageView(
        const Image                        &image,
        const VkFormat                     &format,
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkImageViewCreateInfo(
                image, format
        );

        ImageView imageView{};
        VkResult result = vkCreateImageView(
                device, &createInfo,
                pAllocator, &imageView
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create image view!");

        return imageView;
}

Instance vk::createVkInstance(
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

        VkInstanceCreateInfo createInfo = vk::createVkInstanceCreateInfo(
                appInfo, enabledLayerNames, enabledExtensionNames
        );

        Instance instance{};
        result = vkCreateInstance(&createInfo, pAllocator, &instance);

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create vulkan instance!");

        return instance;
}

std::vector<PhysicalDevice> vk::getVkPhysicalDevices(
        const Instance        &instance
) {
        uint32_t physicalDevicesCount = 0;
        VkResult result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr);

        if (result != VK_SUCCESS && result != VK_INCOMPLETE)
                throw std::runtime_error("Could not get physical devices count!");

        std::vector<PhysicalDevice> physicalDevices(physicalDevicesCount);
        result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not get physical devices!");

        return physicalDevices;
}

Pipeline vk::createVkPipeline(
        const Device                                                &device,
        const RenderPass                                            &renderPass,
        const std::vector<VkViewport>                               &viewports,
        const std::vector<VkRect2D>                                 &scissors,
        const PipelineLayout                                        &layout,
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

        VkGraphicsPipelineCreateInfo createInfo = vk::createVkGraphicsPipelineCreateInfo(
                vertexInputStateCreateInfo,
                inputAssemblyStateCreateInfo,
                viewportStateCreateInfo,
                rasterizationStateCreateInfo,
                multisampleStateCreateInfo,
                colorBlendStateCreateInfo,
                shaderStages, layout, renderPass
        );

        Pipeline pipeline{};
        VkResult result = vkCreateGraphicsPipelines(
                device, nullptr,
                1, &createInfo,
                pAllocator, &pipeline
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create graphic pipeline!");

        return pipeline;
}

PipelineLayout vk::createVkPipelineLayout(
        const Device                                  &device,
        const std::vector<DescriptorSetLayout>        &setLayouts,
        const std::vector<VkPushConstantRange>        &pushConstantRanges,
        const VkAllocationCallbacks                   *pAllocator
) {
        auto createInfo = vk::createVkPipelineLayoutCreateInfo(
                setLayouts, pushConstantRanges
        );

        PipelineLayout layout{};
        VkResult result = vkCreatePipelineLayout(
                device, &createInfo,
                pAllocator, &layout
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create pipeline layout!");

        return layout;
}

Queue vk::getVkQueue(
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

RenderPass vk::createVkRenderPass(
        const PhysicalDevice               &physicalDevice,
        const Device                       &device,
        const SurfaceKHR                   &surface,
        const VkSurfaceFormatKHR           &requiredFormat,
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
                if (f.format == requiredFormat.format && f.colorSpace == requiredFormat.colorSpace) {
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
        auto createInfo = vk::createVkRenderPassCreateInfo(
                attachmentDescription, subpassDescription
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

Sampler vk::createVkSampler(
        const Device                      &device,
        const VkFilter                    &filter,
        const VkSamplerAddressMode        &addressMode,
        const VkBool32                    &anisotropyEnable,
        const float                       &maxAnisotropy,
        const VkBool32                    &compareEnable,
        const VkCompareOp                 &compareOp
) {
        auto createInfo = vk::createVkSamplerCreateInfo(
                filter, addressMode, anisotropyEnable,
                maxAnisotropy, compareEnable, compareOp
        );

        Sampler sampler{};
        VkResult result = vkCreateSampler(
                device, &createInfo,
                nullptr, &sampler
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create sampler!");

        return sampler;
}

Semaphore vk::createVkSemaphore(
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkSemaphoreCreateInfo();

        Semaphore semaphore{};
        VkResult result = vkCreateSemaphore(
                device, &createInfo,
                pAllocator, &semaphore
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create semaphore!");

        return semaphore;
}

ShaderModule vk::createVkShaderModule(
        const std::vector<uint8_t>         &code,
        const Device                       &device,
        const VkAllocationCallbacks        *pAllocator
) {
        auto createInfo = vk::createVkShaderModuleCreateInfo(
                code
        );

        ShaderModule shaderModule{};
        VkResult result = vkCreateShaderModule(
                device, &createInfo,
                pAllocator, &shaderModule
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Failed to create shader module!");

        return shaderModule;
}

SwapchainKHR vk::createVkSwapchainKHR(
        const Device                               &device,
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

        SwapchainKHR swapchain{};
        VkResult result = vkCreateSwapchainKHR(
                device, &createInfo,
                pAllocator, &swapchain
        );

        if (result != VK_SUCCESS)
                throw std::runtime_error("Could not create swapchain.");

        return swapchain;
}