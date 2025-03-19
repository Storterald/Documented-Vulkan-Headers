cmake_minimum_required(VERSION 3.15)

function(generate_headers)
        # Parse args
        set(ONE_VALUE_ARGS OUTPUT_DIRECTORY DEFINE_VULKAN_TARGET)
        set(MULTI_VALUE_ARGS FLAGS)
        cmake_parse_arguments(ARGS "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

        if (NOT ARGS_OUTPUT_DIRECTORY)
                message(FATAL_ERROR "Missing required parameter 'ARGS_OUTPUT_DIRECTORY' "
                                    "in call to generate_headers().")
        endif ()

        set(DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR})

        # Check if python3 is installed.
        include(FindPython3)
        find_package(Python3 COMPONENTS Interpreter REQUIRED)

        execute_process(
                COMMAND ${Python3_EXECUTABLE} "${DIR}/bin/check_requirements.py"
                OUTPUT_QUIET
                ERROR_VARIABLE ERROR
                RESULT_VARIABLE RET
                WORKING_DIRECTORY ${DIR})

        if (NOT ${RET} EQUAL "0")
                string(REGEX MATCH "ImportError: ([^\n ]+)" MISSING_REQUIREMENT ${ERROR})
                set(MISSING_REQUIREMENT "${CMAKE_MATCH_1}")
                message(FATAL_ERROR "Missing python requirement: '${MISSING_REQUIREMENT}'")
        endif ()

        execute_process(
                COMMAND ${Python3_EXECUTABLE} "${DIR}/generate.py" ${ARGS_OUTPUT_DIRECTORY} ${ARGS_FLAGS}
                OUTPUT_QUIET
                ERROR_VARIABLE ERROR
                RESULT_VARIABLE RET
                WORKING_DIRECTORY ${DIR})

        if (NOT ${RET} EQUAL "0")
                message(FATAL_ERROR "Error during script execution:\n${ERROR}")
        endif ()

        # For compatibility with the Vulkan Loader, add the possibility of defining
        # the Vulkan::Headers target, required by Vulkan::Loader.
        if (ARGS_DEFINE_VULKAN_TARGET)
                add_library(DocumentedVulkanHeaders INTERFACE)
                add_library(Vulkan::Headers ALIAS DocumentedVulkanHeaders)
                target_include_directories(DocumentedVulkanHeaders INTERFACE "${DIR}/include")
        endif ()
endfunction()