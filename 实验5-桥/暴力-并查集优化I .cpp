#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#pragma GCC optimize(2)
#pragma comment(linker, "/STACK:102400000,102400000")
const int maxn=1000010;
const int maxm=8000010*2;
//O(V*(E+V))

struct edge{
	int v,nxt;
	bool dele;
}e[maxm];
int tot,head[maxn];
bool vis[maxn];
int n,m;
int num,cu;//原图的连通分量数 桥数 

int f[maxn],h[maxn];
void init()
{
	cu=tot=0;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;i++){
		f[i]=i;
		h[i]=1;
	}
}
int find1(int x)
{
	return x==f[x]?x:f[x]=find1(f[x]); 
}
void union1(int x,int y)
{
	int fx=find1(x),fy=find1(y);
	if(fx!=fy){
		if(h[fx]>h[fy]) swap(fx,fy);
		f[fx]=fy;
		h[fy]++;
	}
}
void addedge(int u,int v)//含重边 
{
	e[tot].v=v;//e[tot].w=w;
	e[tot].nxt=head[u];
	e[tot].dele=0;
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
void dfs(int u)
{
	vis[u]=1;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v]||e[i].dele) continue;
		dfs(v);
	}
}

bool ok()
{
	int cur=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++){
		if(!vis[i]) dfs(i),cur++;
	}
	return cur==num;
	/*
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		vis[u]=1;
		q.pop();
		for(int u=0;u<n;u++){
			for(int i=head[u];~i;i=e[i].nxt){
				if(e[i].dele||vis[i]) continue;
				
			}
		}
	}*/
}
void solve()
{
	LARGE_INTEGER t1,t2,tc;//
	num=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++)
		if(!vis[i]) dfs(i),num++;
	printf("num:%d\n",num);
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	for(int u=0;u<n;u++){
		for(int i=head[u];~i;i=e[i].nxt){
			if(u>=e[i].v) continue;//去掉重边,避免重复计数；去掉自环
			if(find1(u)==find1(e[i].v)) continue;
			e[i].dele=e[i^1].dele=1;
			if(!ok()){
				cut[cu].u=u;
				cut[cu].v=e[i].v;
				if(cut[cu].u>cut[cu].v)
					swap(cut[cu].u,cut[cu].v);
				cu++;
			}
			union1(u,e[i].v);
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
string s[10]={"test1.txt","test2.txt","test3.txt","test4.txt","test5.txt","test6.txt","test7.txt","test8.txt","test9.txt"};
void test1()
{
	ifstream fin("data.txt");
	//ifstream fin("mediumDG.txt");
	//ifstream fin("largeG.txt");
	fin>>n>>m;
	printf("n:%d m:%d\n",n,m);
	int u,v;
	init();
	for(int i=0;i<m;i++){
		fin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	cout<<"over"<<endl;
	solve();
}
void test2()
{
	for(int i=0;i<9;i++){
		ifstream fin(s[i]);
		fin>>n>>m;
		printf("test%d: n:%d m:%d\n",i+1,n,m);
		int u,v;
		init();
		for(int i=0;i<m;i++){
			fin>>u>>v;
			addedge(u,v);
			addedge(v,u);
		}
		solve();
	}
}
int main()
{
	//G++ 手动扩栈 
 	int size = 512 << 20; // 512MB  
    char *p = (char*)malloc(size) + size;  
    __asm__("movq %0, %%rsp\n" :: "r"(p));
	
	test1(); 
	//test2();
}//

/*

*/
