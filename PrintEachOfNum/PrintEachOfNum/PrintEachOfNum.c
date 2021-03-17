#include<stdio.h>
#include<math.h>
//打印一个整数的每一位，从高位到低位
void PrintEachOfNum(int n)
{
	//负数变为整数
	if (n < 0)
		n *= -1;

	//保存n
	int n_copy = n;
	int count = 1;
	//得出整数的位数
	while (n/10 != 0)
	{
		count++;
		n /= 10;
	}

	if (count == 1)
	{
		printf("%d ", n_copy);
	}
	else
	{
		//打印最高位
		printf("%d ", n_copy / (int)(pow(10, count - 1)));
		n_copy %= (int)(pow(10, count - 1));
		//递归调用
		PrintEachOfNum(n_copy);
	}
}
void main()
{
	PrintEachOfNum(123456);
	printf("\n");
	PrintEachOfNum(0);
	printf("\n");
	PrintEachOfNum(-1314);
	printf("\n");
}
