cmake_minimum_required(VERSION 3.5)

function(generate_headers)
        # Parse args
        set(ONE_VALUE_ARGS OUTPUT_DIRECTORY)
        set(MULTI_VALUE_ARGS FLAGS)
        cmake_parse_arguments(ARGS "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

        # Directories
        set(BIN_DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR})

        if (EXISTS "${ARGS_OUTPUT_DIRECTORY}/vulkan")
                message(STATUS "Vulkan headers output location already exists. Not generating headers.")
                return()
        endif ()

        # Run script at configuration time
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E env python ${BIN_DIR}/generate.py ${ARGS_OUTPUT_DIRECTORY} ${ARGS_FLAGS}
                WORKING_DIRECTORY ${BIN_DIR}
        )
endfunction()