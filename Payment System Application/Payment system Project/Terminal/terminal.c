#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>
#include<time.h>
#include"../Terminal/terminal.h"

extern struct ST_accountsDB_t accountsDB[255];


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	termData->transactionDate[0] = int_To_char(tm.tm_mday / 10);
	termData->transactionDate[1] = int_To_char(tm.tm_mday % 10);
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = int_To_char((tm.tm_mon + 1) / 10);
	termData->transactionDate[4] = int_To_char((tm.tm_mon + 1) % 10);
	termData->transactionDate[5] = '/';
	unsigned short year = (tm.tm_year + 1900);
	unsigned short digit = year % 10;
	termData->transactionDate[9] = int_To_char(digit);
	year /= 10;
	digit = year % 10;
	termData->transactionDate[8] = int_To_char(digit);
	year /= 10;
	digit = year % 10;
	termData->transactionDate[7] = int_To_char(digit);
	year /= 10;
	digit = year % 10;
	termData->transactionDate[6] = int_To_char(digit);
	printf("Transaction Date is : ");
	puts(termData->transactionDate);
	return OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	int expiryYear = 0;
	int expiryMonth = 0;

	expiryMonth = (10 * char_To_int(cardData->cardExpirationDate[0])) + char_To_int(cardData->cardExpirationDate[1]);
	expiryYear = 2000 + ((10 * char_To_int(cardData->cardExpirationDate[3])) + char_To_int(cardData->cardExpirationDate[4]));
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	if ((tm.tm_year + 1900) > expiryYear)
	{
		return EXPIRED_CARD;
	}
	else if ((tm.tm_year + 1900) == expiryYear)
	{
		if ((tm.tm_mon + 1) > expiryMonth)
			return EXPIRED_CARD;
		else
			return OK;
	}
	else //if(tm.tm_year + 1900) < expiryYear)
		return OK;
}


EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	int sum = 0;
	int digit = 0;
	for (int k = 0; k < strlen(cardData->primaryAccountNumber); k += 2)
	{
		digit = char_To_int(cardData->primaryAccountNumber[k]);
		if ((digit * 2) >= 10)
		{
			sum += ((digit * 2) / 10);
			sum += ((digit * 2) % 10);
		}
		else
		{
			sum += digit;
		}
	}

	if (sum % 10 == 0)
	{
		return OK;
	}
	else
	{	
		return INVALID_CARD;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the Desired transaction amount: ");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;
	else
		return OK;
	
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please Set the Max amount: ");
	scanf("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else
		return OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return OK;
}
















uint8_t int_To_char(unsigned short i)
{
	switch (i)
	{
	case 0:
		return '0';
		break;
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	case 6:
		return '6';
		break;
	case 7:
		return '7';
		break;
	case 8:
		return '8';
		break;
	case 9:
		return '9';
		break;
	}
}