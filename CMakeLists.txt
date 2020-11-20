cmake_minimum_required(VERSION 3.16.3)
project(Onion_Omega2plus_st7735)
# set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_SYSTEM_PROCESSOR mips)


# set(CMAKE_STAGING_PREFIX /home/dan/source/staging_dir)

# set(tools /home/dan/source/staging_dir/toolchain-mipsel_24kc_gcc-7.3.0_musl)
# set(CMAKE_C_COMPILER ${tools}/bin/mipsel-openwrt-linux-gcc)
# set(CMAKE_CXX_COMPILER ${tools}/bin/mipsel-openwrt-linux-g++)

# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

add_subdirectory(gpio_lib)
add_subdirectory(lib)

file(GLOB source "./src/*.c")
add_executable(omega_st7735 ${source})
target_link_libraries(omega_st7735 PUBLIC st7735)
target_include_directories(omega_st7735 PUBLIC lib)
target_include_directories(omega_st7735 PUBLIC gpio_lib)
