
# enable/disable cmake debug messages related to this pile
set (DXF_DEBUG_MSG ON)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (dxfInit
          ref_cnt_use_mode)

    # default name
    if (NOT DXF_INIT_NAME)
        set(DXF_INIT_NAME "DXF")
    endif ()

    # compose the list of headers and sources
    set(DXF_HEADERS
        "dxf.h"
        "dxfwriter.h")
    set(DXF_SOURCES
        "dxf.cc"
        "dxfwriter.cc")
    set(DXF_QT_MODS
        "Core")
#    set(DXF_LIBS
#        ${USERMSG_LIBRARY})
    set(DXF_DEPENDENCIES
        "UserMsg")

message (STATUS "USERMSG_LIBRARY ------------  =${USERMSG_LIBRARY}")
    pileSetSources(
        "${DXF_INIT_NAME}"
        "${DXF_HEADERS}"
        "${DXF_SOURCES}")

    pileSetCommon(
        "${DXF_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${ref_cnt_use_mode}"
        ""
        "category1"
        "tag1;tag2")

endmacro ()
