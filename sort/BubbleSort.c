#include <stdio.h>

/*
 * ȡ��ԭ��: �������������������С����ǰ�ţ���������ţ��൱�����������������Գ���ð������
 * ƽ��ʱ�临�Ӷ�: O(n^2)��
 * �ռ临�Ӷ�: O(1)��
 * �����ȶ��ԡ�
 * ��̸��ӶȺܵͣ�������д�����롣
 */

/* ʱ�临�Ӷȷ���
 * �ܵıȽϴ���: [n-1, n*(n-1)/2]
 * �ܵĽ�������: [0, n*(n-1)/2]
 *
 * ������: �Ѿ�����ʱ�临�Ӷ���O(n)���ܵıȽϴ�����n-1���ܵĽ���������0��
 * ����: ����ʱ�临�Ӷ���O(n^2)���ܵıȽϴ�����(n-1)+(n-2)+...+1=n*(n-1)/2���ܵĽ���������(n-1)+(n-2)+...+1=n*(n-1)/2��
 */

/* �����������:
[********** Before BubbleSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After BubbleSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ð������
 *       ���αȽ����ڵ�����������С������ǰ�棬�������ں��棻
 *       ��Ҫ�������(nLength-1��)��ÿһ������Ľ���������������������
 * ����: BubbleSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void BubbleSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before BubbleSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	BubbleSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After BubbleSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void BubbleSort(int* pData, int nLength)
{
	// i: �������������������
	int i = 1;
	// j: ����������һ�������ڵ����ȽϵĴ�����
	int j = 0;
	// nTemp: ��ʱ�����������������м������
	int nTemp = 0;
	// nFlag: ����������������Ƿ��Ѿ�ȫ������Ϊ0��ʾȫ������Ϊ1��ʾ��������
	int nFlag = 0;
	for (; i < nLength; ++i)
	{
		nFlag = 0;
		for (j = 0; j < nLength - i; ++j)
		{
			if (pData[j] > pData[j + 1])
			{
				nTemp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = nTemp;
				nFlag = 1;
			}
		}
		if (nFlag == 0)
		{
			break;
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