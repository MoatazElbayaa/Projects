#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>
#include<time.h>
#include "../Card/card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter cardholder's name [1:24]characters, Only a-z and spaces are allowed : ");
	gets(cardData->cardHolderName);

	int nameLength = (int)strlen(cardData->cardHolderName);

	if (nameLength == 0 || nameLength < 20 || nameLength > 24)
	{
		return WRONG_NAME;
	}
	//checking if the Card Holder Name contains an invalid character
	for (int i = 0; i < nameLength; i++)
	{
		int n = (int) cardData->cardHolderName[i];
		/*
			->ASCII codes of 'A' to 'Z' are 65 to 90
			->ASCII codes of 'a' to 'z' are 97 to 122
			->ASCII codes of space '' is 32
			->Then, if the ASCII code of our char is not located between
			one of these two ranges and not a space,then it is not a valid character
		*/
		if (!((n >= 65 && n <= 90) || (n >= 97 && n <= 122) || n==32))
			return WRONG_NAME;

	}
	
	//if no value has been returned till now, then the Card Holder Name is Ok 
	return OK;
	
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter the card expiry date \"MM / YY\": ");
	gets(cardData->cardExpirationDate);

	int expiryDateLength = (int)strlen(cardData->cardExpirationDate);


	if (expiryDateLength == 0 || expiryDateLength != 5 || cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return OK;
	}

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter your Card PAN [16:19] digits Only A-Z and 0-9 are allowed: ");
	gets(cardData->primaryAccountNumber);

	int PAN_Length = (int)strlen(cardData->primaryAccountNumber);
	printf("cardPAN_Length = %d\n", PAN_Length);
	if (PAN_Length == 0 || PAN_Length < 16 || PAN_Length>19)
	{
		return WRONG_PAN;
	}

	//checking if the cardPAN consist of alphanumeric characters
	for (int i = 0; i < PAN_Length; i++)
	{
		int n = cardData->primaryAccountNumber[i];
		/*
			->ASCII codes of '0' to '9' are 48 to 57
			->ASCII codes of 'A' to 'Z' are 65 to 90
			->Then, if the ASCII code of our char is not located between
			one of these two ranges,then it is not an alphanumeric character
		*/
		if (!((n >= 48 && n <= 57) || (n >= 65 && n <= 90)))
			return WRONG_PAN;
	}
	//if no value has been returned till now, then the cardPAN is Ok 
	return OK;
}

int char_To_int(uint8_t var)
{
	switch (var)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	}

}


