file(GLOB lib_source "*.c")
get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB lib_headers "./*.h")


add_library("${dir_name}" STATIC  ${lib_source})
target_include_directories("${dir_name}" PUBLIC "../")
target_include_directories("${dir_name}" PUBLIC "../" "../../gpio_lib")
target_link_libraries("${dir_name}" PUBLIC spi_macro)
target_link_libraries("${dir_name}" PUBLIC gpio_lib)

