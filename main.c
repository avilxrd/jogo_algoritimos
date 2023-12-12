#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const float FPS = 60;
const int SCREEN_W = 1280;
const int SCREEN_H = 768;
ALLEGRO_FONT * font = NULL;

//~~~~~~~~~~GLOBALS~~~~~~~~~~
bool status = false;
float molex, moley;
float wmole, hmole;
float x[3] = {308.1, 559.4, 812};
float y[3] = {138.8, 343.8, 548.4};

float hole_w = 161.3, hole_h = 80;


bool mouse_mole(int mousex, int mousey){
    if(mousex >= molex && mousex <= molex + wmole && mousey >= moley && mousey <= moley + hmole){
        printf("True\n");
        return true;
    }else{
        printf("False\n");
        return false;
    }
}

int main(){
    srand(time(NULL));
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    ALLEGRO_TIMER * timer = NULL;

    //~~~~~~~~~~INICIALIZAÇÕES~~~~~~~~~~
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
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize the audio addon!\n");
        return -1;
    }
    al_init_font_addon();
    font = al_create_builtin_font();
    al_set_font_size(font, 36);
    if (!font) {
        fprintf(stderr, "ailed to initialize the font addon!\n");
        return -1;
    }
    //~~~~~~~~~~PONTEIROS DE BITMAPS~~~~~~~~~~
    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_BITMAP * enemy= NULL;
    ALLEGRO_BITMAP * hole = NULL;
    ALLEGRO_SAMPLE * background_music = NULL;

    //~~~~~~~~~~CARREGANDO IMAGENS~~~~~~~~~~
    background = al_load_bitmap("./images/background.png");
    hole = al_load_bitmap("./images/hole.png");
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            al_draw_bitmap(hole, x[i], y[j], 0);
        }
    }
    enemy = al_load_bitmap("./images/mole.png");
    hmole = al_get_bitmap_height(enemy);
    wmole = al_get_bitmap_width(enemy);

    //~~~~~~~~~~CARREGANDO AUDIOS~~~~~~~~~~
   // al_reserve_samples(10);
   // background_music = al_load_sample("./audios/background_music.mp3");


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
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                float mousex = ev.mouse.x;
                float mousey = ev.mouse.y;
                printf("x: %f y: %f\n", mousex, mousey);
                if(mouse_mole(mousex, mousey) == true){
                        score = score + 1;
                        status = false;
                }
        }else if(ev.type == ALLEGRO_EVENT_TIMER){
            //create_enemy();
            if(status==false){
                int randx, randy;
                randx = rand()%3;
                randy = rand()%3;
                molex = x[randx] + 15.0;
                moley = y[randy] - 60.0;
                al_draw_bitmap(enemy, molex, moley, 0);
                status = true;
            }
            redraw = true;
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_draw_bitmap(background, 0, 0, 0);
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    al_draw_bitmap(hole, x[i], y[j], 0);
                }
            }
            if (status == true) {
                al_draw_bitmap(enemy, molex, moley, 0);
            }
            al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 25, ALLEGRO_ALIGN_CENTER, "Pontos: %d", score);

            al_flip_display();
        }

    }

        return 0;
    }

