#include "card.h"
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter Card Holder name: ");
	char exp[35];
	int count = 0;
	for (int i = 0; i < 35; i++)
	{
		exp[i] = '0';
	}

	fgets(exp, 35, stdin);

	for (int i = 0; i < 35; i++)
	{
		if (exp[i] != '0')
			count++;
	}
	int n = count - 2;

	if ((n) >= 20 && (n) <= 24)
	{
		printf("\nCorrect Name!");
		//return CARD_OK;
		for (int i = 0; i < 25; i++)
		{
			cardData->cardHolderName[i] = exp[i];

		}
		return CARD_OK;
	}
	else
	{
		printf("\nWrong Name");
		return WRONG_NAME;

	}

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

	printf("\nPlease enter Card ExpiryDate in this Format MM/YY: ");
	char exp[20];
	int count1 = 0;
	for (int i = 0; i < 20; i++)
	{
		exp[i] = 'm';
	}

	fgets(exp, 20, stdin);

	for (int i = 0; i < 20; i++)
	{
		if (exp[i] != 'm')
			count1++;
	}
	int m = count1 - 2;

	if (exp == NULL) {
		printf("\nWrong Date");
		return WRONG_EXP_DATE;
	}
	else if ((m) == 5 && exp[2] == '/')
	{
		printf("\nCorrect Date!");

		for (int i = 0; i < 6; i++)
		{
			cardData->cardExpirationDate[i] = exp[i];
		}
		return CARD_OK;
	}
	else
	{
		printf("\nWrong Date");
		return WRONG_EXP_DATE;
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("\nPlease enter Card PAN: ");
	char exp[35];
	int count = 0;
	for (int i = 0; i < 35; i++)
	{
		exp[i] = 'x';
	}

	fgets(exp, 35, stdin);

	for (int i = 0; i < 35; i++)
	{
		if (exp[i] != 'x')
			count++;
	}

	int x = count - 2;


	if ((x) >= 16 && (x) <= 19)
	{
		printf("\nCorrect PAN!");
		for (int i = 0; i < 20; i++)
		{
			cardData->primaryAccountNumber[i] = exp[i];
		}
		return CARD_OK;
	}
	else
	{
		printf("\nWrong PAN");
		return WRONG_PAN;
	}


}

/*int main()
{
	ST_cardData_t cardData;
	getCardHolderName(&cardData);
	getCardExpiryDate(&cardData);
	getCardPAN(&cardData);
}*/