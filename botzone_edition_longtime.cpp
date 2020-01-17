#include<iostream>
#include<cstdio>
#ifdef _WIN32
#include<windows.h>
#endif
#include<cstring>
#include<ctime>
#include<algorithm>
#define SIZE 8
#define NR 10
#define MAX_SEARCH 12
#define HT_SIZE 1000000
const int nxgo[8][2]={{-1,1},{-1,0},{-1,-1},{0,1},{1,-1},{1,0},{1,1},{0,-1}};
double train_speed=1;
const int terrain[10][10]={
	{  0,   0,   0,  0,  0,  0,  0,   0,   0},
	{  0, 100, -50, 20, 10, 10, 20, -50, 100},
	{  0, -50, -75, 10,  5,  5, 10, -75, -50},
	{  0,  20,  10,  5,  2,  2,  5,  10,  20},
	{  0,  10,   5,  2,  0,  0,  2,   5,  10},
	{  0,  10,   5,  2,  0,  0,  2,   5,  10},
	{  0,  20,  10,  5,  2,  2,  5,  10,  20},
	{  0, -50, -75, 10,  5,  5, 10, -75, -50},
	{  0, 100, -50, 20, 10, 10, 20, -50, 100},
	{  0,   0,   0,  0,  0,  0,  0,   0,   0}
};
unsigned long long board_hash[2][10][10]={
{
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0},
	{0U,6880564125076973460U,8324189626661103252U,18273013313536353004U,9680968481607266591U,5492320330231943804U,1249362745900412647U,160179827196583684U,6681710116497670309U,0},
	{0U,1508769556914029984U,15415643906805116207U,486100235785905806U,9947246947985066330U,14593476464710908444U,5204558755076186142U,9193345226612537840U,18039998673436205159U,0},
	{0U,4807433278066979240U,1635706424295147269U,11758715261254788729U,9453572104691090370U,17599186514115795539U,17218040696116590974U,7825202553757965241U,11331629225907237345U,0},
	{0U,2920812594559588416U,11280620404528885234U,2075229208224760943U,9230542178674550209U,4677042827364327542U,287918573564643801U,9147171852733279732U,14772579261011096114U,0},
	{0U,17511384049467264954U,15672751083188213461U,11120284664497817925U,15807033665981183858U,5987058041098856561U,17134698507899238288U,11956823493740220549U,2528957373664062997U,0},
	{0U,7824177812580278938U,24611691876890470U,12138132438791167003U,11347041215002591799U,13330524194470656193U,2543636495829569510U,16208975603279458898U,3252764369285659128U,0},
	{0U,2531180725562481936U,5549910741902475019U,10087486789654011021U,2323624920730739276U,2333723648593396068U,11689786842637011288U,9410669541618633983U,1626756346365148430U,0},
	{0U,7855006699904867692U,4468248172647203502U,13274692541110870001U,7924942984322083681U,14943013835775188439U,12552325516060801269U,8013377263012184989U,4380232981446971238U,0},
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0}
},
{
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0},
	{0U,14551515592020777080U,4823849562544556286U,10011598329503054321U,3276394181865583935U,480837640536690263U,9616561975051951394U,16413619954229161241U,16102083386597509907U,0},
	{0U,16455655125709783132U,13097603048799968574U,2557769112663562518U,14372140218105605893U,8668602070843897104U,14959307820543376574U,4147621103451302130U,4873987076167870808U,0},
	{0U,16776072393217450276U,6501928437302794753U,11831266000601400607U,2108218376515158235U,10521432051942128004U,7994370536239934554U,4549610295612737039U,10796029931026892250U,0},
	{0U,14494284575743034679U,1082037426959292057U,12609244668461923358U,10447887621414465285U,15458067462460738064U,4712924002240162083U,9475785636554852293U,17427659223159092084U,0},
	{0U,5650587863820349216U,6174135021917560474U,15579136525968145686U,6160515218314710192U,8452137823063306241U,6144106305003052551U,12708933124641721736U,16399122017912212421U,0},
	{0U,13737281093197659106U,14529551438036159895U,8554208011544343312U,11905853981891980393U,11809755174055254888U,13414322181094031590U,15366286782272460671U,6742129215521329446U,0},
	{0U,17754267428286986321U,14564332153346477519U,17542883574078649140U,16964851541241254805U,15550219440551551472U,6620732655983792846U,8888147703720615446U,17519482211064239010U,0},
	{0U,11258952966829779303U,13581543917194656235U,9084085038834421212U,2263737883562340577U,7803221793363816630U,5160131817510830895U,15677181952285801626U,15928173089446975721U,0},
	{0U,0U,0U,0U,0U,0U,0U,0U,0U,0}
}
};
const double trained[60][3]={
	{200.000000,50.000000,300.000000},
	{342.399267,50.000000,300.000000},
	{123.573570,26.812011,300.000000},
	{67.403450,97.114756,300.000000},
	{38.787090,50.431973,300.000000},
	{61.918028,65.501506,300.000000},
	{63.258364,66.540620,300.000000},
	{65.775479,117.881630,301.957603},
	{71.229492,53.424392,301.914344},
	{51.300562,182.608851,301.654103},
	{71.640343,-32.592268,304.324193},
	{47.389016,155.913446,309.061844},
	{76.146558,16.538875,309.743881},
	{48.720785,205.696993,333.799172},
	{82.361877,116.530088,315.909881},
	{51.330837,305.908609,357.189987},
	{87.772445,287.883905,359.922751},
	{54.027771,478.388985,408.011546},
	{94.324533,482.194458,421.473356},
	{55.289618,744.522106,501.035029},
	{100.687477,663.330860,386.159219},
	{55.407360,993.358201,693.326450},
	{105.916363,842.059909,471.335222},
	{52.954649,1535.119541,1046.177889},
	{106.485415,1181.752931,886.799360},
	{42.299535,2623.247800,1435.630267},
	{92.610019,2089.294686,1499.742114},
	{14.613625,4096.879821,2159.358971},
	{51.100458,3361.193940,2781.051996},
	{-21.913044,5327.028423,2647.947903},
	{6.532987,3911.619546,3853.263663},
	{-23.089185,4958.151230,3062.992129},
	{-4.101075,4344.196033,3319.760587},
	{11.751585,3255.565059,3523.198764},
	{6.768109,3826.932578,3149.701010},
	{34.387956,1854.677079,3825.167777},
	{23.673072,2867.530568,3295.995950},
	{31.555396,1576.317907,3675.472048},
	{30.926978,2109.052880,3342.675091},
	{26.224591,1440.410810,3476.743107},
	{30.919659,1500.781001,3288.413862},
	{21.596665,1475.778533,3215.610422},
	{30.879305,1124.348684,3173.821336},
	{20.263560,1278.979560,3084.697328},
	{25.691579,1002.827731,3047.161705},
	{21.043797,1332.634759,2860.584708},
	{18.477976,1093.853718,2878.455967},
	{20.964943,1325.162679,2675.065315},
	{6.178954,1162.844630,2770.329803},
	{14.807834,1214.287830,2595.166761},
	{3.665885,1292.818098,2590.839805},
	{10.375080,1130.712175,2491.116860},
	{5.909639,1188.295336,2452.599166},
	{9.079119,1038.671620,2390.666468},
	{8.318732,782.182674,2364.159294},
	{9.073038,878.520646,2287.556660},
	{17.459295,581.700616,2253.343311},
	{13.048135,643.529460,2201.955632},
	{29.889959,584.274759,2175.681438},
	{13.191873,-344.460105,2185.081120}
};
struct s_result{
	unsigned long long hash;
	double low,high;
	int bx,by,depth;
	s_result(unsigned long long hash=0,double low=-1e9,double high=1e9,int bx=-1,int by=-1,int depth=-1):hash(hash),low(low),high(high),bx(bx),by(by),depth(depth){}
};
struct s_save{
	s_result deepest,newest;
}hashtable[HT_SIZE];
bool cmp1(std::pair<int, double> x, std::pair<int, double> y){
	return x.second > y.second;
}
bool cmp2(std::pair<int, double> x, std::pair<int, double> y){
	return x.second < y.second;
}
struct Reversi_Board{
	/*
	 * 先手  1 黑棋
	 * 后手 -1 白棋
	 * 空地  0
	 */
	unsigned long long hash;
	int board[NR][NR],step;
	inline bool inboard(int x,int y){return (x>0 && x<=SIZE && y>0 && y<=SIZE);}
	double w[64][3];

