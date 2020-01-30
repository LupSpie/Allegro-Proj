#include <stdio.h>
#include <stdlib.h>
// Sorry mate, this is only in portuguese for now smh
// N�o deve tar tudo certo (o que comentei) smh
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int main(int argc, char** argv) {

    // Isso aqui � necessario, pois n�o queremos que o programa carregue tudo sem ter nem inicializado
    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_EVENT_QUEUE* evnt_queue = nullptr;
    ALLEGRO_BITMAP* imagem = nullptr;

    // Tudo isso aqui serve pra testar se nada deu ruim, nesse caso, se der ruim ele s� retorna -1.
    if (!al_init()) return -1;
    if (!al_init_image_addon()) return -1;
    if (!al_install_keyboard()) return -1;
    if (!al_install_mouse()) return -1;

    //Esse aqui fala pro allegro criar o display, nesse caso sendo 640x480
    display = al_create_display(640, 480);
    //Esse aqui carrega a logo, no caso chamada de image
    imagem = al_load_bitmap("image.png");

    //Esse aqui � o come�o do input
    /*Esses dois comandos abaixo, come�ando do primeiro, falam que evnt_queue vai criar uma lista de eventos que antes estava definida
    como null (vazio) ja o segundo apenas da um check pra ver se n�o deu problema.
    */
    evnt_queue = al_create_event_queue();
    if (!evnt_queue) return -1;

    //Essas belezinhas aqui adicionam os inputs, ou as sources, do teclado, mouse e display respectivamente para a nossa lista de eventos
    al_register_event_source(evnt_queue, al_get_keyboard_event_source());
    al_register_event_source(evnt_queue, al_get_mouse_event_source());
    al_register_event_source(evnt_queue, al_get_display_event_source(display));

    while (1)
    {
        //Esse aqui fala que o evento que queremos se chama evnt
        ALLEGRO_EVENT evnt;

        al_wait_for_event(evnt_queue, &evnt);

        //Se o user clicar no teclado e esse clique for a tecla espa�o, executar o que tem dentro dele
        if (evnt.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            //Esses aqui desenha a nossa imagem e a posiciona no meio da tela (160) depois ele flipa o display para mostrar no display.
            al_draw_scaled_bitmap(imagem, 0, 0, 160, 32, 160, 50, 320, 64, 0);
            al_flip_display();


            //Descansar ap�s tudo, ent�o fechar
            al_rest(10.0);
        }
    }

    return 0;
}