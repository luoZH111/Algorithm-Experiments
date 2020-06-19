#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#pragma comment(linker, "/STACK:102400000,102400000")
const int maxn=1000010;
const int maxm=8000010*2;


struct edge{
	int v,nxt;
	bool dele;
}e[maxm];
bool flag[maxm];
int tot,head[maxn];
bool vis[maxn];
int n,m;
int num,cu;//原图的连通分量数 桥数 
void init()
{
	cu=tot=0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v)//含重边 
{
	e[tot].v=v;//e[tot].w=w;
	e[tot].nxt=head[u];
	e[tot].dele=0;
//	e[tot].flag=0;
	flag[tot]=0;
	head[u]=tot++;
}
struct node{
	int u,v;
}cut[maxm];
bool cmp(const node& a,const node& b)
{
	if(a.u==b.u) return a.v<b.v;
	return a.u<b.u;
}

int ed;
bool is_bridge(int u)
{
	queue<int> q;
	q.push(u);
//	printf("u:%d ed:%d\n",u,ed);
	int cur=u;
	while(!q.empty()){
		u=q.front();q.pop();
		//printf("%d ",u);
		if(u==ed) return false;
		vis[u]=1;
		for(int i=head[u];~i;i=e[i].nxt){
			int v=e[i].v;
			if(flag[i]) continue;
			if(vis[v]||e[i].dele) continue;
//			if(cur==0&&ed==1){//
//				printf("*%d ",v);
//			}
			vis[v]=1;
			if(v==ed) return false;//
//			if(e[i].flag) continue;
//			e[i].flag=e[i^1].flag=1;
			
			flag[i]=flag[i^1]=1;
			q.push(v);
		}
	}
//	printf("\n");
	return true;
}

void solve()
{
	LARGE_INTEGER t1,t2,tc;//
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	for(int u=0;u<n;u++){
		if(u%10000==0) printf("u:%d\n",u);//
		for(int i=head[u];~i;i=e[i].nxt){
			if(u>=e[i].v) continue;//去掉重边,避免重复计数 去掉自环 
			e[i].dele=e[i^1].dele=1;
			ed=e[i].v;
			memset(flag,0,sizeof(flag));
			memset(vis,0,sizeof(vis));
			if(is_bridge(u)){
				cut[cu].u=u;
				cut[cu].v=e[i].v;
				if(cut[cu].u>cut[cu].v)
					swap(cut[cu].u,cut[cu].v);
				cu++;
			}
			e[i].dele=e[i^1].dele=0;
		}
	}
	QueryPerformanceCounter(&t2);
	double time2=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	sort(cut,cut+cu,cmp);
	printf("The number of bridges:%d Used Time:%.3fms\n",cu,time2);
	for(int i=0;i<cu;i++){
		printf("Bridge %d: %d--%d\n",i+1,cut[i].u,cut[i].v);
	}
}
string s[20]={"test1.txt","test2.txt","test3.txt","test4.txt","test5.txt","test6.txt","test7.txt","test8.txt","test9.txt","test10.txt","test11.txt","test12.txt"};
void test1()
{
	//ifstream fin("data.txt");
	//ifstream fin("mediumDG.txt");
	ifstream fin("largeG.txt");
	fin>>n>>m;
	printf("n:%d m:%d\n",n,m);
	int u,v;
	init();
	for(int i=0;i<m;i++){
		fin>>u>>v;
		if(u==v) continue;
		addedge(u,v);
		addedge(v,u);
	}
	cout<<"over"<<endl;
	solve();
}
void test2()
{
	for(int i=0;i<10;i++){
		ifstream fin(s[i]);
		fin>>n>>m;
		printf("test%d: n:%d m:%d\n",i+1,n,m);
		int u,v;
		init();
		for(int i=0;i<m;i++){
			fin>>u>>v;
			if(u==v) continue;
			addedge(u,v);
			addedge(v,u);
		}
		solve();
	}
}
int main()
{
	//G++ 手动扩栈 
// 	int size = 512 << 20; // 512MB  
//    char *p = (char*)malloc(size) + size;  
//    __asm__("movq %0, %%rsp\n" :: "r"(p));
	test1(); 
	//test2();
}

/*
data:
num:4
The number of bridges:6
Bridge 1: 0--1
Bridge 2: 2--6
Bridge 3: 2--3
Bridge 4: 6--7
Bridge 5: 9--10
Bridge 6: 12--13

mediumDG:
num:1
The number of bridges:0

*/

for(u=0 to n-1){
	for(edge of u:){
		v=cur_edge.v;
		if(v已访问) continue;
		if(find1(u)==find1(v)) continue;
		set cur_edge.dele to true;
		if(!ok()){
			该边为割边，桥数+1； 
		}
		set cur_edge.dele to false;
		union1(u,v);
	} 
}

