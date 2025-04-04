set(vesa_asm_sources
    ports.asm
    vesabank.asm
    vesaloop.asm
)
set_property(SOURCE ${vesa_asm_sources} PROPERTY LANGUAGE "ASM_MASM")
set_property(SOURCE ${vesa_asm_sources} APPEND PROPERTY COMPILE_OPTIONS "-omf")
set_property(SOURCE ${vesa_asm_sources} APPEND PROPERTY COMPILE_OPTIONS "-nologo")
set_property(SOURCE ${vesa_asm_sources} APPEND PROPERTY OBJECT_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/drv.inc")

add_library(vesa
    bios.c
    devclut.c
    device.c
    devpixmp.c
    devpml.c
    devpmwb.c
    devpmw.c
    driver.c
    object.c
    ocfree.c
    outfcty.c
    vesaapi.c
    ${vesa_asm_sources}
)

get_target_property(target_type vesa TYPE)
if(target_type STREQUAL SHARED_LIBRARY)
    target_compile_definitions(vesa PRIVATE -DDEFINE_BR_ENTRY_POINT)
endif()

target_include_directories(vesa PRIVATE ddi)

target_link_libraries(vesa PRIVATE BRender::DDI)

set_target_properties(vesa PROPERTIES
    EXPORT_NAME "Drivers::vesa"
    FOLDER "BRender/Drivers"
)

add_library(BRender::Drivers::vesa ALIAS vesa)
