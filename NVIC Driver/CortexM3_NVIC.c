/*
 * CortexM3_NVIC.c
 *
 *  Created on: Aug 2, 2023
 *      Author: Ahmed Gaber
 */

#include "CortexM3_NVIC.h"

/*
 * Note:
 * 		should >=0 positive number
 * 		We could use if statments instead of using this equation
 * 		Ex:if(0 < IRQn && IRQn <32){ NVIC->ISER[0]= (1 << ((uint32_t)IRQn & 0xF1))}
 */
void NVIC_EnableIRQ(IRQn_Type IRQn){
	if((uint32_t)IRQn >= 0){
		// 39=100111 >>5 =1  means (first array)
		//In mask part 0xf1=31= 11111 & 100111 =000111 = 7 we choose 7th bit
		NVIC->ISER[(uint32_t)IRQn >>5 ] = (1UL << ((uint32_t)IRQn & 0x1F));
	}
}

void NVIC_DisableIRQ(IRQn_Type IRQn){
	if((uint32_t)IRQn >= 0){
		NVIC->ICER[(uint32_t)IRQn >> 5 ] = (1 << ((uint32_t)IRQn & 0x1F));
	}
}

void NVIC_SetPendingIRQ(IRQn_Type IRQn){
	if((uint32_t)IRQn >= 0){
			NVIC->ISPR[(uint32_t)IRQn >> 5 ] = (1 << ((uint32_t)IRQn & 0x1F));
		}
}

void NVIC_ClearPendingIRQ(IRQn_Type IRQn){
	if((uint32_t)IRQn >= 0){
			NVIC->ICPR[(uint32_t)IRQn >> 5 ] = (1UL << ((uint32_t)IRQn & 0x1F));
		}
}

//get the value of the Active
uint32_t NVIC_GetActive(IRQn_Type IRQn){
	if(((NVIC->ICPR[(uint32_t)IRQn >> 5 ]) & (1UL << ((uint32_t)IRQn & 0x1F)) ) !=0){
		return 1UL;
	}
	else{
		return 0UL;
	}
}

