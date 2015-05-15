#include <stdio.h>

/*
 * ȡ��ԭ��: ����������������������Ǵ�δ�����������ѡ�����С����������ǰ�棬���Գ���ѡ������
 * ƽ��ʱ�临�Ӷ�: O(n^2)��
 * �ռ临�Ӷ�: O(1)��
 * ���в��ȶ��ԡ�
 * ��̸��ӶȺܵͣ�������д�����롣
 */

/* ʱ�临�Ӷȷ���
 * �ܵıȽϴ���: (n-1)+(n-2)+...+1=n*(n-1)/2
 * �ܵĽ�������: [0, n-1]
 *
 * ������: �Ѿ�����ʱ�临�Ӷ���O(n^2)���ܵıȽϴ�����n*(n-1)/2���ܵĽ���������0��
 * ����: ����ʱ�临�Ӷ���O(n^2)���ܵıȽϴ�����n*(n-1)/2���ܵĽ���������n-1��
 */

/* �����������:
[********** Before SelectSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After SelectSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ѡ������
 *       ÿһ�˴Ӵ����������Ԫ����ѡ����С��һ��Ԫ�أ�˳��������ź�������е����ֱ��ȫ�������������Ԫ�����ꣻ
 *       ��Ҫ�������(nLength-1��)��ÿһ������Ľ������С������������ǰ�档
 * ����: SelectSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void SelectSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before SelectSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	SelectSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After SelectSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void SelectSort(int* pData, int nLength)
{
	// i: �������������������
	int i = 0;
	// j: ����������δ�������������һ�������У��������͵�1�����ȽϵĴ�����
	int j = 0;
	// nTempPos: ��¼��δ��������������ֵ��С��Ԫ�ص��±�λ�á�
	int nTempPos = 0;
	// nTemp: ��ʱ�����������������м������
	int nTempValue = 0;
	for (i = 0; i < nLength - 1; ++i)
	{
		nTempPos = i;
		for (j = i + 1; j < nLength; ++j)
		{
			if (pData[j] < pData[nTempPos])
			{
				nTempPos = j;
			}
		}
		if (nTempPos != i)
		{
			nTempValue = pData[i];
			pData[i] = pData[nTempPos];
			pData[nTempPos] = nTempValue;
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