#include "CUnit/Basic.h"
#include <stdio.h>
#include"simpleSimon.h"

void testaValorCarta(void){
    CU_ASSERT_EQUAL(valorCarta(52),13);
    CU_ASSERT_EQUAL(valorCarta(12),12);
    CU_ASSERT_EQUAL(valorCarta(40),1);
    CU_ASSERT_EQUAL(valorCarta(23),10);
    CU_ASSERT_EQUAL(valorCarta(36),3);
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

}

void testaFBase(CU_pSuite * suite){
	CU_add_test(*suite,"testa_valor_carta",testaValorCarta);
    CU_add_test(*suite,"testa_verifica_vitoria",testaVerificaVitoria);
    CU_add_test(*suite,"testa_carta_pegavel",testaCartaPegavel);
}