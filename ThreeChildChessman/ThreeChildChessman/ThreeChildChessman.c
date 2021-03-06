#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW 3
#define MAX_COL 3

//��ʼ������
void init(char chessBoard[MAX_ROW][MAX_COL]){
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			//��ʼ������Ϊ��
			chessBoard[row][col] = ' ';
		}
	}
}

//��ӡ����
void print_chessBoard(char chessBoard[MAX_ROW][MAX_COL]){
	printf("+---+---+---+\n");
	for (int row = 0; row <MAX_ROW; row++) {
		printf("| %c | %c | %c |\n", chessBoard[row][0],
			chessBoard[row][1], chessBoard[row][2]);
		printf("+---+---+---+\n");
	}
}

//����ƶ�
void playerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = 0;
		int col = 0;
		printf("���������꣨row col����");
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL){
			printf("�������겻�ںϷ���Χ�� [0, 2],���������룺\n");
			continue;
		}
		if (chessBoard[row][col] != ' '){
			printf("��������λ���Ѿ�������!\n");
			continue;
		}
		chessBoard[row][col] = 'x';
		break;
	}
}

//�����ƶ�
void computerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (chessBoard[row][col] != ' ') {
			continue;
		}
		chessBoard[row][col] = 'o';
		break;
	}
}

//�Ƿ���壺���е����Ѿ����꣬�����޷��ֳ�ʤ��
int isFull(char chessBoard[MAX_ROW][MAX_COL]){
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			if (chessBoard[row][col] == ' '){
				return 0;
			}

		}
	}
	return 1;
}

//�ж���Ӯ
//����'x':���Ӯ    ����'o':����Ӯ
//����'q':����      ����' ':ʤ��δ��
char isWin(char chessBoard[MAX_ROW][MAX_COL]){
	for (int row = 0; row < MAX_ROW; row++) {
		if (chessBoard[row][0] != ' '
			&& chessBoard[row][0] == chessBoard[row][1]
			&& chessBoard[row][0] == chessBoard[row][2]) {
			return chessBoard[row][0];
		}
	}
	for (int col = 0; col < MAX_COL; col++) {
		if (chessBoard[0][col] != ' '
			&& chessBoard[0][col] == chessBoard[1][col]
			&& chessBoard[0][col] == chessBoard[2][col]) {
			return chessBoard[0][col];
		}
	}
	if (chessBoard[0][0] != ' '
		&& chessBoard[0][0] == chessBoard[1][1]
		&& chessBoard[0][0] == chessBoard[2][2]) {
		return chessBoard[0][0];
	}
	if (chessBoard[2][0] != ' '
		&& chessBoard[2][0] == chessBoard[1][1]
		&& chessBoard[2][0] == chessBoard[0][2]) {
		return chessBoard[2][0];
	}
	if (isFull(chessBoard)) {
		return 'q';
	}
	return ' ';
}

//��Ϸ
void game(){
	//����һ���������еĶ�ά����
	char chessBoard[MAX_ROW][MAX_COL] = { 0 };
	//��ʼ������Ϊ��
	init(chessBoard);
	//winner����Ϸ��Ӯ�Ľ��
	//��ʼ��Ϊ�� ����ʾʤ��δ��
	char winner = ' ';
	while (1){
		//����
		system("cls");
		//��ӡ������
		print_chessBoard(chessBoard);
		//�������
		playerMove(chessBoard);
		//������Ϸ���
		winner = isWin(chessBoard);
		//�����Ϸ�������ʤ��δ�֣���ô��Ӯ�Ѿ����ֻ��߳��ֺ��壬��Ϸ����������ѭ��
		//�����Ϸ���Ϊʤ��δ�֣�������Ϸ
		if (winner != ' ') {
			break;
		}
		//��������
		computerMove(chessBoard);
		//������Ϸ���
		winner = isWin(chessBoard);
		//�����Ϸ�������ʤ��δ�֣���ô��Ӯ�Ѿ����ֻ��߳��ֺ��壬��Ϸ����������ѭ��
		//�����Ϸ���Ϊʤ��δ�֣�������Ϸ
		if (winner != ' ') {
			break;
		}
	}
	//��ӡ�����ϵĽ��
	print_chessBoard(chessBoard);
	if (winner == 'x') {
		printf("��ϲ��, ��Ӯ��!\n");
	}
	else if (winner == 'o') {
		printf("�����������˹����϶��²���!\n");
	}
	else {
		printf("��ֻ�ܺ��˹����ϴ�ƽ��!!\n");
	}
}


//�˵�
int menu(){
	printf("--------------------------\n");
	printf("--------1.��ʼ��Ϸ--------\n");
	printf("--------0.�˳���Ϸ--------\n");
	printf("--------------------------\n");
	int choice = 0;
	printf("���������ѡ��");
	scanf("%d", &choice);
	return choice;
}

int main()
{
	//��ʱ����Ϊ��������ӣ�ȷ���õ������������������������
	srand((unsigned int)time(0));
	while (1){
		//�����û������ѡ��
		int choice = menu();
		if (choice == 1){
			game();
		}
		else if (choice == 0){
			printf("�˳���Ϸ,GOODBYE!!!!!!\n");
			break;
		}
		else{
			printf("����������������룡\n");
			continue;
		}
	}
	//����ͣ����ִ�У���������󽫼���ִ��
	system("pause");
	return 0;
}
