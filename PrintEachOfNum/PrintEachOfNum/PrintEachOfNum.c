#include<stdio.h>
#include<math.h>
//��ӡһ��������ÿһλ���Ӹ�λ����λ
void PrintEachOfNum(int n)
{
	//������Ϊ����
	if (n < 0)
		n *= -1;

	//����n
	int n_copy = n;
	int count = 1;
	//�ó�������λ��
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
		//��ӡ���λ
		printf("%d ", n_copy / (int)(pow(10, count - 1)));
		n_copy %= (int)(pow(10, count - 1));
		//�ݹ����
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
