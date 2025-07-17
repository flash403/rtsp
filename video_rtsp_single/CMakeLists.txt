cmake_minimum_required(VERSION 3.5)
project(rtsp_server_example)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

# 找 gstreamer 和 gstreamer-rtsp-server 依赖
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.14)
pkg_check_modules(GSTRTSP REQUIRED gstreamer-rtsp-server-1.0>=1.14)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GIO REQUIRED gio-2.0)

include_directories(
    ${GST_INCLUDE_DIRS}
    ${GSTRTSP_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${GIO_INCLUDE_DIRS}
)

link_directories(
    ${GST_LIBRARY_DIRS}
    ${GSTRTSP_LIBRARY_DIRS}
    ${GLIB_LIBRARY_DIRS}
    ${GIO_LIBRARY_DIRS}
)

add_executable(rtsp_server main.cpp)

target_link_libraries(rtsp_server
    ${GST_LIBRARIES}
    ${GSTRTSP_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${GIO_LIBRARIES}
)

# 添加编译选项，防止警告
target_compile_options(rtsp_server PRIVATE -Wall -Wextra)

