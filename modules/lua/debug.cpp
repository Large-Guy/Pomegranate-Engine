#include "debug.h"

int LuaDebug::LuaLog::info(lua_State* L) {
//Get arg count
    int n = lua_gettop(L);

//Concatenate all args
    std::string message;
    for (int i = 1; i <= n; i++) {
        message += lua_tostring(L, i);
        if (i != n) {
            message += " ";
        }
    }

//Log message
    Debug::Log::info(message);
    return 0;
}

int LuaDebug::LuaLog::pass(lua_State* L) {
//Get arg count
    int n = lua_gettop(L);

//Concatenate all args
    std::string message;
    for (int i = 1; i <= n; i++) {
        message += lua_tostring(L, i);
        if (i != n) {
            message += " ";
        }
    }

//Log message
    Debug::Log::pass(message);
    return 0;
}

int LuaDebug::LuaLog::fail(lua_State* L) {
//Get arg count
    int n = lua_gettop(L);

//Concatenate all args
    std::string message;
    for (int i = 1; i <= n; i++) {
        message += lua_tostring(L, i);
        if (i != n) {
            message += " ";
        }
    }

//Log message
    Debug::Log::fail(message);
    return 0;
}

int LuaDebug::LuaLog::warn(lua_State* L) {
//Get arg count
    int n = lua_gettop(L);

//Concatenate all args
    std::string message;
    for (int i = 1; i <= n; i++) {
        message += lua_tostring(L, i);
        if (i != n) {
            message += " ";
        }
    }

//Log message
    Debug::Log::warn(message);
    return 0;
}

int LuaDebug::LuaLog::error(lua_State* L) {
//Get arg count
    int n = lua_gettop(L);

//Concatenate all args
    std::string message;
    for (int i = 1; i <= n; i++) {
        message += lua_tostring(L, i);
        if (i != n) {
            message += " ";
        }
    }

//Log message
    Debug::Log::error(message);
    return 0;
}

void LuaDebug::registerFunctions(LuaState& script) {
    script.beginNamespace("Debug");

    //Log
    script.beginNamespace("Log");

    script.function("info", LuaLog::info);
    script.function("pass", LuaLog::pass);
    script.function("fail", LuaLog::fail);
    script.function("warn", LuaLog::warn);
    script.function("error", LuaLog::error);

    script.endNamespace();

    script.endNamespace();
}
