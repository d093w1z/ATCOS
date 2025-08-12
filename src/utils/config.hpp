#pragma once
#include <filesystem>

namespace Defaults
{
constexpr unsigned int WIDTH = 1920u;
constexpr unsigned int HEIGHT = 1080u;
constexpr unsigned int FPS = 60;
constexpr const char* TITLE = "ATCOS Game";
};  // namespace Defaults

struct Settings
{
    struct _Window
    {
        unsigned int Height = 0;
        unsigned int Width = 0;
        unsigned int FPS = 0;
        int PositionX;
        int PositionY;
        std::string Title = "";
    } Window;
};

class AppConfig
{
   private:
    static Settings mSettings;

   public:
    AppConfig(/* args */) = default;
    ~AppConfig() = default;
    static void parseFile(const std::filesystem::path&);

    Settings& GetSettings();
};
