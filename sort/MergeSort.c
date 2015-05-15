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
[********** Before MergeSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After MergeSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: �鲢����
 *       ���㷨��Ҫ�ݹ�ؽ��У�ÿһ�εݹ�Ĳ�������
 *       (1) ���nLeft��nRight��ƽ��ֵ��
 *       (2) �ֱ��[nLeft, nMiddle]��Χ�����ݺ�[nMiddle + 1, nRight]��Χ�����ݽ��й鲢����
 *       (3) �������[nLeft, nMiddle]��Χ�����ݺ������[nMiddle + 1, nRight]��Χ�����ݽ��й鲢������
 * ����: MergeSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLeft�������������Ŀ�ʼ�±�λ�á�
 * ����: int nRight�������������Ľ����±�λ�á�
 * ����ֵ: void��
 */
void MergeSort(int* pData, int nLeft, int nRight);

/*
 * ����: �鲢������
 *       �������[nLeft, nMiddle]��Χ�����ݺ������[nMiddle + 1, nRight]��Χ�����ݽ��й鲢������
 * ����: Merge��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLeft�������������Ŀ�ʼ�±�λ�á�
 * ����: int nMiddle���������������м��±�λ�á�
 * ����: int nRight�������������Ľ����±�λ�á�
 * ����ֵ: void��
 */
void Merge(int* pData, int nLeft, int nMiddle, int nRight);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before MergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	MergeSort(arrData, 0, sizeof(arrData) / sizeof(int) - 1);

	printf("[********** After MergeSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void MergeSort(int* pData, int nLeft, int nRight)
{
	if (nLeft < nRight)
	{
		// ��[nLeft, nRight]��Χƽ�ֳ�[nLeft, nMiddle]��[nMiddle + 1, nRight]������Χ
		int nMiddle = (nLeft + nRight) / 2;
		// ��[nLeft, nMiddle]��Χ�����ݽ��й鲢����
		MergeSort(pData, nLeft, nMiddle);
		// ��[nMiddle + 1, nRight]��Χ�����ݽ��й鲢����
		MergeSort(pData, nMiddle + 1, nRight);
		// �������[nLeft, nMiddle]��Χ�����ݺ������[nMiddle + 1, nRight]��Χ�����ݽ��й鲢����
		Merge(pData, nLeft, nMiddle, nRight);
	}
}

void Merge(int* pData, int nLeft, int nMiddle, int nRight)
{
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