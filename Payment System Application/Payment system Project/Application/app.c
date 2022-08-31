#include "../Server/server.h"

//Invalid card user story

void appStart(void)
{
	ST_cardData_t card1 =
	{
		.cardHolderName = 0,
		.primaryAccountNumber = 0,
		.cardExpirationDate = 0
	};
	ST_cardData_t* card1_ptr = &card1;
	EN_cardError_t cardError;
//***************************************************

	ST_terminalData_t terminalData =
	{
		.transAmount = 0,
		.maxTransAmount = 0,
		.transactionDate = 0
	};
	ST_terminalData_t* terminalData_ptr = &terminalData;
	EN_terminalError_t terminalError;

	EN_serverError_t ServerError;
//**************************************************
	cardError = getCardHolderName(card1_ptr);

	if (cardError == WRONG_NAME)
	{
		printf("WRONG_NAME Format\n");
		return 0;
	}
	else
		printf("Right Name Format\n");
//****************************************************
	cardError = getCardExpiryDate(card1_ptr);
	if (cardError == WRONG_EXP_DATE)
	{
		printf("Wrong Expiry Date Format\n");
		return 0;
	}
	else
		printf("Right Expiry Date Format\n");
//***************************************************
	cardError = getCardPAN(card1_ptr);
	if (cardError == WRONG_PAN)
	{
		printf("Wrong Card PAN Format \"alphanumeric character and Length are wrong\"\n");
		return 0;
	}
	else
		printf("Right Card PAN Format \"alphanumeric character and Length are right\"\n");
	
//***************************************************************************************
	terminalError = isValidCardPAN(card1_ptr);
	if (terminalError == INVALID_CARD)
	{
		printf("Invalid Card : PAN is inValid \"PAN is not a Luhn number\"\n");
		return 0;
	}
	else
		printf("Valid Card :  PAN is Valid \"PAN is a Luhn number\"\n");
//***************************************************************************
	terminalError = getTransactionDate(terminalData_ptr);
	if (terminalError == WRONG_DATE)
	{
		printf("Wrong Transaction Date\n");
		return 0;
	}
	else
		printf("Right Transaction Date\n");
//***************************************************************
	terminalError = isCardExpired(card1_ptr, terminalData_ptr);
	if (terminalError == EXPIRED_CARD)
	{
		printf("Expired Card\n");
		return 0;
	}
	else
		printf("Valid Card\n");

//***************************************************************
	terminalError = getTransactionAmount(terminalData_ptr);
	if (terminalError == INVALID_AMOUNT)
	{
		printf("InValid Amount\n");
		return 0;
	}
	else
		printf("Valid Amount [Amount > 0]\n");
//************************************************************
	terminalError = setMaxAmount(terminalData_ptr);
	if (terminalError == INVALID_MAX_AMOUNT)
	{
		printf("Max Amount is invalid\n");
	}
	else
		printf("Max Amount is valid\n");
	
//******************************************************************
	terminalError = isBelowMaxAmount(terminalData_ptr);
	if (terminalError == EXCEED_MAX_AMOUNT)
	{
		printf("Transaction Amount exeeded the Max Amount\n");
		return 0;
	}
	else
		printf("Transaction Amount is Below the Max Amount\n");
//****************************************************************************
	ServerError=isValidAccount(card1_ptr);
	if(ServerError== DECLINED_STOLEN_CARD)
		printf("DECLINED STOLEN CARD: Invalid Account\n");
	else
		printf("Valid Account\n");
//****************************************************************************
	ServerError=isAmountAvailable(terminalData_ptr);
	if (ServerError == LOW_BALANCE)
		printf("LOW BALANCE: Amount is not Availavble\n");
	else
		printf("Amount is Availavble\n");
//****************************************************************************
	ServerError = saveTransaction(tansactionsDB, card1_ptr, terminalData_ptr);
	if (ServerError == SAVING_FAILED)
		printf("Saving Transaction failed\n");
	else
		printf("Saving Transaction suceeded\n");
//****************************************************************************
	ServerError = recieveTransactionData(tansactionsDB, terminalData_ptr);
	if(ServerError== DECLINED_STOLEN_CARD)
		printf("DECLINED_STOLEN_CARD\n");
	else if (ServerError == DECLINED_INSUFFECIENT_FUND)
		printf("DECLINED_INSUFFECIENT_FUND\n");
	else if (ServerError == INTERNAL_SERVER_ERROR)
		printf("INTERNAL_SERVER_ERROR\n");
	else if (ServerError == APPROVED)
		printf("APPROVED\n");
//**************************************************************************
	uint32_t Desired_transactionSequenceNumber = 0;
	printf("\nPlease Enter Your Desired Transaction Number\n");
	scanf("%d", &Desired_transactionSequenceNumber);
	ServerError = getTransaction(Desired_transactionSequenceNumber, tansactionsDB);
	if (ServerError == TRANSACTION_NOT_FOUND)
		printf("TRANSACTION_NOT_FOUND\n");

}
