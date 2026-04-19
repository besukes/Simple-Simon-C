#include "CUnit/Basic.h"
#include <stdio.h>
#include"simpleSimon.h"

void testa_jogadorQuerDica(void){
    UserBase args;
    int linha = 1 , linha2 = 2;
    jogadorQuerDica(&args,linha);
    CU_ASSERT_EQUAL(args.dica.querDica,1);
    CU_ASSERT_EQUAL(args.dica.filas[0],linha);
    jogadorQuerDica(&args,linha2);
    CU_ASSERT_EQUAL(args.dica.filas[1],linha2);
}


void testa_ColocaDicaUtilizador(void){
    int mj[10][21] = {{}};
    mj[0][0] = 2 ; mj[1][0] = 1; mj[2][0] = 1;
    mj[0][1] = 3; mj[0][2] = 2;
    mj[1][1] = 4;
    mj[2][1] = 5 ;
    UserBase args;
    colocaDicaUtilizador(mj,&args);
    CU_ASSERT_EQUAL(args.dica.filas[0],0);
    CU_ASSERT_EQUAL(args.dica.filas[1],1);
}

void testaDicas (CU_pSuite * suite){
    CU_add_test(*suite,"testa_atualizaEstadoDica",testa_jogadorQuerDica);
}