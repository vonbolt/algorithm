#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

/*
 * �ⷨ1: ��Ӧ����Deal����һ����Χ���������һ���ƣ�ȡ�������ƣ�Ȼ����С��Χ����˼�����ȥ��
 * �ⷨ2: ��Ӧ����DealEx���Ȳ���54������ƣ�Ȼ��ֱ��2, 3, ......, 51�����в����Ʒ���3�����е�һ����
 */

/* �����������:
[********** Before Deal **********]
����A, ����2, ����3, ����4, ����5, ����6, ����7, ����8, ����9, ����10,
����J, ����Q, ����K, ÷��A, ÷��2, ÷��3, ÷��4, ÷��5, ÷��6, ÷��7,
÷��8, ÷��9, ÷��10, ÷��J, ÷��Q, ÷��K, ����A, ����2, ����3, ����4,
����5, ����6, ����7, ����8, ����9, ����10, ����J, ����Q, ����K, ����A,
����2, ����3, ����4, ����5, ����6, ����7, ����8, ����9, ����10, ����J,
����Q, ����K, С��, ����

[********** After Deal **********]
Person 1:
����4, ����3, ����5, ����J, ����Q, ����7, ����K, ����3, ÷��5, ����9,
����4, ����2, ����5, ����7, ����2, ����8, С��
Person 2:
����8, ÷��4, ÷��J, ����3, ����A, ����K, ����J, ÷��K, ÷��Q, ����9,
÷��7, ����10, ����6, ����A, ����5, ÷��6, ÷��3
Person 3:
����, ����9, ����2, ����4, ����Q, ����10, ����6, ����A, ����7, ÷��8,
÷��2, ÷��9, ����K, ÷��10, ����10, ����6, ÷��A
Remain:
����Q, ����J, ����8


[********** Before DealEx **********]
����A, ����2, ����3, ����4, ����5, ����6, ����7, ����8, ����9, ����10,
����J, ����Q, ����K, ÷��A, ÷��2, ÷��3, ÷��4, ÷��5, ÷��6, ÷��7,
÷��8, ÷��9, ÷��10, ÷��J, ÷��Q, ÷��K, ����A, ����2, ����3, ����4,
����5, ����6, ����7, ����8, ����9, ����10, ����J, ����Q, ����K, ����A,
����2, ����3, ����4, ����5, ����6, ����7, ����8, ����9, ����10, ����J,
����Q, ����K, С��, ����

[********** After DealEx **********]
Person 1:
����8, ÷��3, ÷��6, ÷��A, ����A, ����6, ����10, ÷��7, ����9, ÷��Q,
÷��K, ����J, ����K, ����A, ����3, ÷��J, ÷��4
Person 2:
����J, С��, ����8, ����2, ����7, ����5, ����2, ����4, ����9, ÷��5,
����3, ����K, ����7, ����Q, ����J, ����5, ����3
Person 3:
����Q, ����6, ����10, ÷��10, ����K, ����5, ÷��2, ÷��8, ����7, ����A,
����6, ����10, ����Q, ����4, ����2, ����9, ÷��9
Remain:
����, ����8, ����4
*/

#define POKER_NUM 54
#define REMAIN_POKER_NUM 3
#define EVERY_PERSON_POKER_NUM (POKER_NUM - REMAIN_POKER_NUM) / 3
#define PART_POKER_NUM 13
#define POKER_COLOR_NUM 4

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef enum 
{
	// ����
	PT_DIAMONDS,
	// ÷��
	PT_CLUBS,
	// ����
	PT_HEARTS,
	// ����
	PT_SPADES,
	// С��
	PT_SMALLJOKER,
	// ����
	PT_BIGJOKER
} PokerType;

typedef struct
{
	int nNum;
	PokerType pt;
} Poker;

typedef struct
{
	Poker p;
	// ��Ǹ���������ֵ�Ƿ��Ѿ����������
	BOOL bFlag;
} PokerEx;

