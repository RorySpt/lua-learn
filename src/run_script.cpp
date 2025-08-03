//
// Created by zhang on 25-7-31.
//

#include "run_script.h"

#include <chrono>
#include <iostream>
#include <utility>
#include <bits/this_thread_sleep.h>
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

void lua_learn::run_script_test() {
    system("");

    // 创建Lua状态
    lua_State* L = luaL_newstate();

    // 加载标准库
    luaL_openlibs(L);

    // 计时工具
    auto create_timer = []{return std::chrono::high_resolution_clock::now();};
    auto time_it = [](std::chrono::system_clock::time_point& tp_) {
        return tp_ - std::exchange(tp_, std::chrono::system_clock::now());
    };
    auto time_it_and_print_cost = [time_it](std::chrono::system_clock::time_point& tp_, std::string_view prefix = {}) {
        constexpr auto color = fmt::emphasis::bold | fg(fmt::color::blue);

        std::chrono::duration<double> dur = time_it(tp_);
        if (prefix.empty()) {
            fmt::print(color, "cost: {: .3}ms\n", dur.count() * 1000.0);
        }else {
            fmt::print(color, "{}, cost: {: .3}ms\n", prefix, dur.count() * 1000.0);
        }
        time_it(tp_);
    };

    // 打印代码内容
    fmt::print(fmt::emphasis::bold | fg(fmt::color::purple), "-------scripts/script.lua----------\n");
    system(R"(powershell Get-Content "scripts/script.lua")");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::purple), "-----------------------------------\n");

    auto tp = create_timer();
    time_it_and_print_cost(tp, "self.test");
    time_it_and_print_cost(tp, "self.test");
    // 执行Lua脚本文件
    if (luaL_dofile(L, "scripts/script.lua")) {
        fmt::println("Error: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    time_it_and_print_cost(tp, "load and run script.lua");


    lua_getglobal(L, "test");
    if (lua_pcall(L, 0, 0, 0) != 0) {
        fmt::println("Error: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    time_it_and_print_cost(tp, "call lua_pcall test");

    lua_getglobal(L, "test1");
    if (lua_pcall(L, 0, 0, 0) != 0) {
        fmt::println("Error: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    time_it_and_print_cost(tp, "call a lua print function");

    // 执行Lua字符串
    if (luaL_dostring(L, "print('Hello from Lua!')")) {
        fmt::println("Error: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    time_it_and_print_cost(tp, "call luaL_dostring");


    lua_getglobal(L, "test2");
    if (lua_pcall(L, 0, 0, 0) != 0) {
        fmt::println("Error: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    time_it_and_print_cost(tp, "call test2");
}