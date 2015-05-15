#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/*
 * ����: ���������Ƕ�ð�������һ�ָĽ���
 * ƽ��ʱ�临�Ӷ�: O(nlogn)��
 * ���в��ȶ��ԡ�
 */

/* �����������:
[********** Before NoRecursionQuickSort **********]
2, 46, 5, 17, 2, 3, 99, 12, 66, 21
[********** After NoRecursionQuickSort **********]
2, 2, 3, 5, 12, 17, 21, 46, 66, 99
*/

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct StackData
{
    int nLeft;
    int nRight;
} StackData;

typedef struct StackNode
{
    StackData data;
    struct StackNode* pNext;
} StackNode;

/*
 * ����: ��������(�ǵݹ�)��
 *       ��ջ��ʵ�ֿ�������ÿ�������ж��Ѵ��������еĵ�1��ֵ��Ϊ��ֵ��
 * ����: NoRecursionQuickSort��
 * ����: int* pData��ָ��һ���������顣
 * ����: int nLength������ĳ��ȡ�
 * ����ֵ: void��
 */
void NoRecursionQuickSort(int* pData, int nLength);

/*
 * ����: ��ջ��
 * ����: StackPush��
 * ����: StackNode** ppStackTop��ջ��ָ��ĵ�ַ��
 * ����: const StackData* pData����ջ���ݵĵ�ַ��
 * ����ֵ: void��
 */
void StackPush(StackNode** ppStackTop, const StackData* pData);

/*
 * ����: ��ջ��
 * ����: StackPop��
 * ����: StackNode** ppStackTop��ջ��ָ��ĵ�ַ��
 * ����: StackData* pData�������������Ŀ�ʼ�±�λ�á�
 * ����ֵ: BOOL������TRUE��ʾ�ɹ�������FALSE��ʾʧ�ܡ�
 */
BOOL StackPop(StackNode** ppStackTop, StackData* pData);

/*
 * ����: �ж��Ƿ�ջΪ�ա�
 * ����: IsStackEmpty��
 * ����: const StackNode* pStackTop��ջ��ָ�롣
 * ����ֵ: BOOL������TRUE��ʾ�ɹ�������FALSE��ʾʧ�ܡ�
 */
BOOL IsStackEmpty(const StackNode* pStackTop);
void Output(const int* pData, int nLength);

int main()
{
	int arrData[10] = {2, 46, 5, 17, 2, 3, 99, 12, 66, 21};

	printf("[********** Before NoRecursionQuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	NoRecursionQuickSort(arrData, sizeof(arrData) / sizeof(int));

	printf("[********** After NoRecursionQuickSort **********]\n");
	Output(arrData, sizeof(arrData) / sizeof(int));

	return 0;
}

void NoRecursionQuickSort(int* pData, int nLength)
{
    int i = 0;
    int j = 0;
    int nLeft = 0;
    int nRight = 0;
    int nTemp = 0;
    int nTop = 0;
    StackNode* pStackTop = NULL;

    StackData data;
    data.nLeft = 0;
    data.nRight = nLength - 1;
    StackPush(&pStackTop, &data);

    while (!IsStackEmpty(pStackTop))
    {
        BOOL bPopSuccess = StackPop(&pStackTop, &data);
        if (!bPopSuccess)
        {
            break;
        }
        nLeft = data.nLeft;
        nRight = data.nRight;

        i = nLeft;
        j = nRight;
        if (nLeft < nRight)
        {
            // ������ߵ�ֵ��Ϊ��ֵ��
            nTemp = pData[nLeft];
            while (i < j)
            {
                while (i < j && pData[j] > nTemp)
                {
                    --j;
                }
                if (i < j)
                {
                    pData[i] = pData[j];
                    ++i;
                }

                while (i < j && pData[i] < nTemp)
                {
                    ++i;
                }
                if (i < j)
                {
                    pData[j] = pData[i];
                    --j;
                }
                // ��ֵ���±�λ����i��
                // ��ǰ�Ľ���ǣ�
                //     [nLeft, i - 1]�ε����ݶ�С�ڻ����iλ�õ����ݣ�iλ�õ�����С�ڻ����[i + 1, nRight]�ε����ݡ�
                pData[i] = nTemp;

                // ��[nLeft, i - 1]ѹ��ջ�У��Ժ��ȡ�����Ըö����ݽ�������
                data.nLeft = nLeft;
                data.nRight = i - 1;
                StackPush(&pStackTop, &data);

                // ��[i + 1, nRight]ѹ��ջ�У��Ժ��ȡ�����Ըö����ݽ�������
                data.nLeft = i + 1;
                data.nRight = nRight;
                StackPush(&pStackTop, &data);
            }
        }
    }

    assert(IsStackEmpty(pStackTop));
}

void StackPush(StackNode** ppStackTop, const StackData* pData)
{
    StackNode* pStackNode = (StackNode*)malloc(sizeof(StackNode));
    pStackNode->data = *pData;
    pStackNode->pNext = *ppStackTop;
    *ppStackTop = pStackNode;
}

BOOL StackPop(StackNode** ppStackTop, StackData* pData)
{
    if (ppStackTop != NULL && *ppStackTop != NULL)
    {
        StackNode* pPopStackNode = *ppStackTop;
        pData->nLeft = pPopStackNode->data.nLeft;
        pData->nRight = pPopStackNode->data.nRight;
        *ppStackTop = pPopStackNode->pNext;

		pPopStackNode->pNext = NULL;
        free(pPopStackNode);
        pPopStackNode = NULL;
        return TRUE;
    }
    return FALSE;
}

BOOL IsStackEmpty(const StackNode* pStackTop)
{
    if (pStackTop == NULL)
    {
        return TRUE;
    }
    return FALSE;
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