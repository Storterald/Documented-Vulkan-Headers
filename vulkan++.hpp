#pragma once

#ifndef VULKANPP_HPP
#define VULKANPP_HPP

#ifdef VULKANPP_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#endif

#include <vector>

#ifdef VULKAN_HPP
        #error "Vulkan++ should not be used with the vulkan.hpp header."
#endif

#ifdef VULKANPP_ENABLE_CONSTEXPR
        #define VULKANPP_CONSTEXPR inline constexpr
#else
        #define VULKANPP_CONSTEXPR inline
#endif

namespace vk {

        /** <b>Name</b><hr><br>
         *
         * VkBool32 - Vulkan boolean type<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * VkBool32 represents boolean True and False values, since C does not have a sufficiently portable built-in boolean type:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef uint32_t VkBool32;
         * @endcode
         *
         * <b>Description</b><hr><br>
         *
         * VK_TRUE represents a boolean <b>True</b> (unsigned integer 1) value, and VK_FALSE a boolean <b>False</b> (unsigned integer 0) value.<br><br>
         *
         * All values returned from a Vulkan implementation in a VkBool32 will be either VK_TRUE or VK_FALSE.<br><br>
         *
         * Applications <b>must</b> not pass any other values than VK_TRUE or VK_FALSE into a Vulkan implementation where a VkBool32 is expected.
         */
        using Bool32 = VkBool32;

        /** <b>Name</b><hr><br>
         *
         * VkResult - Vulkan command return codes<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * While the core Vulkan API is not designed to capture incorrect usage, some circumstances still require return codes. Commands in Vulkan return their status via return codes that are in one of two categories:
         * <ul>
         * <li>Successful completion codes are returned when a command needs to communicate success or status information. All successful completion codes are non-negative values.
         * <li>Run time error codes are returned when a command needs to communicate a failure that could only be detected at runtime. All runtime error codes are negative values.
         * </ul>
         * All return codes in Vulkan are reported via VkResult return values. The possible codes are:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef enum VkResult {
         *     VK_SUCCESS = 0,
         *     VK_NOT_READY = 1,
         *     VK_TIMEOUT = 2,
         *     VK_EVENT_SET = 3,
         *     VK_EVENT_RESET = 4,
         *     VK_INCOMPLETE = 5,
         *     VK_ERROR_OUT_OF_HOST_MEMORY = -1,
         *     VK_ERROR_OUT_OF_DEVICE_MEMORY = -2,
         *     VK_ERROR_INITIALIZATION_FAILED = -3,
         *     VK_ERROR_DEVICE_LOST = -4,
         *     VK_ERROR_MEMORY_MAP_FAILED = -5,
         *     VK_ERROR_LAYER_NOT_PRESENT = -6,
         *     VK_ERROR_EXTENSION_NOT_PRESENT = -7,
         *     VK_ERROR_FEATURE_NOT_PRESENT = -8,
         *     VK_ERROR_INCOMPATIBLE_DRIVER = -9,
         *     VK_ERROR_TOO_MANY_OBJECTS = -10,
         *     VK_ERROR_FORMAT_NOT_SUPPORTED = -11,
         *     VK_ERROR_FRAGMENTED_POOL = -12,
         *     VK_ERROR_UNKNOWN = -13,
         *   // Provided by VK_VERSION_1_1
         *     VK_ERROR_OUT_OF_POOL_MEMORY = -1000069000,
         *   // Provided by VK_VERSION_1_1
         *     VK_ERROR_INVALID_EXTERNAL_HANDLE = -1000072003,
         *   // Provided by VK_VERSION_1_2
         *     VK_ERROR_FRAGMENTATION = -1000161000,
         *   // Provided by VK_VERSION_1_2
         *     VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS = -1000257000,
         *   // Provided by VK_VERSION_1_3
         *     VK_PIPELINE_COMPILE_REQUIRED = 1000297000,
         *   // Provided by VK_KHR_surface
         *     VK_ERROR_SURFACE_LOST_KHR = -1000000000,
         *   // Provided by VK_KHR_surface
         *     VK_ERROR_NATIVE_WINDOW_IN_USE_KHR = -1000000001,
         *   // Provided by VK_KHR_swapchain
         *     VK_SUBOPTIMAL_KHR = 1000001003,
         *   // Provided by VK_KHR_swapchain
         *     VK_ERROR_OUT_OF_DATE_KHR = -1000001004,
         *   // Provided by VK_KHR_display_swapchain
         *     VK_ERROR_INCOMPATIBLE_DISPLAY_KHR = -1000003001,
         *   // Provided by VK_EXT_debug_report
         *     VK_ERROR_VALIDATION_FAILED_EXT = -1000011001,
         *   // Provided by VK_NV_glsl_shader
         *     VK_ERROR_INVALID_SHADER_NV = -1000012000,
         *   // Provided by VK_KHR_video_queue
         *     VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR = -1000023000,
         *   // Provided by VK_KHR_video_queue
         *     VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR = -1000023001,
         *   // Provided by VK_KHR_video_queue
         *     VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR = -1000023002,
         *   // Provided by VK_KHR_video_queue
         *     VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR = -1000023003,
         *   // Provided by VK_KHR_video_queue
         *     VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR = -1000023004,
         *   // Provided by VK_KHR_video_queue
         *     VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR = -1000023005,
         *   // Provided by VK_EXT_image_drm_format_modifier
         *     VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT = -1000158000,
         *   // Provided by VK_KHR_global_priority
         *     VK_ERROR_NOT_PERMITTED_KHR = -1000174001,
         *   // Provided by VK_EXT_full_screen_exclusive
         *     VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT = -1000255000,
         *   // Provided by VK_KHR_deferred_host_operations
         *     VK_THREAD_IDLE_KHR = 1000268000,
         *   // Provided by VK_KHR_deferred_host_operations
         *     VK_THREAD_DONE_KHR = 1000268001,
         *   // Provided by VK_KHR_deferred_host_operations
         *     VK_OPERATION_DEFERRED_KHR = 1000268002,
         *   // Provided by VK_KHR_deferred_host_operations
         *     VK_OPERATION_NOT_DEFERRED_KHR = 1000268003,
         *   // Provided by VK_KHR_video_encode_queue
         *     VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR = -1000299000,
         *   // Provided by VK_EXT_image_compression_control
         *     VK_ERROR_COMPRESSION_EXHAUSTED_EXT = -1000338000,
         *   // Provided by VK_EXT_shader_object
         *     VK_INCOMPATIBLE_SHADER_BINARY_EXT = 1000482000,
         *   // Provided by VK_KHR_maintenance1
         *     VK_ERROR_OUT_OF_POOL_MEMORY_KHR = VK_ERROR_OUT_OF_POOL_MEMORY,
         *   // Provided by VK_KHR_external_memory
         *     VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR = VK_ERROR_INVALID_EXTERNAL_HANDLE,
         *   // Provided by VK_EXT_descriptor_indexing
         *     VK_ERROR_FRAGMENTATION_EXT = VK_ERROR_FRAGMENTATION,
         *   // Provided by VK_EXT_global_priority
         *     VK_ERROR_NOT_PERMITTED_EXT = VK_ERROR_NOT_PERMITTED_KHR,
         *   // Provided by VK_EXT_buffer_device_address
         *     VK_ERROR_INVALID_DEVICE_ADDRESS_EXT = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
         *   // Provided by VK_KHR_buffer_device_address
         *     VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
         *   // Provided by VK_EXT_pipeline_creation_cache_control
         *     VK_PIPELINE_COMPILE_REQUIRED_EXT = VK_PIPELINE_COMPILE_REQUIRED,
         *   // Provided by VK_EXT_pipeline_creation_cache_control
         *     VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT = VK_PIPELINE_COMPILE_REQUIRED,
         *   // Provided by VK_EXT_shader_object
         *     VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT = VK_INCOMPATIBLE_SHADER_BINARY_EXT,
         * } VkResult;
         * @endcode
         *
         * <b>Description</b><hr><br>
         *
         * Success Codes:
         * <ul>
         * <li>VK_SUCCESS Command successfully completed
         * <li>VK_NOT_READY A fence or query has not yet completed
         * <li>VK_TIMEOUT A wait operation has not completed in the specified time
         * <li>VK_EVENT_SET An event is signaled
         * <li>VK_EVENT_RESET An event is unsignaled
         * <li>VK_INCOMPLETE A return array was too small for the result
         * <li>VK_SUBOPTIMAL_KHR A swapchain no longer matches the surface properties exactly, but <b>can</b> still be used to present to the surface successfully.
         * <li>VK_THREAD_IDLE_KHR A deferred operation is not complete but there is currently no work for this thread to do at the time of this call.
         * <li>VK_THREAD_DONE_KHR A deferred operation is not complete but there is no work remaining to assign to additional threads.
         * <li>VK_OPERATION_DEFERRED_KHR A deferred operation was requested and at least some of the work was deferred.
         * <li>VK_OPERATION_NOT_DEFERRED_KHR A deferred operation was requested and no operations were deferred.
         * <li>VK_PIPELINE_COMPILE_REQUIRED A requested pipeline creation would have required compilation, but the application requested compilation to not be performed.
         * <li>VK_INCOMPATIBLE_SHADER_BINARY_EXT The provided binary shader code is not compatible with this device.
         * </ul>
         * @note In the initial version of the VK_EXT_shader_object extension, this return code was named VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT and improperly described as an error code. The name has been changed, but the old name is retained as an alias for compatibility with old code.
         *
         * Error codes:
         * <ul>
         * <li>VK_ERROR_OUT_OF_HOST_MEMORY A host memory allocation has failed.
         * <li>VK_ERROR_OUT_OF_DEVICE_MEMORY A device memory allocation has failed.
         * <li>VK_ERROR_INITIALIZATION_FAILED Initialization of an object could not be completed for implementation-specific reasons.
         * <li>VK_ERROR_DEVICE_LOST The logical or physical device has been lost. See Lost Device
         * <li>VK_ERROR_MEMORY_MAP_FAILED Mapping of a memory object has failed.
         * <li>VK_ERROR_LAYER_NOT_PRESENT A requested layer is not present or could not be loaded.
         * <li>VK_ERROR_EXTENSION_NOT_PRESENT A requested extension is not supported.
         * <li>VK_ERROR_FEATURE_NOT_PRESENT A requested feature is not supported.
         * <li>VK_ERROR_INCOMPATIBLE_DRIVER The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons.
         * <li>VK_ERROR_TOO_MANY_OBJECTS Too many objects of the type have already been created.
         * <li>VK_ERROR_FORMAT_NOT_SUPPORTED A requested format is not supported on this device.
         * <li>VK_ERROR_FRAGMENTED_POOL A pool allocation has failed due to fragmentation of the pool’s memory. This <b>must</b> only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation. This <b>should</b> be returned in preference to VK_ERROR_OUT_OF_POOL_MEMORY, but only if the implementation is certain that the pool allocation failure was due to fragmentation.
         * <li>VK_ERROR_SURFACE_LOST_KHR A surface is no longer available.
         * <li>VK_ERROR_NATIVE_WINDOW_IN_USE_KHR The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again.
         * <li>VK_ERROR_OUT_OF_DATE_KHR A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail. Applications <b>must</b> query the new surface properties and recreate their swapchain if they wish to continue presenting to the surface.
         * <li>VK_ERROR_INCOMPATIBLE_DISPLAY_KHR The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image.
         * <li>VK_ERROR_INVALID_SHADER_NV One or more shaders failed to compile or link. More details are reported back to the application via VK_EXT_debug_report if enabled.
         * <li>VK_ERROR_OUT_OF_POOL_MEMORY A pool memory allocation has failed. This <b>must</b> only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation. If the failure was definitely due to fragmentation of the pool, VK_ERROR_FRAGMENTED_POOL <b>should</b> be returned instead.
         * <li>VK_ERROR_INVALID_EXTERNAL_HANDLE An external handle is not a valid handle of the specified type.
         * <li>VK_ERROR_FRAGMENTATION A descriptor pool creation has failed due to fragmentation.
         * <li>VK_ERROR_INVALID_DEVICE_ADDRESS_EXT A buffer creation failed because the requested address is not available.
         * <li>VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS A buffer creation or memory allocation failed because the requested address is not available. A shader group handle assignment failed because the requested shader group handle information is no longer valid.
         * <li>VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT An operation on a swapchain created with VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT failed as it did not have exclusive full-screen access. This <b>may</b> occur due to implementation-dependent reasons, outside of the application’s control.
         * <li>VK_ERROR_VALIDATION_FAILED_EXT A command failed because invalid usage was detected by the implementation or a validation-layer.
         * <li>VK_ERROR_COMPRESSION_EXHAUSTED_EXT An image creation failed because internal resources required for compression are exhausted. This <b>must</b> only be returned when fixed-rate compression is requested.
         * <li>VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR The requested VkImageUsageFlags are not supported.
         * <li>VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR The requested video picture layout is not supported.
         * <li>VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR A video profile operation specified via VkVideoProfileInfoKHR::videoCodecOperation is not supported.
         * <li>VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR Format parameters in a requested VkVideoProfileInfoKHR chain are not supported.
         * <li>VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR Codec-specific parameters in a requested VkVideoProfileInfoKHR chain are not supported.
         * <li>VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR The specified video Std header version is not supported.
         * <li>VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR The specified Video Std parameters do not adhere to the syntactic or semantic requirements of the used video compression standard, or values derived from parameters according to the rules defined by the used video compression standard do not adhere to the capabilities of the video compression standard or the implementation.
         * <li>VK_ERROR_NOT_PERMITTED_KHR The driver implementation has denied a request to acquire a priority above the default priority (VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT) because the application does not have sufficient privileges.
         * <li>VK_ERROR_UNKNOWN An unknown error has occurred; either the application has provided invalid input, or an implementation failure has occurred.
         * </ul>
         * If a command returns a runtime error, unless otherwise specified any output parameters will have undefined contents, except that if the output parameter is a structure with sType and pNext fields, those fields will be unmodified. Any structures chained from pNext will also have undefined contents, except that sType and pNext will be unmodified.<br><br>
         * VK_ERROR_OUT_OF_*_MEMORY errors do not modify any currently existing Vulkan objects. Objects that have already been successfully created <b>can</b> still be used by the application.
         *
         * @note As a general rule, Free, Release, and Reset commands do not return VK_ERROR_OUT_OF_HOST_MEMORY, while any other command with a return code <b>may</b> return it. Any exceptions from this rule are described for those commands.
         *
         * VK_ERROR_UNKNOWN will be returned by an implementation when an unexpected error occurs that cannot be attributed to valid behavior of the application and implementation. Under these conditions, it <b>may</b> be returned from any command returning a VkResult.
         *
         * @note VK_ERROR_UNKNOWN is not expected to ever be returned if the application behavior is valid, and if the implementation is bug-free. If VK_ERROR_UNKNOWN is received, the application should be checked against the latest validation layers to verify correct behavior as much as possible. If no issues are identified it could be an implementation issue, and the implementor should be contacted for support.
         *
         * Any command returning a VkResult <b>may</b> return VK_ERROR_VALIDATION_FAILED_EXT if a violation of valid usage is detected, even though commands do not explicitly list this as a possible return code.<br><br>
         *
         * Performance-critical commands generally do not have return codes. If a runtime error occurs in such commands, the implementation will defer reporting the error until a specified point. For commands that record into command buffers (vkCmd*) runtime errors are reported by vkEndCommandBuffer.
         */
        using Result = VkResult;

