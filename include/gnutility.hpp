#ifndef GNUTILITY_PUBLIC_H
#define GNUTILITY_PUBLIC_H

#include <iosfwd>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace gnutility {

class Log {

  static inline std::mutex mtx;

public:
  /// Writes to log.txt
  /// \param [in] in Text to be written
  /// \param [in] err Format as [ERROR] or [INFO]
  static void write(const std::string& str, bool err = false);
};

class Settings {
public:
  typedef std::unordered_map<std::string, std::string> configFile;

  mutable configFile configMap;

  static bool createConfigFile();

  /// Queries the config file by key
  /// \param [in] key name to query
  /// \return const ptr to the value
  const std::string* ConfigValue(const char* key) const;

  ///  Parses a JSON file into memory
  /// \param str Name of JSON file to load
  /// \return unique ptr to the cfg file
  static std::unique_ptr<gnutility::Settings::configFile>
  ParseJSON(const char* str);
};

} // namespace gnutility

#endif // GNUTILITY_PUBLIC_H
