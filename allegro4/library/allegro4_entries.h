/* Made by tools/gen_lib.py from include/allegro.h: do not edit. */

static int L__getpixel(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = _getpixel(bmp, x, y);
    LEAVE();
    return _r;
}

static void L__putpixel(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    _putpixel(bmp, x, y, color);
    LEAVE();
}

static void L_a4_flush_screen(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    a4_flush_screen();
    LEAVE();
}

static int L_a4_install(REG(a0, struct a4_public * pub), REG(d0, int system_id), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = a4_install(pub, system_id);
    LEAVE();
    return _r;
}

static void L_a4_mix_s16stereo(REG(a0, int16_t * out), REG(d0, int frames), REG(d1, int rate), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    a4_mix_s16stereo(out, frames, rate);
    LEAVE();
}

static void L_acquire_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    acquire_bitmap(bmp);
    LEAVE();
}

static void L_add_clip_rect(REG(a0, BITMAP * bitmap), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    add_clip_rect(bitmap, x1, y1, x2, y2);
    LEAVE();
}

static void L_adjust_sample(REG(a0, const SAMPLE * spl), REG(d0, int vol), REG(d1, int pan), REG(d2, int freq), REG(d3, int loop), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    adjust_sample(spl, vol, pan, freq, loop);
    LEAVE();
}

static void L_al_findclose(REG(a0, struct al_ffblk * info), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    al_findclose(info);
    LEAVE();
}

static int L_al_findfirst(REG(a0, const char * pattern), REG(a1, struct al_ffblk * info), REG(d0, int attrib), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = al_findfirst(pattern, info, attrib);
    LEAVE();
    return _r;
}

static int L_al_findnext(REG(a0, struct al_ffblk * info), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = al_findnext(info);
    LEAVE();
    return _r;
}

static int L_alert(REG(a0, const char * s1), REG(a1, const char * s2), REG(a2, const char * s3), REG(a3, const char * b1), REG(d0, const char * b2), REG(d1, int c1), REG(d2, int c2), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = alert(s1, s2, s3, b1, b2, c1, c2);
    LEAVE();
    return _r;
}

static int L_alert3(REG(a0, const char * s1), REG(a1, const char * s2), REG(a2, const char * s3), REG(a3, const char * b1), REG(d0, const char * b2), REG(d1, const char * b3), REG(d2, int c1), REG(d3, int c2), REG(d4, int c3), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = alert3(s1, s2, s3, b1, b2, b3, c1, c2, c3);
    LEAVE();
    return _r;
}

static void L_allegro_exit(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    allegro_exit();
    LEAVE();
}

static int L_allocate_voice(REG(a0, const SAMPLE * spl), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = allocate_voice(spl);
    LEAVE();
    return _r;
}

static char * L_append_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = append_filename(dest, path, filename, size);
    LEAVE();
    return _r;
}

static void L_arc(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, fixed ang1), REG(d3, fixed ang2), REG(d4, int r), REG(d5, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    arc(bmp, x, y, ang1, ang2, r, color);
    LEAVE();
}

static int L_bestfit_color(REG(a0, const RGB * pal), REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = bestfit_color(pal, r, g, b);
    LEAVE();
    return _r;
}

static int L_bitmap_color_depth(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = bitmap_color_depth(bmp);
    LEAVE();
    return _r;
}

static int L_bitmap_mask_color(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = bitmap_mask_color(bmp);
    LEAVE();
    return _r;
}

static void L_blit(REG(a0, BITMAP * source), REG(a1, BITMAP * dest), REG(d0, int source_x), REG(d1, int source_y), REG(d2, int dest_x), REG(d3, int dest_y), REG(d4, int width), REG(d5, int height), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    blit(source, dest, source_x, source_y, dest_x, dest_y, width, height);
    LEAVE();
}

static unsigned long L_bmp_read_line(REG(a0, BITMAP * bmp), REG(d0, int line), REG(a6, struct A4Base *_lb))
{
    unsigned long _r;
    ENTER(_lb);
    _r = bmp_read_line(bmp, line);
    LEAVE();
    return _r;
}

static void L_bmp_unwrite_line(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    bmp_unwrite_line(bmp);
    LEAVE();
}

static unsigned long L_bmp_write_line(REG(a0, BITMAP * bmp), REG(d0, int line), REG(a6, struct A4Base *_lb))
{
    unsigned long _r;
    ENTER(_lb);
    _r = bmp_write_line(bmp, line);
    LEAVE();
    return _r;
}

static int L_calibrate_joystick(REG(d0, int n), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = calibrate_joystick(n);
    LEAVE();
    return _r;
}

static const char * L_calibrate_joystick_name(REG(d0, int n), REG(a6, struct A4Base *_lb))
{
    const char * _r;
    ENTER(_lb);
    _r = calibrate_joystick_name(n);
    LEAVE();
    return _r;
}

static char * L_canonicalize_filename(REG(a0, char * dest), REG(a1, const char * filename), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = canonicalize_filename(dest, filename, size);
    LEAVE();
    return _r;
}

static void L_check_cpu(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    check_cpu();
    LEAVE();
}

static void L_circle(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int radius), REG(d3, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    circle(bmp, x, y, radius, color);
    LEAVE();
}

static void L_circlefill(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int radius), REG(d3, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    circlefill(bmp, x, y, radius, color);
    LEAVE();
}

static void L_clear_bitmap(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    clear_bitmap(bitmap);
    LEAVE();
}

static void L_clear_keybuf(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    clear_keybuf();
    LEAVE();
}

