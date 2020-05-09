#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<set>
#include<stack>
#include<vector>
#include<map> 
#include<windows.h>
#include<ctime>
#include<stdlib.h> 
using namespace std;
const int maxn=12;//二维数组维度的最大规模 

int N,M,K,X;//N*M K是地图的元素种类 X是递归的深度，即交换次数 
int mp[maxn][maxn];// init map
stack<int> mp2[maxn][maxn];// 动态地图 
int vis[maxn][maxn];//储存每个元素的初始位置，当某个元素被消去时，把它相应的位置标记为当前的deep+1 
map<string,int> visited;//状态储存，string储存01矩阵地图的状态，int储存相应的分数和操作次数 
int dx[4]={0,1,0,-1};// right down left up
int dy[4]={1,0,-1,0};
int goal[3]={1,4,10}; 
int Ans;//储存当前最大分数 

//
inline bool Debug(int x1,int y1,int x2,int y2,int deep)
{
	return false;//
	return x1==0&&y1==1&&x2==1&&y2==1&&deep==1;//
	return x1==2&&y1==2&&x2==3&&y2==2&&deep==0;// 
//	       x1==3&&y1==0&&x2==4&&y2==0&&deep==1||//
//	       x1==4&&y1==0&&x2==4&&y2==1&&deep==2||
//	       x1==3&&y1==0&&x2==3&&y2==1&&deep==3||
//	       x1==7&&y1==2&&x2==7&&y2==3&&deep==4;
	       
	return x1==2&&y1==0&&x2==3&&y2==0&&deep==0;//;//
	       x1==5&&y1==1&&x2==5&&y2==2&&deep==1;//
	return x1==2&&y1==0&&x2==3&&y2==0||
		   x1==3&&y1==0&&x2==3&&y2==1||
		   x1==3&&y1==1&&x2==4&&y2==1||
	       x1==3&&y1==2&&x2==4&&y2==2||
	       x1==5&&y1==1&&x2==5&&y2==2;
}
// print map
void print_map2()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(mp2[i][j].empty()||mp2[i][j].top()==-1){//no value
				printf("-1 ");continue;
			}
			int cur=mp2[i][j].top();//
			cur%=K;
			printf("%d ",cur);
		}
		printf("\n");
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(mp2[i][j].empty()||mp2[i][j].top()==-1){
				printf("( , ) ");continue;
			}
			int cur=mp2[i][j].top();//
			cur/=K;
			printf("(%d,%d) ",cur/M,cur%M);
		}
		printf("\n");
	}
}
void print_map()
{
	//printf("------------\n");
	printf("\n\n");//
	printf("N:%d M:%d \n",N,M);
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			printf("%d ",mp[i][j]);
		}
		printf("\n");
	}
}
//判断两个元素的权值是否相同 
inline bool Equal(int val,int val2)
{
	return (val%K)==(val2%K);
}
//判断是否越界 
inline bool check(int x,int y)
{
	if(x<0||y<0||x>=N||y>=M)
		return false;
	return true;
}
//判断初始地图是否合法 
inline bool legal()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			for(int k=0;k<4;k++){//只需判断右下 
				int ans=1;
				int x=i+dx[k],y=j+dy[k];
				while(check(x,y)&&mp[x][y]==mp[i][j]){
					ans++;
					x+=dx[k];
					y+=dy[k];
				}
				if(ans>=3) return false;
			}
			
		}
	}
	return true;
}
//把当前地图的元素对应的原始坐标染色 
inline void Color(int x,int y,int deep)//染色 
{
	int cur=mp2[x][y].top();
	int xx=cur/K/M,yy=cur/K%M;
	vis[xx][yy]=deep+1;//
}
//回溯过程：当前元素对应的原始坐标去色 
inline void Decolor(int x,int y)//去色 
{
	if(mp2[x][y].empty()||mp2[x][y].top()==-1){
		printf("Decolor fail --- %d\n",mp2[x][y].top());//debug
		return;//
	}
	int cur=mp2[x][y].top();
	int xx=cur/K/M,yy=cur/K%M;
	vis[xx][yy]=0;
}

