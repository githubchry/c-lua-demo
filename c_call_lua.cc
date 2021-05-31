
#include <lua.hpp>

//g++ -Wall main.cc -o main -llua -ldl -I/mnt/d/codes/new-root/wsl/include -L/mnt/d/codes/new-root/wsl/lib

//为了方便说明,在C code中调用Lua Code函数,函数以calllua_XXX命名
int calllua_sum(lua_State *L, int a, int b) {

    //把_G["name"] 函数压入到虚拟栈上面
    lua_getglobal(L, "sum");

    //按时Lua函数顺序,从左到右依次压入参数
    lua_pushnumber(L, a);
    lua_pushnumber(L, b);

    //调用lua_call()函数,实际调用Lua Code函数
    lua_call(L, 2, 1);

    //当Lua Code函数调用结束后,把结果值压入虚拟栈中
    int sum = (int) lua_tonumber(L, -1);

    return sum;
}

int main(int argc, char **argv) {
    //初始化Lua虚拟机
    auto L = luaL_newstate();

    //设置待注册的Lua标准库，这个库是给你的Lua脚本用的
    luaL_openlibs(L);

    //执行add.lua
    luaL_dofile(L, "c_call_lua.lua");

    // 获取lua的全局变量
    printf("获取lua的全局变量\n");
    lua_getglobal(L, "width");
    lua_getglobal(L, "height");

    // 根据lua_getglobal顺序 逐个转码lua_tonumber，注意index是从1开始
    for (int i = 1; i <= lua_gettop(L); ++i) {
        int num = lua_tonumber(L, i);
        printf("num:%d\n", num);
    }

    //调用Lua Code函数
    int sum = calllua_sum(L, 1, 2);

    printf("sum: %d\n", sum);

    //关闭lua_State
    lua_close(L);
    return 1;
}