project(statement_processor)

set(PDFIUM_DIR "${BANK_STATEMENT_CONVERTER_ROOT}/external/pdfium_binaries/140.0.7281.0_chromium-7281/pdfium-win-x64")

# Create PDFium import target manually
add_library(PDFium::PDFium STATIC IMPORTED)
set_target_properties(PDFium::PDFium PROPERTIES
    IMPORTED_LOCATION "${PDFIUM_DIR}/lib/pdfium.dll.lib"  # Use the actual filename
    INTERFACE_INCLUDE_DIRECTORIES "${PDFIUM_DIR}/include"
)

file(GLOB STATEMENT_PROCESSOR_SOURCES "*.cpp")
add_library(statement_processor STATIC ${STATEMENT_PROCESSOR_SOURCES})

target_link_libraries(statement_processor PRIVATE bank_statement_includes rk_logger PDFium::PDFium)

target_include_directories(statement_processor PRIVATE "${PDFIUM_DIR}/include")

# Copy PDFium DLL to executable directory
add_custom_command(
    TARGET statement_processor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PDFIUM_DIR}/bin/pdfium.dll"
        $<TARGET_FILE_DIR:bank_statement_converter>
)
