#include <stdio.h>

/*
 * ȡ��ԭ��: ���������зָ������С�������зֱ���в�������ÿһ������ָ�ɵ������еĳ������𽥼�С��ֱ�����ٵ�1��
 *           ����D.L. Shell��ƺ�ʵ���˸��㷨�����Գ���ϣ������
 * ƽ��ʱ�临�Ӷ�: O(n^1.5)��
 * ƽ���ռ临�Ӷ�: O(1)��
 * ���в��ȶ��ԡ�
 * ϣ���������ڲ����������ֱ�������С��������
 */

/*
 * ϣ������Ĺؼ��㣺ʹ���������������С�
 * �ó���ʹ�õ�����������{n/(2^1), n/(2^2), n/(2^3), n/(2^k), ..., 1}��
 * ��������������{n/(3^1), n/(3^2), n/(3^3), n/(3^k), ..., 1}��
 */

/* �����������:
[********** Before ShellSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After ShellSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ϣ������
 *       ��������ʹ����������{nLength/(2^1), nLength/(2^2), nLength/(2^3), nLength/(2^k), ..., 1}�е�����ֵ��
 *       ÿһ������ֵ����Ҫ����һ���������һ������ֵ������1����������֤���յ���������
 *       ��һ�������У����������ȡ��[nIncrement, nLength-1]�е�ֵi����ʹ�ò��������pData[i]�����������˳����뵽
 *       ��������{..., i-nIncrement*k, ..., i-nIncrement*3, i-nIncrement*2, i-nIncrement}�С�
 * ����: ShellSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void ShellSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before ShellSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	ShellSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After ShellSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void ShellSort(int* pData, int nLength)
{
	// i: ����ÿ��ѭ����[nIncrement, nLength-1]�Ĵ�����
	int i = 0;
	// j: ���������ʾ����ֵ{..., i-nIncrement*k, ..., i-nIncrement*3, i-nIncrement*2, i-nIncrement}��
	int j = 0;
	// nTemp: ��ʱ�������������Ҫ����ı���ֵpData[i]��
	int nTemp = 0;
	// nIncrement: ������
	int nIncrement = nLength / 2;

	// nIncrement�ĵ����ڶ���ֵһ����1��
	for (; nIncrement > 0; nIncrement /= 2)
	{
		for (i = nIncrement; i < nLength; ++i)
		{
			// ʹ�ò������򣬰�pData[i]�����������˳����뵽
			// ��������{..., i-nIncrement*k, ..., i-nIncrement*3, i-nIncrement*2, i-nIncrement}�С�
			if (pData[i] < pData[i - nIncrement])
			{
				nTemp = pData[i];
				j = i - nIncrement;
				do
				{
					pData[j + nIncrement] = pData[j];
					j -= nIncrement;
				} while (j >= 0 && nTemp < pData[j]);
				if (j + nIncrement != i)
				{
					pData[j + nIncrement] = nTemp;
				}
			}
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