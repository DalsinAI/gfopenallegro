/* Made by tools/gen_lib.py from include/allegro.h: do not edit. */

static void L_a4_flush_screen(REG(a6, struct A4Base *base))
{
    ENTER(base);
    a4_flush_screen();
    LEAVE();
}

static int L_a4_install(REG(a0, struct a4_public * pub), REG(d0, int system_id), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = a4_install(pub, system_id);
    LEAVE();
    return r;
}

static void L_acquire_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    ENTER(base);
    acquire_bitmap(bmp);
    LEAVE();
}

static void L_adjust_sample(REG(a0, const SAMPLE * spl), REG(d0, int vol), REG(d1, int pan), REG(d2, int freq), REG(d3, int loop), REG(a6, struct A4Base *base))
{
    ENTER(base);
    adjust_sample(spl, vol, pan, freq, loop);
    LEAVE();
}

static void L_al_findclose(REG(a0, struct al_ffblk * info), REG(a6, struct A4Base *base))
{
    ENTER(base);
    al_findclose(info);
    LEAVE();
}

static int L_al_findfirst(REG(a0, const char * pattern), REG(a1, struct al_ffblk * info), REG(d0, int attrib), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = al_findfirst(pattern, info, attrib);
    LEAVE();
    return r;
}

static int L_alert(REG(a0, const char * s1), REG(a1, const char * s2), REG(a2, const char * s3), REG(a3, const char * b1), REG(d0, const char * b2), REG(d1, int c1), REG(d2, int c2), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = alert(s1, s2, s3, b1, b2, c1, c2);
    LEAVE();
    return r;
}

static char * L_append_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = append_filename(dest, path, filename, size);
    LEAVE();
    return r;
}

static void L_arc(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, fixed ang1), REG(d3, fixed ang2), REG(d4, int r), REG(d5, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    arc(bmp, x, y, ang1, ang2, r, color);
    LEAVE();
}

static int L_bestfit_color(REG(a0, const RGB * pal), REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = bestfit_color(pal, r, g, b);
    LEAVE();
    return r;
}

static int L_bitmap_color_depth(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = bitmap_color_depth(bmp);
    LEAVE();
    return r;
}

static unsigned long L_bmp_read_line(REG(a0, BITMAP * bmp), REG(d0, int line), REG(a6, struct A4Base *base))
{
    unsigned long r;
    ENTER(base);
    r = bmp_read_line(bmp, line);
    LEAVE();
    return r;
}

static const char * L_calibrate_joystick_name(REG(d0, int n), REG(a6, struct A4Base *base))
{
    const char * r;
    ENTER(base);
    r = calibrate_joystick_name(n);
    LEAVE();
    return r;
}

static char * L_canonicalize_filename(REG(a0, char * dest), REG(a1, const char * filename), REG(d0, int size), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = canonicalize_filename(dest, filename, size);
    LEAVE();
    return r;
}

static void L_circle(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int radius), REG(d3, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    circle(bmp, x, y, radius, color);
    LEAVE();
}

static void L_clear_bitmap(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *base))
{
    ENTER(base);
    clear_bitmap(bitmap);
    LEAVE();
}

static void L_clear_keybuf(REG(a6, struct A4Base *base))
{
    ENTER(base);
    clear_keybuf();
    LEAVE();
}

static BITMAP * L_create_bitmap(REG(d0, int width), REG(d1, int height), REG(a6, struct A4Base *base))
{
    BITMAP * r;
    ENTER(base);
    r = create_bitmap(width, height);
    LEAVE();
    return r;
}

static void L_create_color_table(REG(a0, COLOR_MAP * table), REG(a1, const RGB * pal), REG(a2, void(*blend)(const PALETTE pal, int x, int y, RGB *rgb)), REG(a3, void(*callback)(int pos)), REG(a6, struct A4Base *base))
{
    ENTER(base);
    create_color_table(table, pal, blend, callback);
    LEAVE();
}

static void L_create_light_table(REG(a0, COLOR_MAP * table), REG(a1, const RGB * pal), REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a2, void(*callback)(int pos)), REG(a6, struct A4Base *base))
{
    ENTER(base);
    create_light_table(table, pal, r, g, b, callback);
    LEAVE();
}

static BITMAP * L_create_sub_bitmap(REG(a0, BITMAP * parent), REG(d0, int x), REG(d1, int y), REG(d2, int width), REG(d3, int height), REG(a6, struct A4Base *base))
{
    BITMAP * r;
    ENTER(base);
    r = create_sub_bitmap(parent, x, y, width, height);
    LEAVE();
    return r;
}

static BITMAP * L_create_system_bitmap(REG(d0, int width), REG(d1, int height), REG(a6, struct A4Base *base))
{
    BITMAP * r;
    ENTER(base);
    r = create_system_bitmap(width, height);
    LEAVE();
    return r;
}

static void L_deallocate_voice(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    ENTER(base);
    deallocate_voice(voice);
    LEAVE();
}

static void L_destroy_font(REG(a0, FONT * f), REG(a6, struct A4Base *base))
{
    ENTER(base);
    destroy_font(f);
    LEAVE();
}

static void L_destroy_gfx_mode_list(REG(a0, GFX_MODE_LIST * gfx_mode_list), REG(a6, struct A4Base *base))
{
    ENTER(base);
    destroy_gfx_mode_list(gfx_mode_list);
    LEAVE();
}

