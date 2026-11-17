/* gfopenmusic.library (GFOpenMusic): music for games and programs, from
 * any file a datatype reads as a sound (MOD, S3M, XM, IT and the other
 * modules through gfopenmodule.datatype; Ogg Vorbis, FLAC and MP3 through
 * gfopensound.datatype; WAV and AIFF; 8SVX through sound.datatype),
 * streamed to ahi.device a piece at a time. docs/gfopenmusic.library.md is
 * the contract. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef LIBRARIES_GFOPENMUSIC_H
#define LIBRARIES_GFOPENMUSIC_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define GFOPENMUSICNAME    "gfopenmusic.library"
#define GFOPENMUSIC_VERSION 1

/* A song: made by GMOpenA, ended by GMClose. Its fields are private. */
struct GMSong;

#define GMA_Dummy     (TAG_USER + 0x0DA16000)

/* GMOpenA's tags */
#define GMA_Unit      (GMA_Dummy + 1)  /* (ULONG) ahi.device unit (default 0, music's) */
#define GMA_MixRate   (GMA_Dummy + 2)  /* (ULONG) a module's mixing rate (default 44100) */
#define GMA_Interp    (GMA_Dummy + 3)  /* (ULONG) a module's: 0 nearest, 1 linear, 2 spline (default) */
#define GMA_Volume    (GMA_Dummy + 4)  /* (ULONG) also GMGetAttr: 0 to GM_VOLUME_FULL (default full) */
#define GMA_Buffer    (GMA_Dummy + 5)  /* (ULONG) milliseconds in each of the two AHI buffers, 50 to 2000 (default 500) */
#define GMA_Decoder   (GMA_Dummy + 6)  /* (ULONG) GMDEC_: who decodes (default GMDEC_AUTO, or ENV:GFOpenMusic/Decoder) */

/* GMGetAttr's */
#define GMA_State     (GMA_Dummy + 16) /* GMS_ */
#define GMA_Length    (GMA_Dummy + 17) /* milliseconds in one pass of the song (0: not known) */
#define GMA_Position  (GMA_Dummy + 18) /* milliseconds into this pass, as mixed */
#define GMA_Title     (GMA_Dummy + 19) /* (STRPTR) the datatype's DTA_ObjName: a module's title, else the file's name */
#define GMA_Kind      (GMA_Dummy + 20) /* (STRPTR) the datatype's DTA_ObjAnnotation, or NULL ("Protracker M.K.") */
#define GMA_Rate      (GMA_Dummy + 21) /* frames a second, as sent to AHI */
#define GMA_Channels  (GMA_Dummy + 22) /* 1 or 2 */
#define GMA_Loops     (GMA_Dummy + 23) /* times still to play again (-1: for ever) */
#define GMA_Error     (GMA_Dummy + 24) /* 0, or why it stopped: the datatype's IoErr() */
#define GMA_Streamed  (GMA_Dummy + 25) /* TRUE: read a piece at a time (OIA_Reader); FALSE: SDTA_Sample whole */

#define GMA_DecodedBy (GMA_Dummy + 26) /* GMDB_ */

/* GMA_Decoder: auto is AkikoPlus first (the host decodes), then datatypes */
#define GMDEC_AUTO      0
#define GMDEC_AKIKOPLUS 1              /* akikoplus.device only: no datatypes */
#define GMDEC_DATATYPES 2              /* datatypes only: never the host */

/* GMA_DecodedBy */
#define GMDB_AKIKOPLUS  1              /* on the host, through akikoplus.device */
#define GMDB_DATATYPE   2              /* a datatype with OIA_Reader, a piece at a time */
#define GMDB_WHOLE      3              /* a datatype's SDTA_Sample, whole */

#define GM_VOLUME_FULL 256

#define GMS_STOPPED 0                  /* not started, stopped, or played to its end */
#define GMS_PLAYING 1
#define GMS_PAUSED  2

#define GM_LOOP_FOREVER (-1)

#endif
