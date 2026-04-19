#include"simpleSimon.h"
#include "testesMain.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <CUnit/Basic.h>
//CU ASSERT EQUAL
//CU_add_teste


int initTestes(void){
	CU_pSuite pSuite = CU_add_suite("simpleSimon_tests",NULL,NULL);
    if(NULL == pSuite) return CU_get_error();
	testaDicas(&pSuite);
	testaFBase(&pSuite);
	testaHandleJogadas(&pSuite);
	return CUE_SUCCESS;
}

int main(void){
	SDL_Init(SDL_INIT_VIDEO);
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
