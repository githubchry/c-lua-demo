print("add.lua") -- luaL_dofile 时打印


-- 访问全局变量
print("name：", name)
print("age：", age)


-- 访问全局表

print("t.name：", t.name)
print("t.age：", t.age)




first = 10
second = 20
-- 访问全局函数
local ans = addmethod(10, 20)
printmethod(ans)