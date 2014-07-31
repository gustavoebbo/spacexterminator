#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL_mixer.h>


#define MAX_ARRAY 10
#define MAX_NOME 50

/* ------ Anotações ------ //

Pavilhão
Setor
radiotatividade




// ------- Fim anotações ------- */

/*
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    //PASSANDO OS DESTINOS;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}
*/
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

/*
void blita_tudo(int mapa[][], SDL_Surface* blocoind, SDL_Surface* blocodes, SDL_Surface* imgbomb, SDL_Surface* screen){
    int i,j;
    for(i=0;i<17;i++){
        for(j=0;j<11;j++){
            if(mapa[j][i]==1){
                apply_surface((53+i*54),(119+j*54),blocoind,screen);
            }
            else if(mapa[j][i]==3){
                apply_surface((53+i*54),(119+j*54),blocodes,screen);
            }
                 // else if(mapa[j][i]==2)
                 // {
                 //     apply_surface((68+i*64),(164+j*64),sprite_dn_bai3_game_DN,screen);
                 // }
             else if(mapa[j][i]==5){
                apply_surface((53+i*54),(119+j*54),imgbomb,screen);
             }
         }
     }
}
*/





typedef struct
{
    char nome[20];
    int pontuacaorecord;
} RECORDE;


typedef struct
{
    RECORDE vetor[10];
    int n;

} ARRAY;


RECORDE elemento(ARRAY *, int);
int tamanho(ARRAY *);
void insere(ARRAY *, RECORDE);

void remove_posicao(ARRAY *, int);
//void imprime(ARRAY *);
void sort(ARRAY *);
void bubble_sort(RECORDE *, int);


