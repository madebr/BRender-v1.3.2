add_library(mcga
    bios.c
    devclut.c
    device.c
    devpixmp.c
    driver.c
    object.c
    outfcty.c
)

get_target_property(target_type mcga TYPE)
if(target_type STREQUAL SHARED_LIBRARY)
    target_compile_definitions(mcga PRIVATE -DDEFINE_BR_ENTRY_POINT)
endif()

target_include_directories(mcga PRIVATE ddi)

target_link_libraries(mcga PRIVATE BRender::DDI)

set_target_properties(mcga PROPERTIES
    EXPORT_NAME "Drivers::mcga"
    FOLDER "BRender/Drivers"
)

add_library(BRender::Drivers::mcga ALIAS mcga)
