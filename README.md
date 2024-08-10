# Vulkan With Documentation

Wrappers for the `vulkan.h` header. ***Incompatible*** with the `vulkan.hpp` header (throws compile time error).

### Contents

`vulkan++.hpp` header file: contains documentation written in `HTML`.

`vulkan++M.hpp` header file: contains documentation written in `MARKDOWN`.

### Manually generating the headers

Both files can be generated via the python script located in `bin/generate.py`. The output will be an **HTML** formatted
file by default, if the script is run with the `-M` flag, the output will be a **MARKDOWN** formatted file.

The python script can also be executed with the `CMakeLists.txt` cmake file.
Example `CMAKE` code to automatically download and generate the headers:

```cmake
set(VK_DOC_PATH ${CMAKE_HOME_DIRECTORY}/docs) # Where the library is stored
set(VK_DOC_NAME vk_doc) # The name of the library

# This fetches the latest release
include(ExternalProject)
ExternalProject_Add(${VK_DOC_NAME}
    # The URL to the latest release
    URL "https://github.com/Storterald/VulkanWithDocumentation/releases/latest/download/source.tar.gz"
    
    # Important! Won't compile if missing
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "Skipping install step."

    # Where the library is stored    
    PREFIX ${VK_DOC_PATH}
        
    # Optional. Set 'VULKAN_WITH_DOC_FLAGS' with the arguments to pass to the python script.
    CMAKE_ARGS
        -DVULKAN_WITH_DOC_FLAGS="M"
)

# Generate before project build
add_dependencies(${PROJECT_NAME} ${VK_DOC_NAME})

# Include the generated header. The path is the 'PREFIX' parameter + the library name + the header name
target_include_directories(${PROJECT_NAME} PRIVATE ${VK_DOC_PATH}/${VK_DOC_NAME}/vulkan++-M.hpp)
```