static void L_clear_to_color(REG(a0, BITMAP * bitmap), REG(d0, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    clear_to_color(bitmap, color);
    LEAVE();
}

static BITMAP * L_create_bitmap(REG(d0, int width), REG(d1, int height), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = create_bitmap(width, height);
    LEAVE();
    return _r;
}

static BITMAP * L_create_bitmap_ex(REG(d0, int color_depth), REG(d1, int width), REG(d2, int height), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = create_bitmap_ex(color_depth, width, height);
    LEAVE();
    return _r;
}

static void L_create_blender_table(REG(a0, COLOR_MAP * table), REG(a1, const RGB * pal), REG(a2, void(*callback)(int pos)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    create_blender_table(table, pal, callback);
    LEAVE();
}

static void L_create_color_table(REG(a0, COLOR_MAP * table), REG(a1, const RGB * pal), REG(a2, void(*blend)(const PALETTE pal, int x, int y, RGB *rgb)), REG(a3, void(*callback)(int pos)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    create_color_table(table, pal, blend, callback);
    LEAVE();
}

static DATAFILE_INDEX * L_create_datafile_index(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    DATAFILE_INDEX * _r;
    ENTER(_lb);
    _r = create_datafile_index(filename);
    LEAVE();
    return _r;
}

static void L_create_light_table(REG(a0, COLOR_MAP * table), REG(a1, const RGB * pal), REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a2, void(*callback)(int pos)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    create_light_table(table, pal, r, g, b, callback);
    LEAVE();
}

static void L_create_rgb_table(REG(a0, RGB_MAP * table), REG(a1, const RGB * pal), REG(a2, void(*callback)(int pos)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    create_rgb_table(table, pal, callback);
    LEAVE();
}

static SAMPLE * L_create_sample(REG(d0, int bits), REG(d1, int stereo), REG(d2, int freq), REG(d3, int len), REG(a6, struct A4Base *_lb))
{
    SAMPLE * _r;
    ENTER(_lb);
    _r = create_sample(bits, stereo, freq, len);
    LEAVE();
    return _r;
}

static BITMAP * L_create_sub_bitmap(REG(a0, BITMAP * parent), REG(d0, int x), REG(d1, int y), REG(d2, int width), REG(d3, int height), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = create_sub_bitmap(parent, x, y, width, height);
    LEAVE();
    return _r;
}

static BITMAP * L_create_system_bitmap(REG(d0, int width), REG(d1, int height), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = create_system_bitmap(width, height);
    LEAVE();
    return _r;
}

static void L_create_trans_table(REG(a0, COLOR_MAP * table), REG(a1, const RGB * pal), REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a2, void(*callback)(int pos)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    create_trans_table(table, pal, r, g, b, callback);
    LEAVE();
}

static BITMAP * L_create_video_bitmap(REG(d0, int width), REG(d1, int height), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = create_video_bitmap(width, height);
    LEAVE();
    return _r;
}

static void L_deallocate_voice(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    deallocate_voice(voice);
    LEAVE();
}

static int L_delete_file(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = delete_file(filename);
    LEAVE();
    return _r;
}

static int L_desktop_color_depth(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = desktop_color_depth();
    LEAVE();
    return _r;
}

static void L_destroy_bitmap(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_bitmap(bitmap);
    LEAVE();
}

static void L_destroy_datafile_index(REG(a0, DATAFILE_INDEX * index), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_datafile_index(index);
    LEAVE();
}

static void L_destroy_font(REG(a0, FONT * f), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_font(f);
    LEAVE();
}

static void L_destroy_gfx_mode_list(REG(a0, GFX_MODE_LIST * gfx_mode_list), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_gfx_mode_list(gfx_mode_list);
    LEAVE();
}

static void L_destroy_midi(REG(a0, MIDI * midi), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_midi(midi);
    LEAVE();
}

static void L_destroy_rle_sprite(REG(a0, RLE_SPRITE * sprite), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_rle_sprite(sprite);
    LEAVE();
}

static void L_destroy_sample(REG(a0, SAMPLE * spl), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    destroy_sample(spl);
    LEAVE();
}

static int L_detect_digi_driver(REG(d0, int driver_id), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = detect_digi_driver(driver_id);
    LEAVE();
    return _r;
}

static int L_detect_midi_driver(REG(d0, int driver_id), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = detect_midi_driver(driver_id);
    LEAVE();
    return _r;
}

static void L_disable_hardware_cursor(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    disable_hardware_cursor();
    LEAVE();
}

static void L_do_arc(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, fixed ang1), REG(d3, fixed ang2), REG(d4, int r), REG(d5, int d), REG(a1, void(*proc)(BITMAP *, int, int, int)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    do_arc(bmp, x, y, ang1, ang2, r, d, proc);
    LEAVE();
}

static void L_do_circle(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int radius), REG(d3, int d), REG(a1, void(*proc)(BITMAP *, int, int, int)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    do_circle(bmp, x, y, radius, d, proc);
    LEAVE();
}

static void L_do_ellipse(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int rx), REG(d3, int ry), REG(d4, int d), REG(a1, void(*proc)(BITMAP *, int, int, int)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    do_ellipse(bmp, x, y, rx, ry, d, proc);
    LEAVE();
}

static void L_do_line(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int d), REG(a1, void(*proc)(BITMAP *, int, int, int)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    do_line(bmp, x1, y1, x2, y2, d, proc);
    LEAVE();
}

static void L_draw_character_ex(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(d3, int bg), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_character_ex(bmp, sprite, x, y, color, bg);
    LEAVE();
}

static void L_draw_lit_rle_sprite(REG(a0, BITMAP * bmp), REG(a1, const RLE_SPRITE * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_lit_rle_sprite(bmp, sprite, x, y, color);
    LEAVE();
}

static void L_draw_lit_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_lit_sprite(bmp, sprite, x, y, color);
    LEAVE();
}

static void L_draw_rle_sprite(REG(a0, BITMAP * bmp), REG(a1, const RLE_SPRITE * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_rle_sprite(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_sprite(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite_ex(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int mode), REG(d3, int flip), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_sprite_ex(bmp, sprite, x, y, mode, flip);
    LEAVE();
}

static void L_draw_sprite_h_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_sprite_h_flip(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite_v_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_sprite_v_flip(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite_vh_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_sprite_vh_flip(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_trans_rle_sprite(REG(a0, BITMAP * bmp), REG(a1, const RLE_SPRITE * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_trans_rle_sprite(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_trans_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    draw_trans_sprite(bmp, sprite, x, y);
    LEAVE();
}

static void L_drawing_mode(REG(d0, int mode), REG(a0, BITMAP * pattern), REG(d1, int x_anchor), REG(d2, int y_anchor), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    drawing_mode(mode, pattern, x_anchor, y_anchor);
    LEAVE();
}

static void L_ellipse(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int rx), REG(d3, int ry), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    ellipse(bmp, x, y, rx, ry, color);
    LEAVE();
}

static void L_ellipsefill(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int rx), REG(d3, int ry), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    ellipsefill(bmp, x, y, rx, ry, color);
    LEAVE();
}

static void L_enable_hardware_cursor(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    enable_hardware_cursor();
    LEAVE();
}

static int L_enable_triple_buffer(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = enable_triple_buffer();
    LEAVE();
    return _r;
}

static int L_exists(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = exists(filename);
    LEAVE();
    return _r;
}

static void L_fade_from(REG(a0, const RGB * source), REG(a1, const RGB * dest), REG(d0, int speed), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_from(source, dest, speed);
    LEAVE();
}

static void L_fade_from_range(REG(a0, const RGB * source), REG(a1, const RGB * dest), REG(d0, int speed), REG(d1, int from), REG(d2, int to), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_from_range(source, dest, speed, from, to);
    LEAVE();
}

static void L_fade_in(REG(a0, const RGB * p), REG(d0, int speed), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_in(p, speed);
    LEAVE();
}

static void L_fade_in_range(REG(a0, const RGB * p), REG(d0, int speed), REG(d1, int from), REG(d2, int to), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_in_range(p, speed, from, to);
    LEAVE();
}

static void L_fade_interpolate(REG(a0, const RGB * source), REG(a1, const RGB * dest), REG(a2, RGB * output), REG(d0, int pos), REG(d1, int from), REG(d2, int to), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_interpolate(source, dest, output, pos, from, to);
    LEAVE();
}

static void L_fade_out(REG(d0, int speed), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_out(speed);
    LEAVE();
}

static void L_fade_out_range(REG(d0, int speed), REG(d1, int from), REG(d2, int to), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fade_out_range(speed, from, to);
    LEAVE();
}

static void L_fastline(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fastline(bmp, x1, y1, x2, y2, color);
    LEAVE();
}

static int L_file_exists(REG(a0, const char * filename), REG(d0, int attrib), REG(a1, int * aret), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = file_exists(filename, attrib, aret);
    LEAVE();
    return _r;
}

static long L_file_size(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = file_size(filename);
    LEAVE();
    return _r;
}

static time_t L_file_time(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    time_t _r;
    ENTER(_lb);
    _r = file_time(filename);
    LEAVE();
    return _r;
}

static int L_find_allegro_resource(REG(a0, char * dest), REG(a1, const char * resource), REG(a2, const char * ext), REG(a3, const char * datafile), REG(d0, const char * objectname), REG(d1, const char * envvar), REG(d2, const char * subdir), REG(d3, int size), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = find_allegro_resource(dest, resource, ext, datafile, objectname, envvar, subdir, size);
    LEAVE();
    return _r;
}

static DATAFILE * L_find_datafile_object(REG(a0, const DATAFILE * dat), REG(a1, const char * objectname), REG(a6, struct A4Base *_lb))
{
    DATAFILE * _r;
    ENTER(_lb);
    _r = find_datafile_object(dat, objectname);
    LEAVE();
    return _r;
}

static char * L_fix_filename_case(REG(a0, char * path), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = fix_filename_case(path);
    LEAVE();
    return _r;
}

static char * L_fix_filename_path(REG(a0, char * dest), REG(a1, const char * path), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = fix_filename_path(dest, path, size);
    LEAVE();
    return _r;
}

static char * L_fix_filename_slashes(REG(a0, char * path), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = fix_filename_slashes(path);
    LEAVE();
    return _r;
}

static fixed L_fixatan(REG(d0, fixed x), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixatan(x);
    LEAVE();
    return _r;
}

static fixed L_fixatan2(REG(d0, fixed y), REG(d1, fixed x), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixatan2(y, x);
    LEAVE();
    return _r;
}

static fixed L_fixcos(REG(d0, fixed x), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixcos(x);
    LEAVE();
    return _r;
}

static fixed L_fixhypot(REG(d0, fixed x), REG(d1, fixed y), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixhypot(x, y);
    LEAVE();
    return _r;
}

static fixed L_fixsin(REG(d0, fixed x), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixsin(x);
    LEAVE();
    return _r;
}

static fixed L_fixsqrt(REG(d0, fixed x), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixsqrt(x);
    LEAVE();
    return _r;
}

static fixed L_fixtan(REG(d0, fixed x), REG(a6, struct A4Base *_lb))
{
    fixed _r;
    ENTER(_lb);
    _r = fixtan(x);
    LEAVE();
    return _r;
}

static void L_fixup_datafile(REG(a0, DATAFILE * data), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    fixup_datafile(data);
    LEAVE();
}

static void L_floodfill(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    floodfill(bmp, x, y, color);
    LEAVE();
}

static void L_flush_config_file(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    flush_config_file();
    LEAVE();
}

static int L_font_has_alpha(REG(a0, FONT * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = font_has_alpha(f);
    LEAVE();
    return _r;
}

static int L_for_each_file_ex(REG(a0, const char * name), REG(d0, int in_attrib), REG(d1, int out_attrib), REG(a1, int(*callback)(const char *filename, int attrib, void *param)), REG(a2, void * param), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = for_each_file_ex(name, in_attrib, out_attrib, callback, param);
    LEAVE();
    return _r;
}

static void L_generate_332_palette(REG(a0, RGB * pal), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    generate_332_palette(pal);
    LEAVE();
}

static int L_generate_optimized_palette(REG(a0, struct BITMAP * image), REG(a1, RGB * pal), REG(a2, const signed char * rsvdcols), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = generate_optimized_palette(image, pal, rsvdcols);
    LEAVE();
    return _r;
}

static void L_get_clip_rect(REG(a0, BITMAP * bitmap), REG(a1, int * x1), REG(a2, int * y1), REG(a3, int * x2), REG(d0, int * y2), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_clip_rect(bitmap, x1, y1, x2, y2);
    LEAVE();
}

static int L_get_clip_state(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_clip_state(bitmap);
    LEAVE();
    return _r;
}

static void L_get_color(REG(d0, int idx), REG(a0, RGB * p), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_color(idx, p);
    LEAVE();
}

static int L_get_color_conversion(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_color_conversion();
    LEAVE();
    return _r;
}

static int L_get_color_depth(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_color_depth();
    LEAVE();
    return _r;
}

static int L_get_config_int(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int def), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_config_int(section, name, def);
    LEAVE();
    return _r;
}

static const char * L_get_config_string(REG(a0, const char * section), REG(a1, const char * name), REG(a2, const char * def), REG(a6, struct A4Base *_lb))
{
    const char * _r;
    ENTER(_lb);
    _r = get_config_string(section, name, def);
    LEAVE();
    return _r;
}

static const char * L_get_datafile_property(REG(a0, const DATAFILE * dat), REG(d0, int type), REG(a6, struct A4Base *_lb))
{
    const char * _r;
    ENTER(_lb);
    _r = get_datafile_property(dat, type);
    LEAVE();
    return _r;
}

static int L_get_desktop_resolution(REG(a0, int * width), REG(a1, int * height), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_desktop_resolution(width, height);
    LEAVE();
    return _r;
}

static int L_get_display_switch_mode(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_display_switch_mode();
    LEAVE();
    return _r;
}

static void L_get_executable_name(REG(a0, char * output), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_executable_name(output, size);
    LEAVE();
}

static char * L_get_extension(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = get_extension(filename);
    LEAVE();
    return _r;
}

static char * L_get_filename(REG(a0, const char * path), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = get_filename(path);
    LEAVE();
    return _r;
}

static int L_get_font_range_begin(REG(a0, FONT * f), REG(d0, int range), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_font_range_begin(f, range);
    LEAVE();
    return _r;
}

static int L_get_font_range_end(REG(a0, FONT * f), REG(d0, int range), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_font_range_end(f, range);
    LEAVE();
    return _r;
}

static int L_get_font_ranges(REG(a0, FONT * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_font_ranges(f);
    LEAVE();
    return _r;
}

static int L_get_gfx_mode(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_gfx_mode();
    LEAVE();
    return _r;
}

static GFX_MODE_LIST * L_get_gfx_mode_list(REG(d0, int card), REG(a6, struct A4Base *_lb))
{
    GFX_MODE_LIST * _r;
    ENTER(_lb);
    _r = get_gfx_mode_list(card);
    LEAVE();
    return _r;
}

static int L_get_gfx_mode_type(REG(d0, int graphics_card), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_gfx_mode_type(graphics_card);
    LEAVE();
    return _r;
}

static int L_get_midi_length(REG(a0, MIDI * midi), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_midi_length(midi);
    LEAVE();
    return _r;
}

static void L_get_mouse_mickeys(REG(a0, int * mickeyx), REG(a1, int * mickeyy), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_mouse_mickeys(mickeyx, mickeyy);
    LEAVE();
}

static void L_get_palette(REG(a0, RGB * p), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_palette(p);
    LEAVE();
}

static void L_get_palette_range(REG(a0, RGB * p), REG(d0, int from), REG(d1, int to), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_palette_range(p, from, to);
    LEAVE();
}

static int L_get_refresh_rate(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_refresh_rate();
    LEAVE();
    return _r;
}

static RLE_SPRITE * L_get_rle_sprite(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *_lb))
{
    RLE_SPRITE * _r;
    ENTER(_lb);
    _r = get_rle_sprite(bitmap);
    LEAVE();
    return _r;
}

static int L_get_uformat(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_uformat();
    LEAVE();
    return _r;
}

static void L_get_volume(REG(a0, int * digi_volume), REG(a1, int * midi_volume), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    get_volume(digi_volume, midi_volume);
    LEAVE();
}

static int L_geta(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = geta(c);
    LEAVE();
    return _r;
}

static int L_getb(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb(c);
    LEAVE();
    return _r;
}

static int L_getb8(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb8(c);
    LEAVE();
    return _r;
}

static int L_getb_depth(REG(d0, int color_depth), REG(d1, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb_depth(color_depth, c);
    LEAVE();
    return _r;
}

static int L_getg(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg(c);
    LEAVE();
    return _r;
}

static int L_getg8(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg8(c);
    LEAVE();
    return _r;
}

static int L_getg_depth(REG(d0, int color_depth), REG(d1, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg_depth(color_depth, c);
    LEAVE();
    return _r;
}

static int L_getpixel(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getpixel(bmp, x, y);
    LEAVE();
    return _r;
}

static int L_getr(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr(c);
    LEAVE();
    return _r;
}

static int L_getr8(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr8(c);
    LEAVE();
    return _r;
}

static int L_getr_depth(REG(d0, int color_depth), REG(d1, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr_depth(color_depth, c);
    LEAVE();
    return _r;
}

static void L_hline(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y), REG(d2, int x2), REG(d3, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    hline(bmp, x1, y, x2, color);
    LEAVE();
}

static int L_initialise_joystick(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = initialise_joystick();
    LEAVE();
    return _r;
}

static int L_install_int(REG(a0, void(*proc)(void)), REG(d0, long speed), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_int(proc, speed);
    LEAVE();
    return _r;
}

static int L_install_int_ex(REG(a0, void(*proc)(void)), REG(d0, long speed), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_int_ex(proc, speed);
    LEAVE();
    return _r;
}

static int L_install_joystick(REG(d0, int type), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_joystick(type);
    LEAVE();
    return _r;
}

static int L_install_keyboard(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_keyboard();
    LEAVE();
    return _r;
}

static void L_install_keyboard_hooks(REG(a0, int(*keypressed)(void)), REG(a1, int(*readkey)(void)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    install_keyboard_hooks(keypressed, readkey);
    LEAVE();
}

static int L_install_mouse(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_mouse();
    LEAVE();
    return _r;
}

static int L_install_param_int(REG(a0, void(*proc)(void *param)), REG(a1, void * param), REG(d0, long speed), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_param_int(proc, param, speed);
    LEAVE();
    return _r;
}

static int L_install_param_int_ex(REG(a0, void(*proc)(void *param)), REG(a1, void * param), REG(d0, long speed), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_param_int_ex(proc, param, speed);
    LEAVE();
    return _r;
}

static int L_install_sound(REG(d0, int digi), REG(d1, int midi), REG(a0, const char * cfg_path), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_sound(digi, midi, cfg_path);
    LEAVE();
    return _r;
}

static int L_install_timer(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = install_timer();
    LEAVE();
    return _r;
}

static int L_is_color_font(REG(a0, FONT * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_color_font(f);
    LEAVE();
    return _r;
}

static int L_is_inside_bitmap(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int clip), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_inside_bitmap(bmp, x, y, clip);
    LEAVE();
    return _r;
}

static int L_is_linear_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_linear_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_is_memory_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_memory_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_is_mono_font(REG(a0, FONT * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_mono_font(f);
    LEAVE();
    return _r;
}

static int L_is_planar_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_planar_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_is_relative_filename(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_relative_filename(filename);
    LEAVE();
    return _r;
}

static int L_is_same_bitmap(REG(a0, BITMAP * bmp1), REG(a1, BITMAP * bmp2), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_same_bitmap(bmp1, bmp2);
    LEAVE();
    return _r;
}

static int L_is_screen_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_screen_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_is_sub_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_sub_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_is_system_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_system_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_is_video_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_video_bitmap(bmp);
    LEAVE();
    return _r;
}

static int L_keyboard_needs_poll(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = keyboard_needs_poll();
    LEAVE();
    return _r;
}

static int L_keypressed(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = keypressed();
    LEAVE();
    return _r;
}

static void L_line(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    line(bmp, x1, y1, x2, y2, color);
    LEAVE();
}

static BITMAP * L_load_bitmap(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = load_bitmap(filename, pal);
    LEAVE();
    return _r;
}

static BITMAP * L_load_bmp(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = load_bmp(filename, pal);
    LEAVE();
    return _r;
}

static BITMAP * L_load_bmp_pf(REG(a0, PACKFILE * f), REG(a1, RGB * pal), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = load_bmp_pf(f, pal);
    LEAVE();
    return _r;
}

static DATAFILE * L_load_datafile(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    DATAFILE * _r;
    ENTER(_lb);
    _r = load_datafile(filename);
    LEAVE();
    return _r;
}

static DATAFILE * L_load_datafile_callback(REG(a0, const char * filename), REG(a1, void(*callback)(DATAFILE *)), REG(a6, struct A4Base *_lb))
{
    DATAFILE * _r;
    ENTER(_lb);
    _r = load_datafile_callback(filename, callback);
    LEAVE();
    return _r;
}

static DATAFILE * L_load_datafile_object(REG(a0, const char * filename), REG(a1, const char * objectname), REG(a6, struct A4Base *_lb))
{
    DATAFILE * _r;
    ENTER(_lb);
    _r = load_datafile_object(filename, objectname);
    LEAVE();
    return _r;
}

static DATAFILE * L_load_datafile_object_indexed(REG(a0, const DATAFILE_INDEX * index), REG(d0, int item), REG(a6, struct A4Base *_lb))
{
    DATAFILE * _r;
    ENTER(_lb);
    _r = load_datafile_object_indexed(index, item);
    LEAVE();
    return _r;
}

static FONT * L_load_font(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a2, void * param), REG(a6, struct A4Base *_lb))
{
    FONT * _r;
    ENTER(_lb);
    _r = load_font(filename, pal, param);
    LEAVE();
    return _r;
}

static int L_load_joystick_data(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = load_joystick_data(filename);
    LEAVE();
    return _r;
}

static MIDI * L_load_midi(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    MIDI * _r;
    ENTER(_lb);
    _r = load_midi(filename);
    LEAVE();
    return _r;
}

static BITMAP * L_load_pcx(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = load_pcx(filename, pal);
    LEAVE();
    return _r;
}

static BITMAP * L_load_pcx_pf(REG(a0, PACKFILE * f), REG(a1, RGB * pal), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = load_pcx_pf(f, pal);
    LEAVE();
    return _r;
}

static SAMPLE * L_load_sample(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    SAMPLE * _r;
    ENTER(_lb);
    _r = load_sample(filename);
    LEAVE();
    return _r;
}

static BITMAP * L_load_tga(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a6, struct A4Base *_lb))
{
    BITMAP * _r;
    ENTER(_lb);
    _r = load_tga(filename, pal);
    LEAVE();
    return _r;
}

static SAMPLE * L_load_voc(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    SAMPLE * _r;
    ENTER(_lb);
    _r = load_voc(filename);
    LEAVE();
    return _r;
}

static SAMPLE * L_load_wav(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    SAMPLE * _r;
    ENTER(_lb);
    _r = load_wav(filename);
    LEAVE();
    return _r;
}

static SAMPLE * L_load_wav_pf(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    SAMPLE * _r;
    ENTER(_lb);
    _r = load_wav_pf(f);
    LEAVE();
    return _r;
}

static void L_lock_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    lock_bitmap(bmp);
    LEAVE();
}

static char * L_make_absolute_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = make_absolute_filename(dest, path, filename, size);
    LEAVE();
    return _r;
}

static char * L_make_relative_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = make_relative_filename(dest, path, filename, size);
    LEAVE();
    return _r;
}

static int L_makeacol(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makeacol(r, g, b, a);
    LEAVE();
    return _r;
}

static int L_makeacol_depth(REG(d0, int color_depth), REG(d1, int r), REG(d2, int g), REG(d3, int b), REG(d4, int a), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makeacol_depth(color_depth, r, g, b, a);
    LEAVE();
    return _r;
}

static int L_makecol(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol(r, g, b);
    LEAVE();
    return _r;
}

static int L_makecol8(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol8(r, g, b);
    LEAVE();
    return _r;
}

static int L_makecol_depth(REG(d0, int color_depth), REG(d1, int r), REG(d2, int g), REG(d3, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol_depth(color_depth, r, g, b);
    LEAVE();
    return _r;
}

static void L_masked_blit(REG(a0, BITMAP * source), REG(a1, BITMAP * dest), REG(d0, int source_x), REG(d1, int source_y), REG(d2, int dest_x), REG(d3, int dest_y), REG(d4, int width), REG(d5, int height), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    masked_blit(source, dest, source_x, source_y, dest_x, dest_y, width, height);
    LEAVE();
}

static void L_masked_stretch_blit(REG(a0, BITMAP * source), REG(a1, BITMAP * dest), REG(d0, int source_x), REG(d1, int source_y), REG(d2, int source_w), REG(d3, int source_h), REG(d4, int dest_x), REG(d5, int dest_y), REG(d6, int dest_w), REG(d7, int dest_h), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    masked_stretch_blit(source, dest, source_x, source_y, source_w, source_h, dest_x, dest_y, dest_w, dest_h);
    LEAVE();
}

static void L_midi_pause(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    midi_pause();
    LEAVE();
}

static void L_midi_resume(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    midi_resume();
    LEAVE();
}

static int L_midi_seek(REG(d0, int target), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = midi_seek(target);
    LEAVE();
    return _r;
}

static int L_mouse_needs_poll(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = mouse_needs_poll();
    LEAVE();
    return _r;
}

static void L_override_config_file(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    override_config_file(filename);
    LEAVE();
}

static int L_pack_fclose(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_fclose(f);
    LEAVE();
    return _r;
}

static PACKFILE * L_pack_fclose_chunk(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    PACKFILE * _r;
    ENTER(_lb);
    _r = pack_fclose_chunk(f);
    LEAVE();
    return _r;
}

static int L_pack_feof(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_feof(f);
    LEAVE();
    return _r;
}

static int L_pack_ferror(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_ferror(f);
    LEAVE();
    return _r;
}

static char * L_pack_fgets(REG(a0, char * p), REG(d0, int max), REG(a1, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = pack_fgets(p, max, f);
    LEAVE();
    return _r;
}

static PACKFILE * L_pack_fopen(REG(a0, const char * filename), REG(a1, const char * mode), REG(a6, struct A4Base *_lb))
{
    PACKFILE * _r;
    ENTER(_lb);
    _r = pack_fopen(filename, mode);
    LEAVE();
    return _r;
}

static PACKFILE * L_pack_fopen_chunk(REG(a0, PACKFILE * f), REG(d0, int pack), REG(a6, struct A4Base *_lb))
{
    PACKFILE * _r;
    ENTER(_lb);
    _r = pack_fopen_chunk(f, pack);
    LEAVE();
    return _r;
}

static PACKFILE * L_pack_fopen_vtable(REG(a0, const PACKFILE_VTABLE * vtable), REG(a1, void * userdata), REG(a6, struct A4Base *_lb))
{
    PACKFILE * _r;
    ENTER(_lb);
    _r = pack_fopen_vtable(vtable, userdata);
    LEAVE();
    return _r;
}

static int L_pack_fputs(REG(a0, const char * p), REG(a1, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_fputs(p, f);
    LEAVE();
    return _r;
}

static long L_pack_fread(REG(a0, void * p), REG(d0, long n), REG(a1, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = pack_fread(p, n, f);
    LEAVE();
    return _r;
}

static int L_pack_fseek(REG(a0, PACKFILE * f), REG(d0, int offset), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_fseek(f, offset);
    LEAVE();
    return _r;
}

static long L_pack_fwrite(REG(a0, const void * p), REG(d0, long n), REG(a1, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = pack_fwrite(p, n, f);
    LEAVE();
    return _r;
}

static int L_pack_getc(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_getc(f);
    LEAVE();
    return _r;
}

static long L_pack_igetl(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = pack_igetl(f);
    LEAVE();
    return _r;
}

static int L_pack_igetw(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_igetw(f);
    LEAVE();
    return _r;
}

static long L_pack_iputl(REG(d0, long l), REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = pack_iputl(l, f);
    LEAVE();
    return _r;
}

static int L_pack_iputw(REG(d0, int w), REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_iputw(w, f);
    LEAVE();
    return _r;
}

static long L_pack_mgetl(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = pack_mgetl(f);
    LEAVE();
    return _r;
}

static int L_pack_mgetw(REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_mgetw(f);
    LEAVE();
    return _r;
}

static long L_pack_mputl(REG(d0, long l), REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    long _r;
    ENTER(_lb);
    _r = pack_mputl(l, f);
    LEAVE();
    return _r;
}

static int L_pack_mputw(REG(d0, int w), REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_mputw(w, f);
    LEAVE();
    return _r;
}

static int L_pack_putc(REG(d0, int c), REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_putc(c, f);
    LEAVE();
    return _r;
}

static int L_pack_ungetc(REG(d0, int c), REG(a0, PACKFILE * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = pack_ungetc(c, f);
    LEAVE();
    return _r;
}

static void L_packfile_password(REG(a0, const char * password), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    packfile_password(password);
    LEAVE();
}

static void L_pivot_scaled_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int cx), REG(d3, int cy), REG(d4, fixed angle), REG(d5, fixed scale), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    pivot_scaled_sprite(bmp, sprite, x, y, cx, cy, angle, scale);
    LEAVE();
}

static void L_pivot_scaled_sprite_v_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int cx), REG(d3, int cy), REG(d4, fixed angle), REG(d5, fixed scale), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    pivot_scaled_sprite_v_flip(bmp, sprite, x, y, cx, cy, angle, scale);
    LEAVE();
}

static void L_pivot_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int cx), REG(d3, int cy), REG(d4, fixed angle), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    pivot_sprite(bmp, sprite, x, y, cx, cy, angle);
    LEAVE();
}

static void L_pivot_sprite_v_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int cx), REG(d3, int cy), REG(d4, fixed angle), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    pivot_sprite_v_flip(bmp, sprite, x, y, cx, cy, angle);
    LEAVE();
}

static int L_play_looped_midi(REG(a0, MIDI * midi), REG(d0, int loop_start), REG(d1, int loop_end), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = play_looped_midi(midi, loop_start, loop_end);
    LEAVE();
    return _r;
}

static int L_play_midi(REG(a0, MIDI * midi), REG(d0, int loop), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = play_midi(midi, loop);
    LEAVE();
    return _r;
}

static int L_play_sample(REG(a0, const SAMPLE * spl), REG(d0, int vol), REG(d1, int pan), REG(d2, int freq), REG(d3, int loop), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = play_sample(spl, vol, pan, freq, loop);
    LEAVE();
    return _r;
}

static int L_poll_joystick(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = poll_joystick();
    LEAVE();
    return _r;
}

static int L_poll_keyboard(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = poll_keyboard();
    LEAVE();
    return _r;
}

static int L_poll_mouse(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = poll_mouse();
    LEAVE();
    return _r;
}

static int L_poll_scroll(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = poll_scroll();
    LEAVE();
    return _r;
}

static void L_polygon(REG(a0, BITMAP * bmp), REG(d0, int vertices), REG(a1, const int * points), REG(d1, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    polygon(bmp, vertices, points, color);
    LEAVE();
}

static void L_position_mouse(REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    position_mouse(x, y);
    LEAVE();
}

static void L_position_mouse_z(REG(d0, int z), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    position_mouse_z(z);
    LEAVE();
}

static void L_put_backslash(REG(a0, char * filename), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    put_backslash(filename);
    LEAVE();
}

static void L_putpixel(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    putpixel(bmp, x, y, color);
    LEAVE();
}

static int L_readkey(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = readkey();
    LEAVE();
    return _r;
}

static void L_reallocate_voice(REG(d0, int voice), REG(a0, const SAMPLE * spl), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    reallocate_voice(voice, spl);
    LEAVE();
}

static void L_rect(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rect(bmp, x1, y1, x2, y2, color);
    LEAVE();
}

static void L_rectfill(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rectfill(bmp, x1, y1, x2, y2, color);
    LEAVE();
}

static void L_register_bitmap_file_type(REG(a0, const char * ext), REG(a1, BITMAP *(*load)(const char *filename, RGB *pal)), REG(a2, int(*save)(const char *filename, BITMAP *bmp, const RGB *pal)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    register_bitmap_file_type(ext, load, save);
    LEAVE();
}

static void L_register_datafile_object(REG(d0, int id), REG(a0, void *(*load)(PACKFILE *f, long size)), REG(a1, void(*destroy)(void *data)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    register_datafile_object(id, load, destroy);
    LEAVE();
}

static void L_release_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    release_bitmap(bmp);
    LEAVE();
}

static void L_release_voice(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    release_voice(voice);
    LEAVE();
}

static void L_remove_display_switch_callback(REG(a0, void(*cb)(void)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_display_switch_callback(cb);
    LEAVE();
}

static void L_remove_int(REG(a0, void(*proc)(void)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_int(proc);
    LEAVE();
}

static void L_remove_joystick(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_joystick();
    LEAVE();
}

static void L_remove_keyboard(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_keyboard();
    LEAVE();
}

static void L_remove_mouse(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_mouse();
    LEAVE();
}

static void L_remove_param_int(REG(a0, void(*proc)(void *param)), REG(a1, void * param), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_param_int(proc, param);
    LEAVE();
}

static void L_remove_sound(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_sound();
    LEAVE();
}

static void L_remove_timer(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    remove_timer();
    LEAVE();
}

static char * L_replace_extension(REG(a0, char * dest), REG(a1, const char * filename), REG(a2, const char * ext), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = replace_extension(dest, filename, ext, size);
    LEAVE();
    return _r;
}

static char * L_replace_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = replace_filename(dest, path, filename, size);
    LEAVE();
    return _r;
}

static void L_request_refresh_rate(REG(d0, int rate), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    request_refresh_rate(rate);
    LEAVE();
}

static int L_request_scroll(REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = request_scroll(x, y);
    LEAVE();
    return _r;
}

static int L_request_video_bitmap(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = request_video_bitmap(bitmap);
    LEAVE();
    return _r;
}

static void L_reserve_voices(REG(d0, int digi_voices), REG(d1, int midi_voices), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    reserve_voices(digi_voices, midi_voices);
    LEAVE();
}

static void L_rest(REG(d0, unsigned int time), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rest(time);
    LEAVE();
}

static void L_rest_callback(REG(d0, unsigned int time), REG(a0, void(*callback)(void)), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rest_callback(time, callback);
    LEAVE();
}

static void L_rotate_scaled_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, fixed angle), REG(d3, fixed scale), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rotate_scaled_sprite(bmp, sprite, x, y, angle, scale);
    LEAVE();
}

static void L_rotate_scaled_sprite_v_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, fixed angle), REG(d3, fixed scale), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rotate_scaled_sprite_v_flip(bmp, sprite, x, y, angle, scale);
    LEAVE();
}

static void L_rotate_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, fixed angle), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rotate_sprite(bmp, sprite, x, y, angle);
    LEAVE();
}

static void L_rotate_sprite_v_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, fixed angle), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    rotate_sprite_v_flip(bmp, sprite, x, y, angle);
    LEAVE();
}

static int L_save_bitmap(REG(a0, const char * filename), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_bitmap(filename, bmp, pal);
    LEAVE();
    return _r;
}

static int L_save_bmp(REG(a0, const char * filename), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_bmp(filename, bmp, pal);
    LEAVE();
    return _r;
}

static int L_save_bmp_pf(REG(a0, PACKFILE * f), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_bmp_pf(f, bmp, pal);
    LEAVE();
    return _r;
}

static int L_save_joystick_data(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_joystick_data(filename);
    LEAVE();
    return _r;
}

static int L_save_pcx(REG(a0, const char * filename), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_pcx(filename, bmp, pal);
    LEAVE();
    return _r;
}

static int L_save_pcx_pf(REG(a0, PACKFILE * f), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_pcx_pf(f, bmp, pal);
    LEAVE();
    return _r;
}

static int L_save_sample(REG(a0, const char * filename), REG(a1, SAMPLE * spl), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = save_sample(filename, spl);
    LEAVE();
    return _r;
}

static int L_scancode_to_ascii(REG(d0, int scancode), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = scancode_to_ascii(scancode);
    LEAVE();
    return _r;
}

static const char * L_scancode_to_name(REG(d0, int scancode), REG(a6, struct A4Base *_lb))
{
    const char * _r;
    ENTER(_lb);
    _r = scancode_to_name(scancode);
    LEAVE();
    return _r;
}

static void L_scare_mouse(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    scare_mouse();
    LEAVE();
}

static void L_scare_mouse_area(REG(d0, int x), REG(d1, int y), REG(d2, int w), REG(d3, int h), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    scare_mouse_area(x, y, w, h);
    LEAVE();
}

static int L_scroll_screen(REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = scroll_screen(x, y);
    LEAVE();
    return _r;
}

static void L_select_mouse_cursor(REG(d0, int cursor), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    select_mouse_cursor(cursor);
    LEAVE();
}

static void L_select_palette(REG(a0, const RGB * p), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    select_palette(p);
    LEAVE();
}

static void L_set_clip_rect(REG(a0, BITMAP * bitmap), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_clip_rect(bitmap, x1, y1, x2, y2);
    LEAVE();
}

static void L_set_clip_state(REG(a0, BITMAP * bitmap), REG(d0, int state), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_clip_state(bitmap, state);
    LEAVE();
}

static int L_set_close_button_callback(REG(a0, void(*proc)(void)), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = set_close_button_callback(proc);
    LEAVE();
    return _r;
}

static void L_set_color(REG(d0, int idx), REG(a0, const RGB * p), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_color(idx, p);
    LEAVE();
}

static void L_set_color_conversion(REG(d0, int mode), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_color_conversion(mode);
    LEAVE();
}

static void L_set_color_depth(REG(d0, int depth), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_color_depth(depth);
    LEAVE();
}

static void L_set_config_file(REG(a0, const char * filename), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_config_file(filename);
    LEAVE();
}

static void L_set_config_int(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int val), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_config_int(section, name, val);
    LEAVE();
}

static void L_set_config_string(REG(a0, const char * section), REG(a1, const char * name), REG(a2, const char * val), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_config_string(section, name, val);
    LEAVE();
}

static int L_set_display_switch_callback(REG(d0, int dir), REG(a0, void(*cb)(void)), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = set_display_switch_callback(dir, cb);
    LEAVE();
    return _r;
}

static int L_set_display_switch_mode(REG(d0, int mode), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = set_display_switch_mode(mode);
    LEAVE();
    return _r;
}

static int L_set_gfx_mode(REG(d0, int card), REG(d1, int w), REG(d2, int h), REG(d3, int v_w), REG(d4, int v_h), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = set_gfx_mode(card, w, h, v_w, v_h);
    LEAVE();
    return _r;
}

static void L_set_hardware_volume(REG(d0, int digi_volume), REG(d1, int midi_volume), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_hardware_volume(digi_volume, midi_volume);
    LEAVE();
}

static void L_set_keyboard_rate(REG(d0, int delay), REG(d1, int repeat), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_keyboard_rate(delay, repeat);
    LEAVE();
}

static void L_set_leds(REG(d0, int leds), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_leds(leds);
    LEAVE();
}

static void L_set_mouse_range(REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_mouse_range(x1, y1, x2, y2);
    LEAVE();
}

static void L_set_mouse_speed(REG(d0, int xspeed), REG(d1, int yspeed), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_mouse_speed(xspeed, yspeed);
    LEAVE();
}

static void L_set_mouse_sprite(REG(a0, BITMAP * sprite), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_mouse_sprite(sprite);
    LEAVE();
}

static void L_set_mouse_sprite_focus(REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_mouse_sprite_focus(x, y);
    LEAVE();
}

static void L_set_palette(REG(a0, const RGB * p), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_palette(p);
    LEAVE();
}

static void L_set_palette_range(REG(a0, const RGB * p), REG(d0, int from), REG(d1, int to), REG(d2, int retracesync), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_palette_range(p, from, to, retracesync);
    LEAVE();
}

static void L_set_uformat(REG(d0, int type), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_uformat(type);
    LEAVE();
}

static void L_set_volume(REG(d0, int digi_volume), REG(d1, int midi_volume), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_volume(digi_volume, midi_volume);
    LEAVE();
}

static void L_set_volume_per_voice(REG(d0, int scale), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_volume_per_voice(scale);
    LEAVE();
}

static void L_set_window_title(REG(a0, const char * name), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_window_title(name);
    LEAVE();
}

static void L_show_mouse(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    show_mouse(bmp);
    LEAVE();
}

static int L_show_os_cursor(REG(d0, int cursor), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = show_os_cursor(cursor);
    LEAVE();
    return _r;
}

static int L_show_video_bitmap(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = show_video_bitmap(bitmap);
    LEAVE();
    return _r;
}

static void L_simulate_keypress(REG(d0, int keycode), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    simulate_keypress(keycode);
    LEAVE();
}

static void L_simulate_ukeypress(REG(d0, int keycode), REG(d1, int scancode), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    simulate_ukeypress(keycode, scancode);
    LEAVE();
}

static void L_solid_mode(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    solid_mode();
    LEAVE();
}

static void L_spline(REG(a0, BITMAP * bmp), REG(a1, const int * points), REG(d0, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    spline(bmp, points, color);
    LEAVE();
}

static void L_stop_midi(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    stop_midi();
    LEAVE();
}

static void L_stop_sample(REG(a0, const SAMPLE * spl), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    stop_sample(spl);
    LEAVE();
}

static void L_stretch_blit(REG(a0, BITMAP * source), REG(a1, BITMAP * dest), REG(d0, int source_x), REG(d1, int source_y), REG(d2, int source_width), REG(d3, int source_height), REG(d4, int dest_x), REG(d5, int dest_y), REG(d6, int dest_width), REG(d7, int dest_height), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    stretch_blit(source, dest, source_x, source_y, source_width, source_height, dest_x, dest_y, dest_width, dest_height);
    LEAVE();
}

static void L_stretch_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int w), REG(d3, int h), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    stretch_sprite(bmp, sprite, x, y, w, h);
    LEAVE();
}

