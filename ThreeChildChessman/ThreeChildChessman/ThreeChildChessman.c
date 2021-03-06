#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW 3
#define MAX_COL 3

//初始化棋盘
void init(char chessBoard[MAX_ROW][MAX_COL]){
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			//初始化都置为空
			chessBoard[row][col] = ' ';
		}
	}
}

//打印棋盘
void print_chessBoard(char chessBoard[MAX_ROW][MAX_COL]){
	printf("+---+---+---+\n");
	for (int row = 0; row <MAX_ROW; row++) {
		printf("| %c | %c | %c |\n", chessBoard[row][0],
			chessBoard[row][1], chessBoard[row][2]);
		printf("+---+---+---+\n");
	}
}

//玩家移动
void playerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = 0;
		int col = 0;
		printf("请输入坐标（row col）：");
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL){
			printf("您的坐标不在合法范围内 [0, 2],请重新输入：\n");
			continue;
		}
		if (chessBoard[row][col] != ' '){
			printf("您的坐标位置已经有子了!\n");
			continue;
		}
		chessBoard[row][col] = 'x';
		break;
	}
}

//电脑移动
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

//是否和棋：所有的子已经落完，明显无法分出胜负
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

//判断输赢
//返回'x':玩家赢    返回'o':电脑赢
//返回'q':和棋      返回' ':胜负未分
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

//游戏
void game(){
	//定义一个三行三列的二维数组
	char chessBoard[MAX_ROW][MAX_COL] = { 0 };
	//初始化棋盘为空
	init(chessBoard);
	//winner：游戏输赢的结果
	//初始化为‘ ’表示胜负未分
	char winner = ' ';
	while (1){
		//清屏
		system("cls");
		//打印出棋盘
		print_chessBoard(chessBoard);
		//玩家落子
		playerMove(chessBoard);
		//接收游戏结果
		winner = isWin(chessBoard);
		//如果游戏结果不是胜负未分，那么输赢已经出现或者出现和棋，游戏结束，跳出循环
		//如果游戏结果为胜负未分，继续游戏
		if (winner != ' ') {
			break;
		}
		//电脑落子
		computerMove(chessBoard);
		//接收游戏结果
		winner = isWin(chessBoard);
		//如果游戏结果不是胜负未分，那么输赢已经出现或者出现和棋，游戏结束，跳出循环
		//如果游戏结果为胜负未分，继续游戏
		if (winner != ' ') {
			break;
		}
	}
	//打印棋盘上的结果
	print_chessBoard(chessBoard);
	if (winner == 'x') {
		printf("恭喜您, 您赢了!\n");
	}
	else if (winner == 'o') {
		printf("哈哈，您连人工智障都下不过!\n");
	}
	else {
		printf("您只能和人工智障打平手!!\n");
	}
}


//菜单
int menu(){
	printf("--------------------------\n");
	printf("--------1.开始游戏--------\n");
	printf("--------0.退出游戏--------\n");
	printf("--------------------------\n");
	int choice = 0;
	printf("请输入你的选择：");
	scanf("%d", &choice);
	return choice;
}

int main()
{
	//将时间作为随机数种子，确保得到的行列坐标是真正的随机数
	srand((unsigned int)time(0));
	while (1){
		//接收用户输入的选择
		int choice = menu();
		if (choice == 1){
			game();
		}
		else if (choice == 0){
			printf("退出游戏,GOODBYE!!!!!!\n");
			break;
		}
		else{
			printf("输入错误！请重新输入！\n");
			continue;
		}
	}
	//来暂停程序执行，按任意键后将继续执行
	system("pause");
	return 0;
}
