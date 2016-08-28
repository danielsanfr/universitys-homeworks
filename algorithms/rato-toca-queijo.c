#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

const float FPS = 60;
const float SPEED = 4.0; //Velocidade que o rato ira se mover
const int SCREEN_W = 640; //Largura da tela.
const int SCREEN_H = 480; //Altura da tela.
const int TOCA_SIZEX = 96; //Largura do toca.
const int TOCA_SIZEY = 143; //Altura do toca.
const int RATO_SIZEX = 74; //Largura do rato.
const int RATO_SIZEY = 75; //Altura do rato.
const int QUEIJO_SIZEX = 102; //Largura do queijo.
const int QUEIJO_SIZEY = 54; //Alturo do queijo.

enum MYKEYS
{
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL; //Ponteiro que aponta para display(tela).
    ALLEGRO_TIMER *timer = NULL; //Ponteiro que aponta para o time(tempo).
    ALLEGRO_EVENT_QUEUE *filaEventos = NULL; //Ponteiro que aponta para os eventos.
    ALLEGRO_EVENT evento; //Ponteiro que aponta para o evento.
    ALLEGRO_BITMAP  *toca    = NULL; //Ponteiro que aponta para imagem da toca.
    ALLEGRO_BITMAP  *rato    = NULL; //Ponteiro que aponta para imagem do rato.
    ALLEGRO_BITMAP  *queijo  = NULL; //Ponteiro que aponta para imagem do queijo.
    int queijo_x = 0, queijo_y = 0; //Coordenadas do queijo.
    int rato_x = 5 , rato_y = 55; //Coordenadas do Rato.
    int direcao = 0; //Variavel que auxilia na direcao do rato.
    float orientacao = 0; //Angulo que o rato ira aparecer na tela.
    bool key[4] = {false, false, false, false};
    bool redraw = false; //Variavel para auxiliar no redesenho das imagens.
    bool sair = false; //Variavel para sair do loop de movimento.
    bool vitoria = false; //Variavel logica para informar que o rato realmente chegou no queijo -> false = nao pego o queijo - true = pego o queijo.
    /*******************************Testes se tudo foi inicializado com sucesso********************************/
    if(!al_init())
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao inicializar o allegro!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if(!al_init_image_addon())
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao inicializar o complemento image!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if (!al_init_primitives_addon())
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao inicializar o complemento primitives!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if(!al_install_keyboard())
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao inicializar o Teclado(keyboard)!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao criar tempo(timer)!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H); //Cria a Janela(display) com um tamando de 640x480.
    if(!display)
    {
        al_show_native_message_box(display, "Error", "Error", "Falha do criar o display!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_set_window_title(display, "Rato e o Queijo"); //Titulo da Janela.
    /**********************Eventos (fechar janela)*********************/
    filaEventos = al_create_event_queue();
    if (!filaEventos)
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao criar a fila de eventos!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    al_register_event_source(filaEventos, al_get_display_event_source(display));
    /******************************************************************/
    /*************************Carrega imagens**************************/
    toca = al_load_bitmap("toca2.png"); //Carrega imagem da toca no vetor da toca.
    rato = al_load_bitmap("rato2.png"); //Carrega imagem do rato no vetor do rato.
    queijo = al_load_bitmap("queijo2.png"); //Carrega imagem do queijo no vetor do queijo.
    if((!toca) || (!rato) || (!queijo)) //Testa se alguma imagem nao foi carregada.
    {
        al_show_native_message_box(display, "Error", "Error", "Falha ao carregar imagens!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    /******************************************************************/
    /***********************************Fim dos testes de Inicialicao******************************************/
    al_register_event_source(filaEventos, al_get_display_event_source(display)); //Registra os eventos do display(tela).
    al_register_event_source(filaEventos, al_get_timer_event_source(timer)); //Registra os eventos do timer(tempo).
    al_register_event_source(filaEventos, al_get_keyboard_event_source()); //Registra os eventos do keyboard(teclado).
    srand(time(NULL));
    queijo_x = rand() % SCREEN_W; //Escolhe coordenada X aleatoria para queijo.
    queijo_y = rand() % SCREEN_H; //Escolhe coordenada Y aleatoria para queijo.
    /****************************************Garante que o queijo ficara a + de 100 pixeis da toca*************************************************/
    while(1)
    {
        if((queijo_x > TOCA_SIZEX + 105 && queijo_x < SCREEN_W - QUEIJO_SIZEX) && (queijo_y > 0 && queijo_y < SCREEN_H - QUEIJO_SIZEY)) break;
        else if((queijo_x > 0 && queijo_x < SCREEN_W - QUEIJO_SIZEX) && (queijo_y > TOCA_SIZEY + 100 && queijo_y < SCREEN_H - QUEIJO_SIZEY)) break;
        //Caso o queijo não esteja a + de 100 pixeis da toca escolhe outras coordenadas aleatoriamente para o queijo.
        queijo_x = rand() % SCREEN_W; //Escolhe outra coordenada X aleatoria para queijo.
        queijo_y = rand() % SCREEN_H; //Escolhe outra coordenada Y aleatoria para queijo.
    }
    /*********************************************************************************************************************************************/
    al_clear_to_color(al_map_rgb(255,255,255)); //Apaga tudo e coloca o undo do display(tela) em branco.
    al_draw_bitmap(toca, 5, 0, 0); //Desenha a toca na display(tela).
    al_draw_bitmap(rato, rato_x, rato_y, 0); //Desenha o rato na display(tela).
    al_draw_bitmap(queijo, queijo_x, queijo_y, 0); //Desenha o queijo na display(tela).
    al_flip_display(); //Atualiza o que esta no display(tela).
    al_start_timer(timer); //Inicia o tempo.
    /*************************Loop de movimentação do rato****************************/
    while(!sair)
    {
        al_wait_for_event(filaEventos, &evento);
        if(evento.type == ALLEGRO_EVENT_TIMER)
        {
            /********************Incrementa ou decrementa a nova posicao do rato*********************/
            if(key[KEY_UP] && rato_y >= SPEED)
            {
                rato_y -= SPEED;
                ++direcao;
            }
            if(key[KEY_DOWN] && rato_y <= SCREEN_H - RATO_SIZEY - SPEED)
            {
                rato_y += SPEED;
                direcao += 2;
            }
            if(key[KEY_LEFT] && rato_x >= SPEED)
            {
                rato_x -= SPEED;
                direcao += 4;
            }
            if(key[KEY_RIGHT] && rato_x <= SCREEN_W - RATO_SIZEX - SPEED)
            {
                rato_x += SPEED;
                direcao += 8;
            }
            /*********************************Fim da nova posicao************************************/
            /********************Para onde o rato vai virar*********************/
            if(direcao == 1) orientacao = 3.14; //Norte.
            else if(direcao == 2) orientacao = 0; //Sul.
            else if(direcao == 4) orientacao = 1.57; //Oeste.
            else if(direcao == 8) orientacao = 4.71; //Leste.
            else if(direcao == 9) orientacao = 3.93; //Nordeste.
            else if(direcao == 5) orientacao = 2.36; //Noroeste.
            else if(direcao == 6) orientacao = 0.79; //Sudoeste.
            else if(direcao == 10) orientacao = 5.5; //Sudeste.
            direcao = 0;
            /******************************************************************/
            redraw = true;
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Teste se o display(tela) foi fechado.
        {
            vitoria = false; //Rato não chegou no queijo. A janela foi fechada.
            break;
        }
        else if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            /***************Verifica qual tecla foi apertada******************/
            switch(evento.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
            /******************************************************************/
        }
        else if(evento.type == ALLEGRO_EVENT_KEY_UP)
        {
            /*****************Verifica qual tecla foi solta********************/
            switch(evento.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE: // Testa se a tecla ESC foi apertada. Se sim acaba o jogo.
                sair = true;
                vitoria = false;
                break;
            }
            /******************************************************************/
        }
        /**************Se preciso redesenha a o rato na nova posicao*****************/
        if(redraw && al_is_event_queue_empty(filaEventos))
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(255,255,255)); //Apaga tudo e coloca o undo do display(tela) em branco.
            al_draw_bitmap(toca, 5, 0, 0); //Desenha a toca na display(tela).
            al_draw_bitmap(queijo, queijo_x, queijo_y, 0); //Desenha o queijo na display(tela).
            al_draw_rotated_bitmap(rato, RATO_SIZEX / 2.0, RATO_SIZEY / 2.0, rato_x + (RATO_SIZEX / 2.0), rato_y + (RATO_SIZEY / 2.0), orientacao, 0); //Desenha o rato na display(tela) na nova posicao e na nova orientacao.
            al_flip_display(); //Atualiza o que esta no display(tela).
        }
        /*******************Fim da atualizacao do display(tela)***********************/
        /***********************Teste: se o rato chegou no queijo*********************/
        if(((rato_x - 10 >= queijo_x) || (rato_x + RATO_SIZEX - 10 >= queijo_x)) && ((rato_x + 10 <= (queijo_x + QUEIJO_SIZEX)) || (rato_x + RATO_SIZEX + 10 <= (queijo_x + QUEIJO_SIZEX))) &&
           ((rato_y - 10 >= queijo_y) || (rato_y + RATO_SIZEY - 10 >= queijo_y)) && ((rato_y + 10 <= (queijo_y + QUEIJO_SIZEY)) || (rato_y + RATO_SIZEY + 10 <= (queijo_y + QUEIJO_SIZEY))))
        {
            vitoria = true;
            sair = true;
        }
        /********************************Fim do teste*********************************/
    }
    /***********************Fim do Loop de movimentação do rato**************************/
    /***********************Dialogo de vitoria***********************/
    if(vitoria)
    {
        al_show_native_message_box(al_get_current_display(),
            "Rato e o Queijo",
            "Você Conseguiu!!!",
            "Parabéns por ter conseguido fazer o ratinho pegar o queijo!",
            NULL, ALLEGRO_MESSAGEBOX_WARN);
    }
    /****************************************************************/
    al_destroy_display(display); //Destroi o ponteiro para o display(tela) - Limpa a memoria
    al_destroy_bitmap(toca); //Destroi o ponteiro para o bitmap da toca - Limpa a memoria
    al_destroy_bitmap(rato); //Destroi o ponteiro para o bitmap do rato - Limpa a memoria
    al_destroy_bitmap(queijo); //Destroi o ponteiro para o bitmap do queijo - Limpa a memoria
    al_destroy_timer(timer); //Destroi o ponteiro para o timer - Limpa a memoria
    return 0;
}
