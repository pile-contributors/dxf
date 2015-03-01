/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dxfwriter.cc
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
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include "dxfwriter.h"

#include <usermsg/usermsg.h>

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QDate>
#include <QTime>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

#if DEBUG_OFF
#define DXF_DBG DBG_PMESSAGE
#else
#define DXF_DBG black_hole
#endif

#if DEBUG_OFF
#define DXF_TRACE_ENTRY DBG_TRACE_ENTRY
#else
#define DXF_TRACE_ENTRY
#endif

#if DEBUG_OFF
#define DXF_TRACE_EXIT DBG_TRACE_EXIT
#else
#define DXF_TRACE_EXIT
#endif

#include "string_templates.h"

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
DxfWriter::DxfWriter (const QString & s_path) :
    s_full_path_(s_path),
    file_(NULL),
    stream_(NULL),
    cache_table_(),
    table_entry_count_(0),
    next_handle_(0x50)
{
    DXF_TRACE_ENTRY;
    DXF_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DxfWriter::~DxfWriter ()
{
    DXF_TRACE_ENTRY;

    if (stream_ != NULL) {
        stream_->flush ();
        delete stream_;
    }

    if (file_ != NULL) {
        file_->flush ();
        delete file_;
    }
    DXF_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::autostart (UserMsg & um)
{
    DXF_TRACE_ENTRY;
    bool b_ret = false;
    for (;;) {

        if (s_full_path_.isEmpty ()) {
            um.err ("Target file path is empty");
            break;
        }

        if (file_ == NULL) {
            file_ = new QFile (s_full_path_);
            if (!file_->open (QIODevice::WriteOnly | QIODevice::Text)) {
                um.err (
                            QString("Failed to create the file: %1")
                            .arg(file_->error ()));
                break;
            }

            stream_ = new QTextStream (file_);
            if (stream_->status () != QTextStream::Ok) {
                um.err (
                            QString("Failed to create the stream"));
                break;
            }
        } else if (stream_ == NULL) {
            // previous failure
            break;
        }

        b_ret = true;
        break;
    }

    DXF_TRACE_EXIT;
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startSecHeader (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startSection ("HEADER");
        (*stream_) << s_template_header_section;

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endSecHeader (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endSection ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startSecTables (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startSection ("TABLES");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endSecTables (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endSection ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::startTable (const QString & s_name)
{
    (*stream_) << "  0\n"
                  "TABLE\n"
                  "  2\n"
               << s_name << "\n";

    cache_table_.clear ();
    table_entry_count_ = 0;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::endTable ()
{
    QString number = QString("%1").arg (table_entry_count_, 6, 10, QChar(' '));
    (*stream_) << " 70\n"
               << number << "\n";

    foreach (const QString & s, cache_table_) {
        (*stream_) << s;
    }

    (*stream_) << "  0\n"
                  "ENDTAB\n";
    cache_table_.clear ();
    table_entry_count_ = 0;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appendTableEntry (const QString & s_name)
{
    cache_table_.append (s_name);
    ++table_entry_count_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appendToTable (const QString & s_name)
{
    cache_table_.append (s_name);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::incTableCount ()
{
    ++table_entry_count_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::setTableCount (int value)
{
    table_entry_count_ = value;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableVport (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("VPORT");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableVport (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableLtype (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("LTYPE");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableLtype (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableLayer (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("LAYER");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableLayer (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableStyle (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("STYLE");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableStyle (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableDimStyle (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("DIMSTYLE");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableDimStyle (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableAppId (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("APPID");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableAppId (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableView (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("VIEW");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableView (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startTableUCS (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startTable ("UCS");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endTableUCS (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endTable ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startSecBlocks (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startSection ("BLOCKS");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endSecBlocks (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endSection ();

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startSecEntities (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        startSection ("ENTITIES");

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endSecEntities (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        endSection ();
        (*stream_) << "  0\n"
                      "EOF\n";

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::statusOk (UserMsg & um)
{
    bool b_ret = false;
    for (;;) {
        if (stream_ == NULL) break;

        b_ret = stream_->status () == QTextStream::Ok;
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::startSection (const QString & s_name)
{
    (*stream_) << "  0\n"
                  "SECTION\n"
                  "  2\n"
               << s_name << "\n";
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::endSection()
{
    (*stream_) << "  0\n"
                  "ENDSEC\n";
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::vpTableAddDefault ()
{
    appendTableEntry (s_template_vports_table);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::ltyTableAddDefault ()
{
    appendTableEntry (s_template_ltype_table);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::styleTableAddDefault ()
{
    appendTableEntry (s_template_style_table);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::dimstyleTableAddDefault ()
{
    appendTableEntry (s_template_dimstyle_table);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appidTableAddDefault ()
{
    appendTableEntry (s_template_appid_table);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::lyTableAddDefault ()
{
    appendTableEntry (
                "  0\n"
                "LAYER\n"
                "  2\n"
                "0\n"
                " 70\n"
                "     0\n"
                " 62\n"
                "     7\n"
                "  6\n"
                "CONTINUOUS\n");
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::lyTableAdd (
        const QString & s_name, int base_color,
        const QString & s_line_style)
{
    QString col = QString("%1").arg (base_color, 6, 10, QChar(' '));
    appendTableEntry (
                QString(
                    "  0\n"
                    "LAYER\n"
                    "  2\n"
                    "%1\n"
                    " 70\n"
                    "     0\n"
                    " 62\n"
                    "%2\n"
                    "  6\n"
                    "%3\n")
                .arg(s_name)
                .arg(col)
                .arg(s_line_style));
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::startPolyline (const QString &layer, UserMsg &um, int color)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        (*stream_) << "  0\n"
                      "POLYLINE\n"
                      "  5\n"
                   << QString::number (next_handle_++, 16) << "\n"
                      "  8\n"
                   << layer << "\n";

        if ((color > -1) && (color < 256)) {
            QString number = QString("%1").arg (color, 6, 10, QChar(' '));

            (*stream_) << " 62\n"
                       << number << "\n";
        }

        (*stream_) << " 66\n"
                      "     1\n"
                      " 10\n"
                      "0.0\n"
                      " 20\n"
                      "0.0\n"
                      " 30\n"
                      "0.0\n";

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DxfWriter::endPolyline(UserMsg &um, int color)
{
    bool b_ret = false;
    for (;;) {
        if (!autostart (um)) break;

        (*stream_) << "  0\n"
                      "SEQEND\n"
                      "  5\n"
                   << QString::number (next_handle_++, 16) << "\n"
                      "  8\n"
                      "0\n";

        if ((color > -1) && (color < 256)) {
            QString number = QString("%1").arg (color, 6, 10, QChar(' '));

            (*stream_) << " 62\n"
                       << number << "\n";
        }

        b_ret = statusOk (um);
        break;
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appendVertex (double x, double y, double z, int color)
{

    (*stream_) << "  0\n"
                  "VERTEX\n"
                  "  5\n"
               << QString::number (next_handle_++, 16) << "\n"
                  "  8\n"
                  "0\n"
                  " 10\n"
               << x << "\n"
                  " 20\n"
               << y << "\n"
                  " 30\n"
               << z << "\n";

    if ((color > -1) && (color < 256)) {
        QString number = QString("%1").arg (color, 6, 10, QChar(' '));

        (*stream_) << " 62\n"
                   << number << "\n";
    }

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appendPoint (
        const QString &layer, double x, double y, double z, int color)
{
    (*stream_) << "  0\n"
                  "POINT\n"
                  "  5\n"
               << QString::number (next_handle_++, 16) << "\n"
                  "  8\n"
               << layer << "\n"
                  " 10\n"
               << x << "\n"
                  " 20\n"
               << y << "\n"
                  " 30\n"
               << z << "\n";

    if ((color > -1) && (color < 256)) {
        QString number = QString("%1").arg (color, 6, 10, QChar(' '));

        (*stream_) << " 62\n"
                   << number << "\n";
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appendCircle (
        const QString &layer, double radius,
        double x, double y, double z, int color)
{
    (*stream_) << "  0\n"
                  "CIRCLE\n"
                  "  5\n"
               << QString::number (next_handle_++, 16) << "\n"
                  "  8\n"
               << layer << "\n"
                  " 10\n"
               << x << "\n"
                  " 20\n"
               << y << "\n"
                  " 30\n"
               << z << "\n"
                  " 40\n"
               << radius << "\n";

    if ((color > -1) && (color < 256)) {
        QString number = QString("%1").arg (color, 6, 10, QChar(' '));

        (*stream_) << " 62\n"
                   << number << "\n";
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::appendText (
        const QString &layer, const QString &value,
        double x, double y, double z, double height,
        double deg_rotation, int color)
{
    (*stream_) << "  0\n"
                  "TEXT\n"
                  "  5\n"
               << QString::number (next_handle_++, 16) << "\n"
                  "  8\n"
               << layer << "\n"
                  " 10\n"
               << x << "\n"
                  " 20\n"
               << y << "\n"
                  " 30\n"
               << z << "\n"
                  " 40\n"
               << height << "\n"
                  "  1\n"
               << value << "\n"
                  " 50\n"
               << deg_rotation << "\n";

    if ((color > -1) && (color < 256)) {
        QString number = QString("%1").arg (color, 6, 10, QChar(' '));

        (*stream_) << " 62\n"
                   << number << "\n";
    }

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::blockAddDefModel ()
{
    (*stream_) << s_template_block_model;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::blockAddDefPaper ()
{
    (*stream_) << s_template_block_paper;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DxfWriter::blockAddDef (const QString & s_name)
{
    QString s = QString (
                "  0\n"
                "BLOCK\n"
                "  8\n"
                "0\n"
                "  2\n"
                "%1\n"
                " 70\n"
                "     0\n"
                " 10\n"
                "0.0\n"
                " 20\n"
                "0.0\n"
                " 30\n"
                "0.0\n"
                "  3\n"
                "%2\n"
                "  1\n"
                "\n"
                "  0\n"
                "ENDBLK\n"
                "  5\n"
                "B\n"
                "  8\n"
                "0\n")
            .arg(s_name)
            .arg(s_name);

    (*stream_) << s;
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