int main ( int argc, char** argv )
{

    //SDL_EnableUNICODE( SDL_ENABLE );


    RECORDE jogador;
    char temp[20];

    jogador.pontuacaorecord = 0;
    // jogador.nome = 'JOGADOR';

    char *nome_arquivo = "saves/recordes.dat";
    FILE *p_arquivo;

    ARRAY array;
    array.n = 0;

    if((p_arquivo = fopen(nome_arquivo, "r")) != NULL)
    {
        fread(&array, sizeof(ARRAY), 1, p_arquivo);
        fclose(p_arquivo);
    }

    //imprime(&array);

    RECORDE rec1;
    RECORDE recorde;
    char vaiblitar[50];
    SDL_Surface *text_vaiblitar = NULL;



    SDL_Rect personagem;
    SDL_Rect dn_sprite[16];
    SDL_Rect *dn_pointer;

    SDL_Rect bomb;
    SDL_Rect bomb_sprite[2];
    SDL_Rect *bomb_pointer;

    SDL_Rect exp_cent;
    SDL_Rect exp_cim;
    SDL_Rect exp_esq;
    SDL_Rect exp_bai;
    SDL_Rect exp_dir;
    SDL_Rect exp_cimfim;
    SDL_Rect exp_esqfim;
    SDL_Rect exp_baifim;
    SDL_Rect exp_dirfim;
    SDL_Rect exp_sprite[27];
    SDL_Rect *exp_cent_pointer;
    SDL_Rect *exp_cim_pointer;
    SDL_Rect *exp_esq_pointer;
    SDL_Rect *exp_bai_pointer;
    SDL_Rect *exp_dir_pointer;
    SDL_Rect *exp_cimfim_pointer;
    SDL_Rect *exp_esqfim_pointer;
    SDL_Rect *exp_baifim_pointer;
    SDL_Rect *exp_dirfim_pointer;

    SDL_Rect caiexp;
    SDL_Rect caiexp_sprite[5];
    SDL_Rect *caiexp_pointer;


    SDL_Rect inimigoa;
    SDL_Rect *inia_pointer;

    SDL_Rect inimigob;
    SDL_Rect *inib_pointer;

    SDL_Rect inimigoc;
    SDL_Rect *inic_pointer;

    SDL_Rect inimigod;
    SDL_Rect *inid_pointer;


    SDL_Rect strdanc_sprite[6];
    SDL_Rect alienogre_sprite[16];
    SDL_Rect alienradio_sprite[16];
    SDL_Rect alienberserk_sprite[16];

    Uint8 *keystates = SDL_GetKeyState( NULL );
    srand(time(NULL));

    int i,j,l;
    int tempo_passo = 0, ult_sent = 8, cmpr_sent = 8, rodador_movdn = 1, conf_bomb = 0, frac_passoy = 0, frac_passox = 0, tempo_passo_mov = 0, tempo_bomb, conf_kup = 0, rb = 1, rodador_tbomb = 0, tempo_spritebomb = SDL_GetTicks(), colexp_a = 0, colexp_b = 0, colexp_c = 0, colexp_d = 0, tempo_rodexp = 0, rodador_animexp = 0, tempo_parexp = 0, rodador_parexp = 0, morreu_bomba = 1, rodador_temporenasc = 0, tempo_renasc = -1500, roda_blitaplayer = 1, tempo_passoinia = SDL_GetTicks(), tempo_passoinib = SDL_GetTicks(), escolhe_movinia = 0, escolhe_movinib = 0, decidido_movinia = 0, decidido_movinib = 0, ult_sentinia = 0, ult_sentinib = 0, rodador_animinia = 0, rodador_animinib = 0, rodador_primeiro_passo_movinia = 0, rodador_primeiro_passo_movinib = 0, frac_passoinia = 1, frac_passoinib = 1, tempo_passo_movinia = SDL_GetTicks(), tempo_passo_movinib = SDL_GetTicks(), rodador_primeiro_passo_mov = 0, mudou_bloco = 0, inimigoa_morto = 0, inimigob_morto = 0, colet_clubcard = 0, tempo_blinkiconclub = 0, cron_segjogo = 1, cron_segrest = 1, cron_minrest = 0, cron_segminrest = 0, matou_alien = 0, tempo_matoualien = -101, cont_decmovinia = 0, cont_decmovinib = 0, tempo_passoinic = SDL_GetTicks(), escolhe_movinic = 0, decidido_movinic = 0, ult_sentinic = 0, rodador_animinic = 0, rodador_primeiro_passo_movinic = 0, frac_passoinic = 1, tempo_passo_movinic = SDL_GetTicks(), inimigoc_morto = 0, cont_decmovinic = 0, tempo_passoinid = SDL_GetTicks(), escolhe_movinid = 0, decidido_movinid = 0, ult_sentinid = 0, rodador_animinid = 0, rodador_primeiro_passo_movinid = 0, frac_passoinid = 1, tempo_passo_movinid = SDL_GetTicks(), inimigod_morto = 0, cont_decmovinid = 0, exist_inia = 0, exist_inib = 0, exist_inic = 0, exist_inid = 0;
    int  movimenta_x[2], movimenta_y[2], cord_animexp[2];
    char string_pontuacao[20];
    char string_vidas[20];
    char string_raiobomb[20];
    char string_cronometro[50];
    char string_faladn[80];
    movimenta_x[0] = 1;
    movimenta_y[0] = 1;    




    //O BLOCO QUE SE MOVE COMEÇA
    int yAtual = 0;
    int xAtual = 0;
    int inc_mx  = 0;
    int inc_my  = 0; 

    int xInimigoa;
    int yInimigoa;

    int xInimigob;
    int yInimigob;

    int xInimigoc;
    int yInimigoc;

    int xInimigod;
    int yInimigod;

    //xAtual está relacionado com a coluna.
    //yAtual está relacionado com a linha.


    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        return 0;
    }

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 1;
    }

     //Initialize SDL_ttf
    if( TTF_Init() == -1 ) {
        return 0;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1024, 768, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
//|SDL_FULLSCREEN
    if ( !screen )
    {
        printf("Nao deu pra por 1024x768 de tamanho: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption( "Duke Nukem - Nuke Time", NULL );

    //SDL_Surface* posi_matriz;
    //posi_matriz = IMG_Load("posi_matriz.png");
    //if (!posi_matriz)
    //{
    //    printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
    //    return 1;
    //}

    SDL_Surface *textrecord = NULL;

    SDL_Surface *text_pontuacao = NULL;
    SDL_Surface *text_vidas = NULL;
    SDL_Surface *text_raiobomb = NULL;
    SDL_Surface *text_cronometro = NULL;
    SDL_Surface *text_faladn = NULL;
    TTF_Font *font = NULL;
    TTF_Font *font_fala = NULL;
    TTF_Font *font_pontos = NULL;
    SDL_Color textCorVermelho = {255,0,0};
    SDL_Color textCorAmarelo = {253,170,23};
    SDL_Color textColorCinza = {56,56,56};
    
    //Open the font
    font = TTF_OpenFont( "fontes/display.ttf", 28 );

    //Open the font
    font_fala = TTF_OpenFont( "fontes/arial.ttf", 18 );

    //Open the font
    font_pontos = TTF_OpenFont( "fontes/arial.ttf", 30 );


    //If there was an error in loading the font
    if( font == NULL ) {
        return 0;
    }

    // load an image
    SDL_Surface* blocoind = NULL;
    blocoind = IMG_Load("imagens/blocoindes_game_DN_2.png");
    if (!blocoind)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* player = NULL;
    player = IMG_Load("imagens/sprite_dn_game_DN.png");
    if (!player)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* alienogre = NULL;
    alienogre = IMG_Load("imagens/sprite_alienogre_game_DN.png");
    if (!alienogre)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* stripdanc = NULL;
    stripdanc = IMG_Load("imagens/sprite_strip_fimfase_DN.png");
    if (!stripdanc)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* alienradio = NULL;
    alienradio = IMG_Load("imagens/sprite_alienradio_game_DN.png");
    if (!alienradio)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* iconstrip = NULL;
    iconstrip = IMG_Load("imagens/iconstrip_game_DN.png");
    if (!iconstrip)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* iconstripfimfase = NULL;
    iconstripfimfase = IMG_Load("imagens/iconstrip_fimfase_DN.png");
    if (!iconstrip)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* iconclub = NULL;
    iconclub = IMG_Load("imagens/iconclub_game_DN.png");
    if (!iconclub)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* blocodes = NULL;
    blocodes = IMG_Load("imagens/blocodes_game_DN.png");
    if (!blocodes)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgcaiexp = NULL;
    imgcaiexp = IMG_Load("imagens/sprite_blocodes_game_DN.png");
    if (!imgcaiexp)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgbomb = NULL;
    imgbomb = IMG_Load("imagens/sprite_bomb_game_DN.png");
    if (!imgbomb)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgexp = NULL;
    imgexp = IMG_Load("imagens/sprite_explosion_game_DN.png");
    if (!imgexp)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgpkplut = NULL;
    imgpkplut = IMG_Load("imagens/pkplut_game_DN.png");
    if (!imgpkplut)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgpkvida = NULL;
    imgpkvida = IMG_Load("imagens/pkvida_game_DN.png");
    if (!imgpkvida)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgpkclub = NULL;
    imgpkclub = IMG_Load("imagens/pkclub_game_DN.png");
    if (!imgpkclub)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* clubfimfase = NULL;
    clubfimfase = IMG_Load("imagens/logo_club_fimfase_DN.png");
    if (!clubfimfase)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgburaco = NULL;
    imgburaco = IMG_Load("imagens/buraco_game_DN.png");
    if (!imgburaco)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundoperdeujogo = NULL;
    fundoperdeujogo = IMG_Load("imagens/bg_gameover_DN.png");
    if (!fundoperdeujogo)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundoinstrucoes = NULL;
    fundoinstrucoes = IMG_Load("imagens/bg_instrucoes_DN.png");
    if (!fundoinstrucoes)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundorecordes = NULL;
    fundorecordes = IMG_Load("imagens/bg_recordes_DN.png");
    if (!fundorecordes)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundo = NULL;
    fundo = IMG_Load("imagens/bg_game_DN.png");
    if (!fundo)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundomenu = NULL;
    fundomenu = IMG_Load("imagens/bg_menu_DN.png");
    if (!fundomenu)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundofimfase = NULL;
    fundofimfase = IMG_Load("imagens/bg_fimfase_DN.png");
    if (!fundofimfase)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundopause = NULL;
    fundopause = IMG_Load("imagens/bg_pause_DN.png");
    if (!fundopause)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *fundowingame = NULL;
    fundowingame = IMG_Load("imagens/bg_wingame_DN.png");
    if (!fundowingame)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *seletor = NULL;
    seletor = IMG_Load("imagens/selec_menu_DN.png");
    if (!seletor)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

        SDL_Surface *fundocreditos = NULL;
      fundocreditos = IMG_Load("imagens/creditos_game_DN.png");
      if (!fundocreditos)
      {
      printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
      return 1;
      }

      SDL_Surface *fundopreto = NULL;
      fundopreto = IMG_Load("imagens/fundopreto_game_DN.png");
      if (!fundopreto)
      {
      printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
      return 1;
      }

    Mix_Music *theme = NULL;
    
    // LOAD FALAS.
    Mix_Chunk *diesob = NULL;
    Mix_Chunk *letgod = NULL;
    Mix_Chunk *hell = NULL;
    Mix_Chunk *hurts = NULL;
    // LOAD EXPLOSAO
    Mix_Chunk *explosao = NULL;

    theme = Mix_LoadMUS( "audio/theme.wav" );
    

    if(theme == NULL)
        printf("Erro ao carregar a música\n");

    diesob = Mix_LoadWAV( "audio/mutantdie.wav" );
  
    hurts = Mix_LoadWAV( "audio/mutantdie.wav" );
    letgod = Mix_LoadWAV( "audio/mutantdie.wav" );
   
    hell = Mix_LoadWAV( "audio/mutantdie.wav" );
   
    explosao = Mix_LoadWAV( "audio/explosao.wav" );
    


     /* ----- Sprites bomba ----- */
     bomb_sprite[ 0 ].x = 0;
     bomb_sprite[ 0 ].y = 0;
     bomb_sprite[ 0 ].w = 54;
     bomb_sprite[ 0 ].h = 54;

     bomb_sprite[ 1 ].x = 54;
     bomb_sprite[ 1 ].y = 0;
     bomb_sprite[ 1 ].w = 54;
     bomb_sprite[ 1 ].h = 54;

     /* ----- Sprites caixa Explodindo ----- */
     caiexp_sprite[ 0 ].x = 0;
     caiexp_sprite[ 0 ].y = 0;
     caiexp_sprite[ 0 ].w = 54;
     caiexp_sprite[ 0 ].h = 54;

     caiexp_sprite[ 1 ].x = 54;
     caiexp_sprite[ 1 ].y = 0;
     caiexp_sprite[ 1 ].w = 54;
     caiexp_sprite[ 1 ].h = 54;

     caiexp_sprite[ 2 ].x = 108;
     caiexp_sprite[ 2 ].y = 0;
     caiexp_sprite[ 2 ].w = 54;
     caiexp_sprite[ 2 ].h = 54;

     caiexp_sprite[ 3 ].x = 162;
     caiexp_sprite[ 3 ].y = 0;
     caiexp_sprite[ 3 ].w = 54;
     caiexp_sprite[ 3 ].h = 54;

     caiexp_sprite[ 4 ].x = 216;
     caiexp_sprite[ 4 ].y = 0;
     caiexp_sprite[ 4 ].w = 54;
     caiexp_sprite[ 4 ].h = 54;

     /* ----- Sprites explosao ----- */
     exp_sprite[ 0 ].x = 0;
     exp_sprite[ 0 ].y = 0;
     exp_sprite[ 0 ].w = 54;
     exp_sprite[ 0 ].h = 54;
     
     exp_sprite[ 1 ].x = 54;
     exp_sprite[ 1 ].y = 0;
     exp_sprite[ 1 ].w = 54;
     exp_sprite[ 1 ].h = 54;
     
     exp_sprite[ 2 ].x = 108;
     exp_sprite[ 2 ].y = 0;
     exp_sprite[ 2 ].w = 54;
     exp_sprite[ 2 ].h = 54;
     
     exp_sprite[ 3 ].x = 162;
     exp_sprite[ 3 ].y = 0;
     exp_sprite[ 3 ].w = 54;
     exp_sprite[ 3 ].h = 54;
     
     exp_sprite[ 4 ].x = 216;
     exp_sprite[ 4 ].y = 0;
     exp_sprite[ 4 ].w = 54;
     exp_sprite[ 4 ].h = 54;
     
     exp_sprite[ 5 ].x = 270;
     exp_sprite[ 5 ].y = 0;
     exp_sprite[ 5 ].w = 54;
     exp_sprite[ 5 ].h = 54;
     
     exp_sprite[ 6 ].x = 324;
     exp_sprite[ 6 ].y = 0;
     exp_sprite[ 6 ].w = 54;
     exp_sprite[ 6 ].h = 54;
     
     exp_sprite[ 7 ].x = 378;
     exp_sprite[ 7 ].y = 0;
     exp_sprite[ 7 ].w = 54;
     exp_sprite[ 7 ].h = 54;
     
     exp_sprite[ 8 ].x = 432;
     exp_sprite[ 8 ].y = 0;
     exp_sprite[ 8 ].w = 54;
     exp_sprite[ 8 ].h = 54;
     
     exp_sprite[ 9 ].x = 0;
     exp_sprite[ 9 ].y = 54;
     exp_sprite[ 9 ].w = 54;
     exp_sprite[ 9 ].h = 54;
     
     exp_sprite[ 10 ].x = 54;
     exp_sprite[ 10 ].y = 54;
     exp_sprite[ 10 ].w = 54;
     exp_sprite[ 10 ].h = 54;
     
     exp_sprite[ 11 ].x = 108;
     exp_sprite[ 11 ].y = 54;
     exp_sprite[ 11 ].w = 54;
     exp_sprite[ 11 ].h = 54;

     exp_sprite[ 12 ].x = 162;
     exp_sprite[ 12 ].y = 54;
     exp_sprite[ 12 ].w = 54;
     exp_sprite[ 12 ].h = 54;
     
     exp_sprite[ 13 ].x = 216;
     exp_sprite[ 13 ].y = 54;
     exp_sprite[ 13 ].w = 54;
     exp_sprite[ 13 ].h = 54;
     
     exp_sprite[ 14 ].x = 270;
     exp_sprite[ 14 ].y = 54;
     exp_sprite[ 14 ].w = 54;
     exp_sprite[ 14 ].h = 54;
     
     exp_sprite[ 15 ].x = 324;
     exp_sprite[ 15 ].y = 54;
     exp_sprite[ 15 ].w = 54;
     exp_sprite[ 15 ].h = 54;
     
     exp_sprite[ 16 ].x = 378;
     exp_sprite[ 16 ].y = 54;
     exp_sprite[ 16 ].w = 54;
     exp_sprite[ 16 ].h = 54;
     
     exp_sprite[ 17 ].x = 432;
     exp_sprite[ 17 ].y = 54;
     exp_sprite[ 17 ].w = 54;
     exp_sprite[ 17 ].h = 54;
     
     exp_sprite[ 18 ].x = 0;
     exp_sprite[ 18 ].y = 108;
     exp_sprite[ 18 ].w = 54;
     exp_sprite[ 18 ].h = 54;
     
     exp_sprite[ 19 ].x = 54;
     exp_sprite[ 19 ].y = 108;
     exp_sprite[ 19 ].w = 54;
     exp_sprite[ 19 ].h = 54;
     
     exp_sprite[ 20 ].x = 108;
     exp_sprite[ 20 ].y = 108;
     exp_sprite[ 20 ].w = 54;
     exp_sprite[ 20 ].h = 54;

     exp_sprite[ 21 ].x = 162;
     exp_sprite[ 21 ].y = 108;
     exp_sprite[ 21 ].w = 54;
     exp_sprite[ 21 ].h = 54;
     
     exp_sprite[ 22 ].x = 216;
     exp_sprite[ 22 ].y = 108;
     exp_sprite[ 22 ].w = 54;
     exp_sprite[ 22 ].h = 54;
     
     exp_sprite[ 23 ].x = 270;
     exp_sprite[ 23 ].y = 108;
     exp_sprite[ 23 ].w = 54;
     exp_sprite[ 23 ].h = 54;
     
     exp_sprite[ 24 ].x = 324;
     exp_sprite[ 24 ].y = 108;
     exp_sprite[ 24 ].w = 54;
     exp_sprite[ 24 ].h = 54;
     
     exp_sprite[ 25 ].x = 378;
     exp_sprite[ 25 ].y = 108;
     exp_sprite[ 25 ].w = 54;
     exp_sprite[ 25 ].h = 54;
     
     exp_sprite[ 26 ].x = 432;
     exp_sprite[ 26 ].y = 108;
     exp_sprite[ 26 ].w = 54;
     exp_sprite[ 26 ].h = 54;

     /* ----- Sprites Duke Nukem ----- */
     dn_sprite[ 0 ].x = 0;
     dn_sprite[ 0 ].y = 0;
     dn_sprite[ 0 ].w = 54;
     dn_sprite[ 0 ].h = 54;

     dn_sprite[ 1 ].x = 54;
     dn_sprite[ 1 ].y = 0;
     dn_sprite[ 1 ].w = 54;
     dn_sprite[ 1 ].h = 54;

     dn_sprite[ 2 ].x = 108;
     dn_sprite[ 2 ].y = 0;
     dn_sprite[ 2 ].w = 54;
     dn_sprite[ 2 ].h = 54;

     dn_sprite[ 3 ].x = 162;
     dn_sprite[ 3 ].y = 0;
     dn_sprite[ 3 ].w = 54;
     dn_sprite[ 3 ].h = 54;

     dn_sprite[ 4 ].x = 0;
     dn_sprite[ 4 ].y = 54;
     dn_sprite[ 4 ].w = 54;
     dn_sprite[ 4 ].h = 54;

     dn_sprite[ 5 ].x = 54;
     dn_sprite[ 5 ].y = 54;
     dn_sprite[ 5 ].w = 54;
     dn_sprite[ 5 ].h = 54;

     dn_sprite[ 6 ].x = 108;
     dn_sprite[ 6 ].y = 54;
     dn_sprite[ 6 ].w = 54;
     dn_sprite[ 6 ].h = 54;

     dn_sprite[ 7 ].x = 162;
     dn_sprite[ 7 ].y = 54;
     dn_sprite[ 7 ].w = 54;
     dn_sprite[ 7 ].h = 54;

     dn_sprite[ 8 ].x = 0;
     dn_sprite[ 8 ].y = 108;
     dn_sprite[ 8 ].w = 54;
     dn_sprite[ 8 ].h = 54;

     dn_sprite[ 9 ].x = 54;
     dn_sprite[ 9 ].y = 108;
     dn_sprite[ 9 ].w = 54;
     dn_sprite[ 9 ].h = 54;

     dn_sprite[ 10 ].x = 108;
     dn_sprite[ 10 ].y = 108;
     dn_sprite[ 10 ].w = 54;
     dn_sprite[ 10 ].h = 54;

     dn_sprite[ 11 ].x = 162;
     dn_sprite[ 11 ].y = 108;
     dn_sprite[ 11 ].w = 54;
     dn_sprite[ 11 ].h = 54;

     dn_sprite[ 12 ].x = 0;
     dn_sprite[ 12 ].y = 162;
     dn_sprite[ 12 ].w = 54;
     dn_sprite[ 12 ].h = 54;

     dn_sprite[ 13 ].x = 54;
     dn_sprite[ 13 ].y = 162;
     dn_sprite[ 13 ].w = 54;
     dn_sprite[ 13 ].h = 54;

     dn_sprite[ 14 ].x = 108;
     dn_sprite[ 14 ].y = 162;
     dn_sprite[ 14 ].w = 54;
     dn_sprite[ 14 ].h = 54;

     dn_sprite[ 15 ].x = 162;
     dn_sprite[ 15 ].y = 162;
     dn_sprite[ 15 ].w = 54;
     dn_sprite[ 15 ].h = 54;

     /* ----- Fim sprites Duke Nukem ----- */


     /* ----- Sprites alien ogre----- */
     alienogre_sprite[ 0 ].x = 0;
     alienogre_sprite[ 0 ].y = 0;
     alienogre_sprite[ 0 ].w = 54;
     alienogre_sprite[ 0 ].h = 54;

     alienogre_sprite[ 1 ].x = 54;
     alienogre_sprite[ 1 ].y = 0;
     alienogre_sprite[ 1 ].w = 54;
     alienogre_sprite[ 1 ].h = 54;

     alienogre_sprite[ 2 ].x = 108;
     alienogre_sprite[ 2 ].y = 0;
     alienogre_sprite[ 2 ].w = 54;
     alienogre_sprite[ 2 ].h = 54;

     alienogre_sprite[ 3 ].x = 162;
     alienogre_sprite[ 3 ].y = 0;
     alienogre_sprite[ 3 ].w = 54;
     alienogre_sprite[ 3 ].h = 54;

     alienogre_sprite[ 4 ].x = 0;
     alienogre_sprite[ 4 ].y = 54;
     alienogre_sprite[ 4 ].w = 54;
     alienogre_sprite[ 4 ].h = 54;

     alienogre_sprite[ 5 ].x = 54;
     alienogre_sprite[ 5 ].y = 54;
     alienogre_sprite[ 5 ].w = 54;
     alienogre_sprite[ 5 ].h = 54;

     alienogre_sprite[ 6 ].x = 108;
     alienogre_sprite[ 6 ].y = 54;
     alienogre_sprite[ 6 ].w = 54;
     alienogre_sprite[ 6 ].h = 54;

     alienogre_sprite[ 7 ].x = 162;
     alienogre_sprite[ 7 ].y = 54;
     alienogre_sprite[ 7 ].w = 54;
     alienogre_sprite[ 7 ].h = 54;

     alienogre_sprite[ 8 ].x = 0;
     alienogre_sprite[ 8 ].y = 108;
     alienogre_sprite[ 8 ].w = 54;
     alienogre_sprite[ 8 ].h = 54;

     alienogre_sprite[ 9 ].x = 54;
     alienogre_sprite[ 9 ].y = 108;
     alienogre_sprite[ 9 ].w = 54;
     alienogre_sprite[ 9 ].h = 54;

     alienogre_sprite[ 10 ].x = 108;
     alienogre_sprite[ 10 ].y = 108;
     alienogre_sprite[ 10 ].w = 54;
     alienogre_sprite[ 10 ].h = 54;

     alienogre_sprite[ 11 ].x = 162;
     alienogre_sprite[ 11 ].y = 108;
     alienogre_sprite[ 11 ].w = 54;
     alienogre_sprite[ 11 ].h = 54;

     alienogre_sprite[ 12 ].x = 0;
     alienogre_sprite[ 12 ].y = 162;
     alienogre_sprite[ 12 ].w = 54;
     alienogre_sprite[ 12 ].h = 54;

     alienogre_sprite[ 13 ].x = 54;
     alienogre_sprite[ 13 ].y = 162;
     alienogre_sprite[ 13 ].w = 54;
     alienogre_sprite[ 13 ].h = 54;

     alienogre_sprite[ 14 ].x = 108;
     alienogre_sprite[ 14 ].y = 162;
     alienogre_sprite[ 14 ].w = 54;
     alienogre_sprite[ 14 ].h = 54;

     alienogre_sprite[ 15 ].x = 162;
     alienogre_sprite[ 15 ].y = 162;
     alienogre_sprite[ 15 ].w = 54;
     alienogre_sprite[ 15 ].h = 54;

     /* ----- Fim sprites alien ----- */


     /* ----- Sprites alien radio----- */
     alienradio_sprite[ 0 ].x = 0;
     alienradio_sprite[ 0 ].y = 0;
     alienradio_sprite[ 0 ].w = 54;
     alienradio_sprite[ 0 ].h = 54;

     alienradio_sprite[ 1 ].x = 54;
     alienradio_sprite[ 1 ].y = 0;
     alienradio_sprite[ 1 ].w = 54;
     alienradio_sprite[ 1 ].h = 54;

     alienradio_sprite[ 2 ].x = 108;
     alienradio_sprite[ 2 ].y = 0;
     alienradio_sprite[ 2 ].w = 54;
     alienradio_sprite[ 2 ].h = 54;

     alienradio_sprite[ 3 ].x = 162;
     alienradio_sprite[ 3 ].y = 0;
     alienradio_sprite[ 3 ].w = 54;
     alienradio_sprite[ 3 ].h = 54;

     alienradio_sprite[ 4 ].x = 0;
     alienradio_sprite[ 4 ].y = 54;
     alienradio_sprite[ 4 ].w = 54;
     alienradio_sprite[ 4 ].h = 54;

     alienradio_sprite[ 5 ].x = 54;
     alienradio_sprite[ 5 ].y = 54;
     alienradio_sprite[ 5 ].w = 54;
     alienradio_sprite[ 5 ].h = 54;

     alienradio_sprite[ 6 ].x = 108;
     alienradio_sprite[ 6 ].y = 54;
     alienradio_sprite[ 6 ].w = 54;
     alienradio_sprite[ 6 ].h = 54;

     alienradio_sprite[ 7 ].x = 162;
     alienradio_sprite[ 7 ].y = 54;
     alienradio_sprite[ 7 ].w = 54;
     alienradio_sprite[ 7 ].h = 54;

     alienradio_sprite[ 8 ].x = 0;
     alienradio_sprite[ 8 ].y = 108;
     alienradio_sprite[ 8 ].w = 54;
     alienradio_sprite[ 8 ].h = 54;

     alienradio_sprite[ 9 ].x = 54;
     alienradio_sprite[ 9 ].y = 108;
     alienradio_sprite[ 9 ].w = 54;
     alienradio_sprite[ 9 ].h = 54;

     alienradio_sprite[ 10 ].x = 108;
     alienradio_sprite[ 10 ].y = 108;
     alienradio_sprite[ 10 ].w = 54;
     alienradio_sprite[ 10 ].h = 54;

     alienradio_sprite[ 11 ].x = 162;
     alienradio_sprite[ 11 ].y = 108;
     alienradio_sprite[ 11 ].w = 54;
     alienradio_sprite[ 11 ].h = 54;

     alienradio_sprite[ 12 ].x = 0;
     alienradio_sprite[ 12 ].y = 162;
     alienradio_sprite[ 12 ].w = 54;
     alienradio_sprite[ 12 ].h = 54;

     alienradio_sprite[ 13 ].x = 54;
     alienradio_sprite[ 13 ].y = 162;
     alienradio_sprite[ 13 ].w = 54;
     alienradio_sprite[ 13 ].h = 54;

     alienradio_sprite[ 14 ].x = 108;
     alienradio_sprite[ 14 ].y = 162;
     alienradio_sprite[ 14 ].w = 54;
     alienradio_sprite[ 14 ].h = 54;

     alienradio_sprite[ 15 ].x = 162;
     alienradio_sprite[ 15 ].y = 162;
     alienradio_sprite[ 15 ].w = 54;
     alienradio_sprite[ 15 ].h = 54;

     /* ----- Fim sprites alien radio----- */


     /* ----- Sprites strip dancer ----- */
     strdanc_sprite[ 0 ].x = 0;
     strdanc_sprite[ 0 ].y = 0;
     strdanc_sprite[ 0 ].w = 378;
     strdanc_sprite[ 0 ].h = 476;

     strdanc_sprite[ 1 ].x = 378;
     strdanc_sprite[ 1 ].y = 0;
     strdanc_sprite[ 1 ].w = 378;
     strdanc_sprite[ 1 ].h = 476;

     strdanc_sprite[ 2 ].x = 756;
     strdanc_sprite[ 2 ].y = 0;
     strdanc_sprite[ 2 ].w = 378;
     strdanc_sprite[ 2 ].h = 476;

     strdanc_sprite[ 3 ].x = 1134;
     strdanc_sprite[ 3 ].y = 0;
     strdanc_sprite[ 3 ].w = 378;
     strdanc_sprite[ 3 ].h = 476;

     strdanc_sprite[ 4 ].x = 1512;
     strdanc_sprite[ 4 ].y = 0;
     strdanc_sprite[ 4 ].w = 378;
     strdanc_sprite[ 4 ].h = 476;

     strdanc_sprite[ 5 ].x = 1890;
     strdanc_sprite[ 5 ].y = 0;
     strdanc_sprite[ 5 ].w = 378;
     strdanc_sprite[ 5 ].h = 476;

     /* ------- Fim sprite strip dancer ------- */

    exp_cent_pointer = &exp_sprite[18]; 
    exp_cim_pointer = &exp_sprite[25]; 
    exp_esq_pointer = &exp_sprite[23];
    exp_bai_pointer = &exp_sprite[21];  
    exp_dir_pointer = &exp_sprite[19]; 
    exp_cimfim_pointer = &exp_sprite[26]; 
    exp_esqfim_pointer = &exp_sprite[24];
    exp_baifim_pointer = &exp_sprite[22];  
    exp_dirfim_pointer = &exp_sprite[20]; 



    //11 LINHAS 17 COLUNAS
/*
  int mapa[11][17] = {
{0,3,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0},
{0,0,0,3,0,11,0,1,3,0,0,0,1,0,3,3,3},
{3,0,0,1,0,3,0,0,3,0,0,1,0,0,3,3,7},
{0,14,0,3,0,3,0,3,0,41,0,0,0,11,3,3,3},
{0,0,0,1,1,0,0,3,0,3,0,0,0,0,1,1,3},
{1,3,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
{0,3,0,1,3,0,0,1,3,0,0,3,1,1,0,0,0},
{3,17,1,1,3,3,0,14,0,1,1,3,1,1,0,3,3},
{0,3,1,1,3,0,0,0,0,0,3,3,1,1,0,3,3},
{0,3,1,1,1,1,3,3,17,1,1,1,1,1,0,0,1},
{3,3,1,3,3,3,0,0,0,0,0,0,0,0,3,3,1}
};
*/

/*
 0 - nada
 1 - bloco indestrutivel
 3 - bloco destrutivel
 11 - pk plutonio
 14 - pk vida
 17 - pk club
 41 - inimigo a
 42 - inimigo b
 43 - inimigo c
 44 - inimigo d
 50 - saída
*/
/*
  int mapa[11][17] = {
{0,0,3,0,3,0,14,0,0,3,17,3,0,3,3,0,0},
{0,1,3,1,0,1,0,1,14,1,3,1,0,1,3,1,0},
{17,3,0,0,3,11,0,3,0,3,0,0,14,3,3,0,0},
{17,1,14,1,0,1,3,1,3,1,0,1,0,1,0,1,0},
{50,0,0,0,0,0,3,0,41,0,17,0,0,3,3,3,0},
{0,1,14,1,0,1,3,1,0,1,0,1,0,1,3,1,0},
{0,0,0,0,14,3,3,0,0,0,0,3,0,0,0,0,0},
{3,1,0,1,3,1,0,1,0,1,0,1,0,1,0,1,0},
{3,0,0,3,3,3,0,0,3,0,0,0,43,0,0,0,0},
{0,1,42,1,17,1,3,1,0,1,0,1,0,1,3,1,0},
{0,3,
    */
  /*
    int mapa[11][17] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
*/


    SDL_Surface *text_pontuacao_fimfase = NULL;
    SDL_Surface *text_pontuacaototal_fimfase = NULL;
    SDL_Surface *text_vidas_fimfase = NULL;
    SDL_Surface *text_bonusvidas_fimfase = NULL;
    SDL_Surface *text_cronometro_fimfase = NULL;

    char string_pontuacao_fimfase[50];
    char string_pontuacaototal_fimfase[50];
    char string_vidas_fimfase[20];
    char string_bonusvidas_fimfase[20];
    char string_cronometro_fimfase[50];


    SDL_Event eventwingame;
    SDL_Event eventinstrucoes;
    SDL_Event eventrecordes;
    SDL_Event eventperdeujogo;
    SDL_Event eventfimfase;
    SDL_Event eventpause;
    SDL_Event eventmenu;
    SDL_Event event;
    int rodador_jogokup = 0;
    int contin_passoufase = 0;
    int contin_recordes = 0;
    int contin_instrucoes = 0;
    int contin_wingame = 0;
    int contin_perdeujogo = 0;
    int contin_pause = 0;

    int mapa[11][17];
    FILE* leitorfase;
    FILE* continfasesave;
    FILE* continfasepont;

    int faseatual = 1;
    int val_matriz = 0;
    //int ultfase = fscanf(leitorfase,"%d", &val_matriz);
    int ultfase = 10;
    int passou_fase = 1;
    int horainicfase = SDL_GetTicks();
    int radioatividade = 0;
    int tempo_stripdance = 0;
    int cont_spritestrdanc = 0;

    SDL_Rect stripdancer;
    SDL_Rect *strdanc_pointer;

    stripdancer.x = 15;
    stripdancer.y = 110;

    char nomearqfase[15];

    int pontuacaototaljogador = 0;

    int opcaomenu = 1, opcaofimfase = 1, opcaoperdeujogo = 1, opcaopause = 1, continuar = 0, recordes = 0, linha = 0 ;

    int perdeu_jogo = 0;

    int sairjogo = 0;
    int jogorodando = 1;
    int faserodando = 1;
    int fimjogo = 0;
    int wingame = 0;
    int instrucoes = 0;
    int emorreu = 0;
    int fimtempo = 0;
    int vidas = 3;
    int pontuacao = 0;
    int raiobomb = 1;
    int tempototal_fase = 300;
    
         int rodador_creditos = 1;
      int rodador_fundopreto = 1;
      int tempo_credidos = SDL_GetTicks();
      int tempo_fundopreto;

      while(rodador_creditos == 1){
      apply_surface(0,0,fundocreditos,screen, NULL);
      if(SDL_GetTicks() - tempo_credidos > 3000){
      rodador_creditos = 0;
      }
      SDL_Flip(screen);
      }
      tempo_fundopreto = SDL_GetTicks();
      while(rodador_fundopreto == 1){
      apply_surface(0,0,fundopreto,screen, NULL);
      if(SDL_GetTicks() - tempo_fundopreto > 500){
      rodador_fundopreto = 0;
      }
      SDL_Flip(screen);
      }

/*---------------------------------- Main Loop ------------------------------*/
    opcaomenu = 1;

    Mix_PlayMusic(theme, -1 );

    while(sairjogo == 0)
    {    
    Mix_VolumeMusic(50);
    Mix_ResumeMusic();
    perdeu_jogo = 0;
    contin_perdeujogo = 0;

    apply_surface(0,0,fundomenu,screen, NULL);

        while (SDL_PollEvent(&eventmenu))
        {
            // check for messages
            switch (eventmenu.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                sairjogo = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // SE A TECLA PRESSIONADA FOR ESC

                    if (eventmenu.key.keysym.sym == SDLK_ESCAPE){
                        sairjogo = 1;
                    break;
                    }

                    if (eventmenu.key.keysym.sym == SDLK_UP){
                        opcaomenu--;
                        if(opcaomenu<1)
                            opcaomenu = 1;
                        break;
                    }

                    if (eventmenu.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                        
                        opcaomenu++;
                        if(opcaomenu>5)
                            opcaomenu = 5;
                        break;
                    }


                    if (eventmenu.key.keysym.sym == SDLK_RETURN){
                       if(opcaomenu == 1){
                            jogorodando = 0;
                            faserodando = 0;
                            passou_fase = 0;
                            faseatual = 1;
                            perdeu_jogo = 0;
                            wingame = 0;
                            contin_perdeujogo = 0;
                            pontuacaototaljogador = 0;
                        }
                        else if(opcaomenu == 2){
                            continfasesave = fopen("saves/fasesalva.dat" ,"r");
                            fread(&faseatual, sizeof(int), 1, continfasesave);
                            fclose(continfasesave);
                            continfasepont = fopen("saves/pontuacaosalva.dat" ,"r");
                            fread(&pontuacaototaljogador, sizeof(int), 1, continfasepont);
                            fclose(continfasepont);
                            jogorodando = 0;
                            faserodando = 0;
                            passou_fase = 0;

                        }
                        else if(opcaomenu == 3)
                            instrucoes = 1;
                        else if(opcaomenu == 4)
                            recordes = 1;
                        else if (opcaomenu==5)
                            sairjogo = 1;
                        break;

                    }
                }
            case SDL_KEYUP:
                {
                    
                }


            } // end switch
        }
for(linha=0;linha<5;linha++)
{
    if(opcaomenu==1)
        apply_surface(662,278,seletor,screen, NULL);
    else if(opcaomenu==2)
        apply_surface(670,329,seletor,screen, NULL);
    else if(opcaomenu==3)
        apply_surface(690,380,seletor,screen, NULL);
    else if(opcaomenu==4)
        apply_surface(715,429,seletor,screen, NULL);
    else if(opcaomenu==5)
        apply_surface(842,478,seletor,screen, NULL);

}
SDL_Flip(screen);


while(jogorodando == 0 && faseatual <= ultfase){
     Mix_VolumeMusic(10);
     //Mix_PauseMusic();
     if(passou_fase == 1){
        faseatual += 1;
        passou_fase = 0;
        if(faseatual > ultfase){
            faserodando = 1;
            jogorodando = 1;
            wingame = 1;
        }
    }

    continfasesave = fopen("saves/fasesalva.dat" ,"w");
    fwrite(&faseatual, sizeof(int), 1, continfasesave);
    fclose(continfasesave);
    continfasepont = fopen("saves/pontuacaosalva.dat" ,"w");
    fwrite(&pontuacaototaljogador, sizeof(int), 1, continfasepont);
    fclose(continfasepont);

    horainicfase = SDL_GetTicks();
    raiobomb = 1;
    vidas = 3;
    pontuacao = 0;
    colet_clubcard = 0;

    sprintf(nomearqfase, "fases/fase%d.txt", faseatual);
    puts(nomearqfase);
    leitorfase = fopen(nomearqfase ,"r");
    inimigoa_morto = 0;
    inimigob_morto = 0;
    inimigoc_morto = 0;
    inimigod_morto = 0;
        if(faseatual <= ultfase){
            for(j=0;j<11;j++)
            {
                for(i=0;i<17;i++)
                {
                    fscanf(leitorfase,"%d", &val_matriz);
                    mapa[j][i] = val_matriz;
                }
            }
            fclose(leitorfase);
            conf_kup = 0;
            inc_my = 0;
            inc_mx = 0;

            xAtual = 0;
            yAtual = 0;
            personagem.y = 119 + (xAtual*54);
            personagem.x = 53 + (xAtual*54);

            exist_inia = 0;
            exist_inib = 0;
            exist_inic = 0;
            exist_inid = 0;

            for(i=0;i<17;i++){
                for(j=0;j<11;j++){
                    if(mapa[j][i] == 41){ 
                        xInimigoa = i;
                        yInimigoa = j;
                        mapa[j][i] = 0;
                        exist_inia = 1;
                    }
                    if(mapa[j][i] == 42){ 
                        xInimigob = i;
                        yInimigob = j;
                        mapa[j][i] = 0;
                        exist_inib = 1;
                    }
                    if(mapa[j][i] == 43){
                        xInimigoc = i;
                        yInimigoc = j;
                        mapa[j][i] = 0;
                        exist_inic = 1;
                    }
                    if(mapa[j][i] == 44){
                        xInimigod = i;
                        yInimigod = j;
                        mapa[j][i] = 0;
                        exist_inid = 1;
                    }
                }
            }
            inimigoa.y = 119 + (yInimigoa*54);
            inimigoa.x = 53 + (xInimigoa*54);

            inimigob.y = 119 + (yInimigob*54);
            inimigob.x = 53 + (xInimigob*54);

            inimigoc.y = 119 + (yInimigoc*54);
            inimigoc.x = 53 + (xInimigoc*54);

            inimigod.y = 119 + (yInimigod*54);
            inimigod.x = 53 + (xInimigod*54);

        } else{
            fimjogo = 1;
        }



    while(faserodando == 0 && passou_fase == 0){
        
    if(vidas <= 0){
        faserodando = 1;
        perdeu_jogo = 1;
    }

    /* ------- Movimentacao do Duke Nukem ------- */

    if(!(inc_my != 0 && inc_mx != 0)){
        if(rodador_movdn == 1){

            if(mapa[yAtual+inc_my][xAtual] != 50 && mapa[yAtual+inc_my][xAtual] != 1 && mapa[yAtual+inc_my][xAtual] != 4 && mapa[yAtual+inc_my][xAtual] != 11 && mapa[yAtual+inc_my][xAtual] != 12 && mapa[yAtual+inc_my][xAtual] != 14 && mapa[yAtual+inc_my][xAtual] != 15 && mapa[yAtual+inc_my][xAtual] != 17 && mapa[yAtual+inc_my][xAtual] != 18 && mapa[yAtual+inc_my][xAtual] != 3 && mapa[yAtual+inc_my][xAtual] != 5 && yAtual+inc_my >= 0 && yAtual+inc_my <= 10 && movimenta_y[0] != 1){
                if(mapa[yAtual+inc_my][xAtual] == 13){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    raiobomb += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 16){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    vidas += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 19){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    pontuacao += 200;
                    colet_clubcard += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 52){ 
                    passou_fase = 1;
                }
                yAtual += inc_my;
                if(inc_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = inc_my;
                    rodador_primeiro_passo_mov = 1;
                }
            }
            if(mapa[yAtual][xAtual+inc_mx] != 50 && mapa[yAtual][xAtual+inc_mx] != 1 && mapa[yAtual][xAtual+inc_mx] != 4 && mapa[yAtual][xAtual+inc_mx] != 11 && mapa[yAtual][xAtual+inc_mx] != 12 && mapa[yAtual][xAtual+inc_mx] != 14 && mapa[yAtual][xAtual+inc_mx] != 15 && mapa[yAtual][xAtual+inc_mx] != 17 && mapa[yAtual][xAtual+inc_mx] != 18 && mapa[yAtual][xAtual+inc_mx] != 3 && mapa[yAtual][xAtual+inc_mx] != 5 && xAtual+inc_mx >= 0 && xAtual+inc_mx <= 16 && movimenta_x[0] != 1){
                if(mapa[yAtual][xAtual+inc_mx] == 13){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    raiobomb += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 16){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    vidas += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 19){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    pontuacao += 200;
                    colet_clubcard += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 52){ 
                    passou_fase = 1;
                }
                xAtual += inc_mx;
                if(inc_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = inc_mx;
                    rodador_primeiro_passo_mov = 1;
                }
            }

            rodador_movdn = 0;
            tempo_passo = SDL_GetTicks();

        } else if(SDL_GetTicks() - tempo_passo > 500){

            if(mapa[yAtual+inc_my][xAtual] != 50 && mapa[yAtual+inc_my][xAtual] != 1 && mapa[yAtual+inc_my][xAtual] != 4 && mapa[yAtual+inc_my][xAtual] != 11 && mapa[yAtual+inc_my][xAtual] != 12 && mapa[yAtual+inc_my][xAtual] != 14 && mapa[yAtual+inc_my][xAtual] != 15 && mapa[yAtual+inc_my][xAtual] != 17 && mapa[yAtual+inc_my][xAtual] != 18 && mapa[yAtual+inc_my][xAtual] != 3 && mapa[yAtual+inc_my][xAtual] != 5 && yAtual+inc_my >= 0 && yAtual+inc_my <= 10){
                if(mapa[yAtual+inc_my][xAtual] == 13){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    raiobomb += 1;
                    
                } else if(mapa[yAtual+inc_my][xAtual] == 16){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    vidas += 1;
                    
                } else if(mapa[yAtual+inc_my][xAtual] == 19){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    pontuacao += 200;
                    colet_clubcard += 1;
                     
                } else if(mapa[yAtual+inc_my][xAtual] == 52){
                    passou_fase = 1;
                    
                }
                yAtual += inc_my;
                if(inc_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = inc_my;
                    rodador_primeiro_passo_mov = 1;
                }
            }
            if(mapa[yAtual][xAtual+inc_mx] != 50 && mapa[yAtual][xAtual+inc_mx] != 1 && mapa[yAtual][xAtual+inc_mx] != 4 && mapa[yAtual][xAtual+inc_mx] != 11 && mapa[yAtual][xAtual+inc_mx] != 12 && mapa[yAtual][xAtual+inc_mx] != 14 && mapa[yAtual][xAtual+inc_mx] != 15 && mapa[yAtual][xAtual+inc_mx] != 17 && mapa[yAtual][xAtual+inc_mx] != 18 && mapa[yAtual][xAtual+inc_mx] != 3 && mapa[yAtual][xAtual+inc_mx] != 5 && xAtual+inc_mx >= 0 && xAtual+inc_mx <= 16){
                if(mapa[yAtual][xAtual+inc_mx] == 13){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    raiobomb += 1;
                    
                } else if(mapa[yAtual][xAtual+inc_mx] == 16){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    vidas += 1;
                    
                } else if(mapa[yAtual][xAtual+inc_mx] == 19){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    pontuacao += 200;
                    colet_clubcard += 1;
                    
                } else if(mapa[yAtual][xAtual+inc_mx] == 52){
                    passou_fase = 1;
                    
                }
                xAtual += inc_mx;
                if(inc_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = inc_mx;
                    rodador_primeiro_passo_mov = 1;
                }
            }
            tempo_passo = SDL_GetTicks();
        }
    }
    if(movimenta_y[0] == 0 && movimenta_x[0] == 0){
        tempo_passo_mov = SDL_GetTicks();
    } else if(rodador_primeiro_passo_mov == 1){
        tempo_passo_mov = -125;
        rodador_primeiro_passo_mov = 0;
    }
    if(SDL_GetTicks() - tempo_passo_mov > 124){
        if(movimenta_y[0] == 1){
            if(frac_passoy != 4){
                personagem.y = 119 + ((yAtual-movimenta_y[1])*54) + movimenta_y[1]*frac_passoy*13;
                dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                mudou_bloco = 0;
                if(frac_passoy == 3){
                    mudou_bloco = 1;
                }
                frac_passoy += 1;
            } else{
                dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                frac_passoy = 1;
                personagem.y = 119 + ((yAtual)*54);
                movimenta_y[0] = 0;
            }
        }

        if(movimenta_x[0] == 1){
            if(frac_passox != 4){
                personagem.x = 53 + ((xAtual-movimenta_x[1])*54) + movimenta_x[1]*frac_passox*13;
                dn_pointer = &dn_sprite[ult_sent+frac_passox-1];
                mudou_bloco = 0;
                if(frac_passox == 3){
                    mudou_bloco = 1;
                }
                frac_passox += 1;
            } else{
                dn_pointer = &dn_sprite[ult_sent+frac_passox-1];
                frac_passox = 1;
                personagem.x = 53 + ((xAtual)*54);
                movimenta_x[0] = 0;
            }
        }
        tempo_passo_mov = SDL_GetTicks();
    }

    /* ------- Fim movimentacao do Duke Nukem ------- */




    /* ------- Movimentacao do inimigo A ------- */
    if(exist_inia == 1){
        if(inimigoa_morto == 0){
            if(SDL_GetTicks() - tempo_passoinia > 1000){
                escolhe_movinia = rand()%8;
                decidido_movinia = 0; 
                cont_decmovinia = 0;
                while(decidido_movinia != 1 && cont_decmovinia < 5){
                    if(escolhe_movinia == 0){
                        if(mapa[yInimigoa-1][xInimigoa] != 1 && mapa[yInimigoa-1][xInimigoa] != 4 && mapa[yInimigoa-1][xInimigoa] != 11 && mapa[yInimigoa-1][xInimigoa] != 12 && mapa[yInimigoa-1][xInimigoa] != 14 && mapa[yInimigoa-1][xInimigoa] != 15 && mapa[yInimigoa-1][xInimigoa] != 17 && mapa[yInimigoa-1][xInimigoa] != 18 && mapa[yInimigoa-1][xInimigoa] != 3 && mapa[yInimigoa-1][xInimigoa] != 5 && yInimigoa-1 >= 0){
                            decidido_movinia = 1;
                            yInimigoa = yInimigoa - 1;
                            ult_sentinia = 0;
                        } else{
                            while(escolhe_movinia == 0){
                                escolhe_movinia = rand()%4;
                            }
                            cont_decmovinia += 1;
                            decidido_movinia = 0;
                        }
                    } else if(escolhe_movinia == 1){
                        if(mapa[yInimigoa+1][xInimigoa] != 1 && mapa[yInimigoa+1][xInimigoa] != 4 && mapa[yInimigoa+1][xInimigoa] != 11 && mapa[yInimigoa+1][xInimigoa] != 12 && mapa[yInimigoa+1][xInimigoa] != 14 && mapa[yInimigoa+1][xInimigoa] != 15 && mapa[yInimigoa+1][xInimigoa] != 17 && mapa[yInimigoa+1][xInimigoa] != 18 && mapa[yInimigoa+1][xInimigoa] != 3 && mapa[yInimigoa+1][xInimigoa] != 5 && yInimigoa+1 <= 10){
                            decidido_movinia = 1;
                            yInimigoa = yInimigoa + 1;
                            ult_sentinia = 1;
                        } else{
                            while(escolhe_movinia == 1){
                                escolhe_movinia = rand()%4;
                            }
                            cont_decmovinia += 1;
                            decidido_movinia = 0;
                        }
                    } else if(escolhe_movinia == 2){
                        if(mapa[yInimigoa][xInimigoa-1] != 1 && mapa[yInimigoa][xInimigoa-1] != 4 && mapa[yInimigoa][xInimigoa-1] != 11 && mapa[yInimigoa][xInimigoa-1] != 12 && mapa[yInimigoa][xInimigoa-1] != 14 && mapa[yInimigoa][xInimigoa-1] != 15 && mapa[yInimigoa][xInimigoa-1] != 17 && mapa[yInimigoa][xInimigoa-1] != 18 && mapa[yInimigoa][xInimigoa-1] != 3 && mapa[yInimigoa][xInimigoa-1] != 5 && xInimigoa-1 >= 0){
                            decidido_movinia = 1;
                            xInimigoa = xInimigoa - 1;
                            ult_sentinia = 2;
                        } else{
                            while(escolhe_movinia == 2){
                                escolhe_movinia = rand()%4;                     
                            }
                            cont_decmovinia += 1;
                            decidido_movinia = 0;
                        }
                    } else if(escolhe_movinia == 3){
                        if(mapa[yInimigoa][xInimigoa+1] != 1 && mapa[yInimigoa][xInimigoa+1] != 4 && mapa[yInimigoa][xInimigoa+1] != 11 && mapa[yInimigoa][xInimigoa+1] != 12 && mapa[yInimigoa][xInimigoa+1] != 14 && mapa[yInimigoa][xInimigoa+1] != 15 && mapa[yInimigoa][xInimigoa+1] != 17 && mapa[yInimigoa][xInimigoa+1] != 18 && mapa[yInimigoa][xInimigoa+1] != 3 && mapa[yInimigoa][xInimigoa+1] != 5 && xInimigoa+1 <= 16){
                            decidido_movinia = 1;
                            xInimigoa = xInimigoa + 1;
                            ult_sentinia = 3;
                        } else{
                            while(escolhe_movinia == 3){
                                escolhe_movinia = rand()%4;
                            }
                            cont_decmovinia += 1;
                            decidido_movinia = 0;
                        }
                    } else{
                        if(ult_sentinia == 0 && mapa[yInimigoa-1][xInimigoa] != 1 && mapa[yInimigoa-1][xInimigoa] != 4 && mapa[yInimigoa-1][xInimigoa] != 11 && mapa[yInimigoa-1][xInimigoa] != 12 && mapa[yInimigoa-1][xInimigoa] != 14 && mapa[yInimigoa-1][xInimigoa] != 15 && mapa[yInimigoa-1][xInimigoa] != 17 && mapa[yInimigoa-1][xInimigoa] != 18 && mapa[yInimigoa-1][xInimigoa] != 3 && mapa[yInimigoa-1][xInimigoa] != 5 && yInimigoa-1 >= 0){
                            yInimigoa = yInimigoa - 1;
                            decidido_movinia = 1;
                        } else if(ult_sentinia == 1 && mapa[yInimigoa+1][xInimigoa] != 1 && mapa[yInimigoa+1][xInimigoa] != 4 && mapa[yInimigoa+1][xInimigoa] != 11 && mapa[yInimigoa+1][xInimigoa] != 12 && mapa[yInimigoa+1][xInimigoa] != 14 && mapa[yInimigoa+1][xInimigoa] != 15 && mapa[yInimigoa+1][xInimigoa] != 17 && mapa[yInimigoa+1][xInimigoa] != 18 && mapa[yInimigoa+1][xInimigoa] != 3 && mapa[yInimigoa+1][xInimigoa] != 5 && yInimigoa+1 <= 10){
                            yInimigoa = yInimigoa + 1;
                            decidido_movinia = 1;
                        } else if(ult_sentinia == 2 && mapa[yInimigoa][xInimigoa-1] != 1 && mapa[yInimigoa][xInimigoa-1] != 4 && mapa[yInimigoa][xInimigoa-1] != 11 && mapa[yInimigoa][xInimigoa-1] != 12 && mapa[yInimigoa][xInimigoa-1] != 14 && mapa[yInimigoa][xInimigoa-1] != 15 && mapa[yInimigoa][xInimigoa-1] != 17 && mapa[yInimigoa][xInimigoa-1] != 18 && mapa[yInimigoa][xInimigoa-1] != 3 && mapa[yInimigoa][xInimigoa-1] != 5 && xInimigoa-1 >= 0){
                            xInimigoa = xInimigoa - 1;
                            decidido_movinia = 1;
                        } else if(ult_sentinia == 3 && mapa[yInimigoa][xInimigoa+1] != 1 && mapa[yInimigoa][xInimigoa+1] != 4 && mapa[yInimigoa][xInimigoa+1] != 11 && mapa[yInimigoa][xInimigoa+1] != 12 && mapa[yInimigoa][xInimigoa+1] != 14 && mapa[yInimigoa][xInimigoa+1] != 15 && mapa[yInimigoa][xInimigoa+1] != 17 && mapa[yInimigoa][xInimigoa+1] != 18 && mapa[yInimigoa][xInimigoa+1] != 3 && mapa[yInimigoa][xInimigoa+1] != 5 && xInimigoa+1 <= 16){
                            xInimigoa = xInimigoa + 1;
                            decidido_movinia = 1;
                        } else{
                            while(escolhe_movinia != 0 && escolhe_movinia != 1 && escolhe_movinia != 2 && escolhe_movinia != 3){
                                escolhe_movinia = rand()%4;
                            }
                            cont_decmovinia += 1;
                            decidido_movinia = 0;
                        }
                    }
                }

                rodador_animinia = 1;
                if(cont_decmovinia >= 5){
                    rodador_animinia = 0;
                }
                tempo_passoinia = SDL_GetTicks();
                rodador_primeiro_passo_movinia = 1;
            }

            if(rodador_animinia == 0){
                tempo_passo_movinia = SDL_GetTicks();
            } else if(rodador_primeiro_passo_movinia == 1){
                tempo_passo_movinia = -400;
                rodador_primeiro_passo_movinia = 0;
            }
            if(SDL_GetTicks() - tempo_passo_movinia > 249){
                if(ult_sentinia == 0){
                    if(frac_passoinia != 4){
                        inimigoa.y = 119 + ((yInimigoa+1)*54) - frac_passoinia*13;
                        inia_pointer = &alienogre_sprite[frac_passoinia-1];
                        frac_passoinia += 1;
                    } else{
                        inia_pointer = &alienogre_sprite[frac_passoinia-1];
                        frac_passoinia = 1;
                        inimigoa.y = 119 + (yInimigoa*54);
                        inimigoa.x = 53 + (xInimigoa*54);
                        rodador_animinia = 0;
                    }
                } else if(ult_sentinia == 1){
                    if(frac_passoinia != 4){
                        inimigoa.y = 119 + ((yInimigoa-1)*54) + frac_passoinia*13;
                        inimigoa.x = inimigoa.x;
                        inia_pointer = &alienogre_sprite[7+frac_passoinia];
                        frac_passoinia += 1;
                    } else{
                        inia_pointer = &alienogre_sprite[7+frac_passoinia];
                        frac_passoinia = 1;
                        inimigoa.y = 119 + (yInimigoa*54);
                        inimigoa.x = 53 + (xInimigoa*54);
                        rodador_animinia = 0;
                    }
                } else if(ult_sentinia == 2){
                    if(frac_passoinia != 4){
                        inimigoa.x = 53 + ((xInimigoa+1)*54) - frac_passoinia*13;
                        inia_pointer = &alienogre_sprite[11+frac_passoinia];
                        frac_passoinia += 1;
                    } else{
                        dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                        inia_pointer = &alienogre_sprite[11+frac_passoinia];
                        frac_passoinia = 1;
                        inimigoa.x = 53 + (xInimigoa*54);
                        inimigoa.y = 119 + (yInimigoa*54);
                        rodador_animinia = 0;
                    }
                } else if(ult_sentinia == 3){
                    if(frac_passoinia != 4){
                        inimigoa.x = 53 + ((xInimigoa-1)*54) + frac_passoinia*13;
                        inia_pointer = &alienogre_sprite[3+frac_passoinia];
                        frac_passoinia += 1;
                    } else{
                        inia_pointer = &alienogre_sprite[3+frac_passoinia];
                        frac_passoinia = 1;
                        inimigoa.x = 53 + (xInimigoa*54);
                        inimigoa.y = 119 + (yInimigoa*54);
                        rodador_animinia = 0;
                    }
                }
                tempo_passo_movinia = SDL_GetTicks();
            }
        }
    }
    /* ------- Fim movimentacao do inimigo A ------- */



    /* ------- Movimentacao do inimigo B ------- */
    if(exist_inib == 1){
        if(inimigob_morto == 0){
            if(SDL_GetTicks() - tempo_passoinib > 1000){
                escolhe_movinib = rand()%8;
                decidido_movinib = 0;
                cont_decmovinib = 0;
                while(decidido_movinib != 1 && cont_decmovinib < 5){
                    if(escolhe_movinib == 0){
                        if(mapa[yInimigob-1][xInimigob] != 50 && mapa[yInimigob-1][xInimigob] != 1 && mapa[yInimigob-1][xInimigob] != 4 && mapa[yInimigob-1][xInimigob] != 11 && mapa[yInimigob-1][xInimigob] != 12 && mapa[yInimigob-1][xInimigob] != 14 && mapa[yInimigob-1][xInimigob] != 15 && mapa[yInimigob-1][xInimigob] != 17 && mapa[yInimigob-1][xInimigob] != 18 && mapa[yInimigob-1][xInimigob] != 3 && mapa[yInimigob-1][xInimigob] != 5 && yInimigob-1 >= 0){
                            decidido_movinib = 1;
                            yInimigob = yInimigob - 1;
                            ult_sentinib = 0;
                        } else{
                            while(escolhe_movinib == 0){
                                escolhe_movinib = rand()%4;                         
                            }
                            cont_decmovinib += 1;
                            decidido_movinib = 0;
                        }
                    } else if(escolhe_movinib == 1){
                        if(mapa[yInimigob+1][xInimigob] != 50 && mapa[yInimigob+1][xInimigob] != 1 && mapa[yInimigob+1][xInimigob] != 4 && mapa[yInimigob+1][xInimigob] != 11 && mapa[yInimigob+1][xInimigob] != 12 && mapa[yInimigob+1][xInimigob] != 14 && mapa[yInimigob+1][xInimigob] != 15 && mapa[yInimigob+1][xInimigob] != 17 && mapa[yInimigob+1][xInimigob] != 18 && mapa[yInimigob+1][xInimigob] != 3 && mapa[yInimigob+1][xInimigob] != 5 && yInimigob+1 <= 10){
                            decidido_movinib = 1;
                            yInimigob = yInimigob + 1;
                            ult_sentinib = 1;
                        } else{
                            while(escolhe_movinib == 1){
                                escolhe_movinib = rand()%4;                         
                            }
                            cont_decmovinib += 1;
                            decidido_movinib = 0;
                        }
                    } else if(escolhe_movinib == 2){
                        if(mapa[yInimigob][xInimigob-1] != 50 && mapa[yInimigob][xInimigob-1] != 1 && mapa[yInimigob][xInimigob-1] != 4 && mapa[yInimigob][xInimigob-1] != 11 && mapa[yInimigob][xInimigob-1] != 12 && mapa[yInimigob][xInimigob-1] != 14 && mapa[yInimigob][xInimigob-1] != 15 && mapa[yInimigob][xInimigob-1] != 17 && mapa[yInimigob][xInimigob-1] != 18 && mapa[yInimigob][xInimigob-1] != 3 && mapa[yInimigob][xInimigob-1] != 5 && xInimigob-1 >= 0){
                            decidido_movinib = 1;
                            xInimigob = xInimigob - 1;
                            ult_sentinib = 2;
                        } else{
                            while(escolhe_movinib == 2){
                                escolhe_movinib = rand()%4;                         
                            }
                            cont_decmovinib += 1;
                            decidido_movinib = 0;
                        }
                    } else if(escolhe_movinib == 3){
                        if(mapa[yInimigob][xInimigob+1] != 50 && mapa[yInimigob][xInimigob+1] != 1 && mapa[yInimigob][xInimigob+1] != 4 && mapa[yInimigob][xInimigob+1] != 11 && mapa[yInimigob][xInimigob+1] != 12 && mapa[yInimigob][xInimigob+1] != 14 && mapa[yInimigob][xInimigob+1] != 15 && mapa[yInimigob][xInimigob+1] != 17 && mapa[yInimigob][xInimigob+1] != 18 && mapa[yInimigob][xInimigob+1] != 3 && mapa[yInimigob][xInimigob+1] != 5 && xInimigob+1 <= 16){
                            decidido_movinib = 1;
                            xInimigob = xInimigob + 1;
                            ult_sentinib = 3;
                        } else{
                            while(escolhe_movinib == 3){
                                escolhe_movinib = rand()%4;                         
                            }
                            cont_decmovinib += 1;
                            decidido_movinib = 0;
                        }
                    } else{
                        if(ult_sentinib == 0 && mapa[yInimigob-1][xInimigob] != 1 && mapa[yInimigob-1][xInimigob] != 50 && mapa[yInimigob-1][xInimigob] != 4 && mapa[yInimigob-1][xInimigob] != 11 && mapa[yInimigob-1][xInimigob] != 12 && mapa[yInimigob-1][xInimigob] != 14 && mapa[yInimigob-1][xInimigob] != 15 && mapa[yInimigob-1][xInimigob] != 17 && mapa[yInimigob-1][xInimigob] != 18 && mapa[yInimigob-1][xInimigob] != 3 && mapa[yInimigob-1][xInimigob] != 5 && yInimigob-1 >= 0){
                            yInimigob = yInimigob - 1;
                            decidido_movinib = 1;
                        } else if(ult_sentinib == 1 && mapa[yInimigob+1][xInimigob] != 1 && mapa[yInimigob+1][xInimigob] != 50 && mapa[yInimigob+1][xInimigob] != 4 && mapa[yInimigob+1][xInimigob] != 11 && mapa[yInimigob+1][xInimigob] != 12 && mapa[yInimigob+1][xInimigob] != 14 && mapa[yInimigob+1][xInimigob] != 15 && mapa[yInimigob+1][xInimigob] != 17 && mapa[yInimigob+1][xInimigob] != 18 && mapa[yInimigob+1][xInimigob] != 3 && mapa[yInimigob+1][xInimigob] != 5 && yInimigob+1 <= 10){
                            yInimigob = yInimigob + 1;
                            decidido_movinib = 1;
                        } else if(ult_sentinib == 2 && mapa[yInimigob][xInimigob-1] != 1 && mapa[yInimigob][xInimigob-1] != 50 && mapa[yInimigob][xInimigob-1] != 4 && mapa[yInimigob][xInimigob-1] != 11 && mapa[yInimigob][xInimigob-1] != 12 && mapa[yInimigob][xInimigob-1] != 14 && mapa[yInimigob][xInimigob-1] != 15 && mapa[yInimigob][xInimigob-1] != 17 && mapa[yInimigob][xInimigob-1] != 18 && mapa[yInimigob][xInimigob-1] != 3 && mapa[yInimigob][xInimigob-1] != 5 && xInimigob-1 >= 0){
                            xInimigob = xInimigob - 1;
                            decidido_movinib = 1;
                        } else if(ult_sentinib == 3 && mapa[yInimigob][xInimigob+1] != 1 && mapa[yInimigob][xInimigob+1] != 50 && mapa[yInimigob][xInimigob+1] != 4 && mapa[yInimigob][xInimigob+1] != 11 && mapa[yInimigob][xInimigob+1] != 12 && mapa[yInimigob][xInimigob+1] != 14 && mapa[yInimigob][xInimigob+1] != 15 && mapa[yInimigob][xInimigob+1] != 17 && mapa[yInimigob][xInimigob+1] != 18 && mapa[yInimigob][xInimigob+1] != 3 && mapa[yInimigob][xInimigob+1] != 5 && xInimigob+1 <= 16){
                            xInimigob = xInimigob + 1;
                            decidido_movinib = 1;
                        } else{
                            while(escolhe_movinib != 0 && escolhe_movinib != 1 && escolhe_movinib != 2 && escolhe_movinib != 3){
                                escolhe_movinib = rand()%4;
                            }
                            cont_decmovinib += 1;
                            decidido_movinib = 0;
                        }
                    }
                }


                rodador_animinib = 1;
                if(cont_decmovinib >= 5){
                    rodador_animinib = 0;
                }
                tempo_passoinib = SDL_GetTicks();
                rodador_primeiro_passo_movinib = 1;
            }

            if(rodador_animinib == 0){
                tempo_passo_movinib = SDL_GetTicks();
            } else if(rodador_primeiro_passo_movinib == 1){
                tempo_passo_movinib = -400;
                rodador_primeiro_passo_movinib = 0;
            }
            if(SDL_GetTicks() - tempo_passo_movinib > 249){
                if(ult_sentinib == 0){
                    if(frac_passoinib != 4){
                        inimigob.y = 119 + ((yInimigob+1)*54) - frac_passoinib*13;
                        inib_pointer = &alienogre_sprite[frac_passoinib-1];
                        frac_passoinib += 1;
                    } else{
                        inib_pointer = &alienogre_sprite[frac_passoinib-1];
                        frac_passoinib = 1;
                        inimigob.y = 119 + (yInimigob*54);
                        inimigob.x = 53 + (xInimigob*54);
                        rodador_animinib = 0;
                    }
                } else if(ult_sentinib == 1){
                    if(frac_passoinib != 4){
                        inimigob.y = 119 + ((yInimigob-1)*54) + frac_passoinib*13;
                        inimigob.x = inimigob.x;
                        inib_pointer = &alienogre_sprite[7+frac_passoinib];
                        frac_passoinib += 1;
                    } else{
                        inib_pointer = &alienogre_sprite[7+frac_passoinib];
                        frac_passoinib = 1;
                        inimigob.y = 119 + (yInimigob*54);
                        inimigob.x = 53 + (xInimigob*54);
                        rodador_animinib = 0;
                    }
                } else if(ult_sentinib == 2){
                    if(frac_passoinib != 4){
                        inimigob.x = 53 + ((xInimigob+1)*54) - frac_passoinib*13;
                        inib_pointer = &alienogre_sprite[11+frac_passoinib];
                        frac_passoinib += 1;
                    } else{
                        dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                        inib_pointer = &alienogre_sprite[11+frac_passoinib];
                        frac_passoinib = 1;
                        inimigob.x = 53 + (xInimigob*54);
                        inimigob.y = 119 + (yInimigob*54);
                        rodador_animinib = 0;
                    }
                } else if(ult_sentinib == 3){
                    if(frac_passoinib != 4){
                        inimigob.x = 53 + ((xInimigob-1)*54) + frac_passoinib*13;
                        inib_pointer = &alienogre_sprite[3+frac_passoinib];
                        frac_passoinib += 1;
                    } else{
                        inib_pointer = &alienogre_sprite[3+frac_passoinib];
                        frac_passoinib = 1;
                        inimigob.x = 53 + (xInimigob*54);
                        inimigob.y = 119 + (yInimigob*54);
                        rodador_animinib = 0;
                    }
                }
                tempo_passo_movinib = SDL_GetTicks();
            }
        }
    }
    /* ------- Fim movimentacao do inimigo B ------- */


    /* ------- Movimentacao do inimigo C ------- */
    if(exist_inic == 1){
        if(inimigoc_morto == 0){
            if(SDL_GetTicks() - tempo_passoinic > 600){
                escolhe_movinic = rand()%8;
                decidido_movinic = 0;
                cont_decmovinic = 0;
                while(decidido_movinic != 1 && cont_decmovinic < 5){
                    if(escolhe_movinic == 0){
                        if(mapa[yInimigoc-1][xInimigoc] != 1 && mapa[yInimigoc-1][xInimigoc] != 50 && mapa[yInimigoc-1][xInimigoc] != 4 && mapa[yInimigoc-1][xInimigoc] != 11 && mapa[yInimigoc-1][xInimigoc] != 12 && mapa[yInimigoc-1][xInimigoc] != 14 && mapa[yInimigoc-1][xInimigoc] != 15 && mapa[yInimigoc-1][xInimigoc] != 17 && mapa[yInimigoc-1][xInimigoc] != 18 && mapa[yInimigoc-1][xInimigoc] != 3 && mapa[yInimigoc-1][xInimigoc] != 5 && yInimigoc-1 >= 0){
                            decidido_movinic = 1;
                            yInimigoc = yInimigoc - 1;
                            ult_sentinic = 0;
                        } else{
                            while(escolhe_movinic == 0){
                                escolhe_movinic = rand()%4;                         
                            }
                            cont_decmovinic += 1;
                            decidido_movinic = 0;
                        }
                    } else if(escolhe_movinic == 1){
                        if(mapa[yInimigoc+1][xInimigoc] != 1 && mapa[yInimigoc+1][xInimigoc] != 50 && mapa[yInimigoc+1][xInimigoc] != 4 && mapa[yInimigoc+1][xInimigoc] != 11 && mapa[yInimigoc+1][xInimigoc] != 12 && mapa[yInimigoc+1][xInimigoc] != 14 && mapa[yInimigoc+1][xInimigoc] != 15 && mapa[yInimigoc+1][xInimigoc] != 17 && mapa[yInimigoc+1][xInimigoc] != 18 && mapa[yInimigoc+1][xInimigoc] != 3 && mapa[yInimigoc+1][xInimigoc] != 5 && yInimigoc+1 <= 10){
                            decidido_movinic = 1;
                            yInimigoc = yInimigoc + 1;
                            ult_sentinic = 1;
                        } else{
                            while(escolhe_movinic == 1){
                                escolhe_movinic = rand()%4;                         
                            }
                            cont_decmovinic += 1;
                            decidido_movinic = 0;
                        }
                    } else if(escolhe_movinic == 2){
                        if(mapa[yInimigoc][xInimigoc-1] != 1 && mapa[yInimigoc][xInimigoc-1] != 50 && mapa[yInimigoc][xInimigoc-1] != 4 && mapa[yInimigoc][xInimigoc-1] != 11 && mapa[yInimigoc][xInimigoc-1] != 12 && mapa[yInimigoc][xInimigoc-1] != 14 && mapa[yInimigoc][xInimigoc-1] != 15 && mapa[yInimigoc][xInimigoc-1] != 17 && mapa[yInimigoc][xInimigoc-1] != 18 && mapa[yInimigoc][xInimigoc-1] != 3 && mapa[yInimigoc][xInimigoc-1] != 5 && xInimigoc-1 >= 0){
                            decidido_movinic = 1;
                            xInimigoc = xInimigoc - 1;
                            ult_sentinic = 2;
                        } else{
                            while(escolhe_movinic == 2){
                                escolhe_movinic = rand()%4;                         
                            }
                            cont_decmovinic += 1;
                            decidido_movinic = 0;
                        }
                    } else if(escolhe_movinic == 3){
                        if(mapa[yInimigoc][xInimigoc+1] != 1 && mapa[yInimigoc][xInimigoc+1] != 50 && mapa[yInimigoc][xInimigoc+1] != 4 && mapa[yInimigoc][xInimigoc+1] != 11 && mapa[yInimigoc][xInimigoc+1] != 12 && mapa[yInimigoc][xInimigoc+1] != 14 && mapa[yInimigoc][xInimigoc+1] != 15 && mapa[yInimigoc][xInimigoc+1] != 17 && mapa[yInimigoc][xInimigoc+1] != 18 && mapa[yInimigoc][xInimigoc+1] != 3 && mapa[yInimigoc][xInimigoc+1] != 5 && xInimigoc+1 <= 16){
                            decidido_movinic = 1;
                            xInimigoc = xInimigoc + 1;
                            ult_sentinic = 3;
                        } else{
                            while(escolhe_movinic == 3){
                                escolhe_movinic = rand()%4;                         
                            }
                            cont_decmovinic += 1;
                            decidido_movinic = 0;
                        }
                    } else{
                        if(ult_sentinic == 0 && mapa[yInimigoc-1][xInimigoc] != 1 && mapa[yInimigoc-1][xInimigoc] != 50 && mapa[yInimigoc-1][xInimigoc] != 4 && mapa[yInimigoc-1][xInimigoc] != 11 && mapa[yInimigoc-1][xInimigoc] != 12 && mapa[yInimigoc-1][xInimigoc] != 14 && mapa[yInimigoc-1][xInimigoc] != 15 && mapa[yInimigoc-1][xInimigoc] != 17 && mapa[yInimigoc-1][xInimigoc] != 18 && mapa[yInimigoc-1][xInimigoc] != 3 && mapa[yInimigoc-1][xInimigoc] != 5 && yInimigoc-1 >= 0){
                            yInimigoc = yInimigoc - 1;
                            decidido_movinic = 1;
                        } else if(ult_sentinic == 1 && mapa[yInimigoc+1][xInimigoc] != 1 && mapa[yInimigoc+1][xInimigoc] != 50 && mapa[yInimigoc+1][xInimigoc] != 4 && mapa[yInimigoc+1][xInimigoc] != 11 && mapa[yInimigoc+1][xInimigoc] != 12 && mapa[yInimigoc+1][xInimigoc] != 14 && mapa[yInimigoc+1][xInimigoc] != 15 && mapa[yInimigoc+1][xInimigoc] != 17 && mapa[yInimigoc+1][xInimigoc] != 18 && mapa[yInimigoc+1][xInimigoc] != 3 && mapa[yInimigoc+1][xInimigoc] != 5 && yInimigoc+1 <= 10){
                            yInimigoc = yInimigoc + 1;
                            decidido_movinic = 1;
                        } else if(ult_sentinic == 2 && mapa[yInimigoc][xInimigoc-1] != 1 && mapa[yInimigoc][xInimigoc-1] != 50 && mapa[yInimigoc][xInimigoc-1] != 4 && mapa[yInimigoc][xInimigoc-1] != 11 && mapa[yInimigoc][xInimigoc-1] != 12 && mapa[yInimigoc][xInimigoc-1] != 14 && mapa[yInimigoc][xInimigoc-1] != 15 && mapa[yInimigoc][xInimigoc-1] != 17 && mapa[yInimigoc][xInimigoc-1] != 18 && mapa[yInimigoc][xInimigoc-1] != 3 && mapa[yInimigoc][xInimigoc-1] != 5 && xInimigoc-1 >= 0){
                            xInimigoc = xInimigoc - 1;
                            decidido_movinic = 1;
                        } else if(ult_sentinic == 3 && mapa[yInimigoc][xInimigoc+1] != 1 && mapa[yInimigoc][xInimigoc+1] != 50 && mapa[yInimigoc][xInimigoc+1] != 4 && mapa[yInimigoc][xInimigoc+1] != 11 && mapa[yInimigoc][xInimigoc+1] != 12 && mapa[yInimigoc][xInimigoc+1] != 14 && mapa[yInimigoc][xInimigoc+1] != 15 && mapa[yInimigoc][xInimigoc+1] != 17 && mapa[yInimigoc][xInimigoc+1] != 18 && mapa[yInimigoc][xInimigoc+1] != 3 && mapa[yInimigoc][xInimigoc+1] != 5 && xInimigoc+1 <= 16){
                            xInimigoc = xInimigoc + 1;
                            decidido_movinic = 1;
                        } else{
                            while(escolhe_movinic != 0 && escolhe_movinic != 1 && escolhe_movinic != 2 && escolhe_movinic != 3){
                                escolhe_movinic = rand()%4;
                            }
                            cont_decmovinic += 1;
                            decidido_movinic = 0;
                        }
                    }
                }


                rodador_animinic = 1;
                if(cont_decmovinic >= 5){
                    rodador_animinic = 0;
                }
                tempo_passoinic = SDL_GetTicks();
                rodador_primeiro_passo_movinic = 1;
            }

            if(rodador_animinic == 0){
                tempo_passo_movinic = SDL_GetTicks();
            } else if(rodador_primeiro_passo_movinic == 1){
                tempo_passo_movinic = -400;
                rodador_primeiro_passo_movinic = 0;
            }
            if(SDL_GetTicks() - tempo_passo_movinic > 149){
                if(ult_sentinic == 0){
                    if(frac_passoinic != 4){
                        inimigoc.y = 119 + ((yInimigoc+1)*54) - frac_passoinic*13;
                        inic_pointer = &alienradio_sprite[frac_passoinic-1];
                        frac_passoinic += 1;
                    } else{
                        inic_pointer = &alienradio_sprite[frac_passoinic-1];
                        frac_passoinic = 1;
                        inimigoc.y = 119 + (yInimigoc*54);
                        inimigoc.x = 53 + (xInimigoc*54);
                        rodador_animinic = 0;
                    }
                } else if(ult_sentinic == 1){
                    if(frac_passoinic != 4){
                        inimigoc.y = 119 + ((yInimigoc-1)*54) + frac_passoinic*13;
                        inic_pointer = &alienradio_sprite[7+frac_passoinic];
                        frac_passoinic += 1;
                    } else{
                        inic_pointer = &alienradio_sprite[7+frac_passoinic];
                        frac_passoinic = 1;
                        inimigoc.y = 119 + (yInimigoc*54);
                        inimigoc.x = 53 + (xInimigoc*54);
                        rodador_animinic = 0;
                    }
                } else if(ult_sentinic == 2){
                    if(frac_passoinic != 4){
                        inimigoc.x = 53 + ((xInimigoc+1)*54) - frac_passoinic*13;
                        inic_pointer = &alienradio_sprite[11+frac_passoinic];
                        frac_passoinic += 1;
                    } else{
                        dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                        inic_pointer = &alienradio_sprite[11+frac_passoinic];
                        frac_passoinic = 1;
                        inimigoc.x = 53 + (xInimigoc*54);
                        inimigoc.y = 119 + (yInimigoc*54);
                        rodador_animinic = 0;
                    }
                } else if(ult_sentinic == 3){
                    if(frac_passoinic != 4){
                        inimigoc.x = 53 + ((xInimigoc-1)*54) + frac_passoinic*13;
                        inic_pointer = &alienradio_sprite[3+frac_passoinic];
                        frac_passoinic += 1;
                    } else{
                        inic_pointer = &alienradio_sprite[3+frac_passoinic];
                        frac_passoinic = 1;
                        inimigoc.x = 53 + (xInimigoc*54);
                        inimigoc.y = 119 + (yInimigoc*54);
                        rodador_animinic = 0;
                    }
                }
                tempo_passo_movinic = SDL_GetTicks();
            }
        }
    }
    /* ------- Fim movimentacao do inimigo C ------- */



    /* ------- Movimentacao do inimigo D ------- */
    if(exist_inid == 1){
        if(inimigod_morto == 0){
            if(SDL_GetTicks() - tempo_passoinid > 1000){
                escolhe_movinid = rand()%8;
                decidido_movinid = 0;
                cont_decmovinid = 0;
                while(decidido_movinid != 1 && cont_decmovinid < 5){
                    if(escolhe_movinid == 0){
                        if(mapa[yInimigod-1][xInimigod] != 1 && mapa[yInimigod-1][xInimigod] != 50 && mapa[yInimigod-1][xInimigod] != 4 && mapa[yInimigod-1][xInimigod] != 11 && mapa[yInimigod-1][xInimigod] != 12 && mapa[yInimigod-1][xInimigod] != 14 && mapa[yInimigod-1][xInimigod] != 15 && mapa[yInimigod-1][xInimigod] != 17 && mapa[yInimigod-1][xInimigod] != 18 && mapa[yInimigod-1][xInimigod] != 3 && mapa[yInimigod-1][xInimigod] != 5 && yInimigod-1 >= 0){
                            decidido_movinid = 1;
                            yInimigod = yInimigod - 1;
                            ult_sentinid = 0;
                        } else{
                            while(escolhe_movinid == 0){
                                escolhe_movinid = rand()%4;                         
                            }
                            cont_decmovinid += 1;
                            decidido_movinid = 0;
                        }
                    } else if(escolhe_movinid == 1){
                        if(mapa[yInimigod+1][xInimigod] != 1 && mapa[yInimigod+1][xInimigod] != 50 && mapa[yInimigod+1][xInimigod] != 4 && mapa[yInimigod+1][xInimigod] != 11 && mapa[yInimigod+1][xInimigod] != 12 && mapa[yInimigod+1][xInimigod] != 14 && mapa[yInimigod+1][xInimigod] != 15 && mapa[yInimigod+1][xInimigod] != 17 && mapa[yInimigod+1][xInimigod] != 18 && mapa[yInimigod+1][xInimigod] != 3 && mapa[yInimigod+1][xInimigod] != 5 && yInimigod+1 <= 10){
                            decidido_movinid = 1;
                            yInimigod = yInimigod + 1;
                            ult_sentinid = 1;
                        } else{
                            while(escolhe_movinid == 1){
                                escolhe_movinid = rand()%4;                         
                            }
                            cont_decmovinid += 1;
                            decidido_movinid = 0;
                        }
                    } else if(escolhe_movinid == 2){
                        if(mapa[yInimigod][xInimigod-1] != 1 && mapa[yInimigod][xInimigod-1] != 50 && mapa[yInimigod][xInimigod-1] != 4 && mapa[yInimigod][xInimigod-1] != 11 && mapa[yInimigod][xInimigod-1] != 12 && mapa[yInimigod][xInimigod-1] != 14 && mapa[yInimigod][xInimigod-1] != 15 && mapa[yInimigod][xInimigod-1] != 17 && mapa[yInimigod][xInimigod-1] != 18 && mapa[yInimigod][xInimigod-1] != 3 && mapa[yInimigod][xInimigod-1] != 5 && xInimigod-1 >= 0){
                            decidido_movinid = 1;
                            xInimigod = xInimigod - 1;
                            ult_sentinid = 2;
                        } else{
                            while(escolhe_movinid == 2){
                                escolhe_movinid = rand()%4;                         
                            }
                            cont_decmovinid += 1;
                            decidido_movinid = 0;
                        }
                    } else if(escolhe_movinid == 3){
                        if(mapa[yInimigod][xInimigod+1] != 1 && mapa[yInimigod][xInimigod+1] != 50 && mapa[yInimigod][xInimigod+1] != 4 && mapa[yInimigod][xInimigod+1] != 11 && mapa[yInimigod][xInimigod+1] != 12 && mapa[yInimigod][xInimigod+1] != 14 && mapa[yInimigod][xInimigod+1] != 15 && mapa[yInimigod][xInimigod+1] != 17 && mapa[yInimigod][xInimigod+1] != 18 && mapa[yInimigod][xInimigod+1] != 3 && mapa[yInimigod][xInimigod+1] != 5 && xInimigod+1 <= 16){
                            decidido_movinid = 1;
                            xInimigod = xInimigod + 1;
                            ult_sentinid = 3;
                        } else{
                            while(escolhe_movinid == 3){
                                escolhe_movinid = rand()%4;                         
                            }
                            cont_decmovinid += 1;
                            decidido_movinid = 0;
                        }
                    } else{
                        if(ult_sentinid == 0 && mapa[yInimigod-1][xInimigod] != 1 && mapa[yInimigod-1][xInimigod] != 50 && mapa[yInimigod-1][xInimigod] != 4 && mapa[yInimigod-1][xInimigod] != 11 && mapa[yInimigod-1][xInimigod] != 12 && mapa[yInimigod-1][xInimigod] != 14 && mapa[yInimigod-1][xInimigod] != 15 && mapa[yInimigod-1][xInimigod] != 17 && mapa[yInimigod-1][xInimigod] != 18 && mapa[yInimigod-1][xInimigod] != 3 && mapa[yInimigod-1][xInimigod] != 5 && yInimigod-1 >= 0){
                            yInimigod = yInimigod - 1;
                            decidido_movinid = 1;
                        } else if(ult_sentinid == 1 && mapa[yInimigod+1][xInimigod] != 1 && mapa[yInimigod+1][xInimigod] != 50 && mapa[yInimigod+1][xInimigod] != 4 && mapa[yInimigod+1][xInimigod] != 11 && mapa[yInimigod+1][xInimigod] != 12 && mapa[yInimigod+1][xInimigod] != 14 && mapa[yInimigod+1][xInimigod] != 15 && mapa[yInimigod+1][xInimigod] != 17 && mapa[yInimigod+1][xInimigod] != 18 && mapa[yInimigod+1][xInimigod] != 3 && mapa[yInimigod+1][xInimigod] != 5 && yInimigod+1 <= 10){
                            yInimigod = yInimigod + 1;
                            decidido_movinid = 1;
                        } else if(ult_sentinid == 2 && mapa[yInimigod][xInimigod-1] != 1 && mapa[yInimigod][xInimigod-1] != 50 && mapa[yInimigod][xInimigod-1] != 4 && mapa[yInimigod][xInimigod-1] != 11 && mapa[yInimigod][xInimigod-1] != 12 && mapa[yInimigod][xInimigod-1] != 14 && mapa[yInimigod][xInimigod-1] != 15 && mapa[yInimigod][xInimigod-1] != 17 && mapa[yInimigod][xInimigod-1] != 18 && mapa[yInimigod][xInimigod-1] != 3 && mapa[yInimigod][xInimigod-1] != 5 && xInimigod-1 >= 0){
                            xInimigod = xInimigod - 1;
                            decidido_movinid = 1;
                        } else if(ult_sentinid == 3 && mapa[yInimigod][xInimigod+1] != 1 && mapa[yInimigod][xInimigod+1] != 50 && mapa[yInimigod][xInimigod+1] != 4 && mapa[yInimigod][xInimigod+1] != 11 && mapa[yInimigod][xInimigod+1] != 12 && mapa[yInimigod][xInimigod+1] != 14 && mapa[yInimigod][xInimigod+1] != 15 && mapa[yInimigod][xInimigod+1] != 17 && mapa[yInimigod][xInimigod+1] != 18 && mapa[yInimigod][xInimigod+1] != 3 && mapa[yInimigod][xInimigod+1] != 5 && xInimigod+1 <= 16){
                            xInimigod = xInimigod + 1;
                            decidido_movinid = 1;
                        } else{
                            while(escolhe_movinid != 0 && escolhe_movinid != 1 && escolhe_movinid != 2 && escolhe_movinid != 3){
                                escolhe_movinid = rand()%4;
                            }
                            cont_decmovinid += 1;
                            decidido_movinid = 0;
                        }
                    }
                }


                rodador_animinid = 1;
                if(cont_decmovinid >= 5){
                    rodador_animinid = 0;
                }
                tempo_passoinid = SDL_GetTicks();
                rodador_primeiro_passo_movinid = 1;
            }

            if(rodador_animinid == 0){
                tempo_passo_movinid = SDL_GetTicks();
            } else if(rodador_primeiro_passo_movinid == 1){
                tempo_passo_movinid = -400;
                rodador_primeiro_passo_movinid = 0;
            }
            if(SDL_GetTicks() - tempo_passo_movinid > 249){
                if(ult_sentinid == 0){
                    if(frac_passoinid != 4){
                        inimigod.y = 119 + ((yInimigod+1)*54) - frac_passoinid*13;
                        inid_pointer = &alienogre_sprite[frac_passoinid-1];
                        frac_passoinid += 1;
                    } else{
                        inid_pointer = &alienogre_sprite[frac_passoinid-1];
                        frac_passoinid = 1;
                        inimigod.y = 119 + (yInimigod*54);
                        inimigod.x = 53 + (xInimigod*54);
                        rodador_animinid = 0;
                    }
                } else if(ult_sentinid == 1){
                    if(frac_passoinid != 4){
                        inimigod.y = 119 + ((yInimigod-1)*54) + frac_passoinid*13;
                        inid_pointer = &alienogre_sprite[7+frac_passoinid];
                        frac_passoinid += 1;
                    } else{
                        inid_pointer = &alienogre_sprite[7+frac_passoinid];
                        frac_passoinid = 1;
                        inimigod.y = 119 + (yInimigod*54);
                        inimigod.x = 53 + (xInimigod*54);
                        rodador_animinid = 0;
                    }
                } else if(ult_sentinid == 2){
                    if(frac_passoinid != 4){
                        inimigod.x = 53 + ((xInimigod+1)*54) - frac_passoinid*13;
                        inid_pointer = &alienogre_sprite[11+frac_passoinid];
                        frac_passoinid += 1;
                    } else{
                        dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                        inid_pointer = &alienogre_sprite[11+frac_passoinid];
                        frac_passoinid = 1;
                        inimigod.x = 53 + (xInimigod*54);
                        inimigod.y = 119 + (yInimigod*54);
                        rodador_animinid = 0;
                    }
                } else if(ult_sentinid == 3){
                    if(frac_passoinid != 4){
                        inimigod.x = 53 + ((xInimigod-1)*54) + frac_passoinid*13;
                        inid_pointer = &alienogre_sprite[3+frac_passoinid];
                        frac_passoinid += 1;
                    } else{
                        inid_pointer = &alienogre_sprite[3+frac_passoinid];
                        frac_passoinid = 1;
                        inimigod.x = 53 + (xInimigod*54);
                        inimigod.y = 119 + (yInimigod*54);
                        rodador_animinid = 0;
                    }
                }
                tempo_passo_movinid = SDL_GetTicks();
            }
        }
    }
    /* ------- Fim movimentacao do inimigo D ------- */






    /* ------- Perde vida com a bomba -------- */
    if(mapa[yAtual][xAtual] == 20 || mapa[yAtual][xAtual] == 21 || mapa[yAtual][xAtual] == 22 || mapa[yAtual][xAtual] == 23 || mapa[yAtual][xAtual] == 24 || mapa[yAtual][xAtual] == 25 || mapa[yAtual][xAtual] == 26 || mapa[yAtual][xAtual] == 27 || mapa[yAtual][xAtual] == 28){ 
        if(morreu_bomba == 0 && mudou_bloco == 1){
            vidas -= 1;
            morreu_bomba = 1;
            rodador_temporenasc = 1;
            tempo_renasc = SDL_GetTicks();
            roda_blitaplayer = 0;
            yAtual = -100;
            xAtual = -100;
            personagem.x = -54;
            personagem.y = -54;
        }
    }
    if(rodador_temporenasc == 1 && SDL_GetTicks()-tempo_renasc > 1500){
        yAtual = 0;
        xAtual = 0;
        personagem.x = 53;
        personagem.y = 119;
        rodador_temporenasc = 0;
        roda_blitaplayer = 1;
        tempo_renasc = -1500;
        
    }
    /* ------ Fim perde vida com a bomba ------ */


    /* ------- Mata o inimigo A com a bomba -------- */
    if(exist_inia == 1){
        if(mapa[yInimigoa][xInimigoa] == 20 || mapa[yInimigoa][xInimigoa] == 21 || mapa[yInimigoa][xInimigoa] == 22 || mapa[yInimigoa][xInimigoa] == 23 || mapa[yInimigoa][xInimigoa] == 24 || mapa[yInimigoa][xInimigoa] == 25 || mapa[yInimigoa][xInimigoa] == 26 || mapa[yInimigoa][xInimigoa] == 27 || mapa[yInimigoa][xInimigoa] == 28){ 
            if(inimigoa_morto == 0)
                pontuacao += 100;
            inimigoa_morto = 1;
            xInimigoa = -30;
            yInimigoa = -30;
            matou_alien = 1;
            Mix_PlayChannel( -1, diesob, 0 );
            tempo_matoualien = SDL_GetTicks();
            //
        }
        //Mix_PlayChannel( -1, diesob, 0 );
        
    }
    /* ------ Fim mata o inimigo A com a bomba ------ */


    /* ------- Mata o inimigo B com a bomba -------- */
    if(exist_inib == 1){
        if(mapa[yInimigob][xInimigob] == 20 || mapa[yInimigob][xInimigob] == 21 || mapa[yInimigob][xInimigob] == 22 || mapa[yInimigob][xInimigob] == 23 || mapa[yInimigob][xInimigob] == 24 || mapa[yInimigob][xInimigob] == 25 || mapa[yInimigob][xInimigob] == 26 || mapa[yInimigob][xInimigob] == 27 || mapa[yInimigob][xInimigob] == 28){ 
            if(inimigob_morto == 0)
                pontuacao += 100;
            inimigob_morto = 1;
            xInimigob = -30;
            yInimigob = -30;
            matou_alien = 1;
            Mix_PlayChannel( -1, letgod, 0 );
            tempo_matoualien = SDL_GetTicks();
            
        }
        //Mix_PlayChannel( -1, letgod, 0 );
    }
    /* ------ Fim mata o inimigo B com a bomba ------ */


    /* ------- Mata o inimigo C com a bomba -------- */
    if(exist_inic == 1){
        if(mapa[yInimigoc][xInimigoc] == 20 || mapa[yInimigoc][xInimigoc] == 21 || mapa[yInimigoc][xInimigoc] == 22 || mapa[yInimigoc][xInimigoc] == 23 || mapa[yInimigoc][xInimigoc] == 24 || mapa[yInimigoc][xInimigoc] == 25 || mapa[yInimigoc][xInimigoc] == 26 || mapa[yInimigoc][xInimigoc] == 27 || mapa[yInimigoc][xInimigoc] == 28){ 
            if(inimigoc_morto == 0)
                pontuacao += 100;
            inimigoc_morto = 1;
            xInimigoc = -30;
            yInimigoc = -30;
            matou_alien = 1;
            Mix_PlayChannel( -1, hurts, 0 );
            tempo_matoualien = SDL_GetTicks();
            
        }
        //Mix_PlayChannel( -1, hurts, 0 );
    }
    /* ------ Fim mata o inimigo C com a bomba ------ */


    /* ------- Mata o inimigo D com a bomba -------- */
    if(exist_inid == 1){
        if(mapa[yInimigod][xInimigod] == 20 || mapa[yInimigod][xInimigod] == 21 || mapa[yInimigod][xInimigod] == 22 || mapa[yInimigod][xInimigod] == 23 || mapa[yInimigod][xInimigod] == 24 || mapa[yInimigod][xInimigod] == 25 || mapa[yInimigod][xInimigod] == 26 || mapa[yInimigod][xInimigod] == 27 || mapa[yInimigod][xInimigod] == 28){ 
            if(inimigod_morto == 0)
                pontuacao += 100;
            inimigod_morto = 1;
            xInimigod = -30;
            yInimigod = -30;
            matou_alien = 1;
            Mix_PlayChannel( -1, hell, 0 );
            tempo_matoualien = SDL_GetTicks();
            //
        }
        //Mix_PlayChannel( -1, hell, 0 );
    }
    /* ------ Fim mata o inimigo D com a bomba ------ */


    /* ------- Perde vida com inimigo -------- */
    if(exist_inia == 1){
        if(yAtual == yInimigoa && xAtual == xInimigoa && mudou_bloco == 1){ 
            if(yInimigoa == yAtual && xInimigoa == xAtual){
                vidas -= 1;
                rodador_temporenasc = 1;
                tempo_renasc = SDL_GetTicks();
                roda_blitaplayer = 0;
                yAtual = -100;
                xAtual = -100;
                personagem.x = -54;
                personagem.y = -54;
            }
        }
    }
    if(exist_inib == 1){
        if(yAtual == yInimigob && xAtual == xInimigob && mudou_bloco == 1){ 
            if(yInimigob == yAtual && xInimigob == xAtual){
                vidas -= 1;
                rodador_temporenasc = 1;
                tempo_renasc = SDL_GetTicks();
                roda_blitaplayer = 0;
                yAtual = -100;
                xAtual = -100;
                personagem.x = -54;
                personagem.y = -54;
            }
        }
    }
    if(exist_inic == 1){
        if(yAtual == yInimigoc && xAtual == xInimigoc && mudou_bloco == 1){ 
            if(yInimigoc == yAtual && xInimigoc == xAtual){
                vidas -= 1;
                rodador_temporenasc = 1;
                tempo_renasc = SDL_GetTicks();
                roda_blitaplayer = 0;
                yAtual = -100;
                xAtual = -100;
                personagem.x = -54;
                personagem.y = -54;
            }
        }
    }
    if(exist_inid == 1){
        if(yAtual == yInimigod && xAtual == xInimigod && mudou_bloco == 1){ 
            if(yInimigod == yAtual && xInimigod == xAtual){
                vidas -= 1;
                rodador_temporenasc = 1;
                tempo_renasc = SDL_GetTicks();
                roda_blitaplayer = 0;
                yAtual = -100;
                xAtual = -100;
                personagem.x = -54;
                personagem.y = -54;
            }
        }
    }
    if(rodador_temporenasc == 1 && SDL_GetTicks()-tempo_renasc > 1500){
        yAtual = 0;
        xAtual = 0;
        personagem.x = 53;
        personagem.y = 119;
        rodador_temporenasc = 0;
        roda_blitaplayer = 1;
        tempo_renasc = -1500;
        
    }
    /* ------ Fim perde vida com inimigo ------ */




    if(rodador_tbomb == 0){
        tempo_bomb = SDL_GetTicks();
    }
    if(SDL_GetTicks() - tempo_bomb > 3000){
        for(i=0;i<17;i++){
            for(j=0;j<11;j++){
                if(mapa[j][i]==5){
                        mapa[j][i] = 20;
                        rodador_animexp = 1;
                        tempo_rodexp = 0;
                        morreu_bomba = 0;

                        for(rb=1;rb<=raiobomb;rb++){
                            if(mapa[j-rb][i] == 3 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 4;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 11 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 12;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 14 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 15;
                                colexp_a = 1;
                            }  else if(mapa[j-rb][i] == 17 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 18;
                                colexp_a = 1;
                            }  else if(mapa[j-rb][i] == 50 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 51;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 1 && j-rb >= 0 && colexp_a == 0){
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 0 && j-rb >= 0 && colexp_a == 0){
                                mapa[j-rb][i] = 21;
                                if(rb == raiobomb)
                                    mapa[j-rb][i] = 25;
                            }
                            if(mapa[j][i-rb] == 3 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 4;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 11 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 12;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 14 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 15;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 17 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 18;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 50 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 51;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 1 && i-rb >= 0 && colexp_b == 0){
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 0 && i-rb >= 0 && colexp_b == 0){
                                mapa[j][i-rb] = 22;
                                if(rb == raiobomb)
                                    mapa[j][i-rb] = 26;
                            }
                            if(mapa[j+rb][i] == 3 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 4;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 11 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 12;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 14 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 15;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 17 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 18;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 50 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 51;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 1 && j+rb <= 10 && colexp_c == 0){
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 0 && j+rb <= 10 && colexp_c == 0){
                                mapa[j+rb][i] = 23;
                                if(rb == raiobomb)
                                    mapa[j+rb][i] = 27;
                            }
                            if(mapa[j][i+rb] == 3 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 4;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 11 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 12;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 14 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 15;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 17 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 18;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 50 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 51;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 1 && i+rb <= 16 && colexp_d == 0){
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 0 && i+rb <= 16 && colexp_d == 0){
                                mapa[j][i+rb] = 24;
                                if(rb == raiobomb)
                                    mapa[j][i+rb] = 28;
                            }
                        }
                    }
                }
            }
            rodador_tbomb = 0;
        }




        /* --------- Info do HUD ----------- */

        sprintf(string_pontuacao, "%d", pontuacao);
        text_pontuacao = TTF_RenderText_Solid( font, string_pontuacao, textCorVermelho );
        apply_surface( 805, 13, text_pontuacao, screen, NULL );

        sprintf(string_vidas, "%d", vidas);
        text_vidas = TTF_RenderText_Solid( font, string_vidas, textCorVermelho );
        apply_surface( 580, 13, text_vidas, screen, NULL );

        sprintf(string_raiobomb, "%d", raiobomb);
        text_raiobomb = TTF_RenderText_Solid( font, string_raiobomb, textCorVermelho );
        apply_surface( 686, 13, text_raiobomb, screen, NULL );



        cron_segjogo = (SDL_GetTicks()-horainicfase) / 1000;

        //Segundos restantes para o jogo acabar. O 180 representa o tempo inicial da contagem regressiva
        cron_segrest = tempototal_fase - cron_segjogo;
        cron_minrest = cron_segrest / 60;
        cron_segminrest = cron_segrest - (cron_minrest*60);

        //A linha a baixo define o tempo restante
        sprintf(string_cronometro, "%.2d:%.2d",cron_minrest,cron_segminrest);

        if(cron_segrest == 0){
            jogorodando = 1;
            faserodando = 1;
        }

        text_cronometro = TTF_RenderText_Solid( font, string_cronometro, textCorVermelho );
        apply_surface( 464, 13, text_cronometro, screen, NULL );

        
        if(matou_alien == 1){
            sprintf(string_faladn, " ");
            text_faladn = TTF_RenderText_Solid( font_fala, string_faladn, textCorVermelho );
            apply_surface( 200, 13, text_faladn, screen, NULL );
            if(SDL_GetTicks()-tempo_matoualien > 4000){
                matou_alien = 0;
            }
        }
        


        /* --------- Fim info do HUD ----------- */



        if(rodador_animexp == 1){
            Mix_Volume(-1, 10);
            Mix_PlayChannel( -1, explosao, 0 );
            for(i=0;i<17;i++){
                for(j=0;j<11;j++){
                    if(SDL_GetTicks()-tempo_parexp < 100){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[0]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[7]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[5]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[3]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[1]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[8]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[6]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[4]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[2]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==51){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        }
                        
                    } else if(SDL_GetTicks()-tempo_parexp >= 100 && SDL_GetTicks()-tempo_parexp < 200){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[9]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[16]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[14]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[12]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[10]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[17]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[15]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[13]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[11]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==51){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        }
                    } else if(SDL_GetTicks()-tempo_parexp >= 200 && SDL_GetTicks()-tempo_parexp < 300){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[18]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[25]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[23]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[21]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[19]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[26]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[24]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[22]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[20]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==51){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        }
                    } else if(SDL_GetTicks()-tempo_parexp >= 300 && SDL_GetTicks()-tempo_parexp < 400){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[9]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[16]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[14]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[12]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[10]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[17]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[15]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[13]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[11]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==51){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        }
                    } else if(SDL_GetTicks()-tempo_parexp >= 400){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[0]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[7]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[5]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[3]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[1]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[8]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[6]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[4]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[2]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==51){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        }
                    }
                }
            }
            rodador_parexp = 1;
        }
        if(rodador_parexp == 0){
            tempo_parexp = SDL_GetTicks();
        }
        if(SDL_GetTicks()-tempo_parexp > 500){
            rodador_parexp = 0;
            rodador_animexp = 0;
            morreu_bomba = 1;
            for(i=0;i<17;i++){
                for(j=0;j<11;j++){
                    if(mapa[j][i] == 20 || mapa[j][i] == 21 || mapa[j][i] == 22 || mapa[j][i] == 23 || mapa[j][i] == 24 || mapa[j][i] == 25 || mapa[j][i] == 26 || mapa[j][i] == 27 || mapa[j][i] == 28 || mapa[j][i] == 4){
                        mapa[j][i] = 0;
                    }
                    if(mapa[j][i] == 12){
                        mapa[j][i] = 13;
                    } else if(mapa[j][i] == 15){
                        mapa[j][i] = 16;
                    } else if(mapa[j][i] == 18){
                        mapa[j][i] = 19;
                    } else if(mapa[j][i] == 51){
                        mapa[j][i] = 52;
                    }
                }
            }
        }

        //DESENHO TODOS OS ELEMENTOS DO MAPA
        // SE MAPA[Y(LINHA)][X(COLUNA)].
        for(i=0;i<17;i++){

            for(j=0;j<11;j++){

                if(mapa[j][i]==1){
                    apply_surface((53+i*54),(119+j*54),blocoind,screen, NULL);
                }
                else if(mapa[j][i]==3 || mapa[j][i]==11 || mapa[j][i]==14 || mapa[j][i]==17 || mapa[j][i]==50)
                {
                    apply_surface((53+i*54),(119+j*54),blocodes,screen, NULL);
                }
               // else if(mapa[j][i]==2)
               // {
               //     apply_surface((68+i*64),(164+j*64),sprite_dn_bai3_game_DN,screen);
               // }
                else if(mapa[j][i]==5)
                {
                    bomb.x = 53 + (i*54);
                    bomb.y = 119 + (j*54);

                    if(SDL_GetTicks() - tempo_spritebomb > 300){
                        if(bomb_pointer == &bomb_sprite[0]){
                            bomb_pointer = &bomb_sprite[1];
                        } else{
                            bomb_pointer = &bomb_sprite[0];                            
                        }
                        tempo_spritebomb = SDL_GetTicks();
                    }
                    SDL_BlitSurface(imgbomb,bomb_pointer,screen,&bomb);
                }
                else if(mapa[j][i]==13)
                {
                    apply_surface((53+i*54),(119+j*54),imgpkplut,screen, NULL);
                }
                else if(mapa[j][i]==16)
                {
                    apply_surface((53+i*54),(119+j*54),imgpkvida,screen, NULL);
                }
                else if(mapa[j][i]==19)
                {
                    apply_surface((53+i*54),(119+j*54),imgpkclub,screen, NULL);
                }
                else if(mapa[j][i]==52)
                {
                    apply_surface((53+i*54),(119+j*54),imgburaco,screen, NULL);
                }
            }
        }

        if(colet_clubcard == 1){
            apply_surface(987,2,iconstrip,screen, NULL);
        } else if(colet_clubcard == 2){
            apply_surface(957,2,iconstrip,screen, NULL);
            apply_surface(987,2,iconstrip,screen, NULL);
        } else if(colet_clubcard >= 3){
            apply_surface(927,2,iconstrip,screen, NULL);
            apply_surface(957,2,iconstrip,screen, NULL);
            apply_surface(987,2,iconstrip,screen, NULL);
            if(SDL_GetTicks()-tempo_blinkiconclub > 500){
                apply_surface(877,2,iconclub,screen, NULL);
                if(SDL_GetTicks()-tempo_blinkiconclub > 2200){
                    tempo_blinkiconclub = SDL_GetTicks();
                }
            }
        }
        

        // Marcador da posição na matriz
        //apply_surface((53+xAtual*54),(119+yAtual*54),posi_matriz,screen);
        //apply_surface((53+xInimigoa*54),(119+yInimigoa*54),posi_matriz,screen);

        if(roda_blitaplayer == 1){
            SDL_BlitSurface(player,dn_pointer,screen,&personagem);
        }

        if(exist_inia == 1){
            if(inimigoa_morto == 0){
                SDL_BlitSurface(alienogre,inia_pointer,screen,&inimigoa);
                if(cont_decmovinia >= 5){
                    inimigoa.x = 53 + xInimigoa * 54;
                    inimigoa.y = 119 + yInimigoa * 54;
                    inia_pointer = &alienogre_sprite[ult_sentinia];
                    SDL_BlitSurface(alienogre,inia_pointer,screen,&inimigoa);
                }
            }
        }
        if(exist_inib == 1){
            if(inimigob_morto == 0){
                SDL_BlitSurface(alienogre,inib_pointer,screen,&inimigob);
                if(cont_decmovinib >= 5){
                    inimigob.x = 53 + xInimigob * 54;
                    inimigob.y = 119 + yInimigob * 54;
                    inib_pointer = &alienogre_sprite[ult_sentinib];
                    SDL_BlitSurface(alienogre,inib_pointer,screen,&inimigob);
                }
            }
        }
        if(exist_inic == 1){
            if(inimigoc_morto == 0){
                SDL_BlitSurface(alienradio,inic_pointer,screen,&inimigoc);
                if(cont_decmovinic >= 5){
                    inimigoc.x = 53 + xInimigoc * 54;
                    inimigoc.y = 119 + yInimigoc * 54;
                    inic_pointer = &alienradio_sprite[ult_sentinic];
                    SDL_BlitSurface(alienradio,inic_pointer,screen,&inimigoc);
                }
            }
        }
        if(exist_inid == 1){
            if(inimigod_morto == 0){
                SDL_BlitSurface(alienogre,inid_pointer,screen,&inimigod);
                if(cont_decmovinid >= 5){
                    inimigod.x = 53 + xInimigod * 54;
                    inimigod.y = 119 + yInimigod * 54;
                    inid_pointer = &alienogre_sprite[ult_sentinid];
                    SDL_BlitSurface(alienogre,inid_pointer,screen,&inimigod);
                }
            }
        }

        SDL_Flip(screen);
        apply_surface(0,0,fundo,screen, NULL);

        // message processing loop
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                jogorodando = 1;
                faserodando = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // SE A TECLA PRESSIONADA FOR ESC

                    if (event.key.keysym.sym == SDLK_ESCAPE){


                        contin_pause = 0;
                        while(contin_pause == 0){

                        apply_surface(0,0,fundopause,screen, NULL);

                        while (SDL_PollEvent(&eventpause))
                        {
                            // check for messages
                            switch (eventpause.type)
                            {
                                // exit if the window is closed
                            case SDL_QUIT:
                                jogorodando = 1;
                                faserodando = 1;
                                sairjogo = 1;
                                break;


                                // check for keypresses
                            case SDL_KEYDOWN:
                                {

                                    if (eventpause.key.keysym.sym == SDLK_UP){
                                        opcaopause = 1;
                                        break;
                                    }

                                    if (eventpause.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                                        opcaopause = 2;
                                        break;
                                    }


                                    if (eventpause.key.keysym.sym == SDLK_RETURN){
                                       if(opcaopause == 1){
                                            contin_pause = 1;
                                        }
                                        else if(opcaopause == 2){
                                            jogorodando = 1;
                                            faserodando = 1;
                                            contin_pause = 1;
                                        }

                                    }
                                }

                            } // end switch
                        }
                        for(linha=0;linha<5;linha++)
                        {
                            if(opcaopause==1)
                                apply_surface(345,370,seletor,screen, NULL);
                            else if(opcaopause==2)
                                apply_surface(280,430,seletor,screen, NULL);
                        }
                        SDL_Flip(screen);
                    }



                    break;
                    }

                    if (event.key.keysym.sym == SDLK_UP){
                        inc_my = -1;
                        ult_sent = 0;
                        rodador_movdn = 1;
                        conf_kup += 1;

                        break;
                    }

                    if (event.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                        inc_my = 1;
                        ult_sent = 8;
                        rodador_movdn = 1;
                        conf_kup += 1;

                        break;
                    }

                    if (event.key.keysym.sym == SDLK_RIGHT){
                        inc_mx = 1;
                        ult_sent = 4;
                        rodador_movdn = 1;
                        conf_kup += 1;
                            
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_LEFT){
                        inc_mx = -1;
                        ult_sent = 12;
                        rodador_movdn = 1;
                        conf_kup += 1;
                        
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_SPACE){
                        rodador_tbomb = 1;
                        conf_bomb = 0;
                        for(i=0;i<11;i++){
                            for(j=0;j<17;j++){
                                if(mapa[i][j] == 5){
                                    conf_bomb += 1;
                                }
                            }
                        }
                        if(conf_bomb < 1){
                            mapa[yAtual][xAtual] = 5;
                        }

                        colexp_a = 0;
                        colexp_b = 0;
                        colexp_c = 0;
                        colexp_d = 0;

                        conf_kup += 1;
                        break;
                    }
                }
            case SDL_KEYUP:
                {
                    /*
                    */
                    if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_SPACE) {
                        if(conf_kup == 1){
                            inc_my = 0;
                            inc_mx = 0;
                        } else {
                            if(ult_sent == 4 || ult_sent == 12){
                                inc_my = 0;
                            }
                            if(ult_sent == 0 || ult_sent == 8){
                                inc_mx = 0;
                            }
                        }
                        conf_kup--;
                    }

                            //inc_my = 0;
                            //inc_mx = 0;
                }


            } // end switch
        } // end of message processing
    }


