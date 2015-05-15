#include <stdio.h>

/*
 * ȡ��ԭ��: ��һ�����ݲ��뵽�Ѿ��ź�������������У��Ӷ��õ�һ���µġ�������һ���������ݣ����Գ�����������
 * ƽ��ʱ�临�Ӷ�: O(n^2)��
 * �ռ临�Ӷ�: O(1)��
 * �����ȶ��ԡ�
 * ��̸��ӶȺܵͣ�������д�����롣
 * �㷨�������������ݵ�������Ϊ���ڴ��������ݵ��ƶ�(����)��
 */

/* ʱ�临�Ӷȷ���
 * �ܵıȽϴ���: [3*(n-1), (n+1)*(n-1)]
 * �ܵĽ�������: [0, (n-1)*(n+2)/2]
 * 
 * ������: �Ѿ�����ʱ�临�Ӷ���O(n)���ܵıȽϴ�����3*(n-1)���ܵĽ���������0��
 * ����: ����ʱ�临�Ӷ���O(n^2)���ܵıȽϴ�����(n+1)*(n-1)���ܵĽ���������(n-1)*(n+2)/2��
 */

/* �����������:
[********** Before InsertSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After InsertSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ��������
 *       ��һ�����ݲ��뵽�Ѿ��ź�������������У��Ӷ��õ�һ���µġ�������һ���������ݣ�
 *       ÿһ�˰��������ݵ���һ��Ԫ�ز��뵽�����������У���Ԫ�غ����������а����������˳��õ���Ԫ�����ν��бȽϣ�
 *       ��Ҫ�������(nLength-1��)��ÿһ������Ľ����ǰ����������ݸ�����һ������
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void InsertSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before InsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	InsertSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After InsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void InsertSort(int* pData, int nLength)
{
	// i: �������������������
	int i = 1;
	// j: ����������һ�������У���ǰҪ�����������ǰ�����е����ıȽϴ�����
	int j = 0;
	// ��ʱ�������������浱ǰҪ���������
	int nTempValue = 0;
	for (; i < nLength; ++i)
	{
		nTempValue = pData[i];
		j = i - 1;
		while (j >= 0 && nTempValue < pData[j])
		{
			pData[j + 1] = pData[j];
			--j;
		}
		if (j + 1 != i)
		{
			pData[j + 1] = nTempValue;
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