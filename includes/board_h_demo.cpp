#include <iostream>
#include <cstdio>

/*
 * 一定引入 board.h 头文件
 * 一定引入 board.h 头文件
 * 一定引入 board.h 头文件
 */
#include "board.h"

using namespace std;
int arr[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,-1,0,0,0,0,0,0},
	{0,0,0,1,-1,1,0,0,0,0},
	{0,0,0,0,1,-1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
};
int main(){
	/*
	 * 表示棋盘的所有数组下标全部为1-8
	 * 结构体内有一 8*8 数组board，存储棋盘信息
	 * 数组中的表示
	 *  1 黑棋（先手）
	 * -1 白棋（后手）
	 * 空地  0
	 */
	Reversi_Board myboard;//新建棋盘

	/*
	 * eat函数
	 * 判断黑方能否在(2,2)下子
	 * 4个参数，第一个参数一定填0
	 * 第二三个参数表示下棋坐标
	 * cur 表示下棋者是哪方
	 * 返回值非零就表示可以下
	 */
	cout<<(myboard.eat(0,2,2,1)?"valid":"invalid!")<<endl;

	/*
	 * putchess函数(用来下一个棋，下完后会自动翻转能吃掉的子)
	 * 参数为
	 * 坐标及身份(1或者-1)
	 * 失败返回0
	 * 成功返回1
	 */
	myboard.putchess(5,6,1);


	//输出棋盘
	myboard.prt();

	//自动下
	myboard.auto_putchess(-1);
	
	//输出棋盘
	myboard.prt();

	//没有图形的输出
	myboard.raw_prt();


	/*
	 * assess函数
	 * 对于某一方，棋盘的估价
	 * 比如对黑方越有利则估价越高，参数就是1
	 */
	cout<<"value to black: "<<myboard.assess(1)<<endl;


	/*
	 * 支持导入棋局
	 * 不要尝试在结构体外头自己写循环赋值导入board数组！
	 */
	myboard=Reversi_Board(arr);


	/*
	 * 判断哪方胜利
	 * 尚未分出胜负 -2
	 * 平局返回 0
	 * 黑方胜利返回 1
	 * 白方胜利返回 -1
	 */
	cout<<myboard.win();
	
	return 0;
}
