#include "events.h"


int LuaEvents::on(lua_State* L) {
    const char* event = lua_tostring(L, 1);
    lua_pushvalue(L, 2); // Push the callback function
    int ref = luaL_ref(L, LUA_REGISTRYINDEX); // Store the reference to the callback in the registry

    /*Event::on(event, Function::create<void>([L, ref]() {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref); // Push the callback function to the stack
        if (lua_pcall(L, 0, 0, 0) != LUA_OK) { // Handle Lua errors properly
            //Get the error message
            Debug::Log::error(lua_tostring(L, -1));
        }
    }));*/
    return 0;
}

int LuaEvents::call(lua_State* L) {
    const char* event = lua_tostring(L, 1);
    Event::emit(event);
    return 0;
}

void LuaEvents::registerFunctions(LuaState& script) {
    script.beginNamespace("Event");

    script.function("on", LuaEvents::on);

    script.function("call", LuaEvents::call);

    script.endNamespace();
}