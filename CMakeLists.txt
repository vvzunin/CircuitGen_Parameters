cmake_minimum_required(VERSION 3.21)

project("OptimizationsVerilogLib"
    VERSION 1.0.0
    LANGUAGES CXX
)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/optimization_utils/AbcUtils.cpp
        src/optimization_utils/YosysUtils.cpp
        src/private_headers/UtilsCommands.hpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
    include/AbcUtils.hpp
    include/YosysUtils.hpp
    include/StandartUtils.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

add_library(
    ${PROJECT_NAME}
)
add_library(OptimizationsVerilog::OptimizationsVerilog ALIAS ${PROJECT_NAME})