static int L_text_height(REG(a0, const FONT * f), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = text_height(f);
    LEAVE();
    return _r;
}

static int L_text_length(REG(a0, const FONT * f), REG(a1, const char * str), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = text_length(f, str);
    LEAVE();
    return _r;
}

static int L_text_mode(REG(d0, int mode), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = text_mode(mode);
    LEAVE();
    return _r;
}

static void L_textout(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout(bmp, f, s, x, y, color);
    LEAVE();
}

static void L_textout_centre(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_centre(bmp, f, s, x, y, color);
    LEAVE();
}

static void L_textout_centre_ex(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(d3, int bg), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_centre_ex(bmp, f, s, x, y, color, bg);
    LEAVE();
}

static void L_textout_ex(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(d3, int bg), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_ex(bmp, f, s, x, y, color, bg);
    LEAVE();
}

static void L_textout_justify(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x1), REG(d1, int x2), REG(d2, int y), REG(d3, int diff), REG(d4, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_justify(bmp, f, s, x1, x2, y, diff, color);
    LEAVE();
}

static void L_textout_justify_ex(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x1), REG(d1, int x2), REG(d2, int y), REG(d3, int diff), REG(d4, int color), REG(d5, int bg), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_justify_ex(bmp, f, s, x1, x2, y, diff, color, bg);
    LEAVE();
}

