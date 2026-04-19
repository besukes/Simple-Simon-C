#include "CUnit/Basic.h"
#include <stdio.h>
#include"simpleSimon.h"

void testaValorCarta(void){
    CU_ASSERT_EQUAL(valorCarta(52),13);
    CU_ASSERT_EQUAL(valorCarta(12),12);
    CU_ASSERT_EQUAL(valorCarta(40),1);
    CU_ASSERT_EQUAL(valorCarta(23),10);
    CU_ASSERT_EQUAL(valorCarta(36),10);
    CU_ASSERT_EQUAL(valorCarta(31),5);
    CU_ASSERT_EQUAL(valorCarta(32),6);
    CU_ASSERT_EQUAL(valorCarta(20),7);
}

void testaVerificaVitoria(void){
    int m[10][21] = {{}};
    UserBase args;
    args.jogada=valido;args.screen=jogo;args.numCartasSelecionadas=0;
    verificaVitoria(m,&args);
    CU_ASSERT_EQUAL(args.jogada,vitoria);
    CU_ASSERT_EQUAL(args.screen,win);
    m[0][0] = 1;
    args.jogada=valido;args.screen=jogo;
    verificaVitoria(m,&args);
    CU_ASSERT_EQUAL(args.jogada,valido);
    CU_ASSERT_EQUAL(args.screen,jogo);
}

void testaCartaPegavel(void){
    int mj[10][21] = {{8,13,28,49,20,14,12,11,10},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(cartaPegavel(13,0,mj),0);
    CU_ASSERT_EQUAL(cartaPegavel(28,0,mj),0);
    CU_ASSERT_EQUAL(cartaPegavel(10,0,mj),1);
    CU_ASSERT_EQUAL(cartaPegavel(12,0,mj),1);
}

void testaCartaColocavel(void){
    CU_ASSERT_EQUAL(cartaColocavel(14,13),0);
    CU_ASSERT_EQUAL(cartaColocavel(16,13),0);
    CU_ASSERT_EQUAL(cartaColocavel(52,13),0);
    CU_ASSERT_EQUAL(cartaColocavel(20,6),1);
    CU_ASSERT_EQUAL(cartaColocavel(51,37),1);
    CU_ASSERT_EQUAL(cartaColocavel(49,24),0);
}

void testa_ePosicaoMatriz(void){
    CU_ASSERT_EQUAL(ePosicaoMatriz(4,9),1);
    CU_ASSERT_EQUAL(ePosicaoMatriz(11,1),0);
    CU_ASSERT_EQUAL(ePosicaoMatriz(-1,9),0);
    CU_ASSERT_EQUAL(ePosicaoMatriz(4,-1),0);
    CU_ASSERT_EQUAL(ePosicaoMatriz(9,20),1);
    CU_ASSERT_EQUAL(ePosicaoMatriz(9,21),0);
    CU_ASSERT_EQUAL(ePosicaoMatriz(10,20),0);
    CU_ASSERT_EQUAL(ePosicaoMatriz(5,5),1);
}

void testaResetArgs(void){
    UserBase args;
    args.filaSelecionada=1;
    args.numCartasSelecionadas=10;
    args.mouseButtonDown=1;
    resetArgs(&args);
    CU_ASSERT_EQUAL(args.mouseButtonDown,0);
    CU_ASSERT_EQUAL(args.numCartasSelecionadas,0);
    CU_ASSERT_EQUAL(args.filaSelecionada,-1);
}

void testa_resetDicaArgs(void){
    UserBase args;
    args.dica.querDica=1;
    args.dica.numDicas=9;
    args.dica.timeout=1;
    resetDicaArgs(&args);
    CU_ASSERT_EQUAL(args.dica.querDica,0);
    CU_ASSERT_EQUAL(args.dica.numDicas,0);
    CU_ASSERT_EQUAL(args.dica.timeout,0); 
}


void testa_ultimaCartaPegavel(void){
    int mj[10][21] = {{8,13,28,49,20,14,12,11,10},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(calculaUltimaCartaPegavel(mj,0,8),12);
    int mj1[10][21] = {{8,13,28,49,14,13,12,11,10},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(calculaUltimaCartaPegavel(mj1,0,8),13);
    int mj2[10][21] = {{8,13,28,49,20,14,12,15,1},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(calculaUltimaCartaPegavel(mj2,0,8),1);
}

void testaFilaCompleta(void){
    int mj[10][21] = {{8,13,12,11,10,9,8,7,6,5,4,3,2,1},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(verificaFilaCompleta(mj,0),0);
    int mj1[10][21] = {{13,13,12,11,10,9,8,7,6,5,4,3,2,1},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(verificaFilaCompleta(mj1,0),1);
    int mj2[10][21] = {{13,26,25,24,23,22,21,20,19,18,17,16,15,14},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(verificaFilaCompleta(mj2,0),1);
    int mj3[10][21] = {{18,13,12,11,10,9,8,7,6,5,4,3,2,1,14,15,16,20,18},{},{},{},{},{},{},{},{},{}};
    CU_ASSERT_EQUAL(verificaFilaCompleta(mj3,0),0);
}


void testaFBase(CU_pSuite * suite){
	CU_add_test(*suite,"testa_valor_carta",testaValorCarta);
    CU_add_test(*suite,"testa_verifica_vitoria",testaVerificaVitoria);
    CU_add_test(*suite,"testa_carta_pegavel",testaCartaPegavel);
    CU_add_test(*suite,"testa_carta_colocavel",testaCartaColocavel);
    CU_add_test(*suite,"testa_ePosicaoMatriz",testa_ePosicaoMatriz);
    CU_add_test(*suite,"testa_resetArgs",testaResetArgs);
    CU_add_test(*suite,"testa_resetDicaArgs",testa_resetDicaArgs);
    CU_add_test(*suite,"testa_ultimaCartaPegavel",testa_ultimaCartaPegavel);
    CU_add_test(*suite,"testa_verificaFilaCompleta",testaFilaCompleta);
}