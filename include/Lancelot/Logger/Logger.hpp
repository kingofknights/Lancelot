#pragma once

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <fmt/ranges.h>

//#define LOG(TYPE, format, ...) LOG_##TYPE(format, __VA_ARGS__)

//#define LOG_INFO(format, ...) fmt::print(stderr, fmt::fg(fmt::color::green), "{:%Y-%m-%d %H:%M:%S} " format "\n", fmt::localtime(std::time(0)), __VA_ARGS__);

//#define LOG_ERROR(format, ...) fmt::print(stderr, fmt::fg(fmt::color::red), "{:%Y-%m-%d %H:%M:%S} " format "\n", fmt::localtime(std::time(0)), __VA_ARGS__);

//#define LOG_WARNING(format, ...) fmt::print(stderr, fmt::fg(fmt::color::purple), "{:%Y-%m-%d %H:%M:%S} " format "\n", fmt::localtime(std::time(0)), __VA_ARGS__);

#define FORMAT(args, ...) fmt::format(args, __VA_ARGS__)

enum LEVEL : int
{
    INFO = 0,
    WARNING,
    ERROR
};

template <typename... Args>
constexpr void LOG_INFO(Args... args_) {}

template <typename... Args>
constexpr void LOG_WARNING(Args... args_) {}

template <typename... Args>
constexpr void LOG_ERROR(Args... args_) {}

template <LEVEL level_, typename... Args>
constexpr void LOG(Args... args_) {
    if constexpr (level_ == LEVEL::INFO) {
        LOG_INFO(args_...);
    } else if constexpr (level_ == LEVEL::WARNING) {
        LOG_WARNING(args_...);
    } else if constexpr (level_ == LEVEL::ERROR) {
        LOG_ERROR(args_...);
    }
}