static void L_textout_right(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_right(bmp, f, s, x, y, color);
    LEAVE();
}

static void L_textout_right_ex(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(d3, int bg), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    textout_right_ex(bmp, f, s, x, y, color, bg);
    LEAVE();
}

static int L_timer_can_simulate_retrace(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = timer_can_simulate_retrace();
    LEAVE();
    return _r;
}

static int L_timer_is_using_retrace(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = timer_is_using_retrace();
    LEAVE();
    return _r;
}

static void L_timer_simulate_retrace(REG(d0, int enable), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    timer_simulate_retrace(enable);
    LEAVE();
}

static void L_triangle(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int x3), REG(d5, int y3), REG(d6, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    triangle(bmp, x1, y1, x2, y2, x3, y3, color);
    LEAVE();
}

static const char * L_uconvert(REG(a0, const char * s), REG(d0, int type), REG(a1, char * buf), REG(d1, int newtype), REG(d2, int size), REG(a6, struct A4Base *_lb))
{
    const char * _r;
    ENTER(_lb);
    _r = uconvert(s, type, buf, newtype, size);
    LEAVE();
    return _r;
}

static int L_uinsert(REG(a0, char * s), REG(d0, int index), REG(d1, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = uinsert(s, index, c);
    LEAVE();
    return _r;
}

static void L_unload_datafile(REG(a0, DATAFILE * dat), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    unload_datafile(dat);
    LEAVE();
}

static void L_unload_datafile_object(REG(a0, DATAFILE * dat), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    unload_datafile_object(dat);
    LEAVE();
}

static void L_unscare_mouse(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    unscare_mouse();
    LEAVE();
}

static void L_unselect_palette(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    unselect_palette();
    LEAVE();
}

static int L_ureadkey(REG(a0, int * scancode), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = ureadkey(scancode);
    LEAVE();
    return _r;
}

static int L_uremove(REG(a0, char * s), REG(d0, int index), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = uremove(s, index);
    LEAVE();
    return _r;
}

static int L_usetat(REG(a0, char * s), REG(d0, int index), REG(d1, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = usetat(s, index, c);
    LEAVE();
    return _r;
}

static int L_ustricmp(REG(a0, const char * s1), REG(a1, const char * s2), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = ustricmp(s1, s2);
    LEAVE();
    return _r;
}

static char * L_ustrlwr(REG(a0, char * s), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrlwr(s);
    LEAVE();
    return _r;
}

static int L_ustrnicmp(REG(a0, const char * s1), REG(a1, const char * s2), REG(d0, int n), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = ustrnicmp(s1, s2, n);
    LEAVE();
    return _r;
}

static char * L_ustrtok(REG(a0, char * s), REG(a1, const char * set), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrtok(s, set);
    LEAVE();
    return _r;
}

static char * L_ustrtok_r(REG(a0, char * s), REG(a1, const char * set), REG(a2, char ** last), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrtok_r(s, set, last);
    LEAVE();
    return _r;
}

static char * L_ustrupr(REG(a0, char * s), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrupr(s);
    LEAVE();
    return _r;
}

static char * L_ustrzcat(REG(a0, char * dest), REG(d0, int size), REG(a1, const char * src), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrzcat(dest, size, src);
    LEAVE();
    return _r;
}

static char * L_ustrzcpy(REG(a0, char * dest), REG(d0, int size), REG(a1, const char * src), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrzcpy(dest, size, src);
    LEAVE();
    return _r;
}

static char * L_ustrzncpy(REG(a0, char * dest), REG(d0, int size), REG(a1, const char * src), REG(d1, int n), REG(a6, struct A4Base *_lb))
{
    char * _r;
    ENTER(_lb);
    _r = ustrzncpy(dest, size, src, n);
    LEAVE();
    return _r;
}

static void L_vline(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y1), REG(d2, int y2), REG(d3, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    vline(bmp, x, y1, y2, color);
    LEAVE();
}

static SAMPLE * L_voice_check(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    SAMPLE * _r;
    ENTER(_lb);
    _r = voice_check(voice);
    LEAVE();
    return _r;
}

static int L_voice_get_frequency(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = voice_get_frequency(voice);
    LEAVE();
    return _r;
}

static int L_voice_get_pan(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = voice_get_pan(voice);
    LEAVE();
    return _r;
}

static int L_voice_get_position(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = voice_get_position(voice);
    LEAVE();
    return _r;
}

static int L_voice_get_volume(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = voice_get_volume(voice);
    LEAVE();
    return _r;
}

static void L_voice_set_frequency(REG(d0, int voice), REG(d1, int frequency), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_set_frequency(voice, frequency);
    LEAVE();
}

static void L_voice_set_pan(REG(d0, int voice), REG(d1, int pan), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_set_pan(voice, pan);
    LEAVE();
}

static void L_voice_set_playmode(REG(d0, int voice), REG(d1, int playmode), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_set_playmode(voice, playmode);
    LEAVE();
}

static void L_voice_set_position(REG(d0, int voice), REG(d1, int position), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_set_position(voice, position);
    LEAVE();
}

static void L_voice_set_priority(REG(d0, int voice), REG(d1, int priority), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_set_priority(voice, priority);
    LEAVE();
}

static void L_voice_set_volume(REG(d0, int voice), REG(d1, int volume), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_set_volume(voice, volume);
    LEAVE();
}

static void L_voice_start(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_start(voice);
    LEAVE();
}

static void L_voice_stop(REG(d0, int voice), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    voice_stop(voice);
    LEAVE();
}

static void L_vsync(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    vsync();
    LEAVE();
}

static void L_xor_mode(REG(d0, int on), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    xor_mode(on);
    LEAVE();
}

static void L_yield_timeslice(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    yield_timeslice();
    LEAVE();
}

static void L_pop_config_state(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    pop_config_state();
    LEAVE();
}

static void L_push_config_state(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    push_config_state();
    LEAVE();
}

static FONT * L_grab_font_from_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *_lb))
{
    FONT * _r;
    ENTER(_lb);
    _r = grab_font_from_bitmap(bmp);
    LEAVE();
    return _r;
}

