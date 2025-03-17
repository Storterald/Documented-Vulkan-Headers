cmake_minimum_required(VERSION 3.15)

function(generate_headers)
        # Parse args
        set(ONE_VALUE_ARGS OUTPUT_DIRECTORY)
        set(MULTI_VALUE_ARGS FLAGS)
        cmake_parse_arguments(ARGS "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

        if (NOT ARGS_OUTPUT_DIRECTORY)
                message(FATAL_ERROR "Missing required parameter 'ARGS_OUTPUT_DIRECTORY' "
                                    "in call to generate_headers().")
        endif ()

        if (NOT DEFINED Python3_FIND_REGISTRY)
                set(Python3_FIND_REGISTRY LAST)  # Prefer the python in the environment
        endif ()

        if (NOT DEFINED Python3_FIND_STRATEGY)
                set(Python3_FIND_STRATEGY VERSION)  # Find the latest python
        endif ()

        # Check if python3 is installed.
        include(FindPython3)
        find_package(Python3 COMPONENTS Interpreter REQUIRED)

        # Directories
        set(DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR})

        execute_process(
                COMMAND ${Python3_EXECUTABLE} "${DIR}/bin/check_requirements.py"
                OUTPUT_QUIET
                ERROR_QUIET
                RESULT_VARIABLE RET
                WORKING_DIRECTORY ${DIR})

        if (NOT ${RET} EQUAL "0")
                message(FATAL_ERROR "Missing python requirement(s). Please install "
                                    "the pip modules 'bs4' and 'requests'.")
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
endfunction()