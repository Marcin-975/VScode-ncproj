#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <rapidjson/document.h>

#include <GeneralParserDefines.h>

#include "CodesReader.h"
#include "NCParser.h"

namespace nclangsrv {

class NCSettingsReader;
class JsonMessageHandler
{
public:
    JsonMessageHandler(std::ofstream* logger, const std::string& rootPath, NCSettingsReader& ncSettingsReader,
                       parser::ELanguage language = parser::ELanguage::English);

    bool parse(const std::string& json);
    bool exit() const
    {
        return mExit;
    }

private:
    void initialize(int32_t id);
    void initialized();
    void workspace_didChangeConfiguration(const rapidjson::Document& request);
    void textDocument_didOpen(const rapidjson::Document& request);
    void textDocument_didChange(const rapidjson::Document& request);
    void textDocument_didClose(const rapidjson::Document& request);
    void textDocument_completion(int32_t id);
    void completionItem_resolve(const rapidjson::Document& request);
    void textDocument_hover(const rapidjson::Document& request);
    void cancelRequest();
    void shutdown(int32_t id);
    void textDocument_publishDiagnostics(const std::string& uri, const std::string& content);

    void fetch_gCodesDesc();
    void fetch_mCodesDesc();

    struct FileContext
    {
        std::vector<std::string> contenLines;
        parser::fanuc::macro_map macroMap;
    };

private:
    std::map<std::string, FileContext> mFileContexts;
    std::vector<std::string>           mSuggestions;
    std::ofstream*                     mLogger;
    std::unique_ptr<CodesReader>       mGCodes;
    std::unique_ptr<CodesReader>       mMCodes;
    std::string                        mRootPath;
    NCSettingsReader&                  mNcSettingsReader;
    NCParser                           mParser;
    parser::ELanguage                  mLanguage;
    bool                               mExit{};
};

} // namespace nclangsrv