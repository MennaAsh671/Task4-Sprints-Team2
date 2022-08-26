#include"server.h"
int account_no = 0;

void initialize_account_transaction_numbers_array() {
	for (int i = 0; i < 255; i++) {
		account_transaction_numbers[i] = 0;
	}
}

EN_transState_t receiveTransactionData(ST_transaction_t* transData) {
	int account_validity;
	printf("\nPlease enter your account balance: ");
	scanf("%f", &Accounts[account_no].balance);
	
	for (int i = 0; i < 255; i++) {
		ST_cardData_t cardData = transData->cardHolderData;
		account_validity = isValidAccount(cardData, Accounts[i]);
		if (account_validity == SERVER_OK) {
			account_no = i;
			break;
		}
	}

	if (account_validity == ACCOUNT_NOT_FOUND)
		return FRAUD_CARD;
	else if (isAmountAvailable(transData->terminalData) == LOW_BALANCE) {
		return DECLINED_INSUFFICIENT_FUND;
	}
	else if (transData->transState == BLOCKED) {
		return DECLINED_STOLEN_CART;
	}

	
	Accounts[account_no].balance = (Accounts[account_no].balance) - (transData->terminalData.transAmount);
	return APPROVED;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t termData) {
	if (termData.transAmount > Accounts[account_no].balance) {
		return LOW_BALANCE;
	}

	return SERVER_OK;
}

EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t accountReference) {
	int j;
	int flag2 = 1;
	for (j = 0; j < 16; j++) {
		if (cardData.primaryAccountNumber[j] != accountReference.primaryAccountNumber[j])
			flag2 = 0;
	}
	if (flag2 == 0)
		return ACCOUNT_NOT_FOUND;

	return SERVER_OK;
}



EN_serverError_t saveTransaction(ST_transaction_t* transData) {

	transactions[account_no].cardHolderData = transData->cardHolderData;
	transactions[account_no].terminalData = transData->terminalData;
	transactions[account_no].transState = transData->transState;

	transData->transactionSequenceNumber = ++account_transaction_numbers[account_no];

	transactions[account_no].transactionSequenceNumber = transData->transactionSequenceNumber;

	if (receiveTransactionData(transData) == APPROVED)
		printf("\nTransaction state: approved");

	else if (receiveTransactionData(transData) == FRAUD_CARD)
		printf("\nTransaction state: declined due to a fraud card");

	else if (receiveTransactionData(transData) == DECLINED_INSUFFICIENT_FUND)
		printf("\nTransaction state: declined due to an insufficient fund");

	else if (receiveTransactionData(transData) == DECLINED_STOLEN_CART)
		printf("\nTransaction state: declined due to a stolen cart");

	else if (receiveTransactionData(transData) == INTERNAL_SERVER_ERROR)
		printf("\nTransaction state: declined due to an internal server error");

	if (getTransaction(transactions[account_no].transactionSequenceNumber, transData) == TRANSACTION_NOT_FOUND)
		return SAVING_FAILED;
	return SERVER_OK;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	if (transactionSequenceNumber < transData->transactionSequenceNumber)
		return TRANSACTION_NOT_FOUND;
	return SERVER_OK;
}


