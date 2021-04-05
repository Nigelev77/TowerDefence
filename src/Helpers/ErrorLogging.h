#pragma once
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define ERR_LOG(_msg_) spdlog::stderr_color_mt(#_msg_, spdlog::color_mode::always);std::cin.get()

