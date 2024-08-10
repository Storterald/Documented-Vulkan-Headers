# Vulkan With Documentation

Wrappers for the `vulkan.h` header. ***Incompatible*** with the `vulkan.hpp` header (throws compile time error).

### Contents

`vulkan++H.hpp` header file: contains documentation written in `HTML`.

`vulkan++M.hpp` header file: contains documentation written in `MARKDOWN`.

### Include vulkan

To include vulkan **VULKANPP_INCLUDE_VULKAN** must be defined:

In the `C++` file:
```cpp
    #define VULKANPP_INCLUDE_VULKAN
    #include <vulkan/vulkan++.hpp>
```
Or in the `CMake` file *(recommended)*:
```cmake
    target_compile_definitions(${PROJECT_NAME} PRIVATE VULKANPP_INCLUDE_VULKAN)
    target_include_directories(${PROJECT_NAME} PRIVATE ${VK_DOC_PATH}/include/)
```

### Manually generating the headers

Both files can be generated via the python script located in `bin/generate.py`. The output will be an **HTML** formatted
file by default, if the script is run with the `M` flag, the output will be a **MARKDOWN** formatted file.

The python script can also be executed with the `CMakeLists.txt` cmake file.

This is an example `CMAKE` code that automatically downloads and generates the headers at configuration time using the
`ExternalProject` cmake library:

```cmake
set(VK_DOC_PATH ${CMAKE_HOME_DIRECTORY}/docs) # Where the library is stored
set(VK_DOC_NAME vk_doc) # The name of the library

# This fetches the latest release
include(ExternalProject)
ExternalProject_Add(${VK_DOC_NAME}
    # The URL to the latest release
    URL "https://github.com/Storterald/VulkanWithDocumentation/releases/latest/download/source.tar.gz"

    # Where the library is stored
    PREFIX ${VK_DOC_PATH}

    CMAKE_ARGS
        # Where the library is installed, this is where the include/vulkan/vulkan++.hpp
        # directory and header will be placed
        -DCMAKE_INSTALL_PREFIX:PATH=${VK_DOC_PATH}
        # Optional. Set 'VULKAN_WITH_DOC_FLAGS' with the arguments for the python script.
        -DVULKAN_WITH_DOC_FLAGS="M"
)

# Generate before project build
add_dependencies(${PROJECT_NAME} ${VK_DOC_NAME})

# Include the generated header. The path is the 'PREFIX' parameter + "/include/"
# The header will be available with #include <vulkan/vulkan++.hpp>
target_include_directories(${PROJECT_NAME} PRIVATE ${VK_DOC_PATH}/include/)
```