#include<stdio.h>
#include<stdlib.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

//交换
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//检查容量
void checkCapacity(Heap* hp)
{
	if (hp->_size == hp->_capacity)
	{
		int newC = hp->_capacity == 0 ? 1 : 2 * hp->_capacity;
		hp->_a = (HPDataType*)realloc(hp->_a, sizeof(HPDataType)* newC);	//realloc不需要关心内存拷贝的问题
		hp->_capacity = newC;
	}
}

/*
大堆的向下调整
调整的前提是调整的结点的左右孩子也是堆结构
从cur结点开始向下调整，n为元素的个数
*/
void BigHeapshiftDown(int* arr, int n, int cur)
{
	//找到孩子的位置
	//左孩子
	int child = 2 * cur + 1;
	while (child < n)
	{
		//从左右孩子中找一个最大的
		if (child + 1 < n && arr[child] < arr[child + 1])
			++child;

		//和当前数据进行比较
		//孩子>当前 --》调整
		if (arr[child] > arr[cur])
		{
			Swap(&arr[child], &arr[cur]);

			//更新位置，继续调整
			cur = child;
			child = 2 * cur + 1;
		}
		//孩子 <= 当前 --》不调整
		else
			break;
	}
}

//从当前节点cur,向上进行调整--------大堆的向上调整
void BigHeapshiftUp(int* arr, int n, int cur)
{
	//和父节点进行比较
	int parent = (cur - 1) / 2;

	while (cur > 0)
	{
		if (arr[cur] > arr[parent])
		{
			//当前节点小于父节点，调整
			Swap(&arr[cur], &arr[parent]);
			
			//更新,向上继续
			cur = parent;
			parent = (cur - 1) / 2;
		}
		else
			break;
	}
}

//堆的初始化
void HeapInit(Heap* hp)
{
	//先初始化
	if (hp == NULL)
		return;

	hp->_a = NULL;
	hp->_size = hp->_capacity = 0;
}

// 堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	//先初始化
	if (hp == NULL)
		return;

	hp->_a =(HPDataType*)malloc(sizeof(HPDataType)*n);
	hp->_size = 0;
	hp->_capacity = n;

	//把元素存进堆中
	for (int i = 0; i < n; ++i)
	{
		hp->_a[i] = a[i];
		hp->_size++;
	}

	/*
	堆的创建:从最后一个非叶子节点开始，向下调整
	最后一个叶子节点：n-1
	最后一个非叶子节点：（(n-1)-1）/ 2
	*/
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		BigHeapshiftDown(&hp->_a[i], n, i);
	}

}
// 堆的销毁
void HeapDestory(Heap* hp)
{
	free(hp->_a);
	hp->_size = hp->_capacity = 0;
	free(hp);
}

// 堆的插入
void HeapPush(Heap* hp, HPDataType x)
{
	if (hp == NULL)
		return;

	//检查容量够不够
	checkCapacity(hp);

	//尾插
	hp->_a[hp->_size++] = x;
	
	//向上调整
	BigHeapshiftUp(hp->_a, hp->_size, hp->_size - 1);
}
// 堆的删除，只能删除根节点
void HeapPop(Heap* hp)
{
	//将根节点和最后一个元素交换
	if (hp->_size > 0)
	{
		Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);

		//尾删
		--hp->_size;

		//从堆顶位置向下调整
		BigHeapshiftDown(hp->_a, hp->_size, 0);
	}
}
// 取堆顶的数据
HPDataType HeapTop(Heap* hp)
{
	return hp->_a[0];
}
// 堆的数据个数
int HeapSize(Heap* hp)
{
	return hp->_size;
}
// 堆的判空
int HeapEmpty(Heap* hp)
{
	if (hp == NULL || hp->_size == 0)
		return 1;
	else
		return 0;
}

// 对数组进行堆排序（从小到大排序）
void HeapSort(int* a, int n)
{
	int end = n - 1;
	
	while (end > 0)
	{
		//堆顶元素的交换+向下调整
		Swap(&a[0], &a[end]);
		BigHeapshiftDown(a, end, 0);
		end--;
	}
}

// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆
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
		printf("%d ", HeapTop(&hp));		//获取堆顶元素
		HeapPop(&hp);		//删除堆顶元素
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