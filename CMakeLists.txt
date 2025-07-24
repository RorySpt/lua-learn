cmake_minimum_required(VERSION 3.31)
project(untitled)

set(CMAKE_CXX_STANDARD 26)

add_executable(untitled main.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE fmt::fmt-header-only)

find_package(Lua REQUIRED)
target_include_directories(untitled PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(untitled PRIVATE ${LUA_LIBRARIES})



# 安装脚本文件
#file(COPY scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#add_custom_command(TARGET untitled POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/scripts
#        $<TARGET_FILE_DIR:untitled>/scripts
#        COMMENT "Copying Lua scripts to output directory"
#)

# 定义拷贝函数
function(add_script_copy_target target src_dir dest_dir)
    if(MSVC)
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${dest_dir}"
                COMMAND xcopy /Y /E "${src_dir}" "${dest_dir}"
                COMMENT "Copying Lua scripts (Post-Build)"
        )
    else()
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${dest_dir}"
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${src_dir}" "${dest_dir}"
                COMMENT "Copying Lua scripts (Post-Build)"
        )
    endif()
endfunction()

# 使用函数
add_script_copy_target(untitled
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts
        $<TARGET_FILE_DIR:untitled>/scripts
)