static void L_destroy_sample(REG(a0, SAMPLE * spl), REG(a6, struct A4Base *base))
{
    ENTER(base);
    destroy_sample(spl);
    LEAVE();
}

static int L_detect_digi_driver(REG(d0, int driver_id), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = detect_digi_driver(driver_id);
    LEAVE();
    return r;
}

static void L_disable_hardware_cursor(REG(a6, struct A4Base *base))
{
    ENTER(base);
    disable_hardware_cursor();
    LEAVE();
}

static void L_do_ellipse(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int rx), REG(d3, int ry), REG(d4, int d), REG(a1, void(*proc)(BITMAP *, int, int, int)), REG(a6, struct A4Base *base))
{
    ENTER(base);
    do_ellipse(bmp, x, y, rx, ry, d, proc);
    LEAVE();
}

static void L_do_line(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int d), REG(a1, void(*proc)(BITMAP *, int, int, int)), REG(a6, struct A4Base *base))
{
    ENTER(base);
    do_line(bmp, x1, y1, x2, y2, d, proc);
    LEAVE();
}

static void L_draw_lit_rle_sprite(REG(a0, BITMAP * bmp), REG(a1, const RLE_SPRITE * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    draw_lit_rle_sprite(bmp, sprite, x, y, color);
    LEAVE();
}

static void L_draw_lit_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    draw_lit_sprite(bmp, sprite, x, y, color);
    LEAVE();
}

