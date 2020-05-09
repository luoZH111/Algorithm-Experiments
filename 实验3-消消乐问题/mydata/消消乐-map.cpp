#include<iostream>
#include<algorithm>
#include<set>
#include<stack>
#include<ctime>
using namespace std;

int N,M,K,X;
int mp[50][50];
stack<int> mp2[50][50];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool check(int x,int y)
{
	if(x<0||y<0||x>=N||y>=M)
		return false;
	return true;
}
bool legal()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			for(int k=0;k<4;k++){
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
bool deal()
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
void print_map2()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(mp2[i][j].empty()){//no value
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
			if(mp2[i][j].empty()){
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
	//printf("\n\n");//
	printf("%d %d\n",N,M);// N:%d M:%d 
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			printf("%d ",mp[i][j]);
		}
		printf("\n");
	}
}
int a[10]={8,8,20,20,30,30};
int b[10]={4,5,20,30,20,30};
int c[10]={4,6,8,8,8,8};
void process()
{
	//K=8;
	srand((int)time(NULL));

	for(int i=0;i<2;i++){
		N=a[i];
		M=b[i];
		K=c[i];
		int t=50;
		while(t--){
			init_map();
			//printf("map:\n");
			print_map();
			//printf("map2:\n");
			//print_map2();
		}
	}
	
	
}
int main()
{
	freopen("my_map.txt","w",stdout); 
	process();
	fclose(stdout);
} 
