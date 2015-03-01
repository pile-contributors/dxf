/**
 * @file dxf-private.h
 * @brief Declarations for DXF class
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_DXF_PRIVATE_H_INCLUDE
#define GUARD_DXF_PRIVATE_H_INCLUDE

#include <dxf/dxf-config.h>

#if 0
#    define DXF_DEBUGM printf
#else
#    define DXF_DEBUGM black_hole
#endif

#if 0
#    define DXF_TRACE_ENTRY printf("DXF ENTRY %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define DXF_TRACE_ENTRY
#endif

#if 0
#    define DXF_TRACE_EXIT printf("DXF EXIT %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define DXF_TRACE_EXIT
#endif


static inline void black_hole (...)
{}

#endif // GUARD_DXF_PRIVATE_H_INCLUDE
