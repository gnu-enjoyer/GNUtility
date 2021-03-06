#include <iostream>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

#include "fmt/format.h"
#include "fmt/chrono.h"
#include "simdjson.h"

#include "gnutility.hpp"

namespace gnutility
{
    void Log::write(const std::string& str, bool err ) const {

        std::scoped_lock lock(mtx);

        std::ofstream logfile("log.txt", std::ofstream::app);

        logfile << fmt::format("{0:%F_%T}", std::chrono::system_clock::now());

        err ? logfile << " [ERROR] " << str << std::endl : logfile << " [INFO] " << str << std::endl;

    }    

    bool Settings::createConfigFile() {

        const char fd[32] = "config.json";

        if(std::filesystem::exists(fd)) return true;

        const char debug[32] = {
                "{\n \"debug\":\"test\"\n}"
        };

        std::ofstream o("config.json");        
        o << debug << std::endl;

        o.close();

        return (std::filesystem::exists(fd));

    }

    void Settings::ParseJSON(const char *str, configFile *cfg) {

        if (auto path = std::filesystem::path(str); !std::filesystem::exists(path))
            createConfigFile();

        simdjson::ondemand::parser parser;
        simdjson::padded_string json = simdjson::padded_string::load(str);

        simdjson::ondemand::document iterator = parser.iterate(json);
        simdjson::ondemand::object object = iterator.get_object();

        for (auto &&obj: object)
            cfg->try_emplace(std::string(obj.unescaped_key().value()),
                             obj.value().get_string().value());

    }

    Settings::Settings(const char* str) {

        std::cout << "Settings instance loaded at: " << this;

        ParseJSON(str, &this->configMap);

    }

    const std::string* Settings::ConfigValue(const char *key) const {

        return &configMap.find(key)->second;

    }

}
