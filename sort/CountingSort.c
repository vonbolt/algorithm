#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * ����: �����������������ÿ������Ԫ�����������������е�λ�ã�Ȼ��Ѵ�����������ÿ������Ԫ�طŵ�����λ�ã�����ЩԪ����ɵ�����������ģ�
 *       ��������Ԫ��pData[i]������λ�õķ�����ͳ�ƴ����������б�pData[i]С������Ԫ�صĸ����������j������С��
 *       ��ô�Ͱ�pData[i]�ŵ��������е�j+1��λ���ϣ�������ͬ������Ԫ��ֵ�����ǻ��ȴ�Ŵ����������ұߵ�����Ԫ�أ�������ߵ�����Ԫ�أ�
 *       ����ʹ����ͳ�Ƹ����ķ��������Գ�����������
 * ƽ��ʱ�临�Ӷ�: O(n)��n�Ǵ������ݵĸ�����
 * �����ȶ��ԡ�
 */

/*
 * ��������Ĺؼ��㣺���������������������ÿ������Ԫ�����������������е�λ�á�
 * ���ڼ��������ǷǱȽ����㷨����ʱ�临�Ӷ�Ҫ�������Եģ�
 * ���ԣ�����ͨ���Ƚϴ����������е�ֵ�����ÿ������Ԫ�����������������е�λ�á�
 */

/* �����������:
[********** Before CountingSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After CountingSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99

[********** Before CountingSortEx **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After CountingSortEx **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ��������
 *       ������������pData���ҳ���СֵnMin�����ֵnMax��
 *       �¿���(nMax - nMin + 1)��С���ڴ�ռ�pCounting��pCounting[i]��ӦnMin+i��
 *       ������������pData����pCounting�ж�Ӧ��λ�ý��м����������������pData[i]�Ͱ�pCounting[pData[i] - nMin]��1��
 *       ����pCounting�е����ݣ���pCounting[i]��ֵ����pCounting[i - 1]��
 *       �¿���nLength��С���ڴ�ռ�pTempData��
 *       ������������pData����pData[i]���ݷŵ�pTempData[k]�У������pTempData�е�����������ģ�
 *       ��pTempData�е��������θ��Ƶ�pData�С� 
 * ����: CountingSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void CountingSort(int* pData, int nLength);

/*
 * ����: ��������(ʵ�ַ�����CountingSort����)��
 *       ������������pData���ҳ���СֵnMin�����ֵnMax��
 *       �¿���(nMax - nMin + 1)��С���ڴ�ռ�pCounting��pCounting[i]��ӦnMin+i��
 *       ������������pData����pCounting�ж�Ӧ��λ�ý��м����������������pData[i]�Ͱ�pCounting[pData[i] - nMin]��1��
 *       ����pCounting�е����ݣ����pCounting[i]����0���Ͱ�(nMin + i)ֵ�ŵ�pData����Ӧ��λ�á� 
 * ����: CountingSortEx��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void CountingSortEx(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};
	int arrDataEx[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before CountingSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));
	CountingSort(arrData, sizeof(arrData) / sizeof(int));
	printf("[********** After CountingSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	printf("\n[********** Before CountingSortEx **********]\n");
	Output(arrDataEx, sizeof(arrDataEx) / sizeof(int));
	CountingSortEx(arrDataEx, sizeof(arrDataEx) / sizeof(int));
	printf("[********** After CountingSortEx **********]\n");
	Output(arrDataEx, sizeof(arrDataEx) / sizeof(int));

	return 0;
}

void CountingSort(int* pData, int nLength)
{
	int i = 0;
	int j = 0;
	// nMin: pData������Ԫ��ֵ��С��ֵ��
	int nMin = pData[0];
	// nMax: pData������Ԫ��ֵ����ֵ��
	int nMax = nMin;
	// nCount: ��������Ĵ�С��
	int nCount = 0;
	// pCounting: ��������ָ�롣
	int* pCounting = NULL;
	// pTempData: ��ʱ���飬������������Ľ����
	int* pTempData = NULL;
	int nTempPos = 0;

	for (i = 1; i < nLength; ++i)
	{
		if (pData[i] < nMin)
		{
			nMin = pData[i];
		}
		else if (pData[i] > nMax)
		{
			nMax = pData[i];
		}
	}
	nCount = nMax - nMin + 1;
	pCounting = (int*)malloc(sizeof(int) * nCount);
	memset(pCounting, 0, sizeof(int) * nCount);

	for (i = 0; i < nLength; ++i)
	{
		++pCounting[pData[i] - nMin];
	}

	for (i = 1; i < nCount; ++i)
	{
		pCounting[i] += pCounting[i - 1];
	}

	pTempData = (int*)malloc(sizeof(int) * nLength);
	memset(pTempData, 0, sizeof(int) * nLength);
	for (i = nLength - 1; i >= 0; --i)
	{
		nTempPos = pCounting[pData[i] - nMin];
		pTempData[nTempPos - 1] = pData[i];
		--pCounting[pData[i] - nMin];
	}

	for (i = 0; i < nLength; ++i)
	{
		pData[i] = pTempData[i];
	}

	free(pCounting);
	pCounting = NULL;
	free(pTempData);
	pTempData = NULL;
}

void CountingSortEx(int* pData, int nLength)
{
	int i = 0;
	int j = 0;
	// nMin: pData������Ԫ��ֵ��С��ֵ��
	int nMin = pData[0];
	// nMax: pData������Ԫ��ֵ����ֵ��
	int nMax = nMin;
	// nCount: ��������Ĵ�С��
	int nCount = 0;
	// pCounting: ��������ָ�롣
	int* pCounting = NULL;

	for (i = 1; i < nLength; ++i)
	{
		if (pData[i] < nMin)
		{
			nMin = pData[i];
		}
		else if (pData[i] > nMax)
		{
			nMax = pData[i];
		}
	}
	nCount = nMax - nMin + 1;
	pCounting = (int*)malloc(sizeof(int) * nCount);
	memset(pCounting, 0, sizeof(int) * nCount);

	for (i = 0; i < nLength; ++i)
	{
		++pCounting[pData[i] - nMin];
	}

	for (i = 0; i < nCount; ++i)
	{
		while (pCounting[i] > 0)
		{
			pData[j++] = nMin + i;
			--pCounting[i];
		}
	}

	free(pCounting);
	pCounting = NULL;
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