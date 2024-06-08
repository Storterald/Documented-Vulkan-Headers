#pragma once

#ifndef VULKANPP_HPP_HEADER
#define VULKANPP_HPP_HEADER

#include <vulkan/vulkan.h>
#include <vector>

namespace vk {

        /** <b>Name</b><hr><br>
         *
         * VkApplicationInfo - Structure specifying application information<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkApplicationInfo structure is defined as:
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkApplicationInfo {
         *     VkStructureType    sType;
         *     const void*        pNext;
         *     const char*        pApplicationName;
         *     uint32_t           applicationVersion;
         *     const char*        pEngineName;
         *     uint32_t           engineVersion;
         *     uint32_t           apiVersion;
         * } VkApplicationInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>pApplicationName is NULL or is a pointer to a null-terminated UTF-8 string containing the name of the application.
         * <li>applicationVersion is an unsigned integer variable containing the developer-supplied version number of the application.
         * <li>pEngineName is NULL or is a pointer to a null-terminated UTF-8 string containing the name of the engine (if any) used to create the application.
         * <li>engineVersion is an unsigned integer variable containing the developer-supplied version number of the engine used to create the application.
         * <li>apiVersion <b>must</b> be the highest version of Vulkan that the application is designed to use, encoded as described in https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#extendingvulkan-coreversions-versionnumbers. The patch version number specified in apiVersion is ignored when creating an instance object. The variant version of the instance <b>must</b> match that requested in apiVersion.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Vulkan 1.0 implementations were required to return VK_ERROR_INCOMPATIBLE_DRIVER if apiVersion was larger than 1.0. Implementations that support Vulkan 1.1 or later <b>must</b> not return VK_ERROR_INCOMPATIBLE_DRIVER for any value of apiVersion .
         *
         * @note Because Vulkan 1.0 implementations <b>may</b> fail with VK_ERROR_INCOMPATIBLE_DRIVER, applications <b>should</b> determine the version of Vulkan available before calling vkCreateInstance. If the vkGetInstanceProcAddr returns NULL for vkEnumerateInstanceVersion, it is a Vulkan 1.0 implementation. Otherwise, the application <b>can</b> call vkEnumerateInstanceVersion to determine the version of Vulkan.
         *
         * As long as the instance supports at least Vulkan 1.1, an application <b>can</b> use different versions of Vulkan with an instance than it does with a device or physical device.
         *
         * @note The Khronos validation layers will treat apiVersion as the highest API version the application targets, and will validate API usage against the minimum of that version and the implementation version (instance or device, depending on context). If an application tries to use functionality from a greater version than this, a validation error will be triggered.<br><br>
                 For example, if the instance supports Vulkan 1.1 and three physical devices support Vulkan 1.0, Vulkan 1.1, and Vulkan 1.2, respectively, and if the application sets apiVersion to 1.2, the application <b>can</b> use the following versions of Vulkan:
                 <ul>
                 <li>Vulkan 1.0 <b>can</b> be used with the instance and with all physical devices.
                 <li>Vulkan 1.1 <b>can</b> be used with the instance and with the physical devices that support Vulkan 1.1 and Vulkan 1.2.
                 <li>Vulkan 1.2 <b>can</b> be used with the physical device that supports Vulkan 1.2.
                 </ul>
                 If we modify the above example so that the application sets apiVersion to 1.1, then the application <b>must</b> not use Vulkan 1.2 functionality on the physical device that supports Vulkan 1.2.
         *
         * @note Providing a NULL VkInstanceCreateInfo::pApplicationInfo or providing an apiVersion of 0 is equivalent to providing an apiVersion of VK_MAKE_API_VERSION(0,1,0,0).
         */
        VkApplicationInfo createVkApplicationInfo(
                const char            *pApplicationName,
                const uint32_t        &applicationVersion,
                const uint32_t        &version
        );
        /** <b>Name</b><hr><br>
         *
         * VkPipelineVertexInputStateCreateInfo - Structure specifying parameters of a newly created pipeline vertex input state<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineVertexInputStateCreateInfo structure is defined as:
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineVertexInputStateCreateInfo {
         *     VkStructureType                             sType;
         *     const void*                                 pNext;
         *     VkPipelineVertexInputStateCreateFlags       flags;
         *     uint32_t                                    vertexBindingDescriptionCount;
         *     const VkVertexInputBindingDescription*      pVertexBindingDescriptions;
         *     uint32_t                                    vertexAttributeDescriptionCount;
         *     const VkVertexInputAttributeDescription*    pVertexAttributeDescriptions;
         * } VkPipelineVertexInputStateCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>vertexBindingDescriptionCount is the number of vertex binding descriptions provided in pVertexBindingDescriptions.
         * <li>pVertexBindingDescriptions is a pointer to an array of VkVertexInputBindingDescription structures.
         * <li>vertexAttributeDescriptionCount is the number of vertex attribute descriptions provided in pVertexAttributeDescriptions.
         * <li>pVertexAttributeDescriptions is a pointer to an array of VkVertexInputAttributeDescription structures.
         * </ul>
         */
        VkPipelineVertexInputStateCreateInfo createVkPipelineVertexInputStateCreateInfo(
                const std::vector<VkVertexInputBindingDescription>          &bindingDescriptions,
                const std::vector<VkVertexInputAttributeDescription>        &attributeDescriptions
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipelineInputAssemblyStateCreateInfo - Structure specifying parameters of a newly created pipeline input assembly state<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Drawing can be achieved in two modes:<br><br>
         *
         * <li>Programmable Mesh Shading, the mesh shader assembles primitives, or<br>
         * <li>Programmable Primitive Shading, the input primitives are assembled as follows.<br><br>
         *
         * Each draw is made up of zero or more vertices and zero or more instances, which are processed by the device and result in the assembly of primitives. Primitives are assembled according to the pInputAssemblyState member of the VkGraphicsPipelineCreateInfo structure, which is of type VkPipelineInputAssemblyStateCreateInfo:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineInputAssemblyStateCreateInfo {
         *     VkStructureType                            sType;
         *     const void*                                pNext;
         *     VkPipelineInputAssemblyStateCreateFlags    flags;
         *     VkPrimitiveTopology                        topology;
         *     VkBool32                                   primitiveRestartEnable;
         * } VkPipelineInputAssemblyStateCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>topology is a VkPrimitiveTopology defining the primitive topology, as described below.
         * <li>primitiveRestartEnable controls whether a special vertex index value is treated as restarting the assembly of primitives. This enable only applies to indexed draws (vkCmdDrawIndexed, vkCmdDrawMultiIndexedEXT, and vkCmdDrawIndexedIndirect), and the special index value is either 0xFFFFFFFF when the indexType parameter of vkCmdBindIndexBuffer2KHR or vkCmdBindIndexBuffer is equal to VK_INDEX_TYPE_UINT32, 0xFF when indexType is equal to VK_INDEX_TYPE_UINT8_KHR, or 0xFFFF when indexType is equal to VK_INDEX_TYPE_UINT16. Primitive restart is not allowed for “list” topologies, unless one of the features primitiveTopologyPatchListRestart (for VK_PRIMITIVE_TOPOLOGY_PATCH_LIST) or primitiveTopologyListRestart (for all other list topologies) is enabled.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Restarting the assembly of primitives discards the most recent index values if those elements formed an incomplete primitive, and restarts the primitive assembly using the subsequent indices, but only assembling the immediately following element through the end of the originally specified elements. The primitive restart index value comparison is performed before adding the vertexOffset value to the index value.
         */
        VkPipelineInputAssemblyStateCreateInfo createVkPipelineInputAssemblyStateCreateInfo();

        /** <b>Name</b><hr><br>
         * VkPipelineShaderStageCreateInfo - Structure specifying parameters of a newly created pipeline shader stage<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineShaderStageCreateInfo structure is defined as:
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineShaderStageCreateInfo {
         *     VkStructureType                     sType;
         *     const void*                         pNext;
         *     VkPipelineShaderStageCreateFlags    flags;
         *     VkShaderStageFlagBits               stage;
         *     VkShaderModule                      module;
         *     const char*                         pName;
         *     const VkSpecializationInfo*         pSpecializationInfo;
         * } VkPipelineShaderStageCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkPipelineShaderStageCreateFlagBits specifying how the pipeline shader stage will be generated.
         * <li>stage is a VkShaderStageFlagBits value specifying a single pipeline stage.
         * <li>module is optionally a VkShaderModule object containing the shader code for this stage.
         * <li>pName is a pointer to a null-terminated UTF-8 string specifying the entry point name of the shader for this stage.
         * <li>pSpecializationInfo is a pointer to a VkSpecializationInfo structure, as described in Specialization Constants, or NULL.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * If module is not VK_NULL_HANDLE, the shader code used by the pipeline is defined by module. If module is VK_NULL_HANDLE, the shader code is defined by the chained VkShaderModuleCreateInfo if present.<br><br>
         *
         * If the shaderModuleIdentifier feature is enabled, applications can omit shader code for stage and instead provide a module identifier. This is done by including a VkPipelineShaderStageModuleIdentifierCreateInfoEXT struct with identifierSize not equal to 0 in the pNext chain. A shader stage created in this way is equivalent to one created using a shader module with the same identifier. The identifier allows an implementation to look up a pipeline without consuming a valid SPIR-V module. If a pipeline is not found, pipeline compilation is not possible and the implementation must fail as specified by VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT. <br><br>
         *
         * When an identifier is used in lieu of a shader module, implementations may fail pipeline compilation with VK_PIPELINE_COMPILE_REQUIRED for any reason.
         *
         * @note The rationale for the relaxed requirement on implementations to return a pipeline with VkPipelineShaderStageModuleIdentifierCreateInfoEXT is that layers or tools may intercept pipeline creation calls and require the full SPIR-V context to operate correctly. ICDs are not expected to fail pipeline compilation if the pipeline exists in a cache somewhere.
         *
         * Applications <b>can</b> use identifiers when creating pipelines with VK_PIPELINE_CREATE_LIBRARY_BIT_KHR. When creating such pipelines, VK_SUCCESS <b>may</b> be returned, but subsequently fail when referencing the pipeline in a VkPipelineLibraryCreateInfoKHR struct.<br>
         * Applications <b>must</b> allow pipeline compilation to fail during link steps with VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT as it <b>may</b> not be possible to determine if a pipeline <b>can</b> be created from identifiers until the link step.
         */
        VkPipelineShaderStageCreateInfo createVkPipelineShaderStageCreateInfo(
                const VkShaderStageFlagBits        &stage,
                const VkShaderModule               &module
        );

        /** <b>Name</b><hr><br>
         *
         * VkViewport - Structure specifying a viewport<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkViewport structure is defined as:
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkViewport {
         *     float    x;
         *     float    y;
         *     float    width;
         *     float    height;
         *     float    minDepth;
         *     float    maxDepth;
         * } VkViewport;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>x and y are the viewport’s upper left corner (x,y).
         * <li>width and height are the viewport’s width and height, respectively.
         * <li>minDepth and maxDepth are the depth range for the viewport.
         * </ul><br>
         * <b>Description</b><hr>
         *
         * @note Despite their names, minDepth <b>can</b> be less than, equal to, or greater than maxDepth.
         *
         * The framebuffer depth coordinate zf <b>may</b> be represented using either a fixed-point or floating-point representation. However, a floating-point representation <b>must</b> be used if the depth/stencil attachment has a floating-point depth component. If an m-bit fixed-point representation is used, we assume that it represents each value k/(2^m-1), where k ∈ { 0, 1, ..., 2^m-1 }, as k (e.g. 1.0 is represented in binary as a string of all ones).<br><br>
         *
         * The viewport parameters shown in the above equations are found from these values as<br><br>
         *
         * Ox = x + width / 2<br><br>
         *
         * Oy = y + height / 2<br><br>
         *
         * Oz = minDepth (or (maxDepth + minDepth) / 2 if VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne is VK_TRUE)<br><br>
         *
         * Px = width<br><br>
         *
         * Py = height<br><br>
         *
         * Pz = maxDepth - minDepth (or (maxDepth - minDepth) / 2 if VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne is VK_TRUE)<br><br>
         *
         * If a render pass transform is enabled, the values (px,py) and (ox, oy) defining the viewport are transformed as described in render pass transform before participating in the viewport transform.<br><br>
         *
         * The application <b>can</b> specify a negative term for height, which has the effect of negating the y coordinate in clip space before performing the transform. When using a negative height, the application <b>should</b> also adjust the y value to point to the lower left corner of the viewport instead of the upper left corner. Using the negative height allows the application to avoid having to negate the y component of the Position output from the last pre-rasterization shader stage.<br><br>
         *
         * The width and height of the implementation-dependent maximum viewport dimensions <b>must</b> be greater than or equal to the width and height of the largest image which <b>can</b> be created and attached to a framebuffer.<br><br>
         *
         * The floating-point viewport bounds are represented with an implementation-dependent precision.
         *
         */
        VkViewport createVkViewport(
                const VkExtent2D        &extent
        );

        /** <b>Name</b><hr><br>
         *
         * VkRect2D - Structure specifying a two-dimensional subregion<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Rectangles are used to describe a specified rectangular region of pixels within an image or framebuffer. Rectangles include both an offset and an extent of the same dimensionality, as described above. Two-dimensional rectangles are defined by the structure
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkRect2D {
         *     VkOffset2D    offset;
         *     VkExtent2D    extent;
         * } VkRect2D;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>offset is a VkOffset2D specifying the rectangle offset.
         * <li>extent is a VkExtent2D specifying the rectangle extent.
         * </ul>
         */
        VkRect2D createVkRect2D(
                const VkExtent2D        &extent
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipelineViewportStateCreateInfo - Structure specifying parameters of a newly created pipeline viewport state<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineViewportStateCreateInfo structure is defined as:
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineViewportStateCreateInfo {
         *     VkStructureType                       sType;
         *     const void*                           pNext;
         *     VkPipelineViewportStateCreateFlags    flags;
         *     uint32_t                              viewportCount;
         *     const VkViewport*                     pViewports;
         *     uint32_t                              scissorCount;
         *     const VkRect2D*                       pScissors;
         * } VkPipelineViewportStateCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>viewportCount is the number of viewports used by the pipeline.
         * <li>pViewports is a pointer to an array of VkViewport structures, defining the viewport transforms. If the viewport state is dynamic, this member is ignored.
         * <li>scissorCount is the number of scissors and must match the number of viewports.
         * <li>pScissors is a pointer to an array of VkRect2D structures defining the rectangular bounds of the scissor for the corresponding viewport. If the scissor state is dynamic, this member is ignored.
         * </ul>
         */
        VkPipelineViewportStateCreateInfo createVkPipelineViewportStateCreateInfo(
                const std::vector<VkViewport>        &viewports,
                const std::vector<VkRect2D>          &scissors
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipelineRasterizationStateCreateInfo - Structure specifying parameters of a newly created pipeline rasterization state<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineRasterizationStateCreateInfo structure is defined as:
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineRasterizationStateCreateInfo {
         *     VkStructureType                            sType;
         *     const void*                                pNext;
         *     VkPipelineRasterizationStateCreateFlags    flags;
         *     VkBool32                                   depthClampEnable;
         *     VkBool32                                   rasterizerDiscardEnable;
         *     VkPolygonMode                              polygonMode;
         *     VkCullModeFlags                            cullMode;
         *     VkFrontFace                                frontFace;
         *     VkBool32                                   depthBiasEnable;
         *     float                                      depthBiasConstantFactor;
         *     float                                      depthBiasClamp;
         *     float                                      depthBiasSlopeFactor;
         *     float                                      lineWidth;
         * } VkPipelineRasterizationStateCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>depthClampEnable controls whether to clamp the fragment’s depth values as described in Depth Test. If the pipeline is not created with VkPipelineRasterizationDepthClipStateCreateInfoEXT present then enabling depth clamp will also disable clipping primitives to the z planes of the frustum as described in Primitive Clipping. Otherwise depth clipping is controlled by the state set in VkPipelineRasterizationDepthClipStateCreateInfoEXT.
         * <li>rasterizerDiscardEnable controls whether primitives are discarded immediately before the rasterization stage.
         * <li>polygonMode is the triangle rendering mode. See VkPolygonMode.
         * <li>cullMode is the triangle facing direction used for primitive culling. See VkCullModeFlagBits-
         * <li>frontFace is a VkFrontFace value specifying the front-facing triangle orientation to be used for culling.
         * <li>depthBiasEnable controls whether to bias fragment depth values.
         * <li>depthBiasConstantFactor is a scalar factor controlling the constant depth value added to each fragment.
         * <li>depthBiasClamp is the maximum (or minimum) depth bias of a fragment.
         * <li>depthBiasSlopeFactor is a scalar factor applied to a fragment’s slope in depth bias calculations.
         * <li>lineWidth is the width of rasterized line segments.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The application <b>can</b> also add a VkPipelineRasterizationStateRasterizationOrderAMD structure to the pNext chain of a VkPipelineRasterizationStateCreateInfo structure. This structure enables selecting the rasterization order to use when rendering with the corresponding graphics pipeline as described in Rasterization Order.
         */
        VkPipelineRasterizationStateCreateInfo createVkPipelineRasterizationStateCreateInfo();

        /** <b>Name</b><hr><br>
         *
         * VkPipelineMultisampleStateCreateInfo - Structure specifying parameters of a newly created pipeline multisample state<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineMultisampleStateCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineMultisampleStateCreateInfo {
         *     VkStructureType                          sType;
         *     const void*                              pNext;
         *     VkPipelineMultisampleStateCreateFlags    flags;
         *     VkSampleCountFlagBits                    rasterizationSamples;
         *     VkBool32                                 sampleShadingEnable;
         *     float                                    minSampleShading;
         *     const VkSampleMask*                      pSampleMask;
         *     VkBool32                                 alphaToCoverageEnable;
         *     VkBool32                                 alphaToOneEnable;
         * } VkPipelineMultisampleStateCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>rasterizationSamples is a VkSampleCountFlagBits value specifying the number of samples used in rasterization. This value is ignored for the purposes of setting the number of samples used in rasterization if the pipeline is created with the VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT dynamic state set, but if VK_DYNAMIC_STATE_SAMPLE_MASK_EXT dynamic state is not set, it is still used to define the size of the pSampleMask array as described below.
         * <li>sampleShadingEnable <b>can</b> be used to enable Sample Shading.
         * <li>minSampleShading specifies a minimum fraction of sample shading if sampleShadingEnable is set to VK_TRUE.
         * <li>pSampleMask is a pointer to an array of VkSampleMask values used in the sample mask test.
         * <li>alphaToCoverageEnable controls whether a temporary coverage value is generated based on the alpha component of the fragment’s first color output as specified in the Multisample Coverage section.
         * <li>alphaToOneEnable controls whether the alpha component of the fragment’s first color output is replaced with one as described in Multisample Coverage.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Each bit in the sample mask is associated with a unique sample index as defined for the coverage mask. Each bit b for mask word w in the sample mask corresponds to sample index i, where i = 32 × w + b. pSampleMask has a length equal to ⌈ rasterizationSamples / 32 ⌉ words.<br><br>
         * If pSampleMask is NULL, it is treated as if the mask has all bits set to 1.
         */
        VkPipelineMultisampleStateCreateInfo createVkPipelineMultisampleStateCreateInfo();

        /** <b>Name</b><hr><br>
         *
         * VkPipelineColorBlendAttachmentState - Structure specifying a pipeline color blend attachment state<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineColorBlendAttachmentState structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineColorBlendAttachmentState {
         *     VkBool32                 blendEnable;
         *     VkBlendFactor            srcColorBlendFactor;
         *     VkBlendFactor            dstColorBlendFactor;
         *     VkBlendOp                colorBlendOp;
         *     VkBlendFactor            srcAlphaBlendFactor;
         *     VkBlendFactor            dstAlphaBlendFactor;
         *     VkBlendOp                alphaBlendOp;
         *     VkColorComponentFlags    colorWriteMask;
         * } VkPipelineColorBlendAttachmentState;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>blendEnable controls whether blending is enabled for the corresponding color attachment. If blending is not enabled, the source fragment’s color for that attachment is passed through unmodified.
         * <li>srcColorBlendFactor selects which blend factor is used to determine the source factors (Sr,Sg,Sb).
         * <li>dstColorBlendFactor selects which blend factor is used to determine the destination factors (Dr,Dg,Db).
         * <li>colorBlendOp selects which blend operation is used to calculate the RGB values to write to the color attachment.
         * <li>srcAlphaBlendFactor selects which blend factor is used to determine the source factor Sa.
         * <li>dstAlphaBlendFactor selects which blend factor is used to determine the destination factor Da.
         * <li>alphaBlendOp selects which blend operation is used to calculate the alpha values to write to the color attachment.
         * <li>colorWriteMask is a bitmask of VkColorComponentFlagBits specifying which of the R, G, B, and/or A components are enabled for writing, as described for the Color Write Mask.
         * </ul>
         */
        VkPipelineColorBlendAttachmentState createVkPipelineColorBlendAttachmentState();

        /** <b>Name</b><hr><br>
         *
         * VkPipelineColorBlendStateCreateInfo - Structure specifying parameters of a newly created pipeline color blend state<br><br><br>
         *
         * The VkPipelineColorBlendStateCreateInfo structure is defined as:<b>C Specification</b><hr><br>
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPipelineColorBlendStateCreateInfo {
         *     VkStructureType                               sType;
         *     const void*                                   pNext;
         *     VkPipelineColorBlendStateCreateFlags          flags;
         *     VkBool32                                      logicOpEnable;
         *     VkLogicOp                                     logicOp;
         *     uint32_t                                      attachmentCount;
         *     const VkPipelineColorBlendAttachmentState*    pAttachments;
         *     float                                         blendConstants[4];
         * } VkPipelineColorBlendStateCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkPipelineColorBlendStateCreateFlagBits specifying additional color blending information.
         * <li>logicOpEnable controls whether to apply Logical Operations.
         * <li>logicOp selects which logical operation to apply.
         * <li>attachmentCount is the number of VkPipelineColorBlendAttachmentState elements in pAttachments. It is ignored if the pipeline is created with VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT, and VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT dynamic states set, and either VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT set or advancedBlendCoherentOperations is not enabled on the device.
         * <li>pAttachments is a pointer to an array of VkPipelineColorBlendAttachmentState structures defining blend state for each color attachment. It is ignored if the pipeline is created with VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT, and VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT dynamic states set, and either VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT set or advancedBlendCoherentOperations is not enabled on the device.
         * <li>blendConstants is a pointer to an array of four values used as the R, G, B, and A components of the blend constant that are used in blending, depending on the blend factor.
         * </ul>
         */
        VkPipelineColorBlendStateCreateInfo createVkPipelineColorBlendStateCreateInfo(
                const VkPipelineColorBlendAttachmentState        &colorBlendAttachmentState
        );

        /** <b>Name</b><hr><br>
         *
         * VkAttachmentDescription - Structure specifying an attachment description<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkAttachmentDescription structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkAttachmentDescription {
         *     VkAttachmentDescriptionFlags    flags;
         *     VkFormat                        format;
         *     VkSampleCountFlagBits           samples;
         *     VkAttachmentLoadOp              loadOp;
         *     VkAttachmentStoreOp             storeOp;
         *     VkAttachmentLoadOp              stencilLoadOp;
         *     VkAttachmentStoreOp             stencilStoreOp;
         *     VkImageLayout                   initialLayout;
         *     VkImageLayout                   finalLayout;
         * } VkAttachmentDescription;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>flags is a bitmask of VkAttachmentDescriptionFlagBits specifying additional properties of the attachment.
         * <li>format is a VkFormat value specifying the format of the image view that will be used for the attachment.
         * <li>samples is a VkSampleCountFlagBits value specifying the number of samples of the image.
         * <li>loadOp is a VkAttachmentLoadOp value specifying how the contents of color and depth components of the attachment are treated at the beginning of the subpass where it is first used.
         * <li>storeOp is a VkAttachmentStoreOp value specifying how the contents of color and depth components of the attachment are treated at the end of the subpass where it is last used.
         * <li>stencilLoadOp is a VkAttachmentLoadOp value specifying how the contents of stencil components of the attachment are treated at the beginning of the subpass where it is first used.
         * <li>stencilStoreOp is a VkAttachmentStoreOp value specifying how the contents of stencil components of the attachment are treated at the end of the last subpass where it is used.
         * <li>initialLayout is the layout the attachment image subresource will be in when a render pass instance begins.
         * <li>finalLayout is the layout the attachment image subresource will be transitioned to when a render pass instance ends.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * If the attachment uses a color format, then loadOp and storeOp are used, and stencilLoadOp and stencilStoreOp are ignored. If the format has depth and/or stencil components, loadOp and storeOp apply only to the depth data, while stencilLoadOp and stencilStoreOp define how the stencil data is handled. loadOp and stencilLoadOp define the load operations for the attachment. storeOp and stencilStoreOp define the store operations for the attachment. If an attachment is not used by any subpass, loadOp, storeOp, stencilStoreOp, and stencilLoadOp will be ignored for that attachment, and no load or store ops will be performed. However, any transition specified by initialLayout and finalLayout will still be executed.<br><br>
         *
         * If flags includes VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT, then the attachment is treated as if it shares physical memory with another attachment in the same render pass. This information limits the ability of the implementation to reorder certain operations (like layout transitions and the loadOp) such that it is not improperly reordered against other uses of the same physical memory via a different attachment. This is described in more detail below.<br><br>
         *
         * If a render pass uses multiple attachments that alias the same device memory, those attachments must each include the VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT bit in their attachment description flags. Attachments aliasing the same memory occurs in multiple ways:<br><br>
         * <ul>
         * <li>Multiple attachments being assigned the same image view as part of framebuffer creation.
         * <li>Attachments using distinct image views that correspond to the same image subresource of an image.
         * <li>Attachments using views of distinct image subresources which are bound to overlapping memory ranges.
         * </ul>
         * @note Render passes <b>must</b> include subpass dependencies (either directly or via a subpass dependency chain) between any two subpasses that operate on the same attachment or aliasing attachments and those subpass dependencies <b>must</b> include execution and memory dependencies separating uses of the aliases, if at least one of those subpasses writes to one of the aliases. These dependencies <b>must</b> not include the VK_DEPENDENCY_BY_REGION_BIT if the aliases are views of distinct image subresources which overlap in memory.
         *
         * Multiple attachments that alias the same memory <b>must</b> not be used in a single subpass. A given attachment index <b>must</b> not be used multiple times in a single subpass, with one exception: two subpass attachments <b>can</b> use the same attachment index if at least one use is as an input attachment and neither use is as a resolve or preserve attachment. In other words, the same view <b>can</b> be used simultaneously as an input and color or depth/stencil attachment, but <b>must</b> not be used as multiple color or depth/stencil attachments nor as resolve or preserve attachments.<br><br>
         *
         * If a set of attachments alias each other, then all except the first to be used in the render pass <b>must</b> use an initialLayout of VK_IMAGE_LAYOUT_UNDEFINED, since the earlier uses of the other aliases make their contents undefined. Once an alias has been used and a different alias has been used after it, the first alias <b>must</b> not be used in any later subpasses. However, an application <b>can</b> assign the same image view to multiple aliasing attachment indices, which allows that image view to be used multiple times even if other aliases are used in between.
         *
         * @note Once an attachment needs the VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT bit, there <b>should</b> be no additional cost of introducing additional aliases, and using these additional aliases <b>may</b> allow more efficient clearing of the attachments on multiple uses via VK_ATTACHMENT_LOAD_OP_CLEAR.
         */
        VkAttachmentDescription createVkAttachmentDescription(
                const VkFormat        &format
        );

        /** <b>Name</b><hr><br>
         *
         * VkAttachmentReference - Structure specifying an attachment reference<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkAttachmentReference structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkAttachmentReference {
         *     uint32_t         attachment;
         *     VkImageLayout    layout;
         * } VkAttachmentReference;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>attachment is either an integer value identifying an attachment at the corresponding index in VkRenderPassCreateInfo::pAttachments, or VK_ATTACHMENT_UNUSED to signify that this attachment is not used.
         * <li>layout is a VkImageLayout value specifying the layout the attachment uses during the subpass.
         * </ul>
         */
        VkAttachmentReference createVkAttachmentReference(
                const uint32_t             &attachment,
                const VkImageLayout        &layout
        );

        /** <b>Name</b><hr><br>
         *
         * VkSubpassDescription - Structure specifying a subpass description<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSubpassDescription structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkSubpassDescription {
         *     VkSubpassDescriptionFlags       flags;
         *     VkPipelineBindPoint             pipelineBindPoint;
         *     uint32_t                        inputAttachmentCount;
         *     const VkAttachmentReference*    pInputAttachments;
         *     uint32_t                        colorAttachmentCount;
         *     const VkAttachmentReference*    pColorAttachments;
         *     const VkAttachmentReference*    pResolveAttachments;
         *     const VkAttachmentReference*    pDepthStencilAttachment;
         *     uint32_t                        preserveAttachmentCount;
         *     const uint32_t*                 pPreserveAttachments;
         * } VkSubpassDescription;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>flags is a bitmask of VkSubpassDescriptionFlagBits specifying usage of the subpass.
         * <li>pipelineBindPoint is a VkPipelineBindPoint value specifying the pipeline type supported for this subpass.
         * <li>inputAttachmentCount is the number of input attachments.
         * <li>pInputAttachments is a pointer to an array of VkAttachmentReference structures defining the input attachments for this subpass and their layouts.
         * <li>colorAttachmentCount is the number of color attachments.
         * <li>pColorAttachments is a pointer to an array of colorAttachmentCount VkAttachmentReference structures defining the color attachments for this subpass and their layouts.
         * <li>pResolveAttachments is NULL or a pointer to an array of colorAttachmentCount VkAttachmentReference structures defining the resolve attachments for this subpass and their layouts.
         * <li>pDepthStencilAttachment is a pointer to a VkAttachmentReference structure specifying the depth/stencil attachment for this subpass and its layout.
         * <li>preserveAttachmentCount is the number of preserved attachments.
         * <li>pPreserveAttachments is a pointer to an array of preserveAttachmentCount render pass attachment indices identifying attachments that are not used by this subpass, but whose contents <b>must</b> be preserved throughout the subpass.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Each element of the pInputAttachments array corresponds to an input attachment index in a fragment shader, i.e. if a shader declares an image variable decorated with a InputAttachmentIndex value of X, then it uses the attachment provided in pInputAttachments[X]. Input attachments <b>must</b> also be bound to the pipeline in a descriptor set. If the attachment member of any element of pInputAttachments is VK_ATTACHMENT_UNUSED, the application <b>must</b> not read from the corresponding input attachment index. Fragment shaders <b>can</b> use subpass input variables to access the contents of an input attachment at the fragment’s (x, y, layer) framebuffer coordinates. Input attachments <b>must</b> not be used by any subpasses within a render pass that enables render pass transform.<br><br>
         *
         * Each element of the pColorAttachments array corresponds to an output location in the shader, i.e. if the shader declares an output variable decorated with a Location value of X, then it uses the attachment provided in pColorAttachments[X]. If the attachment member of any element of pColorAttachments is VK_ATTACHMENT_UNUSED, or if Color Write Enable has been disabled for the corresponding attachment index, then writes to the corresponding location by a fragment shader are discarded.<br><br>
         *
         * If flags does not include VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM, and if pResolveAttachments is not NULL, each of its elements corresponds to a color attachment (the element in pColorAttachments at the same index), and a multisample resolve operation is defined for each attachment unless the resolve attachment index is VK_ATTACHMENT_UNUSED.<br><br>
         *
         * Similarly, if flags does not include VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM, and VkSubpassDescriptionDepthStencilResolve::pDepthStencilResolveAttachment is not NULL and does not have the value VK_ATTACHMENT_UNUSED, it corresponds to the depth/stencil attachment in pDepthStencilAttachment, and multisample resolve operation for depth and stencil are defined by VkSubpassDescriptionDepthStencilResolve::depthResolveMode and VkSubpassDescriptionDepthStencilResolve::stencilResolveMode, respectively. If VkSubpassDescriptionDepthStencilResolve::depthResolveMode is VK_RESOLVE_MODE_NONE or the pDepthStencilResolveAttachment does not have a depth aspect, no resolve operation is performed for the depth attachment. If VkSubpassDescriptionDepthStencilResolve::stencilResolveMode is VK_RESOLVE_MODE_NONE or the pDepthStencilResolveAttachment does not have a stencil aspect, no resolve operation is performed for the stencil attachment.<br><br>
         *
         * If the image subresource range referenced by the depth/stencil attachment is created with VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT, then the multisample resolve operation uses the sample locations state specified in the sampleLocationsInfo member of the element of the VkRenderPassSampleLocationsBeginInfoEXT::pPostSubpassSampleLocations for the subpass.<br><br>
         *
         * If pDepthStencilAttachment is NULL, or if its attachment index is VK_ATTACHMENT_UNUSED, it indicates that no depth/stencil attachment will be used in the subpass.<br><br>
         *
         * The contents of an attachment within the render area become undefined at the start of a subpass S if all of the following conditions are true:
         * <ul>
         * <li> The attachment is used as a color, depth/stencil, or resolve attachment in any subpass in the render pass.
         * <li> There is a subpass S1 that uses or preserves the attachment, and a subpass dependency from S1 to S.
         * <li> The attachment is not used or preserved in subpass S.
         * </ul>
         * In addition, the contents of an attachment within the render area become undefined at the start of a subpass S if all of the following conditions are true:
         * <ul>
         * <li> VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM is set.
         * <li> The attachment is used as a color or depth/stencil in the subpass.
         * </ul>
         *
         * Once the contents of an attachment become undefined in subpass S, they remain undefined for subpasses in subpass dependency chains starting with subpass S until they are written again. However, they remain valid for subpasses in other subpass dependency chains starting with subpass S1 if those subpasses use or preserve the attachment.<br><br>
         */
        VkSubpassDescription createVkSubpassDescription(
                const std::vector<VkAttachmentReference>        &inputAttachments,
                const std::vector<VkAttachmentReference>        &colorAttachments,
                const std::vector<VkAttachmentReference>        &resolveAttachments,
                const std::vector<VkAttachmentReference>        &depthStencilAttachment,
                const std::vector<uint32_t>                     &preserveAttachments
        );

        /** <b>Name</b><hr><br>
         *
         * VkCommandBufferBeginInfo - Structure specifying a command buffer begin operation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkCommandBufferBeginInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkCommandBufferBeginInfo {
         *     VkStructureType                          sType;
         *     const void*                              pNext;
         *     VkCommandBufferUsageFlags                flags;
         *     const VkCommandBufferInheritanceInfo*    pInheritanceInfo;
         * } VkCommandBufferBeginInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkCommandBufferUsageFlagBits specifying usage behavior for the command buffer.
         * <li>pInheritanceInfo is a pointer to a VkCommandBufferInheritanceInfo structure, used if commandBuffer is a secondary command buffer. If this is a primary command buffer, then this value is ignored.
         * </ul>
         */
        VkCommandBufferBeginInfo createVkCommandBufferBeginInfo(
                const VkCommandBufferUsageFlags        &flags
        );

        /** <b>Name</b><hr><br>
         *
         * VkRenderPassBeginInfo - Structure specifying render pass begin information<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkRenderPassBeginInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkRenderPassBeginInfo {
         *     VkStructureType        sType;
         *     const void*            pNext;
         *     VkRenderPass           renderPass;
         *     VkFramebuffer          framebuffer;
         *     VkRect2D               renderArea;
         *     uint32_t               clearValueCount;
         *     const VkClearValue*    pClearValues;
         * } VkRenderPassBeginInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>renderPass is the render pass to begin an instance of.
         * <li>framebuffer is the framebuffer containing the attachments that are used with the render pass.
         * <li>renderArea is the render area that is affected by the render pass instance, and is described in more detail below.
         * <li>clearValueCount is the number of elements in pClearValues.
         * <li>pClearValues is a pointer to an array of clearValueCount VkClearValue structures containing clear values for each attachment, if the attachment uses a loadOp value of VK_ATTACHMENT_LOAD_OP_CLEAR or if the attachment has a depth/stencil format and uses a stencilLoadOp value of VK_ATTACHMENT_LOAD_OP_CLEAR. The array is indexed by attachment number. Only elements corresponding to cleared attachments are used. Other elements of pClearValues are ignored.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * renderArea is the render area that is affected by the render pass instance. The effects of attachment load, store and multisample resolve operations are restricted to the pixels whose x and y coordinates fall within the render area on all attachments. The render area extends to all layers of framebuffer. The application <b>must</b> ensure (using scissor if necessary) that all rendering is contained within the render area. The render area, after any transform specified by VkRenderPassTransformBeginInfoQCOM::transform is applied, <b>must</b> be contained within the framebuffer dimensions.<br><br>
         *
         * If render pass transform is enabled, then renderArea <b>must</b> equal the framebuffer pre-transformed dimensions. After renderArea has been transformed by VkRenderPassTransformBeginInfoQCOM::transform, the resulting render area <b>must</b> be equal to the framebuffer dimensions.<br><br>
         *
         * If multiview is enabled in renderPass, and multiviewPerViewRenderAreas feature is enabled, and there is an instance of VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM included in the pNext chain with perViewRenderAreaCount not equal to 0, then the elements of VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM::pPerViewRenderAreas override renderArea and define a render area for each view. In this case, renderArea <b>must</b> be set to an area at least as large as the union of all the per-view render areas.<br><br>
         *
         * If the subpassShading feature is enabled, then renderArea <b>must</b> equal the framebuffer dimensions.
         *
         * @note There <b>may</b> be a performance cost for using a render area smaller than the framebuffer, unless it matches the render area granularity for the render pass.
         */
        VkRenderPassBeginInfo createVkRenderPassBeginInfo(
                const VkRenderPass                     &renderPass,
                const VkFramebuffer                    &framebuffer,
                const VkExtent2D                       &extent,
                const std::vector<VkClearValue>        &clearValues
        );

        /** <b>Name</b><hr><br>
         *
         * VkSubmitInfo - Structure specifying a queue submit operation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSubmitInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkSubmitInfo {
         *     VkStructureType                sType;
         *     const void*                    pNext;
         *     uint32_t                       waitSemaphoreCount;
         *     const VkSemaphore*             pWaitSemaphores;
         *     const VkPipelineStageFlags*    pWaitDstStageMask;
         *     uint32_t                       commandBufferCount;
         *     const VkCommandBuffer*         pCommandBuffers;
         *     uint32_t                       signalSemaphoreCount;
         *     const VkSemaphore*             pSignalSemaphores;
         * } VkSubmitInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>waitSemaphoreCount is the number of semaphores upon which to wait before executing the command buffers for the batch.
         * <li>pWaitSemaphores is a pointer to an array of VkSemaphore handles upon which to wait before the command buffers for this batch begin execution. If semaphores to wait on are provided, they define a semaphore wait operation.
         * <li>pWaitDstStageMask is a pointer to an array of pipeline stages at which each corresponding semaphore wait will occur.
         * <li>commandBufferCount is the number of command buffers to execute in the batch.
         * <li>pCommandBuffers is a pointer to an array of VkCommandBuffer handles to execute in the batch.
         * <li>signalSemaphoreCount is the number of semaphores to be signaled once the commands specified in pCommandBuffers have completed execution.
         * <li>pSignalSemaphores is a pointer to an array of VkSemaphore handles which will be signaled when the command buffers for this batch have completed execution. If semaphores to be signaled are provided, they define a semaphore signal operation.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The order that command buffers appear in pCommandBuffers is used to determine submission order, and thus all the implicit ordering guarantees that respect it. Other than these implicit ordering guarantees and any explicit synchronization primitives, these command buffers <b>may</b> overlap or otherwise execute out of order.
         */
        VkSubmitInfo createVkSubmitInfo(
                const std::vector<VkSemaphore>            &waitSemaphores,
                const VkPipelineStageFlags                *pWaitDstStageMask,
                const std::vector<VkCommandBuffer>        &commandBuffers,
                const std::vector<VkSemaphore>            &signalSemaphores
        );

        /** <b>Name</b><hr><br>
         *
         * VkPresentInfoKHR - Structure describing parameters of a queue presentation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPresentInfoKHR structure is defined as:
         *
         * @code
         * // Provided by VK_KHR_swapchain
         * typedef struct VkPresentInfoKHR {
         *     VkStructureType          sType;
         *     const void*              pNext;
         *     uint32_t                 waitSemaphoreCount;
         *     const VkSemaphore*       pWaitSemaphores;
         *     uint32_t                 swapchainCount;
         *     const VkSwapchainKHR*    pSwapchains;
         *     const uint32_t*          pImageIndices;
         *     VkResult*                pResults;
         * } VkPresentInfoKHR;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>waitSemaphoreCount is the number of semaphores to wait for before issuing the present request. The number <b>may</b> be zero.
         * <li>pWaitSemaphores is NULL or a pointer to an array of VkSemaphore objects with waitSemaphoreCount entries, and specifies the semaphores to wait for before issuing the present request.
         * <li>swapchainCount is the number of swapchains being presented to by this command.
         * <li>pSwapchains is a pointer to an array of VkSwapchainKHR objects with swapchainCount entries.
         * <li>pImageIndices is a pointer to an array of indices into the array of each swapchain’s presentable images, with swapchainCount entries. Each entry in this array identifies the image to present on the corresponding entry in the pSwapchains array.
         * <li>pResults is a pointer to an array of VkResult typed elements with swapchainCount entries. Applications that do not need per-swapchain results <b>can</b> use NULL for pResults. If non-NULL, each entry in pResults will be set to the VkResult for presenting the swapchain corresponding to the same index in pSwapchains.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Before an application <b>can</b> present an image, the image’s layout <b>must</b> be transitioned to the VK_IMAGE_LAYOUT_PRESENT_SRC_KHR layout, or for a shared presentable image the VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR layout.
         *
         * @note When transitioning the image to VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR or VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, there is no need to delay subsequent processing, or perform any visibility operations (as vkQueuePresentKHR performs automatic visibility operations). To achieve this, the dstAccessMask member of the VkImageMemoryBarrier <b>should</b> be set to 0, and the dstStageMask parameter <b>should</b> be set to VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT.
         */
        VkPresentInfoKHR createVkPresentInfoKHR(
                const std::vector<VkSemaphore>          &waitSemaphores,
                const std::vector<VkSwapchainKHR>       &swapchains,
                const std::vector<uint32_t>             &imageIndices
        );

        /** <b>Name</b><hr><br>
         *
         * VkPushConstantRange - Structure specifying a push constant range<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPushConstantRange structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPushConstantRange {
         *     VkShaderStageFlags    stageFlags;
         *     uint32_t              offset;
         *     uint32_t              size;
         * } VkPushConstantRange;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>stageFlags is a set of stage flags describing the shader stages that will access a range of push constants. If a particular stage is not included in the range, then accessing members of that range of push constants from the corresponding shader stage will return undefined values.
         * <li>offset and size are the start offset and size, respectively, consumed by the range. Both offset and size are in units of bytes and <b>must</b> be a multiple of 4. The layout of the push constant variables is specified in the shader.
         * </ul>
         */
        VkPushConstantRange createVkPushConstantRange(
                const VkShaderStageFlags        &stageFlags,
                const uint32_t                  &offset,
                const uint32_t                  &size
        );

        /** <b>Name</b><hr><br>
         *
         * VkVertexInputBindingDescription - Structure specifying vertex input binding description<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Each vertex input binding is specified by the VkVertexInputBindingDescription structure, defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkVertexInputBindingDescription {
         *     uint32_t             binding;
         *     uint32_t             stride;
         *     VkVertexInputRate    inputRate;
         * } VkVertexInputBindingDescription;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>binding is the binding number that this structure describes.
         * <li>stride is the byte stride between consecutive elements within the buffer.
         * <li>inputRate is a VkVertexInputRate value specifying whether vertex attribute addressing is a function of the vertex index or of the instance index.
         * </ul>
         */
        VkVertexInputBindingDescription createVkVertexInputBindingDescription(
                const uint32_t                 &binding,
                const uint32_t                 &size,
                const VkVertexInputRate        &inputRate
        );

        /** <b>Name</b><hr><br>
         *
         * VkVertexInputAttributeDescription - Structure specifying vertex input attribute description<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Each vertex input attribute is specified by the VkVertexInputAttributeDescription structure, defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkVertexInputAttributeDescription {
         *     uint32_t    location;
         *     uint32_t    binding;
         *     VkFormat    format;
         *     uint32_t    offset;
         * } VkVertexInputAttributeDescription;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>location is the shader input location number for this attribute.
         * <li>binding is the binding number which this attribute takes its data from.
         * <li>format is the size and type of the vertex attribute data.
         * <li>offset is a byte offset of this attribute relative to the start of an element in the vertex input binding.
         * </ul>
         */
        VkVertexInputAttributeDescription createVkVertexInputAttributeDescription(
                const uint32_t        &location,
                const uint32_t        &binding,
                const VkFormat        &format,
                const uint32_t        &offset
        );

        /** <b>Name</b><hr><br>
         *
         * VkMemoryAllocateInfo - Structure containing parameters of a memory allocation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkMemoryAllocateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkMemoryAllocateInfo {
         *   VkStructureType    sType;
         *   const void*        pNext;
         *   VkDeviceSize       allocationSize;
         *   uint32_t           memoryTypeIndex;
         * } VkMemoryAllocateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>allocationSize is the size of the allocation in bytes.
         * <li>memoryTypeIndex is an index identifying a memory type from the memoryTypes array of the VkPhysicalDeviceMemoryProperties structure.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The internal data of an allocated device memory object <b>must</b> include a reference to implementation-specific resources, referred to as the memory object’s payload. Applications <b>can</b> also import and export that internal data to and from device memory objects to share data between Vulkan instances and other compatible APIs. A VkMemoryAllocateInfo structure defines a memory import operation if its pNext chain includes one of the following structures:
         * <ul>
         * <li>VkImportMemoryWin32HandleInfoKHR with a non-zero handleType value
         * <li>VkImportMemoryFdInfoKHR with a non-zero handleType value
         * <li>VkImportMemoryHostPointerInfoEXT with a non-zero handleType value
         * <li>VkImportAndroidHardwareBufferInfoANDROID with a non-NULL buffer value
         * <li>VkImportMemoryZirconHandleInfoFUCHSIA with a non-zero handleType value
         * <li>VkImportMemoryBufferCollectionFUCHSIA
         * <li>VkImportScreenBufferInfoQNX with a non-NULL buffer value
         * </ul>
         * If the parameters define an import operation and the external handle type is VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT, or VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT, allocationSize is ignored. The implementation must query the size of these allocations from the OS.<br><br>
         *
         * Whether device memory objects constructed via a memory import operation hold a reference to their payload depends on the properties of the handle type used to perform the import, as defined below for each valid handle type. Importing memory must not modify the content of the memory. Implementations <b>must</b> ensure that importing memory does not enable the importing Vulkan instance to access any memory or resources in other Vulkan instances other than that corresponding to the memory object imported. Implementations <b>must</b> also ensure accessing imported memory which has not been initialized does not allow the importing Vulkan instance to obtain data from the exporting Vulkan instance or vice-versa.
         *
         * @note How exported and imported memory is isolated is left to the implementation, but applications should be aware that such isolation <b>may</b> prevent implementations from placing multiple exportable memory objects in the same physical or virtual page. Hence, applications <b>should</b> avoid creating many small external memory objects whenever possible.
         *
         * Importing memory <b>must</b> not increase overall heap usage within a system. However, it <b>must</b> affect the following per-process values:
         * <ul>
         * <li>VkPhysicalDeviceMaintenance3Properties::maxMemoryAllocationCount
         * <li>VkPhysicalDeviceMemoryBudgetPropertiesEXT::heapUsage
         * </ul>
         * When performing a memory import operation, it is the responsibility of the application to ensure the external handles and their associated payloads meet all valid usage requirements. However, implementations <b>must</b> perform sufficient validation of external handles and payloads to ensure that the operation results in a valid memory object which will not cause program termination, device loss, queue stalls, or corruption of other resources when used as allowed according to its allocation parameters. If the external handle provided does not meet these requirements, the implementation <b>must</b> fail the memory import operation with the error code VK_ERROR_INVALID_EXTERNAL_HANDLE. If the parameters define an export operation and the external handle type is VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID, implementations <b>should</b> not strictly follow memoryTypeIndex. Instead, they <b>should</b> modify the allocation internally to use the required memory type for the application’s given usage. This is because for an export operation, there is currently no way for the client to know the memory type index before allocating.
         */
        VkMemoryAllocateInfo createVkMemoryAllocateInfo(
                const uint64_t        &allocationSize,
                const uint32_t        &memoryTypeIndex
        );

        /** <b>Name</b><hr><br>
         *
         * VkExtent2D - Structure specifying a two-dimensional extent<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A two-dimensional extent is defined by the structure:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkExtent2D {
         *     uint32_t    width;
         *     uint32_t    height;
         * } VkExtent2D;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>width is the width of the extent.
         * <li>height is the height of the extent.
         * </ul>
         */
        VkExtent2D createVkExtent2D(
                const uint32_t        &width,
                const uint32_t        &height
        );

        /** <b>Name</b><hr><br>
         *
         * VkBufferCopy - Structure specifying a buffer copy operation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkBufferCopy structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkBufferCopy {
         *     VkDeviceSize    srcOffset;
         *     VkDeviceSize    dstOffset;
         *     VkDeviceSize    size;
         * } VkBufferCopy;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>srcOffset is the starting offset in bytes from the start of srcBuffer.
         * <li>dstOffset is the starting offset in bytes from the start of dstBuffer.
         * <li>size is the number of bytes to copy.
         * </ul>
         */
        VkBufferCopy createVkBufferCopy(
                const size_t        &size
        );

        /** <b>Name</b><hr><br>
         *
         * VkBufferCreateInfo - Structure specifying the parameters of a newly created buffer object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkBufferCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkBufferCreateInfo {
         *     VkStructureType        sType;
         *     const void*            pNext;
         *     VkBufferCreateFlags    flags;
         *     VkDeviceSize           size;
         *     VkBufferUsageFlags     usage;
         *     VkSharingMode          sharingMode;
         *     uint32_t               queueFamilyIndexCount;
         *     const uint32_t*        pQueueFamilyIndices;
         * } VkBufferCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkBufferCreateFlagBits specifying additional parameters of the buffer.
         * <li>size is the size in bytes of the buffer to be created.
         * <li>usage is a bitmask of VkBufferUsageFlagBits specifying allowed usages of the buffer.
         * <li>sharingMode is a VkSharingMode value specifying the sharing mode of the buffer when it will be accessed by multiple queue families.
         * <li>queueFamilyIndexCount is the number of entries in the pQueueFamilyIndices array.
         * <li>pQueueFamilyIndices is a pointer to an array of queue families that will access this buffer. It is ignored if sharingMode is not VK_SHARING_MODE_CONCURRENT.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * If a VkBufferUsageFlags2CreateInfoKHR structure is present in the pNext chain, VkBufferUsageFlags2CreateInfoKHR::usage from that structure is used instead of usage from this structure.
         */
        VkBufferCreateInfo createVkBufferCreateInfo(
                const VkDeviceSize              &size,
                const VkBufferUsageFlags        &usage
        );

        /** <b>Name</b><hr><br>
         *
         * VkCommandBufferAllocateInfo - Structure specifying the allocation parameters for command buffer object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkCommandBufferAllocateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkCommandBufferAllocateInfo {
         *     VkStructureType         sType;
         *     const void*             pNext;
         *     VkCommandPool           commandPool;
         *     VkCommandBufferLevel    level;
         *     uint32_t                commandBufferCount;
         * } VkCommandBufferAllocateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>commandPool is the command pool from which the command buffers are allocated.
         * <li>level is a VkCommandBufferLevel value specifying the command buffer level.
         * <li>commandBufferCount is the number of command buffers to allocate from the pool.
         * </ul>
         */
        VkCommandBufferAllocateInfo createVkCommandBufferAllocateInfo(
                const VkCommandPool        &commandPool
        );

        /** <b>Name</b><hr><br>
         *
         * VkCommandPoolCreateInfo - Structure specifying parameters of a newly created command pool<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkCommandPoolCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkCommandPoolCreateInfo {
         *     VkStructureType             sType;
         *     const void*                 pNext;
         *     VkCommandPoolCreateFlags    flags;
         *     uint32_t                    queueFamilyIndex;
         * } VkCommandPoolCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkCommandPoolCreateFlagBits indicating usage behavior for the pool and command buffers allocated from it.
         * <li>queueFamilyIndex designates a queue family as described in section Queue Family Properties. All command buffers allocated from this command pool <b>must</b> be submitted on queues from the same queue family.
         * </ul>
         */
        VkCommandPoolCreateInfo createVkCommandPoolCreateInfo(
                const uint32_t        &queueFamilyIndex
        );

        /** <b>Name</b><hr><br>
         *
         * VkDeviceQueueCreateInfo - Structure specifying parameters of a newly created device queue<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDeviceQueueCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkDeviceQueueCreateInfo {
         *     VkStructureType             sType;
         *     const void*                 pNext;
         *     VkDeviceQueueCreateFlags    flags;
         *     uint32_t                    queueFamilyIndex;
         *     uint32_t                    queueCount;
         *     const float*                pQueuePriorities;
         * } VkDeviceQueueCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask indicating behavior of the queues.
         * <li>queueFamilyIndex is an unsigned integer indicating the index of the queue family in which to create the queues on this device. This index corresponds to the index of an element of the pQueueFamilyProperties array that was returned by vkGetPhysicalDeviceQueueFamilyProperties.
         * <li>queueCount is an unsigned integer specifying the number of queues to create in the queue family indicated by queueFamilyIndex, and with the behavior specified by flags.
         * <li>pQueuePriorities is a pointer to an array of queueCount normalized floating point values, specifying priorities of work that will be submitted to each created queue. See Queue Priority for more information.
         * </ul>
         */
        VkDeviceQueueCreateInfo createVkDeviceQueueCreateInfo(
                const uint32_t        &queueFamilyIndex,
                const float           *queuePriority
        );

        /** <b>Name</b><hr><br>
         *
         * VkDeviceCreateInfo - Structure specifying parameters of a newly created device<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDeviceCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkDeviceCreateInfo {
         *     VkStructureType                    sType;
         *     const void*                        pNext;
         *     VkDeviceCreateFlags                flags;
         *     uint32_t                           queueCreateInfoCount;
         *     const VkDeviceQueueCreateInfo*     pQueueCreateInfos;
         *     uint32_t                           enabledLayerCount;
         *     const char* const*                 ppEnabledLayerNames;
         *     uint32_t                           enabledExtensionCount;
         *     const char* const*                 ppEnabledExtensionNames;
         *     const VkPhysicalDeviceFeatures*    pEnabledFeatures;
         * } VkDeviceCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>queueCreateInfoCount is the unsigned integer size of the pQueueCreateInfos array. Refer to the Queue Creation section below for further details.
         * <li>pQueueCreateInfos is a pointer to an array of VkDeviceQueueCreateInfo structures describing the queues that are requested to be created along with the logical device. Refer to the Queue Creation section below for further details.
         * <li>enabledLayerCount is deprecated and ignored.
         * <li>ppEnabledLayerNames is deprecated and ignored. See https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#extendingvulkan-layers-devicelayerdeprecation.
         * <li>enabledExtensionCount is the number of device extensions to enable.
         * <li>ppEnabledExtensionNames is a pointer to an array of enabledExtensionCount null-terminated UTF-8 strings containing the names of extensions to enable for the created device. See the https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#extendingvulkan-extensions section for further details.
         * <li>pEnabledFeatures is NULL or a pointer to a VkPhysicalDeviceFeatures structure containing boolean indicators of all the features to be enabled. Refer to the Features section for further details.
         * </ul>
         */
        VkDeviceCreateInfo createVkDeviceCreateInfo(
                const std::vector<VkDeviceQueueCreateInfo>        &queueCreateInfos,
                const std::vector<const char *>                   &enabledExtensionNames
        );

        /** <b>Name</b><hr><br>
         *
         * VkFenceCreateInfo - Structure specifying parameters of a newly created fence<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkFenceCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkFenceCreateInfo {
         *   VkStructureType       sType;
         *   const void*           pNext;
         *   VkFenceCreateFlags    flags;
         * } VkFenceCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkFenceCreateFlagBits specifying the initial state and behavior of the fence.
         * </ul>
         */
        VkFenceCreateInfo createVkFenceCreateInfo();

        /** <b>Name</b><hr><br>
         *
         * VkFramebufferCreateInfo - Structure specifying parameters of a newly created framebuffer<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkFramebufferCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkFramebufferCreateInfo {
         *     VkStructureType             sType;
         *     const void*                 pNext;
         *     VkFramebufferCreateFlags    flags;
         *     VkRenderPass                renderPass;
         *     uint32_t                    attachmentCount;
         *     const VkImageView*          pAttachments;
         *     uint32_t                    width;
         *     uint32_t                    height;
         *     uint32_t                    layers;
         * } VkFramebufferCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkFramebufferCreateFlagBits
         * <li>renderPass is a render pass defining what render passes the framebuffer will be compatible with. See Render Pass Compatibility for details.
         * <li>attachmentCount is the number of attachments.
         * <li>pAttachments is a pointer to an array of VkImageView handles, each of which will be used as the corresponding attachment in a render pass instance. If flags includes VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT, this parameter is ignored.
         * <li>width, height and layers define the dimensions of the framebuffer. If the render pass uses multiview, then layers must be one and each attachment requires a number of layers that is greater than the maximum bit index set in the view mask in the subpasses in which it is used.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * It is legal for a subpass to use no color or depth/stencil attachments, either because it has no attachment references or because all of them are VK_ATTACHMENT_UNUSED. This kind of subpass <b>can</b> use shader side effects such as image stores and atomics to produce an output. In this case, the subpass continues to use the width, height, and layers of the framebuffer to define the dimensions of the rendering area, and the rasterizationSamples from each pipeline’s VkPipelineMultisampleStateCreateInfo to define the number of samples used in rasterization; however, if VkPhysicalDeviceFeatures::variableMultisampleRate is VK_FALSE, then all pipelines to be bound with the subpass <b>must</b> have the same value for VkPipelineMultisampleStateCreateInfo::rasterizationSamples. In all such cases, rasterizationSamples <b>must</b> be a valid VkSampleCountFlagBits value that is set in VkPhysicalDeviceLimits::framebufferNoAttachmentsSampleCounts.
         */
        VkFramebufferCreateInfo createVkFramebufferCreateInfo(
                const VkRenderPass                     &renderPass,
                const VkExtent2D                       &extent,
                const std::vector<VkImageView>         &imageViews
        );

        /** <b>Name</b><hr><br>
         *
         * VkImageViewCreateInfo - Structure specifying parameters of a newly created image view<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkImageViewCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkImageViewCreateInfo {
         *     VkStructureType            sType;
         *     const void*                pNext;
         *     VkImageViewCreateFlags     flags;
         *     VkImage                    image;
         *     VkImageViewType            viewType;
         *     VkFormat                   format;
         *     VkComponentMapping         components;
         *     VkImageSubresourceRange    subresourceRange;
         * } VkImageViewCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkImageViewCreateFlagBits specifying additional parameters of the image view.
         * <li>image is a VkImage on which the view will be created.
         * <li>viewType is a VkImageViewType value specifying the type of the image view.
         * <li>format is a VkFormat specifying the format and type used to interpret texel blocks of the image.
         * <li>components is a VkComponentMapping structure specifying a remapping of color components (or of depth or stencil components after they have been converted into color components).
         * <li>subresourceRange is a VkImageSubresourceRange structure selecting the set of mipmap levels and array layers to be accessible to the view.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Some of the image creation parameters are inherited by the view. In particular, image view creation inherits the implicit parameter usage specifying the allowed usages of the image view that, by default, takes the value of the corresponding usage parameter specified in VkImageCreateInfo at image creation time. The implicit usage <b>can</b> be overridden by adding a VkImageViewUsageCreateInfo structure to the pNext chain, but the view usage <b>must</b> be a subset of the image usage. If image has a depth-stencil format and was created with a VkImageStencilUsageCreateInfo structure included in the pNext chain of VkImageCreateInfo, the usage is calculated based on the subresource.aspectMask provided:
         * <ul>
         * <li>If aspectMask includes only VK_IMAGE_ASPECT_STENCIL_BIT, the implicit usage is equal to VkImageStencilUsageCreateInfo::stencilUsage.
         * <li>If aspectMask includes only VK_IMAGE_ASPECT_DEPTH_BIT, the implicit usage is equal to VkImageCreateInfo::usage.
         * <li>If both aspects are included in aspectMask, the implicit usage is equal to the intersection of VkImageCreateInfo::usage and VkImageStencilUsageCreateInfo::stencilUsage.
         * </ul>
         * If image is a 3D image, its Z range <b>can</b> be restricted to a subset by adding a VkImageViewSlicedCreateInfoEXT to the pNext chain.<br><br>
         *
         * If image was created with the VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT flag, and if the format of the image is not multi-planar, format <b>can</b> be different from the image’s format, but if image was created without the VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT flag and they are not equal they <b>must</b> be compatible. Image format compatibility is defined in the Format Compatibility Classes section. Views of compatible formats will have the same mapping between texel coordinates and memory locations irrespective of the format, with only the interpretation of the bit pattern changing.<br><br>
         *
         * If image was created with a multi-planar format, and the image view’s aspectMask is one of VK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT or VK_IMAGE_ASPECT_PLANE_2_BIT, the view’s aspect mask is considered to be equivalent to VK_IMAGE_ASPECT_COLOR_BIT when used as a framebuffer attachment.
         *
         * @note Values intended to be used with one view format <b>may</b> not be exactly preserved when written or read through a different format. For example, an integer value that happens to have the bit pattern of a floating point denorm or NaN may be flushed or canonicalized when written or read through a view with a floating point format. Similarly, a value written through a signed normalized format that has a bit pattern exactly equal to -2^b <b>may</b> be changed to -2^b + 1 as described in Conversion from Normalized Fixed-Point to Floating-Point.
         *
         * If image was created with the VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT flag, format <b>must</b> be compatible with the image’s format as described above; or <b>must</b> be an uncompressed format, in which case it <b>must</b> be size-compatible with the image’s format. In this case, the resulting image view’s texel dimensions equal the dimensions of the selected mip level divided by the compressed texel block size and rounded up.<br><br>
         *
         * The VkComponentMapping components member describes a remapping from components of the image to components of the vector returned by shader image instructions. This remapping <b>must</b> be the identity swizzle for storage image descriptors, input attachment descriptors, framebuffer attachments, and any VkImageView used with a combined image sampler that enables sampler Y′CBCR conversion.<br><br>
         *
         * If the image view is to be used with a sampler which supports sampler Y′CBCR conversion, an identically defined object of type VkSamplerYcbcrConversion to that used to create the sampler <b>must</b> be passed to vkCreateImageView in a VkSamplerYcbcrConversionInfo included in the pNext chain of VkImageViewCreateInfo. Conversely, if a VkSamplerYcbcrConversion object is passed to vkCreateImageView, an identically defined VkSamplerYcbcrConversion object <b>must</b> be used when sampling the image.<br><br>
         *
         * If the image has a multi-planar format, subresourceRange.aspectMask is VK_IMAGE_ASPECT_COLOR_BIT, and usage includes VK_IMAGE_USAGE_SAMPLED_BIT, then the format <b>must</b> be identical to the image format and the sampler to be used with the image view <b>must</b> enable sampler Y′CBCR conversion.<br><br>
         *
         * When such an image is used in a video coding operation, the sampler Y′CBCR conversion has no effect.<br><br>
         *
         * If image was created with the VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT and the image has a multi-planar format, and if subresourceRange.aspectMask is VK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT, or VK_IMAGE_ASPECT_PLANE_2_BIT, format <b>must</b> be compatible with the corresponding plane of the image, and the sampler to be used with the image view <b>must</b> not enable sampler Y′CBCR conversion. The width and height of the single-plane image view must be derived from the multi-planar image’s dimensions in the manner listed for plane compatibility for the plane.<br><br>
         *
         * Any view of an image plane will have the same mapping between texel coordinates and memory locations as used by the components of the color aspect, subject to the formulae relating texel coordinates to lower-resolution planes as described in Chroma Reconstruction. That is, if an R or B plane has a reduced resolution relative to the G plane of the multi-planar image, the image view operates using the (uplane, vplane) unnormalized coordinates of the reduced-resolution plane, and these coordinates access the same memory locations as the (ucolor, vcolor) unnormalized coordinates of the color aspect for which chroma reconstruction operations operate on the same (uplane, vplane) or (iplane, jplane) coordinates.<br><br>
         *
         * Table 1. Image type and image view type compatibility requirements
         *
         * <pre> <b>   Image View Type</b>               | <b>Compatible Image Types</b></pre><
         * <pre>    VK_IMAGE_VIEW_TYPE_1D         | VK_IMAGE_TYPE_1D</pre>
         * <pre>    VK_IMAGE_VIEW_TYPE_1D_ARRAY   | VK_IMAGE_TYPE_1D</pre>
         * <pre>    VK_IMAGE_VIEW_TYPE_2D         | VK_IMAGE_TYPE_2D , VK_IMAGE_TYPE_3D</pre>
         * <pre>    VK_IMAGE_VIEW_TYPE_2D_ARRAY   | VK_IMAGE_TYPE_2D , VK_IMAGE_TYPE_3D</pre>
         * <pre>    VK_IMAGE_VIEW_TYPE_CUBE       | VK_IMAGE_TYPE_2D</pre>
         * <pre>    VK_IMAGE_VIEW_TYPE_CUBE_ARRAY | VK_IMAGE_TYPE_2D</pre>
         * <pre>    VK_IMAGE_VIEW_TYPE_3D         | VK_IMAGE_TYPE_3D</pre>
         *
         *
         */
        VkImageViewCreateInfo createVkImageViewCreateInfo(
                const VkImage         &image,
                const VkFormat        &format
        );

        /** <b>Name</b><hr><br>
         *
         * VkInstanceCreateInfo - Structure specifying parameters of a newly created instance<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkInstanceCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkInstanceCreateInfo {
         *     VkStructureType             sType;
         *     const void*                 pNext;
         *     VkInstanceCreateFlags       flags;
         *     const VkApplicationInfo*    pApplicationInfo;
         *     uint32_t                    enabledLayerCount;
         *     const char* const*          ppEnabledLayerNames;
         *     uint32_t                    enabledExtensionCount;
         *     const char* const*          ppEnabledExtensionNames;
         * } VkInstanceCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkInstanceCreateFlagBits indicating the behavior of the instance.
         * <li>pApplicationInfo is NULL or a pointer to a VkApplicationInfo structure. If not NULL, this information helps implementations recognize behavior inherent to classes of applications. VkApplicationInfo is defined in detail below.
         * <li>enabledLayerCount is the number of global layers to enable.
         * <li>ppEnabledLayerNames is a pointer to an array of enabledLayerCount null-terminated UTF-8 strings containing the names of layers to enable for the created instance. The layers are loaded in the order they are listed in this array, with the first array element being the closest to the application, and the last array element being the closest to the driver. See the https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#extendingvulkan-layers section for further details.
         * <li>enabledExtensionCount is the number of global extensions to enable.
         * <li>ppEnabledExtensionNames is a pointer to an array of enabledExtensionCount null-terminated UTF-8 strings containing the names of extensions to enable.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * To capture events that occur while creating or destroying an instance, an application <b>can</b> link a VkDebugReportCallbackCreateInfoEXT structure or a VkDebugUtilsMessengerCreateInfoEXT structure to the pNext element of the VkInstanceCreateInfo structure given to vkCreateInstance. This callback is only valid for the duration of the vkCreateInstance and the vkDestroyInstance call. Use vkCreateDebugReportCallbackEXT or vkCreateDebugUtilsMessengerEXT to create persistent callback objects.<br><br>
         *
         * An application can add additional drivers by including the VkDirectDriverLoadingListLUNARG struct to the pNext element of the VkInstanceCreateInfo structure given to vkCreateInstance.
         *
         * @note VkDirectDriverLoadingListLUNARG allows applications to ship drivers with themselves. Only drivers that are designed to work with it should be used, such as drivers that implement Vulkan in software or that implement Vulkan by translating it to a different API. Any driver that requires installation should not be used, such as hardware drivers.
         */
        VkInstanceCreateInfo createVkInstanceCreateInfo(
                const VkApplicationInfo                &applicationInfo,
                const std::vector<const char *>        &enabledLayerNames,
                const std::vector<const char *>        &enabledExtensionNames
        );

        /** <b>Name</b><hr><br>
         *
         * VkGraphicsPipelineCreateInfo - Structure specifying parameters of a newly created graphics pipeline<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkGraphicsPipelineCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkGraphicsPipelineCreateInfo {
         *     VkStructureType                                  sType;
         *     const void*                                      pNext;
         *     VkPipelineCreateFlags                            flags;
         *     uint32_t                                         stageCount;
         *     const VkPipelineShaderStageCreateInfo*           pStages;
         *     const VkPipelineVertexInputStateCreateInfo*      pVertexInputState;
         *     const VkPipelineInputAssemblyStateCreateInfo*    pInputAssemblyState;
         *     const VkPipelineTessellationStateCreateInfo*     pTessellationState;
         *     const VkPipelineViewportStateCreateInfo*         pViewportState;
         *     const VkPipelineRasterizationStateCreateInfo*    pRasterizationState;
         *     const VkPipelineMultisampleStateCreateInfo*      pMultisampleState;
         *     const VkPipelineDepthStencilStateCreateInfo*     pDepthStencilState;
         *     const VkPipelineColorBlendStateCreateInfo*       pColorBlendState;
         *     const VkPipelineDynamicStateCreateInfo*          pDynamicState;
         *     VkPipelineLayout                                 layout;
         *     VkRenderPass                                     renderPass;
         *     uint32_t                                         subpass;
         *     VkPipeline                                       basePipelineHandle;
         *     int32_t                                          basePipelineIndex;
         * } VkGraphicsPipelineCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkPipelineCreateFlagBits specifying how the pipeline will be generated.
         * <li>stageCount is the number of entries in the pStages array.
         * <li>pStages is a pointer to an array of stageCount VkPipelineShaderStageCreateInfo structures describing the set of the shader stages to be included in the graphics pipeline.
         * <li>pVertexInputState is a pointer to a VkPipelineVertexInputStateCreateInfo structure. It is ignored if the pipeline includes a mesh shader stage. It <b>can</b> be NULL if the pipeline is created with the VK_DYNAMIC_STATE_VERTEX_INPUT_EXT dynamic state set.
         * <li>pInputAssemblyState is a pointer to a VkPipelineInputAssemblyStateCreateInfo structure which determines input assembly behavior for vertex shading, as described in Drawing Commands. If the VK_EXT_extended_dynamic_state3 extension is enabled, it <b>can</b> be NULL if the pipeline is created with both VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE, and VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY dynamic states set and dynamicPrimitiveTopologyUnrestricted is VK_TRUE. It is ignored if the pipeline includes a mesh shader stage.
         * <li>pTessellationState is a pointer to a VkPipelineTessellationStateCreateInfo structure defining tessellation state used by tessellation shaders. It <b>can</b> be NULL if the pipeline is created with the VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT dynamic state set.
         * <li>pViewportState is a pointer to a VkPipelineViewportStateCreateInfo structure defining viewport state used when rasterization is enabled. If the VK_EXT_extended_dynamic_state3 extension is enabled, it <b>can</b> be NULL if the pipeline is created with both VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT, and VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT dynamic states set.
         * <li>pRasterizationState is a pointer to a VkPipelineRasterizationStateCreateInfo structure defining rasterization state. If the VK_EXT_extended_dynamic_state3 extension is enabled, it <b>can</b> be NULL if the pipeline is created with all of VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT, VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE, VK_DYNAMIC_STATE_POLYGON_MODE_EXT, VK_DYNAMIC_STATE_CULL_MODE, VK_DYNAMIC_STATE_FRONT_FACE, VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE, VK_DYNAMIC_STATE_DEPTH_BIAS, and VK_DYNAMIC_STATE_LINE_WIDTH dynamic states set.
         * <li>pMultisampleState is a pointer to a VkPipelineMultisampleStateCreateInfo structure defining multisample state used when rasterization is enabled. If the VK_EXT_extended_dynamic_state3 extension is enabled, it <b>can</b> be NULL if the pipeline is created with all of VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT, VK_DYNAMIC_STATE_SAMPLE_MASK_EXT, and VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT dynamic states set, and either alphaToOne is disabled on the device or VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT is set, in which case VkPipelineMultisampleStateCreateInfo::sampleShadingEnable is assumed to be VK_FALSE.
         * <li>pDepthStencilState is a pointer to a VkPipelineDepthStencilStateCreateInfo structure defining depth/stencil state used when rasterization is enabled for depth or stencil attachments accessed during rendering. If the VK_EXT_extended_dynamic_state3 extension is enabled, it <b>can</b> be NULL if the pipeline is created with all of VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE, VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE, VK_DYNAMIC_STATE_DEPTH_COMPARE_OP, VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_OP, and VK_DYNAMIC_STATE_DEPTH_BOUNDS dynamic states set.
         * <li>pColorBlendState is a pointer to a VkPipelineColorBlendStateCreateInfo structure defining color blend state used when rasterization is enabled for any color attachments accessed during rendering. If the VK_EXT_extended_dynamic_state3 extension is enabled, it <b>can</b> be NULL if the pipeline is created with all of VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT, VK_DYNAMIC_STATE_LOGIC_OP_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT, VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT, and VK_DYNAMIC_STATE_BLEND_CONSTANTS dynamic states set.
         * <li>pDynamicState is a pointer to a VkPipelineDynamicStateCreateInfo structure defining which properties of the pipeline state object are dynamic and <b>can</b> be changed independently of the pipeline state. This <b>can</b> be NULL, which means no state in the pipeline is considered dynamic.
         * <li>layout is the description of binding locations used by both the pipeline and descriptor sets used with the pipeline.
         * <li>renderPass is a handle to a render pass object describing the environment in which the pipeline will be used. The pipeline <b>must</b> only be used with a render pass instance compatible with the one provided. See Render Pass Compatibility for more information.
         * <li>subpass is the index of the subpass in the render pass where this pipeline will be used.
         * <li>basePipelineHandle is a pipeline to derive from.
         * <li>basePipelineIndex is an index into the pCreateInfos parameter to use as a pipeline to derive from.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The parameters basePipelineHandle and basePipelineIndex are described in more detail in Pipeline Derivatives.<br><br>
         *
         * If any shader stage fails to compile, the compile log will be reported back to the application, and VK_ERROR_INVALID_SHADER_NV will be generated.
         *
         * @note With VK_EXT_extended_dynamic_state3, it is possible that many of the VkGraphicsPipelineCreateInfo members above <b>can</b> be NULL because all their state is dynamic and therefore ignored. This is optional so the application <b>can</b> still use a valid pointer if it needs to set the pNext or flags fields to specify state for other extensions.
         *
         * The state required for a graphics pipeline is divided into vertex input state, pre-rasterization shader state, fragment shader state, and fragment output state.<br><br>
         *
         * Vertex Input State<br><br>
         *
         * Vertex input state is defined by:
         * <ul>
         * <li>VkPipelineVertexInputStateCreateInfo
         * <li>VkPipelineInputAssemblyStateCreateInfo
         * </ul>
         *
         * If this pipeline specifies pre-rasterization state either directly or by including it as a pipeline library and its pStages includes a vertex shader, this state <b>must</b> be specified to create a complete graphics pipeline.<br><br>
         *
         * If a pipeline includes VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT in VkGraphicsPipelineLibraryCreateInfoEXT::flags either explicitly or as a default, and either the conditions requiring this state for a complete graphics pipeline are met or this pipeline does not specify pre-rasterization state in any way, that pipeline <b>must</b> specify this state directly.<br><br>
         *
         * Pre-Rasterization Shader State<br><br>
         *
         * Pre-rasterization shader state is defined by:
         * <ul>
         * <li>VkPipelineShaderStageCreateInfo entries for:
         *     <ul>
         *     <li>Vertex shaders
         *     <li>Tessellation control shaders
         *     <li>Tessellation evaluation shaders
         *     <li>Geometry shaders
         *     <li>Task shaders
         *     <li>Mesh shaders
         *     </ul>
         * <li>Within the VkPipelineLayout, all descriptor sets with pre-rasterization shader bindings if VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT was specified.
         *     <ul>
         *     <li>If VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT was not specified, the full pipeline layout must be specified.
         *     </ul>
         * <li>VkPipelineViewportStateCreateInfo
         * <li>VkPipelineRasterizationStateCreateInfo
         * <li>VkPipelineTessellationStateCreateInfo
         * <li>VkRenderPass and subpass parameter
         * <li>The viewMask parameter of VkPipelineRenderingCreateInfo (formats are ignored)
         * <li>VkPipelineDiscardRectangleStateCreateInfoEXT
         * <li>VkPipelineFragmentShadingRateStateCreateInfoKHR
         * </ul>
         * This state <b>must</b> be specified to create a complete graphics pipeline.<br><br>
         *
         * If either the pNext chain includes a VkGraphicsPipelineLibraryCreateInfoEXT structure with VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT included in flags, or it is not specified and would default to include that value, this state <b>must</b> be specified in the pipeline.
         *
         * Fragment Shader State<br><br>
         *
         * Fragment shader state is defined by:
         * <ul>
         * <li>A VkPipelineShaderStageCreateInfo entry for the fragment shader
         * <li>Within the VkPipelineLayout, all descriptor sets with fragment shader bindings if VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT was specified.
         *     <ul>
         *     <li>If VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT was not specified, the full pipeline layout must be specified.
         *     </ul>
         * <li>VkPipelineMultisampleStateCreateInfo if sample shading is enabled or renderpass is not VK_NULL_HANDLE
         * <li>VkPipelineDepthStencilStateCreateInfo
         * <li>VkRenderPass and subpass parameter
         * <li>The viewMask parameter of VkPipelineRenderingCreateInfo (formats are ignored)
         * <li>VkPipelineFragmentShadingRateStateCreateInfoKHR
         * <li>VkPipelineFragmentShadingRateEnumStateCreateInfoNV
         * <li>VkPipelineRepresentativeFragmentTestStateCreateInfoNV
         * <li>Inclusion/omission of the VK_PIPELINE_RASTERIZATION_STATE_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR flag
         * <li>Inclusion/omission of the VK_PIPELINE_RASTERIZATION_STATE_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT flag
         * <li>VkRenderingInputAttachmentIndexInfoKHR
         * </ul>
         * If a pipeline specifies pre-rasterization state either directly or by including it as a pipeline library and rasterizerDiscardEnable is set to VK_FALSE or VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE is used, this state <b>must</b> be specified to create a complete graphics pipeline.<br><br>
         *
         * If a pipeline includes VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT in VkGraphicsPipelineLibraryCreateInfoEXT::flags either explicitly or as a default, and either the conditions requiring this state for a complete graphics pipeline are met or this pipeline does not specify pre-rasterization state in any way, that pipeline <b>must</b> specify this state directly.<br><br>
         *
         * Fragment Output State<br><br>
         *
         * Fragment output state is defined by:
         * <ul>
         * <li>VkPipelineColorBlendStateCreateInfo
         * <li>VkRenderPass and subpass parameter
         * <li>VkPipelineMultisampleStateCreateInfo
         * <li>VkPipelineRenderingCreateInfo
         * <li>VkAttachmentSampleCountInfoAMD
         * <li>VkAttachmentSampleCountInfoNV
         * <li>VkExternalFormatANDROID
         * <li>Inclusion/omission of the VK_PIPELINE_CREATE_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT and VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT flags
         * <li>Inclusion/omission of the VK_PIPELINE_CREATE_2_ENABLE_LEGACY_DITHERING_BIT_EXT flag
         * <li>VkRenderingAttachmentLocationInfoKHR
         * </ul>
         * If a pipeline specifies pre-rasterization state either directly or by including it as a pipeline library and rasterizerDiscardEnable is set to VK_FALSE or VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE is used, this state <b>must</b> be specified to create a complete graphics pipeline.<br><br>
         *
         * If a pipeline includes VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT in VkGraphicsPipelineLibraryCreateInfoEXT::flags either explicitly or as a default, and either the conditions requiring this state for a complete graphics pipeline are met or this pipeline does not specify pre-rasterization state in any way, that pipeline <b>must</b> specify this state directly.<br><br>
         *
         * Dynamic State<br><br>
         *
         * Dynamic state values set via pDynamicState <b>must</b> be ignored if the state they correspond to is not otherwise statically set by one of the state subsets used to create the pipeline. Additionally, setting dynamic state values <b>must</b> not modify whether state in a linked library is static or dynamic; this is set and unchangeable when the library is created. For example, if a pipeline only included pre-rasterization shader state, then any dynamic state value corresponding to depth or stencil testing has no effect. Any linked library that has dynamic state enabled that same dynamic state <b>must</b> also be enabled in all the other linked libraries to which that dynamic state applies.<br><br>
         *
         * Complete Graphics Pipelines<br><br>
         *
         * A complete graphics pipeline always includes pre-rasterization shader state, with other subsets included depending on that state as specified in the above sections.<br><br>
         *
         * Graphics Pipeline Library Layouts<br><br>
         *
         * If different subsets are linked together with pipeline layouts created with VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT, the final effective pipeline layout is effectively the union of the linked pipeline layouts. When binding descriptor sets for this pipeline, the pipeline layout used <b>must</b> be compatible with this union. This pipeline layout <b>can</b> be overridden when linking with VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT by providing a VkPipelineLayout that is compatible with this union other than VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT, or when linking without VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT by providing a VkPipelineLayout that is fully compatible with this union.<br><br>
         *
         * If a VkPipelineCreateFlags2CreateInfoKHR structure is present in the pNext chain, VkPipelineCreateFlags2CreateInfoKHR::flags from that structure is used instead of flags from this structure.
         */
        VkGraphicsPipelineCreateInfo createVkGraphicsPipelineCreateInfo(
                const VkPipelineVertexInputStateCreateInfo                &vertexInputStateCreateInfo,
                const VkPipelineInputAssemblyStateCreateInfo              &inputAssemblyStateCreateInfo,
                const VkPipelineViewportStateCreateInfo                   &viewportStateCreateInfo,
                const VkPipelineRasterizationStateCreateInfo              &rasterizationStateCreateInfo,
                const VkPipelineMultisampleStateCreateInfo                &multisampleStateCreateInfo,
                const VkPipelineColorBlendStateCreateInfo                 &colorBlendStateCreateInfo,
                const std::vector<VkPipelineShaderStageCreateInfo>        &shaderStages,
                const VkPipelineLayout                                    &layout,
                const VkRenderPass                                        &renderPass
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipelineLayoutCreateInfo - Structure specifying the parameters of a newly created pipeline layout object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineLayoutCreateInfo structure is defined as:
         *
         * @code
         * typedef struct VkPipelineLayoutCreateInfo {
         *     VkStructureType                 sType;
         *     const void*                     pNext;
         *     VkPipelineLayoutCreateFlags     flags;
         *     uint32_t                        setLayoutCount;
         *     const VkDescriptorSetLayout*    pSetLayouts;
         *     uint32_t                        pushConstantRangeCount;
         *     const VkPushConstantRange*      pPushConstantRanges;
         * } VkPipelineLayoutCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is reserved for future use.
         * <li>setLayoutCount is the number of descriptor sets included in the pipeline layout.
         * <li>pSetLayouts is a pointer to an array of VkDescriptorSetLayout objects.
         * <li>pushConstantRangeCount is the number of push constant ranges included in the pipeline layout.
         * <li>pPushConstantRanges is a pointer to an array of VkPushConstantRange structures defining a set of push constant ranges for use in a single pipeline layout. In addition to descriptor set layouts, a pipeline layout also describes how many push constants <b>can</b> be accessed by each stage of the pipeline.
         * </ul>
         */
        VkPipelineLayoutCreateInfo createVkPipelineLayoutCreateInfo(
                const std::vector<VkDescriptorSetLayout>        &setLayouts,
                const std::vector<VkPushConstantRange>          &pushConstantRanges
        );

        /** <b>Name</b><hr><br>
         *
         * VkRenderPassCreateInfo - Structure specifying parameters of a newly created render pass<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkRenderPassCreateInfo structure is defined as:
         *
         * @code
         * typedef struct VkRenderPassCreateInfo {
         *     VkStructureType                   sType;
         *     const void*                       pNext;
         *     VkRenderPassCreateFlags           flags;
         *     uint32_t                          attachmentCount;
         *     const VkAttachmentDescription*    pAttachments;
         *     uint32_t                          subpassCount;
         *     const VkSubpassDescription*       pSubpasses;
         *     uint32_t                          dependencyCount;
         *     const VkSubpassDependency*        pDependencies;
         * } VkRenderPassCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is reserved for future use.
         * <li>attachmentCount is the number of attachments used by this render pass.
         * <li>pAttachments is a pointer to an array of attachmentCount VkAttachmentDescription structures describing the attachments used by the render pass.
         * <li>subpassCount is the number of subpasses to create.
         * <li>pSubpasses is a pointer to an array of subpassCount VkSubpassDescription structures describing each subpass.
         * <li>dependencyCount is the number of memory dependencies between pairs of subpasses.
         * <li>pDependencies is a pointer to an array of dependencyCount VkSubpassDependency structures describing dependencies between pairs of subpasses.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note Care should be taken to avoid a data race here; if any subpasses access attachments with overlapping memory locations, and one of those accesses is a write, a subpass dependency needs to be included between them.
         */
        VkRenderPassCreateInfo createVkRenderPassCreateInfo(
                const VkAttachmentDescription        &attachmentDescription,
                const VkSubpassDescription           &subpassDescription
        );

        /** <b>Name</b><hr><br>
         *
         * VkSemaphoreCreateInfo - Structure specifying parameters of a newly created semaphore<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSemaphoreCreateInfo structure is defined as:
         *
         * @code
         * typedef struct VkSemaphoreCreateInfo {
         *     VkStructureType           sType;
         *     const void*               pNext;
         *     VkSemaphoreCreateFlags    flags;
         * } VkSemaphoreCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is reserved for future use.
         * </ul>
         */
        VkSemaphoreCreateInfo createVkSemaphoreCreateInfo();

        /** <b>Name</b><hr><br>
         *
         * VkShaderModuleCreateInfo - Structure specifying parameters of a newly created shader module<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkShaderModuleCreateInfo structure is defined as:
         *
         * @code
         * typedef struct VkShaderModuleCreateInfo {
         *     VkStructureType              sType;
         *     const void*                  pNext;
         *     VkShaderModuleCreateFlags    flags;
         *     size_t                       codeSize;
         *     const uint32_t*              pCode;
         * } VkShaderModuleCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is reserved for future use.
         * <li>codeSize is the size, in bytes, of the code pointed to by pCode.
         * <li>pCode is a pointer to code that is used to create the shader module. The type and format of the code is determined from the content of the memory addressed by pCode.
         * </ul>
         */
        VkShaderModuleCreateInfo createVkShaderModuleCreateInfo(
                const std::vector<uint8_t>        &code
        );

        /** <b>Name</b><hr><br>
         *
         * VkSwapchainCreateInfoKHR - Structure specifying parameters of a newly created swapchain object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSwapchainCreateInfoKHR structure is defined as:
         *
         * @code
         * typedef struct VkSwapchainCreateInfoKHR {
         *     VkStructureType                  sType;
         *     const void*                      pNext;
         *     VkSwapchainCreateFlagsKHR        flags;
         *     VkSurfaceKHR                     surface;
         *     uint32_t                         minImageCount;
         *     VkFormat                         imageFormat;
         *     VkColorSpaceKHR                  imageColorSpace;
         *     VkExtent2D                       imageExtent;
         *     uint32_t                         imageArrayLayers;
         *     VkImageUsageFlags                imageUsage;
         *     VkSharingMode                    imageSharingMode;
         *     uint32_t                         queueFamilyIndexCount;
         *     const uint32_t*                  pQueueFamilyIndices;
         *     VkSurfaceTransformFlagBitsKHR    preTransform;
         *     VkCompositeAlphaFlagBitsKHR      compositeAlpha;
         *     VkPresentModeKHR                 presentMode;
         *     VkBool32                         clipped;
         *     VkSwapchainKHR                   oldSwapchain;
         * } VkSwapchainCreateInfoKHR;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is a bitmask of VkSwapchainCreateFlagBitsKHR indicating parameters of the swapchain creation.
         * <li>surface is the surface onto which the swapchain will present images. If the creation succeeds, the swapchain becomes associated with surface.
         * <li>minImageCount is the minimum number of presentable images that the application needs. The implementation will either create the swapchain with at least that many images, or it will fail to create the swapchain.
         * <li>imageFormat is a VkFormat value specifying the format the swapchain image(s) will be created with.
         * <li>imageColorSpace is a VkColorSpaceKHR value specifying the way the swapchain interprets image data.
         * <li>imageExtent is the size (in pixels) of the swapchain image(s). The behavior is platform-dependent if the image extent does not match the surface’s currentExtent as returned by vkGetPhysicalDeviceSurfaceCapabilitiesKHR.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note On some platforms, it is normal that maxImageExtent <b>may</b> become (0, 0), for example when the window is minimized. In such a case, it is not possible to create a swapchain due to the Valid Usage requirements.
         *
         * <ul>
         * <li>imageArrayLayers is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
         * <li>imageUsage is a bitmask of VkImageUsageFlagBits describing the intended usage of the (acquired) swapchain images.
         * <li>imageSharingMode is the sharing mode used for the image(s) of the swapchain.
         * <li>queueFamilyIndexCount is the number of queue families having access to the image(s) of the swapchain when imageSharingMode is VK_SHARING_MODE_CONCURRENT.
         * <li>pQueueFamilyIndices is a pointer to an array of queue family indices having access to the images(s) of the swapchain when imageSharingMode is VK_SHARING_MODE_CONCURRENT.
         * <li>preTransform is a VkSurfaceTransformFlagBitsKHR value describing the transform, relative to the presentation engine’s natural orientation, applied to the image content prior to presentation. If it does not match the currentTransform value returned by vkGetPhysicalDeviceSurfaceCapabilitiesKHR, the presentation engine will transform the image content as part of the presentation operation.
         * <li>compositeAlpha is a VkCompositeAlphaFlagBitsKHR value indicating the alpha compositing mode to use when this surface is composited together with other surfaces on certain window systems.
         * <li>presentMode is the presentation mode the swapchain will use. A swapchain’s present mode determines how incoming present requests will be processed and queued internally.
         * <li>clipped specifies whether the Vulkan implementation is allowed to discard rendering operations that affect regions of the surface that are not visible.
         *     <ul>
         *     <li>If set to VK_TRUE, the presentable images associated with the swapchain <b>may</b> not own all of their pixels. Pixels in the presentable images that correspond to regions of the target surface obscured by another window on the desktop, or subject to some other clipping mechanism will have undefined content when read back. Fragment shaders <b>may</b> not execute for these pixels, and thus any side effects they would have had will not occur. VK_TRUE value does not guarantee any clipping will occur, but allows more optimal presentation methods to be used on some platforms.
         *     <li>If set to VK_FALSE, presentable images associated with the swapchain will own all of the pixels they contain.
         *     </ul>
         * </ul>
         * @note Applications <b>should</b> set this value to VK_TRUE if they do not expect to read back the content of presentable images before presenting them or after reacquiring them, and if their fragment shaders do not have any side effects that require them to run for all pixels in the presentable image.
         *
         * <ul>
         * <li> oldSwapchain is VK_NULL_HANDLE, or the existing non-retired swapchain currently associated with surface. Providing a valid oldSwapchain <b>may</b> aid in the resource reuse, and also allows the application to still present any images that are already acquired from it.
         * </ul>
         *
         * Upon calling vkCreateSwapchainKHR with an oldSwapchain that is not VK_NULL_HANDLE, oldSwapchain is retired — even if creation of the new swapchain fails. The new swapchain is created in the non-retired state whether or not oldSwapchain is VK_NULL_HANDLE.<br><br>
         *
         * Upon calling vkCreateSwapchainKHR with an oldSwapchain that is not VK_NULL_HANDLE, any images from oldSwapchain that are not acquired by the application <b>may</b> be freed by the implementation, which <b>may</b> occur even if creation of the new swapchain fails. The application <b>can</b> destroy oldSwapchain to free all memory associated with oldSwapchain.<br><br>
         *
         * @note Multiple retired swapchains <b>can</b> be associated with the same VkSurfaceKHR through multiple uses of oldSwapchain that outnumber calls to vkDestroySwapchainKHR.<br><br>
         * After oldSwapchain is retired, the application <b>can</b> pass to vkQueuePresentKHR any images it had already acquired from oldSwapchain. E.g., an application may present an image from the old swapchain before an image from the new swapchain is ready to be presented. As usual, vkQueuePresentKHR <b>may</b> fail if oldSwapchain has entered a state that causes VK_ERROR_OUT_OF_DATE_KHR to be returned.<br><br>
         * The application <b>can</b> continue to use a shared presentable image obtained from oldSwapchain until a presentable image is acquired from the new swapchain, as long as it has not entered a state that causes it to return VK_ERROR_OUT_OF_DATE_KHR.
         */
        VkSwapchainCreateInfoKHR createVkSwapchainCreateInfoKHR(
                const VkSurfaceCapabilitiesKHR        &capabilities,
                const uint32_t                        &minImageCount,
                const VkSurfaceFormatKHR              &format,
                const VkExtent2D                      &extent,
                const VkPresentModeKHR                &presentMode,
                const VkSurfaceKHR                    &surface,
                const VkSharingMode                   &sharingMode,
                const std::vector<uint32_t>           &queueFamilyIndices
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSetLayoutBinding - Structure specifying a descriptor set layout binding<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorSetLayoutBinding structure is defined as:
         *
         * @code
         * typedef struct VkDescriptorSetLayoutBinding {
         *     uint32_t              binding;
         *     VkDescriptorType      descriptorType;
         *     uint32_t              descriptorCount;
         *     VkShaderStageFlags    stageFlags;
         *     const VkSampler*      pImmutableSamplers;
         * } VkDescriptorSetLayoutBinding;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>binding is the binding number of this entry and corresponds to a resource of the same binding number in the shader stages.
         * <li>descriptorType is a VkDescriptorType specifying which type of resource descriptors are used for this binding.
         * <li>descriptorCount is the number of descriptors contained in the binding, accessed in a shader as an array , except if descriptorType is VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT in which case descriptorCount is the size in bytes of the inline uniform block . If descriptorCount is zero this binding entry is reserved and the resource <b>must</b> not be accessed from any stage via this binding within any pipeline using the set layout.
         * <li>stageFlags member is a bitmask of VkShaderStageFlagBits specifying which pipeline shader stages <b>can</b> access a resource for this binding. VK_SHADER_STAGE_ALL is a shorthand specifying that all defined shader stages, including any additional stages defined by extensions, <b>can</b> access the resource.
         * <li>If a shader stage is not included in stageFlags, then a resource <b>must</b> not be accessed from that stage via this binding within any pipeline using the set layout. Other than input attachments which are limited to the fragment shader, there are no limitations on what combinations of stages <b>can</b> use a descriptor binding, and in particular a binding <b>can</b> be used by both graphics stages and the compute stage.
         * </ul><br>
         * <b>Description</b><hr><br>
         * <ul>
         * <li>pImmutableSamplers affects initialization of samplers. If descriptorType specifies a VK_DESCRIPTOR_TYPE_SAMPLER or VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER type descriptor, then pImmutableSamplers <b>can</b> be used to initialize a set of immutable samplers. Immutable samplers are permanently bound into the set layout and <b>must</b> not be changed; updating a VK_DESCRIPTOR_TYPE_SAMPLER descriptor with immutable samplers is not allowed and updates to a VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER descriptor with immutable samplers does not modify the samplers (the image views are updated, but the sampler updates are ignored). If pImmutableSamplers is not NULL, then it points to an array of sampler handles that will be copied into the set layout and used for the corresponding binding. Only the sampler handles are copied; the sampler objects <b>must</b> not be destroyed before the final use of the set layout and any descriptor pools and sets created using it. If pImmutableSamplers is NULL, then the sampler slots are dynamic and sampler handles <b>must</b> be bound into descriptor sets using this layout. If descriptorType is not one of these descriptor types, then pImmutableSamplers is ignored.
         * </ul>
         * The above layout definition allows the descriptor bindings to be specified sparsely such that not all binding numbers between 0 and the maximum binding number need to be specified in the pBindings array. Bindings that are not specified have a descriptorCount and stageFlags of zero, and the value of descriptorType is undefined. However, all binding numbers between 0 and the maximum binding number in the VkDescriptorSetLayoutCreateInfo::pBindings array <b>may</b> consume memory in the descriptor set layout even if not all descriptor bindings are used, though it <b>should</b> not consume additional memory from the descriptor pool.
         */
        VkDescriptorSetLayoutBinding createVkDescriptorSetLayoutBinding(
                const uint32_t                  &binding,
                const VkDescriptorType          &descriptorType,
                const uint32_t                  &descriptorCount,
                const VkShaderStageFlags        &stageFlags,
                const VkSampler                 *pImmutableSamplers
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSetLayoutCreateInfo - Structure specifying parameters of a newly created descriptor set layout<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Information about the descriptor set layout is passed in a VkDescriptorSetLayoutCreateInfo structure:
         *
         * @code
         * typedef struct VkDescriptorSetLayoutCreateInfo {
         *     VkStructureType                        sType;
         *     const void*                            pNext;
         *     VkDescriptorSetLayoutCreateFlags       flags;
         *     uint32_t                               bindingCount;
         *     const VkDescriptorSetLayoutBinding*    pBindings;
         * } VkDescriptorSetLayoutCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is a bitmask of VkDescriptorSetLayoutCreateFlagBits specifying options for descriptor set layout creation.
         * <li>bindingCount is the number of elements in pBindings.
         * <li>pBindings is a pointer to an array of VkDescriptorSetLayoutBinding structures.
         * </ul>
         */
        VkDescriptorSetLayoutCreateInfo createVkDescriptorSetLayoutCreateInfo(
                const std::vector<VkDescriptorSetLayoutBinding>        &bindings
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorPoolSize - Structure specifying descriptor pool size<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorPoolSize structure is defined as:
         *
         * @code
         * typedef struct VkDescriptorPoolSize {
         *     VkDescriptorType    type;
         *     uint32_t            descriptorCount;
         * } VkDescriptorPoolSize;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>type is the type of descriptor.
         * <li>descriptorCount is the number of descriptors of that type to allocate. If type is VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT then descriptorCount is the number of bytes to allocate for descriptors of this type.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note When creating a descriptor pool that will contain descriptors for combined image samplers of multi-planar formats, an application needs to account for non-trivial descriptor consumption when choosing the descriptorCount value, as indicated by VkSamplerYcbcrConversionImageFormatProperties::combinedImageSamplerDescriptorCount.
         */
        VkDescriptorPoolSize createVkDescriptorPoolSize(
                const VkDescriptorType        &type,
                const uint32_t                &descriptorCount
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorPoolCreateInfo - Structure specifying parameters of a newly created descriptor pool<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Additional information about the pool is passed in a VkDescriptorPoolCreateInfo structure:
         *
         * @code
         * typedef struct VkDescriptorPoolCreateInfo {
         *     VkStructureType                sType;
         *     const void*                    pNext;
         *     VkDescriptorPoolCreateFlags    flags;
         *     uint32_t                       maxSets;
         *     uint32_t                       poolSizeCount;
         *     const VkDescriptorPoolSize*    pPoolSizes;
         * } VkDescriptorPoolCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>flags is a bitmask of VkDescriptorPoolCreateFlagBits specifying certain supported operations on the pool.
         * <li>maxSets is the maximum number of descriptor sets that <b>can</b> be allocated from the pool.
         * <li>poolSizeCount is the number of elements in pPoolSizes.
         * <li>pPoolSizes is a pointer to an array of VkDescriptorPoolSize structures, each containing a descriptor type and number of descriptors of that type to be allocated in the pool.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * If multiple VkDescriptorPoolSize structures appear in the pPoolSizes array then the pool will be created with enough storage for the total number of descriptors of each type.<br><br>
         *
         * Fragmentation of a descriptor pool is possible and <b>may</b> lead to descriptor set allocation failures. A failure due to fragmentation is defined as failing a descriptor set allocation despite the sum of all outstanding descriptor set allocations from the pool plus the requested allocation requiring no more than the total number of descriptors requested at pool creation. Implementations provide certain guarantees of when fragmentation <b>must</b> not cause allocation failure, as described below.<br><br>
         *
         * If a descriptor pool has not had any descriptor sets freed since it was created or most recently reset then fragmentation <b>must</b> not cause an allocation failure (note that this is always the case for a pool created without the VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT bit set). Additionally, if all sets allocated from the pool since it was created or most recently reset use the same number of descriptors (of each type) and the requested allocation also uses that same number of descriptors (of each type), then fragmentation <b>must</b> not cause an allocation failure.<br><br>
         *
         * If an allocation failure occurs due to fragmentation, an application <b>can</b> create an additional descriptor pool to perform further descriptor set allocations.<br><br>
         *
         * If flags has the VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT bit set, descriptor pool creation <b>may</b> fail with the error VK_ERROR_FRAGMENTATION if the total number of descriptors across all pools (including this one) created with this bit set exceeds maxUpdateAfterBindDescriptorsInAllPools, or if fragmentation of the underlying hardware resources occurs.
         */
        VkDescriptorPoolCreateInfo createVkDescriptorPoolCreateInfo(
                const uint32_t                                 &maxSets,
                const std::vector<VkDescriptorPoolSize>        &poolSizes
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSetAllocateInfo - Structure specifying the allocation parameters for descriptor sets<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorSetAllocateInfo structure is defined as:
         *
         * @code
         * typedef struct VkDescriptorSetAllocateInfo {
         *     VkStructureType                 sType;
         *     const void*                     pNext;
         *     VkDescriptorPool                descriptorPool;
         *     uint32_t                        descriptorSetCount;
         *     const VkDescriptorSetLayout*    pSetLayouts;
         * } VkDescriptorSetAllocateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>descriptorPool is the pool which the sets will be allocated from.
         * <li>descriptorSetCount determines the number of descriptor sets to be allocated from the pool.
         * <li>pSetLayouts is a pointer to an array of descriptor set layouts, with each member specifying how the corresponding descriptor set is allocated.
         * </ul>
         */
        VkDescriptorSetAllocateInfo createVkDescriptorSetAllocateInfo(
                const VkDescriptorPool                          &descriptorPool,
                const std::vector<VkDescriptorSetLayout>        &setLayouts
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorBufferInfo - Structure specifying descriptor buffer info<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorBufferInfo structure is defined as:
         *
         * @code
         * typedef struct VkDescriptorBufferInfo {
         *     VkBuffer        buffer;
         *     VkDeviceSize    offset;
         *     VkDeviceSize    range;
         * } VkDescriptorBufferInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>buffer is the buffer resource.
         * <li>offset is the offset in bytes from the start of buffer. Access to buffer memory via this descriptor uses addressing that is relative to this starting offset.
         * <li>range is the size in bytes that is used for this descriptor update, or VK_WHOLE_SIZE to use the range from offset to the end of the buffer.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note When setting range to VK_WHOLE_SIZE, the effective range <b>must</b> not be larger than the maximum range for the descriptor type (maxUniformBufferRange or maxStorageBufferRange). This means that VK_WHOLE_SIZE is not typically useful in the common case where uniform buffer descriptors are suballocated from a buffer that is much larger than maxUniformBufferRange.
         *
         * For VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC and VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC descriptor types, offset is the base offset from which the dynamic offset is applied and range is the static size used for all dynamic offsets.
         */
        VkDescriptorBufferInfo createVkDescriptorBufferInfo(
                const VkBuffer            &buffer,
                const VkDeviceSize        &offset,
                const VkDeviceSize        &range
        );

        /** <b>Name</b><hr><br>
         *
         * VkWriteDescriptorSet - Structure specifying the parameters of a descriptor set write operation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkWriteDescriptorSet structure is defined as:
         *
         * @code
         * typedef struct VkWriteDescriptorSet {
         *     VkStructureType                  sType;
         *     const void*                      pNext;
         *     VkDescriptorSet                  dstSet;
         *     uint32_t                         dstBinding;
         *     uint32_t                         dstArrayElement;
         *     uint32_t                         descriptorCount;
         *     VkDescriptorType                 descriptorType;
         *     const VkDescriptorImageInfo*     pImageInfo;
         *     const VkDescriptorBufferInfo*    pBufferInfo;
         *     const VkBufferView*              pTexelBufferView;
         * } VkWriteDescriptorSet;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is the type of this structure.
         * <li>pNext is NULL or a pointer to an extension-specific structure.
         * <li>dstSet is the destination descriptor set to update.
         * <li>dstBinding is the descriptor binding within that set.
         * <li>dstArrayElement is the starting element in that array. If the descriptor binding identified by dstSet and dstBinding has a descriptor type of VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT then dstArrayElement specifies the starting byte offset within the binding.
         * <li>descriptorCount is the number of descriptors to update (the number of elements in pImageInfo, pBufferInfo, or pTexelBufferView , or a value matching the dataSize member of a VkWriteDescriptorSetInlineUniformBlockEXT structure in the pNext chain , or a value matching the accelerationStructureCount of a VkWriteDescriptorSetAccelerationStructureNV structure in the pNext chain ). If the descriptor binding identified by dstSet and dstBinding has a descriptor type of VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT then descriptorCount specifies the number of bytes to update.
         * <li>descriptorType is a VkDescriptorType specifying the type of each descriptor in pImageInfo, pBufferInfo, or pTexelBufferView, as described below. It <b>must</b> be the same type as that specified in VkDescriptorSetLayoutBinding for dstSet at dstBinding. The type of the descriptor also controls which array the descriptors are taken from.
         * <li>pImageInfo is a pointer to an array of VkDescriptorImageInfo structures or is ignored, as described below.
         * <li>pBufferInfo is a pointer to an array of VkDescriptorBufferInfo structures or is ignored, as described below.
         * <li>pTexelBufferView is a pointer to an array of VkBufferView handles as described in the Buffer Views section or is ignored, as described below.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Only one of pImageInfo, pBufferInfo, or pTexelBufferView members is used according to the descriptor type specified in the descriptorType member of the containing VkWriteDescriptorSet structure, or none of them in case descriptorType is VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT, in which case the source data for the descriptor writes is taken from the VkWriteDescriptorSetInlineUniformBlockEXT structure included in the pNext chain of VkWriteDescriptorSet, or if descriptorType is VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV, in which case the source data for the descriptor writes is taken from the VkWriteDescriptorSetAccelerationStructureNV structure in the pNext chain of VkWriteDescriptorSet, as specified below.<br><br>
         *
         * If the dstBinding has fewer than descriptorCount array elements remaining starting from dstArrayElement, then the remainder will be used to update the subsequent binding - dstBinding+1 starting at array element zero. If a binding has a descriptorCount of zero, it is skipped. This behavior applies recursively, with the update affecting consecutive bindings as needed to update all descriptorCount descriptors.
         *
         * @note The same behavior applies to bindings with a descriptor type of VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT where descriptorCount specifies the number of bytes to update while dstArrayElement specifies the starting byte offset, thus in this case if the dstBinding has a smaller byte size than the sum of dstArrayElement and descriptorCount, then the remainder will be used to update the subsequent binding - dstBinding+1 starting at offset zero. This falls out as a special case of the above rule.
         */
        VkWriteDescriptorSet createVkWriteDescriptorSet(
                const VkDescriptorSet               &dstSet,
                const uint32_t                      &dstBinding,
                const uint32_t                      &dstArrayElement,
                const uint32_t                      &descriptorCount,
                const VkDescriptorType              &descriptorType,
                const VkDescriptorImageInfo         *pImageInfo,
                const VkDescriptorBufferInfo        *pBufferInfo,
                const VkBufferView                  *pTexelBufferView
        );

        /** <b>Name</b><hr><br>
         *
         * VkBuffer - Opaque handle to a buffer object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Buffers represent linear arrays of data which are used for various purposes by binding them to a graphics or compute pipeline via descriptor sets or certain commands, or by directly specifying them as parameters to certain commands.<br><br>
         *
         * Buffers are represented by VkBuffer handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBuffer)
         * @endcode
         */
        VkBuffer createVkBuffer(
                 const VkDevice                     &device,
                 const VkDeviceSize                 &size,
                 const VkBufferUsageFlags           &usage,
                 const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkCommandBuffer - Opaque handle to a command buffer object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Command buffers are objects used to record commands which <b>can</b> be subsequently submitted to a device queue for execution. There are two levels of command buffers - primary command buffers, which <b>can</b> execute secondary command buffers, and which are submitted to queues, and secondary command buffers, which <b>can</b> be executed by primary command buffers, and which are not directly submitted to queues.<br><br>
         *
         * Command buffers are represented by VkCommandBuffer handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_HANDLE(VkCommandBuffer)
         * @endcode
         */
        VkCommandBuffer createVkCommandBuffer(
                const VkCommandPool        &commandPool,
                const VkDevice             &device
        );

        /** <b>Name</b><hr><br>
         *
         * VkCommandPool - Opaque handle to a command pool object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Command pools are opaque objects that command buffer memory is allocated from, and which allow the implementation to amortize the cost of resource creation across multiple command buffers. Command pools are externally synchronized, meaning that a command pool <b>must</b> not be used concurrently in multiple threads. That includes use via recording commands on any command buffers allocated from the pool, as well as operations that allocate, free, and reset command buffers or the pool itself.<br><br>
         *
         * Command pools are represented by VkCommandPool handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCommandPool)
         * @endcode
         */
        VkCommandPool createVkCommandPool(
                const uint32_t                     &queueFamilyIndex,
                const VkDevice                     &device,
                const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorPool - Opaque handle to a descriptor pool object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A descriptor pool maintains a pool of descriptors, from which descriptor sets are allocated. Descriptor pools are externally synchronized, meaning that the application <b>must</b> not allocate and/or free descriptor sets from the same pool in multiple threads simultaneously.<br><br>
         *
         * Descriptor pools are represented by VkDescriptorPool handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorPool)
         * @endcode
         */
        VkDescriptorPool createVkDescriptorPool(
                const VkDevice                                 &device,
                const uint32_t                                 &descriptorCount,
                const std::vector<VkDescriptorPoolSize>        &poolSizes,
                const VkAllocationCallbacks                    *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSet - Opaque handle to a descriptor set object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Descriptor sets are allocated from descriptor pool objects, and are represented by VkDescriptorSet handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSet)
         * @endcode
         */
        std::vector<VkDescriptorSet> createVkDescriptorSets(
                const VkDevice                                  &device,
                const VkDescriptorPool                          &pool,
                const std::vector<VkDescriptorSetLayout>        &descriptorSetLayouts
        );

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSetLayout - Opaque handle to a descriptor set layout object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A descriptor set layout object is defined by an array of zero or more descriptor bindings. Each individual descriptor binding is specified by a descriptor type, a count (array size) of the number of descriptors in the binding, a set of shader stages that <b>can</b> access the binding, and (if using immutable samplers) an array of sampler descriptors.<br><br>
         *
         * Descriptor set layout objects are represented by VkDescriptorSetLayout handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSetLayout)
         * @endcode
         */
        VkDescriptorSetLayout createVkDescriptorSetLayout(
                const VkDevice                                         &device,
                const std::vector<VkDescriptorSetLayoutBinding>        &bindings,
                const VkAllocationCallbacks                            *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkDevice - Opaque handle to a device object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Logical devices are represented by VkDevice handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_HANDLE(VkDevice)
         * @endcode
         */
        VkDevice createVkDevice(
                const VkPhysicalDevice                 &physicalDevice,
                const std::vector<uint32_t>            &queueFamilyIndices,
                const std::vector<const char *>        &enabledExtensionNames,
                const VkAllocationCallbacks            *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkFence - Opaque handle to a fence object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Fences are a synchronization primitive that <b>can</b> be used to insert a dependency from a queue to the host. Fences have two states - signaled and unsignaled. A fence <b>can</b> be signaled as part of the execution of a queue submission command. Fences <b>can</b> be unsignaled on the host with vkResetFences. Fences <b>can</b> be waited on by the host with the vkWaitForFences command, and the current state <b>can</b> be queried with vkGetFenceStatus.<br><br>
         *
         * The internal data of a fence <b>may</b> include a reference to any resources and pending work associated with signal or unsignal operations performed on that fence object, collectively referred to as the fence’s payload. Mechanisms to import and export that internal data to and from fences are provided below. These mechanisms indirectly enable applications to share fence state between two or more fences and other synchronization primitives across process and API boundaries.<br><br>
         *
         * Fences are represented by VkFence handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFence)
         * @endcode
         */
        VkFence createVkFence(
                const VkDevice                     &device,
                const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkFramebuffer - Opaque handle to a framebuffer object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Render passes operate in conjunction with framebuffers. Framebuffers represent a collection of specific memory attachments that a render pass instance uses.<br><br>
         *
         * Framebuffers are represented by VkFramebuffer handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFramebuffer)
         * @endcode
         */
        VkFramebuffer createVkFramebuffer(
                const VkRenderPass                     &renderPass,
                const VkExtent2D                       &extent,
                const std::vector<VkImageView>         &imageViews,
                const VkDevice                         &device,
                const VkAllocationCallbacks            *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkImageView - Opaque handle to an image view object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Image objects are not directly accessed by pipeline shaders for reading or writing image data. Instead, image views representing contiguous ranges of the image subresources and containing additional metadata are used for that purpose. Views <b>must</b> be created on images of compatible types, and <b>must</b> represent a valid subset of image subresources.<br><br>
         *
         * Image views are represented by VkImageView handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImageView)
         * @endcode
         */
        VkImageView createVkImageView(
                const VkImage                      &image,
                const VkFormat                     &format,
                const VkDevice                     &device,
                const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkInstance - Opaque handle to an instance object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * There is no global state in Vulkan and all per-application state is stored in a VkInstance object. Creating a VkInstance object initializes the Vulkan library and allows the application to pass information about itself to the implementation.<br><br>
         *
         * Instances are represented by VkInstance handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_HANDLE(VkInstance)
         * @endcode
         */
        VkInstance createVkInstance(
                const char                             *name,
                const uint32_t                         &version,
                const std::vector<const char *>        &enabledLayerNames,
                const std::vector<const char *>        &enabledExtensionNames,
                const VkAllocationCallbacks            *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipeline - Opaque handle to a pipeline object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Compute, ray tracing, and graphics pipelines are each represented by VkPipeline handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipeline)
         * @endcode
         */
        VkPipeline createVkPipeline(
                const VkDevice                                              &device,
                const VkRenderPass                                          &renderPass,
                const std::vector<VkViewport>                               &viewports,
                const std::vector<VkRect2D>                                 &scissors,
                const VkPipelineLayout                                      &layout,
                const std::vector<VkPipelineShaderStageCreateInfo>          &shaderStages,
                const std::vector<VkVertexInputBindingDescription>          &bindingDescriptions,
                const std::vector<VkVertexInputAttributeDescription>        &attributeDescriptions,
                const VkAllocationCallbacks                                 *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipelineLayout - Opaque handle to a pipeline layout object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Access to descriptor sets from a pipeline is accomplished through a pipeline layout. Zero or more descriptor set layouts and zero or more push constant ranges are combined to form a pipeline layout object describing the complete set of resources that <b>can</b> be accessed by a pipeline. The pipeline layout represents a sequence of descriptor sets with each having a specific layout. This sequence of layouts is used to determine the interface between shader stages and shader resources. Each pipeline is created using a pipeline layout.<br><br>
         *
         * Pipeline layout objects are represented by VkPipelineLayout handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineLayout)
         * @endcode
         */
        VkPipelineLayout createVkPipelineLayout(
                const VkDevice                                  &device,
                const std::vector<VkDescriptorSetLayout>        &setLayouts,
                const std::vector<VkPushConstantRange>          &pushConstantRanges,
                const VkAllocationCallbacks                     *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkRenderPass - Opaque handle to a render pass object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A render pass object represents a collection of attachments, subpasses, and dependencies between the subpasses, and describes how the attachments are used over the course of the subpasses.<br><br>
         *
         * Render passes are represented by VkRenderPass handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkRenderPass)
         * @endcode
         */
        VkRenderPass createVkRenderPass(
                const VkPhysicalDevice             &physicalDevice,
                const VkDevice                     &device,
                const VkSurfaceKHR                 &surface,
                const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkSemaphore - Opaque handle to a semaphore object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Semaphores are a synchronization primitive that <b>can</b> be used to insert a dependency between queue operations or between a queue operation and the host. Binary semaphores have two states - signaled and unsignaled. Timeline semaphores have a strictly increasing 64-bit unsigned integer payload and are signaled with respect to a particular reference value. A semaphore <b>can</b> be signaled after execution of a queue operation is completed, and a queue operation <b>can</b> wait for a semaphore to become signaled before it begins execution. A timeline semaphore <b>can</b> additionally be signaled from the host with the vkSignalSemaphore command and waited on from the host with the vkWaitSemaphores command.<br><br>
         *
         * The internal data of a semaphore <b>may</b> include a reference to any resources and pending work associated with signal or unsignal operations performed on that semaphore object, collectively referred to as the semaphore’s payload. Mechanisms to import and export that internal data to and from semaphores are provided below. These mechanisms indirectly enable applications to share semaphore state between two or more semaphores and other synchronization primitives across process and API boundaries.<br><br>
         *
         * Semaphores are represented by VkSemaphore handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSemaphore)
         * @endcode
         */
        VkSemaphore createVkSemaphore(
                const VkDevice                     &device,
                const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkShaderModule - Opaque handle to a shader module object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Shader modules contain shader code and one or more entry points. Shaders are selected from a shader module by specifying an entry point as part of pipeline creation. The stages of a pipeline <b>can</b> use shaders that come from different modules. The shader code defining a shader module <b>must</b> be in the SPIR-V format, as described by the Vulkan Environment for SPIR-V appendix.<br><br>
         *
         * Shader modules are represented by VkShaderModule handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkShaderModule)
         * @endcode
         */
        VkShaderModule createVkShaderModule(
                const std::vector<uint8_t>         &code,
                const VkDevice                     &device,
                const VkAllocationCallbacks        *pAllocator
        );

        /** <b>Name</b><hr><br>
         *
         * VkSwapchainKHR - Opaque handle to a swapchain object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A swapchain object (a.k.a. swapchain) provides the ability to present rendering results to a surface. Swapchain objects are represented by VkSwapchainKHR handles:
         *
         * @code
         * // Provided by VK_KHR_swapchain
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSwapchainKHR)
         * @endcode
         *
         * <b>Description</b><hr><br>
         * A swapchain is an abstraction for an array of presentable images that are associated with a surface. The presentable images are represented by VkImage objects created by the platform. One image (which <b>can</b> be an array image for multiview/stereoscopic-3D surfaces) is displayed at a time, but multiple images <b>can</b> be queued for presentation. An application renders to the image, and then queues the image for presentation to the surface.<br><br>
         *
         * A native window <b>cannot</b> be associated with more than one non-retired swapchain at a time. Further, swapchains <b>cannot</b> be created for native windows that have a non-Vulkan graphics API surface associated with them.
         *
         * @note The presentation engine is an abstraction for the platform’s compositor or display engine.<br><br>
         * The presentation engine <b>may</b> be synchronous or asynchronous with respect to the application and/or logical device.<br><br>
         * Some implementations <b>may</b> use the device’s graphics queue or dedicated presentation hardware to perform presentation.
         *
         * The presentable images of a swapchain are owned by the presentation engine. An application <b>can</b> acquire use of a presentable image from the presentation engine. Use of a presentable image <b>must</b> occur only after the image is returned by vkAcquireNextImageKHR, and before it is released by vkQueuePresentKHR. This includes transitioning the image layout and rendering commands.<br><br>
         *
         * An application <b>can</b> acquire use of a presentable image with vkAcquireNextImageKHR. After acquiring a presentable image and before modifying it, the application <b>must</b> use a synchronization primitive to ensure that the presentation engine has finished reading from the image. The application <b>can</b> then transition the image’s layout, queue rendering commands to it, etc. Finally, the application presents the image with vkQueuePresentKHR, which releases the acquisition of the image. The application <b>can</b> also release the acquisition of the image through vkReleaseSwapchainImagesEXT, if the image is not in use by the device, and skip the present operation.<br><br>
         *
         * The presentation engine controls the order in which presentable images are acquired for use by the application.
         *
         * @note This allows the platform to handle situations which require out-of-order return of images after presentation. At the same time, it allows the application to generate command buffers referencing all of the images in the swapchain at initialization time, rather than in its main loop.
         */
        VkSwapchainKHR createVkSwapchainKHR(
                const VkDevice                             &device,
                const VkSurfaceKHR                         &surface,
                const std::vector<VkPresentModeKHR>        &presentModes,
                const VkSurfaceCapabilitiesKHR             &capabilities,
                const std::vector<uint32_t>                &queueFamilyIndices,
                const VkSurfaceFormatKHR                   &format,
                const VkExtent2D                           &extent,
                const VkAllocationCallbacks                *pAllocator
        );

}

#endif // VULKANPP_HPP_HEADER