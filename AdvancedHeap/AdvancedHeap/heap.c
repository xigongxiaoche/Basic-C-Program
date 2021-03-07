#include<stdio.h>
#include<stdlib.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

//����
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//�������
void checkCapacity(Heap* hp)
{
	if (hp->_size == hp->_capacity)
	{
		int newC = hp->_capacity == 0 ? 1 : 2 * hp->_capacity;
		hp->_a = (HPDataType*)realloc(hp->_a, sizeof(HPDataType)* newC);	//realloc����Ҫ�����ڴ濽��������
		hp->_capacity = newC;
	}
}

/*
��ѵ����µ���
������ǰ���ǵ����Ľ������Һ���Ҳ�Ƕѽṹ
��cur��㿪ʼ���µ�����nΪԪ�صĸ���
*/
void BigHeapshiftDown(int* arr, int n, int cur)
{
	//�ҵ����ӵ�λ��
	//����
	int child = 2 * cur + 1;
	while (child < n)
	{
		//�����Һ�������һ������
		if (child + 1 < n && arr[child] < arr[child + 1])
			++child;

		//�͵�ǰ���ݽ��бȽ�
		//����>��ǰ --������
		if (arr[child] > arr[cur])
		{
			Swap(&arr[child], &arr[cur]);

			//����λ�ã���������
			cur = child;
			child = 2 * cur + 1;
		}
		//���� <= ��ǰ --��������
		else
			break;
	}
}

//�ӵ�ǰ�ڵ�cur,���Ͻ��е���--------��ѵ����ϵ���
void BigHeapshiftUp(int* arr, int n, int cur)
{
	//�͸��ڵ���бȽ�
	int parent = (cur - 1) / 2;

	while (cur > 0)
	{
		if (arr[cur] > arr[parent])
		{
			//��ǰ�ڵ�С�ڸ��ڵ㣬����
			Swap(&arr[cur], &arr[parent]);
			
			//����,���ϼ���
			cur = parent;
			parent = (cur - 1) / 2;
		}
		else
			break;
	}
}

//�ѵĳ�ʼ��
void HeapInit(Heap* hp)
{
	//�ȳ�ʼ��
	if (hp == NULL)
		return;

	hp->_a = NULL;
	hp->_size = hp->_capacity = 0;
}

// �ѵĹ���
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	//�ȳ�ʼ��
	if (hp == NULL)
		return;

	hp->_a =(HPDataType*)malloc(sizeof(HPDataType)*n);
	hp->_size = 0;
	hp->_capacity = n;

	//��Ԫ�ش������
	for (int i = 0; i < n; ++i)
	{
		hp->_a[i] = a[i];
		hp->_size++;
	}

	/*
	�ѵĴ���:�����һ����Ҷ�ӽڵ㿪ʼ�����µ���
	���һ��Ҷ�ӽڵ㣺n-1
	���һ����Ҷ�ӽڵ㣺��(n-1)-1��/ 2
	*/
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		BigHeapshiftDown(&hp->_a[i], n, i);
	}

}
// �ѵ�����
void HeapDestory(Heap* hp)
{
	free(hp->_a);
	hp->_size = hp->_capacity = 0;
	free(hp);
}

// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x)
{
	if (hp == NULL)
		return;

	//�������������
	checkCapacity(hp);

	//β��
	hp->_a[hp->_size++] = x;
	
	//���ϵ���
	BigHeapshiftUp(hp->_a, hp->_size, hp->_size - 1);
}
// �ѵ�ɾ����ֻ��ɾ�����ڵ�
void HeapPop(Heap* hp)
{
	//�����ڵ�����һ��Ԫ�ؽ���
	if (hp->_size > 0)
	{
		Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);

		//βɾ
		--hp->_size;

		//�ӶѶ�λ�����µ���
		BigHeapshiftDown(hp->_a, hp->_size, 0);
	}
}
// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp)
{
	return hp->_a[0];
}
// �ѵ����ݸ���
int HeapSize(Heap* hp)
{
	return hp->_size;
}
// �ѵ��п�
int HeapEmpty(Heap* hp)
{
	if (hp == NULL || hp->_size == 0)
		return 1;
	else
		return 0;
}

// ��������ж����򣨴�С��������
void HeapSort(int* a, int n)
{
	int end = n - 1;
	
	while (end > 0)
	{
		//�Ѷ�Ԫ�صĽ���+���µ���
		Swap(&a[0], &a[end]);
		BigHeapshiftDown(a, end, 0);
		end--;
	}
}

// TopK���⣺�ҳ�N�����������/��С��ǰK�����⡣
// ���磺δ��������ǰ10�����ɣ�������ͨ��ѧ������ҫ����ǰ10�ĺ��ţ�ȫ������ǰ10����ס��ȵ����ⶼ��Topk���⣬
// ��Ҫע�⣺
// ������ǰK��������K������С��
// ����С��ǰK��������K�����Ĵ��
void PrintTopK(int* a, int n, int k)
{
	Heap hp;
	HeapInit(&hp);
	
	for (int i = 0; i < n; ++i)
	{
		HeapPush(&hp, a[i]);
	}

	for (int i = 0; i < k; ++i)
	{
		printf("%d ", HeapTop(&hp));		//��ȡ�Ѷ�Ԫ��
		HeapPop(&hp);		//ɾ���Ѷ�Ԫ��
	}
	printf("\n");
}

void TestTopk()
{
	int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	PrintTopK(&arr, n, 6);
}

int main()
{
	TestTopk();
	return 0;
}