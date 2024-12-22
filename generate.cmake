cmake_minimum_required(VERSION 3.12)

function(generate_headers)
        # Parse args
        set(ONE_VALUE_ARGS OUTPUT_DIRECTORY)
        set(MULTI_VALUE_ARGS FLAGS)
        cmake_parse_arguments(ARGS "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

        # Check if python3 is installed.
        include(FindPython3)
        find_package(Python3 COMPONENTS Interpreter REQUIRED)
        get_filename_component(PYTHON ${Python3_EXECUTABLE} NAME)

        # Directories
        set(BIN_DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR})

        # Run script at configuration time
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E env ${PYTHON} "${BIN_DIR}/generate.py" ${ARGS_OUTPUT_DIRECTORY} ${ARGS_FLAGS}
                WORKING_DIRECTORY ${BIN_DIR})
endfunction()