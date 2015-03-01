/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dxfwriter.h
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
#ifndef __PILE_DXF_WRITER_INC__
#define __PILE_DXF_WRITER_INC__
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dxf/dxf-config.h>

#include "gdal.h"
#include "ogr_srs_api.h"

#include <QString>
#include <QStringList>
#include <QList>
#include <QTextStream>
#include <QFile>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class UserMsg;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! Writes a dxf file
///
class DXF_EXPORT DxfWriter {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */

public:

    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    //! the path to the file
    QString s_full_path_;

    //! the path to the file
    QFile * file_;

    //! the path to the file
    QTextStream * stream_;

    //! the cache for writing Table.
    QStringList cache_table_;

    //! Number of entries in the table.
    int table_entry_count_;

    //! Used to tag internal entities.
    int next_handle_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! constructor
    ///
    explicit DxfWriter (const QString & s_path);

    //! destructor
    ///
    virtual ~DxfWriter (void);

    //! the path to the file
    ///
    inline const QString &
    path () const {
        return s_full_path_;
    }

    bool
    startSecBlocks (
            UserMsg & um);
    bool
    startSecEntities (
            UserMsg & um);
    bool
    startSecHeader (
            UserMsg & um);
    bool
    startSecTables (
            UserMsg & um);

    bool
    endSecBlocks (
            UserMsg & um);
    bool
    endSecEntities (
            UserMsg & um);
    bool
    endSecHeader (
            UserMsg & um);
    bool
    endSecTables (
            UserMsg & um);


    void
    appendTableEntry (
            const QString & s_name);

    void
    appendToTable (
            const QString & s_name);
    void
    incTableCount ();

    void
    setTableCount (
            int value);

    bool
    startTableVport (
            UserMsg & um);
    bool
    endTableVport (
            UserMsg & um);
    bool
    startTableLtype (
            UserMsg & um);
    bool
    endTableLtype (
            UserMsg & um);
    bool
    startTableLayer (
            UserMsg & um);
    bool
    endTableLayer (
            UserMsg & um);
    bool
    startTableStyle (
            UserMsg & um);
    bool
    endTableStyle (
            UserMsg & um);
    bool
    startTableAppId (
            UserMsg & um);
    bool
    endTableAppId (
            UserMsg & um);
    bool
    startTableView (
            UserMsg & um);
    bool
    endTableView (
            UserMsg & um);
    bool
    startTableUCS (
            UserMsg & um);
    bool
    endTableUCS (
            UserMsg & um);
    bool
    startTableDimStyle (
            UserMsg & um);
    bool
    endTableDimStyle (
            UserMsg & um);



    void vpTableAddDefault ();
    void ltyTableAddDefault ();
    void lyTableAddDefault ();
    void styleTableAddDefault ();
    void appidTableAddDefault ();
    void dimstyleTableAddDefault ();

    void blockAddDefModel ();
    void blockAddDefPaper ();
    void blockAddDef (
            const QString & s_name);

    void lyTableAdd (
            const QString & s_name,
            int base_color = 7,
            const QString & s_line_style = "CONTINUOUS");

    bool
    startPolyline (
            const QString & layer,
            UserMsg & um);

    bool
    endPolyline (
            UserMsg & um);

    void
    appendVertex (
            double x,
            double y,
            double z);


private:


    bool
    autostart (
            UserMsg & um);

    bool
    statusOk (
            UserMsg & um);

    void
    startSection (
            const QString & s_name);

    void
    endSection ();

    void
    startTable (
            const QString & s_name);

    void
    endTable ();

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

};	/*	class DxfWriter	*/

/*  CLASS    =============================================================== */
//
//
//
//

#endif // __PILE_DXF_WRITER_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
