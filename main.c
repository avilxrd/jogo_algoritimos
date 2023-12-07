#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


void main(){

    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_mouse();

    ALLEGRO_DISPLAY * display = al_create_display(1280, 768);
    al_set_window_title(display, "HeadHunters");
    ALLEGRO_FONT * font = al_create_builtin_font();
    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();

    ALLEGRO_BITMAP * background = al_load_bitmap("./images/background.png");
    al_draw_bitmap(background, 0, 0, 0);
    al_flip_display();

    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        srand(time(NULL));

        ALLEGRO_BITMAP * mole = al_load_bitmap("./images/mole.png");
        float holes_x[3], holes_y[3];
        holes_x[0] = 385.7; holes_x[1] = 578.3; holes_x[2] = 770.9;
        holes_y[0] = 196.9; holes_y[1] = 353.2; holes_y[2] = 509.8;

        int i, x, y;
        for(i=0; i<10; i++){
            x = rand() % 3;
            y = rand() % 3;
            al_draw_bitmap(mole, holes_x[x], holes_y[y], 0);
            al_flip_display();

        }






    }
    printf("break");

}