static void L_draw_rle_sprite(REG(a0, BITMAP * bmp), REG(a1, const RLE_SPRITE * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    ENTER(base);
    draw_rle_sprite(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    ENTER(base);
    draw_sprite(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite_v_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    ENTER(base);
    draw_sprite_v_flip(bmp, sprite, x, y);
    LEAVE();
}

static void L_draw_sprite_vh_flip(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    ENTER(base);
    draw_sprite_vh_flip(bmp, sprite, x, y);
    LEAVE();
}

static void L_ellipsefill(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int rx), REG(d3, int ry), REG(d4, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    ellipsefill(bmp, x, y, rx, ry, color);
    LEAVE();
}

static int L_enable_triple_buffer(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = enable_triple_buffer();
    LEAVE();
    return r;
}

static void L_fade_from(REG(a0, const RGB * source), REG(a1, const RGB * dest), REG(d0, int speed), REG(a6, struct A4Base *base))
{
    ENTER(base);
    fade_from(source, dest, speed);
    LEAVE();
}

static void L_fade_in_range(REG(a0, const RGB * p), REG(d0, int speed), REG(d1, int from), REG(d2, int to), REG(a6, struct A4Base *base))
{
    ENTER(base);
    fade_in_range(p, speed, from, to);
    LEAVE();
}

static void L_fade_interpolate(REG(a0, const RGB * source), REG(a1, const RGB * dest), REG(a2, RGB * output), REG(d0, int pos), REG(d1, int from), REG(d2, int to), REG(a6, struct A4Base *base))
{
    ENTER(base);
    fade_interpolate(source, dest, output, pos, from, to);
    LEAVE();
}

static void L_fade_out(REG(d0, int speed), REG(a6, struct A4Base *base))
{
    ENTER(base);
    fade_out(speed);
    LEAVE();
}

static void L_fastline(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    fastline(bmp, x1, y1, x2, y2, color);
    LEAVE();
}

static int L_file_exists(REG(a0, const char * filename), REG(d0, int attrib), REG(a1, int * aret), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = file_exists(filename, attrib, aret);
    LEAVE();
    return r;
}

static long L_file_size(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    long r;
    ENTER(base);
    r = file_size(filename);
    LEAVE();
    return r;
}

static time_t L_file_time(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    time_t r;
    ENTER(base);
    r = file_time(filename);
    LEAVE();
    return r;
}

static int L_find_allegro_resource(REG(a0, char * dest), REG(a1, const char * resource), REG(a2, const char * ext), REG(a3, const char * datafile), REG(d0, const char * objectname), REG(d1, const char * envvar), REG(d2, const char * subdir), REG(d3, int size), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = find_allegro_resource(dest, resource, ext, datafile, objectname, envvar, subdir, size);
    LEAVE();
    return r;
}

static char * L_fix_filename_slashes(REG(a0, char * path), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = fix_filename_slashes(path);
    LEAVE();
    return r;
}

static fixed L_fixatan2(REG(d0, fixed y), REG(d1, fixed x), REG(a6, struct A4Base *base))
{
    fixed r;
    ENTER(base);
    r = fixatan2(y, x);
    LEAVE();
    return r;
}

static fixed L_fixhypot(REG(d0, fixed x), REG(d1, fixed y), REG(a6, struct A4Base *base))
{
    fixed r;
    ENTER(base);
    r = fixhypot(x, y);
    LEAVE();
    return r;
}

static fixed L_fixsin(REG(d0, fixed x), REG(a6, struct A4Base *base))
{
    fixed r;
    ENTER(base);
    r = fixsin(x);
    LEAVE();
    return r;
}

static fixed L_fixtan(REG(d0, fixed x), REG(a6, struct A4Base *base))
{
    fixed r;
    ENTER(base);
    r = fixtan(x);
    LEAVE();
    return r;
}

static void L_fixup_datafile(REG(a0, DATAFILE * data), REG(a6, struct A4Base *base))
{
    ENTER(base);
    fixup_datafile(data);
    LEAVE();
}

static int L_generate_optimized_palette(REG(a0, struct BITMAP * image), REG(a1, RGB * pal), REG(a2, const signed char * rsvdcols), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = generate_optimized_palette(image, pal, rsvdcols);
    LEAVE();
    return r;
}

static void L_get_clip_rect(REG(a0, BITMAP * bitmap), REG(a1, int * x1), REG(a2, int * y1), REG(a3, int * x2), REG(d0, int * y2), REG(a6, struct A4Base *base))
{
    ENTER(base);
    get_clip_rect(bitmap, x1, y1, x2, y2);
    LEAVE();
}

static int L_get_clip_state(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_clip_state(bitmap);
    LEAVE();
    return r;
}

static int L_get_config_int(REG(a0, const char * section), REG(a1, const char * name), REG(d0, int def), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_config_int(section, name, def);
    LEAVE();
    return r;
}

static const char * L_get_datafile_property(REG(a0, const DATAFILE * dat), REG(d0, int type), REG(a6, struct A4Base *base))
{
    const char * r;
    ENTER(base);
    r = get_datafile_property(dat, type);
    LEAVE();
    return r;
}

static int L_get_desktop_resolution(REG(a0, int * width), REG(a1, int * height), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_desktop_resolution(width, height);
    LEAVE();
    return r;
}

static int L_get_display_switch_mode(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_display_switch_mode();
    LEAVE();
    return r;
}

static char * L_get_filename(REG(a0, const char * path), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = get_filename(path);
    LEAVE();
    return r;
}

static int L_get_font_range_end(REG(a0, FONT * f), REG(d0, int range), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_font_range_end(f, range);
    LEAVE();
    return r;
}

static int L_get_font_ranges(REG(a0, FONT * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_font_ranges(f);
    LEAVE();
    return r;
}

static int L_get_gfx_mode_type(REG(d0, int graphics_card), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_gfx_mode_type(graphics_card);
    LEAVE();
    return r;
}

static int L_get_midi_length(REG(a0, MIDI * midi), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_midi_length(midi);
    LEAVE();
    return r;
}

static void L_get_mouse_mickeys(REG(a0, int * mickeyx), REG(a1, int * mickeyy), REG(a6, struct A4Base *base))
{
    ENTER(base);
    get_mouse_mickeys(mickeyx, mickeyy);
    LEAVE();
}

static void L_get_palette(REG(a0, RGB * p), REG(a6, struct A4Base *base))
{
    ENTER(base);
    get_palette(p);
    LEAVE();
}

static int L_get_refresh_rate(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = get_refresh_rate();
    LEAVE();
    return r;
}

static RLE_SPRITE * L_get_rle_sprite(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *base))
{
    RLE_SPRITE * r;
    ENTER(base);
    r = get_rle_sprite(bitmap);
    LEAVE();
    return r;
}

static int L_getb(REG(d0, int c), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = getb(c);
    LEAVE();
    return r;
}

static int L_getb8(REG(d0, int c), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = getb8(c);
    LEAVE();
    return r;
}

static int L_getg_depth(REG(d0, int color_depth), REG(d1, int c), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = getg_depth(color_depth, c);
    LEAVE();
    return r;
}

static int L_getpixel(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = getpixel(bmp, x, y);
    LEAVE();
    return r;
}

static int L_getr(REG(d0, int c), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = getr(c);
    LEAVE();
    return r;
}

static int L_getr8(REG(d0, int c), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = getr8(c);
    LEAVE();
    return r;
}

static int L_install_int(REG(a0, void(*proc)(void)), REG(d0, long speed), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = install_int(proc, speed);
    LEAVE();
    return r;
}

static int L_install_joystick(REG(d0, int type), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = install_joystick(type);
    LEAVE();
    return r;
}

static int L_install_param_int_ex(REG(a0, void(*proc)(void *param)), REG(a1, void * param), REG(d0, long speed), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = install_param_int_ex(proc, param, speed);
    LEAVE();
    return r;
}

static int L_install_sound(REG(d0, int digi), REG(d1, int midi), REG(a0, const char * cfg_path), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = install_sound(digi, midi, cfg_path);
    LEAVE();
    return r;
}

static int L_is_color_font(REG(a0, FONT * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = is_color_font(f);
    LEAVE();
    return r;
}

static int L_is_planar_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = is_planar_bitmap(bmp);
    LEAVE();
    return r;
}

static int L_is_same_bitmap(REG(a0, BITMAP * bmp1), REG(a1, BITMAP * bmp2), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = is_same_bitmap(bmp1, bmp2);
    LEAVE();
    return r;
}

static int L_is_screen_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = is_screen_bitmap(bmp);
    LEAVE();
    return r;
}

static int L_is_system_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = is_system_bitmap(bmp);
    LEAVE();
    return r;
}

static int L_keyboard_needs_poll(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = keyboard_needs_poll();
    LEAVE();
    return r;
}

static BITMAP * L_load_bitmap(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a6, struct A4Base *base))
{
    BITMAP * r;
    ENTER(base);
    r = load_bitmap(filename, pal);
    LEAVE();
    return r;
}

