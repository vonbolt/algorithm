#include <stdio.h>

/*
 * ȡ��ԭ��: ��һ�����ݲ��뵽�Ѿ��ź�������������У��Ӷ��õ�һ���µġ�������һ���������ݣ�
 *           ���������������в��Ҳ�������λ��ʱʹ���˶��ֲ��ң����Գ������ֲ�������
 * ƽ��ʱ�临�Ӷ�: O(n^2)��
 * �ռ临�Ӷ�: O(1)��
 * �����ȶ��ԡ�
 * ��̸��ӶȺܵͣ�������д�����롣
 * �㷨�������������ݵ�������Ϊ���ڴ��������ݵ��ƶ�(����)��
 */

/* ʱ�临�Ӷȷ���
 * �ܵıȽϴ���: (n-1)*(n+8)/2
 * �ܵĽ�������: [0, (n+2)*(n-1)/2]
 *
 * ������: �Ѿ�����ʱ�临�Ӷ���O(n^2)���ܵıȽϴ�����(n-1)*(n+8)/2���ܵĽ���������0��
 * ����: ����ʱ�临�Ӷ���O(n^2)���ܵıȽϴ�����(n-1)*(n+8)/2���ܵĽ���������(n+2)*(n-1)/2��
 */

/* �����������:
[********** Before BinaryInsertSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After BinaryInsertSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ���ֲ�������(�۰��������)��
 *       ��һ�����ݲ��뵽�Ѿ��ź�������������У��Ӷ��õ�һ���µġ�������һ���������ݣ�
 *       ÿһ�˰��������ݵ���һ��Ԫ�ز��뵽�����������У���Ԫ�غ����������а����ֲ��ҵõ���Ԫ�����ν��бȽϣ�
 *       ��Ҫ�������(nLength-1��)��ÿһ������Ľ����ǰ����������ݸ�����һ������
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void BinaryInsertSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before BinaryInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	BinaryInsertSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After BinaryInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void BinaryInsertSort(int* pData, int nLength)
{
	// i: �������������������
	int i = 1;
	// j: ����������һ�������У�������Ԫ�ز���λ�ú�����������ݵ��ƶ�������
	int j = 0;
	// ��ʱ�������������浱ǰҪ���������
	int nTempValue = 0;

	int nLeft = 0;
	int nMiddle = 0;
	int nRight = 0;

	for (; i < nLength; ++i)
	{
		nTempValue = pData[i];

		// �����ֲ���
		nLeft = 0;
		nRight = i - 1;
		while (nLeft <= nRight)
		{
			nMiddle = (nLeft + nRight) / 2;
			if (pData[nMiddle] <= nTempValue)
			{
				nLeft = nMiddle + 1;
			}
			else
			{
				nRight = nMiddle - 1;
			}
		}

		// nTempValue�Ĳ���λ����nLeft
		// ע��: ��ʱ��nLeft = nRight + 1
		for (j = i; j > nLeft; --j)
		{
			pData[j] = pData[j - 1];
		}
		if (nLeft != i)
		{
			pData[nLeft] = nTempValue;
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