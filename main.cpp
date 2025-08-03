#include <chrono>
#include <utility>
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "run_script.h"

#define STR_(x) #x
#define STR(x) STR_(x)
#define CAT_(x, y) x ## y
#define CAT(x, y) CAT_(x, y)


void copy_scrips(){
    system(R"(xcopy /Y /E "C:\Users/zhang\Documents\GitHub\lua-learn\scripts" .\scripts)");
}

int main() {
    copy_scrips();

    lua_learn::run_script_test();

    fmt::print("{}\n", STR(CAT(__LINE__, __LINE__)));
    return 0;
}