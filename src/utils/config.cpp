#include "config.hpp"
#include <string>
#include <toml++/toml.hpp>
#include "log.hpp"

Settings AppConfig::mSettings;

AppConfig::AppConfig(/* args */) {}

AppConfig::~AppConfig() {}

Settings& AppConfig::GetSettings()
{
    return mSettings;
}

void AppConfig::parseFile(const std::filesystem::path& filePath)
{
    toml::table tbl;
    try
    {
        tbl = toml::parse_file(filePath.c_str());
        ATCOS_LIB_INFO("Configuration loaded: {}", filePath.string());
    }
    catch (const toml::parse_error& err)
    {
        ATCOS_LIB_ERROR("Error parsing file '{}':\n{}\n--> line {}, column {}", *err.source().path,
                        err.description(), err.source().begin.line, err.source().begin.column);
    }
    mSettings.Window.Title = tbl["Window"]["Title"].value_or("ATCOS Game");
    mSettings.Window.Height = tbl["Window"]["Height"].value_or(1080u);
    mSettings.Window.Width = tbl["Window"]["Width"].value_or(1920u);
    mSettings.Window.FPS = tbl["Window"]["FPS"].value_or(144);

    mSettings.Window.PositionX = tbl["Window"]["PositionX"].value_or(0);
    mSettings.Window.PositionY = tbl["Window"]["PositionY"].value_or(0);

    return;
}