if(passou_fase == 1){
    contin_passoufase = 0;
    opcaofimfase = 1;
    cont_spritestrdanc = 0;
    tempo_stripdance = 0;

    radioatividade = pontuacao;
    pontuacao += (vidas*100);
    if(pontuacao != (((300-cron_segjogo)/10)*pontuacao)){
        pontuacao = (((300-cron_segjogo)/10)*pontuacao);
    }
    pontuacaototaljogador += pontuacao;

    while(contin_passoufase == 0){

    apply_surface(0,0,fundofimfase,screen, NULL);


        sprintf(string_cronometro_fimfase, "%d", 300-cron_segjogo);
        text_cronometro_fimfase = TTF_RenderText_Solid( font_pontos, string_cronometro_fimfase, textCorAmarelo );
        apply_surface( 690, 113, text_cronometro_fimfase, screen, NULL );

        sprintf(string_vidas_fimfase, "%d", vidas);
        text_vidas_fimfase = TTF_RenderText_Solid( font_pontos, string_vidas_fimfase, textCorAmarelo );
        apply_surface( 690, 154, text_vidas_fimfase, screen, NULL );

        sprintf(string_bonusvidas_fimfase, "%d", (vidas*100));
        text_bonusvidas_fimfase = TTF_RenderText_Solid( font_pontos, string_bonusvidas_fimfase, textCorAmarelo );
        apply_surface( 690, 200, text_bonusvidas_fimfase, screen, NULL );

        sprintf(string_pontuacao_fimfase, "%d", radioatividade);
        text_pontuacao_fimfase = TTF_RenderText_Solid( font_pontos, string_pontuacao_fimfase, textCorAmarelo );
        apply_surface( 690, 244, text_pontuacao_fimfase, screen, NULL );

        sprintf(string_pontuacaototal_fimfase, "%d", pontuacao);
        text_pontuacaototal_fimfase = TTF_RenderText_Solid( font_pontos, string_pontuacaototal_fimfase, textCorAmarelo );
        apply_surface( 690, 461, text_pontuacaototal_fimfase, screen, NULL );


        if(colet_clubcard == 1){
            apply_surface(674,316,iconstripfimfase,screen, NULL);
        } else if(colet_clubcard == 2){
            apply_surface(674,316,iconstripfimfase,screen, NULL);
            apply_surface(720,316,iconstripfimfase,screen, NULL);
        } else if(colet_clubcard >= 3){
            apply_surface(674,316,iconstripfimfase,screen, NULL);
            apply_surface(720,316,iconstripfimfase,screen, NULL);
            apply_surface(766,316,iconstripfimfase,screen, NULL);
            apply_surface(18, 30, clubfimfase, screen, NULL);

            strdanc_pointer = &strdanc_sprite[cont_spritestrdanc];

            if(SDL_GetTicks()-tempo_stripdance > 100){
                cont_spritestrdanc += 1;
                if(cont_spritestrdanc > 5){
                    cont_spritestrdanc = 0;
                }
                tempo_stripdance = SDL_GetTicks();
            }
            SDL_BlitSurface(stripdanc,strdanc_pointer,screen,&stripdancer);
        }

        while (SDL_PollEvent(&eventfimfase))
        {
            // check for messages
            switch (eventfimfase.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                jogorodando = 1;
                faserodando = 1;
                sairjogo = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {

                    if (eventfimfase.key.keysym.sym == SDLK_UP){
                        opcaofimfase = 1;
                        break;
                    }

                    if (eventfimfase.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                        opcaofimfase = 2;
                        break;
                    }


                    if (eventfimfase.key.keysym.sym == SDLK_RETURN){
                       if(opcaofimfase == 1){
                            contin_passoufase = 1;
                        }
                        else if(opcaofimfase == 2){
                            jogorodando = 1;
                            faserodando = 1;
                            contin_passoufase = 1;
                        }

                    }
                }

            } // end switch
        }
        for(linha=0;linha<5;linha++)
        {
            if(opcaofimfase==1)
                apply_surface(663,628,seletor,screen, NULL);
            else if(opcaofimfase==2)
                apply_surface(533,690,seletor,screen, NULL);
        }
        SDL_Flip(screen);
    }
}