bool debug;//
//把当前位置push进一个元素，注意如果位置有-1要把它pop掉 
inline void Push(int x,int y,int val)
{
	while(!mp2[x][y].empty()&&mp2[x][y].top()==-1){
//		if(debug){
//			if(!mp2[x][y].empty()) 
//				printf("mp2[%d][%d].top:%d\n",x,y,mp2[x][y].top());//
//			else printf("	mp2[%d][%d].empty()\n",x,y);
//		}
		mp2[x][y].pop();
	}
	mp2[x][y].push(val);
}
//结构体 Down和Up过程要用到 
struct node{
	int minx,y,maxx,h;
	node(int x1,int y1,int x2,int h1):minx(x1),y(y1),maxx(x2),h(h1){}
};
stack<node> st,sk;

//恢复下降覆盖的一列(mp2[x][y],mp2[x2][y]) 
inline void Up(int x,int y,int x2,int h)
{
//	if(debug){
//		printf("min_x:%d max_x:%d y:%d h:%d\n",x,x2,y,h);
//	}
	for(int i=x;i<=x2;i++){
		int cur=mp2[i][y].top();
		mp2[i][y].pop();
		//Pop(i,y);
		if(i-h>=0&&cur!=-1) Push(i-h,y,cur);
	}
}
//消去了一列(mp2[x][y],mp2[x+h-1][y]) 上面的格子降h格 考虑只降了一部分，挡了一部分 
inline void Down(int x,int y,int h)
{
	int x1=0;
	while(mp2[x1][y].empty()||mp2[x1][y].top()==-1&&x1<x) x1++;
	if(mp2[x1][y].empty()||mp2[x1][y].top()==-1) x1++;// ++进一位代表没有元素 
	st.push(node(x1,y,x+h-1,h));//
	sk.push(node(x,y,x+h-1,h));//储存被消去的元素的位置，用于后面的回溯过程
	//if(debug) print_map2();//
	for(int i=x-1;i>=x1;i--){
		int cur=mp2[i][y].top();
		//Pop(i,y);
		mp2[i][y].pop();
		//mp2[i][y].push(-1);//Pop 
		mp2[i+h][y].push(cur);// Push
		//Push(i+h,y,cur);//if(i+h<N) 
	}
	//if(debug) print_map2();//
//	for(int i=x1+h-1;i>=x1;i--){//把没被覆盖的元素都置为-1 
//		mp2[i][y].push(-1);
//	}

	for(int i=x1+h-1;i>=x1;i--){//把没被覆盖的元素都置为-1 
		if(mp2[i][y].empty()||(!mp2[i][y].empty()&&mp2[i][y].top()!=-1))
			mp2[i][y].push(-1);//
	} 
	//if(debug) print_map2();//
}
bool row[12],col[12];//
struct State{
	int x,y;
}tmp3;
vector<State> cur3;
//判断该点和周围的点是否可以消去 
inline int judge(int x1,int y1,int deep,int& num)//return the score
{
	int cur,ans,minx,maxx;
	bool flag[2];
	flag[0]=flag[1]=0;
	if(mp2[x1][y1].empty()) cur=-1;//
	else cur=mp2[x1][y1].top();
	int x=x1,y=y1;
	int sum=0;
	for(int i=0;i<2;i++){// right-left  down-up
		ans=1;
		//if(debug) printf("			cur_i:%d\n",i); 
		x=x1;y=y1;//
		while(check(x+dx[i],y+dy[i])&&!mp2[x+dx[i]][y+dy[i]].empty()&&(mp2[x+dx[i]][y+dy[i]].top()!=-1)&&Equal(mp2[x+dx[i]][y+dy[i]].top(),cur)){//mp2[x+dx[i]][y+dy[i]].top()==cur
			if(row[x+dx[i]]||col[y+dy[i]]) break;//
			//if(debug) printf("i:%d mp[%d][%d]:%d cur:%d\n",i,x+dx[i],y+dy[i],mp2[x+dx[i]][y+dy[i]].top()%K,cur%K);
			ans++;x+=dx[i];y+=dy[i];
		}
		//if(debug) printf("right/down  ans:%d\n",ans);//debug
		if(i&1) maxx=x;
		i+=2;x=x1;y=y1;//
		while(check(x+dx[i],y+dy[i])&&!mp2[x+dx[i]][y+dy[i]].empty()&&(mp2[x+dx[i]][y+dy[i]].top()!=-1)&&Equal(mp2[x+dx[i]][y+dy[i]].top(),cur)){
			if(row[x+dx[i]]||col[y+dy[i]]) break;//
			//if(debug) printf("i:%d mp[%d][%d]:%d cur:%d\n",i,x+dx[i],y+dy[i],mp2[x+dx[i]][y+dy[i]].top()%K,cur%K);
			ans++;x+=dx[i];y+=dy[i];
		}
		if(i&1) minx=x;
		i-=2;
		//if(debug) printf("left/up  ans:%d\n",ans);//debug
		if(ans>=3){//printf("ok\n");//debug
			if(ans==3) sum+=goal[0];// 1 point
			else if(ans==4) sum+=goal[1];// 4 points
			else{
				//printf("YYY\n");//
				sum+=goal[2];//10 points
			}
			//num+=ans-1; 
			flag[i&1]=1;
			x=x1;y=y1;//
			//if(debug)printf("       A:\n");
			while(check(x+dx[i],y+dy[i])&&!mp2[x+dx[i]][y+dy[i]].empty()&&(mp2[x+dx[i]][y+dy[i]].top()!=-1)&&Equal(mp2[x+dx[i]][y+dy[i]].top(),cur)){
				if(row[x+dx[i]]||col[y+dy[i]]) break;//
				if((i&1)==0){
					Color(x+dx[i],y+dy[i],deep);
					Down(x+dx[i],y+dy[i],1);//
					tmp3.x=x+dx[i];tmp3.y=y+dy[i];
					cur3.push_back(tmp3);
					num++;//
				}
				else break;//
				//if(debug) print_map2();//
				x+=dx[i];y+=dy[i];//
			}
			//if(debug) print_map2();
			//if(debug)printf("       B:\n");
			i+=2;x=x1;y=y1;//
			while(check(x+dx[i],y+dy[i])&&!mp2[x+dx[i]][y+dy[i]].empty()&&(mp2[x+dx[i]][y+dy[i]].top()!=-1)&&Equal(mp2[x+dx[i]][y+dy[i]].top(),cur)){
				if(row[x+dx[i]]||col[y+dy[i]]) break;//
				if((i&1)==0){
					Color(x+dx[i],y+dy[i],deep);
					Down(x+dx[i],y+dy[i],1);//
					tmp3.x=x+dx[i];tmp3.y=y+dy[i];
					cur3.push_back(tmp3);
					num++;//
				}
				else break;
				x+=dx[i];y+=dy[i];//
			}
			//if(debug) printf("minx:%d maxx:%d\n",minx,maxx);//
			if(i&1){
				for(int h=minx;h<=maxx;h++) //
					Color(h,y,deep);
				Down(minx,y,maxx-minx+1);
				tmp3.x=x+dx[i];tmp3.y=y+dy[i];
					cur3.push_back(tmp3);
				num++;//
			}
			i-=2;//
		}
		//else if(!flag[0]&&!flag[1]) num=0;//
		//if(debug) printf("			last_i:%d\n",i);
	}
	//print_map2();//debug
	
	if(flag[0]||flag[1]){//有得消 
		if(!flag[1]){//如果 [x1][y1]所在列没有消去 
			Color(x1,y1,deep);//记得染色 
			Down(x1,y1,1);
			num++;//
		}
		//return true; 
	}
	return sum;
}
//交换动态地图的两个元素 
inline void Swap(int x1,int y1,int x2,int y2)
{
	int h1=mp2[x1][y1].top();
	int h2=mp2[x2][y2].top();
	mp2[x1][y1].pop();
	mp2[x2][y2].pop();
	//printf("(%d,%d):%d (%d,%d):%d\n",x1,y1,h1%K,x2,y2,h2%K);
	mp2[x1][y1].push(h2);
	mp2[x2][y2].push(h1);
}
//判断当前地图状态是否已出现过，若出现过且分数更高或相同分数次数更少，则剪枝 
inline bool add_status(int val)
{
	return true;//debug
	string str="";
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			str+=vis[i][j]+'0';
		}
	}
	if(visited[str]&&visited[str]>val)
		return false;
	visited[str]=val;
	if(debug) cout<<str<<endl;//
	return true;
}
int hh=0;
void tmp_map(int **mp3)//
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			mp3[i][j]=mp2[i][j].top();//
		}
	}
}
bool ok(int **mp3)//
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(mp3[i][j]!=mp2[i][j].top())
				return false;
		}
	}
	return true;
}