static FONT * L_load_dat_font(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a2, void * param), REG(a6, struct A4Base *_lb))
{
    FONT * _r;
    ENTER(_lb);
    _r = load_dat_font(filename, pal, param);
    LEAVE();
    return _r;
}

static void L_midi_out(REG(a0, unsigned char * data), REG(d0, int length), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    midi_out(data, length);
    LEAVE();
}

static int L_get_config_hex(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int def), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_config_hex(section, name, def);
    LEAVE();
    return _r;
}

static int L_get_config_id(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int def), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_config_id(section, name, def);
    LEAVE();
    return _r;
}

static void L_override_config_data(REG(a0, const char * data), REG(d0, int length), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    override_config_data(data, length);
    LEAVE();
}

static void L_set_config_data(REG(a0, const char * data), REG(d0, int length), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_config_data(data, length);
    LEAVE();
}

static void L_set_config_hex(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int val), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_config_hex(section, name, val);
    LEAVE();
}

static void L_set_config_id(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int val), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_config_id(section, name, val);
    LEAVE();
}

static char ** L_get_config_argv(REG(a0, const char * section), REG(a1, const char * name), REG(a2, int * argc), REG(a6, struct A4Base *_lb))
{
    char ** _r;
    ENTER(_lb);
    _r = get_config_argv(section, name, argc);
    LEAVE();
    return _r;
}

