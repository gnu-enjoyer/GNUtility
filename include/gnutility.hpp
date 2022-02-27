#ifndef GNUTILITY_PUBLIC_H
#define GNUTILITY_PUBLIC_H

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

            void write(const char *in, bool err = false);
    };
}

#endif // GNUTILITY_PUBLIC_H
