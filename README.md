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
# Include ExternalProject
include(ExternalProject)

# Fetch latest release
ExternalProject_Add(vulkanWithDocumentation
    URL "https://github.com/Storterald/VulkanWithDocumentation/releases/latest/download/source.tar.gz"
    CMAKE_ARGS
        -DVULKAN_WITH_DOC_FLAGS="M" # Generate the markdown documentation
)

# Generate before project build
add_dependencies(${PROJECT_NAME} vulkanWithDocumentation)
```