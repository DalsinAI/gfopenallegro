/* Exercise Allegro's held bitmap drawing with OpenGPU-shaped batch sizes.
 *
 * Left/Right: batch size, A: automatic cycling, F10: fullscreen, Escape: quit.
 */
#include <stdio.h>
#include "allegro5/allegro.h"

static const int batch_quads[] = { 1, 2, 16, 64, 256, 1024 };

static ALLEGRO_COLOR colour_for(int i)
{
   static const unsigned char rgb[][3] = {
      { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 },
      { 255, 255, 0 }, { 0, 255, 255 }, { 255, 0, 255 }
   };
   const unsigned char *c = rgb[i % 6];
   return al_map_rgb(c[0], c[1], c[2]);
}

static void update_title(ALLEGRO_DISPLAY *display, int selected, bool automatic)
{
   char title[160];
   int quads = batch_quads[selected];
   snprintf(title, sizeof title,
      "Amiga Allegro batch: %d quads / %d vertices%s | Left Right | A | F10 | Esc",
      quads, quads * 6, automatic ? " | AUTO" : "");
   al_set_window_title(display, title);
}

static void draw_batch(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *tile,
   int selected)
{
   const int quads = batch_quads[selected];
   const int columns = 32;
   const int width = al_get_display_width(display);
   const int height = al_get_display_height(display);
   const float cell_x = (width - 16) / 32.0f;
   const float cell_y = (height - 24) / 32.0f;
   const float cell = cell_x < cell_y ? cell_x : cell_y;
   const float size = cell > 2.0f ? cell - 1.0f : cell;
   int i;

   al_set_target_backbuffer(display);
   al_clear_to_color(al_map_rgb(8, 12, 24));

   /* Every draw uses the same texture, so all vertices belong to one held
    * batch. Allegro's OpenGL backend streams nine floats (36 bytes) per
    * vertex and emits six vertices per bitmap. */
   al_hold_bitmap_drawing(true);
   for (i = 0; i < quads; i++) {
      const int x = i % columns;
      const int y = i / columns;
      al_draw_tinted_scaled_bitmap(tile, colour_for(i),
         0, 0, 8, 8, 8.0f + x * cell, 16.0f + y * cell,
         size, size, 0);
   }
   al_hold_bitmap_drawing(false);
   al_flip_display();
}

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display;
   ALLEGRO_BITMAP *tile;
   ALLEGRO_EVENT_QUEUE *queue;
   ALLEGRO_TIMER *timer;
   bool running = true;
   bool redraw = true;
   bool automatic = false;
   int selected = 3;
   int ticks = 0;

   (void)argc;
   (void)argv;

   if (!al_init() || !al_install_keyboard()) {
      fprintf(stderr, "Could not initialise Allegro and the keyboard.\n");
      return 1;
   }

   al_set_new_display_flags(ALLEGRO_RESIZABLE);
   display = al_create_display(640, 360);
   if (!display) {
      fprintf(stderr, "Could not create the display.\n");
      return 1;
   }

   tile = al_create_bitmap(8, 8);
   queue = al_create_event_queue();
   timer = al_create_timer(1.0 / 30.0);
   if (!tile || !queue || !timer) {
      fprintf(stderr, "Could not create the batch test resources.\n");
      if (tile)
         al_destroy_bitmap(tile);
      if (queue)
         al_destroy_event_queue(queue);
      if (timer)
         al_destroy_timer(timer);
      al_destroy_display(display);
      return 1;
   }

   al_set_target_bitmap(tile);
   al_clear_to_color(al_map_rgb(255, 255, 255));
   al_set_target_backbuffer(display);

   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(display));
   al_register_event_source(queue, al_get_timer_event_source(timer));
   al_start_timer(timer);
   update_title(display, selected, automatic);

   while (running) {
      ALLEGRO_EVENT event;
      al_wait_for_event(queue, &event);

      if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         running = false;
      }
      else if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
         al_acknowledge_resize(display);
         redraw = true;
      }
      else if (event.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
         if (automatic && ++ticks >= 60) {
            ticks = 0;
            selected = (selected + 1) % (int)(sizeof batch_quads / sizeof batch_quads[0]);
            update_title(display, selected, automatic);
         }
      }
      else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
         const int count = (int)(sizeof batch_quads / sizeof batch_quads[0]);
         switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
               running = false;
               break;
            case ALLEGRO_KEY_LEFT:
               selected = (selected + count - 1) % count;
               ticks = 0;
               update_title(display, selected, automatic);
               redraw = true;
               break;
            case ALLEGRO_KEY_RIGHT:
               selected = (selected + 1) % count;
               ticks = 0;
               update_title(display, selected, automatic);
               redraw = true;
               break;
            case ALLEGRO_KEY_A:
               automatic = !automatic;
               ticks = 0;
               update_title(display, selected, automatic);
               break;
            case ALLEGRO_KEY_F10: {
               const bool fullscreen =
                  (al_get_display_flags(display) & ALLEGRO_FULLSCREEN_WINDOW) != 0;
               if (!al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW,
                     !fullscreen)) {
                  fprintf(stderr, "Fullscreen transition failed.\n");
               }
               redraw = true;
               break;
            }
         }
      }

      if (redraw && al_is_event_queue_empty(queue)) {
         draw_batch(display, tile, selected);
         redraw = false;
      }
   }

   al_destroy_timer(timer);
   al_destroy_event_queue(queue);
   al_destroy_bitmap(tile);
   al_destroy_display(display);
   return 0;
}