//递归过程 deep为深度 val=分数*(X+1)+(X-deep) 
void dfs1(int deep,int val)//
{ 
	if(deep>=X){
		//Ans=max(Ans,val/(X+1));
		if(Ans<val/(X+1))
			Ans=val/(X+1);		
		hh++;//
		return;
	}
	bool newway=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			for(int k=0;k<2;k++){//
				bool tag=0;
				
				if(mp2[i][j].empty()||mp2[i][j].top()==-1) continue;// 
				int x=i+dx[k],y=j+dy[k];
				if(!check(x,y)) continue;
				if(mp2[x][y].empty()||mp2[x][y].top()==-1) continue;//
				if(Equal(mp2[i][j].top(),mp2[x][y].top())) continue;
				int **mp4;
				mp4=new int*[N+1];
				for(int c=0;c<N;c++){
					mp4[c]=new int[M+1];
				}
				tmp_map(mp4);//
				if(debug||Debug(i,j,x,y,deep)){//debug
					printf("before Swap((%d,%d) (%d,%d))\n",i,j,x,y);print_map2();//
					debug=1;
				}
				Swap(i,j,x,y);
				//printf("after Swap((%d,%d) (%d,%d))\n",i,j,x,y);print_map2();//
				//debug=1;//debug
				
				//while(!st.empty()) st.pop();
				//while(!sk.empty()) sk.pop();
				int num=0,num2=0;
				int got=0;
				cur3.clear();//
				if(got+=judge(i,j,deep,num)){
//					tag=1;//
					
					num2=num;//
					if(i+1==x){
						row[i]=1;//
					}
					if(j+1==y){
						col[j]=1;
					}
					got+=judge(x,y,deep,num);
					if(i+1==x){
						row[i]=0;//
					}
					if(j+1==y){
						col[j]=0;//
					}				
					for(int h=0;h<cur3.size();h++){//
						got+=judge(cur3[h].x,cur3[h].y,deep,num);//
					}
					cur3.clear();//
					//printf("deep %d: Situation (%d,%d) (%d,%d)\n",deep,i,j,x,y);//debug
					int newval=(X+1)*(val/(X+1)+got)+(X-deep-1);//got+deep+1
					if(add_status(newval)){
						newway=1;						
						dfs1(deep+1,newval);
											
					}
					
				}
				else if(!num&&(got+=judge(x,y,deep,num))){// !num
									
					for(int h=0;h<cur3.size();h++){//
						got+=judge(cur3[h].x,cur3[h].y,deep,num);//
					}
					cur3.clear();//
					//printf("deep %d: Situation (%d,%d) (%d,%d)\n",deep,i,j,x,y);//debug
					int newval=(X+1)*(val/(X+1)+got)+(X-deep-1);//got+deep+1
					if(add_status(newval)){
						newway=1;											
						dfs1(deep+1,newval);
					}						
				} 
				//
							
				for(int c=0;c<num2;c++){
					node cur=st.top();
					st.pop();
					Up(cur.minx,cur.y,cur.maxx,cur.h); 
				}
				for(int c=0;c<num2;c++){
					node cur=sk.top();
					sk.pop();
					for(int i=cur.minx;i<=cur.maxx;i++) Decolor(i,cur.y);//
				}				
				for(int c=num2;c<num;c++){
					node cur=st.top();
					st.pop();
					Up(cur.minx,cur.y,cur.maxx,cur.h); 
				}
				for(int c=num2;c<num;c++){
					node cur=sk.top();
					sk.pop();
					for(int i=cur.minx;i<=cur.maxx;i++) Decolor(i,cur.y);//
				}
				Swap(i,j,x,y);				
				if(tag&&!ok(mp4)){
					printf("			Exception! on swap((%d,%d),(%d,%d))\n",i,j,x,y);
					printf("Exception_map when Swap_back((%d,%d) (%d,%d))\n",i,j,x,y);print_map2();//
				}
				for(int c=0;c<N;c++){
					delete []mp4[c];
				}
				delete []mp4;
				//printf("after Swap((%d,%d) (%d,%d))\n",i,j,x,y);print_map2();//
				
				debug=0;//
			}
		}
	}
	if(!newway){
		if(Ans<val/(X+1))
			Ans=val/(X+1);	
		hh++;//
	}
}
//---init map
inline bool deal()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			set<int> st;
			for(int k=0;k<4;k++){
				int ans=1,cur=mp[i][j];
				int x=i+dx[k],y=j+dy[k];
				while(check(x,y)&&mp[x][y]==cur){
					ans++;
					x+=dx[k];
					y+=dy[k];
				}
				if(ans>=3){
					int h=50;//
					st.insert(cur);
					while(st.find(mp[i][j])!=st.end()){
						mp[i][j]=rand()%K;
						if(--h==0) return false;
					}
				}
			}
			
		}
	}
	return true;
}
void init_map()
{
	srand((int)time(NULL));//
	do{
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				mp[i][j]=rand()%K;
			}
		}
		deal();
	}while(!legal());
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			while(!mp2[i][j].empty()) mp2[i][j].pop();
			int cur=(i*M+j)*K+mp[i][j];//save the position and the val
			mp2[i][j].push(cur);
		}
	}
}
// 
double test()
{
	srand((int)time(NULL));
	//用QueryPerformanceFrequency函数来计时，需要用到头文件<windows.h> 
	LARGE_INTEGER t1,t2,tc;// 用于记录排序所耗时间的频率 
	hh=0;//
	init_map();
	printf("Init the map successfully\n");//
	print_map2();
	Ans=0;//
	 
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	
	dfs1(0,0);//
	QueryPerformanceCounter(&t2);
	double time2=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	printf("the score:%d the count times:%d needed time:%.2fms\n",Ans,hh,time2);
	return time2;
}
int a[10]={6,4,8};
int b[10]={6,8,4};
int c[10]={4,4,4};
int d[10]={8,8,8};


