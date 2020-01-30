#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "enums.h"

//
// Constants
//
const int display_width = 640;
const int display_height = 480;

//
// Separator
//
int main(int argc, char** argv) {

    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_EVENT_QUEUE* evnt_queue = nullptr;
    ALLEGRO_BITMAP* imagem = nullptr;

    if (!al_init()) return -1;
    if (!al_init_image_addon()) return -1;
    if (!al_install_keyboard()) return -1;
    if (!al_install_mouse()) return -1;

    display = al_create_display(display_width, display_height);
    imagem = al_load_bitmap("image.png");

    evnt_queue = al_create_event_queue();
    if (!evnt_queue) return -1;

    al_register_event_source(evnt_queue, al_get_keyboard_event_source());
    al_register_event_source(evnt_queue, al_get_mouse_event_source());
    al_register_event_source(evnt_queue, al_get_display_event_source(display));

    while (1)
    {
        ALLEGRO_EVENT evnt;
        al_wait_for_event(evnt_queue, &evnt);

        // If you press this it will crash the program, I'm going to fix this later :(
        if (evnt.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            al_draw_scaled_bitmap(imagem, 0, 0, 160, 32, 160, 50, 320, 64, 0);
            al_flip_display();

            al_rest(10.0);
            al_destroy_display(display);
        }
        if (evnt.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            al_destroy_display(display);
        }

    }

    return 0;
}