/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dxf.h
  \date			March 2015
  \author		Nicu Tofan <nicu.tofan@gmail.com>

  \brief		Contains the definition for an input file


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __PILE_DXF_INC__
#define __PILE_DXF_INC__
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dxf/dxf-config.h>

#include <QString>
#include <QStringList>
#include <QList>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! Represents a full inputfile (top level node)
///
class DXF_EXPORT Dxf {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */

public:

    enum BaseColors {
        COLOR_RED = 1,
        COLOR_YELLOW = 2,
        COLOR_GREEN = 3,
        COLOR_CYAN = 4,
        COLOR_BLUE = 5,
        COLOR_MAGENTA = 6,
        COLOR_WHITE_BLACK = 7,
        COLOR_DARK_GRAY = 8,
        COLOR_LIGHT_GRAY = 9,
        // 10-255 = various shades of above
    };


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    //! the path to the file
    QString s_full_path_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! constructor
    ///
    explicit Dxf (const QString & s_path);

    //! destructor
    ///
    virtual ~Dxf (void);

    //! the path to the file
    ///
    inline const QString &
    path () const {
        return s_full_path_;
    }



    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

};	/*	class Dxf	*/

/*  CLASS    =============================================================== */
//
//
//
//

#endif // __PILE_DXF_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
