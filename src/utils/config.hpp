#include <filesystem>

struct Settings
{
    struct _Window
    {
        unsigned int Height = 0;
        unsigned int Width = 0;
        unsigned int FPS = 0;
        std::string Title = "";
    } Window;
};

class AppConfig
{
   private:
    static Settings mSettings;

   public:
    AppConfig(/* args */);
    ~AppConfig();
    static void parseFile(const std::filesystem::path&);

    Settings& GetSettings();
};
