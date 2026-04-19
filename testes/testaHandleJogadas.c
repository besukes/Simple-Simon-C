#include "CUnit/Basic.h"
#include <stdio.h>
#include"simpleSimon.h"

void testa_desfazJogadaBasica(void)
{
    int matrizCartaJogo[10][21] = {0};
    undoMove undo = {0};
    SDL_Texture *imgs[10][21] = {NULL};

    matrizCartaJogo[2][0] = 3;
    matrizCartaJogo[5][0] = 2;
    matrizCartaJogo[5][1] = 11;

    undo.isp = 0;
    undo.ultimasJogadas[0].antigaPos = 2;
    undo.ultimasJogadas[0].novaPos = 5;
    undo.ultimasJogadas[0].cartasMovidas = 1;
    undo.ultimasJogadas[0].cartas[0] = 11;
    

    desfazJogadaBasica(matrizCartaJogo , &undo , imgs);

    CU_ASSERT_EQUAL(matrizCartaJogo[5][0] , 0);
    CU_ASSERT_EQUAL(matrizCartaJogo[2][0] , 4);
    CU_ASSERT_EQUAL(matrizCartaJogo[2][4] , 11);
}  
void testa_desfazerFilaCompleta(void)
{
    int matrizCartaJogo[10][21] = {0};
    undoMove undo = {0};
    SDL_Texture *imgs[10][21] = {NULL};

    undo.isp = 0;
    undo.ultimasJogadas[0].antigaPos = 0;
    undo.ultimasJogadas[0].novaPos = 1;
    undo.ultimasJogadas[0].cartasMovidas = 3;
    undo.ultimasJogadas[0].filaPreenchida = 1;

    for(int i = 0 ; i < 13 ; i++)
    undo.ultimasJogadas[0].cartas[i] = 13 - i;

    matrizCartaJogo[1][0] = 0;
    matrizCartaJogo[0][0] = 5;

    desfazerFilaCompleta(matrizCartaJogo , &undo , imgs);

    CU_ASSERT_EQUAL(matrizCartaJogo[1][0] , 10);
    CU_ASSERT_EQUAL(matrizCartaJogo[0][0] , 8);
    CU_ASSERT_EQUAL(matrizCartaJogo[1][1] , 13);
    CU_ASSERT_EQUAL(matrizCartaJogo[0][8] , 1);
}
void testa_rowNaoCompleta(void)
{
    undoMove undo = {0};
    UserBase args = {0};
    undo.isp = 0;

    args.filaSelecionada = 2;
    args.numCartasSelecionadas = 2;
    args. cartas[0] = 11;
    args.cartas[1]= 10;
    
    rowNaoCompleta(5, &args , &undo);

    CU_ASSERT_EQUAL(undo.ultimasJogadas[0].novaPos , 5);
    CU_ASSERT_EQUAL(undo.ultimasJogadas[0].filaPreenchida , 0);
    CU_ASSERT_EQUAL(undo.ultimasJogadas[0].cartas[0] , 11)
}
void testa_rowCompleta(void)
{
    int matrizCartaJogo[10][21] = {0};
    SDL_Texture *imgs[10][21] = {NULL};
    undoMove undo = {0};
    UserBase args = {0};

    matrizCartaJogo[4][0] = 13;
    for(int i = 0 ; i < 13 ; i++)
    matrizCartaJogo[4][i+1] = 13 - i;

    args.filaSelecionada = 0;
    args. numCartasSelecionadas = 1;

    rowCompleta(matrizCartaJogo, imgs , 4 , &args, &undo);

    CU_ASSERT_EQUAL(undo.ultimasJogadas[0].filaPreenchida  , 1);
    CU_ASSERT_EQUAL(undo.ultimasJogadas[0].cartas[0]  , 13);
    CU_ASSERT_EQUAL(undo.ultimasJogadas[0].cartas[12]  , 1);
}
void testa_updateEstado(void)
{
    int matrizCartaJogo[10][21] = {0};
    UserBase args = {0};
    SDL_Texture *imgs[10][21] = {NULL};

    matrizCartaJogo[0][0] = 5;
    matrizCartaJogo[0][1] = 52;
    matrizCartaJogo[0][2] = 51;
    matrizCartaJogo[0][3] = 16;
    matrizCartaJogo[0][4] = 15;
    matrizCartaJogo[0][5] = 14;

    updateEstado(0 , 3 , matrizCartaJogo , &args , imgs);

    CU_ASSERT_EQUAL(args.numCartasSelecionadas , 3);
    CU_ASSERT_EQUAL(matrizCartaJogo[0][0] , 2);
    CU_ASSERT_EQUAL(args.cartas[0] , 16);
    CU_ASSERT_EQUAL(args.cartas[1] , 15);
    CU_ASSERT_EQUAL(args.cartas[2] , 14);
}
void testa_colocaArrayCartas(void)
{
    int matrizCartaJogo[10][21] = {0};
    UserBase args = {0};
    SDL_Texture *imgs[10][21] = {NULL};

    matrizCartaJogo[4][0] = 1;
    matrizCartaJogo[4][1] = 12;
    args.numCartasSelecionadas = 1;
    args.cartas[0] = 11;

    colocaArrayCartas(matrizCartaJogo, &args , imgs , 4);

    CU_ASSERT_EQUAL(matrizCartaJogo[4][0] , 2);
    CU_ASSERT_EQUAL(matrizCartaJogo[4][2] , 11);
}
void testa_jogadaNaoRealizada(void)
{
    int matrizCartaJogo[10][21] = {0};
    UserBase args = {0};
    SDL_Texture *imgs[10][21] = {NULL};

    matrizCartaJogo[7][0] = 3;
    matrizCartaJogo[7][1] = 52;
    matrizCartaJogo[7][2] = 51;
    matrizCartaJogo[7][3] = 11;

    args.filaSelecionada = 7;
    args.numCartasSelecionadas = 2;
    args.cartas[0] = 10;
    args.cartas[1] = 9;

    jogadaNaoRealizada(matrizCartaJogo, 1 , 0 , &args , imgs);

    CU_ASSERT_EQUAL(matrizCartaJogo[7][0], 5);
    CU_ASSERT_EQUAL(matrizCartaJogo[7][4], 10);
    CU_ASSERT_EQUAL(matrizCartaJogo[7][5], 9);
    CU_ASSERT_EQUAL(args.filaSelecionada , -1);
    CU_ASSERT_EQUAL(args.numCartasSelecionadas , 0);
    CU_ASSERT_EQUAL(args.jogada , invalida);
}
void testaHandleJogadas (CU_pSuite * suite){
    CU_add_test(*suite,"testa_desfaz_jogada_basica",testa_desfazJogadaBasica);
    CU_add_test(*suite,"testa_desfazer_fila_completa",testa_desfazerFilaCompleta);
    CU_add_test(*suite,"testa_row_nao_completa",testa_rowNaoCompleta);
    CU_add_test(*suite,"testa_row_completa",testa_rowCompleta);
    CU_add_test(*suite,"testa_update_estado",testa_updateEstado);
    CU_add_test(*suite,"testa_coloca_array_cartas",testa_colocaArrayCartas);
    CU_add_test(*suite,"testa_jogada_nao_realizada",testa_jogadaNaoRealizada);
}