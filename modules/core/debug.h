#ifndef POMEGRANATE_ENGINE_CORE_DEBUG_H
#define POMEGRANATE_ENGINE_CORE_DEBUG_H

#include <string>
#include <iostream>

class Debug {
public:
    class Log {
    public:
        template<typename ...args>
        Log(args... messages) {
            std::cout << "\033[1;44m[LOG]\033[0m  ";
            // Ensure space between messages
            ((std::cout << messages << ' '), ...);
            std::cout << std::endl;
        }

        static void info(std::string message);

        static void warn(std::string message);

        static void error(std::string message);

        static void pass(std::string message);

        static void fail(std::string message);

        template<typename ...args>
        static void info(args... messages) {
            std::cout << "\033[1;44m[INFO]\033[0m  ";
            // Ensure space between messages
            ((std::cout << messages << ' '), ...);
            std::cout << std::endl;
        }

        template<typename ...args>
        static void warn(args... messages) {
            std::cout << "\033[1;43m[WARN]\033[0m  ";
            // Ensure space between messages
            ((std::cout << messages << ' '), ...);
            std::cout << std::endl;
        }

        template<typename ...args>
        static void error(args... messages) {
            std::cout << "\033[1;41m[ERROR]\033[0m ";
            // Ensure space between messages
            ((std::cout << messages << ' '), ...);
            std::cout << std::endl;
        }

        template<typename ...args>
        static void pass(args... messages) {
            std::cout << "\033[1;42m[PASS]\033[0m  ";
            // Ensure space between messages
            ((std::cout << messages << ' '), ...);
            std::cout << std::endl;
        }

        template<typename ...args>
        static void fail(args... messages) {
            std::cout << "\033[1;41m[FAIL]\033[0m  ";
            // Ensure space between messages
            ((std::cout << messages << ' '), ...);
            std::cout << std::endl;
        }
    };

    class AssertIf {
    public:
        template<typename ...args>
        static inline void isTrue(bool condition, args... message) {
            if (condition) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename ...args>
        static inline void isFalse(bool condition, args... message) {
            if (!condition) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename ...args>
        static inline void isNull(void *ptr, args... message) {
            if (ptr == nullptr) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename ...args>
        static inline void isNotNull(void *ptr, args... message) {
            if (ptr != nullptr) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isZero(T value, args... message) {
            if (value == 0) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isNotZero(T value, args... message) {
            if (value != 0) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isEqual(T a, T b, args... message) {
            if (a == b) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isNotEqual(T a, T b, args... message) {
            if (a != b) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isLessThan(T a, T b, args... message) {
            if (a < b) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isLessThanOrEqual(T a, T b, args... message) {
            if (a <= b) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isGreaterThan(T a, T b, args... message) {
            if (a > b) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }

        template<typename T, typename ...args>
        static inline void isGreaterThanOrEqual(T a, T b, args... message) {
            if (a >= b) {
                Log::fail(message...);
                throw std::runtime_error("Assertion failed");
            }
        }
    };

    class WarnIf {
    public:
        template<typename ...args>
        static inline void isTrue(bool condition, args... message) {
            if (condition) {
                Log::warn(message...);
            }
        }

        template<typename ...args>
        static inline void isFalse(bool condition, args... message) {
            if (!condition) {
                Log::warn(message...);
            }
        }

        template<typename ...args>
        static inline void isNull(void *ptr, args... message) {
            if (ptr == nullptr) {
                Log::warn(message...);
            }
        }

        template<typename ...args>
        static inline void isNotNull(void *ptr, args... message) {
            if (ptr != nullptr) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isZero(T value, args... message) {
            if (value == 0) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isNotZero(T value, args... message) {
            if (value != 0) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isEqual(T a, T b, args... message) {
            if (a == b) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isNotEqual(T a, T b, args... message) {
            if (a != b) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isLessThan(T a, T b, args... message) {
            if (a < b) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isLessThanOrEqual(T a, T b, args... message) {
            if (a <= b) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isGreaterThan(T a, T b, args... message) {
            if (a > b) {
                Log::warn(message...);
            }
        }

        template<typename T, typename ...args>
        static inline void isGreaterThanOrEqual(T a, T b, args... message) {
            if (a >= b) {
                Log::warn(message...);
            }
        }
    };
};


#endif //POMEGRANATEENGINE_DEBUG_H