        /** <b>Name</b><hr><br>
         *
         * VkFormat - Available image formats<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The following image formats <b>can</b> be passed to, and <b>may</b> be returned from Vulkan commands. The memory required to store each format is discussed with that format, and also summarized in the Representation and Texel Block Size section and the Compatible formats table.
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef enum VkFormat {
         *     VK_FORMAT_UNDEFINED = 0,
         *     VK_FORMAT_R4G4_UNORM_PACK8 = 1,
         *     VK_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
         *     VK_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
         *     VK_FORMAT_R5G6B5_UNORM_PACK16 = 4,
         *     VK_FORMAT_B5G6R5_UNORM_PACK16 = 5,
         *     VK_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
         *     VK_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
         *     VK_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
         *     VK_FORMAT_R8_UNORM = 9,
         *     VK_FORMAT_R8_SNORM = 10,
         *     VK_FORMAT_R8_USCALED = 11,
         *     VK_FORMAT_R8_SSCALED = 12,
         *     VK_FORMAT_R8_UINT = 13,
         *     VK_FORMAT_R8_SINT = 14,
         *     VK_FORMAT_R8_SRGB = 15,
         *     VK_FORMAT_R8G8_UNORM = 16,
         *     VK_FORMAT_R8G8_SNORM = 17,
         *     VK_FORMAT_R8G8_USCALED = 18,
         *     VK_FORMAT_R8G8_SSCALED = 19,
         *     VK_FORMAT_R8G8_UINT = 20,
         *     VK_FORMAT_R8G8_SINT = 21,
         *     VK_FORMAT_R8G8_SRGB = 22,
         *     VK_FORMAT_R8G8B8_UNORM = 23,
         *     VK_FORMAT_R8G8B8_SNORM = 24,
         *     VK_FORMAT_R8G8B8_USCALED = 25,
         *     VK_FORMAT_R8G8B8_SSCALED = 26,
         *     VK_FORMAT_R8G8B8_UINT = 27,
         *     VK_FORMAT_R8G8B8_SINT = 28,
         *     VK_FORMAT_R8G8B8_SRGB = 29,
         *     VK_FORMAT_B8G8R8_UNORM = 30,
         *     VK_FORMAT_B8G8R8_SNORM = 31,
         *     VK_FORMAT_B8G8R8_USCALED = 32,
         *     VK_FORMAT_B8G8R8_SSCALED = 33,
         *     VK_FORMAT_B8G8R8_UINT = 34,
         *     VK_FORMAT_B8G8R8_SINT = 35,
         *     VK_FORMAT_B8G8R8_SRGB = 36,
         *     VK_FORMAT_R8G8B8A8_UNORM = 37,
         *     VK_FORMAT_R8G8B8A8_SNORM = 38,
         *     VK_FORMAT_R8G8B8A8_USCALED = 39,
         *     VK_FORMAT_R8G8B8A8_SSCALED = 40,
         *     VK_FORMAT_R8G8B8A8_UINT = 41,
         *     VK_FORMAT_R8G8B8A8_SINT = 42,
         *     VK_FORMAT_R8G8B8A8_SRGB = 43,
         *     VK_FORMAT_B8G8R8A8_UNORM = 44,
         *     VK_FORMAT_B8G8R8A8_SNORM = 45,
         *     VK_FORMAT_B8G8R8A8_USCALED = 46,
         *     VK_FORMAT_B8G8R8A8_SSCALED = 47,
         *     VK_FORMAT_B8G8R8A8_UINT = 48,
         *     VK_FORMAT_B8G8R8A8_SINT = 49,
         *     VK_FORMAT_B8G8R8A8_SRGB = 50,
         *     VK_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
         *     VK_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
         *     VK_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
         *     VK_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
         *     VK_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
         *     VK_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
         *     VK_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
         *     VK_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
         *     VK_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
         *     VK_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
         *     VK_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
         *     VK_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
         *     VK_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
         *     VK_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
         *     VK_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
         *     VK_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
         *     VK_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
         *     VK_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
         *     VK_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
         *     VK_FORMAT_R16_UNORM = 70,
         *     VK_FORMAT_R16_SNORM = 71,
         *     VK_FORMAT_R16_USCALED = 72,
         *     VK_FORMAT_R16_SSCALED = 73,
         *     VK_FORMAT_R16_UINT = 74,
         *     VK_FORMAT_R16_SINT = 75,
         *     VK_FORMAT_R16_SFLOAT = 76,
         *     VK_FORMAT_R16G16_UNORM = 77,
         *     VK_FORMAT_R16G16_SNORM = 78,
         *     VK_FORMAT_R16G16_USCALED = 79,
         *     VK_FORMAT_R16G16_SSCALED = 80,
         *     VK_FORMAT_R16G16_UINT = 81,
         *     VK_FORMAT_R16G16_SINT = 82,
         *     VK_FORMAT_R16G16_SFLOAT = 83,
         *     VK_FORMAT_R16G16B16_UNORM = 84,
         *     VK_FORMAT_R16G16B16_SNORM = 85,
         *     VK_FORMAT_R16G16B16_USCALED = 86,
         *     VK_FORMAT_R16G16B16_SSCALED = 87,
         *     VK_FORMAT_R16G16B16_UINT = 88,
         *     VK_FORMAT_R16G16B16_SINT = 89,
         *     VK_FORMAT_R16G16B16_SFLOAT = 90,
         *     VK_FORMAT_R16G16B16A16_UNORM = 91,
         *     VK_FORMAT_R16G16B16A16_SNORM = 92,
         *     VK_FORMAT_R16G16B16A16_USCALED = 93,
         *     VK_FORMAT_R16G16B16A16_SSCALED = 94,
         *     VK_FORMAT_R16G16B16A16_UINT = 95,
         *     VK_FORMAT_R16G16B16A16_SINT = 96,
         *     VK_FORMAT_R16G16B16A16_SFLOAT = 97,
         *     VK_FORMAT_R32_UINT = 98,
         *     VK_FORMAT_R32_SINT = 99,
         *     VK_FORMAT_R32_SFLOAT = 100,
         *     VK_FORMAT_R32G32_UINT = 101,
         *     VK_FORMAT_R32G32_SINT = 102,
         *     VK_FORMAT_R32G32_SFLOAT = 103,
         *     VK_FORMAT_R32G32B32_UINT = 104,
         *     VK_FORMAT_R32G32B32_SINT = 105,
         *     VK_FORMAT_R32G32B32_SFLOAT = 106,
         *     VK_FORMAT_R32G32B32A32_UINT = 107,
         *     VK_FORMAT_R32G32B32A32_SINT = 108,
         *     VK_FORMAT_R32G32B32A32_SFLOAT = 109,
         *     VK_FORMAT_R64_UINT = 110,
         *     VK_FORMAT_R64_SINT = 111,
         *     VK_FORMAT_R64_SFLOAT = 112,
         *     VK_FORMAT_R64G64_UINT = 113,
         *     VK_FORMAT_R64G64_SINT = 114,
         *     VK_FORMAT_R64G64_SFLOAT = 115,
         *     VK_FORMAT_R64G64B64_UINT = 116,
         *     VK_FORMAT_R64G64B64_SINT = 117,
         *     VK_FORMAT_R64G64B64_SFLOAT = 118,
         *     VK_FORMAT_R64G64B64A64_UINT = 119,
         *     VK_FORMAT_R64G64B64A64_SINT = 120,
         *     VK_FORMAT_R64G64B64A64_SFLOAT = 121,
         *     VK_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
         *     VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
         *     VK_FORMAT_D16_UNORM = 124,
         *     VK_FORMAT_X8_D24_UNORM_PACK32 = 125,
         *     VK_FORMAT_D32_SFLOAT = 126,
         *     VK_FORMAT_S8_UINT = 127,
         *     VK_FORMAT_D16_UNORM_S8_UINT = 128,
         *     VK_FORMAT_D24_UNORM_S8_UINT = 129,
         *     VK_FORMAT_D32_SFLOAT_S8_UINT = 130,
         *     VK_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
         *     VK_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
         *     VK_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
         *     VK_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
         *     VK_FORMAT_BC2_UNORM_BLOCK = 135,
         *     VK_FORMAT_BC2_SRGB_BLOCK = 136,
         *     VK_FORMAT_BC3_UNORM_BLOCK = 137,
         *     VK_FORMAT_BC3_SRGB_BLOCK = 138,
         *     VK_FORMAT_BC4_UNORM_BLOCK = 139,
         *     VK_FORMAT_BC4_SNORM_BLOCK = 140,
         *     VK_FORMAT_BC5_UNORM_BLOCK = 141,
         *     VK_FORMAT_BC5_SNORM_BLOCK = 142,
         *     VK_FORMAT_BC6H_UFLOAT_BLOCK = 143,
         *     VK_FORMAT_BC6H_SFLOAT_BLOCK = 144,
         *     VK_FORMAT_BC7_UNORM_BLOCK = 145,
         *     VK_FORMAT_BC7_SRGB_BLOCK = 146,
         *     VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
         *     VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
         *     VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
         *     VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
         *     VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
         *     VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
         *     VK_FORMAT_EAC_R11_UNORM_BLOCK = 153,
         *     VK_FORMAT_EAC_R11_SNORM_BLOCK = 154,
         *     VK_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
         *     VK_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
         *     VK_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
         *     VK_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
         *     VK_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
         *     VK_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
         *     VK_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
         *     VK_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
         *     VK_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
         *     VK_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
         *     VK_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
         *     VK_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
         *     VK_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
         *     VK_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
         *     VK_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
         *     VK_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
         *     VK_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
         *     VK_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
         *     VK_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
         *     VK_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
         *     VK_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
         *     VK_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
         *     VK_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
         *     VK_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
         *     VK_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
         *     VK_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
         *     VK_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
         *     VK_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
         *     VK_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
         *     VK_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G8B8G8R8_422_UNORM = 1000156000,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_B8G8R8G8_422_UNORM = 1000156001,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM = 1000156002,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G8_B8R8_2PLANE_420_UNORM = 1000156003,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM = 1000156004,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G8_B8R8_2PLANE_422_UNORM = 1000156005,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM = 1000156006,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_R10X6_UNORM_PACK16 = 1000156007,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_R10X6G10X6_UNORM_2PACK16 = 1000156008,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_R12X4_UNORM_PACK16 = 1000156017,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_R12X4G12X4_UNORM_2PACK16 = 1000156018,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G16B16G16R16_422_UNORM = 1000156027,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_B16G16R16G16_422_UNORM = 1000156028,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM = 1000156029,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G16_B16R16_2PLANE_420_UNORM = 1000156030,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM = 1000156031,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G16_B16R16_2PLANE_422_UNORM = 1000156032,
         *   // Provided by VK_VERSION_1_1
         *     VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM = 1000156033,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_G8_B8R8_2PLANE_444_UNORM = 1000330000,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 = 1000330001,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 = 1000330002,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_G16_B16R16_2PLANE_444_UNORM = 1000330003,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_A4R4G4B4_UNORM_PACK16 = 1000340000,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_A4B4G4R4_UNORM_PACK16 = 1000340001,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK = 1000066000,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK = 1000066001,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK = 1000066002,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK = 1000066003,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK = 1000066004,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK = 1000066005,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK = 1000066006,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK = 1000066007,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK = 1000066008,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK = 1000066009,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK = 1000066010,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK = 1000066011,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK = 1000066012,
         *   // Provided by VK_VERSION_1_3
         *     VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK = 1000066013,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006,
         *   // Provided by VK_IMG_format_pvrtc
         *     VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007,
         *   // Provided by VK_NV_optical_flow
         *     VK_FORMAT_R16G16_SFIXED5_NV = 1000464000,
         *   // Provided by VK_KHR_maintenance5
         *     VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR = 1000470000,
         *   // Provided by VK_KHR_maintenance5
         *     VK_FORMAT_A8_UNORM_KHR = 1000470001,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK,
         *   // Provided by VK_EXT_texture_compression_astc_hdr
         *     VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G8B8G8R8_422_UNORM_KHR = VK_FORMAT_G8B8G8R8_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_B8G8R8G8_422_UNORM_KHR = VK_FORMAT_B8G8R8G8_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_R10X6_UNORM_PACK16_KHR = VK_FORMAT_R10X6_UNORM_PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR = VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_R12X4_UNORM_PACK16_KHR = VK_FORMAT_R12X4_UNORM_PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR = VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G16B16G16R16_422_UNORM_KHR = VK_FORMAT_G16B16G16R16_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_B16G16R16G16_422_UNORM_KHR = VK_FORMAT_B16G16R16G16_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
         *   // Provided by VK_KHR_sampler_ycbcr_conversion
         *     VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
         *   // Provided by VK_EXT_ycbcr_2plane_444_formats
         *     VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM,
         *   // Provided by VK_EXT_ycbcr_2plane_444_formats
         *     VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16,
         *   // Provided by VK_EXT_ycbcr_2plane_444_formats
         *     VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16,
         *   // Provided by VK_EXT_ycbcr_2plane_444_formats
         *     VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM,
         *   // Provided by VK_EXT_4444_formats
         *     VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT = VK_FORMAT_A4R4G4B4_UNORM_PACK16,
         *   // Provided by VK_EXT_4444_formats
         *     VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT = VK_FORMAT_A4B4G4R4_UNORM_PACK16,
         *   // Provided by VK_NV_optical_flow
         *     VK_FORMAT_R16G16_S10_5_NV = VK_FORMAT_R16G16_SFIXED5_NV,
         * } VkFormat;
         * @endcode
         *
         * <b>Description</b><hr><br>
         * <ul>
         * <li>VK_FORMAT_UNDEFINED specifies that the format is not specified.
         * <li>VK_FORMAT_R4G4_UNORM_PACK8 specifies a two-component, 8-bit packed unsigned normalized format that has a 4-bit R component in bits 4..7, and a 4-bit G component in bits 0..3.
         * <li>VK_FORMAT_R4G4B4A4_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 4-bit R component in bits 12..15, a 4-bit G component in bits 8..11, a 4-bit B component in bits 4..7, and a 4-bit A component in bits 0..3.
         * <li>VK_FORMAT_B4G4R4A4_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 4-bit B component in bits 12..15, a 4-bit G component in bits 8..11, a 4-bit R component in bits 4..7, and a 4-bit A component in bits 0..3.
         * <li>VK_FORMAT_A4R4G4B4_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 4-bit A component in bits 12..15, a 4-bit R component in bits 8..11, a 4-bit G component in bits 4..7, and a 4-bit B component in bits 0..3.
         * <li>VK_FORMAT_A4B4G4R4_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 4-bit A component in bits 12..15, a 4-bit B component in bits 8..11, a 4-bit G component in bits 4..7, and a 4-bit R component in bits 0..3.
         * <li>VK_FORMAT_R5G6B5_UNORM_PACK16 specifies a three-component, 16-bit packed unsigned normalized format that has a 5-bit R component in bits 11..15, a 6-bit G component in bits 5..10, and a 5-bit B component in bits 0..4.
         * <li>VK_FORMAT_B5G6R5_UNORM_PACK16 specifies a three-component, 16-bit packed unsigned normalized format that has a 5-bit B component in bits 11..15, a 6-bit G component in bits 5..10, and a 5-bit R component in bits 0..4.
         * <li>VK_FORMAT_R5G5B5A1_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 5-bit R component in bits 11..15, a 5-bit G component in bits 6..10, a 5-bit B component in bits 1..5, and a 1-bit A component in bit 0.
         * <li>VK_FORMAT_B5G5R5A1_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 5-bit B component in bits 11..15, a 5-bit G component in bits 6..10, a 5-bit R component in bits 1..5, and a 1-bit A component in bit 0.
         * <li>VK_FORMAT_A1R5G5B5_UNORM_PACK16 specifies a four-component, 16-bit packed unsigned normalized format that has a 1-bit A component in bit 15, a 5-bit R component in bits 10..14, a 5-bit G component in bits 5..9, and a 5-bit B component in bits 0..4.
         * <li>VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR specifies a four-component, 16-bit packed unsigned normalized format that has a 1-bit A component in bit 15, a 5-bit B component in bits 10..14, a 5-bit G component in bits 5..9, and a 5-bit R component in bits 0..4.
         * <li>VK_FORMAT_A8_UNORM_KHR specifies a one-component, 8-bit unsigned normalized format that has a single 8-bit A component.
         * <li>VK_FORMAT_R8_UNORM specifies a one-component, 8-bit unsigned normalized format that has a single 8-bit R component.
         * <li>VK_FORMAT_R8_SNORM specifies a one-component, 8-bit signed normalized format that has a single 8-bit R component.
         * <li>VK_FORMAT_R8_USCALED specifies a one-component, 8-bit unsigned scaled integer format that has a single 8-bit R component.
         * <li>VK_FORMAT_R8_SSCALED specifies a one-component, 8-bit signed scaled integer format that has a single 8-bit R component.
         * <li>VK_FORMAT_R8_UINT specifies a one-component, 8-bit unsigned integer format that has a single 8-bit R component.
         * <li>VK_FORMAT_R8_SINT specifies a one-component, 8-bit signed integer format that has a single 8-bit R component.
         * <li>VK_FORMAT_R8_SRGB specifies a one-component, 8-bit unsigned normalized format that has a single 8-bit R component stored with sRGB nonlinear encoding.
         * <li>VK_FORMAT_R8G8_UNORM specifies a two-component, 16-bit unsigned normalized format that has an 8-bit R component in byte 0, and an 8-bit G component in byte 1.
         * <li>VK_FORMAT_R8G8_SNORM specifies a two-component, 16-bit signed normalized format that has an 8-bit R component in byte 0, and an 8-bit G component in byte 1.
         * <li>VK_FORMAT_R8G8_USCALED specifies a two-component, 16-bit unsigned scaled integer format that has an 8-bit R component in byte 0, and an 8-bit G component in byte 1.
         * <li>VK_FORMAT_R8G8_SSCALED specifies a two-component, 16-bit signed scaled integer format that has an 8-bit R component in byte 0, and an 8-bit G component in byte 1.
         * <li>VK_FORMAT_R8G8_UINT specifies a two-component, 16-bit unsigned integer format that has an 8-bit R component in byte 0, and an 8-bit G component in byte 1.
         * <li>VK_FORMAT_R8G8_SINT specifies a two-component, 16-bit signed integer format that has an 8-bit R component in byte 0, and an 8-bit G component in byte 1.
         * <li>VK_FORMAT_R8G8_SRGB specifies a two-component, 16-bit unsigned normalized format that has an 8-bit R component stored with sRGB nonlinear encoding in byte 0, and an 8-bit G component stored with sRGB nonlinear encoding in byte 1.
         * <li>VK_FORMAT_R8G8B8_UNORM specifies a three-component, 24-bit unsigned normalized format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, and an 8-bit B component in byte 2.
         * <li>VK_FORMAT_R8G8B8_SNORM specifies a three-component, 24-bit signed normalized format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, and an 8-bit B component in byte 2.
         * <li>VK_FORMAT_R8G8B8_USCALED specifies a three-component, 24-bit unsigned scaled format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, and an 8-bit B component in byte 2.
         * <li>VK_FORMAT_R8G8B8_SSCALED specifies a three-component, 24-bit signed scaled format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, and an 8-bit B component in byte 2.
         * <li>VK_FORMAT_R8G8B8_UINT specifies a three-component, 24-bit unsigned integer format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, and an 8-bit B component in byte 2.
         * <li>VK_FORMAT_R8G8B8_SINT specifies a three-component, 24-bit signed integer format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, and an 8-bit B component in byte 2.
         * <li>VK_FORMAT_R8G8B8_SRGB specifies a three-component, 24-bit unsigned normalized format that has an 8-bit R component stored with sRGB nonlinear encoding in byte 0, an 8-bit G component stored with sRGB nonlinear encoding in byte 1, and an 8-bit B component stored with sRGB nonlinear encoding in byte 2.
         * <li>VK_FORMAT_B8G8R8_UNORM specifies a three-component, 24-bit unsigned normalized format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, and an 8-bit R component in byte 2.
         * <li>VK_FORMAT_B8G8R8_SNORM specifies a three-component, 24-bit signed normalized format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, and an 8-bit R component in byte 2.
         * <li>VK_FORMAT_B8G8R8_USCALED specifies a three-component, 24-bit unsigned scaled format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, and an 8-bit R component in byte 2.
         * <li>VK_FORMAT_B8G8R8_SSCALED specifies a three-component, 24-bit signed scaled format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, and an 8-bit R component in byte 2.
         * <li>VK_FORMAT_B8G8R8_UINT specifies a three-component, 24-bit unsigned integer format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, and an 8-bit R component in byte 2.
         * <li>VK_FORMAT_B8G8R8_SINT specifies a three-component, 24-bit signed integer format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, and an 8-bit R component in byte 2.
         * <li>VK_FORMAT_B8G8R8_SRGB specifies a three-component, 24-bit unsigned normalized format that has an 8-bit B component stored with sRGB nonlinear encoding in byte 0, an 8-bit G component stored with sRGB nonlinear encoding in byte 1, and an 8-bit R component stored with sRGB nonlinear encoding in byte 2.
         * <li>VK_FORMAT_R8G8B8A8_UNORM specifies a four-component, 32-bit unsigned normalized format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, an 8-bit B component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_R8G8B8A8_SNORM specifies a four-component, 32-bit signed normalized format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, an 8-bit B component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_R8G8B8A8_USCALED specifies a four-component, 32-bit unsigned scaled format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, an 8-bit B component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_R8G8B8A8_SSCALED specifies a four-component, 32-bit signed scaled format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, an 8-bit B component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_R8G8B8A8_UINT specifies a four-component, 32-bit unsigned integer format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, an 8-bit B component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_R8G8B8A8_SINT specifies a four-component, 32-bit signed integer format that has an 8-bit R component in byte 0, an 8-bit G component in byte 1, an 8-bit B component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_R8G8B8A8_SRGB specifies a four-component, 32-bit unsigned normalized format that has an 8-bit R component stored with sRGB nonlinear encoding in byte 0, an 8-bit G component stored with sRGB nonlinear encoding in byte 1, an 8-bit B component stored with sRGB nonlinear encoding in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_UNORM specifies a four-component, 32-bit unsigned normalized format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, an 8-bit R component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_SNORM specifies a four-component, 32-bit signed normalized format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, an 8-bit R component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_USCALED specifies a four-component, 32-bit unsigned scaled format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, an 8-bit R component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_SSCALED specifies a four-component, 32-bit signed scaled format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, an 8-bit R component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_UINT specifies a four-component, 32-bit unsigned integer format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, an 8-bit R component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_SINT specifies a four-component, 32-bit signed integer format that has an 8-bit B component in byte 0, an 8-bit G component in byte 1, an 8-bit R component in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_B8G8R8A8_SRGB specifies a four-component, 32-bit unsigned normalized format that has an 8-bit B component stored with sRGB nonlinear encoding in byte 0, an 8-bit G component stored with sRGB nonlinear encoding in byte 1, an 8-bit R component stored with sRGB nonlinear encoding in byte 2, and an 8-bit A component in byte 3.
         * <li>VK_FORMAT_A8B8G8R8_UNORM_PACK32 specifies a four-component, 32-bit packed unsigned normalized format that has an 8-bit A component in bits 24..31, an 8-bit B component in bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R component in bits 0..7.
         * <li>VK_FORMAT_A8B8G8R8_SNORM_PACK32 specifies a four-component, 32-bit packed signed normalized format that has an 8-bit A component in bits 24..31, an 8-bit B component in bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R component in bits 0..7.
         * <li>VK_FORMAT_A8B8G8R8_USCALED_PACK32 specifies a four-component, 32-bit packed unsigned scaled integer format that has an 8-bit A component in bits 24..31, an 8-bit B component in bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R component in bits 0..7.
         * <li>VK_FORMAT_A8B8G8R8_SSCALED_PACK32 specifies a four-component, 32-bit packed signed scaled integer format that has an 8-bit A component in bits 24..31, an 8-bit B component in bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R component in bits 0..7.
         * <li>VK_FORMAT_A8B8G8R8_UINT_PACK32 specifies a four-component, 32-bit packed unsigned integer format that has an 8-bit A component in bits 24..31, an 8-bit B component in bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R component in bits 0..7.
         * <li>VK_FORMAT_A8B8G8R8_SINT_PACK32 specifies a four-component, 32-bit packed signed integer format that has an 8-bit A component in bits 24..31, an 8-bit B component in bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R component in bits 0..7.
         * <li>VK_FORMAT_A8B8G8R8_SRGB_PACK32 specifies a four-component, 32-bit packed unsigned normalized format that has an 8-bit A component in bits 24..31, an 8-bit B component stored with sRGB nonlinear encoding in bits 16..23, an 8-bit G component stored with sRGB nonlinear encoding in bits 8..15, and an 8-bit R component stored with sRGB nonlinear encoding in bits 0..7.
         * <li>VK_FORMAT_A2R10G10B10_UNORM_PACK32 specifies a four-component, 32-bit packed unsigned normalized format that has a 2-bit A component in bits 30..31, a 10-bit R component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B component in bits 0..9.
         * <li>VK_FORMAT_A2R10G10B10_SNORM_PACK32 specifies a four-component, 32-bit packed signed normalized format that has a 2-bit A component in bits 30..31, a 10-bit R component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B component in bits 0..9.
         * <li>VK_FORMAT_A2R10G10B10_USCALED_PACK32 specifies a four-component, 32-bit packed unsigned scaled integer format that has a 2-bit A component in bits 30..31, a 10-bit R component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B component in bits 0..9.
         * <li>VK_FORMAT_A2R10G10B10_SSCALED_PACK32 specifies a four-component, 32-bit packed signed scaled integer format that has a 2-bit A component in bits 30..31, a 10-bit R component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B component in bits 0..9.
         * <li>VK_FORMAT_A2R10G10B10_UINT_PACK32 specifies a four-component, 32-bit packed unsigned integer format that has a 2-bit A component in bits 30..31, a 10-bit R component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B component in bits 0..9.
         * <li>VK_FORMAT_A2R10G10B10_SINT_PACK32 specifies a four-component, 32-bit packed signed integer format that has a 2-bit A component in bits 30..31, a 10-bit R component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B component in bits 0..9.
         * <li>VK_FORMAT_A2B10G10R10_UNORM_PACK32 specifies a four-component, 32-bit packed unsigned normalized format that has a 2-bit A component in bits 30..31, a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9.
         * <li>VK_FORMAT_A2B10G10R10_SNORM_PACK32 specifies a four-component, 32-bit packed signed normalized format that has a 2-bit A component in bits 30..31, a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9.
         * <li>VK_FORMAT_A2B10G10R10_USCALED_PACK32 specifies a four-component, 32-bit packed unsigned scaled integer format that has a 2-bit A component in bits 30..31, a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9.
         * <li>VK_FORMAT_A2B10G10R10_SSCALED_PACK32 specifies a four-component, 32-bit packed signed scaled integer format that has a 2-bit A component in bits 30..31, a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9.
         * <li>VK_FORMAT_A2B10G10R10_UINT_PACK32 specifies a four-component, 32-bit packed unsigned integer format that has a 2-bit A component in bits 30..31, a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9.
         * <li>VK_FORMAT_A2B10G10R10_SINT_PACK32 specifies a four-component, 32-bit packed signed integer format that has a 2-bit A component in bits 30..31, a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9.
         * <li>VK_FORMAT_R16_UNORM specifies a one-component, 16-bit unsigned normalized format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16_SNORM specifies a one-component, 16-bit signed normalized format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16_USCALED specifies a one-component, 16-bit unsigned scaled integer format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16_SSCALED specifies a one-component, 16-bit signed scaled integer format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16_UINT specifies a one-component, 16-bit unsigned integer format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16_SINT specifies a one-component, 16-bit signed integer format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16_SFLOAT specifies a one-component, 16-bit signed floating-point format that has a single 16-bit R component.
         * <li>VK_FORMAT_R16G16_UNORM specifies a two-component, 32-bit unsigned normalized format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16_SNORM specifies a two-component, 32-bit signed normalized format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16_USCALED specifies a two-component, 32-bit unsigned scaled integer format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16_SSCALED specifies a two-component, 32-bit signed scaled integer format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16_UINT specifies a two-component, 32-bit unsigned integer format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16_SINT specifies a two-component, 32-bit signed integer format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16_SFLOAT specifies a two-component, 32-bit signed floating-point format that has a 16-bit R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
         * <li>VK_FORMAT_R16G16B16_UNORM specifies a three-component, 48-bit unsigned normalized format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16_SNORM specifies a three-component, 48-bit signed normalized format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16_USCALED specifies a three-component, 48-bit unsigned scaled integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16_SSCALED specifies a three-component, 48-bit signed scaled integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16_UINT specifies a three-component, 48-bit unsigned integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16_SINT specifies a three-component, 48-bit signed integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16_SFLOAT specifies a three-component, 48-bit signed floating-point format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, and a 16-bit B component in bytes 4..5.
         * <li>VK_FORMAT_R16G16B16A16_UNORM specifies a four-component, 64-bit unsigned normalized format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R16G16B16A16_SNORM specifies a four-component, 64-bit signed normalized format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R16G16B16A16_USCALED specifies a four-component, 64-bit unsigned scaled integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R16G16B16A16_SSCALED specifies a four-component, 64-bit signed scaled integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R16G16B16A16_UINT specifies a four-component, 64-bit unsigned integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R16G16B16A16_SINT specifies a four-component, 64-bit signed integer format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R16G16B16A16_SFLOAT specifies a four-component, 64-bit signed floating-point format that has a 16-bit R component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A component in bytes 6..7.
         * <li>VK_FORMAT_R32_UINT specifies a one-component, 32-bit unsigned integer format that has a single 32-bit R component.
         * <li>VK_FORMAT_R32_SINT specifies a one-component, 32-bit signed integer format that has a single 32-bit R component.
         * <li>VK_FORMAT_R32_SFLOAT specifies a one-component, 32-bit signed floating-point format that has a single 32-bit R component.
         * <li>VK_FORMAT_R32G32_UINT specifies a two-component, 64-bit unsigned integer format that has a 32-bit R component in bytes 0..3, and a 32-bit G component in bytes 4..7.
         * <li>VK_FORMAT_R32G32_SINT specifies a two-component, 64-bit signed integer format that has a 32-bit R component in bytes 0..3, and a 32-bit G component in bytes 4..7.
         * <li>VK_FORMAT_R32G32_SFLOAT specifies a two-component, 64-bit signed floating-point format that has a 32-bit R component in bytes 0..3, and a 32-bit G component in bytes 4..7.
         * <li>VK_FORMAT_R32G32B32_UINT specifies a three-component, 96-bit unsigned integer format that has a 32-bit R component in bytes 0..3, a 32-bit G component in bytes 4..7, and a 32-bit B component in bytes 8..11.
         * <li>VK_FORMAT_R32G32B32_SINT specifies a three-component, 96-bit signed integer format that has a 32-bit R component in bytes 0..3, a 32-bit G component in bytes 4..7, and a 32-bit B component in bytes 8..11.
         * <li>VK_FORMAT_R32G32B32_SFLOAT specifies a three-component, 96-bit signed floating-point format that has a 32-bit R component in bytes 0..3, a 32-bit G component in bytes 4..7, and a 32-bit B component in bytes 8..11.
         * <li>VK_FORMAT_R32G32B32A32_UINT specifies a four-component, 128-bit unsigned integer format that has a 32-bit R component in bytes 0..3, a 32-bit G component in bytes 4..7, a 32-bit B component in bytes 8..11, and a 32-bit A component in bytes 12..15.
         * <li>VK_FORMAT_R32G32B32A32_SINT specifies a four-component, 128-bit signed integer format that has a 32-bit R component in bytes 0..3, a 32-bit G component in bytes 4..7, a 32-bit B component in bytes 8..11, and a 32-bit A component in bytes 12..15.
         * <li>VK_FORMAT_R32G32B32A32_SFLOAT specifies a four-component, 128-bit signed floating-point format that has a 32-bit R component in bytes 0..3, a 32-bit G component in bytes 4..7, a 32-bit B component in bytes 8..11, and a 32-bit A component in bytes 12..15.
         * <li>VK_FORMAT_R64_UINT specifies a one-component, 64-bit unsigned integer format that has a single 64-bit R component.
         * <li>VK_FORMAT_R64_SINT specifies a one-component, 64-bit signed integer format that has a single 64-bit R component.
         * <li>VK_FORMAT_R64_SFLOAT specifies a one-component, 64-bit signed floating-point format that has a single 64-bit R component.
         * <li>VK_FORMAT_R64G64_UINT specifies a two-component, 128-bit unsigned integer format that has a 64-bit R component in bytes 0..7, and a 64-bit G component in bytes 8..15.
         * <li>VK_FORMAT_R64G64_SINT specifies a two-component, 128-bit signed integer format that has a 64-bit R component in bytes 0..7, and a 64-bit G component in bytes 8..15.
         * <li>VK_FORMAT_R64G64_SFLOAT specifies a two-component, 128-bit signed floating-point format that has a 64-bit R component in bytes 0..7, and a 64-bit G component in bytes 8..15.
         * <li>VK_FORMAT_R64G64B64_UINT specifies a three-component, 192-bit unsigned integer format that has a 64-bit R component in bytes 0..7, a 64-bit G component in bytes 8..15, and a 64-bit B component in bytes 16..23.
         * <li>VK_FORMAT_R64G64B64_SINT specifies a three-component, 192-bit signed integer format that has a 64-bit R component in bytes 0..7, a 64-bit G component in bytes 8..15, and a 64-bit B component in bytes 16..23.
         * <li>VK_FORMAT_R64G64B64_SFLOAT specifies a three-component, 192-bit signed floating-point format that has a 64-bit R component in bytes 0..7, a 64-bit G component in bytes 8..15, and a 64-bit B component in bytes 16..23.
         * <li>VK_FORMAT_R64G64B64A64_UINT specifies a four-component, 256-bit unsigned integer format that has a 64-bit R component in bytes 0..7, a 64-bit G component in bytes 8..15, a 64-bit B component in bytes 16..23, and a 64-bit A component in bytes 24..31.
         * <li>VK_FORMAT_R64G64B64A64_SINT specifies a four-component, 256-bit signed integer format that has a 64-bit R component in bytes 0..7, a 64-bit G component in bytes 8..15, a 64-bit B component in bytes 16..23, and a 64-bit A component in bytes 24..31.
         * <li>VK_FORMAT_R64G64B64A64_SFLOAT specifies a four-component, 256-bit signed floating-point format that has a 64-bit R component in bytes 0..7, a 64-bit G component in bytes 8..15, a 64-bit B component in bytes 16..23, and a 64-bit A component in bytes 24..31.
         * <li>VK_FORMAT_B10G11R11_UFLOAT_PACK32 specifies a three-component, 32-bit packed unsigned floating-point format that has a 10-bit B component in bits 22..31, an 11-bit G component in bits 11..21, an 11-bit R component in bits 0..10. See https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#fundamentals-fp10 and https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#fundamentals-fp11.
         * <li>VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 specifies a three-component, 32-bit packed unsigned floating-point format that has a 5-bit shared exponent in bits 27..31, a 9-bit B component mantissa in bits 18..26, a 9-bit G component mantissa in bits 9..17, and a 9-bit R component mantissa in bits 0..8.
         * <li>VK_FORMAT_D16_UNORM specifies a one-component, 16-bit unsigned normalized format that has a single 16-bit depth component.
         * <li>VK_FORMAT_X8_D24_UNORM_PACK32 specifies a two-component, 32-bit format that has 24 unsigned normalized bits in the depth component and, optionally, 8 bits that are unused.
         * <li>VK_FORMAT_D32_SFLOAT specifies a one-component, 32-bit signed floating-point format that has 32 bits in the depth component.
         * <li>VK_FORMAT_S8_UINT specifies a one-component, 8-bit unsigned integer format that has 8 bits in the stencil component.
         * <li>VK_FORMAT_D16_UNORM_S8_UINT specifies a two-component, 24-bit format that has 16 unsigned normalized bits in the depth component and 8 unsigned integer bits in the stencil component.
         * <li>VK_FORMAT_D24_UNORM_S8_UINT specifies a two-component, 32-bit packed format that has 8 unsigned integer bits in the stencil component, and 24 unsigned normalized bits in the depth component.
         * <li>VK_FORMAT_D32_SFLOAT_S8_UINT specifies a two-component format that has 32 signed float bits in the depth component and 8 unsigned integer bits in the stencil component. There are optionally 24 bits that are unused.
         * <li>VK_FORMAT_BC1_RGB_UNORM_BLOCK specifies a three-component, block-compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data. This format has no alpha and is considered opaque.
         * <li>VK_FORMAT_BC1_RGB_SRGB_BLOCK specifies a three-component, block-compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data with sRGB nonlinear encoding. This format has no alpha and is considered opaque.
         * <li>VK_FORMAT_BC1_RGBA_UNORM_BLOCK specifies a four-component, block-compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data, and provides 1 bit of alpha.
         * <li>VK_FORMAT_BC1_RGBA_SRGB_BLOCK specifies a four-component, block-compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data with sRGB nonlinear encoding, and provides 1 bit of alpha.
         * <li>VK_FORMAT_BC2_UNORM_BLOCK specifies a four-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values.
         * <li>VK_FORMAT_BC2_SRGB_BLOCK specifies a four-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values with sRGB nonlinear encoding.
         * <li>VK_FORMAT_BC3_UNORM_BLOCK specifies a four-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values.
         * <li>VK_FORMAT_BC3_SRGB_BLOCK specifies a four-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values with sRGB nonlinear encoding.
         * <li>VK_FORMAT_BC4_UNORM_BLOCK specifies a one-component, block-compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized red texel data.
         * <li>VK_FORMAT_BC4_SNORM_BLOCK specifies a one-component, block-compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of signed normalized red texel data.
         * <li>VK_FORMAT_BC5_UNORM_BLOCK specifies a two-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RG texel data with the first 64 bits encoding red values followed by 64 bits encoding green values.
         * <li>VK_FORMAT_BC5_SNORM_BLOCK specifies a two-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of signed normalized RG texel data with the first 64 bits encoding red values followed by 64 bits encoding green values.
         * <li>VK_FORMAT_BC6H_UFLOAT_BLOCK specifies a three-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned floating-point RGB texel data.
         * <li>VK_FORMAT_BC6H_SFLOAT_BLOCK specifies a three-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of signed floating-point RGB texel data.
         * <li>VK_FORMAT_BC7_UNORM_BLOCK specifies a four-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_BC7_SRGB_BLOCK specifies a four-component, block-compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK specifies a three-component, ETC2 compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data. This format has no alpha and is considered opaque.
         * <li>VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK specifies a three-component, ETC2 compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data with sRGB nonlinear encoding. This format has no alpha and is considered opaque.
         * <li>VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK specifies a four-component, ETC2 compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data, and provides 1 bit of alpha.
         * <li>VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK specifies a four-component, ETC2 compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGB texel data with sRGB nonlinear encoding, and provides 1 bit of alpha.
         * <li>VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK specifies a four-component, ETC2 compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values.
         * <li>VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK specifies a four-component, ETC2 compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values with sRGB nonlinear encoding applied.
         * <li>VK_FORMAT_EAC_R11_UNORM_BLOCK specifies a one-component, ETC2 compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized red texel data.
         * <li>VK_FORMAT_EAC_R11_SNORM_BLOCK specifies a one-component, ETC2 compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of signed normalized red texel data.
         * <li>VK_FORMAT_EAC_R11G11_UNORM_BLOCK specifies a two-component, ETC2 compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RG texel data with the first 64 bits encoding red values followed by 64 bits encoding green values.
         * <li>VK_FORMAT_EAC_R11G11_SNORM_BLOCK specifies a two-component, ETC2 compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of signed normalized RG texel data with the first 64 bits encoding red values followed by 64 bits encoding green values.
         * <li>VK_FORMAT_ASTC_4x4_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_4x4_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 4×4 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_5x4_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 5×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_5x4_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 5×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 5×4 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_5x5_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 5×5 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_5x5_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 5×5 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 5×5 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_6x5_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 6×5 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_6x5_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 6×5 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 6×5 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_6x6_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 6×6 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_6x6_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 6×6 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 6×6 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_8x5_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes an 8×5 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_8x5_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes an 8×5 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 8×5 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_8x6_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes an 8×6 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_8x6_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes an 8×6 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 8×6 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_8x8_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes an 8×8 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_8x8_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes an 8×8 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 8×8 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x5_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×5 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x5_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×5 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×5 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x6_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×6 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x6_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×6 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×6 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x8_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×8 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x8_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×8 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×8 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x10_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×10 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_10x10_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×10 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 10×10 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_12x10_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 12×10 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_12x10_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 12×10 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 12×10 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_ASTC_12x12_UNORM_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 12×12 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_ASTC_12x12_SRGB_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 12×12 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK specifies a four-component, ASTC compressed format where each 128-bit compressed texel block encodes a 12×12 rectangle of signed floating-point RGBA texel data.
         * <li>VK_FORMAT_G8B8G8R8_422_UNORM specifies a four-component, 32-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has an 8-bit G component for the even i coordinate in byte 0, an 8-bit B component in byte 1, an 8-bit G component for the odd i coordinate in byte 2, and an 8-bit R component in byte 3. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_B8G8R8G8_422_UNORM specifies a four-component, 32-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has an 8-bit B component in byte 0, an 8-bit G component for the even i coordinate in byte 1, an 8-bit R component in byte 2, and an 8-bit G component for the odd i coordinate in byte 3. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM specifies an unsigned normalized multi-planar format that has an 8-bit G component in plane 0, an 8-bit B component in plane 1, and an 8-bit R component in plane 2. The horizontal and vertical dimensions of the R and B planes are halved relative to the image dimensions, and each R and B component is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB =jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G8_B8R8_2PLANE_420_UNORM specifies an unsigned normalized multi-planar format that has an 8-bit G component in plane 0, and a two-component, 16-bit BR plane 1 consisting of an 8-bit B component in byte 0 and an 8-bit R component in byte 1. The horizontal and vertical dimensions of the BR plane are halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM specifies an unsigned normalized multi-planar format that has an 8-bit G component in plane 0, an 8-bit B component in plane 1, and an 8-bit R component in plane 2. The horizontal dimension of the R and B plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G8_B8R8_2PLANE_422_UNORM specifies an unsigned normalized multi-planar format that has an 8-bit G component in plane 0, and a two-component, 16-bit BR plane 1 consisting of an 8-bit B component in byte 0 and an 8-bit R component in byte 1. The horizontal dimension of the BR plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM specifies an unsigned normalized multi-planar format that has an 8-bit G component in plane 0, an 8-bit B component in plane 1, and an 8-bit R component in plane 2. Each plane has the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane.
         * <li>VK_FORMAT_R10X6_UNORM_PACK16 specifies a one-component, 16-bit unsigned normalized format that has a single 10-bit R component in the top 10 bits of a 16-bit word, with the bottom 6 bits unused.
         * <li>VK_FORMAT_R10X6G10X6_UNORM_2PACK16 specifies a two-component, 32-bit unsigned normalized format that has a 10-bit R component in the top 10 bits of the word in bytes 0..1, and a 10-bit G component in the top 10 bits of the word in bytes 2..3, with the bottom 6 bits of each word unused.
         * <li>VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 specifies a four-component, 64-bit unsigned normalized format that has a 10-bit R component in the top 10 bits of the word in bytes 0..1, a 10-bit G component in the top 10 bits of the word in bytes 2..3, a 10-bit B component in the top 10 bits of the word in bytes 4..5, and a 10-bit A component in the top 10 bits of the word in bytes 6..7, with the bottom 6 bits of each word unused.
         * <li>VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 specifies a four-component, 64-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has a 10-bit G component for the even i coordinate in the top 10 bits of the word in bytes 0..1, a 10-bit B component in the top 10 bits of the word in bytes 2..3, a 10-bit G component for the odd i coordinate in the top 10 bits of the word in bytes 4..5, and a 10-bit R component in the top 10 bits of the word in bytes 6..7, with the bottom 6 bits of each word unused. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 specifies a four-component, 64-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has a 10-bit B component in the top 10 bits of the word in bytes 0..1, a 10-bit G component for the even i coordinate in the top 10 bits of the word in bytes 2..3, a 10-bit R component in the top 10 bits of the word in bytes 4..5, and a 10-bit G component for the odd i coordinate in the top 10 bits of the word in bytes 6..7, with the bottom 6 bits of each word unused. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 10-bit G component in the top 10 bits of each 16-bit word of plane 0, a 10-bit B component in the top 10 bits of each 16-bit word of plane 1, and a 10-bit R component in the top 10 bits of each 16-bit word of plane 2, with the bottom 6 bits of each word unused. The horizontal and vertical dimensions of the R and B planes are halved relative to the image dimensions, and each R and B component is shared with the G components for which ⌊iG × 0.5⌋ =iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 10-bit G component in the top 10 bits of each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 10-bit B component in the top 10 bits of the word in bytes 0..1, and a 10-bit R component in the top 10 bits of the word in bytes 2..3, with the bottom 6 bits of each word unused. The horizontal and vertical dimensions of the BR plane are halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG ×0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 10-bit G component in the top 10 bits of each 16-bit word of plane 0, a 10-bit B component in the top 10 bits of each 16-bit word of plane 1, and a 10-bit R component in the top 10 bits of each 16-bit word of plane 2, with the bottom 6 bits of each word unused. The horizontal dimension of the R and B plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 10-bit G component in the top 10 bits of each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 10-bit B component in the top 10 bits of the word in bytes 0..1, and a 10-bit R component in the top 10 bits of the word in bytes 2..3, with the bottom 6 bits of each word unused. The horizontal dimension of the BR plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 10-bit G component in the top 10 bits of each 16-bit word of plane 0, a 10-bit B component in the top 10 bits of each 16-bit word of plane 1, and a 10-bit R component in the top 10 bits of each 16-bit word of plane 2, with the bottom 6 bits of each word unused. Each plane has the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane.
         * <li>VK_FORMAT_R12X4_UNORM_PACK16 specifies a one-component, 16-bit unsigned normalized format that has a single 12-bit R component in the top 12 bits of a 16-bit word, with the bottom 4 bits unused.
         * <li>VK_FORMAT_R12X4G12X4_UNORM_2PACK16 specifies a two-component, 32-bit unsigned normalized format that has a 12-bit R component in the top 12 bits of the word in bytes 0..1, and a 12-bit G component in the top 12 bits of the word in bytes 2..3, with the bottom 4 bits of each word unused.
         * <li>VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 specifies a four-component, 64-bit unsigned normalized format that has a 12-bit R component in the top 12 bits of the word in bytes 0..1, a 12-bit G component in the top 12 bits of the word in bytes 2..3, a 12-bit B component in the top 12 bits of the word in bytes 4..5, and a 12-bit A component in the top 12 bits of the word in bytes 6..7, with the bottom 4 bits of each word unused.
         * <li>VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 specifies a four-component, 64-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has a 12-bit G component for the even i coordinate in the top 12 bits of the word in bytes 0..1, a 12-bit B component in the top 12 bits of the word in bytes 2..3, a 12-bit G component for the odd i coordinate in the top 12 bits of the word in bytes 4..5, and a 12-bit R component in the top 12 bits of the word in bytes 6..7, with the bottom 4 bits of each word unused. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 specifies a four-component, 64-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has a 12-bit B component in the top 12 bits of the word in bytes 0..1, a 12-bit G component for the even i coordinate in the top 12 bits of the word in bytes 2..3, a 12-bit R component in the top 12 bits of the word in bytes 4..5, and a 12-bit G component for the odd i coordinate in the top 12 bits of the word in bytes 6..7, with the bottom 4 bits of each word unused. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 12-bit G component in the top 12 bits of each 16-bit word of plane 0, a 12-bit B component in the top 12 bits of each 16-bit word of plane 1, and a 12-bit R component in the top 12 bits of each 16-bit word of plane 2, with the bottom 4 bits of each word unused. The horizontal and vertical dimensions of the R and B planes are halved relative to the image dimensions, and each R and B component is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 12-bit G component in the top 12 bits of each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 12-bit B component in the top 12 bits of the word in bytes 0..1, and a 12-bit R component in the top 12 bits of the word in bytes 2..3, with the bottom 4 bits of each word unused. The horizontal and vertical dimensions of the BR plane are halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 12-bit G component in the top 12 bits of each 16-bit word of plane 0, a 12-bit B component in the top 12 bits of each 16-bit word of plane 1, and a 12-bit R component in the top 12 bits of each 16-bit word of plane 2, with the bottom 4 bits of each word unused. The horizontal dimension of the R and B plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 12-bit G component in the top 12 bits of each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 12-bit B component in the top 12 bits of the word in bytes 0..1, and a 12-bit R component in the top 12 bits of the word in bytes 2..3, with the bottom 4 bits of each word unused. The horizontal dimension of the BR plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 12-bit G component in the top 12 bits of each 16-bit word of plane 0, a 12-bit B component in the top 12 bits of each 16-bit word of plane 1, and a 12-bit R component in the top 12 bits of each 16-bit word of plane 2, with the bottom 4 bits of each word unused. Each plane has the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane.
         * <li>VK_FORMAT_G16B16G16R16_422_UNORM specifies a four-component, 64-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has a 16-bit G component for the even i coordinate in the word in bytes 0..1, a 16-bit B component in the word in bytes 2..3, a 16-bit G component for the odd i coordinate in the word in bytes 4..5, and a 16-bit R component in the word in bytes 6..7. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_B16G16R16G16_422_UNORM specifies a four-component, 64-bit format containing a pair of G components, an R component, and a B component, collectively encoding a 2×1 rectangle of unsigned normalized RGB texel data. One G value is present at each i coordinate, with the B and R values shared across both G values and thus recorded at half the horizontal resolution of the image. This format has a 16-bit B component in the word in bytes 0..1, a 16-bit G component for the even i coordinate in the word in bytes 2..3, a 16-bit R component in the word in bytes 4..5, and a 16-bit G component for the odd i coordinate in the word in bytes 6..7. This format only supports images with a width that is a multiple of two. For the purposes of the constraints on copy extents, this format is treated as a compressed format with a 2×1 compressed texel block.
         * <li>VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM specifies an unsigned normalized multi-planar format that has a 16-bit G component in each 16-bit word of plane 0, a 16-bit B component in each 16-bit word of plane 1, and a 16-bit R component in each 16-bit word of plane 2. The horizontal and vertical dimensions of the R and B planes are halved relative to the image dimensions, and each R and B component is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G16_B16R16_2PLANE_420_UNORM specifies an unsigned normalized multi-planar format that has a 16-bit G component in each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 16-bit B component in the word in bytes 0..1, and a 16-bit R component in the word in bytes 2..3. The horizontal and vertical dimensions of the BR plane are halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR and ⌊jG × 0.5⌋ = jB = jR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width and height that is a multiple of two.
         * <li>VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM specifies an unsigned normalized multi-planar format that has a 16-bit G component in each 16-bit word of plane 0, a 16-bit B component in each 16-bit word of plane 1, and a 16-bit R component in each 16-bit word of plane 2. The horizontal dimension of the R and B plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G16_B16R16_2PLANE_422_UNORM specifies an unsigned normalized multi-planar format that has a 16-bit G component in each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 16-bit B component in the word in bytes 0..1, and a 16-bit R component in the word in bytes 2..3. The horizontal dimension of the BR plane is halved relative to the image dimensions, and each R and B value is shared with the G components for which ⌊iG × 0.5⌋ = iB = iR. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane. This format only supports images with a width that is a multiple of two.
         * <li>VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM specifies an unsigned normalized multi-planar format that has a 16-bit G component in each 16-bit word of plane 0, a 16-bit B component in each 16-bit word of plane 1, and a 16-bit R component in each 16-bit word of plane 2. Each plane has the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, VK_IMAGE_ASPECT_PLANE_1_BIT for the B plane, and VK_IMAGE_ASPECT_PLANE_2_BIT for the R plane.
         * <li>VK_FORMAT_G8_B8R8_2PLANE_444_UNORM specifies an unsigned normalized multi-planar format that has an 8-bit G component in plane 0, and a two-component, 16-bit BR plane 1 consisting of an 8-bit B component in byte 0 and an 8-bit R component in byte 1. Both planes have the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane.
         * <li>VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 10-bit G component in the top 10 bits of each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 10-bit B component in the top 10 bits of the word in bytes 0..1, and a 10-bit R component in the top 10 bits of the word in bytes 2..3, the bottom 6 bits of each word unused. Both planes have the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane.
         * <li>VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 specifies an unsigned normalized multi-planar format that has a 12-bit G component in the top 12 bits of each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 12-bit B component in the top 12 bits of the word in bytes 0..1, and a 12-bit R component in the top 12 bits of the word in bytes 2..3, the bottom 4 bits of each word unused. Both planes have the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane.
         * <li>VK_FORMAT_G16_B16R16_2PLANE_444_UNORM specifies an unsigned normalized multi-planar format that has a 16-bit G component in each 16-bit word of plane 0, and a two-component, 32-bit BR plane 1 consisting of a 16-bit B component in the word in bytes 0..1, and a 16-bit R component in the word in bytes 2..3. Both planes have the same dimensions and each R, G and B component contributes to a single texel. The location of each plane when this image is in linear layout can be determined via vkGetImageSubresourceLayout, using VK_IMAGE_ASPECT_PLANE_0_BIT for the G plane, and VK_IMAGE_ASPECT_PLANE_1_BIT for the BR plane.
         * <li>VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes an 8×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes an 8×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data.
         * <li>VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes an 8×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes an 8×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG specifies a four-component, PVRTC compressed format where each 64-bit compressed texel block encodes a 4×4 rectangle of unsigned normalized RGBA texel data with sRGB nonlinear encoding applied to the RGB components.
         * <li>VK_FORMAT_R16G16_SFIXED5_NV specifies a two-component, 16-bit signed fixed-point format with linear encoding. The components are signed two’s-complement integers where the most significant bit specifies the sign bit, the next 10 bits specify the integer value, and the last 5 bits represent the fractional value. The signed 16-bit values can be converted to floats in the range [-1024,1023.96875] by dividing the value by 32 (25).
         * </ul>
         */
        using Format = VkFormat;

