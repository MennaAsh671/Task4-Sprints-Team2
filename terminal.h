
#ifndef TERMINAL_H
#define TERMINAL_H

#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "card.h"


/*typedef struct ST_cardData_t {
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];

}ST_cardData_t;*/

typedef struct ST_terminalData_t {
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t {

	Terminal_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termDate);
//22/22/2222
//01/34/6789
int convertToIntTransaction(ST_terminalData_t termData, int end, int start);
// MM/YY
// 01/34
int convertToIntExpiration(ST_cardData_t cardData, int end, int start);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);
//EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);


#endif