static BITMAP * L_load_bmp_pf(REG(a0, PACKFILE * f), REG(a1, RGB * pal), REG(a6, struct A4Base *base))
{
    BITMAP * r;
    ENTER(base);
    r = load_bmp_pf(f, pal);
    LEAVE();
    return r;
}

static DATAFILE * L_load_datafile(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    DATAFILE * r;
    ENTER(base);
    r = load_datafile(filename);
    LEAVE();
    return r;
}

static DATAFILE * L_load_datafile_object_indexed(REG(a0, const DATAFILE_INDEX * index), REG(d0, int item), REG(a6, struct A4Base *base))
{
    DATAFILE * r;
    ENTER(base);
    r = load_datafile_object_indexed(index, item);
    LEAVE();
    return r;
}

static FONT * L_load_font(REG(a0, const char * filename), REG(a1, RGB * pal), REG(a2, void * param), REG(a6, struct A4Base *base))
{
    FONT * r;
    ENTER(base);
    r = load_font(filename, pal, param);
    LEAVE();
    return r;
}

static int L_load_joystick_data(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = load_joystick_data(filename);
    LEAVE();
    return r;
}

static MIDI * L_load_midi(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    MIDI * r;
    ENTER(base);
    r = load_midi(filename);
    LEAVE();
    return r;
}

static BITMAP * L_load_pcx_pf(REG(a0, PACKFILE * f), REG(a1, RGB * pal), REG(a6, struct A4Base *base))
{
    BITMAP * r;
    ENTER(base);
    r = load_pcx_pf(f, pal);
    LEAVE();
    return r;
}

static SAMPLE * L_load_voc(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    SAMPLE * r;
    ENTER(base);
    r = load_voc(filename);
    LEAVE();
    return r;
}

static SAMPLE * L_load_wav(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    SAMPLE * r;
    ENTER(base);
    r = load_wav(filename);
    LEAVE();
    return r;
}

static void L_lock_bitmap(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    ENTER(base);
    lock_bitmap(bmp);
    LEAVE();
}

static char * L_make_relative_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = make_relative_filename(dest, path, filename, size);
    LEAVE();
    return r;
}

static int L_makeacol(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(d3, int a), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = makeacol(r, g, b, a);
    LEAVE();
    return r;
}

static int L_makecol8(REG(d0, int r), REG(d1, int g), REG(d2, int b), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = makecol8(r, g, b);
    LEAVE();
    return r;
}

static void L_masked_blit(REG(a0, BITMAP * source), REG(a1, BITMAP * dest), REG(d0, int source_x), REG(d1, int source_y), REG(d2, int dest_x), REG(d3, int dest_y), REG(d4, int width), REG(d5, int height), REG(a6, struct A4Base *base))
{
    ENTER(base);
    masked_blit(source, dest, source_x, source_y, dest_x, dest_y, width, height);
    LEAVE();
}

static void L_masked_stretch_blit(REG(a0, BITMAP * source), REG(a1, BITMAP * dest), REG(d0, int source_x), REG(d1, int source_y), REG(d2, int source_w), REG(d3, int source_h), REG(d4, int dest_x), REG(d5, int dest_y), REG(d6, int dest_w), REG(d7, int dest_h), REG(a6, struct A4Base *base))
{
    ENTER(base);
    masked_stretch_blit(source, dest, source_x, source_y, source_w, source_h, dest_x, dest_y, dest_w, dest_h);
    LEAVE();
}

static void L_midi_resume(REG(a6, struct A4Base *base))
{
    ENTER(base);
    midi_resume();
    LEAVE();
}

static int L_mouse_needs_poll(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = mouse_needs_poll();
    LEAVE();
    return r;
}

static void L_override_config_file(REG(a0, const char * filename), REG(a6, struct A4Base *base))
{
    ENTER(base);
    override_config_file(filename);
    LEAVE();
}

static int L_pack_fclose(REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = pack_fclose(f);
    LEAVE();
    return r;
}

static int L_pack_feof(REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = pack_feof(f);
    LEAVE();
    return r;
}

static PACKFILE * L_pack_fopen(REG(a0, const char * filename), REG(a1, const char * mode), REG(a6, struct A4Base *base))
{
    PACKFILE * r;
    ENTER(base);
    r = pack_fopen(filename, mode);
    LEAVE();
    return r;
}

static PACKFILE * L_pack_fopen_chunk(REG(a0, PACKFILE * f), REG(d0, int pack), REG(a6, struct A4Base *base))
{
    PACKFILE * r;
    ENTER(base);
    r = pack_fopen_chunk(f, pack);
    LEAVE();
    return r;
}

