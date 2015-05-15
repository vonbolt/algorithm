#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

#define MIN_NUM 100
#define MAN_NUM 900
#define DATA_LENGTH 5000000

/*
 * �ⷨ: ʹ��Ͱ����
         ����(MAN_NUM - MIN_NUM + 1)��Ͱ��Ͱ��ŵĴ�MIN_NUM��MAN_NUM����ÿ�������ķ���score����Ͱscore�У�
 *       Ȼ�����Ͱ�ŵĴ�С���ν�Ͱ�з�������������Եõ�һ����������С�
 */

typedef struct DataNode
{
	int nData;
	struct DataNode* pNext;
} DataNode;

/*
 * ����: ��ʼ��nLength�����ݡ�
 * ����: InitData��
 * ����: int** ppData��ָ��һ�����������ָ�롣
 * ����: int nLength������������ĳ��ȡ�
 * ����: int nMin��
 * ����: int nMax��
 * ����ֵ: void��
 */
void InitData(int** ppData, int nLength, int nMin, int nMax);

/*
 * ����: �ͷ�*ppDataָ��Ŀռ䡣
 * ����: DestoryData��
 * ����: int** ppData��ָ��һ�����������ָ�롣
 * ����ֵ: void��
 */
void DestoryData(int** ppData);

/*
 * ����: Ͱ����
 * ����: BucketSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����: int nMin��
 * ����: int nMax��
 * ����ֵ: void��
 */
void BucketSort(int* pData, int nLength, int nMin, int nMax);
void Output(const int* pData, int nLength);

int main()
{
	int* pData = NULL;
	int nLength = DATA_LENGTH;
	int nMin = MIN_NUM;
	int nMax = MAN_NUM;

	InitData(&pData, nLength, nMin, nMax);

	Output(pData, nLength);
	BucketSort(pData, nLength, nMin, nMax);
	Output(pData, nLength);

	DestoryData(&pData);

	return 0;
}

void InitData(int** ppData, int nLength, int nMin, int nMax)
{
	int i = 0;
	int nData = 0;
	int nRange = nMax - nMin + 1;

	*ppData = (int*)malloc(sizeof(int) * nLength);

	srand((unsigned int)time(NULL));
	for (; i < nLength; ++i)
	{
		// rand()����ֵ�ķ�Χ��[0x0, 0x7fff]��Ox7fff����32767��
		nData = rand() % nRange;
		nData += nMin;
		(*ppData)[i] = nData;
	}
}

void DestoryData(int** ppData)
{
	if (ppData != NULL && *ppData != NULL)
	{
		free(*ppData);
		*ppData = NULL;
	}
}

void BucketSort(int* pData, int nLength, int nMin, int nMax)
{
	int i = 0;
	int j = 0;
	// nBucketNum: Ͱ��������
	int nBucketNum = nMax - nMin + 1;
	DataNode* pDataNode = NULL;
	DataNode* pNextDataNode = NULL;
	DataNode* pPreviousDataNode = NULL;
	// ppBucket: ָ�����е�Ͱ��
	DataNode** ppBucket = NULL;

	ppBucket = (DataNode**)malloc(sizeof(DataNode*) * nBucketNum);
	for (i = 0; i < nBucketNum; ++i)
	{
		ppBucket[i] = NULL;
	}

	// ��pData[i]�ŵ�ͰppBucket�С�
	for (i = 0; i < nLength; ++i)
	{
		pDataNode = (DataNode*)malloc(sizeof(DataNode));
		pDataNode->nData = pData[i];
		pDataNode->pNext = NULL;

		pNextDataNode = ppBucket[pData[i] - nMin];
		if (pNextDataNode == NULL)
		{
			ppBucket[pData[i] - nMin] = pDataNode;
		}
		else
		{
			do
			{
				if (pDataNode->nData >= pNextDataNode->nData)
				{
					pPreviousDataNode = pNextDataNode;
					pNextDataNode = pNextDataNode->pNext;
				}
				else
				{
					pPreviousDataNode = pNextDataNode;
					break;
				}
			} while (pNextDataNode != NULL);
			pDataNode->pNext = pPreviousDataNode->pNext;
			pPreviousDataNode->pNext = pDataNode;
		}
	}

	// ��ͰppBucket�е��������и��Ƶ�pData�С�
	for (i = 0; i < nBucketNum; ++i)
	{
		pNextDataNode = ppBucket[i];
		while (pNextDataNode != NULL)
		{
			pData[j++] = pNextDataNode->nData;
			pNextDataNode = pNextDataNode->pNext;
		}
	}

	// ���ٶ��ڴ档
	for (i = 0; i < nBucketNum; ++i)
	{
		pNextDataNode = ppBucket[i];
		while (pNextDataNode != NULL)
		{
			pDataNode = pNextDataNode;
			pNextDataNode = pNextDataNode->pNext;
			free(pDataNode);
			pDataNode = NULL;
		}
		ppBucket[i] = NULL;
	}
	free(ppBucket);
	ppBucket = NULL;
}

void Output(const int* pData, int nLength)
{
	int i = 0;
	for (; i < nLength - 1; ++i)
	{
		printf("%d, ", pData[i]);
	}
	printf("%d\n", pData[i]);
}