cmake_minimum_required(VERSION 3.23)
project(BRender C)

if(DOS)
    enable_language(ASM_MASM)
    add_compile_definitions(-D__GO32__=1 -D__DPMI__=1 -D__DOS__=1)
    add_compile_options(-U__unix__)
endif()

if(WATCOM)
    add_compile_definitions(-Dsqrtf=sqrt)
    add_compile_definitions(-Dsinf=sin)
    add_compile_definitions(-Dcosf=cos)
    add_compile_definitions(-Dfabsf=fabs)
    add_compile_definitions(-Datanf=atan)
    add_compile_definitions(-Dfmodf=fmod)
    add_compile_definitions(-Datan2f=atan2)
    add_compile_definitions(-Dasinf=asin)
    add_compile_definitions(-Dpowf=pow)
    add_compile_definitions(-Dfmaxf=fmax)
    add_compile_definitions(-Dldexpf=ldexp)
    add_compile_definitions(-Dceilf=ceil)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Prefer glvnd
cmake_policy(SET CMP0072 NEW)

cmake_policy(SET CMP0079 NEW)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Perl REQUIRED)

option(BRENDER_BUILD_DRIVERS "Build Drivers" ON)
option(BRENDER_BUILD_EXAMPLES "Build Examples" OFF)
option(BRENDER_DISABLE_INSTALL "Disable installation" OFF)
option(BRENDER_ASAN_ENABLED "Address Sanitizer" OFF)

add_subdirectory(core)

add_subdirectory(x86emu)

if (BRENDER_BUILD_DRIVERS)
    add_subdirectory(drivers)
endif ()

##
# Core BRender, no drivers, no DDI.
##
add_library(BRender::Core ALIAS brender)

##
# Full BRender, with drivers, no DDI.
##
add_library(BRender::Full ALIAS brender-full)

##
# Core BRender, no drivers, with DDI.
##
add_library(BRender::DDI ALIAS brender-ddi)


# if (BRENDER_BUILD_TOOLS)
#     add_subdirectory(tools)
# endif ()

if (BRENDER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (NOT BRENDER_DISABLE_INSTALL)
    include(cmake/packaging.cmake)
endif ()
