#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * ����: ��·���������ǶԲ��������һ�ָĽ��������������ƶ��Ĵ�����
 * ƽ��ʱ�临�Ӷ�: O(n^2)��
 * �����ȶ��ԡ�
 */

/*
 * ��·��������Ĺؼ���: 
 * (1) �¿����˺ʹ�������������һ����С�Ŀռ䣻
 * (2) ���¿��ٵĿռ���nFirst��nFinal�ָ������С���3���֣�
 * (3) ����ȡ�������ֵ�Ļ������ԡ�
 */

/* �����������:
[********** Before TwoPathInsertSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After TwoPathInsertSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

/*
 * ����: ��·��������
 *       �¿���һ����pDataָ��ռ�һ����Ŀռ�pTempData����pDataָ��ĵ�1�����ݷŵ�pTempDataָ��ĵ�1�����ݣ�
 *       Ȼ���pData�ĵ�2�����ݿ�ʼ���������ұ���pData�е����ݣ�����(nLength-1)�ˣ�
 *       ÿ�˵�Ŀ����ΪpData[i]��pTempDataָ��Ŀռ�����λ�ò����룻
 *       ��λ�õķ����ǰ�pTempData�еĿռ���nFirst��nFinal�ָ���3���֣�
 *       nFirst������ʾ�������е�1������Ԫ�ص�λ�ã�nFinal������ʾ�����������1������Ԫ�ص�λ�ã�
 *       (1) ������������pData[i]С��nFirstָ������ݣ��Ͱ�pData[i]���뵽nFirst����ߣ�
 *       (2) ������������pData[i]����nFinalָ������ݣ��Ͱ�pData[i]���뵽nFinal���ұߣ�
 *       (3) ������������pData[i]���ڻ����nFirstָ���������С�ڻ����nFinalָ������ݣ�
 *           �ʹ�nFinalָ���λ�ÿ�ʼ��ǰ�ƶ���ΪpData[i]��λ�ò����롣
 *       �����pTempData[nFirst%nLength]��pTempData[(nFirst+nLength-1)%nLength]�������������ģ�
 *       ���Ѹ������������θ��Ƶ�pDataָ��Ŀռ��С�
 *       ע�⣺�ó����pTempDataָ����������ݿռ䵱��һ����������������pTempData[0]����ߵ�������pTempData[nLength-1]��
 * ����: TwoPathInsertSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������ĳ��ȡ�
 * ����ֵ: void��
 */
void TwoPathInsertSort(int* pData, int nLength);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before TwoPathInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	TwoPathInsertSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After TwoPathInsertSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void TwoPathInsertSort(int* pData, int nLength)
{
	// i: �����������������������������pData��
	int i = 0;
	// j: ���������ƶ����ݵĴ���������������pTempData��
	int j = 0;
	// nFirst: ��ʾ�������е�1������Ԫ�ص�λ�ã�����������pTempData��
	int nFirst = 0;
	// nFinal: ��ʾ�����������1������Ԫ�ص�λ�ã�����������pTempData��
	int nFinal = 0;
	// pTempData: ��ʱ���ݿ顣
	int* pTempData = (int*)malloc(sizeof(int) * nLength);
	memset(pTempData, 0, sizeof(int) * nLength);

	// pData�еĵ�1������Ԫ��ΪpTempData���ź��������Ԫ�ء�
	pTempData[0] = pData[0];
	
	for (i = 1; i < nLength; ++i)
	{
		if (pData[i] < pTempData[nFirst])
		{
			nFirst = (nFirst - 1 + nLength) % nLength;
			pTempData[nFirst] = pData[i];
		}
		else if (pData[i] > pTempData[nFinal])
		{
			++nFinal;
			pTempData[nFinal] = pData[i];
		}
		else
		{
			j = nFinal;
			while (pData[i] < pTempData[j])
			{
				pTempData[(j + 1) % nLength] = pTempData[j];
				j = (j - 1 + nLength) % nLength;
			}
			pTempData[j + 1] = pData[i];
			// ��Ϊ����������Ԫ�أ���������1
			++nFinal;
		}
	}

	// ��[nFirst % nLength, (nFirst + nLength - 1) % nLength]��������������θ��Ƶ������������С�
	for (i = 0; i < nLength; ++i)
	{
		pData[i] = pTempData[(nFirst + i) % nLength];
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