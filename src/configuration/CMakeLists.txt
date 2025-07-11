file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(configuration STATIC ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(configuration PUBLIC yaml-cpp::yaml-cpp bank_statement_includes)
target_include_directories(configuration PUBLIC ${yaml-cpp_SOURCE_DIR}/include)

add_custom_command(TARGET configuration POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/config.yaml"
            "$<TARGET_FILE_DIR:bank_statement_converter>/config.yaml"
)