/*
 * ����: ���ơ�
         ѭ������(nLength - nRemainLength)�ˣ�ÿһ�˵�ѭ�����£�
         �������һ��[0, i - 1]��Χ�ڵ���nPokerIndex��
		 ���nPokerIndexС��i - 1���Ͱ�pTempPoker[nPokerIndex]��pTempPoker[i - 1]����������i��1��
         ���nPokerIndex����i - 1���Ͱ�i��1��
 * ����: Deal��
 * ����: const Poker* pPoker��ָ��һ�����飬�������������������ݡ�
 * ����: int nLength��pPoker����ĳ��ȡ�
 * ����: Poker* pPoker1��ָ���ŵ�1�����Ƶ����飬������������������ݡ�
 * ����: Poker* pPoker2��ָ���ŵ�2�����Ƶ����飬������������������ݡ�
 * ����: Poker* pPoker3��ָ���ŵ�3�����Ƶ����飬������������������ݡ�
 * ����: int nEveryPersonLength��pPoker1��pPoker2��pPoker3����ĳ��ȡ�
 * ����: Poker* pPokerRemain��ָ����ʣ��δ���Ƶ����飬������������������ݡ�
 * ����: int nRemainLength��pPokerRemain����ĳ��ȡ�
 * ����ֵ: void��
 */
void Deal(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
			Poker* pPokerRemain, int nRemainLength);
void OutputDealBefore(const Poker* pPoker, int nPokerNum);
void OutputDealAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum);

/*
 * ����: ���ơ�
         ���������54���Ʒ���pTempPokerEx�У�
         Ȼ���������һ��[0, i - 1]��Χ�ڵ���nPokerExIndex��
		 ���pTempPokerEx[nPokerExIndex]�ı��λΪTRUE���Ͱ�pTempPokerEx[i - 1]���ΪTRUE��
		                 ���Ѹ�pTempPokerEx[i - 1]�Ʒ���3�����е�һ����
		 ���pTempPokerEx[nPokerExIndex]�ı��λΪFALSE���Ͱ�pTempPokerEx[nPokerExIndex]���ΪTRUE��
		                 ���Ѹ�pTempPokerEx[nPokerExIndex]�Ʒ���3�����е�һ����
 * ����: DealEx��
 * ����: const Poker* pPoker��ָ��һ�����飬�������������������ݡ�
 * ����: int nLength��pPoker����ĳ��ȡ�
 * ����: Poker* pPoker1��ָ���ŵ�1�����Ƶ����飬������������������ݡ�
 * ����: Poker* pPoker2��ָ���ŵ�2�����Ƶ����飬������������������ݡ�
 * ����: Poker* pPoker3��ָ���ŵ�3�����Ƶ����飬������������������ݡ�
 * ����: int nEveryPersonLength��pPoker1��pPoker2��pPoker3����ĳ��ȡ�
 * ����: Poker* pPokerRemain��ָ����ʣ��δ���Ƶ����飬������������������ݡ�
 * ����: int nRemainLength��pPokerRemain����ĳ��ȡ�
 * ����ֵ: void��
 */
void DealEx(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength);
void OutputDealExBefore(const Poker* pPoker, int nPokerNum);
void OutputDealExAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum);

void Output(const Poker* pPoker, int nLength);