static int L_pack_fputs(REG(a0, const char * p), REG(a1, PACKFILE * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = pack_fputs(p, f);
    LEAVE();
    return r;
}

static long L_pack_fwrite(REG(a0, const void * p), REG(d0, long n), REG(a1, PACKFILE * f), REG(a6, struct A4Base *base))
{
    long r;
    ENTER(base);
    r = pack_fwrite(p, n, f);
    LEAVE();
    return r;
}

static int L_pack_getc(REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = pack_getc(f);
    LEAVE();
    return r;
}

static long L_pack_igetl(REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    long r;
    ENTER(base);
    r = pack_igetl(f);
    LEAVE();
    return r;
}

static long L_pack_iputl(REG(d0, long l), REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    long r;
    ENTER(base);
    r = pack_iputl(l, f);
    LEAVE();
    return r;
}

static long L_pack_mgetl(REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    long r;
    ENTER(base);
    r = pack_mgetl(f);
    LEAVE();
    return r;
}

static long L_pack_mputl(REG(d0, long l), REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    long r;
    ENTER(base);
    r = pack_mputl(l, f);
    LEAVE();
    return r;
}

static int L_pack_ungetc(REG(d0, int c), REG(a0, PACKFILE * f), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = pack_ungetc(c, f);
    LEAVE();
    return r;
}

static void L_pivot_scaled_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int cx), REG(d3, int cy), REG(d4, fixed angle), REG(d5, fixed scale), REG(a6, struct A4Base *base))
{
    ENTER(base);
    pivot_scaled_sprite(bmp, sprite, x, y, cx, cy, angle, scale);
    LEAVE();
}

static void L_pivot_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, int cx), REG(d3, int cy), REG(d4, fixed angle), REG(a6, struct A4Base *base))
{
    ENTER(base);
    pivot_sprite(bmp, sprite, x, y, cx, cy, angle);
    LEAVE();
}

static int L_play_midi(REG(a0, MIDI * midi), REG(d0, int loop), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = play_midi(midi, loop);
    LEAVE();
    return r;
}

static int L_play_sample(REG(a0, const SAMPLE * spl), REG(d0, int vol), REG(d1, int pan), REG(d2, int freq), REG(d3, int loop), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = play_sample(spl, vol, pan, freq, loop);
    LEAVE();
    return r;
}

static int L_poll_joystick(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = poll_joystick();
    LEAVE();
    return r;
}

static void L_polygon(REG(a0, BITMAP * bmp), REG(d0, int vertices), REG(a1, const int * points), REG(d1, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    polygon(bmp, vertices, points, color);
    LEAVE();
}

static void L_position_mouse(REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    ENTER(base);
    position_mouse(x, y);
    LEAVE();
}

static void L_put_backslash(REG(a0, char * filename), REG(a6, struct A4Base *base))
{
    ENTER(base);
    put_backslash(filename);
    LEAVE();
}

static void L_putpixel(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    putpixel(bmp, x, y, color);
    LEAVE();
}

static int L_readkey(REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = readkey();
    LEAVE();
    return r;
}

static void L_rectfill(REG(a0, BITMAP * bmp), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(d4, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    rectfill(bmp, x1, y1, x2, y2, color);
    LEAVE();
}

static void L_release_voice(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    ENTER(base);
    release_voice(voice);
    LEAVE();
}

static void L_remove_keyboard(REG(a6, struct A4Base *base))
{
    ENTER(base);
    remove_keyboard();
    LEAVE();
}

static void L_remove_mouse(REG(a6, struct A4Base *base))
{
    ENTER(base);
    remove_mouse();
    LEAVE();
}

static void L_remove_param_int(REG(a0, void(*proc)(void *param)), REG(a1, void * param), REG(a6, struct A4Base *base))
{
    ENTER(base);
    remove_param_int(proc, param);
    LEAVE();
}

static void L_remove_timer(REG(a6, struct A4Base *base))
{
    ENTER(base);
    remove_timer();
    LEAVE();
}

static char * L_replace_filename(REG(a0, char * dest), REG(a1, const char * path), REG(a2, const char * filename), REG(d0, int size), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = replace_filename(dest, path, filename, size);
    LEAVE();
    return r;
}

static int L_request_scroll(REG(d0, int x), REG(d1, int y), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = request_scroll(x, y);
    LEAVE();
    return r;
}

static int L_request_video_bitmap(REG(a0, BITMAP * bitmap), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = request_video_bitmap(bitmap);
    LEAVE();
    return r;
}

static void L_reserve_voices(REG(d0, int digi_voices), REG(d1, int midi_voices), REG(a6, struct A4Base *base))
{
    ENTER(base);
    reserve_voices(digi_voices, midi_voices);
    LEAVE();
}

static void L_rest_callback(REG(d0, unsigned int time), REG(a0, void(*callback)(void)), REG(a6, struct A4Base *base))
{
    ENTER(base);
    rest_callback(time, callback);
    LEAVE();
}

static void L_rotate_scaled_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, fixed angle), REG(d3, fixed scale), REG(a6, struct A4Base *base))
{
    ENTER(base);
    rotate_scaled_sprite(bmp, sprite, x, y, angle, scale);
    LEAVE();
}

static void L_rotate_sprite(REG(a0, BITMAP * bmp), REG(a1, BITMAP * sprite), REG(d0, int x), REG(d1, int y), REG(d2, fixed angle), REG(a6, struct A4Base *base))
{
    ENTER(base);
    rotate_sprite(bmp, sprite, x, y, angle);
    LEAVE();
}

static int L_save_bitmap(REG(a0, const char * filename), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = save_bitmap(filename, bmp, pal);
    LEAVE();
    return r;
}

static int L_save_bmp_pf(REG(a0, PACKFILE * f), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = save_bmp_pf(f, bmp, pal);
    LEAVE();
    return r;
}

static int L_save_pcx_pf(REG(a0, PACKFILE * f), REG(a1, BITMAP * bmp), REG(a2, const RGB * pal), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = save_pcx_pf(f, bmp, pal);
    LEAVE();
    return r;
}

