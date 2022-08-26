#include"app.h"
#pragma warning(disable : 4996)


ST_cardData_t cardData;
ST_accountsDB_t accountReference;
ST_transaction_t transData;

void appStart(void)
{
	/*ST_terminalData_t termData;
	ST_cardData_t cardData;
	ST_accountsDB_t accountReference;*/
	if (getCardHolderName(&cardData) == CARD_OK && getCardExpiryDate(&cardData) == CARD_OK && getCardPAN(&cardData) == CARD_OK)
	{
		if (getTransactionDate(&transData.terminalData) == Terminal_OK)
		{
			if (isCardExpired(cardData, transData.terminalData) == Terminal_OK)
			{
				setMaxAmount(&transData.terminalData);
				if (getTransactionAmount(&transData.terminalData) == Terminal_OK && isBelowMaxAmount(&transData.terminalData) == Terminal_OK)
				{
					if (isValidAccount(cardData, accountReference) == SERVER_OK)
					{
						int state = receiveTransactionData(&transData);
						if (state == APPROVED)
							printf("\nBalance updated");
						else if(state == DECLINED_STOLEN_CART)
							printf("\nYou are using a stolen card");
						else if (state == DECLINED_INSUFFICIENT_FUND)
							printf("\nNot enought balance");
					}
					else
						printf("\nInvalid account");
				}
				else
					printf("\nAmount Exceeded");
			}
			else
				printf("\nCard Expired");
		}
		else
			printf("\nWrong Transaction Date");
		
	}
	else
		printf("\nWrong Information");
}

int main()
{
	//termData.maxTransAmount = 200;

	/*for (int i = 0; i < 16; i++) {
		cardData.primaryAccountNumber[i] = '1';
	}*/

	for (int i = 0; i < 16; i++) {
		accountReference.primaryAccountNumber[i] = '1';
	}


	

	transData.transState = BLOCKED;
	appStart();


	/*ST_cardData_t cardData;
	getCardHolderName(&cardData);*/
}