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
int f[maxn],h[maxn],f2[maxn];// f2[] h[]���鼯���������� f[]��lca 

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
	for(int i=0;i<n;i++) f[i]=i,h[i]=1,f2[i]=i;
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
		if(h[fx]>h[fy]) swap(fx,fy);
		f2[fx]=fy;
		//h[fy]+=h[fx];
		h[fy]++;
		return true;
	}
	return false;
}

int dfn[maxn*2],p2[maxn],f3[maxn*2];//
int dis[maxn],mn[maxn*2][22];// 22-> lg2(n)
void dfs(int u,int fa)
{
	p[u]=fa;
	int tmp=++tt;//ʱ��� 
	dfn[++cnt]=tmp;p2[u]=cnt;f3[tmp]=u;//f[]�״�ʱ���Ӧ��� p2[]����״γ���λ�� 
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		//dis[v]=dis[u]+w;
		dfs(v,u);
		dfn[++cnt]=tmp;//������ʱ���¼��u��Ӧ��ʱ��� 
	}
}
void init_mn(int n)//ʱ�临�Ӷ� O(nlogn) 
{
	int m=floor(log((double)n)/log(2.0));
	for(int i=1;i<=n;i++) mn[i][0]=dfn[i];
	for(int i=1;i<=m;i++){
		for(int j=n;j>0;j--){
			mn[j][i]=mn[j][i-1];
			if(j+(1<<(i-1))<=n){				
				mn[j][i]=min(mn[j][i-1],mn[j+(1<<(i-1))][i-1]);
			}
		}
	}
}
int rmq(int l,int r)//ʱ�临�Ӷ�O(1) 
{
	int m=floor(log((double)(r-l+1))/log(2.0));
	//return min2(mn[l][m],mn[r-(1<<m)+1][m]);
	return min(mn[l][m],mn[r-(1<<m)+1][m]);
}
int lca(int u,int v)//ʱ�临�Ӷ�O(1) 
{
	if(p2[u]>p2[v])
		swap(u,v);
	int k=rmq(p2[u],p2[v]);
	return f3[k];
}




void dfs2(int u)
{
	vis[u]=1;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v]) continue;
		dfs2(v);
		cf[u]+=cf[v];
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
	//for(int i=0;i<n;i++) printf("f2[%d]:%d\n",i,find2(i));
	LARGE_INTEGER t1,t2,tc;//
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	//memset(vis,0,sizeof(vis));
	vector<int> ve;
	for(int i=0;i<n;i++)
		if(find2(i)==i) dfs(i,i),ve.push_back(i);
	//for(int i=0;i<n;i++) if(p[i]!=i) printf("p[%d]:%d\n",i,p[i]);
	init_mn(cnt);
	for(int i=0;i<tot3;i++){
		int u=e3[i].u,v=e3[i].v;
		//if(find2[u]!=find2(v)) continue;//
		//printf("lca(%d,%d):%d\n",u,v,lca(u,v));
		cf[u]++;cf[v]++;cf[lca(u,v)]-=2;
	}
	//printf("before:\n");for(int i=0;i<n;i++) printf("cf[%d]:%d\n",i,cf[i]);//
	
	for(int i=0;i<ve.size();i++){
		dfs2(ve[i]);
	}
	//printf("after:\n");for(int i=0;i<n;i++) printf("cf[%d]:%d\n",i,cf[i]);//
	for(int i=0;i<n;i++){
		if(p[i]==i) continue;//���ĸ���� 
		if(!cf[i]){
			cut[cu].u=i;cut[cu].v=p[i];
			if(cut[cu].u>cut[cu].v) swap(cut[cu].u,cut[cu].v);
			cu++;
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
/*
void init()
{
	tot=0;
	memset(head,-1,sizeof(head));
}
for(int u=0;i<n;u++){
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		...
	}
}
void init()
{
	for(int u=0;u<n;u++)
		ve[u].clear();
} 
for(int u=0;u<n;u++){
	for(int i=0;i<ve[u].size();i++){
		int v=ve[u][i];
		...
	}
}*/