void test3()
{
	//int k=0;// 
	for(int k=0;k<3;k++)
	{
		int t=1;//
		N=a[k];M=b[k];
		K=c[k];X=d[k];
		double time2=0;
		printf("N:%d M:%d K:%d X:%d\n",N,M,K,X);
		for(int i=0;i<t;i++){
			while(!st.empty()) st.pop();
			while(!sk.empty()) sk.pop();
			time2+=test();
		}
		printf("The average needed time:%.2fms\n",time2/t);
	}
}
int main()
{
	memset(row,0,sizeof(row));
	memset(col,0,sizeof(col)); 
	test3();
	
}
/*
okkkk
3 3 0 0 1 2
1 3 0 1 1 0
0 0 3 3 2 3
1 2 0 1 0 3
3 3 1 2 1 1
3 1 1 2 1 2
(0,0) (0,1) (0,2) (0,3) (0,4) (0,5)
(1,0) (1,1) (1,2) (1,3) (1,4) (1,5)
(2,0) (2,1) (2,2) (2,3) (2,4) (2,5)
(3,0) (3,1) (3,2) (3,3) (3,4) (3,5)
(4,0) (4,1) (4,2) (4,3) (4,4) (4,5)
(5,0) (5,1) (5,2) (5,3) (5,4) (5,5)
N:6 M:6 K:4 X:200
the score:23 the count times:10219 needed time:254.32ms


*/
