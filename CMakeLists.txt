cmake_minimum_required(VERSION 3.31.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(bank_statement_converter)

set(BANK_STATEMENT_CONVERTER_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "The root-level of the Bank Statement Converter project")
set(RK_LOGGER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/RK_Logger CACHE PATH "The root-level of the RK Logger project")

file(GLOB_RECURSE MAIN_SOURCES 
    "${BANK_STATEMENT_CONVERTER_ROOT}/src/*.cpp"
    "${BANK_STATEMENT_CONVERTER_ROOT}/src/*/*.cpp"
)

# Remove subprojects from the main sources
list(FILTER MAIN_SOURCES EXCLUDE REGEX ".*src/configuration/.*")
list(FILTER MAIN_SOURCES EXCLUDE REGEX ".*src/statement_processor/.*")

add_executable(bank_statement_converter ${MAIN_SOURCES})

# Get the actual executable output directory
# Fix: This sometimes gets the "build" directory instead of the actual executable directory
get_target_property(BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY bank_statement_converter RUNTIME_OUTPUT_DIRECTORY)
if(NOT BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY)
    set(BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

# This is just for sharing the includes and definitions between the main project and subprojects
add_library(bank_statement_includes INTERFACE)
target_include_directories(bank_statement_includes INTERFACE 
    ${BANK_STATEMENT_CONVERTER_ROOT}/include
    ${RK_LOGGER_SOURCE_DIR}/include
)
target_compile_definitions(bank_statement_includes INTERFACE 
    BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY="${BANK_STATEMENT_CONVERTER_BINARY_DIRECTORY}"
)

target_link_libraries(bank_statement_converter PRIVATE bank_statement_includes rk_logger configuration statement_processor)

add_subdirectory(${RK_LOGGER_SOURCE_DIR})
add_subdirectory(${BANK_STATEMENT_CONVERTER_ROOT}/src/configuration)
add_subdirectory(${BANK_STATEMENT_CONVERTER_ROOT}/src/statement_processor)