	//init & print
	Reversi_Board(){
		for(int i=0;i<60;i++)
			for(int j=0;j<3;j++)
				w[i][j]=trained[i][j];
		step=0;
		memset(board,0,sizeof(board));
		board[4][4]=board[5][5]=-1;
		board[4][5]=board[5][4]=1;
		hash=0;
		hash^=board_hash[0][4][4];
		hash^=board_hash[0][5][5];
		hash^=board_hash[1][4][5];
		hash^=board_hash[1][5][4];
		srand(time(NULL));
	}
	Reversi_Board(int arr[NR][NR]){
		hash=0;
		step=-4;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				board[i][j]=arr[i][j];
				if(arr[i][j]){
					step++;
					hash^=board_hash[(arr[i][j]+1)>>1][i][j];
				}
			}
	}
	void init(){
		step=0;
		memset(board,0,sizeof(board));
		board[4][4]=board[5][5]=-1;
		board[4][5]=board[5][4]=1;
		hash=0;
		hash^=board_hash[0][4][4];
		hash^=board_hash[0][5][5];
		hash^=board_hash[1][4][5];
		hash^=board_hash[1][5][4];
	}

#ifdef _WIN32
	void prt(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
		std :: cout << "    A   B   C   D   E   F   G   H   ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std :: cout << std :: endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
		std :: cout << "  ┌───┬───┬───┬───┬───┬───┬───┬───┐ ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std :: cout << std :: endl;
		for(int i=1;i<=SIZE;i++){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
			std :: cout << ' ' << i;
			for(int j=1;j<=SIZE;j++){
				std :: cout << "│ ";
				if(board[i][j] == 0) {
					std :: cout << "  ";
				} else if(board[i][j] == 1) {
					std :: cout << "■ ";
				} else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
					std :: cout << "■ ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
			std :: cout << "│ ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std :: cout << "\n";
			if(i != SIZE) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
				std :: cout << "  ├───┼───┼───┼───┼───┼───┼───┼───┤ ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std :: cout << "\n";
			} else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
				std :: cout << "  └───┴───┴───┴───┴───┴───┴───┴───┘ " << std :: endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std :: cout << "\n";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
#endif
#ifndef _WIN32
	void prt(){

		printf("\033[30m");
		printf("\033[43m    A   B   C   D   E   F   G   H   ");
		printf("\033[40m\n");
		printf("\033[43m  ┌───┬───┬───┬───┬───┬───┬───┬───┐ ");
		printf("\033[40m\n");
		for(int i=1;i<=SIZE;i++){
			printf("\033[30m");
			printf("\033[43m%d ",i);
			for(int j=1;j<=SIZE;j++){
				printf("\033[30m");
				printf("\033[30m│ ");
				if(board[i][j] == 0) {
					printf("\033[43m  ");
				} else if(board[i][j] == 1) {
					printf("\033[30m");
					printf("\033[43m■ ");
				} else {
					printf("\033[37m");
					printf("\033[43m■ ");
				}
			}
			printf("\033[30m│ ");
			printf("\033[40m\n");
			if(i != SIZE) {
				printf("\033[43m");
				printf("\033[30m  ├───┼───┼───┼───┼───┼───┼───┼───┤ ");
				printf("\033[40m\n");
			} else {
				printf("\033[43m");
				printf("\033[30m  └───┴───┴───┴───┴───┴───┴───┴───┘ ");
				printf("\033[40m\n");
			}
		}
		printf("\033[37m");
		printf("\033[40m");
	}
#endif
	void raw_prt(){
		puts("    A B C D E F G H");
		puts("  +----------------+");
		for(int i=1;i<=SIZE;i++){
			putchar('0'+i);
			putchar(' ');
			putchar('|');
			for(int j=1;j<=SIZE;j++){
				putchar(' ');
				putchar(board[i][j]?(board[i][j]==1?'#':'o'):' ');
			}
			putchar('|');
			putchar('\n');
		}
		puts("  +----------------+");
	}
	

	//Calculation
	void hash_save(double low,double high,int bx,int by,int depth){
		unsigned int place=(hash)%HT_SIZE;
		if(hashtable[place].deepest.hash==hash && hashtable[place].deepest.depth==depth){
			if(hashtable[place].deepest.low<low){
				hashtable[place].deepest.low=low;
				hashtable[place].deepest.bx=bx;
				hashtable[place].deepest.by=by;
			}
			hashtable[place].deepest.high=std::min(hashtable[place].deepest.high,high);
		}
		else if(hashtable[place].newest.hash==hash && hashtable[place].newest.depth==depth){
			if(hashtable[place].newest.low<low){
				hashtable[place].newest.low=low;
				hashtable[place].newest.bx=bx;
				hashtable[place].newest.by=by;
			}
			hashtable[place].newest.high=std::min(hashtable[place].newest.high,high);
		}
		else if(depth>hashtable[place].deepest.depth){
			hashtable[place].newest=hashtable[place].deepest;
			hashtable[place].deepest.hash=hash;
			hashtable[place].deepest.low=low;
			hashtable[place].deepest.high=high;
			hashtable[place].deepest.bx=bx;
			hashtable[place].deepest.by=by;
			hashtable[place].deepest.depth=depth;
		}
		else{
			hashtable[place].deepest.hash=hash;
			hashtable[place].newest.low=low;
			hashtable[place].newest.high=high;
			hashtable[place].newest.bx=bx;
			hashtable[place].newest.by=by;
			hashtable[place].newest.depth=depth;
		}
	}
	s_result hash_get(int depth){
		unsigned int place=(hash)%HT_SIZE;
		if(hashtable[place].deepest.hash==hash && hashtable[place].deepest.depth==depth)return hashtable[place].deepest;
		else if(hashtable[place].newest.hash==hash && hashtable[place].newest.depth==depth)return hashtable[place].newest;
		else return s_result();
	}

	/*
	 * 判断是否有输赢
	 *  1是黑赢
	 * -1是白赢
	 *  0是平局
	 * -2是尚未分出胜负
	 */
	int win(){
		int black=0,white=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				if(board[i][j]==1)black++;
				else if(board[i][j]==-1)white++;
			}
		if(step==60 || (!choice(1) && !choice(-1))){
			if(black>white)return 1;
			else if(white>black)return -1;
			else return 0;
		}
		else{
			if(!white)return 1;
			else if(!black)return -1;
			else return -2;
		}
	}
	/*
	 * (可以用这个函数计算合理的走棋位置)
	 * 计算吃子的函数
	 * flip 表示是否翻转棋子
	 * cur 表示当前是哪方
	 * 返回值表示能反转多少个
	 */
	inline int eat(bool flip,int x,int y,int cur){
		int cnt=0;
		for(int pos=0;pos<8;pos++){
			int tx=x+nxgo[pos][0],ty=y+nxgo[pos][1],tcnt=0;
			//检验
			while(inboard(tx,ty) && board[tx][ty]==-cur)
				tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1],tcnt++;
			//符合翻的要求
			if(inboard(tx,ty) && board[tx][ty]==cur){
				cnt+=tcnt;
				if(flip){
					tx=x+nxgo[pos][0],ty=y+nxgo[pos][1];
					while(inboard(tx,ty) && board[tx][ty]==-cur){
						board[tx][ty]=cur;
						hash^=board_hash[0][tx][ty];
						hash^=board_hash[1][tx][ty];
						tx=tx+nxgo[pos][0];
						ty=ty+nxgo[pos][1];
					}
				}
			}
		}
		return cnt;
	}
	inline int terr(int cur){
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				if(board[i][j]==cur)cnt+=terrain[i][j];
		return cnt;
	}
	//返回cur可以下棋的地方个数
	inline int choice(int cur){
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				if(board[i][j]==0 && eat(0,i,j,cur))cnt++;
		return cnt;
	}
	//计算稳定子
	inline int not_threated(int cur){
		int cnt,ans=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				//如果不是空白不行
				if(board[i][j]!=cur)continue;
				cnt=0;
				for(int pos=0;pos<4;pos++){
					int meet1=-2,meet2=-2;
					int tx=i+nxgo[pos][0],ty=j+nxgo[pos][1];
					//检验
					while(inboard(tx,ty) && board[tx][ty]==cur)
						tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1];
					if(inboard(tx,ty))meet1=board[tx][ty];

					tx=i+nxgo[pos+4][0],ty=j+nxgo[pos+4][1];
					//检验
					while(inboard(tx,ty) && board[tx][ty]==cur)
						tx=tx+nxgo[pos+4][0],ty=ty+nxgo[pos+4][1];
					if(inboard(tx,ty))meet2=board[tx][ty];

					if(meet1==-2 || meet2==-2 ||(meet1==-cur && meet2==-cur))cnt++;
				}
				if(cnt==4)ans++;
			}
		return ans;
	}


	/*
	 * 对于cur，棋局状态如何
	 */
	inline double assess(int cur){
		int iswin=win();
		double ans;
		if(iswin!=-2){
			if(iswin==cur)ans=100000;
			else if(iswin==-cur)ans=-100000;
			else ans=0;
		}
		else ans=w[step][0]*(terr(cur)-terr(-cur))+
			w[step][1]*(choice(cur)-choice(-cur))+
			w[step][2]*(not_threated(cur)-not_threated(-cur));
		return ans;
	}
	void train(double o,double t,int cur){
		w[step][0]+=train_speed*(terr(cur)-terr(-cur))*(t-o);
		w[step][1]+=train_speed*(choice(cur)-choice(-cur))*(t-o);
		w[step][2]+=train_speed*(not_threated(cur)-not_threated(-cur))*(t-o);
	}


	//API
	

	/*
	 * 下一个子
	 * 坐标及身份
	 * 失败返回0
	 */
	inline bool putchess(int x,int y,int cur){
		if(!inboard(x,y) || board[x][y])return 0;
		step++;
		board[x][y]=cur;
		hash^=board_hash[(cur+1)>>1][x][y];
		eat(1,x,y,cur);
		return 1;
	}
	void rand_putchess(int cur){
		int curchoice=choice(cur);
		if(!curchoice)return;
		int choice_num=rand()%curchoice,cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				if(board[i][j]==0 && eat(0,i,j,cur)){
					if(cnt==choice_num){
						putchess(i,j,cur);
						return;
					}
					cnt++;
				}
			}
	}
	s_result min_max(Reversi_Board nowBoard, int depth, bool isMax, double alpha, double beta){ //返回一个坐标 和 最大/最小权值
		bool flag = false;
		if (depth == 0){
			double res=nowBoard.assess(1);
			return s_result(nowBoard.hash,res,res,-1,-1,0);
		}
		int winn = nowBoard.win();
		if (winn != -2)
			return s_result(s_result(nowBoard.hash,winn * 100000,winn * 100000,-1,-1,0));
		std::pair <int, int> pr[151]; //x & y
		std::pair <int, double> pr2[151]; // id & weight
		int cur = isMax ? 1: -1;
		int cnt = 0;
		double fnlWght = isMax ? -1e9 : 1e9;
		std::pair <int, int> fnlChs = std::make_pair(-1, -1);
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				if (nowBoard.eat(0, i, j, cur) && nowBoard.board[i][j] == 0){
					pr[++cnt] = std::make_pair(i, j);
					Reversi_Board nxtBoard = nowBoard;
					nxtBoard.putchess(i, j, cur);
					pr2[cnt] = std::make_pair(cnt, nxtBoard.assess(cur));
				}
		sort(pr2 + 1, pr2 + cnt + 1, isMax ? cmp1 : cmp2);
		for (int i = 1; i <= std::min(cnt, MAX_SEARCH); i++){
			int id = pr2[i].first;
			int nx = pr[id].first;
			int ny = pr[id].second;
			flag = true;
			Reversi_Board nxtBoard = nowBoard;
			nxtBoard.putchess(nx, ny, cur);
			double weight = hash_min_max(nxtBoard, depth - 1, !isMax, alpha, beta).low;
			if (isMax && weight > fnlWght){
				fnlChs = std::make_pair(nx, ny);
				fnlWght = weight;
				alpha = weight;
			}
			if (!isMax && weight < fnlWght){
				fnlChs = std::make_pair(nx, ny);
				fnlWght = weight;
				beta = weight;
			}
			if (beta <= alpha) break;
		}
		if (!flag) fnlWght=hash_min_max(nowBoard, depth, !isMax, alpha, beta).low;
		return s_result(nowBoard.hash,fnlWght,fnlWght,fnlChs.first,fnlChs.second,depth);
	}
	s_result hash_min_max(Reversi_Board nowBoard, int depth, bool isMax, double alpha, double beta){ //返回一个坐标 和 最大/最小权值

		s_result cur_his=nowBoard.hash_get(depth);
		if(cur_his.depth!=-1){
			if(alpha<cur_his.low){
				alpha=cur_his.low;
				if(alpha>=beta)return s_result(nowBoard.hash,alpha,alpha,cur_his.bx,cur_his.by,depth);
			}
			if(beta>cur_his.high){
				beta=cur_his.high;
				if(alpha>=beta)return s_result(nowBoard.hash,beta,beta,cur_his.bx,cur_his.by,depth);
			}
		}
		s_result full_res=min_max(nowBoard, depth, isMax, alpha, beta);
		double cur_w=full_res.low;
		if(cur_w>beta)
			nowBoard.hash_save(cur_w,1e9,full_res.bx,full_res.by,depth);
		else if(cur_w<alpha)
			nowBoard.hash_save(-1e9,cur_w,full_res.bx,full_res.by,depth);
		else 
			nowBoard.hash_save(cur_w,cur_w,full_res.bx,full_res.by,depth);
		return full_res;
	}
	s_result mtd(int cur,int depth){
		int test=0,alpha=-1e9,beta=1e9;
		int answ;
		s_result res;
		int bx=-1,by=-1;
		do {
			res = hash_min_max(*this, depth, (cur + 1) >> 1, test-1, test);
			answ=res.low;
			if (answ < test)test = beta = answ;
			else {
				alpha = answ;
				test = answ + 1;
				bx=res.bx,by=res.by;
			}
		} while (alpha < beta);
		return s_result(hash,answ,answ,bx,by,-1);
	}
	std::pair<int, int> auto_putchess(int cur){
		s_result pr;
		if(step>=50)pr=mtd(cur,7);
		else pr=mtd(cur,5);
		putchess(pr.bx, pr.by, cur);
		return std::make_pair(pr.bx, pr.by);
	}
};
#include<fstream>
int n;
int tx,ty;
int cur=1;
int player=1;
Reversi_Board myboard;
int main(){
	std::ofstream datasave;
	datasave.open("./data/gamedata.dat",std::ios::app);
	datasave<<"start"<<std::endl;
	scanf("%d",&n);n*=2,n--;
	scanf("%d%d",&ty,&tx);
	datasave<<tx<<" "<<ty<<std::endl;
	if(tx!=-1 && ty!=-1){
		ty++,tx++;
		myboard.putchess(tx,ty,1);
		cur=-cur;
	}
	while(1){
		if(player==1){
			std::pair<int, int> pr = myboard.auto_putchess(cur);
			if(!myboard.inboard(pr.first,pr.second))printf("-1 -1\n");
			else printf("%d %d\n",pr.second-1,pr.first-1);
			datasave<<pr.first<<" "<<pr.first<<std::endl;
			printf(">>>BOTZONE_REQUEST_KEEP_RUNNING<<<\n");
			fflush(stdout);
			
		}
		else{
			scanf("%d%d",&ty,&tx);
			ty++,tx++;
			datasave<<tx<<" "<<ty<<std::endl;
			myboard.putchess(tx,ty,cur);
		}
		cur=-cur;
		player=-player;
	}

	
	return 0;
}
