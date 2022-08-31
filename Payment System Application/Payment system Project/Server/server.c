#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<string.h>
#include"../Server/server.h"
static uint32_t transactionSequenceNumber=63819;
static uint32_t i = 0; //i is the index of the cardPAN in the accounts DataBase
EN_serverError_t ValidAccount=-1, AmountAvailable=-1, saveTransactionFlag=-1;
extern ST_cardData_t* card1_ptr;
extern ST_terminalData_t* terminalData_ptr;

EN_transState_t recieveTransactionData(ST_transaction* transData, ST_terminalData_t* termData)
{
	if (ValidAccount == DECLINED_STOLEN_CARD)
	{
		return DECLINED_STOLEN_CARD;
	}
	else if (AmountAvailable == LOW_BALANCE)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransactionFlag == SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}
	else
	{
		printf("Your balance is : %.2f\n", accountsDB[i].balance);

		accountsDB[i].balance -= termData->transAmount; //Update Balance
		printf("Your Tansaction Amount is : %.2f\n", termData->transAmount);
		printf("New balance is : %.2f\n\n", accountsDB[i].balance);

		return APPROVED;
	}

}


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (i = 0; i < 255; i++)
	{
		if (0 == strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber))
		{
			for (int j = 0; j < 20; j++)
			{
				if (0 == strcmp(blockedCards[j].primaryAccountNumber, cardData->primaryAccountNumber))
				{
					ValidAccount = DECLINED_STOLEN_CARD;
					return DECLINED_STOLEN_CARD;
				}
			}
			ValidAccount= Okay;
			return Okay;
		}
	}
	
	ValidAccount = DECLINED_STOLEN_CARD;
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (accountsDB[i].balance >= termData->transAmount)
	{		
		AmountAvailable = Okay;
		return Okay;
	}
	else
	{
		AmountAvailable = LOW_BALANCE;
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction* transData, ST_cardData_t* card1_ptr, ST_terminalData_t* terminalData_ptr)
{
	uint32_t n = 0;
	for (n = 0; n < 255; n++)
	{
		if (tansactionsDB[n].transactionSequenceNumber == 0)
		{
			//Then We found an Empty place in the transaction DataBase with the index n
			strcpy(tansactionsDB[n].cardHolderData.cardHolderName, card1_ptr->cardHolderName);
			strcpy(tansactionsDB[n].cardHolderData.primaryAccountNumber, card1_ptr->primaryAccountNumber);
			strcpy(tansactionsDB[n].cardHolderData.cardExpirationDate, card1_ptr->cardExpirationDate);
			tansactionsDB[n].terminalData.transAmount = terminalData_ptr->transAmount;
			tansactionsDB[n].terminalData.maxTransAmount = terminalData_ptr->maxTransAmount;
			strcpy(tansactionsDB[n].terminalData.transactionDate, terminalData_ptr->transactionDate);

			if (ValidAccount == Okay && AmountAvailable == Okay)
				tansactionsDB[n].transState = APPROVED;
			else if (ValidAccount == DECLINED_STOLEN_CARD)
				tansactionsDB[n].transState = DECLINED_STOLEN_CARD;
			else if (AmountAvailable == LOW_BALANCE)
				tansactionsDB[n].transState = DECLINED_INSUFFECIENT_FUND;

			tansactionsDB[n].transactionSequenceNumber = transactionSequenceNumber;
			transactionSequenceNumber++;

			//Printing the transaction information from Transactions DataBase to make sure that it have been correctly stored
			printf("\nTrasaction Information\n");
			puts(tansactionsDB[n].cardHolderData.cardHolderName);
			puts(tansactionsDB[n].cardHolderData.primaryAccountNumber);
			puts(tansactionsDB[n].cardHolderData.cardExpirationDate);
			printf("Max Transaction Amount is : %.2f\n", tansactionsDB[n].terminalData.maxTransAmount);
			printf("Transaction Amount is : %.2f\n", tansactionsDB[n].terminalData.transAmount);
			puts(tansactionsDB[n].terminalData.transactionDate);
			printf("Transaction Sequence Number is : %d\n\n", tansactionsDB[n].transactionSequenceNumber);

			saveTransactionFlag = Okay;
			return Okay;
		}
	}
	saveTransactionFlag = SAVING_FAILED;
	return SAVING_FAILED;

}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData)
{
	for (int j = 0; j < 255; j++)
	{
		if (tansactionsDB[j].transactionSequenceNumber == transactionSequenceNumber)
		{
			printf("Transaction has been FOUND\n\n");
			printf("Transaction Sequence Number : % d\n", tansactionsDB[j].transactionSequenceNumber);
			printf("Transaction Date : ");
			puts(tansactionsDB[j].terminalData.transactionDate);
			printf("Card Holder Name : ");
			puts(tansactionsDB[j].cardHolderData.cardHolderName);
			printf("Card PAN \"Primary Account Number\" : ");
			puts(tansactionsDB[j].cardHolderData.primaryAccountNumber);
			printf("Transaction Amount : %.2f\n", tansactionsDB[j].terminalData.transAmount);
			printf("New balance is : %.2f\n\n", accountsDB[i].balance);
			if (tansactionsDB[j].transState == APPROVED)
				printf("Transaction State is : APPROVED\n");
			else if (tansactionsDB[j].transState == DECLINED_STOLEN_CARD)
				printf("Transaction State is : DECLINED STOLEN CARD\n");
			else if (tansactionsDB[j].transState == DECLINED_INSUFFECIENT_FUND)
				printf("Transaction State is : DECLINED INSUFFECIENT FUND\n");
			return Okay;
		}
	}
	return TRANSACTION_NOT_FOUND;
}