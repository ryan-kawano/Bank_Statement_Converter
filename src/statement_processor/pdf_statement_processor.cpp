#include <bank_statement_converter/statement_processor/pdf_statement_processor.h>
#include <bank_statement_converter/statement/wells_fargo_statement.h>
#include <fpdfview.h>
#include <rk_logger/logger.h>

std::shared_ptr<IStatement> PdfStatementProcessor::processFile(const std::filesystem::path& path) {
    RK_LOG("Processing PDF file: ", path.string(), "\n");

    FPDF_LIBRARY_CONFIG config;
    config.version = 2;
    config.m_pUserFontPaths = NULL;
    config.m_pIsolate = NULL;
    config.m_v8EmbedderSlot = 0;
  
    FPDF_InitLibraryWithConfig(&config);
  
    std::shared_ptr<IStatement> statement = std::make_shared<WellsFargoStatement>();

    // FPDF_DOCUMENT doc = FPDF_LoadDocument(path.string().c_str(), nullptr);
    // if (!doc) {
    //     RK_LOG("Failed to load PDF document\n");
    //     return nullptr;
    // }

    // FPDF_CloseDocument(doc);

    FPDF_DestroyLibrary();
    return statement;
}

void PdfStatementProcessor::openFile(const std::filesystem::path&) const {
}
