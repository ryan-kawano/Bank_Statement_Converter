#include <string>
#include <vector>
#include <sstream>

#include <bank_statement_converter/statement_processor/pdf_statement_processor.h>
#include <bank_statement_converter/statement/wells_fargo_statement.h>
#include <rk_logger/logger.h>
#include <bank_statement_converter/utility.h>
#include <bank_statement_converter/constants.h>
#include <bank_statement_converter/interfaces/i_statement_processor.h>
#include <bank_statement_converter/statement_processor./statement_processor_factory.h>

namespace bsc {

std::shared_ptr<IStatement> PdfStatementProcessor::processFile(const std::filesystem::path& path) {
    RK_LOG("Processing PDF file: ", path.string(), "\n");

    FPDF_DOCUMENT doc = openFile(path);
    if (!doc) {
        RK_LOG("Failed to open PDF file\n");
        return nullptr;
    }

    int page_count = FPDF_GetPageCount(doc);
    RK_LOG("Total pages: ", page_count, "\n");

    IStatementFileProcessor::StatementLines lines;
    bsc::constants::Bank bank = bsc::constants::Bank::UNKNOWN;

    for (int i = 0; i < page_count; i++) {
      RK_LOG("Processing pdf page ", i, "\n");

      FPDF_PAGE pdf_page = FPDF_LoadPage(doc, i);
      if (pdf_page == NULL) {
          RK_LOG("Failed to load PDF page\n");
          return nullptr;
      }

      // Extract text from the page
      FPDF_TEXTPAGE text_page = FPDFText_LoadPage(pdf_page);
      if (!text_page) {
          RK_LOG("Failed to load text page\n");
          FPDF_ClosePage(pdf_page);
          return nullptr;
      }

      int char_count = FPDFText_CountChars(text_page);
      if (char_count > 0) {
          std::vector<unsigned short> buffer(char_count + 1, 0); // UTF-16LE
          FPDFText_GetText(text_page, 0, char_count, buffer.data());
          std::wstring wtext(buffer.begin(), buffer.end() - 1); // Remove null terminator
          // Convert to UTF-8 for logging
          std::string text;
          text.reserve(wtext.size());
          for (wchar_t wc : wtext) {
              if (wc < 0x80) text += static_cast<char>(wc);
              else text += '?'; // Simple conversion for demo
          }
          // Split into lines and store in a vector
          
          std::istringstream iss(text);
          std::string line;
          while (std::getline(iss, line)) {
            line = bsc::utility::trim(line);
            lines[i].push_back(line);
            RK_LOG("Page ", i, ": ", line, "\n");
          }
      }

      FPDFText_ClosePage(text_page);
      FPDF_ClosePage(pdf_page);
    }

    if (lines.empty()) {
        RK_LOG("No text extracted from PDF\n");
        FPDF_CloseDocument(doc);
        FPDF_DestroyLibrary();
        return nullptr;
    }

    for (const auto& pair : lines) {
        for (const auto& line : pair.second) {
            if (line.find("Wells Fargo") != std::string::npos) {
                bank = bsc::constants::Bank::WELLS_FARGO;
                RK_LOG("Identified bank as Wells Fargo\n");
                break;
            }
        }
    }

    if (bank == bsc::constants::Bank::UNKNOWN) {
        RK_LOG("Could not identify bank from PDF content\n");
        FPDF_CloseDocument(doc);
        FPDF_DestroyLibrary();
        return nullptr;
    }

    std::shared_ptr<IStatement> statement;
    switch (bank) {
        case bsc::constants::Bank::WELLS_FARGO:
            statement = std::make_shared<WellsFargoStatement>();
            break;
        // Add more cases for other banks as needed
        // case bsc::constants::Bank::CHASE:
        //     statement = std::make_shared<ChaseStatement>();
        //     break;
        default:
            RK_LOG("Unsupported bank type\n");
            FPDF_CloseDocument(doc);
            FPDF_DestroyLibrary();
            return nullptr;
    }

    StatementProcessorFactory::createStatementProcessor(bank)->processLines(statement, lines);

    FPDF_CloseDocument(doc);
    FPDF_DestroyLibrary();

    return statement;
}

FPDF_DOCUMENT PdfStatementProcessor::openFile(const std::filesystem::path& path) const {
    FPDF_LIBRARY_CONFIG config;
    config.version = 2;
    config.m_pUserFontPaths = NULL;
    config.m_pIsolate = NULL;
    config.m_v8EmbedderSlot = 0;
  
    FPDF_InitLibraryWithConfig(&config);
    FPDF_DOCUMENT doc = FPDF_LoadDocument(path.string().c_str(), nullptr);
    if (!doc) {
      return nullptr;
    }

    return doc;
}

} // namespace bsc
