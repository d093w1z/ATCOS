#include <filesystem>

class AppConfig
{
   private:
   public:
    AppConfig(/* args */);
    ~AppConfig();
    void parseFile(const std::filesystem::path&);
};