static int L__getpixel15(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = _getpixel15(bmp, x, y);
    LEAVE();
    return _r;
}

static int L__getpixel16(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = _getpixel16(bmp, x, y);
    LEAVE();
    return _r;
}

static int L__getpixel24(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = _getpixel24(bmp, x, y);
    LEAVE();
    return _r;
}

static int L__getpixel32(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = _getpixel32(bmp, x, y);
    LEAVE();
    return _r;
}

static void L__putpixel15(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    _putpixel15(bmp, x, y, color);
    LEAVE();
}

static void L__putpixel16(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    _putpixel16(bmp, x, y, color);
    LEAVE();
}

static void L__putpixel24(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    _putpixel24(bmp, x, y, color);
    LEAVE();
}

static void L__putpixel32(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    _putpixel32(bmp, x, y, color);
    LEAVE();
}

static int L_get_mixer_bits(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_mixer_bits();
    LEAVE();
    return _r;
}

static int L_get_mixer_channels(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_mixer_channels();
    LEAVE();
    return _r;
}

static int L_get_mixer_frequency(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_mixer_frequency();
    LEAVE();
    return _r;
}

static int L_get_mixer_quality(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_mixer_quality();
    LEAVE();
    return _r;
}

static int L_get_mixer_voices(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = get_mixer_voices();
    LEAVE();
    return _r;
}

static int L_geta32(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = geta32(c);
    LEAVE();
    return _r;
}

static int L_geta_depth(REG(d0, int color_depth), REG(d1, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = geta_depth(color_depth, c);
    LEAVE();
    return _r;
}

static int L_getb15(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb15(c);
    LEAVE();
    return _r;
}

static int L_getb16(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb16(c);
    LEAVE();
    return _r;
}

static int L_getb24(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb24(c);
    LEAVE();
    return _r;
}

static int L_getb32(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getb32(c);
    LEAVE();
    return _r;
}

static int L_getg15(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg15(c);
    LEAVE();
    return _r;
}

static int L_getg16(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg16(c);
    LEAVE();
    return _r;
}

static int L_getg24(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg24(c);
    LEAVE();
    return _r;
}

static int L_getg32(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getg32(c);
    LEAVE();
    return _r;
}

static int L_getr15(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr15(c);
    LEAVE();
    return _r;
}

static int L_getr16(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr16(c);
    LEAVE();
    return _r;
}

static int L_getr24(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr24(c);
    LEAVE();
    return _r;
}

static int L_getr32(REG(d0, int c), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = getr32(c);
    LEAVE();
    return _r;
}

static int L_makeacol32(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makeacol32(r, g, b, a);
    LEAVE();
    return _r;
}

static int L_makecol15(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol15(r, g, b);
    LEAVE();
    return _r;
}

static int L_makecol16(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol16(r, g, b);
    LEAVE();
    return _r;
}

static int L_makecol24(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol24(r, g, b);
    LEAVE();
    return _r;
}

static int L_makecol32(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = makecol32(r, g, b);
    LEAVE();
    return _r;
}

static void L_set_add_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_add_blender(r, g, b, a);
    LEAVE();
}

