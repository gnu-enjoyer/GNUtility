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
    void Logger::write(const char *in, bool err) {

            *logfile << fmt::format("{0:%F_%T}",
                                    std::chrono::system_clock::now());

            err ? *logfile << " [ERROR] " << in << std::endl : *logfile << " [INFO] " << in << std::endl;

    }

    Logger &Logger::get() {
        static Logger instance;
        //volatile int dummy{};
        return instance;
    }

    Logger::Logger() {

        logfile = new std::ofstream("log.txt", std::fstream::app);

    }

    bool Settings::createConfigFile() {

        const char fd[32] = "config.json";

        if(std::filesystem::exists(fd)) return true;

        const char debug[32] = {
                "{\n \"debug\":\"test\"\n}"
        };

        //if(std::filesystem::exists(fd))
        //    std::remove(fd);

        std::ofstream o("config.json");
        o << debug << std::endl;

        o.close();

        if(std::filesystem::exists(fd))
            return true;

        return false;

    }

    void Settings::ParseJSON(const char *str, configFile *cfg) {

        if (auto path = std::filesystem::path(str); !std::filesystem::exists(path))
            assert(createConfigFile());

        simdjson::ondemand::parser parser;
        simdjson::padded_string json = simdjson::padded_string::load(str);

        simdjson::ondemand::document iterator = parser.iterate(json);
        simdjson::ondemand::object object = iterator.get_object();

        for (auto &&obj: object) {

            cfg->try_emplace(std::string(obj.unescaped_key().value()),
                             obj.value().get_string().value());
        }
    }

    Settings::Settings(const char* str) {

        std::cout << "Settings instance loaded at: " << this;

        ParseJSON(str, &this->configMap);

    }

    const std::string* Settings::ConfigValue(const char *key) const {

        return &configMap.find(key)->second;

    }

}
