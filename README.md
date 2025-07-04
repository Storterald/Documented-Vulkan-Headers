# Documented Vulkan Headers

> 🔴**IMPORTANT**🔴<br>
> **Python** `3.12` is **required** (mainly due to [**PEP 701**](https://docs.python.org/3/whatsnew/3.12.html#whatsnew312-pep701)).

Automatically generated headers meant to *replace* the original Vulkan headers with
***documentation*** added to every `definition`, `function`, `struct`, `enum`, `flag`,
`handle` and `typedef` with an available description in the
[Vulkan Registry](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/).

Everything has the original Vulkan generated signature and can be used with the ***default*** vulkan library.
The script fetches the [Vulkan Headers](https://github.com/KhronosGroup/Vulkan-Headers) and the
[Vulkan Registry](https://github.com/KhronosGroup/Vulkan-Registry) using **git**.

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

#### Required Arguments
 - `output_path` Where the **vulkan/** and **vk_video/** directories will be put.

#### Optional Arguments
 - `-S`, `--style` The documentation style.
 - `-V`, `--version` The vulkan headers version to clone (must be a **valid git tag**).

#### Boolean Flags
 - `-N`, `--namespace` If the script should generate a *namespace* alias, like shown above.
 - `-F`, `--force` Forces the script to **regenerate** the headers.

#### Style Flags

`-S`, `--style` Flag options:
 - `CL` **CLion** styled documentation.
 - `RS` **ReSharper** *(Visual Studio Extension)* styled documentation.
 - `VSC` **Visual Studio Code** styled documentation.
 - `TXT` **Plain text** documentation.

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

## CMake Vulkan-Loader support

If the [Vulkan-Loader](https://github.com/KhronosGroup/Vulkan-Loader) library is
**built** together with the headers, `DEFINE_VULKAN_TARGET ON` should be passed
to the `generate_headers` function, this will define the `Vulkan::Headers` target
**required** by the **loader**.
