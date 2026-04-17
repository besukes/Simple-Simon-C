#include "CUnit/Basic.h"
#include <stdio.h>
#include"simpleSimon.h"
//CU ASSERT EQUAL


int initTestes(){
	CU_pSuite pSuite = CU_add_suite("golf_tests",NULL,NULL);
        if(NULL == pSuite) return CU_get_error();
        CU_add_test(pSuite, "testa_ValorCarta", /*//////////*/);
        CU_add_test(pSuite, "testa_VerificaVitoria", /*//////////*/);
        CU_add_test(pSuite, "testa_CartaJogavel", /*//////////*/);
        CU_add_test(pSuite, "testa_EfetuaJogada", /*//////////*/);
	CU_add_test(pSuite, "testa_EfetuaJogadaUndo", /*//////////*/);
	CU_add_test(pSuite, "testa_PegaCarta", /*//////////*/);
        CU_add_test(pSuite, "testa_busca_baralho", /*//////////*/);
	//Não é necessário testar as funções de UNDO em si, pois estas são testadas durante o teste do efetuaJogada para o caso jogada=-1
	return CUE_SUCCESS;
}

int main(){
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
	if(CUE_SUCCESS != initTestes()){
		CU_cleanup_registry();
		return CU_get_error();
	}
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
