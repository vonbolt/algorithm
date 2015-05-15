#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * ȡ��ԭ��: ����͸����ֵ�Ĳ�����Ѷ����Ҫ�����Ԫ�ط�����ĳЩ��Ͱ�����Դﵽ�����Ŀ�ģ����Գ�����������
 * ƽ��ʱ�临�Ӷ�: O(d(n+r))��d��λ��(������������)��r�ǻ�����n�Ǵ������ݵĸ�����
 * ƽ���ռ临�Ӷ�: O(r+n)��
 * �����ȶ��ԡ�
 * �����������ڷ���ʽ����(distribution sort)��
 * ��ĳЩʱ�򣬻��������Ч�ʸ��������ıȽ�������
 */

/*
 * ��������Ĺؼ��㣺�����õ�����������ĳһλ����ֵ��
 * �ó���ʹ���˳�����ȡ������õ��˴���������ĳһλ����ֵ��
 *
 * �ó����ǰ���λ��ʮλ����λ�ȵ�˳��������ģ�����LSD(Least significant digital)���λ���ȷ�����
 * Ҳ���԰���λ��ʮλ����λ�ȵ�˳�������򣬳���MSD(Most significant digital)���λ���ȷ�����
 */

/* �����������:
[********** Before RadixSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After RadixSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ��������
 *       �ȸ��ݻ���nRadix�õ����������е�����λ��nMaxDigit���������������
 *       Ȼ�����nMaxDigit������ÿһ��������������
 *       (1) �������ұ���pData�е����ݣ���ÿ�����ݷ����Ӧ��Ͱ�У��ܹ���nMaxDigit��Ͱ��Ͱ�ı�ŷ�Χ��[0, nMaxDigit-1]��
 *           �����ݷ����ĸ�Ͱ��ȡ���ڵ�ǰ�����ǰ���һλ�������簴��λ�����ʱ�����pData[i]���ݵİ�λ��j��
             ��ô���ͰѸ����ݷ�����Ϊj��Ͱ�У�
 *       (2) ������Ͱ�е��������θ��Ƶ�pData�У�
 *       (3) �ı������λ��
 *       ���ڸó��򣬵�1�������ǰ���λ�ţ���2�������λ�ǰ�ʮλ�ţ���3�������λ����λ�ţ�������ơ�
 * ����: RadixSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����: int nRadix���������ڸó�����ָ����(����ʮ���ơ�ʮ�����Ƶ�)��
 * ����ֵ: void��
 */
void RadixSort(int* pData, int nLength, int nRadix);

/*
 * ����: �õ�pData��λ���������ݵ�λ��ֵ��
 * ����: GetMaxDigit��
 * ����: const int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����: int nRadix���������ڸó�����ָ����(����ʮ���ơ�ʮ�����Ƶ�)��
 * ����ֵ: void��
 */
int GetMaxDigit(const int* pData, int nLength, int nRadix);

/*
 * ����: ��ppRadixData�е��������θ��Ƶ�pData�С�
 * ����: CopyData��
 * ����: int* pData��ָ��һ���������顣
 * ����: const int** ppRadixData��ָ��һ����ά�������顣
 * ����: const int* pRadixDataCount��ָ��һ���������飬pRadixDataCount[i]ֵ��¼ppRadixData[i]ָ������ݵĸ�����
 * ����: int nRadixDataCountLength����������pRadixDataCount�ĳ��ȡ�
 * ����ֵ: void��
 */
void CopyData(int* pData, const int** ppRadixData, const int* pRadixDataCount, int nRadixDataCountLength);

void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before RadixSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	RadixSort(arrData, sizeof(arrData) / sizeof(int), 10);

	printf("[********** After RadixSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void RadixSort(int* pData, int nLength, int nRadix)
{
	int i = 0;
	int j = 0;
	int nTempRadix = 1;
	int nMaxDigit = 0;
	int nTemp = 0;
	int nTempIndex = 0;
	int** ppRadixData = NULL;
	int* pRadixDataCount = NULL;

	ppRadixData = (int**)malloc(sizeof(int*) * nRadix);
	memset(ppRadixData, 0, sizeof(int) * nRadix);
	for (i = 0; i < nRadix; ++i)
	{
		ppRadixData[i] = (int*)malloc(sizeof(int) * nLength);
		memset(ppRadixData[i], 0, sizeof(int) * nLength);
	}
	pRadixDataCount = (int*)malloc(sizeof(int) * nRadix);
	memset(pRadixDataCount, 0, sizeof(int) * nRadix);

	nMaxDigit = GetMaxDigit(pData, nLength, nRadix);
	
	for (i = 0; i < nMaxDigit; ++i)
	{
		for (j = 0; j < nLength; ++j)
		{
			// ��pData[j]����[0, nRadix - 1]��Χ�С�
			nTemp = (pData[j] / nTempRadix) % nRadix;
			nTempIndex = pRadixDataCount[nTemp];
			ppRadixData[nTemp][nTempIndex] = pData[j];
			pRadixDataCount[nTemp] += 1;
		}

		// ��ppRadixData�е��������θ��Ƶ�pData�С�
		CopyData(pData, ppRadixData, pRadixDataCount, nRadix);
		// ��pRadixDataCount�е���������
		memset(pRadixDataCount, 0, sizeof(int) * nRadix);

		nTempRadix *= nRadix;
	}

	for (i = 0; i < nRadix; ++i)
	{
		free(ppRadixData[i]);
		ppRadixData[i] = NULL;
	}
	free(ppRadixData);
	ppRadixData = NULL;
}

int GetMaxDigit(const int* pData, int nLength, int nRadix)
{
	// nDigit: pData��λ���������ݵ�λ��ֵ
	int nDigit = 0;
	// nMaxData: pDataָ��������о���ֵ������
	int nMaxData = 0;
	int nTempData = 0;
	int i = 1;
	
	if (nLength < 1)
	{
		return -1;
	}

	// �õ�pDataָ��������о���ֵ������
	nMaxData = pData[0];
	if (nMaxData < 0)
	{
		nMaxData = -nMaxData;
	}
	for (; i < nLength; ++i)
	{
		nTempData = pData[i];
		if (nTempData < 0)
		{
			nTempData = -nTempData;
		}
		if (nMaxData < nTempData)
		{
			nMaxData = nTempData;
		}
	}

	while (nMaxData > 0)
	{
		++nDigit;
		nMaxData /= nRadix;
	}

	return nDigit;
}

void CopyData(int* pData, const int** ppRadixData, const int* pRadixDataCount, int nRadixDataCountLength)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (; i < nRadixDataCountLength; ++i)
	{
		for (j = 0; j < pRadixDataCount[i]; ++j)
		{
			pData[k] = ppRadixData[i][j];
			++k;
		}
	}
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