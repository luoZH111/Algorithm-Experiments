#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
const int maxn=2010;
const int maxm=1000110;// 

int st,ed;
int n,n1,m1,a,b;
struct edge{
	int v,w,nxt;
}e[maxm];
int head[maxn],tot,cur[maxn];
int deep[maxn];
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

bool bfs()
{
	memset(deep,0,sizeof(deep));
	queue<int> q;
	q.push(st);
	deep[st]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];~i;i=e[i].nxt){
			int v=e[i].v;
			if(deep[v]||e[i].w<=0) continue;
			deep[v]=deep[u]+1;
			q.push(v);
		}
	}
	return deep[ed];
}
int dfs(int u,int flow)
{
	if(u==ed) return flow;
	int add_flow=0;
	for(int &i=cur[u];~i&&add_flow<flow;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(deep[v]!=deep[u]+1) continue;
		int tmp_add=dfs(v,min(w,flow-add_flow));
		if(!tmp_add){
			deep[v]=1;
			continue;
		}
		e[i].w-=tmp_add;
		e[i^1].w+=tmp_add;
		add_flow+=tmp_add;
	}
	return add_flow;
}
int Dinic()
{
	int ans=0;
	while(bfs()){
		for(int i=0;i<=n;i++)
			cur[i]=head[i];
		ans+=dfs(st,inf);
	}
	return ans;
}
void get_map()
{
	init();
	st=0;ed=n1+m1+1;
	n=ed;
	for(int i=1;i<=n1;i++){
		//g[st][i]=b;
		addedge(st,i,b);
		addedge(i,st,0);
		for(int j=n1+1;j<=n1+m1;j++){
			//g[i][j]=1;
			addedge(i,j,1);
			addedge(j,i,0);
		}
	}
	for(int i=n1+1;i<=n1+m1;i++){
		//g[i][ed]=a;
		addedge(i,ed,a);
		addedge(ed,i,0);
	}
}
void test()
{
	printf("������ ��ί�� ÿƪ������Ҫ����ί���� ÿ����ί��������������\n");
	scanf("%d%d%d%d",&m1,&n1,&a,&b);
	get_map();
	int tot=Dinic()/a;
	//printf("��������������%d\n",tot);
	if(tot<m1){
		printf("�޽�\n");return;
	}
	int cur=0; 
	for(int k=1;k<=tot;k++){
		printf("��%dƪ���İ��ŵ���ʦ: ",k);
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
/*
������ ��ί�� ÿƪ������Ҫ����ί���� ÿ����ί������������
10  3  2  4
*/