        /** <b>Name</b><hr><br>
         *
         * VkDeviceSize - Vulkan device memory size and offsets<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * VkDeviceSize represents device memory size and offset values:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef uint64_t VkDeviceSize;
         * @endcode
         */
        using DeviceSize = VkDeviceSize;

        /** <b>Name</b><hr><br>
         *
         * VkClearColorValue - Structure specifying a clear color value<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkClearColorValue structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * // Provided by VK_VERSION_1_0
         * typedef union VkClearColorValue {
         *     float       float32[4];
         *     int32_t     int32[4];
         *     uint32_t    uint32[4];
         * } VkClearColorValue;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>float32 are the color clear values when the format of the image or attachment is one of the numeric formats with a numeric type that is floating-point. Floating point values are automatically converted to the format of the image, with the clear value being treated as linear if the image is sRGB.
         * <li>int32 are the color clear values when the format of the image or attachment has a numeric type that is signed integer (SINT). Signed integer values are converted to the format of the image by casting to the smaller type (with negative 32-bit values mapping to negative values in the smaller type). If the integer clear value is not representable in the target type (e.g. would overflow in conversion to that type), the clear value is undefined.
         * <li>uint32 are the color clear values when the format of the image or attachment has a numeric type that is unsigned integer (UINT). Unsigned integer values are converted to the format of the image by casting to the integer type with fewer bits.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The four array elements of the clear color map to R, G, B, and A components of image formats, in order.<br><br>
         *
         * If the image has more than one sample, the same value is written to all samples for any pixels being cleared.<br><br>
         *
         * If the image or attachment format has a 64-bit component width, the first 2 array elements of each of the arrays above are reinterpreted as a single 64-bit element for the R component. The next 2 array elements are used in the same way for the G component. In other words, the union behaves as if it had the following additional members:
         *
         * @code
         * double float64[2];
         * int64_t int64[2];
         * uint64_t uint64[2];
         * @endcode
         */
        using ClearColorValue = VkClearColorValue;
        VULKANPP_CONSTEXPR ClearColorValue createClearColorValue(
                const float        float32[4]
        ) {
                return {
                        .float32 = { float32[0], float32[1], float32[2], float32[3] }
                };
        }
        VULKANPP_CONSTEXPR ClearColorValue createClearColorValue(
                const int32_t        int32[4]
        ) {
                return {
                        .int32 = { int32[0], int32[1], int32[2], int32[3] }
                };
        }
        VULKANPP_CONSTEXPR ClearColorValue createClearColorValue(
                const uint32_t        uint32[4]
        ) {
                return {
                        .uint32 = { uint32[0], uint32[1], uint32[2], uint32[3] }
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkClearDepthStencilValue - Structure specifying a clear depth stencil value<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkClearDepthStencilValue structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkClearDepthStencilValue {
         *     float       depth;
         *     uint32_t    stencil;
         * } VkClearDepthStencilValue;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>depth is the clear value for the depth aspect of the depth/stencil attachment. It is a floating-point value which is automatically converted to the attachment’s format.
         * <li>stencil is the clear value for the stencil aspect of the depth/stencil attachment. It is a 32-bit integer value which is converted to the attachment’s format by taking the appropriate number of LSBs.
         * </ul>
         */
        using ClearDepthStencilValue = VkClearDepthStencilValue;
        VULKANPP_CONSTEXPR ClearDepthStencilValue createClearDepthStencilValue(
                const float           &depth,
                const uint32_t        &stencil
        ) {
                return {
                        .depth = depth,
                        .stencil = stencil
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkClearValue - Structure specifying a clear value<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkClearValue union is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef union VkClearValue {
         *     VkClearColorValue           color;
         *     VkClearDepthStencilValue    depthStencil;
         * } VkClearValue;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>color specifies the color image clear values to use when clearing a color image or attachment.
         * <li>depthStencil specifies the depth and stencil clear values to use when clearing a depth/stencil image or attachment.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * This union is used where part of the API requires either color or depth/stencil clear values, depending on the attachment, and defines the initial clear values in the VkRenderPassBeginInfo structure.
         */
        using ClearValue = VkClearValue;
        VULKANPP_CONSTEXPR ClearValue createClearValue(
                const ClearColorValue        &clearColorValue
        ) {
                return {
                        .color = clearColorValue
                };
        }
        VULKANPP_CONSTEXPR ClearValue createClearValue(
                const ClearDepthStencilValue        &depthStencil
        ) {
                return {
                        .depthStencil = depthStencil
                };
        }
        VULKANPP_CONSTEXPR ClearValue createClearValue(
                const float        &r,
                const float        &g,
                const float        &b,
                const float        &a
        ) {
                const float float32[4]{r, g, b ,a};
                return {
                        .color = vk::createClearColorValue(float32)
                };
        }
        VULKANPP_CONSTEXPR ClearValue createClearValue(
                const int32_t        &r,
                const int32_t        &g,
                const int32_t        &b,
                const int32_t        &a
        ) {
                const int32_t int32[4]{r, g, b ,a};
                return {
                        .color = vk::createClearColorValue(int32)
                };
        }
        VULKANPP_CONSTEXPR ClearValue createClearValue(
                const uint32_t        &r,
                const uint32_t        &g,
                const uint32_t        &b,
                const uint32_t        &a
        ) {
                const uint32_t uint32[4]{r, g, b ,a};
                return {
                        .color = vk::createClearColorValue(uint32)
                };
        }
        VULKANPP_CONSTEXPR ClearValue createClearValue(
                const float           &depth,
                const uint32_t        &stencil
        ) {
                return {
                        .depthStencil = vk::createClearDepthStencilValue(depth, stencil)
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorPoolSize - Structure specifying descriptor pool size<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorPoolSize structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using DescriptorPoolSize = VkDescriptorPoolSize;
        VULKANPP_CONSTEXPR DescriptorPoolSize createDescriptorPoolSize(
                const VkDescriptorType        &type,
                const uint32_t                &descriptorCount
        ) {
                return {
                        .type = type,
                        .descriptorCount = descriptorCount
                };
        }

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
        using Extent2D = VkExtent2D;
        VULKANPP_CONSTEXPR Extent2D createExtent2D(
                const uint32_t        &width,
                const uint32_t        &height
        ) {
                return {
                        .width = width,
                        .height = height
                };
        }

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
        using Viewport = VkViewport;
        VULKANPP_CONSTEXPR Viewport createViewport(
                const Extent2D        &extent
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

        /** <b>Name</b><hr><br>
         *
         * VkOffset2D - Structure specifying a two-dimensional offset<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A two-dimensional offset is defined by the structure:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkOffset2D {
         *     int32_t    x;
         *     int32_t    y;
         * } VkOffset2D;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>x is the x offset.
         * <li>y is the y offset.
         * </ul>
         */
        using Offset2D = VkOffset2D;
        VULKANPP_CONSTEXPR Offset2D createOffset2D(
                const int32_t        &x,
                const int32_t        &y
        ) {
                return {
                        .x = x,
                        .y = y
                };
        }

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
        using Rect2D = VkRect2D;
        VULKANPP_CONSTEXPR Rect2D createRect2D(
                const Offset2D        &offset,
                const Extent2D        &extent
        ) {
                return {
                        .offset = offset,
                        .extent = extent
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkExtent3D - Structure specifying a three-dimensional extent<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A three-dimensional extent is defined by the structure:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkExtent3D {
         *     uint32_t    width;
         *     uint32_t    height;
         *     uint32_t    depth;
         * } VkExtent3D;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>width is the width of the extent.
         * <li>height is the height of the extent.
         * <li>depth is the depth of the extent.
         * </ul>
         */
        using Extent3D = VkExtent3D;
        VULKANPP_CONSTEXPR Extent3D createExtent3D(
                const uint32_t        &width,
                const uint32_t        &height,
                const uint32_t        &depth
        )  {
                return {
                        .width = width,
                        .height = height,
                        .depth = depth
                };
        }
        VULKANPP_CONSTEXPR Extent3D createExtent3D(
                const Extent2D        &extent2D,
                const uint32_t        &depth
        )  {
                return {
                        .width = extent2D.width,
                        .height = extent2D.height,
                        .depth = depth
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkAccelerationStructureNV - Opaque handle to an acceleration structure object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Acceleration structures for the VK_NV_ray_tracing extension are represented by the similar VkAccelerationStructureNV handles:
         *
         * @code
         * // Provided by VK_NV_ray_tracing
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkAccelerationStructureNV)
         * @endcode
         */
        using AccelerationStructureNV = VkAccelerationStructureNV;

        /** <b>Name</b><hr><br>
         *
         * VkDebugReportCallbackEXT - Opaque handle to a debug report callback object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Debug report callbacks are represented by VkDebugReportCallbackEXT handles:
         *
         * @code
         * // Provided by VK_EXT_debug_report
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugReportCallbackEXT)
         * @endcode
         */
        using DebugReportCallbackEXT = VkDebugReportCallbackEXT;

        /** <b>Name</b><hr><br>
         *
         * VkDebugUtilsMessengerEXT - Opaque handle to a debug messenger object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A VkDebugUtilsMessengerEXT is a messenger object which handles passing along debug messages to a provided debug callback.
         *
         * @code
         * // Provided by VK_EXT_debug_utils
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT)
         * @endcode
         *
         * <b>Description</b><hr><br>
         * The debug messenger will provide detailed feedback on the application’s use of Vulkan when events of interest occur. When an event of interest does occur, the debug messenger will submit a debug message to the debug callback that was provided during its creation. Additionally, the debug messenger is responsible with filtering out debug messages that the callback is not interested in and will only provide desired debug messages.
         */
        using DebugUtilsMessengerEXT = VkDebugUtilsMessengerEXT;

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorUpdateTemplate - Opaque handle to a descriptor update template<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A descriptor update template specifies a mapping from descriptor update information in host memory to descriptors in a descriptor set. It is designed to avoid passing redundant information to the driver when frequently updating the same set of descriptors in descriptor sets.<br><br>
         *
         * Descriptor update template objects are represented by VkDescriptorUpdateTemplate handles:
         *
         * @code
         * // Provided by VK_VERSION_1_1
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorUpdateTemplate)
         * @endcode
         *
         * or the equivalent
         *
         * @code
         * // Provided by VK_KHR_descriptor_update_template
         * typedef VkDescriptorUpdateTemplate VkDescriptorUpdateTemplateKHR;
         * @endcode
         */
        using DescriptorUpdateTemplate = VkDescriptorUpdateTemplate;
        // TODO create

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
        using Instance = VkInstance;
        Instance createInstance(
                const char                             *name,
                const uint32_t                         &version,
                const std::vector<const char *>        &enabledLayerNames,
                const std::vector<const char *>        &enabledExtensionNames,
                const VkAllocationCallbacks            *pAllocator,
                const void                             *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDevice - Opaque handle to a physical device object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Vulkan separates the concept of physical and logical devices. A physical device usually represents a single complete implementation of Vulkan (excluding instance-level functionality) available to the host, of which there are a finite number. A logical device represents an instance of that implementation with its own state and resources independent of other logical devices.<br><br>
         *
         * Physical devices are represented by VkPhysicalDevice handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_HANDLE(VkPhysicalDevice)
         * @endcode
         */
        using PhysicalDevice = VkPhysicalDevice;
        std::vector<PhysicalDevice> getPhysicalDevices(
                const Instance        &instance
        );

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceFeatures - Structure describing the fine-grained features that can be supported by an implementation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceFeatures structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPhysicalDeviceFeatures {
         *     VkBool32    robustBufferAccess;
         *     VkBool32    fullDrawIndexUint32;
         *     VkBool32    imageCubeArray;
         *     VkBool32    independentBlend;
         *     VkBool32    geometryShader;
         *     VkBool32    tessellationShader;
         *     VkBool32    sampleRateShading;
         *     VkBool32    dualSrcBlend;
         *     VkBool32    logicOp;
         *     VkBool32    multiDrawIndirect;
         *     VkBool32    drawIndirectFirstInstance;
         *     VkBool32    depthClamp;
         *     VkBool32    depthBiasClamp;
         *     VkBool32    fillModeNonSolid;
         *     VkBool32    depthBounds;
         *     VkBool32    wideLines;
         *     VkBool32    largePoints;
         *     VkBool32    alphaToOne;
         *     VkBool32    multiViewport;
         *     VkBool32    samplerAnisotropy;
         *     VkBool32    textureCompressionETC2;
         *     VkBool32    textureCompressionASTC_LDR;
         *     VkBool32    textureCompressionBC;
         *     VkBool32    occlusionQueryPrecise;
         *     VkBool32    pipelineStatisticsQuery;
         *     VkBool32    vertexPipelineStoresAndAtomics;
         *     VkBool32    fragmentStoresAndAtomics;
         *     VkBool32    shaderTessellationAndGeometryPointSize;
         *     VkBool32    shaderImageGatherExtended;
         *     VkBool32    shaderStorageImageExtendedFormats;
         *     VkBool32    shaderStorageImageMultisample;
         *     VkBool32    shaderStorageImageReadWithoutFormat;
         *     VkBool32    shaderStorageImageWriteWithoutFormat;
         *     VkBool32    shaderUniformBufferArrayDynamicIndexing;
         *     VkBool32    shaderSampledImageArrayDynamicIndexing;
         *     VkBool32    shaderStorageBufferArrayDynamicIndexing;
         *     VkBool32    shaderStorageImageArrayDynamicIndexing;
         *     VkBool32    shaderClipDistance;
         *     VkBool32    shaderCullDistance;
         *     VkBool32    shaderFloat64;
         *     VkBool32    shaderInt64;
         *     VkBool32    shaderInt16;
         *     VkBool32    shaderResourceResidency;
         *     VkBool32    shaderResourceMinLod;
         *     VkBool32    sparseBinding;
         *     VkBool32    sparseResidencyBuffer;
         *     VkBool32    sparseResidencyImage2D;
         *     VkBool32    sparseResidencyImage3D;
         *     VkBool32    sparseResidency2Samples;
         *     VkBool32    sparseResidency4Samples;
         *     VkBool32    sparseResidency8Samples;
         *     VkBool32    sparseResidency16Samples;
         *     VkBool32    sparseResidencyAliased;
         *     VkBool32    variableMultisampleRate;
         *     VkBool32    inheritedQueries;
         * } VkPhysicalDeviceFeatures;
         * @endcode
         *
         * <b>Members</b><hr><br>
         *
         * This structure describes the following features:
         * <ul>
         * <li>robustBufferAccess specifies that accesses to buffers are bounds-checked against the range of the buffer descriptor (as determined by VkDescriptorBufferInfo::range, VkBufferViewCreateInfo::range, or the size of the buffer). Out of bounds accesses <b>must</b> not cause application termination, and the effects of shader loads, stores, and atomics <b>must</b> conform to an implementation-dependent behavior as described below.
         *     <ul>
         *     <li>A buffer access is considered to be out of bounds if any of the following are true:
         *         <ul>
         *         <li>The pointer was formed by OpImageTexelPointer and the coordinate is less than zero or greater than or equal to the number of whole elements in the bound range.
         *         <li>The pointer was not formed by OpImageTexelPointer and the object pointed to is not wholly contained within the bound range. This includes accesses performed via variable pointers where the buffer descriptor being accessed cannot be statically determined. Uninitialized pointers and pointers equal to OpConstantNull are treated as pointing to a zero-sized object, so all accesses through such pointers are considered to be out of bounds. Buffer accesses through buffer device addresses are not bounds-checked.
         *         <li>If the VkPhysicalDeviceCooperativeMatrixFeaturesNV::cooperativeMatrixRobustBufferAccess feature is not enabled, then accesses using OpCooperativeMatrixLoadNV and OpCooperativeMatrixStoreNV may not be bounds-checked.
         *         <li>If the VkPhysicalDeviceCooperativeMatrixFeaturesKHR::cooperativeMatrixRobustBufferAccess feature is not enabled, then accesses using OpCooperativeMatrixLoadKHR and OpCooperativeMatrixStoreKHR may not be bounds-checked.
         *         </ul>
         *     </ul>
         * </ul>
         * @note If a SPIR-V OpLoad instruction loads a structure and the tail end of the structure is out of bounds, then all members of the structure are considered out of bounds even if the members at the end are not statically used.
         *
         * <b>Description</b><hr><br>
         * <ul>
         * <li>If robustBufferAccess2 is not enabled and any buffer access is determined to be out of bounds, then any other access of the same type (load, store, or atomic) to the same buffer that accesses an address less than 16 bytes away from the out of bounds address <b>may</b> also be considered out of bounds.
         * <li>If the access is a load that reads from the same memory locations as a prior store in the same shader invocation, with no other intervening accesses to the same memory locations in that shader invocation, then the result of the load <b>may</b> be the value stored by the store instruction, even if the access is out of bounds. If the load is Volatile, then an out of bounds load <b>must</b> return the appropriate out of bounds value.
         *     <ul>
         *     <li>Accesses to descriptors written with a VK_NULL_HANDLE resource or view are not considered to be out of bounds. Instead, each type of descriptor access defines a specific behavior for accesses to a null descriptor.
         *     <li>Out-of-bounds buffer loads will return any of the following values:
         *     </ul>
         * <li>If the access is to a uniform buffer and robustBufferAccess2 is enabled, loads of offsets between the end of the descriptor range and the end of the descriptor range rounded up to a multiple of robustUniformBufferAccessSizeAlignment bytes <b>must</b> return either zero values or the contents of the memory at the offset being loaded. Loads of offsets past the descriptor range rounded up to a multiple of robustUniformBufferAccessSizeAlignment bytes <b>must</b> return zero values.
         * <li>If the access is to a storage buffer and robustBufferAccess2 is enabled, loads of offsets between the end of the descriptor range and the end of the descriptor range rounded up to a multiple of robustStorageBufferAccessSizeAlignment bytes <b>must</b> return either zero values or the contents of the memory at the offset being loaded. Loads of offsets past the descriptor range rounded up to a multiple of robustStorageBufferAccessSizeAlignment bytes <b>must</b> return zero values. Similarly, stores to addresses between the end of the descriptor range and the end of the descriptor range rounded up to a multiple of robustStorageBufferAccessSizeAlignment bytes <b>may</b> be discarded.
         * <li>Non-atomic accesses to storage buffers that are a multiple of 32 bits <b>may</b> be decomposed into 32-bit accesses that are individually bounds-checked.
         * <li>If the access is to an index buffer and robustBufferAccess2 is enabled, zero values <b>must</b> be returned.
         * <li>If the access is to a uniform texel buffer or storage texel buffer and robustBufferAccess2 is enabled, zero values <b>must</b> be returned, and then Conversion to RGBA is applied based on the buffer view’s format.
         * <li>Values from anywhere within the memory range(s) bound to the buffer (possibly including bytes of memory past the end of the buffer, up to the end of the bound range).
         * <li>Zero values, or (0,0,0,x) vectors for vector reads where x is a valid value represented in the type of the vector components and <b>may</b> be any of:
         *     <ul>
         *     <li>0, 1, or the maximum representable positive integer value, for signed or unsigned integer components
         *     <li>0.0 or 1.0, for floating-point components
         *         <ul>
         *         <li>Out-of-bounds writes <b>may</b> modify values within the memory range(s) bound to the buffer, but <b>must</b> not modify any other memory.
         *         </ul>
         *     </ul>
         * <li>If robustBufferAccess2 is enabled, out of bounds writes <b>must</b> not modify any memory.
         *     <ul>
         *     <li>Out-of-bounds atomics <b>may</b> modify values within the memory range(s) bound to the buffer, but <b>must</b> not modify any other memory, and return an undefined value.
         *     </ul>
         * <li>If robustBufferAccess2 is enabled, out of bounds atomics <b>must</b> not modify any memory, and return an undefined value.
         *     <ul>
         *     <li>If robustBufferAccess2 is disabled, vertex input attributes are considered out of bounds if the offset of the attribute in the bound vertex buffer range plus the size of the attribute is greater than either:
         *     </ul>
         * <li>vertexBufferRangeSize, if bindingStride == 0; or
         * <li>(vertexBufferRangeSize - (vertexBufferRangeSize % bindingStride))<br>
         * where vertexBufferRangeSize is the byte size of the memory range bound to the vertex buffer binding and bindingStride is the byte stride of the corresponding vertex input binding. Further, if any vertex input attribute using a specific vertex input binding is out of bounds, then all vertex input attributes using that vertex input binding for that vertex shader invocation are considered out of bounds.
         * <li>If a vertex input attribute is out of bounds, it will be assigned one of the following values:
         *     <ul>
         *     <li>Values from anywhere within the memory range(s) bound to the buffer, converted according to the format of the attribute.
         *     <li>Zero values, format converted according to the format of the attribute.
         *     <li>Zero values, or (0,0,0,x) vectors, as described above.
         *         <ul>
         *         <li>If robustBufferAccess2 is enabled, vertex input attributes are considered out of bounds if the offset of the attribute in the bound vertex buffer range plus the size of the attribute is greater than the byte size of the memory range bound to the vertex buffer binding.
         *         </ul>
         *     </ul>
         * <li>If a vertex input attribute is out of bounds, the raw data extracted are zero values, and missing G, B, or A components are filled with (0,0,1).
         *     <ul>
         *     <li>If robustBufferAccess is not enabled, applications <b>must</b> not perform out of bounds accesses except under the conditions enabled by the pipelineRobustness feature.
         *     </ul>
         * <li>fullDrawIndexUint32 specifies the full 32-bit range of indices is supported for indexed draw calls when using a VkIndexType of VK_INDEX_TYPE_UINT32. maxDrawIndexedIndexValue is the maximum index value that <b>may</b> be used (aside from the primitive restart index, which is always 2^32-1 when the VkIndexType is VK_INDEX_TYPE_UINT32). If this feature is supported, maxDrawIndexedIndexValue <b>must</b> be 2^32-1; otherwise it <b>must</b> be no smaller than 2^24-1. See maxDrawIndexedIndexValue.
         * <li>imageCubeArray specifies whether image views with a VkImageViewType of VK_IMAGE_VIEW_TYPE_CUBE_ARRAY <b>can</b> be created, and that the corresponding SampledCubeArray and ImageCubeArray SPIR-V capabilities <b>can</b> be used in shader code.
         * <li>independentBlend specifies whether the VkPipelineColorBlendAttachmentState settings are controlled independently per-attachment. If this feature is not enabled, the VkPipelineColorBlendAttachmentState settings for all color attachments must be identical. Otherwise, a different VkPipelineColorBlendAttachmentState <b>can</b> be provided for each bound color attachment.
         * <li>geometryShader specifies whether geometry shaders are supported. If this feature is not enabled, the VK_SHADER_STAGE_GEOMETRY_BIT and VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT enum values <b>must</b> not be used. This also specifies whether shader modules <b>can</b> declare the Geometry capability.
         * <li>tessellationShader specifies whether tessellation control and evaluation shaders are supported. If this feature is not enabled, the VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT, VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT, and VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO enum values <b>must</b> not be used. This also specifies whether shader modules <b>can</b> declare the Tessellation capability.
         * <li>sampleRateShading specifies whether Sample Shading and multisample interpolation are supported. If this feature is not enabled, the sampleShadingEnable member of the VkPipelineMultisampleStateCreateInfo structure <b>must</b> be set to VK_FALSE and the minSampleShading member is ignored. This also specifies whether shader modules <b>can</b> declare the SampleRateShading capability.
         * <li>dualSrcBlend specifies whether blend operations which take two sources are supported. If this feature is not enabled, the VK_BLEND_FACTOR_SRC1_COLOR, VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR, VK_BLEND_FACTOR_SRC1_ALPHA, and VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA enum values <b>must</b> not be used as source or destination blending factors. See https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#framebuffer-dsb.
         * <li>logicOp specifies whether logic operations are supported. If this feature is not enabled, the logicOpEnable member of the VkPipelineColorBlendStateCreateInfo structure <b>must</b> be set to VK_FALSE, and the logicOp member is ignored.
         * <li>multiDrawIndirect specifies whether multiple draw indirect is supported. If this feature is not enabled, the drawCount parameter to the vkCmdDrawIndirect and vkCmdDrawIndexedIndirect commands <b>must</b> be 0 or 1. The maxDrawIndirectCount member of the VkPhysicalDeviceLimits structure <b>must</b> also be 1 if this feature is not supported. See maxDrawIndirectCount.
         * <li>drawIndirectFirstInstance specifies whether indirect drawing calls support the firstInstance parameter. If this feature is not enabled, the firstInstance member of all VkDrawIndirectCommand and VkDrawIndexedIndirectCommand structures that are provided to the vkCmdDrawIndirect and vkCmdDrawIndexedIndirect commands <b>must</b> be 0.
         * <li>depthClamp specifies whether depth clamping is supported. If this feature is not enabled, the depthClampEnable member of the VkPipelineRasterizationStateCreateInfo structure <b>must</b> be set to VK_FALSE. Otherwise, setting depthClampEnable to VK_TRUE will enable depth clamping.
         * <li>depthBiasClamp specifies whether depth bias clamping is supported. If this feature is not enabled, the depthBiasClamp member of the VkPipelineRasterizationStateCreateInfo structure <b>must</b> be set to 0.0 unless the VK_DYNAMIC_STATE_DEPTH_BIAS dynamic state is enabled, and the depthBiasClamp parameter to vkCmdSetDepthBias <b>must</b> be set to 0.0.
         * <li>fillModeNonSolid specifies whether point and wireframe fill modes are supported. If this feature is not enabled, the VK_POLYGON_MODE_POINT and VK_POLYGON_MODE_LINE enum values <b>must</b> not be used.
         * <li>depthBounds specifies whether depth bounds tests are supported. If this feature is not enabled, the depthBoundsTestEnable member of the VkPipelineDepthStencilStateCreateInfo structure <b>must</b> be set to VK_FALSE. When depthBoundsTestEnable is set to VK_FALSE, the minDepthBounds and maxDepthBounds members of the VkPipelineDepthStencilStateCreateInfo structure are ignored.
         * <li>wideLines specifies whether lines with width other than 1.0 are supported. If this feature is not enabled, the lineWidth member of the VkPipelineRasterizationStateCreateInfo structure <b>must</b> be set to 1.0 unless the VK_DYNAMIC_STATE_LINE_WIDTH dynamic state is enabled, and the lineWidth parameter to vkCmdSetLineWidth <b>must</b> be set to 1.0. When this feature is supported, the range and granularity of supported line widths are indicated by the lineWidthRange and lineWidthGranularity members of the VkPhysicalDeviceLimits structure, respectively.
         * <li>largePoints specifies whether points with size greater than 1.0 are supported. If this feature is not enabled, only a point size of 1.0 written by a shader is supported. The range and granularity of supported point sizes are indicated by the pointSizeRange and pointSizeGranularity members of the VkPhysicalDeviceLimits structure, respectively.
         * <li>alphaToOne specifies whether the implementation is able to replace the alpha value of the fragment shader color output in the Multisample Coverage fragment operation. If this feature is not enabled, then the alphaToOneEnable member of the VkPipelineMultisampleStateCreateInfo structure <b>must</b> be set to VK_FALSE. Otherwise setting alphaToOneEnable to VK_TRUE will enable alpha-to-one behavior.
         * <li>multiViewport specifies whether more than one viewport is supported. If this feature is not enabled:
         *     <ul>
         *     <li>The viewportCount and scissorCount members of the VkPipelineViewportStateCreateInfo structure <b>must</b> be set to 1.
         *     <li>The firstViewport and viewportCount parameters to the vkCmdSetViewport command <b>must</b> be set to 0 and 1, respectively.
         *     <li>The firstScissor and scissorCount parameters to the vkCmdSetScissor command <b>must</b> be set to 0 and 1, respectively.
         *     <li>The exclusiveScissorCount member of the VkPipelineViewportExclusiveScissorStateCreateInfoNV structure <b>must</b> be set to 0 or 1.
         *     <li>The firstExclusiveScissor and exclusiveScissorCount parameters to the vkCmdSetExclusiveScissorNV command <b>must</b> be set to 0 and 1, respectively.
         *     </ul>
         * <li>samplerAnisotropy specifies whether anisotropic filtering is supported. If this feature is not enabled, the anisotropyEnable member of the VkSamplerCreateInfo structure <b>must</b> be VK_FALSE.
         * <li>textureCompressionETC2 specifies whether all of the ETC2 and EAC compressed texture formats are supported. If this feature is enabled, then the VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT and VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT features <b>must</b> be supported in optimalTilingFeatures for the following formats:
         *     <ul>
         *     <li>VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK
         *     <li>VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK
         *     <li>VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK
         *     <li>VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK
         *     <li>VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK
         *     <li>VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK
         *     <li>VK_FORMAT_EAC_R11_UNORM_BLOCK
         *     <li>VK_FORMAT_EAC_R11_SNORM_BLOCK
         *     <li>VK_FORMAT_EAC_R11G11_UNORM_BLOCK
         *     <li>VK_FORMAT_EAC_R11G11_SNORM_BLOCK
         *     </ul>
         * </ul>
         * To query for additional properties, or if the feature is not enabled, vkGetPhysicalDeviceFormatProperties and vkGetPhysicalDeviceImageFormatProperties <b>can</b> be used to check for supported properties of individual formats as normal.
         * <ul>
         * <li>textureCompressionASTC_LDR specifies whether all of the ASTC LDR compressed texture formats are supported. If this feature is enabled, then the VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT and VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT features <b>must<li> be supported in optimalTilingFeatures for the following formats:
         *     <ul>
         *     <li>VK_FORMAT_ASTC_4x4_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_4x4_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_5x4_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_5x4_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_5x5_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_5x5_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_6x5_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_6x5_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_6x6_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_6x6_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_8x5_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_8x5_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_8x6_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_8x6_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_8x8_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_8x8_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_10x5_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_10x5_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_10x6_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_10x6_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_10x8_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_10x8_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_10x10_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_10x10_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_12x10_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_12x10_SRGB_BLOCK
         *     <li>VK_FORMAT_ASTC_12x12_UNORM_BLOCK
         *     <li>VK_FORMAT_ASTC_12x12_SRGB_BLOCK
         *     </ul>
         * </ul>
         * To query for additional properties, or if the feature is not enabled, vkGetPhysicalDeviceFormatProperties and vkGetPhysicalDeviceImageFormatProperties <b>can</b> be used to check for supported properties of individual formats as normal.
         * <ul>
         * <li>textureCompressionBC specifies whether all of the BC compressed texture formats are supported. If this feature is enabled, then the VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT and VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT features <b>must</b> be supported in optimalTilingFeatures for the following formats:
         *     <ul>
         *     <li>VK_FORMAT_BC1_RGB_UNORM_BLOCK
         *     <li>VK_FORMAT_BC1_RGB_SRGB_BLOCK
         *     <li>VK_FORMAT_BC1_RGBA_UNORM_BLOCK
         *     <li>VK_FORMAT_BC1_RGBA_SRGB_BLOCK
         *     <li>VK_FORMAT_BC2_UNORM_BLOCK
         *     <li>VK_FORMAT_BC2_SRGB_BLOCK
         *     <li>VK_FORMAT_BC3_UNORM_BLOCK
         *     <li>VK_FORMAT_BC3_SRGB_BLOCK
         *     <li>VK_FORMAT_BC4_UNORM_BLOCK
         *     <li>VK_FORMAT_BC4_SNORM_BLOCK
         *     <li>VK_FORMAT_BC5_UNORM_BLOCK
         *     <li>VK_FORMAT_BC5_SNORM_BLOCK
         *     <li>VK_FORMAT_BC6H_UFLOAT_BLOCK
         *     <li>VK_FORMAT_BC6H_SFLOAT_BLOCK
         *     <li>VK_FORMAT_BC7_UNORM_BLOCK
         *     <li>VK_FORMAT_BC7_SRGB_BLOCK
         *     </ul>
         * </ul>
         * To query for additional properties, or if the feature is not enabled, vkGetPhysicalDeviceFormatProperties and vkGetPhysicalDeviceImageFormatProperties <b>can</b> be used to check for supported properties of individual formats as normal.
         * <ul>
         * <li>occlusionQueryPrecise specifies whether occlusion queries returning actual sample counts are supported. Occlusion queries are created in a VkQueryPool by specifying the queryType of VK_QUERY_TYPE_OCCLUSION in the VkQueryPoolCreateInfo structure which is passed to vkCreateQueryPool. If this feature is enabled, queries of this type <b>can</b> enable VK_QUERY_CONTROL_PRECISE_BIT in the flags parameter to vkCmdBeginQuery. If this feature is not supported, the implementation supports only boolean occlusion queries. When any samples are passed, boolean queries will return a non-zero result value, otherwise a result value of zero is returned. When this feature is enabled and VK_QUERY_CONTROL_PRECISE_BIT is set, occlusion queries will report the actual number of samples passed.
         * <li>pipelineStatisticsQuery specifies whether the pipeline statistics queries are supported. If this feature is not enabled, queries of type VK_QUERY_TYPE_PIPELINE_STATISTICS <b>cannot</b> be created, and none of the VkQueryPipelineStatisticFlagBits bits <b>can</b> be set in the pipelineStatistics member of the VkQueryPoolCreateInfo structure.
         * <li>vertexPipelineStoresAndAtomics specifies whether storage buffers and images support stores and atomic operations in the vertex, tessellation, and geometry shader stages. If this feature is not enabled, all storage image, storage texel buffer, and storage buffer variables used by these stages in shader modules <b>must</b> be decorated with the NonWritable decoration (or the readonly memory qualifier in GLSL).
         * <li>fragmentStoresAndAtomics specifies whether storage buffers and images support stores and atomic operations in the fragment shader stage. If this feature is not enabled, all storage image, storage texel buffer, and storage buffer variables used by the fragment stage in shader modules <b>must</b> be decorated with the NonWritable decoration (or the readonly memory qualifier in GLSL).
         * <li>shaderTessellationAndGeometryPointSize specifies whether the PointSize built-in decoration is available in the tessellation control, tessellation evaluation, and geometry shader stages. If this feature is not enabled, members decorated with the PointSize built-in decoration <b>must</b> not be read from or written to and all points written from a tessellation or geometry shader will have a size of 1.0. This also specifies whether shader modules <b>can</b> declare the TessellationPointSize capability for tessellation control and evaluation shaders, or if the shader modules <b>can</b> declare the GeometryPointSize capability for geometry shaders. An implementation supporting this feature <b>must</b> also support one or both of the tessellationShader or geometryShader features.
         * <li>shaderImageGatherExtended specifies whether the extended set of image gather instructions are available in shader code. If this feature is not enabled, the OpImage*Gather instructions do not support the Offset and ConstOffsets operands. This also specifies whether shader modules <b>can</b> declare the ImageGatherExtended capability.
         * <li>shaderStorageImageExtendedFormats specifies whether all the “storage image extended formats” below are supported; if this feature is supported, then the VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT <b>must</b> be supported in optimalTilingFeatures for the following formats:
         *     <ul>
         *     <li>VK_FORMAT_R16G16_SFLOAT
         *     <li>VK_FORMAT_B10G11R11_UFLOAT_PACK32
         *     <li>VK_FORMAT_R16_SFLOAT
         *     <li>VK_FORMAT_R16G16B16A16_UNORM
         *     <li>VK_FORMAT_A2B10G10R10_UNORM_PACK32
         *     <li>VK_FORMAT_R16G16_UNORM
         *     <li>VK_FORMAT_R8G8_UNORM
         *     <li>VK_FORMAT_R16_UNORM
         *     <li>VK_FORMAT_R8_UNORM
         *     <li>VK_FORMAT_R16G16B16A16_SNORM
         *     <li>VK_FORMAT_R16G16_SNORM
         *     <li>VK_FORMAT_R8G8_SNORM
         *     <li>VK_FORMAT_R16_SNORM
         *     <li>VK_FORMAT_R8_SNORM
         *     <li>VK_FORMAT_R16G16_SINT
         *     <li>VK_FORMAT_R8G8_SINT
         *     <li>VK_FORMAT_R16_SINT
         *     <li>VK_FORMAT_R8_SINT
         *     <li>VK_FORMAT_A2B10G10R10_UINT_PACK32
         *     <li>VK_FORMAT_R16G16_UINT
         *     <li>VK_FORMAT_R8G8_UINT
         *     <li>VK_FORMAT_R16_UINT
         *     <li>VK_FORMAT_R8_UINT
         *
         *     @note shaderStorageImageExtendedFormats feature only adds a guarantee of format support, which is specified for the whole physical device. Therefore enabling or disabling the feature via vkCreateDevice has no practical effect.<br>
         *     To query for additional properties, or if the feature is not supported, vkGetPhysicalDeviceFormatProperties and vkGetPhysicalDeviceImageFormatProperties <b>can</b> be used to check for supported properties of individual formats, as usual rules allow.<br>
         *     VK_FORMAT_R32G32_UINT, VK_FORMAT_R32G32_SINT, and VK_FORMAT_R32G32_SFLOAT from StorageImageExtendedFormats SPIR-V capability, are already covered by core Vulkan mandatory format support.
         *
         *     </ul>
         * <li>shaderStorageImageMultisample specifies whether multisampled storage images are supported. If this feature is not enabled, images that are created with a usage that includes VK_IMAGE_USAGE_STORAGE_BIT <b>must</b> be created with samples equal to VK_SAMPLE_COUNT_1_BIT. This also specifies whether shader modules <b>can</b> declare the StorageImageMultisample and ImageMSArray capabilities.
         * <li>shaderStorageImageReadWithoutFormat specifies whether storage images and storage texel buffers require a format qualifier to be specified when reading. shaderStorageImageReadWithoutFormat applies only to formats listed in the storage without format list.
         * <li>shaderStorageImageWriteWithoutFormat specifies whether storage images and storage texel buffers require a format qualifier to be specified when writing. shaderStorageImageWriteWithoutFormat applies only to formats listed in the storage without format list.
         * <li>shaderUniformBufferArrayDynamicIndexing specifies whether arrays of uniform buffers <b>can</b> be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER or VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also specifies whether shader modules <b>can</b> declare the UniformBufferArrayDynamicIndexing capability.
         * <li>shaderSampledImageArrayDynamicIndexing specifies whether arrays of samplers or sampled images <b>can</b> be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, or VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also specifies whether shader modules <b>can</b> declare the SampledImageArrayDynamicIndexing capability.
         * <li>shaderStorageBufferArrayDynamicIndexing specifies whether arrays of storage buffers <b>can</b< be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_STORAGE_BUFFER or VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also specifies whether shader modules <b>can</b> declare the StorageBufferArrayDynamicIndexing capability.
         * <li>shaderStorageImageArrayDynamicIndexing specifies whether arrays of storage images <b>can</b> be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_STORAGE_IMAGE <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also specifies whether shader modules <b>can</b> declare the StorageImageArrayDynamicIndexing capability.
         * <li>shaderClipDistance specifies whether clip distances are supported in shader code. If this feature is not enabled, any members decorated with the ClipDistance built-in decoration <b>must</b> not be read from or written to in shader modules. This also specifies whether shader modules <b>can</b> declare the ClipDistance capability.
         * <li>shaderCullDistance specifies whether cull distances are supported in shader code. If this feature is not enabled, any members decorated with the CullDistance built-in decoration <b>must</b> not be read from or written to in shader modules. This also specifies whether shader modules <b>can</b> declare the CullDistance capability.
         * <li>shaderFloat64 specifies whether 64-bit floats (doubles) are supported in shader code. If this feature is not enabled, 64-bit floating-point types <b>must</b> not be used in shader code. This also specifies whether shader modules <b>can</b> declare the Float64 capability. Declaring and using 64-bit floats is enabled for all storage classes that SPIR-V allows with the Float64 capability.
         * <li>shaderInt64 specifies whether 64-bit integers (signed and unsigned) are supported in shader code. If this feature is not enabled, 64-bit integer types <b>must</b> not be used in shader code. This also specifies whether shader modules <b>can</b> declare the Int64 capability. Declaring and using 64-bit integers is enabled for all storage classes that SPIR-V allows with the Int64 capability.
         * <li>shaderInt16 specifies whether 16-bit integers (signed and unsigned) are supported in shader code. If this feature is not enabled, 16-bit integer types <b>must</b> not be used in shader code. This also specifies whether shader modules <b>can</b> declare the Int16 capability. However, this only enables a subset of the storage classes that SPIR-V allows for the Int16 SPIR-V capability: Declaring and using 16-bit integers in the Private, Workgroup (for non-Block variables), and Function storage classes is enabled, while declaring them in the interface storage classes (e.g., UniformConstant, Uniform, StorageBuffer, Input, Output, and PushConstant) is not enabled.
         * <li>shaderResourceResidency specifies whether image operations that return resource residency information are supported in shader code. If this feature is not enabled, the OpImageSparse* instructions <b>must</b> not be used in shader code. This also specifies whether shader modules <b>can</b> declare the SparseResidency capability. The feature requires at least one of the sparseResidency* features to be supported.
         * <li>shaderResourceMinLod specifies whether image operations specifying the minimum resource LOD are supported in shader code. If this feature is not enabled, the MinLod image operand <b>must</b> not be used in shader code. This also specifies whether shader modules <b>can</b> declare the MinLod capability.
         * <li>sparseBinding specifies whether resource memory <b>can</b> be managed at opaque sparse block level instead of at the object level. If this feature is not enabled, resource memory <b>must</b> be bound only on a per-object basis using the vkBindBufferMemory and vkBindImageMemory commands. In this case, buffers and images <b>must</b> not be created with VK_BUFFER_CREATE_SPARSE_BINDING_BIT and VK_IMAGE_CREATE_SPARSE_BINDING_BIT set in the flags member of the VkBufferCreateInfo and VkImageCreateInfo structures, respectively. Otherwise resource memory <b>can</b> be managed as described in Sparse Resource Features.
         * <li>sparseResidencyBuffer specifies whether the device <b>can</b> access partially resident buffers. If this feature is not enabled, buffers <b>must</b> not be created with VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkBufferCreateInfo structure.
         * <li>sparseResidencyImage2D specifies whether the device <b>can</b> access partially resident 2D images with 1 sample per pixel. If this feature is not enabled, images with an imageType of VK_IMAGE_TYPE_2D and samples set to VK_SAMPLE_COUNT_1_BIT <b>must</b> not be created with VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkImageCreateInfo structure.
         * <li>sparseResidencyImage3D specifies whether the device <b>can</b> access partially resident 3D images. If this feature is not enabled, images with an imageType of VK_IMAGE_TYPE_3D <b>must</b> not be created with VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkImageCreateInfo structure.
         * <li>sparseResidency2Samples specifies whether the physical device <b>can</b> access partially resident 2D images with 2 samples per pixel. If this feature is not enabled, images with an imageType of VK_IMAGE_TYPE_2D and samples set to VK_SAMPLE_COUNT_2_BIT <b>must</b> not be created with VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkImageCreateInfo structure.
         * <li>sparseResidency4Samples specifies whether the physical device <b>can</b> access partially resident 2D images with 4 samples per pixel. If this feature is not enabled, images with an imageType of VK_IMAGE_TYPE_2D and samples set to VK_SAMPLE_COUNT_4_BIT <b>must</b> not be created with VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkImageCreateInfo structure.
         * <li>sparseResidency8Samples specifies whether the physical device <b>can</b> access partially resident 2D images with 8 samples per pixel. If this feature is not enabled, images with an imageType of VK_IMAGE_TYPE_2D and samples set to VK_SAMPLE_COUNT_8_BIT <b>must</b> not be created with VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkImageCreateInfo structure.
         * <li>sparseResidency16Samples specifies whether the physical device <b>can</b> access partially resident 2D images with 16 samples per pixel. If this feature is not enabled, images with an imageType of VK_IMAGE_TYPE_2D and samples set to VK_SAMPLE_COUNT_16_BIT <b>must</b> not be created with VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT set in the flags member of the VkImageCreateInfo structure.
         * <li>sparseResidencyAliased specifies whether the physical device <b>can</b> correctly access data aliased into multiple locations. If this feature is not enabled, the VK_BUFFER_CREATE_SPARSE_ALIASED_BIT and VK_IMAGE_CREATE_SPARSE_ALIASED_BIT enum values <b>must</b> not be used in flags members of the VkBufferCreateInfo and VkImageCreateInfo structures, respectively.
         * <li>variableMultisampleRate specifies whether all pipelines that will be bound to a command buffer during a subpass which uses no attachments <b>must</b> have the same value for VkPipelineMultisampleStateCreateInfo::rasterizationSamples. If set to VK_TRUE, the implementation supports variable multisample rates in a subpass which uses no attachments. If set to VK_FALSE, then all pipelines bound in such a subpass <b>must</b> have the same multisample rate. This has no effect in situations where a subpass uses any attachments.
         * <li>inheritedQueries specifies whether a secondary command buffer <b>may</b> be executed while a query is active.
         * </ul>
         */
        using PhysicalDeviceFeatures = VkPhysicalDeviceFeatures;
        VULKANPP_CONSTEXPR PhysicalDeviceFeatures createPhysicalDeviceFeatures(
                const Bool32 values[55]
        ) {
                return {
                        values[0],  values[1],  values[2],  values[3],  values[4],
                        values[5],  values[6],  values[7],  values[8],  values[9],
                        values[10], values[11], values[12], values[13], values[14],
                        values[15], values[6],  values[17], values[18], values[19],
                        values[20], values[21], values[22], values[23], values[24],
                        values[25], values[26], values[27], values[28], values[29],
                        values[30], values[31], values[32], values[33], values[34],
                        values[35], values[36], values[37], values[38], values[39],
                        values[40], values[1],  values[42], values[43], values[44],
                        values[45], values[46], values[47], values[48], values[49],
                        values[50], values[51], values[52], values[53], values[54]
                };
        }

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
        using Device = VkDevice;
        Device createDevice(
                const PhysicalDevice                   &physicalDevice,
                const std::vector<uint32_t>            &queueFamilyIndices,
                const std::vector<const char *>        &enabledExtensionNames,
                const PhysicalDeviceFeatures           *pEnabledFeatures,
                const VkAllocationCallbacks            *pAllocator,
                const void                             *pCreateInfoNext = nullptr
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
        using CommandPool = VkCommandPool;
        CommandPool createCommandPool(
                const uint32_t                     &queueFamilyIndex,
                const Device                       &device,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
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
        using CommandBuffer = VkCommandBuffer;
        CommandBuffer createCommandBuffer(
                const CommandPool          &commandPool,
                const Device               &device,
                const void                 *pAllocInfoNext = nullptr
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
        using Buffer = VkBuffer;
        Buffer createBuffer(
                const Device                       &device,
                const DeviceSize                   &size,
                const VkBufferUsageFlags           &usage,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkBufferView - Opaque handle to a buffer view object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A buffer view represents a contiguous range of a buffer and a specific format to be used to interpret the data. Buffer views are used to enable shaders to access buffer contents using image operations. In order to create a valid buffer view, the buffer <b>must</b> have been created with at least one of the following usage flags:
         * <ul>
         * <li>VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT
         * <li>VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT
         * </ul>
         * Buffer views are represented by VkBufferView handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferView)
         * @endcode
         */
        using BufferView = VkBufferView;
        BufferView createBufferView(
                const Device                       &device,
                const Buffer                       &buffer,
                const Format                       &format,
                const DeviceSize                   &offset,
                const DeviceSize                   &range,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
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
        using DescriptorPool = VkDescriptorPool;
        DescriptorPool createDescriptorPool(
                const Device                                 &device,
                const uint32_t                               &descriptorCount,
                const std::vector<DescriptorPoolSize>        &poolSizes,
                const VkAllocationCallbacks                  *pAllocator,
                const void                                   *pCreateInfoNext = nullptr
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
        using DescriptorSetLayout = VkDescriptorSetLayout;
        DescriptorSetLayout createDescriptorSetLayout(
                const Device                                           &device,
                const std::vector<VkDescriptorSetLayoutBinding>        &bindings,
                const VkAllocationCallbacks                            *pAllocator,
                const void                                             *pCreateInfoNext = nullptr
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
        using DescriptorSet = VkDescriptorSet;
        std::vector<DescriptorSet> createDescriptorSets(
                const Device                                  &device,
                const DescriptorPool                          &pool,
                const std::vector<DescriptorSetLayout>        &descriptorSetLayouts,
                const void                                    *pAllocInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkDeviceMemory - Opaque handle to a device memory object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A Vulkan device operates on data in device memory via memory objects that are represented in the API by a VkDeviceMemory handle:<br><br>
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeviceMemory)
         * @endcode
         */
        using DeviceMemory = VkDeviceMemory;

        /** <b>Name</b><hr><br>
         *
         * VkDisplayKHR - Opaque handle to a display object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Displays are represented by VkDisplayKHR handles:<br><br>
         *
         * @code
         * // Provided by VK_KHR_display
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDisplayKHR)
         * @endcode
         */
        using DisplayKHR = VkDisplayKHR;
        // TODO create

        /** <b>Name</b><hr><br>
         *
         * VkDisplayModeKHR - Opaque handle to a display mode object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Display modes are represented by VkDisplayModeKHR handles:<br><br>
         *
         * @code
         * // Provided by VK_KHR_display
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDisplayModeKHR)
         * @endcode
         */
        using DisplayModeKHR = VkDisplayModeKHR;
        // TODO create

        /** <b>Name</b><hr><br>
         *
         * VkEvent - Opaque handle to an event object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Events are a synchronization primitive that <b>can</b> be used to insert a fine-grained dependency between commands submitted to the same queue, or between the host and a queue. Events <b>must</b> not be used to insert a dependency between commands submitted to different queues. Events have two states - signaled and unsignaled. An application <b>can</b> signal or unsignal an event either on the host or on the device. A device <b>can</b> be made to wait for an event to become signaled before executing further operations. No command exists to wait for an event to become signaled on the host, but the current state of an event <b>can</b> be queried.<br><br>
         *
         * Events are represented by VkEvent handles:<br><br>
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkEvent)
         * @endcode
         */
        using Event = VkEvent;
        // TODO create

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
        using Fence = VkFence;
        Fence createFence(
                const Device                       &device,
                const bool                         &signaled,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkImage - Opaque handle to an image object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Images represent multidimensional - up to 3 - arrays of data which <b>can</b> be used for various purposes (e.g. attachments, textures), by binding them to a graphics or compute pipeline via descriptor sets, or by directly specifying them as parameters to certain commands.<br><br>
         *
         * mages are represented by VkImage handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImage)
         * @endcode
         */
        using Image = VkImage;
        Image createImage(
                const Device                       &device,
                const VkImageType                  &imageType,
                const Format                       &format,
                const Extent3D                     &extent,
                const VkImageUsageFlags            &usage,
                const VkImageTiling                &tiling,
                const std::vector<uint32_t>        &queueFamilyIndices,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
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
        using ImageView = VkImageView;
        ImageView createImageView(
                const Image                        &image,
                const VkImageAspectFlags           &aspectMask,
                const Format                       &format,
                const Device                       &device,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkIndirectCommandsLayoutNV - Opaque handle to an indirect commands layout object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The device-side command generation happens through an iterative processing of an atomic sequence comprised of command tokens, which are represented by:
         *
         * @code
         * // Provided by VK_NV_device_generated_commands
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkIndirectCommandsLayoutNV)
         * @endcode
         *
         * <b>Description</b><hr><br>
         *
         * Each indirect command layout <b>must</b> have exactly one action command token and it <b>must</b> be the last token in the sequence.
         */
        using IndirectCommandsLayoutNV = VkIndirectCommandsLayoutNV;
        // TODO create

        /** <b>Name</b><hr><br>
         *
         * VkPerformanceConfigurationINTEL - Device configuration for performance queries<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Before submitting command buffers containing performance queries commands to a device queue, the application must acquire and set a performance query configuration. The configuration can be released once all command buffers containing performance query commands are not in a pending state.<br><br>
         *
         * Image views are represented by VkImageView handles:
         *
         * @code
         * // Provided by VK_INTEL_performance_query
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPerformanceConfigurationINTEL)
         * @endcode
         */
        using PerformanceConfigurationTypeINTEL = VkPerformanceConfigurationTypeINTEL;
        // TODO create

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
        using PushConstantRange = VkPushConstantRange;
        VULKANPP_CONSTEXPR PushConstantRange createPushConstantRange(
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
        using PipelineLayout = VkPipelineLayout;
        PipelineLayout createPipelineLayout(
                const Device                                  &device,
                const std::vector<DescriptorSetLayout>        &setLayouts,
                const std::vector<PushConstantRange>          &pushConstantRanges,
                const VkAllocationCallbacks                   *pAllocator,
                const void                                    *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkSurfaceKHR - Opaque handle to a surface object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Native platform surface or window objects are abstracted by surface objects, which are represented by VkSurfaceKHR handles:<br><br>
         *
         * @code
         * // Provided by VK_KHR_surface
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSurfaceKHR)
         * @endcode
         *
         * <b>Description</b><hr><br>
         * The VK_KHR_surface extension declares the VkSurfaceKHR object, and provides a function for destroying VkSurfaceKHR objects. Separate platform-specific extensions each provide a function for creating a VkSurfaceKHR object for the respective platform. From the application’s perspective this is an opaque handle, just like the handles of other Vulkan objects.
         *
         * @note On certain platforms, the Vulkan loader and ICDs <b>may</b> have conventions that treat the handle as a pointer to a structure containing the platform-specific information about the surface. This will be described in the documentation for the loader-ICD interface, and in the vk_icd.h header file of the LoaderAndTools source-code repository. This does not affect the loader-layer interface; layers <b>may</b> wrap VkSurfaceKHR objects.
         */
        using SurfaceKHR = VkSurfaceKHR;

        /** <b>Name</b><hr><br>
         *
         * VkSurfaceFormatKHR - Structure describing a supported swapchain format-color space pair<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSurfaceFormatKHR structure is defined as:
         *
         * @code
         * // Provided by VK_KHR_surface
         * typedef struct VkSurfaceFormatKHR {
         *     VkFormat           format;
         *     VkColorSpaceKHR    colorSpace;
         * } VkSurfaceFormatKHR;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>format is a VkFormat that is compatible with the specified surface.
         * <li>colorSpace is a presentation VkColorSpaceKHR that is compatible with the surface.
         * </ul><br>
         */
        using SurfaceFormatKHR = VkSurfaceFormatKHR;
        std::vector<SurfaceFormatKHR> getSurfaceFormatKHRs(
                const PhysicalDevice        &physicalDevice,
                const SurfaceKHR            &surface
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
        using AttachmentReference = VkAttachmentReference;
        VULKANPP_CONSTEXPR AttachmentReference createAttachmentReference(
                const uint32_t             &attachment,
                const VkImageLayout        &layout
        ) {
                return {
                        .attachment = attachment,
                        .layout = layout
                };
        }

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
        using AttachmentDescription = VkAttachmentDescription;
        VULKANPP_CONSTEXPR AttachmentDescription createAttachmentDescription(
                const Format               &format,
                const VkImageLayout        &finalLayout
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
                        .finalLayout = finalLayout
                };
        }

        // TODO doc
        using SubpassDependency = VkSubpassDependency;
        VULKANPP_CONSTEXPR SubpassDependency createSubpassDependency(
                const VkPipelineStageFlags        &stageMask,
                const VkAccessFlags               &dstAccessMask
        ) {
                return {
                        .srcSubpass = VK_SUBPASS_EXTERNAL,
                        .dstSubpass = 0,
                        .srcStageMask = stageMask,
                        .dstStageMask = stageMask,
                        .srcAccessMask = VK_ACCESS_NONE,
                        .dstAccessMask = dstAccessMask,
                        .dependencyFlags = VkDependencyFlags()
                };
        }

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
        using SubpassDescription = VkSubpassDescription;
        VULKANPP_CONSTEXPR SubpassDescription createSubpassDescription(
                const std::vector<AttachmentReference>        &inputAttachments,
                const std::vector<AttachmentReference>        &colorAttachments,
                const std::vector<AttachmentReference>        &resolveAttachments,
                const AttachmentReference                     *pDepthStencilAttachment,
                const std::vector<uint32_t>                   &preserveAttachments
        ) {
                return {
                        .flags = VkSubpassDescriptionFlags(),
                        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                        .inputAttachmentCount = static_cast<uint32_t>(inputAttachments.size()),
                        .pInputAttachments = inputAttachments.data(),
                        .colorAttachmentCount = static_cast<uint32_t>(colorAttachments.size()),
                        .pColorAttachments = colorAttachments.data(),
                        .pResolveAttachments = resolveAttachments.data(),
                        .pDepthStencilAttachment = pDepthStencilAttachment,
                        .preserveAttachmentCount = static_cast<uint32_t>(preserveAttachments.size()),
                        .pPreserveAttachments = preserveAttachments.data()
                };
        }

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
        using RenderPass = VkRenderPass;
        RenderPass createRenderPass(
                const Device                                    &device,
                const std::vector<SubpassDescription>           &subpassDescriptions,
                const std::vector<AttachmentDescription>        &attachmentDescriptions,
                const std::vector<SubpassDependency>            &dependencies,
                const VkAllocationCallbacks                     *pAllocator,
                const void                                      *pCreateInfoNext = nullptr
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
        using Framebuffer = VkFramebuffer;
        Framebuffer createFramebuffer(
                const RenderPass                    &renderPass,
                const Extent2D                      &extent,
                const std::vector<ImageView>        &attachments,
                const Device                        &device,
                const VkAllocationCallbacks         *pAllocator,
                const void                          *pCreateInfoNext = nullptr
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
        using VertexInputAttributeDescription = VkVertexInputAttributeDescription;
        VULKANPP_CONSTEXPR VertexInputAttributeDescription createVertexInputAttributeDescription(
                const uint32_t        &location,
                const uint32_t        &binding,
                const Format          &format,
                const uint32_t        &offset
        ) {
                return {
                        .location = location,
                        .binding = binding,
                        .format = format,
                        .offset = offset
                };
        }

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
        using VertexInputBindingDescription = VkVertexInputBindingDescription;
        VULKANPP_CONSTEXPR VertexInputBindingDescription createVertexInputBindingDescription(
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
        using ShaderModule = VkShaderModule;
        ShaderModule createShaderModule(
                const std::vector<uint8_t>         &code,
                const Device                       &device,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
        );

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
        using PipelineShaderStageCreateInfo = VkPipelineShaderStageCreateInfo;
        VULKANPP_CONSTEXPR PipelineShaderStageCreateInfo createPipelineShaderStageCreateInfo(
                const VkShaderStageFlagBits        &stage,
                const ShaderModule                 &module,
                const void                         *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineShaderStageCreateFlags(),
                        .stage = stage,
                        .module = module,
                        .pName = "main",
                        .pSpecializationInfo = nullptr
                };
        }

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
        using Pipeline = VkPipeline;
        Pipeline createPipeline(
                const Device                                              &device,
                const RenderPass                                          &renderPass,
                const std::vector<Viewport>                               &viewports,
                const std::vector<Rect2D>                                 &scissors,
                const PipelineLayout                                      &layout,
                const std::vector<PipelineShaderStageCreateInfo>          &shaderStages,
                const std::vector<VertexInputBindingDescription>          &bindingDescriptions,
                const std::vector<VertexInputAttributeDescription>        &attributeDescriptions,
                const VkAllocationCallbacks                               *pAllocator,
                const void                                                *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkPipelineCache - Opaque handle to a pipeline cache object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Pipeline cache objects allow the result of pipeline construction to be reused between pipelines and between runs of an application. Reuse between pipelines is achieved by passing the same pipeline cache object when creating multiple related pipelines. Reuse across runs of an application is achieved by retrieving pipeline cache contents in one run of an application, saving the contents, and using them to preinitialize a pipeline cache on a subsequent run. The contents of the pipeline cache objects are managed by the implementation. Applications <b>can</b> manage the host memory consumed by a pipeline cache object and control the amount of data retrieved from a pipeline cache object.<br><br>
         *
         * Pipeline cache objects are represented by VkPipelineCache handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineCache)
         * @endcode
         */
        using PipelineCache = VkPipelineCache;
        // TODO create

        /** <b>Name</b><hr><br>
         *
         * VkQueryPool - Opaque handle to a query pool object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Queries are managed using query pool objects. Each query pool is a collection of a specific number of queries of a particular type.<br><br>
         *
         * Query pools are represented by VkQueryPool handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkQueryPool)
         * @endcode
         */
        using QueryPool = VkQueryPool;
        // TODO create

        /** <b>Name</b><hr><br>
         *
         * VkQueue - Opaque handle to a queue object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Creating a logical device also creates the queues associated with that device. The queues to create are described by a set of VkDeviceQueueCreateInfo structures that are passed to vkCreateDevice in pQueueCreateInfos.<br><br>
         *
         * Queues are represented by VkQueue handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_HANDLE(VkQueue)
         * @endcode
         */
        using Queue = VkQueue;
        Queue getQueue(
                const Device          &device,
                const uint32_t        &queueFamilyIndex,
                const uint32_t        &queueIndex
        );

        /** <b>Name</b><hr><br>
         *
         * VkSampler - Opaque handle to a sampler object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * VkSampler objects represent the state of an image sampler which is used by the implementation to read image data and apply filtering and other transformations for the shader.<br><br>
         *
         * Samplers are represented by VkSampler handles:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSampler)
         * @endcode
         */
        using Sampler = VkSampler;
        Sampler createSampler(
                const Device                      &device,
                const VkFilter                    &filter,
                const VkSamplerAddressMode        &addressMode,
                const Bool32                      &anisotropyEnable,
                const float                       &maxAnisotropy,
                const Bool32                      &compareEnable,
                const VkCompareOp                 &compareOp,
                const void                        *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkSamplerYcbcrConversion - Opaque handle to a device-specific sampler Y′CBCR conversion description<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A sampler Y′CBCR conversion is an opaque representation of a device-specific sampler Y′CBCR conversion description, represented as a VkSamplerYcbcrConversion handle:
         *
         * @code
         * // Provided by VK_VERSION_1_1
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSamplerYcbcrConversion)
         * @endcode
         *
         * or the equivalent
         *
         * @code
         * // Provided by VK_KHR_sampler_ycbcr_conversion
         * typedef VkSamplerYcbcrConversion VkSamplerYcbcrConversionKHR;
         * @endcode
         */
        using SamplerYcbcrConversion = VkSamplerYcbcrConversion;
        // TODO create

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
        using Semaphore = VkSemaphore;
        Semaphore createSemaphore(
                const Device                       &device,
                const VkAllocationCallbacks        *pAllocator,
                const void                         *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkPresentModeKHR - Presentation mode supported for a surface<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Possible values of elements of the vkGetPhysicalDeviceSurfacePresentModesKHR::pPresentModes array, indicating the supported presentation modes for a surface, are:
         *
         * @code
         * // Provided by VK_KHR_surface
         * typedef enum VkPresentModeKHR {
         *     VK_PRESENT_MODE_IMMEDIATE_KHR = 0,
         *     VK_PRESENT_MODE_MAILBOX_KHR = 1,
         *     VK_PRESENT_MODE_FIFO_KHR = 2,
         *     VK_PRESENT_MODE_FIFO_RELAXED_KHR = 3,
         *   // Provided by VK_KHR_shared_presentable_image
         *     VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR = 1000111000,
         *   // Provided by VK_KHR_shared_presentable_image
         *     VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR = 1000111001,
         * } VkPresentModeKHR;
         * @endcode
         *
         * <b>Description</b><hr><br>
         * <ul>
         * <li>VK_PRESENT_MODE_IMMEDIATE_KHR specifies that the presentation engine does not wait for a vertical blanking period to update the current image, meaning this mode <b>may</b> result in visible tearing. No internal queuing of presentation requests is needed, as the requests are applied immediately.
         * <li>VK_PRESENT_MODE_MAILBOX_KHR specifies that the presentation engine waits for the next vertical blanking period to update the current image. Tearing <b>cannot</b> be observed. An internal single-entry queue is used to hold pending presentation requests. If the queue is full when a new presentation request is received, the new request replaces the existing entry, and any images associated with the prior entry become available for reuse by the application. One request is removed from the queue and processed during each vertical blanking period in which the queue is non-empty.
         * <li>VK_PRESENT_MODE_FIFO_KHR specifies that the presentation engine waits for the next vertical blanking period to update the current image. Tearing <b>cannot</b> be observed. An internal queue is used to hold pending presentation requests. New requests are appended to the end of the queue, and one request is removed from the beginning of the queue and processed during each vertical blanking period in which the queue is non-empty. This is the only value of presentMode that is <b>required</b> to be supported.
         * <li>VK_PRESENT_MODE_FIFO_RELAXED_KHR specifies that the presentation engine generally waits for the next vertical blanking period to update the current image. If a vertical blanking period has already passed since the last update of the current image then the presentation engine does not wait for another vertical blanking period for the update, meaning this mode <b>may</b> result in visible tearing in this case. This mode is useful for reducing visual stutter with an application that will mostly present a new image before the next vertical blanking period, but may occasionally be late, and present a new image just after the next vertical blanking period. An internal queue is used to hold pending presentation requests. New requests are appended to the end of the queue, and one request is removed from the beginning of the queue and processed during or after each vertical blanking period in which the queue is non-empty.
         * <li>VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR specifies that the presentation engine and application have concurrent access to a single image, which is referred to as a shared presentable image. The presentation engine is only required to update the current image after a new presentation request is received. Therefore the application <b>must</b> make a presentation request whenever an update is required. However, the presentation engine <b>may</b> update the current image at any point, meaning this mode <b>may</b> result in visible tearing.
         * <li>VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR specifies that the presentation engine and application have concurrent access to a single image, which is referred to as a shared presentable image. The presentation engine periodically updates the current image on its regular refresh cycle. The application is only required to make one initial presentation request, after which the presentation engine <b>must</b> update the current image without any need for further presentation requests. The application <b>can</b> indicate the image contents have been updated by making a presentation request, but this does not guarantee the timing of when it will be updated. This mode <b>may</b> result in visible tearing if rendering to the image is not timed correctly.
         * </ul>
         * The supported VkImageUsageFlagBits of the presentable images of a swapchain created for a surface <b>may</b> differ depending on the presentation mode, and can be determined as per the table below:<br><br>
         *
         * Table 1. Presentable image usage queries
         *
         * <pre><b>  Presentation mode</b>                             | <b>Image usage flags</b></pre><
         * <pre>  VK_PRESENT_MODE_IMMEDIATE_KHR                 | VkSurfaceCapabilitiesKHR::supportedUsageFlags</pre>
         * <pre>  VK_PRESENT_MODE_MAILBOX_KHR                   | VkSurfaceCapabilitiesKHR::supportedUsageFlags</pre>
         * <pre>  VK_PRESENT_MODE_FIFO_KHR                      | VkSurfaceCapabilitiesKHR::supportedUsageFlags</pre>
         * <pre>  VK_PRESENT_MODE_FIFO_RELAXED_KHR              | VkSurfaceCapabilitiesKHR::supportedUsageFlags</pre>
         * <pre>  VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR     | VkSharedPresentSurfaceCapabilitiesKHR::sharedPresentSupportedUsageFlags</pre>
         * <pre>  VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR | VkSharedPresentSurfaceCapabilitiesKHR::sharedPresentSupportedUsageFlags</pre>
         *
         * @note For reference, the mode indicated by VK_PRESENT_MODE_FIFO_KHR is equivalent to the behavior of {wgl|glX|egl}SwapBuffers with a swap interval of 1, while the mode indicated by VK_PRESENT_MODE_FIFO_RELAXED_KHR is equivalent to the behavior of {wgl|glX}SwapBuffers with a swap interval of -1 (from the {WGL|GLX}_EXT_swap_control_tear extensions).
         */
        using PresentModeKHR = VkPresentModeKHR;
        std::vector<PresentModeKHR> getPresentModeKHR(
                const PhysicalDevice        &physicalDevice,
                const SurfaceKHR            &surface
        );

        /** <b>Name</b><hr><br>
         *
         * VkSurfaceCapabilitiesKHR - Structure describing capabilities of a surface<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSurfaceCapabilitiesKHR structure is defined as:
         *
         * @code
         * // Provided by VK_KHR_surface
         * typedef struct VkSurfaceCapabilitiesKHR {
         *     uint32_t                         minImageCount;
         *     uint32_t                         maxImageCount;
         *     VkExtent2D                       currentExtent;
         *     VkExtent2D                       minImageExtent;
         *     VkExtent2D                       maxImageExtent;
         *     uint32_t                         maxImageArrayLayers;
         *     VkSurfaceTransformFlagsKHR       supportedTransforms;
         *     VkSurfaceTransformFlagBitsKHR    currentTransform;
         *     VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
         *     VkImageUsageFlags                supportedUsageFlags;
         * } VkSurfaceCapabilitiesKHR;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>minImageCount is the minimum number of images the specified device supports for a swapchain created for the surface, and will be at least one.
         * <li>maxImageCount is the maximum number of images the specified device supports for a swapchain created for the surface, and will be either 0, or greater than or equal to minImageCount. A value of 0 means that there is no limit on the number of images, though there <b>may</b> be limits related to the total amount of memory used by presentable images.
         * <li>currentExtent is the current width and height of the surface, or the special value (0xFFFFFFFF, 0xFFFFFFFF) indicating that the surface size will be determined by the extent of a swapchain targeting the surface.
         * <li>minImageExtent contains the smallest valid swapchain extent for the surface on the specified device. The width and height of the extent will each be less than or equal to the corresponding width and height of currentExtent, unless currentExtent has the special value described above.
         * <li>maxImageExtent contains the largest valid swapchain extent for the surface on the specified device. The width and height of the extent will each be greater than or equal to the corresponding width and height of minImageExtent. The width and height of the extent will each be greater than or equal to the corresponding width and height of currentExtent, unless currentExtent has the special value described above.
         * <li>maxImageArrayLayers is the maximum number of layers presentable images <b>can</b> have for a swapchain created for this device and surface, and will be at least one.
         * <li>supportedTransforms is a bitmask of VkSurfaceTransformFlagBitsKHR indicating the presentation transforms supported for the surface on the specified device. At least one bit will be set.
         * <li>currentTransform is VkSurfaceTransformFlagBitsKHR value indicating the surface’s current transform relative to the presentation engine’s natural orientation.
         * <li>supportedCompositeAlpha is a bitmask of VkCompositeAlphaFlagBitsKHR, representing the alpha compositing modes supported by the presentation engine for the surface on the specified device, and at least one bit will be set. Opaque composition <b>can</b> be achieved in any alpha compositing mode by either using an image format that has no alpha component, or by ensuring that all pixels in the presentable images have an alpha value of 1.0.
         * <li>supportedUsageFlags is a bitmask of VkImageUsageFlagBits representing the ways the application <b>can</b> use the presentable images of a swapchain created with VkPresentModeKHR set to VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR or VK_PRESENT_MODE_FIFO_RELAXED_KHR for the surface on the specified device. VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT <b>must</b> be included in the set. Implementations may support additional usages.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note Supported usage flags of a presentable image when using VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR or VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR presentation mode are provided by VkSharedPresentSurfaceCapabilitiesKHR::sharedPresentSupportedUsageFlags.
         *
         * @note Formulas such as min(N, maxImageCount) are not correct, since maxImageCount <b>may</b> be zero.
         */
        using SurfaceCapabilitiesKHR = VkSurfaceCapabilitiesKHR;
        SurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR(
                const PhysicalDevice        &physicalDevice,
                const SurfaceKHR            &surface
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
        using SwapchainKHR = VkSwapchainKHR;
        SwapchainKHR createSwapchainKHR(
                const Device                             &device,
                const SurfaceKHR                         &surface,
                const std::vector<PresentModeKHR>        &presentModes,
                const SurfaceCapabilitiesKHR             &capabilities,
                const std::vector<uint32_t>              &queueFamilyIndices,
                const SurfaceFormatKHR                   &format,
                const Extent2D                           &extent,
                const VkAllocationCallbacks              *pAllocator,
                const void                               *pCreateInfoNext = nullptr
        );

        /** <b>Name</b><hr><br>
         *
         * VkValidationCacheEXT - Opaque handle to a validation cache object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Validation cache objects allow the result of internal validation to be reused, both within a single application run and between multiple runs. Reuse within a single run is achieved by passing the same validation cache object when creating supported Vulkan objects. Reuse across runs of an application is achieved by retrieving validation cache contents in one run of an application, saving the contents, and using them to preinitialize a validation cache on a subsequent run. The contents of the validation cache objects are managed by the validation layers. Applications <b>can</b> manage the host memory consumed by a validation cache object and control the amount of data retrieved from a validation cache object.<br><br>
         *
         * Validation cache objects are represented by VkValidationCacheEXT handles:
         *
         * @code
         * // Provided by VK_EXT_validation_cache
         * VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkValidationCacheEXT)
         * @endcode
         */
        using ValidationCacheEXT = VkValidationCacheEXT;
        // TODO create

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceProperties - Structure specifying physical device properties<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceProperties structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPhysicalDeviceProperties {
         *     uint32_t                            apiVersion;
         *     uint32_t                            driverVersion;
         *     uint32_t                            vendorID;
         *     uint32_t                            deviceID;
         *     VkPhysicalDeviceType                deviceType;
         *     char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
         *     uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
         *     VkPhysicalDeviceLimits              limits;
         *     VkPhysicalDeviceSparseProperties    sparseProperties;
         * } VkPhysicalDeviceProperties;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>apiVersion is the version of Vulkan supported by the device, encoded as described in https://registry.khronos.org/vulkan/specs/1.3-extensions/html/vkspec.html#extendingvulkan-coreversions-versionnumbers.
         * <li>driverVersion is the vendor-specified version of the driver.
         * <li>vendorID is a unique identifier for the vendor (see below) of the physical device.
         * <li>deviceID is a unique identifier for the physical device among devices available from the vendor.
         * <li>deviceType is a VkPhysicalDeviceType specifying the type of device.
         * <li>deviceName is an array of VK_MAX_PHYSICAL_DEVICE_NAME_SIZE char containing a null-terminated UTF-8 string which is the name of the device.
         * <li>pipelineCacheUUID is an array of VK_UUID_SIZE uint8_t values representing a universally unique identifier for the device.
         * <li>limits is the VkPhysicalDeviceLimits structure specifying device-specific limits of the physical device. See Limits for details.
         * <li>sparseProperties is the VkPhysicalDeviceSparseProperties structure specifying various sparse related properties of the physical device. See Sparse Properties for details.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note The value of apiVersion <b>may</b> be different than the version returned by vkEnumerateInstanceVersion; either higher or lower. In such cases, the application <b>must</b> not use functionality that exceeds the version of Vulkan associated with a given object. The pApiVersion parameter returned by vkEnumerateInstanceVersion is the version associated with a VkInstance and its children, except for a VkPhysicalDevice and its children.<br>
         * VkPhysicalDeviceProperties::apiVersion is the version associated with a VkPhysicalDevice and its children.
         *
         * @note The encoding of driverVersion is implementation-defined. It <b>may</b> not use the same encoding as apiVersion. Applications should follow information from the vendor on how to extract the version information from driverVersion.
         *
         * On implementations that claim support for the Roadmap 2022 profile, the major and minor version expressed by apiVersion <b>must</b> be at least Vulkan 1.3.<br><br>
         *
         * The vendorID and deviceID fields are provided to allow applications to adapt to device characteristics that are not adequately exposed by other Vulkan queries.
         *
         * @note These <b>may</b> include performance profiles, hardware errata, or other characteristics.
         *
         * The vendor identified by vendorID is the entity responsible for the most salient characteristics of the underlying implementation of the VkPhysicalDevice being queried.
         *
         * @note For example, in the case of a discrete GPU implementation, this <b>should</b> be the GPU chipset vendor. In the case of a hardware accelerator integrated into a system-on-chip (SoC), this <b>should</b> be the supplier of the silicon IP used to create the accelerator.
         *
         * If the vendor has a PCI vendor ID, the low 16 bits of vendorID <b>must</b> contain that PCI vendor ID, and the remaining bits <b>must</b> be set to zero. Otherwise, the value returned <b>must</b> be a valid Khronos vendor ID, obtained as described in the Vulkan Documentation and Extensions: Procedures and Conventions document in the section “Registering a Vendor ID with Khronos”. Khronos vendor IDs are allocated starting at 0x10000, to distinguish them from the PCI vendor ID namespace. Khronos vendor IDs are symbolically defined in the VkVendorId type.<br><br>
         *
         * The vendor is also responsible for the value returned in deviceID. If the implementation is driven primarily by a PCI device with a PCI device ID, the low 16 bits of deviceID <b>must</b> contain that PCI device ID, and the remaining bits <b>must</b> be set to zero. Otherwise, the choice of what values to return <b>may</b> be dictated by operating system or platform policies - but <b>should</b> uniquely identify both the device version and any major configuration options (for example, core count in the case of multicore devices).
         *
         * @note The same device ID <b>should</b> be used for all physical implementations of that device version and configuration. For example, all uses of a specific silicon IP GPU version and configuration <b>should</b> use the same device ID, even if those uses occur in different SoCs.
         */
        using PhysicalDeviceProperties = VkPhysicalDeviceProperties;
        PhysicalDeviceProperties getPhysicalDeviceProperties(
                const PhysicalDevice        &physicalDevice
        );

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceMemoryProperties - Structure specifying physical device memory properties<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceMemoryProperties structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkPhysicalDeviceMemoryProperties {
         *     uint32_t        memoryTypeCount;
         *     VkMemoryType    memoryTypes[VK_MAX_MEMORY_TYPES];
         *     uint32_t        memoryHeapCount;
         *     VkMemoryHeap    memoryHeaps[VK_MAX_MEMORY_HEAPS];
         * } VkPhysicalDeviceMemoryProperties;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>memoryTypeCount is the number of valid elements in the memoryTypes array.
         * <li>memoryTypes is an array of VK_MAX_MEMORY_TYPES VkMemoryType structures describing the memory types that <b>can</b> be used to access memory allocated from the heaps specified by memoryHeaps.
         * <li>memoryHeapCount is the number of valid elements in the memoryHeaps array.
         * <li>memoryHeaps is an array of VK_MAX_MEMORY_HEAPS VkMemoryHeap structures describing the memory heaps from which memory <b>can</b> be allocated.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The VkPhysicalDeviceMemoryProperties structure describes a number of memory heaps as well as a number of memory types that <b>can</b> be used to access memory allocated in those heaps. Each heap describes a memory resource of a particular size, and each memory type describes a set of memory properties (e.g. host cached vs. uncached) that <b>can</b> be used with a given memory heap.<br>
         * Allocations using a particular memory type will consume resources from the heap indicated by that memory type’s heap index. More than one memory type <b>may</b> share each heap, and the heaps and memory types provide a mechanism to advertise an accurate size of the physical memory resources while allowing the memory to be used with a variety of different properties.<br><br>
         *
         * The number of memory heaps is given by memoryHeapCount and is less than or equal to VK_MAX_MEMORY_HEAPS. Each heap is described by an element of the memoryHeaps array as a VkMemoryHeap structure. The number of memory types available across all memory heaps is given by memoryTypeCount and is less than or equal to VK_MAX_MEMORY_TYPES. Each memory type is described by an element of the memoryTypes array as a VkMemoryType structure.<br><br
         *
         * At least one heap <b>must</b> include VK_MEMORY_HEAP_DEVICE_LOCAL_BIT in VkMemoryHeap::flags. If there are multiple heaps that all have similar performance characteristics, they <b>may</b> all include VK_MEMORY_HEAP_DEVICE_LOCAL_BIT. In a unified memory architecture (UMA) system there is often only a single memory heap which is considered to be equally “local” to the host and to the device, and such an implementation <b>must</b> advertise the heap as device-local.<br><br>
         *
         * Each memory type returned by vkGetPhysicalDeviceMemoryProperties <b>must</b> have its propertyFlags set to one of the following values:
         * <ul>
         * <li>0
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT
         * <li>VK_MEMORY_PROPERTY_PROTECTED_BIT
         * <li>VK_MEMORY_PROPERTY_PROTECTED_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
         * <li>VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV
         * </ul>
         * There <b>must</b> be at least one memory type with both the VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT and VK_MEMORY_PROPERTY_HOST_COHERENT_BIT bits set in its propertyFlags. There <b>must</b> be at least one memory type with the VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT bit set in its propertyFlags. If the deviceCoherentMemory feature is enabled, there <b>must</b> be at least one memory type with the VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD bit set in its propertyFlags.<br><br>
         *
         * For each pair of elements <b>X</b> and <b>Y</b> returned in memoryTypes, <b>X must</b> be placed at a lower index position than <b>Y</b> if:
         * <ul>
         * <li>the set of bit flags returned in the propertyFlags member of <b>X</b> is a strict subset of the set of bit flags returned in the propertyFlags member of <b>Y</b>; or
         * <li>the propertyFlags members of <b>X</b> and <b>Y</b> are equal, and <b>X</b> belongs to a memory heap with greater performance (as determined in an implementation-specific manner) ; or
         * <li>the propertyFlags members of <b>Y</b> includes VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD or VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD and <b>X</b> does not
         * </ul>
         * @note There is no ordering requirement between <b>X</b> and <b>Y</b> elements for the case their propertyFlags members are not in a subset relation. That potentially allows more than one possible way to order the same set of memory types. Notice that the list of all allowed memory property flag combinations is written in a valid order. But if instead VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT was before VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, the list would still be in a valid order.<br><br>
         * There may be a performance penalty for using device coherent or uncached device memory types, and using these accidentally is undesirable. In order to avoid this, memory types with these properties always appear at the end of the list; but are subject to the same rules otherwise.<br><br>
         *
         * This ordering requirement enables applications to use a simple search loop to select the desired memory type along the lines of:
         * @code
         * // Find a memory in `memoryTypeBitsRequirement` that includes all of `requiredProperties`
         * int32_t findProperties(const VkPhysicalDeviceMemoryProperties* pMemoryProperties,
         *                       uint32_t memoryTypeBitsRequirement,
         *                       VkMemoryPropertyFlags requiredProperties) {
         *     const uint32_t memoryCount = pMemoryProperties->memoryTypeCount;
         *     for (uint32_t memoryIndex = 0; memoryIndex < memoryCount; ++memoryIndex) {
         *         const uint32_t memoryTypeBits = (1 << memoryIndex);
         *         const bool isRequiredMemoryType = memoryTypeBitsRequirement & memoryTypeBits;
         *
         *         const VkMemoryPropertyFlags properties =
         *             pMemoryProperties->memoryTypes[memoryIndex].propertyFlags;
         *         const bool hasRequiredProperties =
         *             (properties & requiredProperties) == requiredProperties;
         *
         *         if (isRequiredMemoryType && hasRequiredProperties)
         *             return static_cast<int32_t>(memoryIndex);
         *     }
         *
         *     // failed to find memory type
         *     return -1;
         * }
         *
         * // Try to find an optimal memory type, or if it does not exist try fallback memory type
         * // `device` is the VkDevice
         * // `image` is the VkImage that requires memory to be bound
         * // `memoryProperties` properties as returned by vkGetPhysicalDeviceMemoryProperties
         * // `requiredProperties` are the property flags that must be present
         * // `optimalProperties` are the property flags that are preferred by the application
         * VkMemoryRequirements memoryRequirements;
         * vkGetImageMemoryRequirements(device, image, &memoryRequirements);
         * int32_t memoryType =
         *     findProperties(&memoryProperties, memoryRequirements.memoryTypeBits, optimalProperties);
         * if (memoryType == -1) // not found; try fallback properties
         *     memoryType =
         *         findProperties(&memoryProperties, memoryRequirements.memoryTypeBits, requiredProperties);
         * @endcode
         */
        using PhysicalDeviceMemoryProperties = VkPhysicalDeviceMemoryProperties;
        PhysicalDeviceMemoryProperties getPhysicalDeviceMemoryProperties(
                const PhysicalDevice        &physicalDevice
        );

        /** <b>Name</b><hr><br>
         *
         * VkAccelerationStructureInfoNV - Structure specifying the parameters of acceleration structure object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkAccelerationStructureInfoNV structure is defined as:
         *
         * @code
         * // Provided by VK_NV_ray_tracing
         * typedef struct VkAccelerationStructureInfoNV {
         *     VkStructureType                        sType;
         *     const void*                            pNext;
         *     VkAccelerationStructureTypeNV          type;
         *     VkBuildAccelerationStructureFlagsNV    flags;
         *     uint32_t                               instanceCount;
         *     uint32_t                               geometryCount;
         *     const VkGeometryNV*                    pGeometries;
         * } VkAccelerationStructureInfoNV;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>type is a VkAccelerationStructureTypeNV value specifying the type of acceleration structure that will be created.
         * <li>flags is a bitmask of VkBuildAccelerationStructureFlagBitsNV specifying additional parameters of the acceleration structure.
         * <li>instanceCount specifies the number of instances that will be in the new acceleration structure.
         * <li>geometryCount specifies the number of geometries that will be in the new acceleration structure.
         * <li>pGeometries is a pointer to an array of geometryCount VkGeometryNV structures containing the scene data being passed into the acceleration structure.
         * </ul>
         * <b>Description</b><hr><br>
         *
         * VkAccelerationStructureInfoNV contains information that is used both for acceleration structure creation with vkCreateAccelerationStructureNV and in combination with the actual geometric data to build the acceleration structure with vkCmdBuildAccelerationStructureNV.
         */
        using AccelerationStructureInfoNV = VkAccelerationStructureInfoNV;
        VULKANPP_CONSTEXPR AccelerationStructureInfoNV createAccelerationStructureInfoNV(
                const VkAccelerationStructureTypeNV              &type,
                const uint32_t                                   &instanceCount,
                const std::vector<VkGeometryNV>                  &geometries,
                const void                                       *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV,
                        .pNext = pNext,
                        .type = type,
                        .flags = VkBuildAccelerationStructureFlagsNV(),
                        .instanceCount = instanceCount,
                        .geometryCount = static_cast<uint32_t>(geometries.size()),
                        .pGeometries = geometries.data()
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkAccelerationStructureCreateInfoNV - Structure specifying the parameters of a newly created acceleration structure object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkAccelerationStructureCreateInfoNV structure is defined as:
         *
         * @code
         * // Provided by VK_NV_ray_tracing
         * typedef struct VkAccelerationStructureCreateInfoNV {
         *     VkStructureType                  sType;
         *     const void*                      pNext;
         *     VkDeviceSize                     compactedSize;
         *     VkAccelerationStructureInfoNV    info;
         * } VkAccelerationStructureCreateInfoNV;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>compactedSize is the size from the result of vkCmdWriteAccelerationStructuresPropertiesNV if this acceleration structure is going to be the target of a compacting copy.
         * <li>info is the VkAccelerationStructureInfoNV structure specifying further parameters of the created acceleration structure.
         * </ul>
         */
        using AccelerationStructureCreateInfoNV = VkAccelerationStructureCreateInfoNV;
        VULKANPP_CONSTEXPR AccelerationStructureCreateInfoNV createAccelerationStructureCreateInfoNV(
                const DeviceSize                           &compactedSize,
                const AccelerationStructureInfoNV          &info,
                const void                                 *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV,
                        .pNext = pNext,
                        .compactedSize = compactedSize,
                        .info = info
                };
        }

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
        using ApplicationInfo = VkApplicationInfo;
        VULKANPP_CONSTEXPR ApplicationInfo createApplicationInfo(
                const char            *pApplicationName,
                const uint32_t        &applicationVersion,
                const uint32_t        &apiVersion,
                const void            *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                        .pNext = pNext,
                        .pApplicationName = pApplicationName,
                        .applicationVersion = applicationVersion,
                        .pEngineName = "Vulkan Engine",
                        .engineVersion = 1,
                        .apiVersion = apiVersion
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkBufferViewCreateInfo - Structure specifying parameters of a newly created buffer view<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkBufferViewCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkBufferViewCreateInfo {
         *     VkStructureType            sType;
         *     const void*                pNext;
         *     VkBufferViewCreateFlags    flags;
         *     VkBuffer                   buffer;
         *     VkFormat                   format;
         *     VkDeviceSize               offset;
         *     VkDeviceSize               range;
         * } VkBufferViewCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is reserved for future use.
         * <li>buffer is a VkBuffer on which the view will be created.
         * <li>format is a VkFormat describing the format of the data elements in the buffer.
         * <li>offset is an offset in bytes from the base address of the buffer. Accesses to the buffer view from shaders use addressing that is relative to this starting offset.
         * <li>range is a size in bytes of the buffer view. If range is equal to VK_WHOLE_SIZE, the range from offset to the end of the buffer is used. If VK_WHOLE_SIZE is used and the remaining size of the buffer is not a multiple of the texel block size of format, the nearest smaller multiple is used.
         * </ul>
         * <b>Description</b><hr><br>
         *
         * The buffer view has a buffer view usage identifying which descriptor types <b>can</b> be created from it. This usage can be defined by including the VkBufferUsageFlags2CreateInfoKHR structure in the pNext chain, and specifying the usage value there. If this structure is not included, it is equal to the VkBufferCreateInfo::usage value used to create buffer.
         */
        using BufferViewCreateInfo = VkBufferViewCreateInfo;
        VULKANPP_CONSTEXPR BufferViewCreateInfo createBufferViewCreateInfo(
                const Buffer            &buffer,
                const Format            &format,
                const DeviceSize        &offset,
                const DeviceSize        &range,
                const void              *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkBufferViewCreateFlags(),
                        .buffer = buffer,
                        .format = format,
                        .offset = offset,
                        .range = range
                };
        }

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
        using PipelineVertexInputStateCreateInfo = VkPipelineVertexInputStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineVertexInputStateCreateInfo createPipelineVertexInputStateCreateInfo(
                const std::vector<VertexInputBindingDescription>          &bindingDescriptions,
                const std::vector<VertexInputAttributeDescription>        &attributeDescriptions,
                const void                                                *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineVertexInputStateCreateFlags(),
                        .vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size()),
                        .pVertexBindingDescriptions = bindingDescriptions.data(),
                        .vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size()),
                        .pVertexAttributeDescriptions = attributeDescriptions.data()
                };
        }

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
        using PipelineInputAssemblyStateCreateInfo = VkPipelineInputAssemblyStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineInputAssemblyStateCreateInfo createPipelineInputAssemblyStateCreateInfo(
                const void        *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineInputAssemblyStateCreateFlags(),
                        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                        .primitiveRestartEnable = VK_FALSE
                };
        }

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
        using PipelineViewportStateCreateInfo = VkPipelineViewportStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineViewportStateCreateInfo createPipelineViewportStateCreateInfo(
                const std::vector<Viewport>        &viewports,
                const std::vector<Rect2D>          &scissors,
                const void                         *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineViewportStateCreateFlags(),
                        .viewportCount = static_cast<uint32_t>(viewports.size()),
                        .pViewports = viewports.data(),
                        .scissorCount = static_cast<uint32_t>(scissors.size()),
                        .pScissors = scissors.data()
                };
        }

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
        using PipelineRasterizationStateCreateInfo = VkPipelineRasterizationStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineRasterizationStateCreateInfo createPipelineRasterizationStateCreateInfo(
                const void        *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                        .pNext = pNext,
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
        using PipelineMultisampleStateCreateInfo = VkPipelineMultisampleStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineMultisampleStateCreateInfo createPipelineMultisampleStateCreateInfo(
                const void        *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineMultisampleStateCreateFlags(),
                        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
                        .sampleShadingEnable = VK_FALSE,
                        .minSampleShading = 0.0f,
                        .pSampleMask = nullptr,
                        .alphaToCoverageEnable = VK_FALSE,
                        .alphaToOneEnable = VK_FALSE
                };
        }

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
        using PipelineColorBlendAttachmentState = VkPipelineColorBlendAttachmentState;
        VULKANPP_CONSTEXPR PipelineColorBlendAttachmentState createPipelineColorBlendAttachmentState()
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
        using PipelineColorBlendStateCreateInfo = VkPipelineColorBlendStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineColorBlendStateCreateInfo createPipelineColorBlendStateCreateInfo(
                const std::vector<PipelineColorBlendAttachmentState>        &attachments,
                const void                                                  *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineColorBlendStateCreateFlags(),
                        .logicOpEnable = VK_FALSE,
                        .logicOp = VK_LOGIC_OP_COPY,
                        .attachmentCount = static_cast<uint32_t>(attachments.size()),
                        .pAttachments = attachments.data(),
                        .blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}
                };
        }

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
        using CommandBufferBeginInfo = VkCommandBufferBeginInfo;
        VULKANPP_CONSTEXPR CommandBufferBeginInfo createCommandBufferBeginInfo(
                const VkCommandBufferUsageFlags        &flags,
                const void                             *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                        .pNext = pNext,
                        .flags = flags,
                        .pInheritanceInfo = nullptr
                };
        }

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
        using RenderPassBeginInfo = VkRenderPassBeginInfo;
        VULKANPP_CONSTEXPR RenderPassBeginInfo createRenderPassBeginInfo(
                const RenderPass                     &renderPass,
                const Framebuffer                    &framebuffer,
                const Extent2D                       &extent,
                const std::vector<ClearValue>        &clearValues,
                const void                           *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                        .pNext = pNext,
                        .renderPass = renderPass,
                        .framebuffer = framebuffer,
                        .renderArea = vk::createRect2D(
                                vk::createOffset2D(0, 0), extent
                        ),
                        .clearValueCount = static_cast<uint32_t>(clearValues.size()),
                        .pClearValues = clearValues.data()
                };
        }

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
        using SubmitInfo = VkSubmitInfo;
        VULKANPP_CONSTEXPR SubmitInfo createSubmitInfo(
                const std::vector<Semaphore>            &waitSemaphores,
                const VkPipelineStageFlags              *pWaitDstStageMask,
                const std::vector<CommandBuffer>        &commandBuffers,
                const std::vector<Semaphore>            &signalSemaphores,
                const void                              *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                        .pNext = pNext,
                        .waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
                        .pWaitSemaphores = waitSemaphores.data(),
                        .pWaitDstStageMask = pWaitDstStageMask,
                        .commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
                        .pCommandBuffers = commandBuffers.data(),
                        .signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size()),
                        .pSignalSemaphores = signalSemaphores.data()
                };
        }

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
        using PresentInfoKHR = VkPresentInfoKHR;
        VULKANPP_CONSTEXPR PresentInfoKHR createPresentInfoKHR(
                const std::vector<Semaphore>          &waitSemaphores,
                const std::vector<SwapchainKHR>       &swapchains,
                const std::vector<uint32_t>           &imageIndices,
                const void                            *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                        .pNext = pNext,
                        .waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
                        .pWaitSemaphores = waitSemaphores.data(),
                        .swapchainCount = static_cast<uint32_t>(swapchains.size()),
                        .pSwapchains = swapchains.data(),
                        .pImageIndices = imageIndices.data(),
                        .pResults = nullptr
                };
        }

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
        using MemoryAllocateInfo = VkMemoryAllocateInfo;
        VULKANPP_CONSTEXPR MemoryAllocateInfo createMemoryAllocateInfo(
                const DeviceSize        &allocationSize,
                const uint32_t          &memoryTypeIndex,
                const void              *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                        .pNext = pNext,
                        .allocationSize = allocationSize,
                        .memoryTypeIndex = memoryTypeIndex
                };
        }

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
        using BufferCopy = VkBufferCopy;
        VULKANPP_CONSTEXPR BufferCopy createBufferCopy(
                const DeviceSize        &size
        ) {
                return {
                        .srcOffset = 0,
                        .dstOffset = 0,
                        .size = size
                };
        }

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
        using BufferCreateInfo = VkBufferCreateInfo;
        VULKANPP_CONSTEXPR BufferCreateInfo createBufferCreateInfo(
                const DeviceSize                &size,
                const VkBufferUsageFlags        &usage,
                const void                      *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkBufferCreateFlags(),
                        .size = size,
                        .usage = usage,
                        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                        .queueFamilyIndexCount = 0,
                        .pQueueFamilyIndices = nullptr
                };
        }

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
        using CommandBufferAllocateInfo = VkCommandBufferAllocateInfo;
        VULKANPP_CONSTEXPR CommandBufferAllocateInfo createCommandBufferAllocateInfo(
                const CommandPool        &commandPool,
                const void               *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                        .pNext = pNext,
                        .commandPool = commandPool,
                        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                        .commandBufferCount = 1
                };
        }

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
        using CommandPoolCreateInfo = VkCommandPoolCreateInfo;
        VULKANPP_CONSTEXPR CommandPoolCreateInfo createCommandPoolCreateInfo(
                const uint32_t        &queueFamilyIndex,
                const void            *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                        .queueFamilyIndex = queueFamilyIndex
                };
        }

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
        using DeviceQueueCreateInfo = VkDeviceQueueCreateInfo;
        VULKANPP_CONSTEXPR DeviceQueueCreateInfo createDeviceQueueCreateInfo(
                const uint32_t        &queueFamilyIndex,
                const float           *queuePriority,
                const void            *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkDeviceQueueCreateFlags(),
                        .queueFamilyIndex = queueFamilyIndex,
                        .queueCount = 1,
                        .pQueuePriorities = queuePriority
                };
        }

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
        using DeviceCreateInfo = VkDeviceCreateInfo;
        VULKANPP_CONSTEXPR DeviceCreateInfo createDeviceCreateInfo(
                const std::vector<DeviceQueueCreateInfo>        &queueCreateInfos,
                const std::vector<const char *>                 &enabledExtensionNames,
                const PhysicalDeviceFeatures                    *pEnabledFeatures,
                const void                                      *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                        .pNext = pNext,
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
        using FenceCreateInfo = VkFenceCreateInfo;
        VULKANPP_CONSTEXPR FenceCreateInfo createFenceCreateInfo(
                const VkFenceCreateFlags        &flags,
                const void                      *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = flags
                };
        }

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
        using FramebufferCreateInfo = VkFramebufferCreateInfo;
        VULKANPP_CONSTEXPR FramebufferCreateInfo createFramebufferCreateInfo(
                const RenderPass                     &renderPass,
                const Extent2D                       &extent,
                const std::vector<ImageView>         &attachments,
                const void                           *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkFramebufferCreateFlags(),
                        .renderPass = renderPass,
                        .attachmentCount = static_cast<uint32_t>(attachments.size()),
                        .pAttachments = attachments.data(),
                        .width = extent.width,
                        .height = extent.height,
                        .layers = 1
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkComponentMapping - Structure specifying a color component mapping<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkComponentMapping structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkComponentMapping {
         *     VkComponentSwizzle    r;
         *     VkComponentSwizzle    g;
         *     VkComponentSwizzle    b;
         *     VkComponentSwizzle    a;
         *} VkComponentMapping;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>r is a VkComponentSwizzle specifying the component value placed in the R component of the output vector.
         * <li>g is a VkComponentSwizzle specifying the component value placed in the G component of the output vector.
         * <li>b is a VkComponentSwizzle specifying the component value placed in the B component of the output vector.
         * <li>a is a VkComponentSwizzle specifying the component value placed in the A component of the output vector.
         * </ul>
         */
        using ComponentMapping = VkComponentMapping;
        VULKANPP_CONSTEXPR ComponentMapping createComponentMapping(
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

        /** <b>Name</b><hr><br>
         *
         * VkImageSubresourceRange - Structure specifying an image subresource range<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkImageSubresourceRange structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkImageSubresourceRange {
         *     VkImageAspectFlags    aspectMask;
         *     uint32_t              baseMipLevel;
         *     uint32_t              levelCount;
         *     uint32_t              baseArrayLayer;
         *     uint32_t              layerCount;
         * } VkImageSubresourceRange;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>aspectMask is a bitmask of VkImageAspectFlagBits specifying which aspect(s) of the image are included in the view.
         * <li>baseMipLevel is the first mipmap level accessible to the view.
         * <li>levelCount is the number of mipmap levels (starting from baseMipLevel) accessible to the view.
         * <li>baseArrayLayer is the first array layer accessible to the view.
         * <li>layerCount is the number of array layers (starting from baseArrayLayer) accessible to the view.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The number of mipmap levels and array layers <b>must</b> be a subset of the image subresources in the image. If an application wants to use all mip levels or layers in an image after the baseMipLevel or baseArrayLayer, it <b>can</b> set levelCount and layerCount to the special values VK_REMAINING_MIP_LEVELS and VK_REMAINING_ARRAY_LAYERS without knowing the exact number of mip levels or layers.<br><br>
         *
         * For cube and cube array image views, the layers of the image view starting at baseArrayLayer correspond to faces in the order +X, -X, +Y, -Y, +Z, -Z. For cube arrays, each set of six sequential layers is a single cube, so the number of cube maps in a cube map array view is layerCount / 6, and image array layer (baseArrayLayer + i) is face index (i mod 6) of cube i / 6. If the number of layers in the view, whether set explicitly in layerCount or implied by VK_REMAINING_ARRAY_LAYERS, is not a multiple of 6, the last cube map in the array <b>must</b> not be accessed.<br><br>
         *
         * aspectMask <b>must</b> be only VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_ASPECT_DEPTH_BIT or VK_IMAGE_ASPECT_STENCIL_BIT if format is a color, depth-only or stencil-only format, respectively, except if format is a multi-planar format. If using a depth/stencil format with both depth and stencil components, aspectMask <b>must</b> include at least one of VK_IMAGE_ASPECT_DEPTH_BIT and VK_IMAGE_ASPECT_STENCIL_BIT, and <b>can</b> include both.<br><br>
         *
         * When the VkImageSubresourceRange structure is used to select a subset of the slices of a 3D image’s mip level in order to create a 2D or 2D array image view of a 3D image created with VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT, baseArrayLayer and layerCount specify the first slice index and the number of slices to include in the created image view. Such an image view <b>can</b> be used as a framebuffer attachment that refers only to the specified range of slices of the selected mip level. However, any layout transitions performed on such an attachment view during a render pass instance still apply to the entire subresource referenced which includes all the slices of the selected mip level.<br><br>
         *
         * When using an image view of a depth/stencil image to populate a descriptor set (e.g. for sampling in the shader, or for use as an input attachment), the aspectMask <b>must</b> only include one bit, which selects whether the image view is used for depth reads (i.e. using a floating-point sampler or input attachment in the shader) or stencil reads (i.e. using an unsigned integer sampler or input attachment in the shader). When an image view of a depth/stencil image is used as a depth/stencil framebuffer attachment, the aspectMask is ignored and both depth and stencil image subresources are used.<br><br>
         *
         * When creating a VkImageView, if sampler Y′CBCR conversion is enabled in the sampler, the aspectMask of a subresourceRange used by the VkImageView <b>must</b> be VK_IMAGE_ASPECT_COLOR_BIT.<br><br>
         *
         * When creating a VkImageView, if sampler Y′CBCR conversion is not enabled in the sampler and the image format is multi-planar, the image <b>must</b> have been created with VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT, and the aspectMask of the VkImageView’s subresourceRange <b>must</b> be VK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT or VK_IMAGE_ASPECT_PLANE_2_BIT.
         */
        using ImageSubresourceRange = VkImageSubresourceRange;
        VULKANPP_CONSTEXPR ImageSubresourceRange createImageSubresourceRange(
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
         * <pre><b>  Image View Type</b>               | <b>Compatible Image Types</b></pre><
         * <pre>  VK_IMAGE_VIEW_TYPE_1D         | VK_IMAGE_TYPE_1D</pre>
         * <pre>  VK_IMAGE_VIEW_TYPE_1D_ARRAY   | VK_IMAGE_TYPE_1D</pre>
         * <pre>  VK_IMAGE_VIEW_TYPE_2D         | VK_IMAGE_TYPE_2D , VK_IMAGE_TYPE_3D</pre>
         * <pre>  VK_IMAGE_VIEW_TYPE_2D_ARRAY   | VK_IMAGE_TYPE_2D , VK_IMAGE_TYPE_3D</pre>
         * <pre>  VK_IMAGE_VIEW_TYPE_CUBE       | VK_IMAGE_TYPE_2D</pre>
         * <pre>  VK_IMAGE_VIEW_TYPE_CUBE_ARRAY | VK_IMAGE_TYPE_2D</pre>
         * <pre>  VK_IMAGE_VIEW_TYPE_3D         | VK_IMAGE_TYPE_3D</pre>
         *
         *
         */
        using ImageViewCreateInfo = VkImageViewCreateInfo;
        VULKANPP_CONSTEXPR ImageViewCreateInfo createImageViewCreateInfo(
                const Image                     &image,
                const Format                    &format,
                const VkImageAspectFlags        &aspectMask,
                const void                      *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkImageViewCreateFlags(),
                        .image = image,
                        .viewType = VK_IMAGE_VIEW_TYPE_2D,
                        .format = format,
                        .components = vk::createComponentMapping(
                                VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                                VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY
                        ),
                        .subresourceRange = vk::createImageSubresourceRange(
                                aspectMask, 0, 1, 0, 1
                        ),
                };
        }

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
        using InstanceCreateInfo = VkInstanceCreateInfo;
        VULKANPP_CONSTEXPR InstanceCreateInfo createInstanceCreateInfo(
                const ApplicationInfo                  &applicationInfo,
                const std::vector<const char *>        &enabledLayerNames,
                const std::vector<const char *>        &enabledExtensionNames,
                const void                             *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkInstanceCreateFlags(),
                        .pApplicationInfo = &applicationInfo,
                        .enabledLayerCount = static_cast<uint32_t>(enabledLayerNames.size()),
                        .ppEnabledLayerNames = enabledLayerNames.data(),
                        .enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size()),
                        .ppEnabledExtensionNames = enabledExtensionNames.data()
                };
        }

        //TODO doc
        using PipelineDepthStencilStateCreateInfo = VkPipelineDepthStencilStateCreateInfo;
        VULKANPP_CONSTEXPR PipelineDepthStencilStateCreateInfo createPipelineDepthStencilStateCreateInfo(
                const Bool32                  &depthTestEnable,
                const Bool32                  &depthWriteEnable,
                const Bool32                  &depthBoundsTestEnable,
                const Bool32                  &stencilTestEnable,
                const VkStencilOpState        &front,
                const VkStencilOpState        &back,
                const void                    *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineDepthStencilStateCreateFlags(),
                        .depthTestEnable = depthTestEnable,
                        .depthWriteEnable = depthWriteEnable,
                        .depthCompareOp = VK_COMPARE_OP_LESS,
                        .depthBoundsTestEnable = depthBoundsTestEnable,
                        .stencilTestEnable = stencilTestEnable,
                        .front = front,
                        .back = back,
                        .minDepthBounds = 0.0f,
                        .maxDepthBounds = 1.0f
                };
        }

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
        using GraphicsPipelineCreateInfo = VkGraphicsPipelineCreateInfo;
        VULKANPP_CONSTEXPR GraphicsPipelineCreateInfo createGraphicsPipelineCreateInfo(
                const PipelineVertexInputStateCreateInfo                &vertexInputStateCreateInfo,
                const PipelineInputAssemblyStateCreateInfo              &inputAssemblyStateCreateInfo,
                const PipelineViewportStateCreateInfo                   &viewportStateCreateInfo,
                const PipelineRasterizationStateCreateInfo              &rasterizationStateCreateInfo,
                const PipelineMultisampleStateCreateInfo                &multisampleStateCreateInfo,
                const PipelineDepthStencilStateCreateInfo               *pDepthStencilState,
                const PipelineColorBlendStateCreateInfo                 &colorBlendStateCreateInfo,
                const std::vector<PipelineShaderStageCreateInfo>        &shaderStages,
                const PipelineLayout                                    &layout,
                const RenderPass                                        &renderPass,
                const void                                              *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineCreateFlags(),
                        .stageCount = static_cast<uint32_t>(shaderStages.size()),
                        .pStages = shaderStages.data(),
                        .pVertexInputState = &vertexInputStateCreateInfo,
                        .pInputAssemblyState = &inputAssemblyStateCreateInfo,
                        .pTessellationState = nullptr,
                        .pViewportState = &viewportStateCreateInfo,
                        .pRasterizationState = &rasterizationStateCreateInfo,
                        .pMultisampleState = &multisampleStateCreateInfo,
                        .pDepthStencilState = pDepthStencilState,
                        .pColorBlendState = &colorBlendStateCreateInfo,
                        .pDynamicState = nullptr,
                        .layout = layout,
                        .renderPass = renderPass,
                        .subpass = 0,
                        .basePipelineHandle = nullptr,
                        .basePipelineIndex = -1,
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkPipelineLayoutCreateInfo - Structure specifying the parameters of a newly created pipeline layout object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPipelineLayoutCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using PipelineLayoutCreateInfo = VkPipelineLayoutCreateInfo;
        VULKANPP_CONSTEXPR PipelineLayoutCreateInfo createPipelineLayoutCreateInfo(
                const std::vector<DescriptorSetLayout>        &setLayouts,
                const std::vector<PushConstantRange>          &pushConstantRanges,
                const void                                    *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkPipelineLayoutCreateFlags(),
                        .setLayoutCount = static_cast<uint32_t>(setLayouts.size()),
                        .pSetLayouts = setLayouts.data(),
                        .pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size()),
                        .pPushConstantRanges = pushConstantRanges.data()
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkRenderPassCreateInfo - Structure specifying parameters of a newly created render pass<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkRenderPassCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using RenderPassCreateInfo = VkRenderPassCreateInfo;
        VULKANPP_CONSTEXPR RenderPassCreateInfo createRenderPassCreateInfo(
                const std::vector<AttachmentDescription>        &attachmentDescriptions,
                const std::vector<SubpassDescription>           &subpassDescriptions,
                const std::vector<VkSubpassDependency>          &dependencies,
                const void                                      *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkRenderPassCreateFlags(),
                        .attachmentCount = static_cast<uint32_t>(attachmentDescriptions.size()),
                        .pAttachments = attachmentDescriptions.data(),
                        .subpassCount = static_cast<uint32_t>(subpassDescriptions.size()),
                        .pSubpasses = subpassDescriptions.data(),
                        .dependencyCount = static_cast<uint32_t>(dependencies.size()),
                        .pDependencies = dependencies.data()
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkSemaphoreCreateInfo - Structure specifying parameters of a newly created semaphore<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSemaphoreCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using SemaphoreCreateInfo = VkSemaphoreCreateInfo;
        VULKANPP_CONSTEXPR SemaphoreCreateInfo createSemaphoreCreateInfo(
                const void        *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkSemaphoreCreateFlags()
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkShaderModuleCreateInfo - Structure specifying parameters of a newly created shader module<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkShaderModuleCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using ShaderModuleCreateInfo = VkShaderModuleCreateInfo;
        VULKANPP_CONSTEXPR ShaderModuleCreateInfo createShaderModuleCreateInfo(
                const std::vector<uint8_t>        &code,
                const void                        *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkShaderModuleCreateFlags(),
                        .codeSize = static_cast<uint32_t>(code.size()),
                        .pCode = std::_Bit_cast<const uint32_t *>(code.data())
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkSwapchainCreateInfoKHR - Structure specifying parameters of a newly created swapchain object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSwapchainCreateInfoKHR structure is defined as:
         *
         * @code
         * // Provided by VK_KHR_swapchain
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
        using SwapchainCreateInfoKHR = VkSwapchainCreateInfoKHR;
        VULKANPP_CONSTEXPR SwapchainCreateInfoKHR createSwapchainCreateInfoKHR(
                const SurfaceCapabilitiesKHR        &capabilities,
                const uint32_t                      &minImageCount,
                const SurfaceFormatKHR              &format,
                const Extent2D                      &extent,
                const PresentModeKHR                &presentMode,
                const SurfaceKHR                    &surface,
                const std::vector<uint32_t>         &queueFamilyIndices,
                const void                          *pNext = nullptr
        ) {

                return {
                        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                        .pNext = pNext,
                        .flags = VkSwapchainCreateFlagsKHR(),
                        .surface = surface,
                        .minImageCount = minImageCount,
                        .imageFormat = format.format,
                        .imageColorSpace = format.colorSpace,
                        .imageExtent = extent,
                        .imageArrayLayers = 1,
                        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                        .imageSharingMode = queueFamilyIndices.size() == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,
                        .queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size()),
                        .pQueueFamilyIndices = queueFamilyIndices.data(),
                        .preTransform = capabilities.currentTransform,
                        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                        .presentMode = presentMode,
                        .clipped = VK_TRUE,
                        .oldSwapchain = nullptr
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSetLayoutBinding - Structure specifying a descriptor set layout binding<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorSetLayoutBinding structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
         * <li>descriptorCount is the number of descriptors contained in the binding, accessed in a shader as an array , except if descriptorType is VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT in which case descriptorCount is the size in bytes of the uniform block . If descriptorCount is zero this binding entry is reserved and the resource <b>must</b> not be accessed from any stage via this binding within any pipeline using the set layout.
         * <li>stageFlags member is a bitmask of VkShaderStageFlagBits specifying which pipeline shader stages <b>can</b> access a resource for this binding. VK_SHADER_STAGE_ALL is a shorthand specifying that all defined shader stages, including any additional stages defined by extensions, <b>can</b> access the resource.
         * <li>If a shader stage is not included in stageFlags, then a resource <b>must</b> not be accessed from that stage via this binding within any pipeline using the set layout. Other than input attachments which are limited to the fragment shader, there are no limitations on what combinations of stages <b>can</b> use a descriptor binding, and in particular a binding <b>can</b> be used by both graphics stages and the compute stage.
         * </ul><br>
         * <b>Description</b><hr><br>
         * <ul>
         * <li>pImmutableSamplers affects initialization of samplers. If descriptorType specifies a VK_DESCRIPTOR_TYPE_SAMPLER or VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER type descriptor, then pImmutableSamplers <b>can</b> be used to initialize a set of immutable samplers. Immutable samplers are permanently bound into the set layout and <b>must</b> not be changed; updating a VK_DESCRIPTOR_TYPE_SAMPLER descriptor with immutable samplers is not allowed and updates to a VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER descriptor with immutable samplers does not modify the samplers (the image views are updated, but the sampler updates are ignored). If pImmutableSamplers is not NULL, then it points to an array of sampler handles that will be copied into the set layout and used for the corresponding binding. Only the sampler handles are copied; the sampler objects <b>must</b> not be destroyed before the final use of the set layout and any descriptor pools and sets created using it. If pImmutableSamplers is NULL, then the sampler slots are dynamic and sampler handles <b>must</b> be bound into descriptor sets using this layout. If descriptorType is not one of these descriptor types, then pImmutableSamplers is ignored.
         * </ul>
         * The above layout definition allows the descriptor bindings to be specified sparsely such that not all binding numbers between 0 and the maximum binding number need to be specified in the pBindings array. Bindings that are not specified have a descriptorCount and stageFlags of zero, and the value of descriptorType is undefined. However, all binding numbers between 0 and the maximum binding number in the VkDescriptorSetLayoutCreateInfo::pBindings array <b>may</b> consume memory in the descriptor set layout even if not all descriptor bindings are used, though it <b>should</b> not consume additional memory from the descriptor pool.
         */
        using DescriptorSetLayoutBinding = VkDescriptorSetLayoutBinding;
        VULKANPP_CONSTEXPR DescriptorSetLayoutBinding createDescriptorSetLayoutBinding(
                const uint32_t                  &binding,
                const VkDescriptorType          &descriptorType,
                const uint32_t                  &descriptorCount,
                const VkShaderStageFlags        &stageFlags,
                const Sampler                   *pImmutableSamplers
        ) {
                return {
                        .binding = binding,
                        .descriptorType = descriptorType,
                        .descriptorCount = descriptorCount,
                        .stageFlags = stageFlags,
                        .pImmutableSamplers = pImmutableSamplers
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorSetLayoutCreateInfo - Structure specifying parameters of a newly created descriptor set layout<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Information about the descriptor set layout is passed in a VkDescriptorSetLayoutCreateInfo structure:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using DescriptorSetLayoutCreateInfo = VkDescriptorSetLayoutCreateInfo;
        VULKANPP_CONSTEXPR DescriptorSetLayoutCreateInfo createDescriptorSetLayoutCreateInfo(
                const std::vector<DescriptorSetLayoutBinding>        &bindings,
                const void                                           *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkDescriptorSetLayoutCreateFlags(),
                        .bindingCount = static_cast<uint32_t>(bindings.size()),
                        .pBindings = bindings.data()
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorPoolCreateInfo - Structure specifying parameters of a newly created descriptor pool<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * Additional information about the pool is passed in a VkDescriptorPoolCreateInfo structure:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using DescriptorPoolCreateInfo = VkDescriptorPoolCreateInfo;
        VULKANPP_CONSTEXPR DescriptorPoolCreateInfo createDescriptorPoolCreateInfo(
                const uint32_t                               &maxSets,
                const std::vector<DescriptorPoolSize>        &poolSizes,
                const void                                   *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkDescriptorPoolCreateFlags(),
                        .maxSets = maxSets,
                        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
                        .pPoolSizes = poolSizes.data()
                };
        }

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
        using DescriptorSetAllocateInfo = VkDescriptorSetAllocateInfo;
        VULKANPP_CONSTEXPR DescriptorSetAllocateInfo createDescriptorSetAllocateInfo(
                const DescriptorPool                          &descriptorPool,
                const std::vector<DescriptorSetLayout>        &setLayouts,
                const void                                    *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                        .pNext = pNext,
                        .descriptorPool = descriptorPool,
                        .descriptorSetCount = static_cast<uint32_t>(setLayouts.size()),
                        .pSetLayouts = setLayouts.data()
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorBufferInfo - Structure specifying descriptor buffer info<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorBufferInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using DescriptorBufferInfo = VkDescriptorBufferInfo;
        VULKANPP_CONSTEXPR DescriptorBufferInfo createDescriptorBufferInfo(
                const Buffer            &buffer,
                const DeviceSize        &offset,
                const DeviceSize        &range
        ) {
                return {
                        .buffer = buffer,
                        .offset = offset,
                        .range = range
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkWriteDescriptorSet - Structure specifying the parameters of a descriptor set write operation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkWriteDescriptorSet structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
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
        using WriteDescriptorSet = VkWriteDescriptorSet;
        VULKANPP_CONSTEXPR WriteDescriptorSet createWriteDescriptorSet(
                const DescriptorSet                 &dstSet,
                const uint32_t                      &dstBinding,
                const uint32_t                      &dstArrayElement,
                const uint32_t                      &descriptorCount,
                const VkDescriptorType              &descriptorType,
                const VkDescriptorImageInfo         *pImageInfo,
                const VkDescriptorBufferInfo        *pBufferInfo,
                const BufferView                    *pTexelBufferView,
                const void                          *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                        .pNext = pNext,
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

        /** <b>Name</b><hr><br>
         *
         * VkImageCreateInfo - Structure specifying the parameters of a newly created image object<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkImageCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkImageCreateInfo {
         *     VkStructureType          sType;
         *     const void*              pNext;
         *     VkImageCreateFlags       flags;
         *     VkImageType              imageType;
         *     VkFormat                 format;
         *     VkExtent3D               extent;
         *     uint32_t                 mipLevels;
         *     uint32_t                 arrayLayers;
         *     VkSampleCountFlagBits    samples;
         *     VkImageTiling            tiling;
         *     VkImageUsageFlags        usage;
         *     VkSharingMode            sharingMode;
         *     uint32_t                 queueFamilyIndexCount;
         *     const uint32_t*          pQueueFamilyIndices;
         *     VkImageLayout            initialLayout;
         * } VkImageCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkImageCreateFlagBits describing additional parameters of the image.
         * <li>imageType is a VkImageType value specifying the basic dimensionality of the image. Layers in array textures do not count as a dimension for the purposes of the image type.
         * <li>format is a VkFormat describing the format and type of the texel blocks that will be contained in the image.
         * <li>extent is a VkExtent3D describing the number of data elements in each dimension of the base level.
         * <li>mipLevels describes the number of levels of detail available for minified sampling of the image.
         * <li>arrayLayers is the number of layers in the image.
         * <li>samples is a VkSampleCountFlagBits value specifying the number of samples per texel.
         * <li>tiling is a VkImageTiling value specifying the tiling arrangement of the texel blocks in memory.
         * <li>usage is a bitmask of VkImageUsageFlagBits describing the intended usage of the image.
         * <li>sharingMode is a VkSharingMode value specifying the sharing mode of the image when it will be accessed by multiple queue families.
         * <li>queueFamilyIndexCount is the number of entries in the pQueueFamilyIndices array.
         * <li>pQueueFamilyIndices is a pointer to an array of queue families that will access this image. It is ignored if sharingMode is not VK_SHARING_MODE_CONCURRENT.
         * <li>initialLayout is a VkImageLayout value specifying the initial VkImageLayout of all image subresources of the image. See Image Layouts.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Images created with tiling equal to VK_IMAGE_TILING_LINEAR have further restrictions on their limits and capabilities compared to images created with tiling equal to VK_IMAGE_TILING_OPTIMAL. Creation of images with tiling VK_IMAGE_TILING_LINEAR <b>may</b> not be supported unless other parameters meet all of the constraints:
         * <ul>
         * <li>imageType is VK_IMAGE_TYPE_2D
         * <li>format is not a depth/stencil format
         * <li>mipLevels is 1
         * <li>arrayLayers is 1
         * <li>samples is VK_SAMPLE_COUNT_1_BIT
         * <li>usage only includes VK_IMAGE_USAGE_TRANSFER_SRC_BIT and/or VK_IMAGE_USAGE_TRANSFER_DST_BIT
         * </ul>
         * Images created with one of the formats that require a sampler Y′CBCR conversion, have further restrictions on their limits and capabilities compared to images created with other formats. Creation of images with a format requiring Y′CBCR conversion <b>may</b> not be supported unless other parameters meet all of the constraints:
         * <ul>
         * imageType is VK_IMAGE_TYPE_2D
         * mipLevels is 1
         * arrayLayers is 1, unless the ycbcrImageArrays feature is enabled, or otherwise indicated by VkImageFormatProperties::maxArrayLayers, as returned by vkGetPhysicalDeviceImageFormatProperties
         * samples is VK_SAMPLE_COUNT_1_BI
         * </ul>
         * Implementations <b>may</b> support additional limits and capabilities beyond those listed above.<br><br>
         *
         * To determine the set of valid usage bits for a given format, call vkGetPhysicalDeviceFormatProperties.<br><br>
         *
         * If the size of the resultant image would exceed maxResourceSize, then vkCreateImage <b>must</b> fail and return VK_ERROR_OUT_OF_DEVICE_MEMORY. This failure <b>may</b> occur even when all image creation parameters satisfy their valid usage requirements.<br><br>
         *
         * If the implementation reports VK_TRUE in VkPhysicalDeviceHostImageCopyPropertiesEXT::identicalMemoryTypeRequirements, usage of VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT <b>must</b> not affect the memory type requirements of the image as described in Sparse Resource Memory Requirements and Resource Memory Association.
         *
         * @note For images created without VK_IMAGE_CREATE_EXTENDED_USAGE_BIT a usage bit is valid if it is supported for the format the image is created with.<br><br>
         * For images created with VK_IMAGE_CREATE_EXTENDED_USAGE_BIT a usage bit is valid if it is supported for at least one of the formats a VkImageView created from the image <b>can</b> have (see Image Views for more detail).
         */
        using ImageCreateInfo = VkImageCreateInfo;
        VULKANPP_CONSTEXPR ImageCreateInfo createImageCreateInfo(
                const VkImageType                  &imageType,
                const Format                       &format,
                const Extent3D                     &extent,
                const VkImageUsageFlags            &usage,
                const VkImageTiling                &tiling,
                const std::vector<uint32_t>        &queueFamilyIndices,
                const void                         *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                        .pNext = pNext,
                        .flags = VkImageCreateFlags(),
                        .imageType = imageType,
                        .format = format,
                        .extent = extent,
                        .mipLevels = 1,
                        .arrayLayers = 1,
                        .samples = VK_SAMPLE_COUNT_1_BIT,
                        .tiling = tiling,
                        .usage = usage,
                        .sharingMode = queueFamilyIndices.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE,
                        .queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size()),
                        .pQueueFamilyIndices = queueFamilyIndices.data(),
                        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkImageMemoryBarrier - Structure specifying the parameters of an image memory barrier<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkImageMemoryBarrier structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkImageMemoryBarrier {
         *     VkStructureType            sType;
         *     const void*                pNext;
         *     VkAccessFlags              srcAccessMask;
         *     VkAccessFlags              dstAccessMask;
         *     VkImageLayout              oldLayout;
         *     VkImageLayout              newLayout;
         *     uint32_t                   srcQueueFamilyIndex;
         *     uint32_t                   dstQueueFamilyIndex;
         *     VkImage                    image;
         *     VkImageSubresourceRange    subresourceRange;
         * } VkImageMemoryBarrier;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>srcAccessMask is a bitmask of VkAccessFlagBits specifying a source access mask.
         * <li>dstAccessMask is a bitmask of VkAccessFlagBits specifying a destination access mask.
         * <li>oldLayout is the old layout in an image layout transition.
         * <li>newLayout is the new layout in an image layout transition.
         * <li>srcQueueFamilyIndex is the source queue family for a queue family ownership transfer.
         * <li>dstQueueFamilyIndex is the destination queue family for a queue family ownership transfer.
         * <li>image is a handle to the image affected by this barrier.
         * <li>subresourceRange describes the image subresource range within image that is affected by this barrier.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The first access scope is limited to access to memory through the specified image subresource range, via access types in the source access mask specified by srcAccessMask. If srcAccessMask includes VK_ACCESS_HOST_WRITE_BIT, memory writes performed by that access type are also made visible, as that access type is not performed through a resource.<br><br>
         *
         * The second access scope is limited to access to memory through the specified image subresource range, via access types in the destination access mask specified by dstAccessMask. If dstAccessMask includes VK_ACCESS_HOST_WRITE_BIT or VK_ACCESS_HOST_READ_BIT, available memory writes are also made visible to accesses of those types, as those access types are not performed through a resource.<br><br>
         *
         * If srcQueueFamilyIndex is not equal to dstQueueFamilyIndex, and srcQueueFamilyIndex is equal to the current queue family, then the memory barrier defines a queue family release operation for the specified image subresource range, and the second synchronization scope of the calling command does not apply to this operation.<br><br>
         *
         * If dstQueueFamilyIndex is not equal to srcQueueFamilyIndex, and dstQueueFamilyIndex is equal to the current queue family, then the memory barrier defines a queue family acquire operation for the specified image subresource range, and the first synchronization scope of the calling command does not apply to this operation.<br><br>
         *
         * If the synchronization2 feature is not enabled or oldLayout is not equal to newLayout, oldLayout and newLayout define an image layout transition for the specified image subresource range.<br><br>
         *
         * @note If the synchronization2 feature is enabled, when the old and new layout are equal, the layout values are ignored - data is preserved no matter what values are specified, or what layout the image is currently in.
         *
         * If image has a multi-planar format and the image is disjoint, then including VK_IMAGE_ASPECT_COLOR_BIT in the aspectMask member of subresourceRange is equivalent to including VK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT, and (for three-plane formats only) VK_IMAGE_ASPECT_PLANE_2_BIT.
         */
        using ImageMemoryBarrier = VkImageMemoryBarrier;
        VULKANPP_CONSTEXPR ImageMemoryBarrier createImageMemoryBarrier(
                const VkAccessFlags             &srcAccessMask,
                const VkAccessFlags             &dstAccessMask,
                const VkImageLayout             &oldLayout,
                const VkImageLayout             &newLayout,
                const uint32_t                  &srcQueueFamilyIndex,
                const uint32_t                  &dstQueueFamilyIndex,
                const Image                     &image,
                const VkImageAspectFlags        &aspectMask,
                const void                      *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                        .pNext = pNext,
                        .srcAccessMask = srcAccessMask,
                        .dstAccessMask = dstAccessMask,
                        .oldLayout = oldLayout,
                        .newLayout = newLayout,
                        .srcQueueFamilyIndex = srcQueueFamilyIndex,
                        .dstQueueFamilyIndex = dstQueueFamilyIndex,
                        .image = image,
                        .subresourceRange = vk::createImageSubresourceRange(
                                aspectMask, 0, 1, 0, 1
                        )
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkImageSubresourceLayers - Structure specifying an image subresource layers<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkImageSubresourceLayers structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkImageSubresourceLayers {
         *     VkImageAspectFlags    aspectMask;
         *     uint32_t              mipLevel;
         *     uint32_t              baseArrayLayer;
         *     uint32_t              layerCount;
         * } VkImageSubresourceLayers;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>aspectMask is a combination of VkImageAspectFlagBits, selecting the color, depth and/or stencil aspects to be copied.
         * <li>mipLevel is the mipmap level to copy
         * <li>baseArrayLayer and layerCount are the starting layer and number of layers to copy.
         * </ul>
         */
        using ImageSubresourceLayers = VkImageSubresourceLayers;
        VULKANPP_CONSTEXPR ImageSubresourceLayers createImageSubresourceLayers(
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

        /** <b>Name</b><hr><br>
         *
         * VkOffset3D - Structure specifying a three-dimensional offset<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * A three-dimensional offset is defined by the structure:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkOffset2D {
         *     int32_t    x;
         *     int32_t    y;
         *     int32_t    z;
         * } VkOffset2D;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>x is the x offset.
         * <li>y is the y offset.
         * <li>z is the z offset.
         * </ul>
         */
        using Offset3D = VkOffset3D;
        VULKANPP_CONSTEXPR Offset3D createOffset3D(
                const int32_t        &x,
                const int32_t        &y,
                const int32_t        &z
        ) {
                return {
                        .x = x,
                        .y = y,
                        .z = z
                };
        }
        VULKANPP_CONSTEXPR Offset3D createOffset3D(
                const Offset2D        &offset2D,
                const int32_t         &z
        ) {
                return {
                        .x = offset2D.x,
                        .y = offset2D.y,
                        .z = z
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkBufferImageCopy - Structure specifying a buffer image copy operation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * For both vkCmdCopyBufferToImage and vkCmdCopyImageToBuffer, each element of pRegions is a structure defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkBufferImageCopy {
         *     VkDeviceSize                bufferOffset;
         *     uint32_t                    bufferRowLength;
         *     uint32_t                    bufferImageHeight;
         *     VkImageSubresourceLayers    imageSubresource;
         *     VkOffset3D                  imageOffset;
         *     VkExtent3D                  imageExtent;
         * } VkBufferImageCopy;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>bufferOffset is the offset in bytes from the start of the buffer object where the image data is copied from or to.
         * <li>bufferRowLength and bufferImageHeight specify in texels a subregion of a larger two- or three-dimensional image in buffer memory, and control the addressing calculations. If either of these values is zero, that aspect of the buffer memory is considered to be tightly packed according to the imageExtent.
         * <li>imageSubresource is a VkImageSubresourceLayers used to specify the specific image subresources of the image used for the source or destination image data.
         * <li>imageOffset selects the initial x, y, z offsets in texels of the sub-region of the source or destination image data.
         * <li>imageExtent is the size in texels of the image to copy in width, height and depth.
         * </ul>
         */
        using BufferImageCopy = VkBufferImageCopy;
        VULKANPP_CONSTEXPR BufferImageCopy createBufferImageCopy(
                const DeviceSize                    &bufferOffset,
                const uint32_t                      &bufferRowLength,
                const uint32_t                      &bufferImageHeight,
                const Extent3D                      &imageExtent
        ) {
                return {
                        .bufferOffset = bufferOffset,
                        .bufferRowLength = bufferRowLength,
                        .bufferImageHeight = bufferImageHeight,
                        .imageSubresource = vk::createImageSubresourceLayers(
                                VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1
                        ),
                        .imageOffset = vk::createOffset3D(0, 0, 0),
                        .imageExtent = imageExtent
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkSamplerCreateInfo - Structure specifying parameters of a newly created sampler<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkSamplerCreateInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkSamplerCreateInfo {
         *     VkStructureType         sType;
         *     const void*             pNext;
         *     VkSamplerCreateFlags    flags;
         *     VkFilter                magFilter;
         *     VkFilter                minFilter;
         *     VkSamplerMipmapMode     mipmapMode;
         *     VkSamplerAddressMode    addressModeU;
         *     VkSamplerAddressMode    addressModeV;
         *     VkSamplerAddressMode    addressModeW;
         *     float                   mipLodBias;
         *     VkBool32                anisotropyEnable;
         *     float                   maxAnisotropy;
         *     VkBool32                compareEnable;
         *     VkCompareOp             compareOp;
         *     float                   minLod;
         *     float                   maxLod;
         *     VkBorderColor           borderColor;
         *     VkBool32                unnormalizedCoordinates;
         * } VkSamplerCreateInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>flags is a bitmask of VkSamplerCreateFlagBits describing additional parameters of the sampler.
         * <li>magFilter is a VkFilter value specifying the magnification filter to apply to lookups.
         * <li>minFilter is a VkFilter value specifying the minification filter to apply to lookups.
         * <li>mipmapMode is a VkSamplerMipmapMode value specifying the mipmap filter to apply to lookups.
         * <li>addressModeU is a VkSamplerAddressMode value specifying the addressing mode for U coordinates outside [0,1).
         * <li>addressModeV is a VkSamplerAddressMode value specifying the addressing mode for V coordinates outside [0,1).
         * <li>addressModeW is a VkSamplerAddressMode value specifying the addressing mode for W coordinates outside [0,1).
         * <li>mipLodBias is the bias to be added to mipmap LOD calculation and bias provided by image sampling functions in SPIR-V, as described in the LOD Operation section.
         * <li>anisotropyEnable is VK_TRUE to enable anisotropic filtering, as described in the Texel Anisotropic Filtering section, or VK_FALSE otherwise.
         * <li>maxAnisotropy is the anisotropy value clamp used by the sampler when anisotropyEnable is VK_TRUE. If anisotropyEnable is VK_FALSE, maxAnisotropy is ignored.
         * <li>compareEnable is VK_TRUE to enable comparison against a reference value during lookups, or VK_FALSE otherwise.
         *     <ul>
         *     <li>Note: Some implementations will default to shader state if this member does not match.
         *     </ul>
         * <li>compareOp is a VkCompareOp value specifying the comparison operator to apply to fetched data before filtering as described in the Depth Compare Operation section.
         * <li>minLod is used to clamp the minimum of the computed LOD value.
         * <li>maxLod is used to clamp the maximum of the computed LOD value. To avoid clamping the maximum value, set maxLod to the constant VK_LOD_CLAMP_NONE.
         * <li>borderColor is a VkBorderColor value specifying the predefined border color to use.
         * <li>unnormalizedCoordinates controls whether to use unnormalized or normalized texel coordinates to address texels of the image. When set to VK_TRUE, the range of the image coordinates used to lookup the texel is in the range of zero to the image size in each dimension. When set to VK_FALSE the range of image coordinates is zero to one.<br>
         * When unnormalizedCoordinates is VK_TRUE, images the sampler is used with in the shader have the following requirements:
         * <ul>
         * <li>The viewType <b>must</b> be either VK_IMAGE_VIEW_TYPE_1D or VK_IMAGE_VIEW_TYPE_2D.
         * <li>The image view <b>must</b> have a single layer and a single mip level.
         * </ul>
         * When unnormalizedCoordinates is VK_TRUE, image built-in functions in the shader that use the sampler have the following requirements:
         * <ul>
         * <li>The functions <b>must</b> not use projection.
         * <li>The functions <b>must</b> not use offsets.
         * </ul>
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * @note Mapping of OpenGL to Vulkan filter modes<br><br>
         * magFilter values of VK_FILTER_NEAREST and VK_FILTER_LINEAR directly correspond to GL_NEAREST and GL_LINEAR magnification filters. minFilter and mipmapMode combine to correspond to the similarly named OpenGL minification filter of GL_minFilter_MIPMAP_mipmapMode (e.g. minFilter of VK_FILTER_LINEAR and mipmapMode of VK_SAMPLER_MIPMAP_MODE_NEAREST correspond to GL_LINEAR_MIPMAP_NEAREST).<br><br>
         * There are no Vulkan filter modes that directly correspond to OpenGL minification filters of GL_LINEAR or GL_NEAREST, but they <b>can</b> be emulated using VK_SAMPLER_MIPMAP_MODE_NEAREST, minLod = 0, and maxLod = 0.25, and using minFilter = VK_FILTER_LINEAR or minFilter = VK_FILTER_NEAREST, respectively.<br><br>
         * Note that using a maxLod of zero would cause magnification to always be performed, and the magFilter to always be used. This is valid, just not an exact match for OpenGL behavior. Clamping the maximum LOD to 0.25 allows the λ value to be non-zero and minification to be performed, while still always rounding down to the base level. If the minFilter and magFilter are equal, then using a maxLod of zero also works.
         *
         * The maximum number of sampler objects which <b>can</b> be simultaneously created on a device is implementation-dependent and specified by the maxSamplerAllocationCount member of the VkPhysicalDeviceLimits structure.
         *
         * @note For historical reasons, if maxSamplerAllocationCount is exceeded, some implementations may return VK_ERROR_TOO_MANY_OBJECTS. Exceeding this limit will result in undefined behavior, and an application should not rely on the use of the returned error code in order to identify when the limit is reached.
         *
         * Since VkSampler is a non-dispatchable handle type, implementations <b>may</b> return the same handle for sampler state vectors that are identical. In such cases, all such objects would only count once against the maxSamplerAllocationCount limit.
         */
        using SamplerCreateInfo = VkSamplerCreateInfo;
        VULKANPP_CONSTEXPR SamplerCreateInfo createSamplerCreateInfo(
                const VkFilter                    &filter,
                const VkSamplerAddressMode        &addressMode,
                const Bool32                      &anisotropyEnable,
                const float                       &maxAnisotropy,
                const Bool32                      &compareEnable,
                const VkCompareOp                 &compareOp,
                const void                        *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                        .pNext = pNext,
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

        /** <b>Name</b><hr><br>
         *
         * VkDescriptorImageInfo - Structure specifying descriptor image information<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkDescriptorImageInfo structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkDescriptorImageInfo {
         *     VkSampler        sampler;
         *     VkImageView      imageView;
         *     VkImageLayout    imageLayout;
         * } VkDescriptorImageInfo;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sampler is a sampler handle, and is used in descriptor updates for types VK_DESCRIPTOR_TYPE_SAMPLER and VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER if the binding being updated does not use immutable samplers.
         * <li>imageView is VK_NULL_HANDLE or an image view handle, and is used in descriptor updates for types VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, and VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT.
         * <li>imageLayout is the layout that the image subresources accessible from imageView will be in at the time this descriptor is accessed. imageLayout is used in descriptor updates for types VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, and VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * Members of VkDescriptorImageInfo that are not used in an update (as described above) are ignored.
         */
        using DescriptorImageInfo = VkDescriptorImageInfo;
        VULKANPP_CONSTEXPR DescriptorImageInfo createDescriptorImageInfo(
                const Sampler              &sampler,
                const ImageView            &imageView,
                const VkImageLayout        &imageLayout
        ) {
                return {
                        .sampler = sampler,
                        .imageView = imageView,
                        .imageLayout = imageLayout
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkQueueFamilyProperties - Structure providing information about a queue family<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkQueueFamilyProperties structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkQueueFamilyProperties {
         *     VkQueueFlags    queueFlags;
         *     uint32_t        queueCount;
         *     uint32_t        timestampValidBits;
         *     VkExtent3D      minImageTransferGranularity;
         * } VkQueueFamilyProperties;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>queueFlags is a bitmask of VkQueueFlagBits indicating capabilities of the queues in this queue family.
         * <li>queueCount is the unsigned integer count of queues in this queue family. Each queue family must support at least one queue.
         * <li>timestampValidBits is the unsigned integer count of meaningful bits in the timestamps written via vkCmdWriteTimestamp2 or vkCmdWriteTimestamp. The valid range for the count is 36 to 64 bits, or a value of 0, indicating no support for timestamps. Bits outside the valid range are guaranteed to be zeros.
         * <li>minImageTransferGranularity is the minimum granularity supported for image transfer operations on the queues in this queue family.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The value returned in minImageTransferGranularity has a unit of compressed texel blocks for images having a block-compressed format, and a unit of texels otherwise.<br><br>
         *
         * Possible values of minImageTransferGranularity are:
         * <ul>
         * <li>(0,0,0) specifies that only whole mip levels <b>must</b> be transferred using the image transfer operations on the corresponding queues. In this case, the following restrictions apply to all offset and extent parameters of image transfer operations:
         *     <ul>
         *     <li>The x, y, and z members of a VkOffset3D parameter <b>must</b> always be zero.
         *     <li>The width, height, and depth members of a VkExtent3D parameter <b>must</b> always match the width, height, and depth of the image subresource corresponding to the parameter, respectively.
         *     </ul>
         * <li>(Ax, Ay, Az) where Ax, Ay, and Az are all integer powers of two. In this case the following restrictions apply to all image transfer operations:
         *     <ul>
         *     <li>x, y, and z of a VkOffset3D parameter <b>must</b> be integer multiples of Ax, Ay, and Az, respectively.
         *     <li>width of a VkExtent3D parameter <b>must</b> be an integer multiple of Ax, or else x + width <b>must</b> equal the width of the image subresource corresponding to the parameter.
         *     <li>height of a VkExtent3D parameter <b>must</b> be an integer multiple of Ay, or else y + height <b>must</b> equal the height of the image subresource corresponding to the parameter.
         *     <li>depth of a VkExtent3D parameter <b>must</b> be an integer multiple of Az, or else z + depth <b>must</b> equal the depth of the image subresource corresponding to the parameter.
         *     <li>If the format of the image corresponding to the parameters is one of the block-compressed formats then for the purposes of the above calculations the granularity <b>must</b> be scaled up by the compressed texel block dimensions.
         *     </ul>
         * </ul>
         * Queues supporting graphics and/or compute operations <b>must</b> report (1,1,1) in minImageTransferGranularity, meaning that there are no additional restrictions on the granularity of image transfer operations for these queues. Other queues supporting image transfer operations are only <b>required</b> to support whole mip level transfers, thus minImageTransferGranularity for queues belonging to such queue families <b>may</b> be (0,0,0).<br><br>
         *
         * The Device Memory section describes memory properties queried from the physical device.<br><br>
         *
         * For physical device feature queries see the Features chapter.
         */
        using QueueFamilyProperties = VkQueueFamilyProperties;
        std::vector<QueueFamilyProperties> getQueueFamilyProperties(
                const PhysicalDevice &physicalDevice
        );

        /** <b>Name</b><hr><br>
         *
         * VkExtensionProperties - Structure specifying an extension properties<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkExtensionProperties structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_0
         * typedef struct VkExtensionProperties {
         *     char        extensionName[VK_MAX_EXTENSION_NAME_SIZE];
         *     uint32_t    specVersion;
         * } VkExtensionProperties;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>extensionName is an array of VK_MAX_EXTENSION_NAME_SIZE char containing a null-terminated UTF-8 string which is the name of the extension.
         * <li>specVersion is the version of this extension. It is an integer, incremented with backward compatible changes.
         * </ul>
         */
        using ExtensionProperties = VkExtensionProperties;
        std::vector<ExtensionProperties> getExtensionProperties(
                const PhysicalDevice &physicalDevice
        );

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceFeatures2 - Structure describing the fine-grained features that can be supported by an implementation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceFeatures2 structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_1
         * typedef struct VkPhysicalDeviceFeatures2 {
         *     VkStructureType             sType;
         *     void*                       pNext;
         *     VkPhysicalDeviceFeatures    features;
         * } VkPhysicalDeviceFeatures2;
         * @endcode
         *
         * or the equivalent
         *
         * @code
         * // Provided by VK_KHR_get_physical_device_properties2
         * typedef VkPhysicalDeviceFeatures2 VkPhysicalDeviceFeatures2KHR;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>features is a VkPhysicalDeviceFeatures structure describing the fine-grained features of the Vulkan 1.0 API.
         * </ul><br>
         * <b>Description</b><hr><br>
         *
         * The pNext chain of this structure is used to extend the structure with features defined by extensions. This structure <b>can</b> be used in vkGetPhysicalDeviceFeatures2 or <b>can</b> be included in the pNext chain of a VkDeviceCreateInfo structure, in which case it controls which features are enabled on the device in lieu of pEnabledFeatures.
         */
        using PhysicalDeviceFeatures2 = VkPhysicalDeviceFeatures2;
        VULKANPP_CONSTEXPR PhysicalDeviceFeatures2 createPhysicalDeviceFeatures2(
                const PhysicalDeviceFeatures        &physicalDeviceFeatures,
                void                                *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                        .pNext = pNext,
                        .features = physicalDeviceFeatures
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceVulkan11Features - Structure describing the Vulkan 1.1 features that can be supported by an implementation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceVulkan11Features structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_2
         * typedef struct VkPhysicalDeviceVulkan11Features {
         *     VkStructureType    sType;
         *     void*              pNext;
         *     VkBool32           storageBuffer16BitAccess;
         *     VkBool32           uniformAndStorageBuffer16BitAccess;
         *     VkBool32           storagePushConstant16;
         *     VkBool32           storageInputOutput16;
         *     VkBool32           multiview;
         *     VkBool32           multiviewGeometryShader;
         *     VkBool32           multiviewTessellationShader;
         *     VkBool32           variablePointersStorageBuffer;
         *     VkBool32           variablePointers;
         *     VkBool32           protectedMemory;
         *     VkBool32           samplerYcbcrConversion;
         *     VkBool32           shaderDrawParameters;
         * } VkPhysicalDeviceVulkan11Features;
         * @endcode
         *
         * <b>Members</b><hr><br>
         *
         * This structure describes the following features:
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * </ul><br>
         * <b>Description</b><hr><br>
         * <ul>
         * <li>storageBuffer16BitAccess specifies whether objects in the StorageBuffer, ShaderRecordBufferKHR, or PhysicalStorageBuffer storage class with the Block decoration <b>can</b> have 16-bit integer and 16-bit floating-point members. If this feature is not enabled, 16-bit integer or 16-bit floating-point members <b>must</b> not be used in such objects. This also specifies whether shader modules <b>can</b> declare the StorageBuffer16BitAccess capability.
         * <li>uniformAndStorageBuffer16BitAccess specifies whether objects in the Uniform storage class with the Block decoration <b>can</b> have 16-bit integer and 16-bit floating-point members. If this feature is not enabled, 16-bit integer or 16-bit floating-point members <b>must</b> not be used in such objects. This also specifies whether shader modules <b>can</b> declare the UniformAndStorageBuffer16BitAccess capability.
         * <li>storagePushConstant16 specifies whether objects in the PushConstant storage class <b>can</b> have 16-bit integer and 16-bit floating-point members. If this feature is not enabled, 16-bit integer or floating-point members <b>must</b> not be used in such objects. This also specifies whether shader modules <b>can</b> declare the StoragePushConstant16 capability.
         * <li>storageInputOutput16 specifies whether objects in the Input and Output storage classes <b>can</b> have 16-bit integer and 16-bit floating-point members. If this feature is not enabled, 16-bit integer or 16-bit floating-point members <b>must</b> not be used in such objects. This also specifies whether shader modules <b>can</b> declare the StorageInputOutput16 capability.
         * <li>multiview specifies whether the implementation supports multiview rendering within a render pass. If this feature is not enabled, the view mask of each subpass <b>must</b> always be zero.
         * <li>multiviewGeometryShader specifies whether the implementation supports multiview rendering within a render pass, with geometry shaders. If this feature is not enabled, then a pipeline compiled against a subpass with a non-zero view mask <b>must</b> not include a geometry shader.
         * <li>multiviewTessellationShader specifies whether the implementation supports multiview rendering within a render pass, with tessellation shaders. If this feature is not enabled, then a pipeline compiled against a subpass with a non-zero view mask <b>must</b> not include any tessellation shaders.
         * <li>variablePointersStorageBuffer specifies whether the implementation supports the SPIR-V VariablePointersStorageBuffer capability. When this feature is not enabled, shader modules <b>must</b> not declare the SPV_KHR_variable_pointers extension or the VariablePointersStorageBuffer capability.
         * <li>variablePointers specifies whether the implementation supports the SPIR-V VariablePointers capability. When this feature is not enabled, shader modules <b>must</b> not declare the VariablePointers capability.
         * <li>protectedMemory specifies whether protected memory is supported.
         * <li>samplerYcbcrConversion specifies whether the implementation supports sampler Y′CBCR conversion. If samplerYcbcrConversion is VK_FALSE, sampler Y′CBCR conversion is not supported, and samplers using sampler Y′CBCR conversion <b>must</b> not be used.
         * <li>shaderDrawParameters specifies whether the implementation supports the SPIR-V DrawParameters capability. When this feature is not enabled, shader modules <b>must</b> not declare the SPV_KHR_shader_draw_parameters extension or the DrawParameters capability.
         * </ul>
         * If the VkPhysicalDeviceVulkan11Features structure is included in the pNext chain of the VkPhysicalDeviceFeatures2 structure passed to vkGetPhysicalDeviceFeatures2, it is filled in to indicate whether each corresponding feature is supported. VkPhysicalDeviceVulkan11Features <b>can</b> also be used in the pNext chain of VkDeviceCreateInfo to selectively enable these features.
         */
        using PhysicalDeviceVulkan11Features = VkPhysicalDeviceVulkan11Features;
        VULKANPP_CONSTEXPR PhysicalDeviceVulkan11Features createPhysicalDeviceVulkan11Features(
                const Bool32        values[12],
                void                *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
                        .pNext = pNext,
                        .storageBuffer16BitAccess = values[0],
                        .uniformAndStorageBuffer16BitAccess = values[1],
                        .storagePushConstant16 = values[2],
                        .storageInputOutput16 = values[3],
                        .multiview = values[4],
                        .multiviewGeometryShader = values[5],
                        .multiviewTessellationShader = values[6],
                        .variablePointersStorageBuffer = values[7],
                        .variablePointers = values[8],
                        .protectedMemory = values[9],
                        .samplerYcbcrConversion = values[10],
                        .shaderDrawParameters = values[11]
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceVulkan12Features - Structure describing the Vulkan 1.2 features that can be supported by an implementation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceVulkan12Features structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_2
         * typedef struct VkPhysicalDeviceVulkan12Features {
         *     VkStructureType    sType;
         *     void*              pNext;
         *     VkBool32           samplerMirrorClampToEdge;
         *     VkBool32           drawIndirectCount;
         *     VkBool32           storageBuffer8BitAccess;
         *     VkBool32           uniformAndStorageBuffer8BitAccess;
         *     VkBool32           storagePushConstant8;
         *     VkBool32           shaderBufferInt64Atomics;
         *     VkBool32           shaderSharedInt64Atomics;
         *     VkBool32           shaderFloat16;
         *     VkBool32           shaderInt8;
         *     VkBool32           descriptorIndexing;
         *     VkBool32           shaderInputAttachmentArrayDynamicIndexing;
         *     VkBool32           shaderUniformTexelBufferArrayDynamicIndexing;
         *     VkBool32           shaderStorageTexelBufferArrayDynamicIndexing;
         *     VkBool32           shaderUniformBufferArrayNonUniformIndexing;
         *     VkBool32           shaderSampledImageArrayNonUniformIndexing;
         *     VkBool32           shaderStorageBufferArrayNonUniformIndexing;
         *     VkBool32           shaderStorageImageArrayNonUniformIndexing;
         *     VkBool32           shaderInputAttachmentArrayNonUniformIndexing;
         *     VkBool32           shaderUniformTexelBufferArrayNonUniformIndexing;
         *     VkBool32           shaderStorageTexelBufferArrayNonUniformIndexing;
         *     VkBool32           descriptorBindingUniformBufferUpdateAfterBind;
         *     VkBool32           descriptorBindingSampledImageUpdateAfterBind;
         *     VkBool32           descriptorBindingStorageImageUpdateAfterBind;
         *     VkBool32           descriptorBindingStorageBufferUpdateAfterBind;
         *     VkBool32           descriptorBindingUniformTexelBufferUpdateAfterBind;
         *     VkBool32           descriptorBindingStorageTexelBufferUpdateAfterBind;
         *     VkBool32           descriptorBindingUpdateUnusedWhilePending;
         *     VkBool32           descriptorBindingPartiallyBound;
         *     VkBool32           descriptorBindingVariableDescriptorCount;
         *     VkBool32           runtimeDescriptorArray;
         *     VkBool32           samplerFilterMinmax;
         *     VkBool32           scalarBlockLayout;
         *     VkBool32           imagelessFramebuffer;
         *     VkBool32           uniformBufferStandardLayout;
         *     VkBool32           shaderSubgroupExtendedTypes;
         *     VkBool32           separateDepthStencilLayouts;
         *     VkBool32           hostQueryReset;
         *     VkBool32           timelineSemaphore;
         *     VkBool32           bufferDeviceAddress;
         *     VkBool32           bufferDeviceAddressCaptureReplay;
         *     VkBool32           bufferDeviceAddressMultiDevice;
         *     VkBool32           vulkanMemoryModel;
         *     VkBool32           vulkanMemoryModelDeviceScope;
         *     VkBool32           vulkanMemoryModelAvailabilityVisibilityChains;
         *     VkBool32           shaderOutputViewportIndex;
         *     VkBool32           shaderOutputLayer;
         *     VkBool32           subgroupBroadcastDynamicId;
         * } VkPhysicalDeviceVulkan12Features;
         * @endcode
         *
         * <b>Members</b><hr><br>
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * <li>features is a VkPhysicalDeviceFeatures structure describing the fine-grained features of the Vulkan 1.0 API.
         * </ul><br>
         * <b>Description</b><hr><br>
         * <ul>
         * <li>samplerMirrorClampToEdge indicates whether the implementation supports the VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE sampler address mode. If this feature is not enabled, the VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE sampler address <b>mode</b> must not be used.
         * <li>drawIndirectCount indicates whether the implementation supports the vkCmdDrawIndirectCount and vkCmdDrawIndexedIndirectCount functions. If this feature is not enabled, these functions <b>must</b> not be used.
         * <li>storageBuffer8BitAccess indicates whether objects in the StorageBuffer, ShaderRecordBufferKHR, or PhysicalStorageBuffer storage class with the Block decoration <b>can</b> have 8-bit integer members. If this feature is not enabled, 8-bit integer members <b>must</b> not be used in such objects. This also indicates whether shader modules <b>can</b> declare the StorageBuffer8BitAccess capability.
         * <li>uniformAndStorageBuffer8BitAccess indicates whether objects in the Uniform storage class with the Block decoration <b>can</b> have 8-bit integer members. If this feature is not enabled, 8-bit integer members <b>must</b> not be used in such objects. This also indicates whether shader modules <b>can</b> declare the UniformAndStorageBuffer8BitAccess capability.
         * <li>storagePushConstant8 indicates whether objects in the PushConstant storage class <b>can</b> have 8-bit integer members. If this feature is not enabled, 8-bit integer members <b>must</b> not be used in such objects. This also indicates whether shader modules <b>can</b> declare the StoragePushConstant8 capability.
         * <li>shaderBufferInt64Atomics indicates whether shaders <b>can</b> perform 64-bit unsigned and signed integer atomic operations on buffers.
         * <li>shaderSharedInt64Atomics indicates whether shaders <b>can</b> perform 64-bit unsigned and signed integer atomic operations on shared and payload memory.
         * <li>shaderFloat16 indicates whether 16-bit floats (halfs) are supported in shader code. This also indicates whether shader modules <b>can</b> declare the Float16 capability. However, this only enables a subset of the storage classes that SPIR-V allows for the Float16 SPIR-V capability: Declaring and using 16-bit floats in the Private, Workgroup (for non-Block variables), and Function storage classes is enabled, while declaring them in the interface storage classes (e.g., UniformConstant, Uniform, StorageBuffer, Input, Output, and PushConstant) is not enabled.
         * <li>shaderInt8 indicates whether 8-bit integers (signed and unsigned) are supported in shader code. This also indicates whether shader modules <b>can</b> declare the Int8 capability. However, this only enables a subset of the storage classes that SPIR-V allows for the Int8 SPIR-V capability: Declaring and using 8-bit integers in the Private, Workgroup (for non-Block variables), and Function storage classes is enabled, while declaring them in the interface storage classes (e.g., UniformConstant, Uniform, StorageBuffer, Input, Output, and PushConstant) is not enabled.
         * <li>descriptorIndexing indicates whether the implementation supports the minimum set of descriptor indexing features as described in the Feature Requirements section. Enabling the descriptorIndexing member when vkCreateDevice is called does not imply the other minimum descriptor indexing features are also enabled. Those other descriptor indexing features <b>must</b> be enabled individually as needed by the application.
         * <li>shaderInputAttachmentArrayDynamicIndexing indicates whether arrays of input attachments <b>can</b> be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the InputAttachmentArrayDynamicIndexing capability.
         * <li>shaderUniformTexelBufferArrayDynamicIndexing indicates whether arrays of uniform texel buffers <b>can</b> be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the UniformTexelBufferArrayDynamicIndexing capability.
         * <li>shaderStorageTexelBufferArrayDynamicIndexing indicates whether arrays of storage texel buffers <b>can</b> be indexed by dynamically uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER <b>must</b> be indexed only by constant integral expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the StorageTexelBufferArrayDynamicIndexing capability.
         * <li>shaderUniformBufferArrayNonUniformIndexing indicates whether arrays of uniform buffers <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER or VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the UniformBufferArrayNonUniformIndexing capability.
         * <li>shaderSampledImageArrayNonUniformIndexing indicates whether arrays of samplers or sampled images <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, or VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the SampledImageArrayNonUniformIndexing capability.
         * <li>shaderStorageBufferArrayNonUniformIndexing indicates whether arrays of storage buffers <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_STORAGE_BUFFER or VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the StorageBufferArrayNonUniformIndexing capability.
         * <li>shaderStorageImageArrayNonUniformIndexing indicates whether arrays of storage images <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_STORAGE_IMAGE <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the StorageImageArrayNonUniformIndexing capability.
         * <li>shaderInputAttachmentArrayNonUniformIndexing indicates whether arrays of input attachments <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the InputAttachmentArrayNonUniformIndexing capability.
         * <li>shaderUniformTexelBufferArrayNonUniformIndexing indicates whether arrays of uniform texel buffers <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the UniformTexelBufferArrayNonUniformIndexing capability.
         * <li>shaderStorageTexelBufferArrayNonUniformIndexing indicates whether arrays of storage texel buffers <b>can</b> be indexed by non-uniform integer expressions in shader code. If this feature is not enabled, resources with a descriptor type of VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER <b>must</b> not be indexed by non-uniform integer expressions when aggregated into arrays in shader code. This also indicates whether shader modules <b>can</b> declare the StorageTexelBufferArrayNonUniformIndexing capability.
         * <li>descriptorBindingUniformBufferUpdateAfterBind indicates whether the implementation supports updating uniform buffer descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER.
         * <li>descriptorBindingSampledImageUpdateAfterBind indicates whether the implementation supports updating sampled image descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, or VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE.
         * <li>descriptorBindingStorageImageUpdateAfterBind indicates whether the implementation supports updating storage image descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_STORAGE_IMAGE.
         * <li>descriptorBindingStorageBufferUpdateAfterBind indicates whether the implementation supports updating storage buffer descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_STORAGE_BUFFER.
         * <li>descriptorBindingUniformTexelBufferUpdateAfterBind indicates whether the implementation supports updating uniform texel buffer descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER.
         * <li>descriptorBindingStorageTexelBufferUpdateAfterBind indicates whether the implementation supports updating storage texel buffer descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER.
         * <li>descriptorBindingUpdateUnusedWhilePending indicates whether the implementation supports updating descriptors while the set is in use. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT <b>must</b> not be used.
         * <li>descriptorBindingPartiallyBound indicates whether the implementation supports statically using a descriptor set binding in which some descriptors are not valid. If this feature is not enabled, VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT <b>must</b> not be used.
         * <li>descriptorBindingVariableDescriptorCount indicates whether the implementation supports descriptor sets with a variable-sized last binding. If this feature is not enabled, VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT <b>must</b> not be used.
         * <li>runtimeDescriptorArray indicates whether the implementation supports the SPIR-V RuntimeDescriptorArray capability. If this feature is not enabled, descriptors <b>must</b> not be declared in runtime arrays.
         * <li>samplerFilterMinmax indicates whether the implementation supports a minimum set of required formats supporting min/max filtering as defined by the filterMinmaxSingleComponentFormats property minimum requirements. If this feature is not enabled, then VkSamplerReductionModeCreateInfo <b>must</b> only use VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE.
         * <li>scalarBlockLayout indicates that the implementation supports the layout of resource blocks in shaders using scalar alignment.
         * <li>imagelessFramebuffer indicates that the implementation supports specifying the image view for attachments at render pass begin time via VkRenderPassAttachmentBeginInfo.
         * <li>uniformBufferStandardLayout indicates that the implementation supports the same layouts for uniform buffers as for storage and other kinds of buffers. See Standard Buffer Layout.
         * <li>shaderSubgroupExtendedTypes is a boolean specifying whether subgroup operations can use 8-bit integer, 16-bit integer, 64-bit integer, 16-bit floating-point, and vectors of these types in group operations with subgroup scope, if the implementation supports the types.
         * <li>separateDepthStencilLayouts indicates whether the implementation supports a VkImageMemoryBarrier for a depth/stencil image with only one of VK_IMAGE_ASPECT_DEPTH_BIT or VK_IMAGE_ASPECT_STENCIL_BIT set, and whether VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, or VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL can be used.
         * <li>hostQueryReset indicates that the implementation supports resetting queries from the host with vkResetQueryPool.
         * <li>timelineSemaphore indicates whether semaphores created with a VkSemaphoreType of VK_SEMAPHORE_TYPE_TIMELINE are supported.
         * <li>bufferDeviceAddress indicates that the implementation supports accessing buffer memory in shaders as storage buffers via an address queried from vkGetBufferDeviceAddress.
         * <li>bufferDeviceAddressCaptureReplay indicates that the implementation supports saving and reusing buffer and device addresses, e.g. for trace capture and replay.
         * <li>bufferDeviceAddressMultiDevice indicates that the implementation supports the bufferDeviceAddress , rayTracingPipeline and rayQuery features for logical devices created with multiple physical devices. If this feature is not supported, buffer and acceleration structure addresses <b>must</b> not be queried on a logical device created with more than one physical device.
         * <li>vulkanMemoryModel indicates whether shader modules <b>can</b> declare the VulkanMemoryModel capability.
         * <li>vulkanMemoryModelDeviceScope indicates whether the Vulkan Memory Model can use Device scope synchronization. This also indicates whether shader modules <b>can</b> declare the VulkanMemoryModelDeviceScope capability.
         * <li>vulkanMemoryModelAvailabilityVisibilityChains indicates whether the Vulkan Memory Model can use availability and visibility chains with more than one element.
         * <li>shaderOutputViewportIndex indicates whether the implementation supports the ShaderViewportIndex SPIR-V capability enabling variables decorated with the ViewportIndex built-in to be exported from mesh, vertex or tessellation evaluation shaders. If this feature is not enabled, the ViewportIndex built-in decoration <b>must</b> not be used on outputs in mesh, vertex or tessellation evaluation shaders.
         * <li>shaderOutputLayer indicates whether the implementation supports the ShaderLayer SPIR-V capability enabling variables decorated with the Layer built-in to be exported from mesh, vertex or tessellation evaluation shaders. If this feature is not enabled, the Layer built-in decoration <b>must</b> not be used on outputs in mesh, vertex or tessellation evaluation shaders.
         * <li>If subgroupBroadcastDynamicId is VK_TRUE, the “Id” operand of OpGroupNonUniformBroadcast <b>can</b> be dynamically uniform within a subgroup, and the “Index” operand of OpGroupNonUniformQuadBroadcast <b>can</b> be dynamically uniform within the derivative group. If it is VK_FALSE, these operands <b>must</b> be constants.
         * </ul>
         * If the VkPhysicalDeviceVulkan12Features structure is included in the pNext chain of the VkPhysicalDeviceFeatures2 structure passed to vkGetPhysicalDeviceFeatures2, it is filled in to indicate whether each corresponding feature is supported. VkPhysicalDeviceVulkan12Features <b>can</b> also be used in the pNext chain of VkDeviceCreateInfo to selectively enable these features.
         */
        using PhysicalDeviceVulkan12Features = VkPhysicalDeviceVulkan12Features;
        VULKANPP_CONSTEXPR PhysicalDeviceVulkan12Features createPhysicalDeviceVulkan12Features(
                const Bool32        values[47],
                void                *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
                        .pNext = pNext,
                        .samplerMirrorClampToEdge = values[0],
                        .drawIndirectCount = values[1],
                        .storageBuffer8BitAccess = values[2],
                        .uniformAndStorageBuffer8BitAccess = values[3],
                        .storagePushConstant8 = values[4],
                        .shaderBufferInt64Atomics = values[5],
                        .shaderSharedInt64Atomics = values[6],
                        .shaderFloat16 = values[7],
                        .shaderInt8 = values[8],
                        .descriptorIndexing = values[9],
                        .shaderInputAttachmentArrayDynamicIndexing = values[10],
                        .shaderUniformTexelBufferArrayDynamicIndexing = values[11],
                        .shaderStorageTexelBufferArrayDynamicIndexing = values[12],
                        .shaderUniformBufferArrayNonUniformIndexing = values[13],
                        .shaderSampledImageArrayNonUniformIndexing = values[14],
                        .shaderStorageBufferArrayNonUniformIndexing = values[15],
                        .shaderStorageImageArrayNonUniformIndexing = values[16],
                        .shaderInputAttachmentArrayNonUniformIndexing = values[17],
                        .shaderUniformTexelBufferArrayNonUniformIndexing = values[18],
                        .shaderStorageTexelBufferArrayNonUniformIndexing = values[19],
                        .descriptorBindingUniformBufferUpdateAfterBind = values[20],
                        .descriptorBindingSampledImageUpdateAfterBind = values[21],
                        .descriptorBindingStorageImageUpdateAfterBind = values[22],
                        .descriptorBindingStorageBufferUpdateAfterBind = values[23],
                        .descriptorBindingUniformTexelBufferUpdateAfterBind = values[24],
                        .descriptorBindingStorageTexelBufferUpdateAfterBind = values[25],
                        .descriptorBindingUpdateUnusedWhilePending = values[26],
                        .descriptorBindingPartiallyBound = values[27],
                        .descriptorBindingVariableDescriptorCount = values[28],
                        .runtimeDescriptorArray = values[29],
                        .samplerFilterMinmax = values[30],
                        .scalarBlockLayout = values[31],
                        .imagelessFramebuffer = values[32],
                        .uniformBufferStandardLayout = values[33],
                        .shaderSubgroupExtendedTypes = values[34],
                        .separateDepthStencilLayouts = values[35],
                        .hostQueryReset = values[36],
                        .timelineSemaphore = values[37],
                        .bufferDeviceAddress = values[38],
                        .bufferDeviceAddressCaptureReplay = values[39],
                        .bufferDeviceAddressMultiDevice = values[40],
                        .vulkanMemoryModel = values[41],
                        .vulkanMemoryModelDeviceScope = values[42],
                        .vulkanMemoryModelAvailabilityVisibilityChains = values[43],
                        .shaderOutputViewportIndex = values[44],
                        .shaderOutputLayer = values[45],
                        .subgroupBroadcastDynamicId = values[46]
                };
        }

        /** <b>Name</b><hr><br>
         *
         * VkPhysicalDeviceVulkan13Features - Structure describing the Vulkan 1.3 features that can be supported by an implementation<br><br><br>
         *
         * <b>C Specification</b><hr><br>
         *
         * The VkPhysicalDeviceVulkan13Features structure is defined as:
         *
         * @code
         * // Provided by VK_VERSION_1_3
         * typedef struct VkPhysicalDeviceVulkan13Features {
         *     VkStructureType    sType;
         *     void*              pNext;
         *     VkBool32           robustImageAccess;
         *     VkBool32           inlineUniformBlock;
         *     VkBool32           descriptorBindingInlineUniformBlockUpdateAfterBind;
         *     VkBool32           pipelineCreationCacheControl;
         *     VkBool32           privateData;
         *     VkBool32           shaderDemoteToHelperInvocation;
         *     VkBool32           shaderTerminateInvocation;
         *     VkBool32           subgroupSizeControl;
         *     VkBool32           computeFullSubgroups;
         *     VkBool32           synchronization2;
         *     VkBool32           textureCompressionASTC_HDR;
         *     VkBool32           shaderZeroInitializeWorkgroupMemory;
         *     VkBool32           dynamicRendering;
         *     VkBool32           shaderIntegerDotProduct;
         *     VkBool32           maintenance4;
         * } VkPhysicalDeviceVulkan13Features;
         * @endcode
         *
         * <b>Members</b><hr><br>
         *
         * This structure describes the following features:
         * <ul>
         * <li>sType is a VkStructureType value identifying this structure.
         * <li>pNext is NULL or a pointer to a structure extending this structure.
         * </ul><br>
         * <b>Description</b><hr><br>
         * <ul>
         * <li>robustImageAccess indicates whether image accesses are tightly bounds-checked against the dimensions of the image view. Invalid texels resulting from out of bounds image loads will be replaced as described in Texel Replacement, with either (0,0,1) or (0,0,0) values inserted for missing G, B, or A components based on the format.
         * <li>inlineUniformBlock indicates whether the implementation supports inline uniform block descriptors. If this feature is not enabled, VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK <b>must</b> not be used.
         * <li>descriptorBindingInlineUniformBlockUpdateAfterBind indicates whether the implementation supports updating inline uniform block descriptors after a set is bound. If this feature is not enabled, VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT <b>must</b> not be used with VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK.
         * <li>pipelineCreationCacheControl indicates that the implementation supports:
         *     <ul>
         *     <li>The following <b>can</b> be used in Vk*PipelineCreateInfo::flags:
         *         <ul>
         *         <li>VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT
         *         <li>VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT
         *         </ul>
         *     <li>The following <b>can</b> be used in VkPipelineCacheCreateInfo::flags:
         *         <ul>
         *         <li>VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT
         *         </ul>
         *     </ul>
         * <li>privateData indicates whether the implementation supports private data. See Private Data.
         * <li>shaderDemoteToHelperInvocation indicates whether the implementation supports the SPIR-V DemoteToHelperInvocationEXT capability.
         * <li>shaderTerminateInvocation specifies whether the implementation supports SPIR-V modules that use the SPV_KHR_terminate_invocation extension.
         * <li>subgroupSizeControl indicates whether the implementation supports controlling shader subgroup sizes via the VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT flag and the VkPipelineShaderStageRequiredSubgroupSizeCreateInfo structure.
         * <li>computeFullSubgroups indicates whether the implementation supports requiring full subgroups in compute , mesh, or task shaders via the VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT flag.
         * <li>synchronization2 indicates whether the implementation supports the new set of synchronization commands introduced in VK_KHR_synchronization2.
         * <li>textureCompressionASTC_HDR indicates whether all of the ASTC HDR compressed texture formats are supported. If this feature is enabled, then the VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT and VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT features <b>must</b> be supported in optimalTilingFeatures for the following formats:
         *     <ul>
         *     <li>VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK
         *     <li>VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK
         *     </ul>
         * </ul>
         * To query for additional properties, or if the feature is not enabled, vkGetPhysicalDeviceFormatProperties and vkGetPhysicalDeviceImageFormatProperties <b>can</b> be used to check for supported properties of individual formats as normal.
         * <ul>
         * <li>shaderZeroInitializeWorkgroupMemory specifies whether the implementation supports initializing a variable in Workgroup storage class.
         * <li>dynamicRendering specifies that the implementation supports dynamic render pass instances using the vkCmdBeginRendering command.
         * <li>shaderIntegerDotProduct specifies whether shader modules <b>can</b> declare the DotProductInputAllKHR, DotProductInput4x8BitKHR, DotProductInput4x8BitPackedKHR and DotProductKHR capabilities.
         * <li>maintenance4 indicates that the implementation supports the following:
         *     <ul>
         *     <li>The application may destroy a VkPipelineLayout object immediately after using it to create another object.
         *     <li>LocalSizeId can be used as an alternative to LocalSize to specify the local workgroup size with specialization constants.
         *     <li>Images created with identical creation parameters will always have the same alignment requirements.
         *     <li>The size memory requirement of a buffer or image is never greater than that of another buffer or image created with a greater or equal size.
         *     <li>Push constants do not have to be initialized before they are dynamically accessed.
         *     <li>The interface matching rules allow a larger output vector to match with a smaller input vector, with additional values being discarded.
         *     </ul>
         * </ul>
         * If the VkPhysicalDeviceVulkan13Features structure is included in the pNext chain of the VkPhysicalDeviceFeatures2 structure passed to vkGetPhysicalDeviceFeatures2, it is filled in to indicate whether each corresponding feature is supported. VkPhysicalDeviceVulkan13Features <b>can</b> also be used in the pNext chain of VkDeviceCreateInfo to selectively enable these features.
         */
        using PhysicalDeviceVulkan13Features = VkPhysicalDeviceVulkan13Features;
        VULKANPP_CONSTEXPR PhysicalDeviceVulkan13Features createPhysicalDeviceVulkan13Features(
                const Bool32        values[15],
                void                *pNext = nullptr
        ) {
                return {
                        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
                        .pNext = pNext,
                        .robustImageAccess = values[0],
                        .inlineUniformBlock = values[1],
                        .descriptorBindingInlineUniformBlockUpdateAfterBind = values[2],
                        .pipelineCreationCacheControl = values[3],
                        .privateData = values[4],
                        .shaderDemoteToHelperInvocation = values[5],
                        .shaderTerminateInvocation = values[6],
                        .subgroupSizeControl = values[7],
                        .computeFullSubgroups = values[8],
                        .synchronization2 = values[9],
                        .textureCompressionASTC_HDR = values[10],
                        .shaderZeroInitializeWorkgroupMemory = values[11],
                        .dynamicRendering = values[12],
                        .shaderIntegerDotProduct = values[13],
                        .maintenance4 = values[14]
                };
        }

}

#endif // VULKANPP_HPP