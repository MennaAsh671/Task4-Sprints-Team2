#include "terminal.h"
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable : 4996)



EN_terminalError_t getTransactionDate(ST_terminalData_t* termDate)
{
	printf("\nPlease enter the transaction date in the form DD/MM/YYYY: ");
	char expression[11];
	for (int i = 0; i < 11; i++) {
		expression[i] = 'X';
	}
	scanf("%s", expression);
	if (expression == NULL) {
		printf("\nWrong Date");
		return WRONG_DATE;
	}
	for (int i = 0; i < 11; i++) {
		if (expression[i] != 'X') {
			continue;
		}
		else {
			printf("\nWrong Date");
			return WRONG_DATE;
		}
	}


	for (int i = 0; i < 11; i++) {
		termDate->transactionDate[i] = expression[i];

	}
	
	printf("\nTransaction Completed\n");
	return Terminal_OK;

}
int convertToIntTransaction(ST_terminalData_t termData, int end, int start) {
	int transNum = 0;
	int count = 0;
	for (int i = end; i >= start; i--) {
		transNum = transNum + (termData.transactionDate[i] - '0') * pow(10, count);
		count++;
	}
	return transNum;
}
int convertToIntExpiration(ST_cardData_t cardData, int end, int start) {
	int ExNum = 0;
	int count = 0;
	for (int i = end; i >= start; i--) {
		ExNum = ExNum + (cardData.cardExpirationDate[i] - '0') * pow(10, count);
		count++;
	}
	return ExNum;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	int transYear = convertToIntTransaction(termData, 9, 6);
	int transMonth = convertToIntTransaction(termData, 4, 3);
	int transDay = convertToIntTransaction(termData, 1, 0);
	int ExYear = convertToIntExpiration(cardData, 4, 3) + 2000;
	int ExMonth = convertToIntExpiration(cardData, 1, 0);

	if (ExYear > transYear) {
		
		return Terminal_OK;
	}
	else if (ExYear < transYear) {
		
		return EXPIRED_CARD;
	}
	else {
		if (ExMonth > transMonth) {
			
			return Terminal_OK;
		}
		else if (ExMonth < transMonth) {
			
			return EXPIRED_CARD;
		}
	}
	
	return Terminal_OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Please enter the transaction amount: ");
	float amount = 0;
	scanf("%f", &amount);
	if (amount == 0 || amount < 0) {
		return INVALID_AMOUNT;
	}
	else {
		termData->transAmount = amount;
		
		return Terminal_OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		
		return EXCEED_MAX_AMOUNT;
	}
	else {
		
		return Terminal_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Please enter the maximum transaction amount: ");
	float amount = 1000;
	scanf("%f", &amount);
	if (amount == 0 || amount < 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		termData->maxTransAmount = amount;
		
		return Terminal_OK;
	}
}

