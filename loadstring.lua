print("add.lua") -- luaL_dofile 时打印

A = 10
B = 15
C = 20
D = 25

function test(A, B)
    --return A + B ? A : B  -- 语法错误
    if A + B then
        return A
    else
        return B
    end
end

function min(A, B)
    return math.min(A, B)
end

function cos(A)
    return math.cos(A)
end

function bool_to_number(value)
    return value and 1 or 0
end
--ret = math.cos(math.min(B % A * C - D, A)) + (A + B ? A : B) -- 语法错误
ret = cos(min(B % A * C - D / 10 + 5, A ^ 2))  + bool_to_number(A < B)

print(load("return ret")())