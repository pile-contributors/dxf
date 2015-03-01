if (NOT DXF_BUILD_MODE)
    set (DXF_BUILD_MODE STATIC)
endif ()

include(pile_support)
pileInclude (Dxf)
dxfInit(${DXF_BUILD_MODE})
