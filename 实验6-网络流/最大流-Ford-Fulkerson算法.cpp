#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
const int maxn=2010;
const int maxm=2010;

int st,ed;
int n,n1,m1,a,b;
struct edge{
	int v,w,nxt;
}e[maxm];
int head[maxn],tot;
int deep[maxn];

bool vis[maxn];
void init()
{
	tot=0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w)
{
	e[tot].v=v;e[tot].w=w;
	e[tot].nxt=head[u];
	head[u]=tot++;
}
int dfs(int u,int flow)
{
	if(u==ed) return flow;
	vis[u]=1;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v]||!e[i].w) continue;
		int tmp_add=dfs(v,min(e[i].w,flow));
		if(tmp_add){
			e[i].w-=tmp_add;
			e[i^1].w+=tmp_add;
			return tmp_add;
		}
	}
	return 0;
}
int Ford_Fulkerson()
{
	int max_flow=0;
	while(1){
		memset(vis,0,sizeof(vis));
		int tmp_add=dfs(st,inf);
		if(!tmp_add) break;
		max_flow+=tmp_add;
	}
	return max_flow;
}


void get_map()
{
	init();
	st=0;ed=n1+m1+1;
	n=ed;
	for(int i=1;i<=n1;i++){
		addedge(st,i,b);
		addedge(i,st,0);
		for(int j=n1+1;j<=n1+m1;j++){
			addedge(i,j,1);
			addedge(j,i,0);
		}
	}
	for(int i=n1+1;i<=n1+m1;i++){
		addedge(i,ed,a);
		addedge(ed,i,0);
	}
}
void test()
{
	printf("论文数 评委数 每篇论文需要的评委人数 每个评委能评的论文数：\n");
	scanf("%d%d%d%d",&m1,&n1,&a,&b);
	get_map();
	int tot=Ford_Fulkerson()/a;
	printf("能评的论文数：%d\n",tot);
	if(tot<m1){
		printf("无解\n");return;
	}
	int cur=0; 
	for(int k=1;k<=tot;k++){
		printf("第%d篇论文安排的老师: ",k);
		for(int i=1;i<=a;i++){
			printf("%d ",cur+1);
			cur=(cur+1)%n1;
		}
		printf("\n");
	}
}
int main()
{
	test();
}

