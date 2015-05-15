#include <stdio.h>

/*
 * ȡ��ԭ��: ��Ϊ�ǰ��նѽṹ����Ƶ��㷨�����Գ���������
 * ƽ��ʱ�临�Ӷ�: O(nlogn)��
 * ƽ���ռ临�Ӷ�: O(1)��
 * ���в��ȶ��ԡ�
 * ��: ����Ϊn������{K1, K2, ..., Kn}������������������ͽ����ѣ�
 *     ��1 <= i <= n�ǣ�Ki >= K(i*2) �� Ki >= K(i*2+1)�����Ǵ���ѣ�����<=����С���ѣ�
       Ki�൱����ȫ�������еķ�Ҷ�ӽ�㣬k(i*2)�൱�����ӣ�k(i*2+1)�൱���Һ��ӣ�
 *     ���������ӽ����ڣ����׽���ֵҪ���ڻ�������Һ��ӵ�ֵ��
 * �ѵĸ߶�: O(logn)��
 */

/*
 * ��������ص�: 
 * ��������ʱ�临�Ӷ�ΪO(nlogn)�������ƽ�����ܽϽӽ�������ܡ�
 * �����������ڼ�¼�����ٵ��ļ�����Ϊ�����ʼ������ıȽϴ����϶ࡣ
 */

/* �����������:
[********** Before HeapSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After HeapSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ������
 *       ���Ȱ�[0, nLength - 1]������ݹ���ɶѣ�
 *       Ȼ�󾭹�nLength - 1����������ʹ[0, nLength - 1]�����������
 *       ÿһ�˵������������ģ��Ȱ�[0, i]���е�pData[0]��pData[i]���н�����
 *       ����iλ�õ�������[0, i]��Χ�������о��������ˣ���Ϊ����ǰ�Ǵ���ѣ�
 *       ��ʱ����pData[0]��ֵ�ı仯�����ڿ��ܲ��Ǵ�����ˣ�
 *       ������ҪΪpData[0]��[0, i - 1]����λ�ã�ʹ[0, i - 1]������ݻ��Ǵ���ѡ�
 * ����: HeapSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������������ĳ��ȡ�
 * ����ֵ: void��
 */
void HeapSort(int* pData, int nLength);

/*
 * ����: �ѵ�����
 *       ΪpData[nPos]ֵ��[0, nLength - 1]����λ�á�
 * ����: HeapAdjust��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength�����������ݵĳ��ȡ�
 * ����ֵ: void��
 */
void HeapAdjust(int* pData, int nPos, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before HeapSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	HeapSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After HeapSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void HeapSort(int* pData, int nLength)
{
	int nTemp = 0;
	int i = nLength / 2 - 1;

	// ��forѭ�����ʹ[0, nLength-1]�е����ݳ�Ϊ�˶ѡ�
	for (; i >= 0; --i)
	{
		// ΪpData[i]ֵ��λ�á�
		HeapAdjust(pData, i, nLength);
	}

	// ÿ��ѭ����[0, i]�е����ֵpData[0]��ĩβ��pData[i]ֵ���н�����
	for (i = nLength - 1; i > 0; --i)
	{
		// ����pData[0]��pData[i]��ֵ
		nTemp = pData[i];
		pData[i] = pData[0];
		pData[0] = nTemp;

		// ����pData[0]ֵ�ı��ˣ�������Ҫ������ʹ[0, i-1]�е����ݳ�Ϊ��
		HeapAdjust(pData, 0, i);
	}
}

void HeapAdjust(int* pData, int nPos, int nLength)
{
	int nTemp = pData[nPos];
	int nChild = 0;

	// ΪpData[nPos]ֵ��λ��i��
	// ��λ�ñ��������������������е�һ��:
	// (1) i * 2 >= nLength����i��Ҷ�ӽ�㣻
	// (2) i * 2 < nLength �� i * 2 + 1 >= nLength �� pData[i] >= pData[i * 2]����iֻ�����ӽ�㣻
	// (3) i * 2 + 1 < nLength �� pData[i] >= pData[i * 2] �� pData[i] >= pData[i * 2 + 1]����i�����Һ��ӽ�㡣
	for (; nPos * 2 + 1 < nLength; nPos = nChild)
	{
		// ����
		nChild = nPos * 2 + 1;
		if (nChild + 1 < nLength)
		{
			if (pData[nChild] < pData[nChild + 1])
			{
				// �Һ���
				++nChild;
			}
		}
		if (nTemp < pData[nChild])
		{
			pData[nPos] = pData[nChild];
			pData[nChild] = nTemp;
		}
		else
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