static void L_set_alpha_blender(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_alpha_blender();
    LEAVE();
}

static void L_set_burn_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_burn_blender(r, g, b, a);
    LEAVE();
}

static void L_set_difference_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_difference_blender(r, g, b, a);
    LEAVE();
}

static void L_set_dodge_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_dodge_blender(r, g, b, a);
    LEAVE();
}

static void L_set_invert_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_invert_blender(r, g, b, a);
    LEAVE();
}

static void L_set_mixer_quality(REG(d0, int quality), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_mixer_quality(quality);
    LEAVE();
}

static void L_set_multiply_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_multiply_blender(r, g, b, a);
    LEAVE();
}

static void L_set_screen_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_screen_blender(r, g, b, a);
    LEAVE();
}

static void L_set_trans_blender(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_trans_blender(r, g, b, a);
    LEAVE();
}

static void L_set_write_alpha_blender(REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    set_write_alpha_blender();
    LEAVE();
}

static int L_is_windowed_mode(REG(a6, struct A4Base *_lb))
{
    int _r;
    ENTER(_lb);
    _r = is_windowed_mode();
    LEAVE();
    return _r;
}

static FONT * L_load_bitmap_font(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a2, void * param), REG(a6, struct A4Base *_lb))
{
    FONT * _r;
    ENTER(_lb);
    _r = load_bitmap_font(filename, pal, param);
    LEAVE();
    return _r;
}

static void L_make_trans_font(REG(a0, FONT * f), REG(a6, struct A4Base *_lb))
{
    ENTER(_lb);
    make_trans_font(f);
    LEAVE();
}