static const char * L_scancode_to_name(REG(d0, int scancode), REG(a6, struct A4Base *base))
{
    const char * r;
    ENTER(base);
    r = scancode_to_name(scancode);
    LEAVE();
    return r;
}

static void L_scare_mouse_area(REG(d0, int x), REG(d1, int y), REG(d2, int w), REG(d3, int h), REG(a6, struct A4Base *base))
{
    ENTER(base);
    scare_mouse_area(x, y, w, h);
    LEAVE();
}

static void L_set_clip_rect(REG(a0, BITMAP * bitmap), REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_clip_rect(bitmap, x1, y1, x2, y2);
    LEAVE();
}

static int L_set_close_button_callback(REG(a0, void(*proc)(void)), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = set_close_button_callback(proc);
    LEAVE();
    return r;
}

static void L_set_color(REG(d0, int idx), REG(a0, const RGB * p), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_color(idx, p);
    LEAVE();
}

static void L_set_color_conversion(REG(d0, int mode), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_color_conversion(mode);
    LEAVE();
}

static void L_set_color_depth(REG(d0, int depth), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_color_depth(depth);
    LEAVE();
}

static void L_set_config_string(REG(a0, const char * section), REG(a1, const char * name), REG(a2, const char * val), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_config_string(section, name, val);
    LEAVE();
}

static int L_set_display_switch_callback(REG(d0, int dir), REG(a0, void(*cb)(void)), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = set_display_switch_callback(dir, cb);
    LEAVE();
    return r;
}

static int L_set_gfx_mode(REG(d0, int card), REG(d1, int w), REG(d2, int h), REG(d3, int v_w), REG(d4, int v_h), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = set_gfx_mode(card, w, h, v_w, v_h);
    LEAVE();
    return r;
}

static void L_set_hardware_volume(REG(d0, int digi_volume), REG(d1, int midi_volume), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_hardware_volume(digi_volume, midi_volume);
    LEAVE();
}

static void L_set_keyboard_rate(REG(d0, int delay), REG(d1, int repeat), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_keyboard_rate(delay, repeat);
    LEAVE();
}

static void L_set_mouse_range(REG(d0, int x1), REG(d1, int y1), REG(d2, int x2), REG(d3, int y2), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_mouse_range(x1, y1, x2, y2);
    LEAVE();
}

static void L_set_mouse_sprite(REG(a0, BITMAP * sprite), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_mouse_sprite(sprite);
    LEAVE();
}

static void L_set_palette_range(REG(a0, const RGB * p), REG(d0, int from), REG(d1, int to), REG(d2, int retracesync), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_palette_range(p, from, to, retracesync);
    LEAVE();
}

static void L_set_uformat(REG(d0, int type), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_uformat(type);
    LEAVE();
}

static void L_set_volume(REG(d0, int digi_volume), REG(d1, int midi_volume), REG(a6, struct A4Base *base))
{
    ENTER(base);
    set_volume(digi_volume, midi_volume);
    LEAVE();
}

static void L_show_mouse(REG(a0, BITMAP * bmp), REG(a6, struct A4Base *base))
{
    ENTER(base);
    show_mouse(bmp);
    LEAVE();
}

static void L_simulate_keypress(REG(d0, int keycode), REG(a6, struct A4Base *base))
{
    ENTER(base);
    simulate_keypress(keycode);
    LEAVE();
}

