#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "fmt/chrono.h"
#include "fmt/format.h"
#include "simdjson.h"

#include "gnutility.hpp"

namespace gnutility {
void Log::write(const std::string& str, bool err) {

  std::scoped_lock lock(mtx);

  std::ofstream logfile("log.txt", std::ofstream::app);

  logfile << fmt::format("{0:%F_%T}", std::chrono::system_clock::now());

  err ? logfile << " [ERROR] " << str << std::endl
      : logfile << " [INFO] " << str << std::endl;
}

bool Settings::createConfigFile() {

  constexpr std::string_view fd{"config.json"};

  if (std::filesystem::exists(fd))
    return true;

  constexpr std::string_view debug{"{\n \"debug\":\"test\"\n}"};

  std::ofstream o("config.json");
  o << debug << std::endl;

  o.close();

  return (std::filesystem::exists(fd));
}

std::unique_ptr<gnutility::Settings::configFile>
Settings::ParseJSON(const char* str) {

  if (auto path = std::filesystem::path(str); !std::filesystem::exists(path))
    createConfigFile();

  auto cfg = std::make_unique<configFile>();

  simdjson::ondemand::parser parser;
  simdjson::padded_string json = simdjson::padded_string::load(str);

  simdjson::ondemand::document iterator = parser.iterate(json);
  simdjson::ondemand::object object = iterator.get_object();

  for (auto&& obj : object)
    cfg->try_emplace(std::string(obj.unescaped_key().value()),
                     obj.value().get_string().value());

  return cfg;
}

const std::string* Settings::ConfigValue(const char* key) const {

  return &configMap.find(key)->second;
}

} // namespace gnutility
