# Vulkan With Documentation

Automatically generated headers meant to *replace* the original Vulkan headers with ***documentation*** added to 
every `function`, `struct`, `enum`, `flag`, `handle` and `typedef`. 

Everything has the original Vulkan generated signature and can be used with the ***default*** vulkan library.

The script fetches the [Vulkan Header](https://github.com/KhronosGroup/Vulkan-Headers) using **git**.

The `generate.py` script can be run with the `-N` **flag** to generate an alias in the namespace `vk`. 
This is what an alias may look like:

```c++
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCommandPool)
namespace vk {
        /** Full documentation
         */
        using CommandPool = VkCommandPool;
}
```

## Script arguments

Required Arguments
 : `output path` The first script argument **must** be the output directory where the `vulkan` and `vk_video` folder
   will be generated.

Style Flags
 : `-CL` Generates the vulkan headers with **CLion** styled documentation. *DEFAULT*
 : `-RS` Generates the vulkan headers with **ReSharper** *(Visual Studio Extension)* styled documentation.
 : `-VS` Generates the vulkan headers with **Visual Studio** styled documentation.

Boolean Flags
 : `-N` If the script should generate a *namespace* alias, like shown above. *DEFAULT=FALSE*

## CMake integration

Along the python script, a `generate.cmake` file is provided, with the function `generate_headers`.
These are the arguments of the function:

```cmake
include(generate.cmake)

# Important! The flags must be a list, not a string:
# This is valid: set(YOUR_FLAGS_HERE -CL -N)
# This is not: set(YOUR_FLAGS_HERE "-CL -N")
generate_headers(
        OUTPUT_DIRECTORY ${YOUR_DIRECTORY_HERE}
        # Flags is a multi-argument parameter, it's not necessary to
        # declare a list outside the function call
        FLAGS ${YOUR_FLAGS_HERE}
)
```
