
#include <lua.hpp>

//g++ -Wall main.cc -o main -llua -ldl -I/mnt/d/codes/new-root/wsl/include -L/mnt/d/codes/new-root/wsl/lib



int main() {

    //初始化Lua虚拟机
    auto L = luaL_newstate();

    //设置待注册的Lua标准库，这个库是给你的Lua脚本用的
    luaL_openlibs(L);

    // 调用lua脚本，脚本里面调用c函数
    luaL_dofile(L, "loadstring.lua");

    lua_close(L);
    return 0;
}