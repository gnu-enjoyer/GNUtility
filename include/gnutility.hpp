#ifndef GNUTILITY_PUBLIC_H
#define GNUTILITY_PUBLIC_H

#include <iosfwd>
#include <string>
#include <mutex>
#include <unordered_map>

namespace gnutility {

    class Log {

        mutable std::mutex mtx;

    public:   

        /// Writes to log.txt
        /// \param [in] in Text to be written
        /// \param [in] err Format as [ERROR] or [INFO]
        void write(const std::string& str, bool err = false) const;

    };

    class Settings {

        typedef std::unordered_map<std::string, std::string> configFile;

        mutable configFile configMap;

        static bool createConfigFile();

        static void ParseJSON(const char *str, configFile *cfg);

    public:
        /// Queries the config file by key
        /// \param [in] key name to query
        /// \return const ptr to the value
        const std::string* ConfigValue(const char *key) const;

        ///  Parses a JSON file into memory
        /// \param str Name of JSON file to load
        explicit Settings(const char *str);

    ~Settings() = default;
};

    inline Settings const Cfg("config.json");

    inline Log const Logger;

} // namespace gnutility

#endif // GNUTILITY_PUBLIC_H
