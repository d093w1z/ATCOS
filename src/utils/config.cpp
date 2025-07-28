#include "config.hpp"

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <toml++/toml.hpp>
AppConfig::AppConfig(/* args */)
{
    toml::table tbl;
    try
    {
        tbl = toml::parse_file("configuration.toml");
    }
    catch (const toml::parse_error& err)
    {
        // std::cerr << "Error parsing file '" << \* err.source().path << "':\n"
        //           << err.description() << "\n (" << err.source().begin << ")\n";
    }
}

AppConfig::~AppConfig() {}

void AppConfig::parseFile(const std::filesystem::path& filePath)
{
    return;
}
