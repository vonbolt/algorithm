#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * ȡ��ԭ��: ������(����������)�������кϲ���һ���µ��������У����Ѵ��������з�Ϊ���ɸ������У�
 *           ÿ��������������ģ�Ȼ���ٰ����������кϲ�Ϊ�����������У����Գ����鲢����
 * ƽ��ʱ�临�Ӷ�: O(nlogn)��
 * ƽ���ռ临�Ӷ�: O(n)��
 * �����ȶ��ԡ�
 * �鲢�����Ƿ��η�(Divide and Conquer)��һ���ǳ����͵�Ӧ�á�
 */

/*
 * �鲢����Ĺؼ���: �鲢��������ʱ�ռ�Ŀ�����
 * �ó�����ÿ�ν��й鲢����ʱ���������¿ռ䣬�������ٺ��ͷ�̫Ƶ����
 * ����ɴ������ڴ���Ƭ��ͬʱ�����ٶ��ڴ��ջ�ڴ�����ٶ�����
 * ��������: ������ǰ�Ϳ���һ��ʹ���������һ����С���¿ռ䣬ÿ�ν��й鲢������ʹ������¿ռ䡣
 */

/* �����������:
[********** Before NoRecursionMergeSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After NoRecursionMergeSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: �鲢����(�ǵݹ�)��
 *       ���㷨�����Ե����ϣ���1������ĵ�Ԫ��2^0������2������ĵ�Ԫ��2^1������n������ĵ�Ԫ��2^(n-1)����
 * ����: NoRecursionMergeSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void NoRecursionMergeSort(int* pData, int nLength);

/*
 * ����: һ�˹鲢����
 * ����: MergePass��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nUnit���鲢�����ĵ�Ԫ���ȡ�
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void MergePass(int* pData, int nUnit, int nLength);

/*
 * ����: �鲢������
 *       �������[nLeft, nLeft + nUnit - 1]��Χ�����ݺ������[nLeft + nUnit, nRight]��Χ�����ݽ��й鲢������
 * ����: Merge��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLeft�������������Ŀ�ʼ�±�λ�á�
 * ����: int nRight�������������Ľ����±�λ�á�
 * ����: int nUnit���鲢�����ĵ�Ԫ���ȡ�
 * ����ֵ: void��
 */
void Merge(int* pData, int nLeft, int nRight, int nUnit);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before NoRecursionMergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	NoRecursionMergeSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After NoRecursionMergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void NoRecursionMergeSort(int* pData, int nLength)
{
	// i: �������ƹ鲢�������������Ҫ����logn������
	int i = 1;
	// ��1������ĵ�Ԫ��2^0������2������ĵ�Ԫ��2^1������n������ĵ�Ԫ��2^(n-1)����
    for (; i < nLength; i *= 2)
	{
		// ��һ�˹鲢����
		MergePass(pData, i, nLength);
	}
}

void MergePass(int* pData, int nUnit, int nLength)
{
	int nLeft = 0;
	int nRight = 0;
	for (; nLeft + nUnit < nLength; nLeft = nRight + 1)
	{
		// ÿ��ѭ����������nUnit*2���ȡ�
		nRight = nLeft + nUnit * 2 - 1;
		if (nRight >= nLength)
		{
			nRight = nLength - 1;
		}
		Merge(pData, nLeft, nRight, nUnit);
	}
}

void Merge(int* pData, int nLeft, int nRight, int nUnit)
{
	// nMiddle: ��Χ[nLeft, nMiddle]ĩβ���±�ֵ
	int nMiddle = nLeft + nUnit - 1;
	// i: �������Ʊ���[nLeft, nMiddle]��Χ���ݵĴ�����
	int i = nLeft;
	// j: �������Ʊ���[nMiddle + 1, nRight]��Χ���ݵĴ�����
	int j = nMiddle + 1;
	// k: �������Ƹ������ݵ�pTempData�е�λ�á�
	int k = 0;
	// nLength: ���鲢�����еĳ��ȡ�
	int nLength = nRight - nLeft + 1;
	// pTempData: ��ʱ���ݿ飬������Ź鲢����������С�
	int* pTempData = (int*)malloc(sizeof(int) * nLength);
	memset(pTempData, 0, sizeof(int) * nLength);

	// �������[nLeft, nMiddle]��Χ�����ݺ������[nMiddle + 1, nRight]��Χ�����ݹ鲢��pTempData�С�
	while (i <= nMiddle && j <= nRight)
	{
		if (pData[i] > pData[j])
		{
			pTempData[k++] = pData[j++];
		}
		else
		{
			pTempData[k++] = pData[i++];
		}
	}
	while (i <= nMiddle)
	{
		pTempData[k++] = pData[i++];
	}
	while (j <= nRight)
	{
		pTempData[k++] = pData[j++];
	}
	
	// ��pTempData�е������������θ��Ƶ�pData��[nLeft, nRight]��Χ�С�
	for (i = nLeft; i <= nRight; ++i)
	{
		pData[i] = pTempData[i - nLeft];
	}

	free(pTempData);
	pTempData = NULL;
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