#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#pragma comment(linker, "/STACK:102400000,102400000")
const int maxn=1000010;
const int maxm=8000010*2;
#pragma GCC optimize(2)

//�������� 
struct edge{
	int v,nxt,flag,dele;
}e[maxm];
int tot,head[maxn];
int p[maxn];//���ϸ��׽�� 
bool vis[maxn];
int n,m;//����������� 
int f[maxn],h[maxn],f2[maxn];// f2[] h[]���鼯���������� f[]��lca 

int num;
int cu;//����� 

inline void init()
{
	cu=tot=0;
	memset(head,-1,sizeof(head));
	for(int i=0;i<n;i++) h[i]=1,f2[i]=i;
	memset(vis,0,sizeof(vis));
}

inline void addedge(int u,int v)//���ر� 
{
	e[tot].v=v;//e[tot].w=w;
	e[tot].nxt=head[u];
	e[tot].flag=0;
	e[tot].dele=0;
	head[u]=tot++;
}

struct node{
	int u,v;
}cut[maxm],e2[maxm],e3[maxm];

bool cmp(const node& a,const node& b)
{
	if(a.u==b.u) return a.v<b.v;
	return a.u<b.u; 
}
int find2(int x)
{
	return x==f2[x]?x:f2[x]=find2(f2[x]);
}
bool union2(int x,int y)
{
	int fx=find2(x),fy=find2(y);
	if(fx!=fy){
		if(h[fx]>h[fy]) swap(fx,fy);
		f2[fx]=fy;
		//h[fy]+=h[fx];
		h[fy]++;
		return true;
	}
	return false;
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
}
void solve()
{
	int u,v;
	for(int u=0;u<n;u++){
		for(int i=head[u];~i;i=e[i].nxt){
			v=e[i].v;
			if(union2(u,v)){
				e[i].flag=e[i^1].flag=1;
			}
		}
	}
	num=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++)
		if(!vis[i]) dfs(i),num++; 
	LARGE_INTEGER t1,t2,tc;//
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	for(int u=0;u<n;u++){
		for(int i=head[u];~i;i=e[i].nxt){
			if(!e[i].flag) continue;
			if(u>=e[i].v) continue;//ȥ���ر�,�����ظ����� ȥ���Ի� 
			e[i].dele=e[i^1].dele=1;
			if(!ok()){
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
	ifstream fin("data.txt");
	//ifstream fin("mediumDG.txt");
	//ifstream fin("largeG.txt");
	fin>>n>>m;
	printf("n:%d m:%d\n",n,m);
	int u,v;
	init();
	for(int i=0;i<m;i++){
		fin>>u>>v;
		//e2[edge_num].flag=0;
		if(u==v) continue;// 
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
			//e2[edge_num].flag=0;
			if(u==v) continue;// 
			addedge(u,v);
			addedge(v,u);
		}
		solve();
	}
}
int main()
{
	//G++ �ֶ���ջ 
// 	int size = 512 << 20; // 512MB  
//    char *p = (char*)malloc(size) + size;  
//    __asm__("movq %0, %%rsp\n" :: "r"(p));
	test1(); 
	//test2();
}