if(perdeu_jogo == 1){
    opcaoperdeujogo = 1;
    contin_perdeujogo = 0;

    pontuacao += (vidas*100);
    pontuacao = (((300-cron_segjogo)/10)*pontuacao);
    pontuacaototaljogador += pontuacao;

    l = 0;
    for(i=0;i<20;i++){
        temp[i] = '\0';
        jogador.nome[i] = '\0';
    }

    SDL_EnableUNICODE( SDL_ENABLE );
    while(contin_perdeujogo == 0)
    {
        
        while( SDL_PollEvent( &eventperdeujogo ) )
        {
            if( eventperdeujogo.type == SDL_KEYDOWN )
            {
                //If the string less than maximum size
                if( strlen(temp) <= 19 )
                {
                    //If the key is a space
                    if( eventperdeujogo.key.keysym.unicode == (Uint16)' ' )
                    {
                        //Append the character
                        temp[l] = (char)eventperdeujogo.key.keysym.unicode;
                        jogador.nome[l] = (char)eventperdeujogo.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                    //If the key is a number
                    if( ( eventperdeujogo.key.keysym.unicode >= (Uint16)'0' ) && ( eventperdeujogo.key.keysym.unicode <= (Uint16)'9' ) )
                    {
                        //Append the character
                        temp[l] = (char)eventperdeujogo.key.keysym.unicode;
                        jogador.nome[l] = (char)eventperdeujogo.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                    //If the key is a uppercase letter
                    if( ( eventperdeujogo.key.keysym.unicode >= (Uint16)'A' ) && ( eventperdeujogo.key.keysym.unicode <= (Uint16)'Z' ) )
                    {
                        //Append the character
                        temp[l] = (char)eventperdeujogo.key.keysym.unicode;
                        jogador.nome[l] = (char)eventperdeujogo.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                    //If the key is a lowercase letter
                    if( ( eventperdeujogo.key.keysym.unicode >= (Uint16)'a' ) && ( eventperdeujogo.key.keysym.unicode <= (Uint16)'z' ) )
                    {
                        //Append the character
                        temp[l] = (char)eventperdeujogo.key.keysym.unicode;
                        jogador.nome[l] = (char)eventperdeujogo.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                }
                    //If backspace was pressed and the string isn't blank
                    if( ( eventperdeujogo.key.keysym.sym == SDLK_BACKSPACE ) && ( l != 0 ) )
                    {
                        //Remove a character from the end
                        l--;
                        temp[l]='\0';
                        jogador.nome[l]='\0';
                    }
                    if( ( eventperdeujogo.key.keysym.sym == SDLK_RETURN ) && ( l != 0 ) )
                    {
                        temp[l]='\0';
                        jogador.nome[l] ='\0';

                        jogorodando = 1;
                        faserodando = 1;
                        contin_perdeujogo = 1;
                        perdeu_jogo = 0;
                    }

                    if (eventperdeujogo.type == SDL_QUIT){
                        jogorodando = 1;
                        faserodando = 1;
                        sairjogo = 1;
                        contin_perdeujogo = 1;
                        perdeu_jogo = 0;
                        break;
                    }

                    //CRIA O TEXTO QUE VAI APARECER NA TELA
                    textrecord = TTF_RenderText_Solid( font_pontos, temp, textColorCinza );
            }
        }

        apply_surface( 380, 507, textrecord, screen, NULL );

            SDL_Flip(screen);
            apply_surface( 0, 0, fundoperdeujogo, screen, NULL );
        }

    for(i=1;temp[i]!='\0';i++){
        rec1.nome[i-1] = temp[i-1];
    }
    //fgets(rec1.nome, MAX_NOME, stdin);

    rec1.nome[strlen(rec1.nome) - 1] = '\0';

    //printf("Pontuação:");
    rec1.pontuacaorecord = pontuacaototaljogador;

    insere(&array, rec1);

    if((p_arquivo = fopen(nome_arquivo, "w")) == NULL)
    {
        perror("fopen:");
        return 1;
    }

    fwrite(&array, sizeof(ARRAY), 1, p_arquivo);
    fclose(p_arquivo);

    pontuacaototaljogador = 0;
}



if(wingame == 1){
    pontuacao += (vidas*100);
    if(pontuacao != (((300-cron_segjogo)/10)*pontuacao)){
        pontuacao = (((300-cron_segjogo)/10)*pontuacao);
    }
    pontuacaototaljogador += pontuacao;


    contin_wingame = 0;

    l = 0;
    for(i=0;i<20;i++){
        temp[i] = '\0';
        jogador.nome[i] = '\0';
    }

    SDL_EnableUNICODE( SDL_ENABLE );
    while(contin_wingame == 0)
    {
        while( SDL_PollEvent( &eventwingame ) )
        {
            if( eventwingame.type == SDL_KEYDOWN )
            {
                //If the string less than maximum size
                if( strlen(temp) <= 19 )
                {
                    //If the key is a space
                    if( eventwingame.key.keysym.unicode == (Uint16)' ' )
                    {
                        //Append the character
                        temp[l] = (char)eventwingame.key.keysym.unicode;
                        jogador.nome[l] = (char)eventwingame.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                    //If the key is a number
                    if( ( eventwingame.key.keysym.unicode >= (Uint16)'0' ) && ( eventwingame.key.keysym.unicode <= (Uint16)'9' ) )
                    {
                        //Append the character
                        temp[l] = (char)eventwingame.key.keysym.unicode;
                        jogador.nome[l] = (char)eventwingame.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                    //If the key is a uppercase letter
                    if( ( eventwingame.key.keysym.unicode >= (Uint16)'A' ) && ( eventwingame.key.keysym.unicode <= (Uint16)'Z' ) )
                    {
                        //Append the character
                        temp[l] = (char)eventwingame.key.keysym.unicode;
                        jogador.nome[l] = (char)eventwingame.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                    //If the key is a lowercase letter
                    if( ( eventwingame.key.keysym.unicode >= (Uint16)'a' ) && ( eventwingame.key.keysym.unicode <= (Uint16)'z' ) )
                    {
                        //Append the character
                        temp[l] = (char)eventwingame.key.keysym.unicode;
                        jogador.nome[l] = (char)eventwingame.key.keysym.unicode;
                        printf("%c\n",temp[l]);
                        l++;
                    }
                }
                    //If backspace was pressed and the string isn't blank
                    if( ( eventwingame.key.keysym.sym == SDLK_BACKSPACE ) && ( l != 0 ) )
                    {
                        //Remove a character from the end
                        l--;
                        temp[l]='\0';
                        jogador.nome[l]='\0';
                    }
                    if( ( eventwingame.key.keysym.sym == SDLK_RETURN ) && ( l != 0 ) )
                    {
                        temp[l]='\0';
                        jogador.nome[l] ='\0';

                        jogorodando = 1;
                        faserodando = 1;
                        contin_wingame = 1;
                        wingame = 0;
                    }

                    if (eventwingame.type == SDL_QUIT){
                        jogorodando = 1;
                        faserodando = 1;
                        sairjogo = 1;
                        contin_wingame = 1;
                        wingame = 0;
                        break;
                    }

                    //CRIA O TEXTO QUE VAI APARECER NA TELA
                    textrecord = TTF_RenderText_Solid( font_pontos, temp, textCorAmarelo );
            }
        }

        apply_surface( 250, 635, textrecord, screen, NULL );

        SDL_Flip(screen);
        apply_surface( 0, 0, fundowingame, screen, NULL );
    }


    for(i=1;temp[i]!='\0';i++){
        rec1.nome[i-1] = temp[i-1];
    }
    //fgets(rec1.nome, MAX_NOME, stdin);

    rec1.nome[strlen(rec1.nome) - 1] = '\0';

    //printf("Pontuação:");
    rec1.pontuacaorecord = pontuacaototaljogador;

    insere(&array, rec1);

    if((p_arquivo = fopen(nome_arquivo, "w")) == NULL)
    {
        perror("fopen:");
        return 1;
    }

    fwrite(&array, sizeof(ARRAY), 1, p_arquivo);
    fclose(p_arquivo);

    pontuacaototaljogador = 0;
}



    }





if(instrucoes == 1){    
    contin_instrucoes = 0;
    while(contin_instrucoes == 0)
    {
        while (SDL_PollEvent(&eventinstrucoes))
        {
            // check for messages
            switch (eventinstrucoes.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                jogorodando = 1;
                faserodando = 1;
                sairjogo = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {
                    if (eventinstrucoes.key.keysym.sym == SDLK_RETURN){
                        jogorodando = 1;
                        faserodando = 1;
                        contin_instrucoes = 1;
                        instrucoes = 0;
                    }
                }
            } // end switch
        }
        SDL_Flip(screen);
        apply_surface( 0, 0, fundoinstrucoes, screen, NULL );
    }
}




if(recordes == 1){
    contin_recordes = 0;
    while(contin_recordes == 0)
    {
        
        while( SDL_PollEvent( &eventrecordes ) )
        {

            // check for messages
            switch (eventrecordes.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
            {
                jogorodando = 1;
                faserodando = 1;
                sairjogo = 1;
                break;
            }

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    if (eventrecordes.key.keysym.sym == SDLK_RETURN){
                        jogorodando = 1;
                        faserodando = 1;
                        contin_recordes = 1;
                        recordes = 0;
                    }
                }
            } // end switch
        }

        for(i = 0; i < tamanho(&array); i++){
            recorde = elemento(&array, i);
            sprintf(vaiblitar,"%d. %s : %d pts", i+1, recorde.nome, recorde.pontuacaorecord);
            text_vaiblitar = TTF_RenderText_Solid( font_pontos, vaiblitar, textCorAmarelo );
            apply_surface( 350, 115 + (i*42), text_vaiblitar, screen, NULL );
        }
        SDL_Flip(screen);
        apply_surface( 0, 0, fundorecordes, screen, NULL );
    }
}






    }


    SDL_FreeSurface( text_pontuacao );
    SDL_FreeSurface( text_vidas );
    SDL_FreeSurface( text_raiobomb );
    SDL_FreeSurface( text_cronometro );
    SDL_FreeSurface( text_faladn );
    SDL_FreeSurface( blocoind );
    SDL_FreeSurface( player );
    SDL_FreeSurface( alienogre );
    SDL_FreeSurface( alienradio );
    SDL_FreeSurface( iconstrip );
    SDL_FreeSurface( iconclub );
    SDL_FreeSurface( blocodes );
    SDL_FreeSurface( imgcaiexp );
    SDL_FreeSurface( imgbomb );
    SDL_FreeSurface( imgexp );
    SDL_FreeSurface( imgpkplut );
    SDL_FreeSurface( imgpkvida );
    SDL_FreeSurface( imgpkclub );
    SDL_FreeSurface( imgburaco );
    SDL_FreeSurface( fundo );
    SDL_FreeSurface( fundoperdeujogo );
    SDL_FreeSurface( fundoinstrucoes );
    SDL_FreeSurface( fundorecordes );
    SDL_FreeSurface( fundofimfase );
    SDL_FreeSurface( fundopause );
    SDL_FreeSurface( fundowingame );
    SDL_FreeSurface( seletor );
    SDL_FreeSurface( fundomenu );
    SDL_FreeSurface( fundopreto );
    SDL_FreeSurface( fundocreditos );


/*

    free(dn_pointer);
    free(bomb_pointer);
    free(exp_cent_pointer);
    free(exp_cim_pointer);
    free(exp_esq_pointer);
    free(exp_bai_pointer);
    free(exp_dir_pointer);
    free(exp_cimfim_pointer);
    free(exp_esqfim_pointer);
    free(exp_baifim_pointer);
    free(exp_dirfim_pointer);
    free(caiexp_pointer);
    free(inia_pointer);
    free(inib_pointer);
    free(inic_pointer);
    free(inid_pointer);
*/

    printf("Fechamento do Jogo\n");
    return 0;
}




RECORDE elemento(ARRAY *array, int posicao)
{
    return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
    return array->n;
}

void insere(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);
        
        if(menor_recorde.pontuacaorecord >= recorde.pontuacaorecord)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            insere(array, recorde);
            return;
        }
    }
    
    sort(array);
}

