cmake_minimum_required(VERSION 3.12)

function(generate_headers)
        # Parse args
        set(ONE_VALUE_ARGS OUTPUT_DIRECTORY)
        set(MULTI_VALUE_ARGS FLAGS)
        cmake_parse_arguments(ARGS "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

        if (NOT ARGS_OUTPUT_DIRECTORY)
                message(FATAL_ERROR "Missing required parameter 'ARGS_OUTPUT_DIRECTORY' "
                                    "in call to generate_headers().")
        endif ()

        # Check if python3 is installed.
        include(FindPython3)
        find_package(Python3 COMPONENTS Interpreter REQUIRED)

        # Directories
        set(DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR})

        # Not using the python found by find_package since it prefers toolchain
        # python installations, this way the one used is the one defined in the
        # environment variables.
        if (WIN32)
                set(PYTHON python)
        else ()
                set(PYTHON python3)
        endif ()

        execute_process(
                COMMAND ${CMAKE_COMMAND} -E env ${PYTHON} "${DIR}/bin/check_requirements.py"
                OUTPUT_QUIET
                ERROR_QUIET
                RESULT_VARIABLE RET
                WORKING_DIRECTORY ${DIR})

        if (NOT ${RET} EQUAL "0")
                message(FATAL_ERROR "Missing python requirement(s). Please install "
                                    "the pip modules 'bs4' and 'requests'.")
        endif ()

        execute_process(
                COMMAND ${CMAKE_COMMAND} -E env ${PYTHON} "${DIR}/generate.py" ${ARGS_OUTPUT_DIRECTORY} ${ARGS_FLAGS}
                OUTPUT_QUIET
                ERROR_VARIABLE ERROR
                RESULT_VARIABLE RET
                WORKING_DIRECTORY ${DIR})

        if (NOT ${RET} EQUAL "0")
                message(FATAL_ERROR "Error during script execution:\n${ERROR}")
        endif ()
endfunction()