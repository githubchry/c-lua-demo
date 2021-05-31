
#include <lua.hpp>

//g++ -Wall main.cc -o main -llua -ldl -I/mnt/d/codes/new-root/wsl/include -L/mnt/d/codes/new-root/wsl/lib

//能够被Lua调用的C函数必须是这种规则 函数的返回值int值表示C函数返回值的个数
//typedef int (*lua_CFunction)(lua_State *L)

static int Addmethod(lua_State *t) {
    //检查栈中的参数是否合法，1表示Lua调用时的第一个参数(从左到右)，依此类推。
    //如果Lua代码在调用时传递的参数不为number，该函数将报错并终止程序的执行。
    int first = luaL_checknumber(t, 1);
    int second = luaL_checknumber(t, 2);

    //将函数的结果压入栈中。如果有多个返回值，可以在这里多次压入栈中。
    lua_pushnumber(t, first + second);

    //返回值用于提示该C函数的返回值数量，即压入栈中的返回值数量。
    return 1;
}

static int Printmethod(lua_State *t) {
    int answer = luaL_checknumber(t, 1);
    printf("answer:%d\n", answer);
    return 0;
}


int main() {

    //初始化Lua虚拟机
    auto L = luaL_newstate();

    //设置待注册的Lua标准库，这个库是给你的Lua脚本用的
    luaL_openlibs(L);

    // 将指定的函数注册为Lua的全局函数变量，其中第一个字符串参数为Lua调用C函数时使用的全局函数名，第二个参数为实际C函数的指针。
    lua_register(L, "addmethod", Addmethod);
    lua_register(L, "printmethod", Printmethod);

    // 注册全局变量
    lua_pushstring(L, "chry");
    lua_setglobal(L, "name");// 将栈顶的数据出栈到lua全局变量区，并且赋给一个变量名"name"

    lua_pushinteger(L, 25);
    lua_setglobal(L, "age");

    // 为了减少干扰，首先清空栈
    lua_settop(L, 0);

    // 注册全局表
    lua_newtable(L); // 新建一个表，并且入栈，因为表在lua虚拟机的栈中，所以表名字是不需要的
    lua_pushinteger(L, 19);
    lua_pushstring(L, "张三"); //用作值

    lua_setfield(L, 1, "name"); //第二个参数是表在栈中的下标。这个函数同样在栈顶弹出一个元素，并赋值给变量bname
    lua_setfield(L, 1, "age");
    lua_setglobal(L, "t");  //给栈顶的内容赋一个变量名，并弹出到lua的全局变量区，这里就是给表一个名字t


    // 调用lua脚本，脚本里面调用c函数
    luaL_dofile(L, "lua_call_c.lua");

    lua_close(L);
    return 0;
}