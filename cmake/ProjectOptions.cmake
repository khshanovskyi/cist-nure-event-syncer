# Shared compiler settings. Included once from the root CMakeLists.txt, before any target exists.

# Warnings for our own targets only. vcpkg libraries are built separately and are not affected.
function(cistsync_set_warnings target)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endfunction()

# Sanitizers are the closest thing to the JVM's safety net: they abort with a stack trace on
# out-of-bounds access, use-after-free, signed overflow and similar bugs instead of silently
# corrupting memory. Debug preset only; they slow the program down about 2x.
if(ENABLE_SANITIZERS)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "^(AppleClang|Clang|GNU)$")
        message(FATAL_ERROR "ENABLE_SANITIZERS requires Clang or GCC")
    endif()
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()
