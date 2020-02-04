// Quick note: this probably isn't really the most optimal way of doing anything here.

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "enums.h"
#define FPS 60.0

//
// Separator
//
ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* evnt_queue = nullptr;
ALLEGRO_BITMAP** bmps = nullptr;
ALLEGRO_FONT* font = nullptr;
ALLEGRO_TIMER* timer = nullptr;

const int screenD[2]{ 640, 480 };

// Starter
int loader()
{
    // Loads
    if (!al_init()) return -1;
    al_init_font_addon();
    if (!al_init_ttf_addon()) return -1;
    if (!al_init_image_addon()) return -1;
    if (!al_install_keyboard()) return -1;
    if (!al_install_mouse()) return -1;
    // Creates display
    display = al_create_display(screenD[0], screenD[1]);
    if (!display) return -1;

    // Creates timer
    timer = al_create_timer(1.0 / FPS);
    if (!timer)
    {
        al_destroy_timer(timer); 
        al_destroy_display(display); 
        return -1;
    }

    // Changes window title name
    al_set_window_title(display, "Wabunga!");

    // Creates the bitmaps
    bmps = new ALLEGRO_BITMAP * [50];
    bmps[0] = al_load_bitmap("image.png"); //logo o.o
    bmps[1] = al_create_bitmap(16, 32); //cubi

    // Gives color to our square!
    al_set_target_bitmap(bmps[1]);
    al_clear_to_color(al_map_rgb(69, 69, 69));
    al_set_target_bitmap(al_get_backbuffer(display));

    // Sets font and size
    font = al_load_ttf_font("Roboto-Regular.ttf", 15, 0);

    // Draws the start stuff idunno
    //start_draws();

    // Creates event queue
    evnt_queue = al_create_event_queue();
    al_register_event_source(evnt_queue, al_get_keyboard_event_source());
    al_register_event_source(evnt_queue, al_get_display_event_source(display));
    al_register_event_source(evnt_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_start_timer(timer);

    return 1;
};


//
// Main
//
int main(int argc, char** argv) {

    // If set to 1 it draws
    int draw = 1;
    // If set to 1 then quit
    int wants_quit = 0;
    // Movement -- Move by
    int posx=50, movex = 5;
    int posy=250, movey = 5;

    // If it fails to load anything it just quits
    if (!loader())
    {
        return -1;
    }

    while (!wants_quit)
    {
        ALLEGRO_EVENT evnts;
        al_wait_for_event(evnt_queue, &evnts);
        // Moves Left / Right

        // I'll change these to switches later
        if (evnts.keyboard.keycode == ALLEGRO_KEY_D)
        {
            posx += movex;
            draw = 1;
        }
        else if (evnts.keyboard.keycode == ALLEGRO_KEY_A)
        {
            posx -= movex;
            draw = 1;
        }
        else if (evnts.keyboard.keycode == ALLEGRO_KEY_W)
        {
            posy -= movey;
            draw = 1;
        }
        else if (evnts.keyboard.keycode == ALLEGRO_KEY_S)
        {
            posy += movey;
            draw = 1;
        }
        else if (evnts.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            wants_quit = 1;
        };

        if (draw && al_is_event_queue_empty(evnt_queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            // Draws logo
            al_draw_scaled_bitmap(bmps[0], 0, 0, 160, 32, 160, 50, 320, 64, 0);
            // Draws the square in posx and posy
            al_draw_bitmap(bmps[1], posx, posy, 0);
            al_flip_display();

            // So it can be called again
            draw = 0;
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_bitmap(bmps[1]);
    al_destroy_event_queue(evnt_queue);

    return 0;
}