static void L_spline(REG(a0, BITMAP * bmp), REG(a1, const int * points), REG(d0, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    spline(bmp, points, color);
    LEAVE();
}

static void L_stop_midi(REG(a6, struct A4Base *base))
{
    ENTER(base);
    stop_midi();
    LEAVE();
}

static int L_text_length(REG(a0, const FONT * f), REG(a1, const char * str), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = text_length(f, str);
    LEAVE();
    return r;
}

static void L_textout(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    textout(bmp, f, s, x, y, color);
    LEAVE();
}

static void L_textout_ex(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(d3, int bg), REG(a6, struct A4Base *base))
{
    ENTER(base);
    textout_ex(bmp, f, s, x, y, color, bg);
    LEAVE();
}

static void L_textout_right(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    textout_right(bmp, f, s, x, y, color);
    LEAVE();
}

static void L_textout_right_ex(REG(a0, BITMAP * bmp), REG(a1, const FONT * f), REG(a2, const char * s), REG(d0, int x), REG(d1, int y), REG(d2, int color), REG(d3, int bg), REG(a6, struct A4Base *base))
{
    ENTER(base);
    textout_right_ex(bmp, f, s, x, y, color, bg);
    LEAVE();
}

static void L_timer_simulate_retrace(REG(d0, int enable), REG(a6, struct A4Base *base))
{
    ENTER(base);
    timer_simulate_retrace(enable);
    LEAVE();
}

static const char * L_uconvert(REG(a0, const char * s), REG(d0, int type), REG(a1, char * buf), REG(d1, int newtype), REG(d2, int size), REG(a6, struct A4Base *base))
{
    const char * r;
    ENTER(base);
    r = uconvert(s, type, buf, newtype, size);
    LEAVE();
    return r;
}

static int L_uinsert(REG(a0, char * s), REG(d0, int index), REG(d1, int c), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = uinsert(s, index, c);
    LEAVE();
    return r;
}

static void L_unload_datafile(REG(a0, DATAFILE * dat), REG(a6, struct A4Base *base))
{
    ENTER(base);
    unload_datafile(dat);
    LEAVE();
}

static void L_unload_datafile_object(REG(a0, DATAFILE * dat), REG(a6, struct A4Base *base))
{
    ENTER(base);
    unload_datafile_object(dat);
    LEAVE();
}

static void L_unselect_palette(REG(a6, struct A4Base *base))
{
    ENTER(base);
    unselect_palette();
    LEAVE();
}

static int L_ustrnicmp(REG(a0, const char * s1), REG(a1, const char * s2), REG(d0, int n), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = ustrnicmp(s1, s2, n);
    LEAVE();
    return r;
}

static char * L_ustrtok_r(REG(a0, char * s), REG(a1, const char * set), REG(a2, char ** last), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = ustrtok_r(s, set, last);
    LEAVE();
    return r;
}

static char * L_ustrupr(REG(a0, char * s), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = ustrupr(s);
    LEAVE();
    return r;
}

static char * L_ustrzcpy(REG(a0, char * dest), REG(d0, int size), REG(a1, const char * src), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = ustrzcpy(dest, size, src);
    LEAVE();
    return r;
}

static char * L_ustrzncpy(REG(a0, char * dest), REG(d0, int size), REG(a1, const char * src), REG(d1, int n), REG(a6, struct A4Base *base))
{
    char * r;
    ENTER(base);
    r = ustrzncpy(dest, size, src, n);
    LEAVE();
    return r;
}

static void L_vline(REG(a0, BITMAP * bmp), REG(d0, int x), REG(d1, int y1), REG(d2, int y2), REG(d3, int color), REG(a6, struct A4Base *base))
{
    ENTER(base);
    vline(bmp, x, y1, y2, color);
    LEAVE();
}

static SAMPLE * L_voice_check(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    SAMPLE * r;
    ENTER(base);
    r = voice_check(voice);
    LEAVE();
    return r;
}

static int L_voice_get_frequency(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = voice_get_frequency(voice);
    LEAVE();
    return r;
}

static int L_voice_get_pan(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = voice_get_pan(voice);
    LEAVE();
    return r;
}

static int L_voice_get_position(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = voice_get_position(voice);
    LEAVE();
    return r;
}

static int L_voice_get_volume(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    int r;
    ENTER(base);
    r = voice_get_volume(voice);
    LEAVE();
    return r;
}

static void L_voice_stop(REG(d0, int voice), REG(a6, struct A4Base *base))
{
    ENTER(base);
    voice_stop(voice);
    LEAVE();
}

static void L_xor_mode(REG(d0, int on), REG(a6, struct A4Base *base))
{
    ENTER(base);
    xor_mode(on);
    LEAVE();
}

static void L_yield_timeslice(REG(a6, struct A4Base *base))
{
    ENTER(base);
    yield_timeslice();
    LEAVE();
}

static const APTR a4_vectors[] = {
    (APTR)lib_open, (APTR)lib_close, (APTR)lib_expunge, (APTR)lib_null,
    (APTR)L_a4_flush_screen,
    (APTR)L_a4_install,
    (APTR)L_acquire_bitmap,
    (APTR)L_adjust_sample,
    (APTR)L_al_findclose,
    (APTR)L_al_findfirst,
    (APTR)L_alert,
    (APTR)L_append_filename,
    (APTR)L_arc,
    (APTR)L_bestfit_color,
    (APTR)L_bitmap_color_depth,
    (APTR)L_bmp_read_line,
    (APTR)L_calibrate_joystick_name,
    (APTR)L_canonicalize_filename,
    (APTR)L_circle,
    (APTR)L_clear_bitmap,
    (APTR)L_clear_keybuf,
    (APTR)L_create_bitmap,
    (APTR)L_create_color_table,
    (APTR)L_create_light_table,
    (APTR)L_create_sub_bitmap,
    (APTR)L_create_system_bitmap,
    (APTR)L_deallocate_voice,
    (APTR)L_destroy_font,
    (APTR)L_destroy_gfx_mode_list,
    (APTR)L_destroy_sample,
    (APTR)L_detect_digi_driver,
    (APTR)L_disable_hardware_cursor,
    (APTR)L_do_ellipse,
    (APTR)L_do_line,
    (APTR)L_draw_lit_rle_sprite,
    (APTR)L_draw_lit_sprite,
    (APTR)L_draw_rle_sprite,
    (APTR)L_draw_sprite,
    (APTR)L_draw_sprite_v_flip,
    (APTR)L_draw_sprite_vh_flip,
    (APTR)L_ellipsefill,
    (APTR)L_enable_triple_buffer,
    (APTR)L_fade_from,
    (APTR)L_fade_in_range,
    (APTR)L_fade_interpolate,
    (APTR)L_fade_out,
    (APTR)L_fastline,
    (APTR)L_file_exists,
    (APTR)L_file_size,
    (APTR)L_file_time,
    (APTR)L_find_allegro_resource,
    (APTR)L_fix_filename_slashes,
    (APTR)L_fixatan2,
    (APTR)L_fixhypot,
    (APTR)L_fixsin,
    (APTR)L_fixtan,
    (APTR)L_fixup_datafile,
    (APTR)L_generate_optimized_palette,
    (APTR)L_get_clip_rect,
    (APTR)L_get_clip_state,
    (APTR)L_get_config_int,
    (APTR)L_get_datafile_property,
    (APTR)L_get_desktop_resolution,
    (APTR)L_get_display_switch_mode,
    (APTR)L_get_filename,
    (APTR)L_get_font_range_end,
    (APTR)L_get_font_ranges,
    (APTR)L_get_gfx_mode_type,
    (APTR)L_get_midi_length,
    (APTR)L_get_mouse_mickeys,
    (APTR)L_get_palette,
    (APTR)L_get_refresh_rate,
    (APTR)L_get_rle_sprite,
    (APTR)L_getb,
    (APTR)L_getb8,
    (APTR)L_getg_depth,
    (APTR)L_getpixel,
    (APTR)L_getr,
    (APTR)L_getr8,
    (APTR)L_install_int,
    (APTR)L_install_joystick,
    (APTR)L_install_param_int_ex,
    (APTR)L_install_sound,
    (APTR)L_is_color_font,
    (APTR)L_is_planar_bitmap,
    (APTR)L_is_same_bitmap,
    (APTR)L_is_screen_bitmap,
    (APTR)L_is_system_bitmap,
    (APTR)L_keyboard_needs_poll,
    (APTR)L_load_bitmap,
    (APTR)L_load_bmp_pf,
    (APTR)L_load_datafile,
    (APTR)L_load_datafile_object_indexed,
    (APTR)L_load_font,
    (APTR)L_load_joystick_data,
    (APTR)L_load_midi,
    (APTR)L_load_pcx_pf,
    (APTR)L_load_voc,
    (APTR)L_load_wav,
    (APTR)L_lock_bitmap,
    (APTR)L_make_relative_filename,
    (APTR)L_makeacol,
    (APTR)L_makecol8,
    (APTR)L_masked_blit,
    (APTR)L_masked_stretch_blit,
    (APTR)L_midi_resume,
    (APTR)L_mouse_needs_poll,
    (APTR)L_override_config_file,
    (APTR)L_pack_fclose,
    (APTR)L_pack_feof,
    (APTR)L_pack_fopen,
    (APTR)L_pack_fopen_chunk,
    (APTR)L_pack_fputs,
    (APTR)L_pack_fwrite,
    (APTR)L_pack_getc,
    (APTR)L_pack_igetl,
    (APTR)L_pack_iputl,
    (APTR)L_pack_mgetl,
    (APTR)L_pack_mputl,
    (APTR)L_pack_ungetc,
    (APTR)L_pivot_scaled_sprite,
    (APTR)L_pivot_sprite,
    (APTR)L_play_midi,
    (APTR)L_play_sample,
    (APTR)L_poll_joystick,
    (APTR)L_polygon,
    (APTR)L_position_mouse,
    (APTR)L_put_backslash,
    (APTR)L_putpixel,
    (APTR)L_readkey,
    (APTR)L_rectfill,
    (APTR)L_release_voice,
    (APTR)L_remove_keyboard,
    (APTR)L_remove_mouse,
    (APTR)L_remove_param_int,
    (APTR)L_remove_timer,
    (APTR)L_replace_filename,
    (APTR)L_request_scroll,
    (APTR)L_request_video_bitmap,
    (APTR)L_reserve_voices,
    (APTR)L_rest_callback,
    (APTR)L_rotate_scaled_sprite,
    (APTR)L_rotate_sprite,
    (APTR)L_save_bitmap,
    (APTR)L_save_bmp_pf,
    (APTR)L_save_pcx_pf,
    (APTR)L_scancode_to_name,
    (APTR)L_scare_mouse_area,
    (APTR)L_set_clip_rect,
    (APTR)L_set_close_button_callback,
    (APTR)L_set_color,
    (APTR)L_set_color_conversion,
    (APTR)L_set_color_depth,
    (APTR)L_set_config_string,
    (APTR)L_set_display_switch_callback,
    (APTR)L_set_gfx_mode,
    (APTR)L_set_hardware_volume,
    (APTR)L_set_keyboard_rate,
    (APTR)L_set_mouse_range,
    (APTR)L_set_mouse_sprite,
    (APTR)L_set_palette_range,
    (APTR)L_set_uformat,
    (APTR)L_set_volume,
    (APTR)L_show_mouse,
    (APTR)L_simulate_keypress,
    (APTR)L_spline,
    (APTR)L_stop_midi,
    (APTR)L_text_length,
    (APTR)L_textout,
    (APTR)L_textout_ex,
    (APTR)L_textout_right,
    (APTR)L_textout_right_ex,
    (APTR)L_timer_simulate_retrace,
    (APTR)L_uconvert,
    (APTR)L_uinsert,
    (APTR)L_unload_datafile,
    (APTR)L_unload_datafile_object,
    (APTR)L_unselect_palette,
    (APTR)L_ustrnicmp,
    (APTR)L_ustrtok_r,
    (APTR)L_ustrupr,
    (APTR)L_ustrzcpy,
    (APTR)L_ustrzncpy,
    (APTR)L_vline,
    (APTR)L_voice_check,
    (APTR)L_voice_get_frequency,
    (APTR)L_voice_get_pan,
    (APTR)L_voice_get_position,
    (APTR)L_voice_get_volume,
    (APTR)L_voice_stop,
    (APTR)L_xor_mode,
    (APTR)L_yield_timeslice,
    (APTR)-1,
};