void remove_posicao(ARRAY *array, int posicao)
{
    if(tamanho(array) == 0)
    {
        return;
    }
    else if(tamanho(array) == 1)
    {
        array->n -= 1;
        return;
    }
    else
    {
        array->n -= 1;
        array->vetor[posicao] = array->vetor[tamanho(array)];
    }
    
    sort(array);
}

/*
void imprime(ARRAY *array)
{
    int i;
    char vaiblitar[50];
    SDL_Surface *text_vaiblitar = NULL;
    RECORDE recorde;

    for(i = 0; i < tamanho(array); i++)
    {
        recorde = elemento(array, i);
        sprintf(vaiblitar,"%d- %s: %d pts\n", i+1, recorde.nome, recorde.pontuacaorecord);
        text_vaiblitar = TTF_RenderText_Solid( font_pontos, vaiblitar, textColorCinza );
        apply_surface( 400, 300, text_vaiblitar, screen, NULL );
    }
}*/

void sort(ARRAY *array)
{
    bubble_sort(array->vetor, array->n);
}

void bubble_sort(RECORDE list[], int n)
{
    int i, j;
    RECORDE swap;

    for(i = 0 ; i < ( n - 1 ); i++)
    {
        for(j = 0 ; j < n - i - 1; j++)
        {
            if(list[j].pontuacaorecord < list[j+1].pontuacaorecord)
            { 
                swap = list[j];
                list[j] = list[j+1];
                list[j+1] = swap;
            }
        }
    }
}