//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"
#include <string.h>
#include <math.h>

//Compare two pointer values
void assert_reg(iRegister *e, iRegister *r){
	if(e->content != r->content){
		printf("\nThe content is not the same! Expected: %d Observed: %d",e->content, r->content);
	}
}
//Compare two ints
void assert_INT(int e,int r){
	if(e != r){
		printf("\n Test is not the same! Expected: %d Observed: %d", e, r);
	}
}
//Test the assignNibble
void unit_assignNibble(int val, int pos, iRegister r, int expected){
	r = {0};
	assignNibble(val, pos, &r);
	assert_INT(expected, r.content);
}

void unit_test(iRegister r){
	iRegister e;
	printf("\nStart tests \n");
	int i;
	
	/*Test resetBit*/
	r = {15};
	int val = 15;
	for(i = 0; i <4; i++){
		val = val - pow(2,i);
		resetBit(i, &r);
		assert_INT(val, r.content);
	}
	
	/*Test setBit*/
	for(i = 0; i <4; i++){
		r = {0};
		setBit(i, &r);
		assert_INT(pow(2,i), r.content);
	}
	/*Test setAll*/
	for(i = 0; i <4; i++){
		r = {(int)pow(2,i)};
		setAll(&r);
		assert_INT(~0, r.content);
	}

	/*Test getBit*/
	r = {35};
	int temp[6] = {1,0,0,0,1,1};
	for(i = 0; i <5; i++){
		assert_INT(temp[5-i], getBit(i,&r));
	}

	/*Test assignNibble*/
	unit_assignNibble(1, 1, r, 1);
	unit_assignNibble(2, 1, r, 16);
	unit_assignNibble(3, 1, r, 256);
	unit_assignNibble(4, 1, r, 4096);
	

	/*Test getNibble*/
	r = {3};
	assert_INT(3,getNibble(1, &r));
	r = {7};
	assert_INT(7,getNibble(1, &r));
	r = {192};
	assert_INT(12,getNibble(2, &r));
	r = {1024};
	assert_INT(4,getNibble(3, &r));
	
	/*Test reg2str*/
	for(i = 0; i < 4; i++){
		e = {i* 54};
		r = {i* 54};
		assert_reg(&e, &r);
	}
	/*Test shiftRight*/
	r = {256};
	e = {128};
	shiftRight(1, &r);
	assert_reg(&e,&r);
	
	r = {64};
	e = {32};
	shiftRight(1, &r);
	assert_reg(&e,&r);
	
	/*Test shiftLeft*/
	r = {128};
	e = {256};
	shiftLeft(1, &r);
	assert_reg(&e,&r);
	
	r = {32};
	e = {64};
	shiftLeft(1, &r);
	assert_reg(&e,&r);
	
}
int main (){
	iRegister r;

	/* Put all your test cases for the implemented functions here */	
	printf("\nAddress_R: %p\n", &r);
	printf("Memory: %s", reg2str(r));
	printf("\nValue in Memory: %d", r.content);
	
	unit_test(r);
	return 0;
}