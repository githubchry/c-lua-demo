cmake_minimum_required(VERSION 3.10)
project(c-lua-demo)
########################
#有时我们的程序会定义一些暂时使用不上的功能和函数，虽然我们不使用这些功能和函数，但它们往往会浪费我们的ROM和RAM的空间。
#这在使用静态库时，体现的更为严重。有时，我们只使用了静态库仅有的几个功能，但是系统默认会自动把整个静态库全部链接到可执行程序中，造成可执行程序的大小大大增加。
#为了解决前面分析的问题，我们引入了以下的几个参数。
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -ffunction-sections -fdata-sections")
set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -Wl,-gc-sections")
#GCC链接操作是以section作为最小的处理单元，只要一个section中的某个符号被引用，该section就会被加入到可执行程序中去。
#因此，GCC在编译时可以使用 -ffunction-sections和 -fdata-sections 将每个函数或符号创建为一个sections，其中每个sections名与function或data名保持一致。
#而在链接阶段， -Wl,–gc-sections 指示链接器去掉不用的section（其中-Wl, 表示后面的参数 -gc-sections 传递给链接器），这样就能减少最终的可执行程序的大小了。
########################

# -g -fsanitize=address开启内存泄漏检测功能，用-fno-omit-frame-pointer编译，以得到更容易理解stack trace。
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer")

########################################################################################################################


if (WIN32)
    message("编译 windows")
    set(OS_PATH_NAME win)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -ffunction-sections -fdata-sections -g -fsanitize=address -fno-omit-frame-pointer")
    
    include_directories(win/include)
    link_directories("win/lib")

else ()
    if (DEFINED ENV{SDK_PATH})
        # 找到SDK_PATH环境变量 说明是交叉编译环境
        message("交叉编译 am335x")

        set(OS_PATH_NAME am335x)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -march=armv7-a -marm -mfpu=neon -mfloat-abi=hard -ffunction-sections -fdata-sections")

        include_directories(am335x/include)
        link_directories("am335x/lib")

    else()
        message("交叉编译 wsl linux")
        set(OS_PATH_NAME linux)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -ffunction-sections -fdata-sections -g -fsanitize=address -fno-omit-frame-pointer")
        
        include_directories(/mnt/d/codes/new-root/wsl/include)
        link_directories("/mnt/d/codes/new-root/wsl/lib")
    endif ()
endif (WIN32)

add_executable(c_call_lua c_call_lua.cc)
add_executable(lua_call_c lua_call_c.cc)
add_executable(loadstring loadstring.cc)

target_link_libraries(c_call_lua lua dl)    # 注意链接顺序 草泥马
target_link_libraries(lua_call_c lua dl)    # 注意链接顺序 草泥马
target_link_libraries(loadstring lua dl)    # 注意链接顺序 草泥马