int main()
{
	Poker arrPoker[POKER_NUM] =
	{
		{1, PT_DIAMONDS}, {2, PT_DIAMONDS}, {3, PT_DIAMONDS}, {4, PT_DIAMONDS}, {5, PT_DIAMONDS}, {6, PT_DIAMONDS}, {7, PT_DIAMONDS},
		{8, PT_DIAMONDS}, {9, PT_DIAMONDS}, {10, PT_DIAMONDS}, {11, PT_DIAMONDS}, {12, PT_DIAMONDS}, {13, PT_DIAMONDS},
		{1, PT_CLUBS}, {2, PT_CLUBS}, {3, PT_CLUBS}, {4, PT_CLUBS}, {5, PT_CLUBS}, {6, PT_CLUBS}, {7, PT_CLUBS},
		{8, PT_CLUBS}, {9, PT_CLUBS}, {10, PT_CLUBS}, {11, PT_CLUBS}, {12, PT_CLUBS}, {13, PT_CLUBS},
		{1, PT_HEARTS}, {2, PT_HEARTS}, {3, PT_HEARTS}, {4, PT_HEARTS}, {5, PT_HEARTS}, {6, PT_HEARTS}, {7, PT_HEARTS},
		{8, PT_HEARTS}, {9, PT_HEARTS}, {10, PT_HEARTS}, {11, PT_HEARTS}, {12, PT_HEARTS}, {13, PT_HEARTS},
		{1, PT_SPADES}, {2, PT_SPADES}, {3, PT_SPADES}, {4, PT_SPADES}, {5, PT_SPADES}, {6, PT_SPADES}, {7, PT_SPADES},
		{8, PT_SPADES}, {9, PT_SPADES}, {10, PT_SPADES}, {11, PT_SPADES}, {12, PT_SPADES}, {13, PT_SPADES},
		{14, PT_SMALLJOKER}, {15, PT_BIGJOKER}
	};
	Poker arrPoker1[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPoker2[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPoker3[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPokerRemain[REMAIN_POKER_NUM] = {0};

	OutputDealBefore(arrPoker, POKER_NUM);
	Deal(arrPoker, POKER_NUM, arrPoker1, arrPoker2, arrPoker3, EVERY_PERSON_POKER_NUM, arrPokerRemain, REMAIN_POKER_NUM);
	OutputDealAfter(arrPoker1, arrPoker2, arrPoker3, arrPokerRemain, EVERY_PERSON_POKER_NUM, REMAIN_POKER_NUM);

	memset(arrPoker1, 0, sizeof(arrPoker1));
	memset(arrPoker2, 0, sizeof(arrPoker2));
	memset(arrPoker3, 0, sizeof(arrPoker3));
	memset(arrPokerRemain, 0, sizeof(arrPokerRemain));

	printf("\n\n");
	OutputDealExBefore(arrPoker, POKER_NUM);
	DealEx(arrPoker, POKER_NUM, arrPoker1, arrPoker2, arrPoker3, EVERY_PERSON_POKER_NUM, arrPokerRemain, REMAIN_POKER_NUM);
	OutputDealExAfter(arrPoker1, arrPoker2, arrPoker3, arrPokerRemain, EVERY_PERSON_POKER_NUM, REMAIN_POKER_NUM);

	return 0;
}

void Deal(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength)
{
	int i = 0;
	int j = 0;
	int k = 0;

	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3 = 0;

	int nPokerIndex = 0;
	Poker pokerTemp = {0};
	Poker* pTempPoker = (Poker*)malloc(sizeof(Poker) * nLength);

	for (i = 0; i < nLength; ++i)
	{
		pTempPoker[i] = pPoker[i];
	}

	srand((unsigned int)time(NULL));
	for (i = nLength; i > nRemainLength; --i)
	{
		nPokerIndex = rand() % i;

		++k;
		if (k == 1)
		{
			pPoker1[nCount1++] = pTempPoker[nPokerIndex];
		}
		else if (k == 2)
		{
			pPoker2[nCount2++] = pTempPoker[nPokerIndex];
		}
		else
		{
			pPoker3[nCount3++] = pTempPoker[nPokerIndex];
			k = 0;
		}

		if (nPokerIndex != i - 1)
		{
			pokerTemp = pTempPoker[nPokerIndex];
			pTempPoker[nPokerIndex] = pTempPoker[i - 1];
			pTempPoker[i - 1] = pokerTemp;
		}
	}
	
	for (i = 0; i < nRemainLength; ++i)
	{
		pPokerRemain[i] = pTempPoker[i];
	}

	free(pTempPoker);
	pTempPoker = NULL;
}

void OutputDealBefore(const Poker* pPoker, int nPokerNum)
{
	printf("[********** Before Deal **********]\n");
	Output(pPoker, nPokerNum);
}

void OutputDealAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum)
{
	printf("\n[********** After Deal **********]\n");
	printf("Person 1:\n");
	Output(pPoker1, nEveryPersonPokerNum);
	printf("Person 2:\n");
	Output(pPoker2, nEveryPersonPokerNum);
	printf("Person 3:\n");
	Output(pPoker3, nEveryPersonPokerNum);
	printf("Remain:\n");
	Output(pPokerRemain, nRemainPokerNum);
}

void DealEx(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength)
{
	int i = 0;
	int j = 0;

	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3 = 0;

	int nPokerExIndex = 0;
	PokerEx pokerExTemp = {0};
	PokerEx* pTempPokerEx = (PokerEx*)malloc(sizeof(PokerEx) * nLength);

	for (i = 0; i < nLength; ++i)
	{
		pTempPokerEx[i].p = pPoker[i];
		pTempPokerEx[i].bFlag = FALSE;
	}
	srand((unsigned int)time(NULL));
	for (i = nLength; i > 1; --i)
	{
		nPokerExIndex = rand() % i;
		if (nPokerExIndex != i - 1)
		{
			pokerExTemp = pTempPokerEx[nPokerExIndex];
			pTempPokerEx[nPokerExIndex] = pTempPokerEx[i - 1];
			pTempPokerEx[i - 1] = pokerExTemp;
		}
	}
	
	for (i = 2; i <= nLength - nRemainLength; ++i)
	{
		nPokerExIndex = rand() % i;
		if (pTempPokerEx[nPokerExIndex].bFlag)
		{
			// nPokerExIndex�϶�������i - 1
			pTempPokerEx[i - 1].bFlag = TRUE;
			pokerExTemp = pTempPokerEx[i - 1];
		}
		else
		{
			pTempPokerEx[nPokerExIndex].bFlag = TRUE;
			pokerExTemp = pTempPokerEx[nPokerExIndex];
		}

		++j;
		if (j == 1)
		{
			pPoker1[nCount1++] = pokerExTemp.p;
		}
		else if (j == 2)
		{
			pPoker2[nCount2++] = pokerExTemp.p;
		}
		else
		{
			pPoker3[nCount3++] = pokerExTemp.p;
			j = 0;
		}
	}

	for (i = 0; i < nLength - nRemainLength; ++i)
	{
		if (!pTempPokerEx[i].bFlag)
		{
			pPoker3[nCount3] = pTempPokerEx[i].p;
			break;
		}
	}

	for (i = 0; i < nRemainLength; ++i)
	{
		pPokerRemain[i] = pTempPokerEx[nLength - nRemainLength + i].p;
	}

	free(pTempPokerEx);
	pTempPokerEx = NULL;
}

void OutputDealExBefore(const Poker* pPoker, int nPokerNum)
{
	printf("[********** Before DealEx **********]\n");
	Output(pPoker, nPokerNum);
}

void OutputDealExAfter(const Poker* pPoker1, const Poker* pPoker2, const Poker* pPoker3, const Poker* pPokerRemain,
					 int nEveryPersonPokerNum, int nRemainPokerNum)
{
	printf("\n[********** After DealEx **********]\n");
	printf("Person 1:\n");
	Output(pPoker1, nEveryPersonPokerNum);
	printf("Person 2:\n");
	Output(pPoker2, nEveryPersonPokerNum);
	printf("Person 3:\n");
	Output(pPoker3, nEveryPersonPokerNum);
	printf("Remain:\n");
	Output(pPokerRemain, nRemainPokerNum);
}

void Output(const Poker* pPoker, int nLength)
{
	const char* arrPokerNumber[PART_POKER_NUM] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	const char* arrPokerType[POKER_COLOR_NUM] = {"����", "÷��", "����", "����"};
	const char* pchSmallJoker = "С��";
	const char* pchBigJoker = "����";
	int i = 0;
	int j = 0;
	int nShowForOneLine = 10;

	for (i = 0; i < nLength; ++i)
	{
		if (pPoker[i].nNum == 14)
		{
			printf("%s", pchSmallJoker);
		}
		else if (pPoker[i].nNum == 15)
		{
			printf("%s", pchBigJoker);
		}
		else
		{
			j = (pPoker[i].nNum - 1) % PART_POKER_NUM;
			printf("%s%s", arrPokerType[pPoker[i].pt], arrPokerNumber[j]);
		}

		if (i != nLength - 1)
		{
			printf(", ");
			if ((i + 1) % nShowForOneLine == 0)
			{
				printf("\n");
			}
		}
		else 
		{
			printf("\n");
		}
	}
}
