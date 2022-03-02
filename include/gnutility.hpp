#ifndef GNUTILITY_PUBLIC_H
#define GNUTILITY_PUBLIC_H

#include <unordered_map>
#include <string>
#include <iosfwd>

namespace gnutility
{
    class Logger {

            Logger();

            ~Logger() = default;

            Logger(const Logger &) = delete;

            Logger &operator=(const Logger &) = delete;

            std::ofstream *logfile;

        public:

            static Logger &get();

            /// Writes to log.txt
            /// \param [in] in Text to be written
            /// \param [in] err Format as [ERROR] or [INFO]
            void write(const char *in, bool err = false);
    };


    class Settings{

        typedef std::unordered_map<std::string, std::string> configFile;

        mutable configFile configMap;

        static bool createConfigFile();

        static void ParseJSON(const char* str, configFile* cfg);

    public:

        /// Queries the config file by key
        /// \param [in] key name to query
        /// \return const ref. to the value
        const std::string* ConfigValue(const char* key) const;


        ///  Parses a JSON file into memory
        /// \param str Name of JSON file to load
        explicit Settings(const char *str);

        ~Settings() = default;

    };

    inline Settings const Cfg("config.json");
}

#endif // GNUTILITY_PUBLIC_H
