#include <iostream>
#include <chrono>
#include <fstream>
#include "fmt/format.h"
#include "fmt/chrono.h"

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

}
