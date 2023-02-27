/*******************************************************************************
 * Size: 40 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#include "lvgl.h"

#ifndef HEARTBEATFONT
#define HEARTBEATFONT 1
#endif

#if HEARTBEATFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E611 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x17, 0xbe, 0xed,
    0x94, 0x0, 0x0, 0x0, 0x0, 0x5, 0x9b, 0xb9,
    0x50, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4e, 0xff,
    0xff, 0xff, 0xfc, 0x40, 0x0, 0x0, 0x4d, 0xff,
    0xff, 0xff, 0xe7, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xa1, 0x0, 0x8f,
    0xff, 0xff, 0xff, 0xff, 0xfa, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0,
    0x0, 0x8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf2, 0x0, 0x0, 0xdf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x80, 0x0, 0x1f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x0, 0x3, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x3f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x0,
    0x2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf8, 0x0, 0x0, 0xcf, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x30, 0x0, 0x6, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd0, 0x4, 0x44, 0x5f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x5, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0,
    0x2b, 0xcc, 0xcc, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x30, 0x0, 0x0, 0x0, 0x2, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x5, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xa, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xd1, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xa, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xd1, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x5, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1, 0xaf, 0xff, 0xff,
    0xfc, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x39,
    0xef, 0xc6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,

    /* U+E73A "" */
    0x0, 0x0, 0x5, 0xab, 0xa6, 0x0, 0x0, 0x0,
    0x7b, 0xcb, 0x70, 0x0, 0x0, 0x0, 0x1, 0xcf,
    0xff, 0xff, 0xe4, 0x0, 0x4e, 0xff, 0xff, 0xfe,
    0x20, 0x0, 0x0, 0xb, 0xff, 0xff, 0xff, 0xff,
    0x22, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x0, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xff,
    0xff, 0xff, 0xf6, 0x0, 0x0, 0x9f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa,
    0x0, 0x0, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x0, 0x0, 0xcf,
    0xff, 0xff, 0xff, 0xff, 0xe9, 0xff, 0xff, 0xff,
    0xff, 0xfb, 0x0, 0x0, 0xaf, 0xff, 0xff, 0xff,
    0xff, 0x60, 0xcf, 0xff, 0xff, 0xff, 0xf9, 0x0,
    0x0, 0x7f, 0xff, 0xff, 0x7e, 0xfd, 0x0, 0x6f,
    0xff, 0xff, 0xff, 0xf6, 0x0, 0x0, 0x2f, 0xff,
    0xf7, 0x4, 0xf3, 0x0, 0xe, 0xff, 0xff, 0xff,
    0xf1, 0x0, 0x29, 0x90, 0x66, 0x50, 0x0, 0x40,
    0x0, 0x9, 0xf4, 0x0, 0x0, 0x4c, 0xc3, 0x3,
    0x32, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0xb0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0,

    /* U+E762 "" */
    0x0, 0x0, 0x0, 0x0, 0x25, 0x66, 0x40, 0x0,
    0x0, 0x0, 0x14, 0x66, 0x41, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7d, 0xff, 0xff, 0xff,
    0xa2, 0x0, 0x4c, 0xff, 0xff, 0xff, 0xc5, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3d, 0xff, 0xeb, 0x9a,
    0xdf, 0xff, 0x7a, 0xff, 0xfc, 0xa9, 0xcf, 0xff,
    0xb1, 0x0, 0x0, 0x0, 0x4, 0xff, 0xd5, 0x0,
    0x0, 0x2, 0xaf, 0xff, 0xf7, 0x10, 0x0, 0x0,
    0x7e, 0xfd, 0x10, 0x0, 0x0, 0x2f, 0xfa, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xfd, 0x20, 0x0, 0x0,
    0x0, 0x2, 0xdf, 0xc0, 0x0, 0x0, 0xbf, 0xb0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1e, 0xf6, 0x0, 0x3, 0xff,
    0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x5, 0xfe, 0x0, 0x9,
    0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xdf, 0x40,
    0xd, 0xf3, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8f,
    0x80, 0xf, 0xf1, 0x0, 0x0, 0x9, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x5f, 0xa0, 0xf, 0xf0, 0x0, 0x0, 0x1f, 0xff,
    0x50, 0x0, 0x0, 0xbb, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x5f, 0xa0, 0xe, 0xf2, 0x0, 0x0, 0x6f,
    0xef, 0xd0, 0x0, 0x7, 0xff, 0xc0, 0x0, 0x0,
    0x0, 0x0, 0x6f, 0x90, 0xb, 0xf6, 0x0, 0x0,
    0xdf, 0x5c, 0xf7, 0x0, 0xd, 0xff, 0xf9, 0x0,
    0x0, 0x0, 0x0, 0xaf, 0x60, 0x6, 0xff, 0xff,
    0xff, 0xfe, 0x4, 0xfe, 0x0, 0x4f, 0xe3, 0xff,
    0xff, 0xff, 0x20, 0x1, 0xff, 0x10, 0x0, 0xff,
    0xff, 0xff, 0xf7, 0x0, 0xbf, 0x80, 0xaf, 0x80,
    0x5f, 0xff, 0xfe, 0x30, 0xa, 0xfa, 0x0, 0x0,
    0x6f, 0xf3, 0x0, 0x0, 0x0, 0x3f, 0xf3, 0xff,
    0x10, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf2, 0x0,
    0x0, 0xa, 0xfe, 0x30, 0x0, 0x0, 0xa, 0xfe,
    0xfb, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0x50,
    0x0, 0x0, 0x0, 0xbf, 0xe3, 0x0, 0x0, 0x1,
    0xff, 0xf5, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xf7,
    0x0, 0x0, 0x0, 0x0, 0xb, 0xfe, 0x30, 0x0,
    0x0, 0x8f, 0xc0, 0x0, 0x0, 0x0, 0x6, 0xff,
    0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xe3,
    0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x6f,
    0xf7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xb,
    0xfe, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6,
    0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xe3, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x6f, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xb, 0xfe, 0x30, 0x0, 0x0, 0x0,
    0x7, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xbf, 0xe3, 0x0, 0x0,
    0x0, 0x7f, 0xf6, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xb, 0xfe, 0x30,
    0x0, 0x7, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0xf9, 0x55, 0xbf, 0xf5, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x9, 0xff, 0xff, 0xfe, 0x40, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x28, 0xaa, 0x61, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 640, .box_w = 35, .box_h = 27, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 473, .adv_w = 640, .box_w = 26, .box_h = 20, .ofs_x = 7, .ofs_y = 5},
    {.bitmap_index = 733, .adv_w = 640, .box_w = 34, .box_h = 28, .ofs_x = 3, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x129, 0x151
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58897, .range_length = 338, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t HeartBeatFont = {
#else
lv_font_t HeartBeatFont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 28,          /*The maximum line height required by the font*/
    .base_line = -1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HEARTBEATFONT*/
