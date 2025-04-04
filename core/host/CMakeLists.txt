project(host)

target_include_directories(brender-inc INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
target_include_directories(brender-inc-ddi INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ddi>
        $<INSTALL_INTERFACE:ddi>
        )

set(DDI_FILES
        ddi/host.h
        ddi/host_p.h
        )

set(INC_FILES
        )

set(HOST_FILES
        himage.c
        hostcfg.c
        hstsetup.c
        host_ip.h
        hook.c
        memmgmt.c
        )

if(DOS)
    set(HOST_ASM_FILES
#        cpuid.asm
        farmem.asm
#        page.asm
#        prot.asm
#        real.asm
#        realmem.asm
#        segregs.asm
        )
    set_property(SOURCE ${HOST_ASM_FILES} PROPERTY LANGUAGE "ASM_MASM")
    set_property(SOURCE ${HOST_ASM_FILES} APPEND PROPERTY COMPILE_OPTIONS "-nologo;-coff;-Gd;-Zf")
    set_property(SOURCE ${HOST_ASM_FILES} APPEND PROPERTY COMPILE_DEFINITIONS "ADD_RCS_ID=0")
    set_property(SOURCE ${HOST_ASM_FILES} APPEND PROPERTY OBJECT_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/host.inc")
    set_property(SOURCE ${HOST_ASM_FILES} APPEND PROPERTY INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/../inc")
    list(APPEND HOST_FILES ${HOST_ASM_FILES})
else()
    list(APPEND HOST_FILES
        host_asm.c
        )
endif()

add_library(host OBJECT ${HOST_FILES})

target_sources(host INTERFACE
        FILE_SET include
        TYPE HEADERS
        BASE_DIRS include
        FILES ${INC_FILES}
        )

target_sources(host INTERFACE
        FILE_SET ddi
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR} ddi
        FILES ${DDI_FILES}
        )

target_include_directories(host PRIVATE .)
target_link_libraries(host PRIVATE brender-inc-ddi ${CMAKE_DL_LIBS})