static const APTR a4_vectors[] = {
    (APTR)lib_open, (APTR)lib_close, (APTR)lib_expunge, (APTR)lib_null,
    (APTR)L__getpixel,
    (APTR)L__putpixel,
    (APTR)L_a4_flush_screen,
    (APTR)L_a4_install,
    (APTR)L_a4_mix_s16stereo,
    (APTR)L_acquire_bitmap,
    (APTR)L_add_clip_rect,
    (APTR)L_adjust_sample,
    (APTR)L_al_findclose,
    (APTR)L_al_findfirst,
    (APTR)L_al_findnext,
    (APTR)L_alert,
    (APTR)L_alert3,
    (APTR)L_allegro_exit,
    (APTR)L_allocate_voice,
    (APTR)L_append_filename,
    (APTR)L_arc,
    (APTR)L_bestfit_color,
    (APTR)L_bitmap_color_depth,
    (APTR)L_bitmap_mask_color,
    (APTR)L_blit,
    (APTR)L_bmp_read_line,
    (APTR)L_bmp_unwrite_line,
    (APTR)L_bmp_write_line,
    (APTR)L_calibrate_joystick,
    (APTR)L_calibrate_joystick_name,
    (APTR)L_canonicalize_filename,
    (APTR)L_check_cpu,
    (APTR)L_circle,
    (APTR)L_circlefill,
    (APTR)L_clear_bitmap,
    (APTR)L_clear_keybuf,
    (APTR)L_clear_to_color,
    (APTR)L_create_bitmap,
    (APTR)L_create_bitmap_ex,
    (APTR)L_create_blender_table,
    (APTR)L_create_color_table,
    (APTR)L_create_datafile_index,
    (APTR)L_create_light_table,
    (APTR)L_create_rgb_table,
    (APTR)L_create_sample,
    (APTR)L_create_sub_bitmap,
    (APTR)L_create_system_bitmap,
    (APTR)L_create_trans_table,
    (APTR)L_create_video_bitmap,
    (APTR)L_deallocate_voice,
    (APTR)L_delete_file,
    (APTR)L_desktop_color_depth,
    (APTR)L_destroy_bitmap,
    (APTR)L_destroy_datafile_index,
    (APTR)L_destroy_font,
    (APTR)L_destroy_gfx_mode_list,
    (APTR)L_destroy_midi,
    (APTR)L_destroy_rle_sprite,
    (APTR)L_destroy_sample,
    (APTR)L_detect_digi_driver,
    (APTR)L_detect_midi_driver,
    (APTR)L_disable_hardware_cursor,
    (APTR)L_do_arc,
    (APTR)L_do_circle,
    (APTR)L_do_ellipse,
    (APTR)L_do_line,
    (APTR)L_draw_character_ex,
    (APTR)L_draw_lit_rle_sprite,
    (APTR)L_draw_lit_sprite,
    (APTR)L_draw_rle_sprite,
    (APTR)L_draw_sprite,
    (APTR)L_draw_sprite_ex,
    (APTR)L_draw_sprite_h_flip,
    (APTR)L_draw_sprite_v_flip,
    (APTR)L_draw_sprite_vh_flip,
    (APTR)L_draw_trans_rle_sprite,
    (APTR)L_draw_trans_sprite,
    (APTR)L_drawing_mode,
    (APTR)L_ellipse,
    (APTR)L_ellipsefill,
    (APTR)L_enable_hardware_cursor,
    (APTR)L_enable_triple_buffer,
    (APTR)L_exists,
    (APTR)L_fade_from,
    (APTR)L_fade_from_range,
    (APTR)L_fade_in,
    (APTR)L_fade_in_range,
    (APTR)L_fade_interpolate,
    (APTR)L_fade_out,
    (APTR)L_fade_out_range,
    (APTR)L_fastline,
    (APTR)L_file_exists,
    (APTR)L_file_size,
    (APTR)L_file_time,
    (APTR)L_find_allegro_resource,
    (APTR)L_find_datafile_object,
    (APTR)L_fix_filename_case,
    (APTR)L_fix_filename_path,
    (APTR)L_fix_filename_slashes,
    (APTR)L_fixatan,
    (APTR)L_fixatan2,
    (APTR)L_fixcos,
    (APTR)L_fixhypot,
    (APTR)L_fixsin,
    (APTR)L_fixsqrt,
    (APTR)L_fixtan,
    (APTR)L_fixup_datafile,
    (APTR)L_floodfill,
    (APTR)L_flush_config_file,
    (APTR)L_font_has_alpha,
    (APTR)L_for_each_file_ex,
    (APTR)L_generate_332_palette,
    (APTR)L_generate_optimized_palette,
    (APTR)L_get_clip_rect,
    (APTR)L_get_clip_state,
    (APTR)L_get_color,
    (APTR)L_get_color_conversion,
    (APTR)L_get_color_depth,
    (APTR)L_get_config_int,
    (APTR)L_get_config_string,
    (APTR)L_get_datafile_property,
    (APTR)L_get_desktop_resolution,
    (APTR)L_get_display_switch_mode,
    (APTR)L_get_executable_name,
    (APTR)L_get_extension,
    (APTR)L_get_filename,
    (APTR)L_get_font_range_begin,
    (APTR)L_get_font_range_end,
    (APTR)L_get_font_ranges,
    (APTR)L_get_gfx_mode,
    (APTR)L_get_gfx_mode_list,
    (APTR)L_get_gfx_mode_type,
    (APTR)L_get_midi_length,
    (APTR)L_get_mouse_mickeys,
    (APTR)L_get_palette,
    (APTR)L_get_palette_range,
    (APTR)L_get_refresh_rate,
    (APTR)L_get_rle_sprite,
    (APTR)L_get_uformat,
    (APTR)L_get_volume,
    (APTR)L_geta,
    (APTR)L_getb,
    (APTR)L_getb8,
    (APTR)L_getb_depth,
    (APTR)L_getg,
    (APTR)L_getg8,
    (APTR)L_getg_depth,
    (APTR)L_getpixel,
    (APTR)L_getr,
    (APTR)L_getr8,
    (APTR)L_getr_depth,
    (APTR)L_hline,
    (APTR)L_initialise_joystick,
    (APTR)L_install_int,
    (APTR)L_install_int_ex,
    (APTR)L_install_joystick,
    (APTR)L_install_keyboard,
    (APTR)L_install_keyboard_hooks,
    (APTR)L_install_mouse,
    (APTR)L_install_param_int,
    (APTR)L_install_param_int_ex,
    (APTR)L_install_sound,
    (APTR)L_install_timer,
    (APTR)L_is_color_font,
    (APTR)L_is_inside_bitmap,
    (APTR)L_is_linear_bitmap,
    (APTR)L_is_memory_bitmap,
    (APTR)L_is_mono_font,
    (APTR)L_is_planar_bitmap,
    (APTR)L_is_relative_filename,
    (APTR)L_is_same_bitmap,
    (APTR)L_is_screen_bitmap,
    (APTR)L_is_sub_bitmap,
    (APTR)L_is_system_bitmap,
    (APTR)L_is_video_bitmap,
    (APTR)L_keyboard_needs_poll,
    (APTR)L_keypressed,
    (APTR)L_line,
    (APTR)L_load_bitmap,
    (APTR)L_load_bmp,
    (APTR)L_load_bmp_pf,
    (APTR)L_load_datafile,
    (APTR)L_load_datafile_callback,
    (APTR)L_load_datafile_object,
    (APTR)L_load_datafile_object_indexed,
    (APTR)L_load_font,
    (APTR)L_load_joystick_data,
    (APTR)L_load_midi,
    (APTR)L_load_pcx,
    (APTR)L_load_pcx_pf,
    (APTR)L_load_sample,
    (APTR)L_load_tga,
    (APTR)L_load_voc,
    (APTR)L_load_wav,
    (APTR)L_load_wav_pf,
    (APTR)L_lock_bitmap,
    (APTR)L_make_absolute_filename,
    (APTR)L_make_relative_filename,
    (APTR)L_makeacol,
    (APTR)L_makeacol_depth,
    (APTR)L_makecol,
    (APTR)L_makecol8,
    (APTR)L_makecol_depth,
    (APTR)L_masked_blit,
    (APTR)L_masked_stretch_blit,
    (APTR)L_midi_pause,
    (APTR)L_midi_resume,
    (APTR)L_midi_seek,
    (APTR)L_mouse_needs_poll,
    (APTR)L_override_config_file,
    (APTR)L_pack_fclose,
    (APTR)L_pack_fclose_chunk,
    (APTR)L_pack_feof,
    (APTR)L_pack_ferror,
    (APTR)L_pack_fgets,
    (APTR)L_pack_fopen,
    (APTR)L_pack_fopen_chunk,
    (APTR)L_pack_fopen_vtable,
    (APTR)L_pack_fputs,
    (APTR)L_pack_fread,
    (APTR)L_pack_fseek,
    (APTR)L_pack_fwrite,
    (APTR)L_pack_getc,
    (APTR)L_pack_igetl,
    (APTR)L_pack_igetw,
    (APTR)L_pack_iputl,
    (APTR)L_pack_iputw,
    (APTR)L_pack_mgetl,
    (APTR)L_pack_mgetw,
    (APTR)L_pack_mputl,
    (APTR)L_pack_mputw,
    (APTR)L_pack_putc,
    (APTR)L_pack_ungetc,
    (APTR)L_packfile_password,
    (APTR)L_pivot_scaled_sprite,
    (APTR)L_pivot_scaled_sprite_v_flip,
    (APTR)L_pivot_sprite,
    (APTR)L_pivot_sprite_v_flip,
    (APTR)L_play_looped_midi,
    (APTR)L_play_midi,
    (APTR)L_play_sample,
    (APTR)L_poll_joystick,
    (APTR)L_poll_keyboard,
    (APTR)L_poll_mouse,
    (APTR)L_poll_scroll,
    (APTR)L_polygon,
    (APTR)L_position_mouse,
    (APTR)L_position_mouse_z,
    (APTR)L_put_backslash,
    (APTR)L_putpixel,
    (APTR)L_readkey,
    (APTR)L_reallocate_voice,
    (APTR)L_rect,
    (APTR)L_rectfill,
    (APTR)L_register_bitmap_file_type,
    (APTR)L_register_datafile_object,
    (APTR)L_release_bitmap,
    (APTR)L_release_voice,
    (APTR)L_remove_display_switch_callback,
    (APTR)L_remove_int,
    (APTR)L_remove_joystick,
    (APTR)L_remove_keyboard,
    (APTR)L_remove_mouse,
    (APTR)L_remove_param_int,
    (APTR)L_remove_sound,
    (APTR)L_remove_timer,
    (APTR)L_replace_extension,
    (APTR)L_replace_filename,
    (APTR)L_request_refresh_rate,
    (APTR)L_request_scroll,
    (APTR)L_request_video_bitmap,
    (APTR)L_reserve_voices,
    (APTR)L_rest,
    (APTR)L_rest_callback,
    (APTR)L_rotate_scaled_sprite,
    (APTR)L_rotate_scaled_sprite_v_flip,
    (APTR)L_rotate_sprite,
    (APTR)L_rotate_sprite_v_flip,
    (APTR)L_save_bitmap,
    (APTR)L_save_bmp,
    (APTR)L_save_bmp_pf,
    (APTR)L_save_joystick_data,
    (APTR)L_save_pcx,
    (APTR)L_save_pcx_pf,
    (APTR)L_save_sample,
    (APTR)L_scancode_to_ascii,
    (APTR)L_scancode_to_name,
    (APTR)L_scare_mouse,
    (APTR)L_scare_mouse_area,
    (APTR)L_scroll_screen,
    (APTR)L_select_mouse_cursor,
    (APTR)L_select_palette,
    (APTR)L_set_clip_rect,
    (APTR)L_set_clip_state,
    (APTR)L_set_close_button_callback,
    (APTR)L_set_color,
    (APTR)L_set_color_conversion,
    (APTR)L_set_color_depth,
    (APTR)L_set_config_file,
    (APTR)L_set_config_int,
    (APTR)L_set_config_string,
    (APTR)L_set_display_switch_callback,
    (APTR)L_set_display_switch_mode,
    (APTR)L_set_gfx_mode,
    (APTR)L_set_hardware_volume,
    (APTR)L_set_keyboard_rate,
    (APTR)L_set_leds,
    (APTR)L_set_mouse_range,
    (APTR)L_set_mouse_speed,
    (APTR)L_set_mouse_sprite,
    (APTR)L_set_mouse_sprite_focus,
    (APTR)L_set_palette,
    (APTR)L_set_palette_range,
    (APTR)L_set_uformat,
    (APTR)L_set_volume,
    (APTR)L_set_volume_per_voice,
    (APTR)L_set_window_title,
    (APTR)L_show_mouse,
    (APTR)L_show_os_cursor,
    (APTR)L_show_video_bitmap,
    (APTR)L_simulate_keypress,
    (APTR)L_simulate_ukeypress,
    (APTR)L_solid_mode,
    (APTR)L_spline,
    (APTR)L_stop_midi,
    (APTR)L_stop_sample,
    (APTR)L_stretch_blit,
    (APTR)L_stretch_sprite,
    (APTR)L_text_height,
    (APTR)L_text_length,
    (APTR)L_text_mode,
    (APTR)L_textout,
    (APTR)L_textout_centre,
    (APTR)L_textout_centre_ex,
    (APTR)L_textout_ex,
    (APTR)L_textout_justify,
    (APTR)L_textout_justify_ex,
    (APTR)L_textout_right,
    (APTR)L_textout_right_ex,
    (APTR)L_timer_can_simulate_retrace,
    (APTR)L_timer_is_using_retrace,
    (APTR)L_timer_simulate_retrace,
    (APTR)L_triangle,
    (APTR)L_uconvert,
    (APTR)L_uinsert,
    (APTR)L_unload_datafile,
    (APTR)L_unload_datafile_object,
    (APTR)L_unscare_mouse,
    (APTR)L_unselect_palette,
    (APTR)L_ureadkey,
    (APTR)L_uremove,
    (APTR)L_usetat,
    (APTR)L_ustricmp,
    (APTR)L_ustrlwr,
    (APTR)L_ustrnicmp,
    (APTR)L_ustrtok,
    (APTR)L_ustrtok_r,
    (APTR)L_ustrupr,
    (APTR)L_ustrzcat,
    (APTR)L_ustrzcpy,
    (APTR)L_ustrzncpy,
    (APTR)L_vline,
    (APTR)L_voice_check,
    (APTR)L_voice_get_frequency,
    (APTR)L_voice_get_pan,
    (APTR)L_voice_get_position,
    (APTR)L_voice_get_volume,
    (APTR)L_voice_set_frequency,
    (APTR)L_voice_set_pan,
    (APTR)L_voice_set_playmode,
    (APTR)L_voice_set_position,
    (APTR)L_voice_set_priority,
    (APTR)L_voice_set_volume,
    (APTR)L_voice_start,
    (APTR)L_voice_stop,
    (APTR)L_vsync,
    (APTR)L_xor_mode,
    (APTR)L_yield_timeslice,
    (APTR)L_pop_config_state,
    (APTR)L_push_config_state,
    (APTR)L_grab_font_from_bitmap,
    (APTR)L_load_dat_font,
    (APTR)L_midi_out,
    (APTR)L_get_config_hex,
    (APTR)L_get_config_id,
    (APTR)L_override_config_data,
    (APTR)L_set_config_data,
    (APTR)L_set_config_hex,
    (APTR)L_set_config_id,
    (APTR)L_get_config_argv,
    (APTR)L__getpixel15,
    (APTR)L__getpixel16,
    (APTR)L__getpixel24,
    (APTR)L__getpixel32,
    (APTR)L__putpixel15,
    (APTR)L__putpixel16,
    (APTR)L__putpixel24,
    (APTR)L__putpixel32,
    (APTR)L_get_mixer_bits,
    (APTR)L_get_mixer_channels,
    (APTR)L_get_mixer_frequency,
    (APTR)L_get_mixer_quality,
    (APTR)L_get_mixer_voices,
    (APTR)L_geta32,
    (APTR)L_geta_depth,
    (APTR)L_getb15,
    (APTR)L_getb16,
    (APTR)L_getb24,
    (APTR)L_getb32,
    (APTR)L_getg15,
    (APTR)L_getg16,
    (APTR)L_getg24,
    (APTR)L_getg32,
    (APTR)L_getr15,
    (APTR)L_getr16,
    (APTR)L_getr24,
    (APTR)L_getr32,
    (APTR)L_makeacol32,
    (APTR)L_makecol15,
    (APTR)L_makecol16,
    (APTR)L_makecol24,
    (APTR)L_makecol32,
    (APTR)L_set_add_blender,
    (APTR)L_set_alpha_blender,
    (APTR)L_set_burn_blender,
    (APTR)L_set_difference_blender,
    (APTR)L_set_dodge_blender,
    (APTR)L_set_invert_blender,
    (APTR)L_set_mixer_quality,
    (APTR)L_set_multiply_blender,
    (APTR)L_set_screen_blender,
    (APTR)L_set_trans_blender,
    (APTR)L_set_write_alpha_blender,
    (APTR)L_is_windowed_mode,
    (APTR)L_load_bitmap_font,
    (APTR)L_make_trans_font,
    (APTR)-1,
};
