# include <board.h>
# include <cstdio>
# include <cstring>
# include <algorithm>
# define ll long long
using namespace std;
int arr[10][10]={
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 1,-1, 0, 0, 0},
	{ 0, 0, 0, 0, 0,-1,-1,-1, 0, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 1, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
pair<pair<int, int>, double> min_max(Reversi_Board nowBoard, int depth, bool isMax, int alpha, int beta){ //返回一个坐标 和 最大/最小权值
	if (depth <= 0){
		return make_pair(make_pair(-1, -1), nowBoard.assess(1));
	}
	int cur = isMax ? 1: -1;
	double fnlWght;
	pair <int, int> fnlChs;
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			if (nowBoard.eat(0, i, j, cur) && nowBoard.board[i][j] == 0){
				Reversi_Board nxtBoard = nowBoard;
				nxtBoard.putchess(i, j, cur);
				double weight = min_max(nxtBoard, depth - 1, isMax ^ 1, alpha, beta).second;
				if (isMax && weight > fnlWght){
					fnlChs = make_pair(i, j);
					fnlWght = weight;
					alpha = weight;
				}
				if (!isMax && weight < fnlWght){
					fnlChs = make_pair(i, j);
					fnlWght = weight;
					beta = weight;
				}
				if (beta <= alpha) break;
			}
		}
	}
	return make_pair(fnlChs, fnlWght);
}
int main(){
	freopen("1.out", "w", stdout);
	Reversi_Board myBoard = Reversi_Board(arr);
	myBoard.prt();
	pair<pair<int, int>, double> rslt = min_max(myBoard, 5, 1, -1e9, 1e9);
	printf("%d %d %f\n", rslt.first.first, rslt.first.second, rslt.second);
	return 0;
}