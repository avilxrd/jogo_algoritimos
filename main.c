#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const float FPS = 60;
const int SCREEN_W = 1280;
const int SCREEN_H = 768;

int main(){

    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    ALLEGRO_TIMER * timer = NULL;

    //INICIALIZAÇÕES
    if(!al_init()){
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer){
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    bool redraw = true; //Variável para atualizar a tela
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);//Flags do display
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display){
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    al_set_window_title(display, "HeadHunters");
    if(!al_install_keyboard()){
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    if(!al_install_mouse()){
        fprintf(stderr, "failed to initialize the mouse!\n");
        return -1;
    }
    if(!al_init_image_addon()){
        fprintf(stderr, "failed to initialize the image addon!\n");
        return -1;
    }
    //PONTEIROS DE BITMAPS
    ALLEGRO_BITMAP * background = NULL;
    //CARREGANDO IMAGENS
    background = al_load_bitmap("./images/background.png");
    //MENSAGENS DE ERRO
    if(!background){
        fprintf(stderr, "falhou ao criar bitmap!\n");
        return -1;
    }
    //**--**--**--**
    al_set_target_bitmap(al_get_backbuffer(display));
    event_queue = al_create_event_queue(); //Criando a fila de eventos
    //MENSAGEM DE ERRO
    if(!event_queue){
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }
    //EVENTOS
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    //ATUALIZANDO A TELA
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);
    //LOOP PRINCIPAL DO JOGO
    int score = 0;
    int click = 0;

    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(evente_queue, &ev);

        float mouse_x, mouse_y;

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            switch(ev.mouse.button)
            {
            case 1:
                printf("x: %d y: %d", ev.mouse.x, ev.mouse.y);
                if(click==0){
                }else{

                }

            }
        }else if(ev.type == ALLEGRO_EVENT_TIMER){
            al_draw_bitmap(background, 0, 0, 0);
            al_flip_display();

        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
    }

    if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_draw_bitmap(background, 0, 0, 0);
            /*
            al_draw_bitmap(rebatedorEsquerda,rebatedorEsquerda_pos_x, rebatedorEsquerda_pos_y, 0);
            al_draw_bitmap(rebatedorDireita,rebatedorDireita_pos_x, rebatedorDireita_pos_y, 0);
            al_draw_bitmap(bola, bola_pos_x, bola_pos_y, 0);
            */
            al_flip_display();
        }

    }


}

