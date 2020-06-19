#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#pragma comment(linker, "/STACK:102400000,102400000")
const int maxn=1000010;
const int maxm=8000010*2;
#pragma GCC optimize(2)

//�������� 
struct edge{
	int v,nxt;
}e[maxm];
int tot,head[maxn];
int p[maxn];//���ϸ��׽�� 
bool vis[maxn];
int n,m;//����������� 
int f[maxn],h[maxn],h2[maxn],f2[maxn];// f2[] h[]���鼯

int edge_num;//�ܱ��� 
int tot3;//�����ϱ��� 
int cf[maxn];//���ϲ�� ÿ�������������ӵĸ��ӱ߱����ʴ��� 
int cu;//����� 

int tt,cnt;//
inline void init()
{
	tt=cnt=0;
	cu=tot=0;
	tot3=edge_num=0;
	memset(cf,0,sizeof(cf));
	memset(head,-1,sizeof(head));
	for(int i=0;i<n;i++) f[i]=i,h2[i]=1,f2[i]=i;
	memset(vis,0,sizeof(vis));
}
inline void addedge(int u,int v)//���ر� 
{
	e[tot].v=v;//e[tot].w=w;
	e[tot].nxt=head[u];
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
		if(h2[fx]>h2[fy]) swap(fx,fy);
		f2[fx]=fy;
		h2[fy]++;
		return true;
	}
	return false;
}
int find1(int x)
{
	return x==f[x]?x:f[x]=find1(f[x]);
}
void union1(int x,int y)
{
	int fx=find1(x),fy=find1(y);
	if(fx!=fy){
		f[fx]=fy;//�������Ϊ����� 
	}
}

int deep[maxn];
void dfs(int u,int fa,int d)
{
	p[u]=fa;deep[u]=d;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u,d+1);
	}
}
void dfs2(int u,int fa)
{
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		if(find1(v)!=find1(u)){
			cut[cu].u=u;cut[cu].v=v;
			if(cut[cu].u>cut[cu].v) swap(cut[cu].u,cut[cu].v);
			cu++;
		}
		dfs2(v,u);
	}
}
void solve()
{
	int u,v;
	for(int i=0;i<edge_num;i++){
		u=e2[i].u;
		v=e2[i].v;
		if(union2(u,v)){
			addedge(u,v);
			addedge(v,u);
			//e2[i].flag=1;
		}else{
			e3[tot3++]=e2[i];
		}
	}
	LARGE_INTEGER t1,t2,tc;//
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	vector<int> ve;
	for(int i=0;i<n;i++)
		if(find2(i)==i) dfs(i,i,1),ve.push_back(i);
	for(int i=0;i<tot3;i++){//���з����ϱ� 
		u=e3[i].u;v=e3[i].v;
		while(find1(u)!=find1(v)){
			if(deep[u]<deep[v]) 
				swap(u,v);
				
			/*
			if(union1(u,p[u])){
				u=p[u];
			}else{
				u=find1(u);
			}*/
			union1(u,p[u]);
			u=find1(u);
		}
	}
	for(int i=0;i<ve.size();i++){
		dfs2(ve[i],ve[i]);
	}
	
	
	QueryPerformanceCounter(&t2);
	double time2=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	sort(cut,cut+cu,cmp);
	printf("The number of bridges:%d Used Time:%.3fms\n",cu,time2);//printf("time3:%.3fms\n",time3);//
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
		//e2[edge_num].flag=0;
		if(u==v) continue;// 
		e2[edge_num].u=u;
		e2[edge_num++].v=v;
	}
	cout<<"over"<<endl;
	solve();
}
void test2()
{
	for(int i=0;i<12;i++){
		ifstream fin(s[i]);
		fin>>n>>m;
		printf("test%d: n:%d m:%d\n",i+1,n,m);
		int u,v;
		init();
		for(int i=0;i<m;i++){
			fin>>u>>v;
			//e2[edge_num].flag=0;
			if(u==v) continue;// 
			e2[edge_num].u=u;
			e2[edge_num++].v=v;
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
/*
void union1(int x,int y)
{
	int fx=find1(x),fy=find1(y);
	if(fx!=fy){
		if(h[fx]<h[fy]) swap(fx,fy);
		f[fx]=fy;
		h[fy]++;
		return true;
	}
	return false;
}
if(vis[v]){
	while(find1(u)!=find1(v)){
		fu=find1(u);
		fv=find1(v);
		if(fu��fv����){
			f[fv]=fu;
			v=find1(v);//
		}else{
			swap(fu,fv);
			f[fv]=fu;
			v=find1(v);//
		}
	}
}
*/
