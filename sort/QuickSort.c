#include <stdio.h>

/*
 * ����: ���������Ƕ�ð�������һ�ָĽ���
 * ƽ��ʱ�临�Ӷ�: O(nlogn)��
 * ƽ���ռ临�Ӷ�: O(logn)��
 * ���в��ȶ��ԡ�
 */

/* ʱ�临�Ӷȷ���
 * ������: ÿ��ͨ����ֵ���ֺ�����������С��Ϊn/2ʱ��ʱ�临�Ӷ���O(nlogn)��
 * ����: ÿ��ͨ����ֵ���ֺ�����������С�ֱ���n-1��1��ʱ(�����Ѿ����������)��ʱ�临�Ӷ���O(n^2)��
 */

/*
 * ��������Ĺؼ��㣺�Ѵ��������е��ĸ�ֵ��Ϊ��ֵ��
 * �ó���Ѵ��������еĵ�1��ֵ��Ϊ��ֵ��
 * ����ѡ��ֵ�ķ���: 
 * (1) �Ѵ��������м�λ�õ�ֵ��Ϊ��ֵ��
 * (2) �Ƚϴ������п�ͷ���м䡢��β3������ֵ���Ѵ�С�����м��ֵ��Ϊ��ֵ(ƽ�����)��
 * (3) �������һ���������е�����ֵ���Ѹ�����ֵ����Ӧ��ֵ��Ϊ��ֵ(���������)��
 */

/* �����������:
[********** Before QuickSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After QuickSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ��������
 *       ��Ҫ��������
 *       ��һ�������У���Ҫ��������ݷָ�������֣��м䲿��ֻ��һ�����ݣ�
 *       �󲿷ֵ��������ݶ�С�ڻ�����м䲿�ֵ����ݣ��м䲿�ֵ�����С�ڻ�����Ҳ��ֵ��������ݣ�
 *       Ȼ���ٰ��˷����ֱ���󲿷����ݺ��в������ݼ������п�������
 *       ����������̿��Եݹ���У�����ʹ�������ݱ������
 * ����: QuickSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLeft�������������Ŀ�ʼ�±�λ�á�
 * ����: int nRight�������������Ľ����±�λ�á�
 * ����ֵ: void��
 */
void QuickSort(int* pData, int nLeft, int nRight);

/*
 * ����: ��pData[nLeft]��Ϊ��ֵ����[nLeft, nRight]��Ϊ����ֵ�Ҹ�λ�ã����Ѹ���ֵ�ŵ���λ���ϣ�
 *       ����Ǹ���ֵ��ߵ�����С�ڻ���ڸ���ֵ������ֵ�ұߵ��������ڻ���ڸ���ֵ��
 * ����: Partition��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLeft�������������Ŀ�ʼ�±�λ�á�
 * ����: int nRight�������������Ľ����±�λ�á�
 * ����ֵ: int��������ֵ��[nLeft, nRight]�е��±�λ�á�
 */
int Partition(int* pData, int nLeft, int nRight);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before QuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	QuickSort(arrData, 0, sizeof(arrData) / sizeof(int) - 1);

	printf("[********** After QuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void QuickSort(int* pData, int nLeft, int nRight)
{
    // nPivotPos: ��ֵ��[nLeft, nRight]�е��±�λ�á�
    int nPivotPos = 0;
    if (nLeft < nRight)
    {
        nPivotPos = Partition(pData, nLeft, nRight);
        QuickSort(pData, nLeft, nPivotPos - 1);
        QuickSort(pData, nPivotPos + 1, nRight);
    }
}

int Partition(int* pData, int nLeft, int nRight)
{
    // ������ߵ�ֵ��Ϊ��ֵ��
    int nPivotValue = pData[nLeft];
    // �ҳ���ֵ���±�λ�ã��Ѵ�����ֵ��ֵ�ŵ���ֵ����ߣ���С����ֵ��ֵ�ŵ���ֵ���ұߡ�
    while (nLeft < nRight)
    {
        while (nLeft < nRight && nPivotValue <= pData[nRight])
        {
            --nRight;
        }
        if (nLeft < nRight)
        {
            pData[nLeft] = pData[nRight];
            ++nLeft;
        }

        while (nLeft < nRight && pData[nLeft] <= nPivotValue)
        {
            ++nLeft;
        }
        if (nLeft < nRight)
        {
            pData[nRight] = pData[nLeft];
            --nRight;
        }
    }
    pData[nLeft] = nPivotValue;

    // ������ֵ���±�λ�á�
    return nLeft;
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