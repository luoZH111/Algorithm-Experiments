#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
//Edmonds karps�㷨 
const int maxn=2010;

int g[maxn][maxn];//�ߵ�����
int path[maxn],flow[maxn],st,ed;
int n;
int n1,m1,a,b;

int bfs()
{
	queue<int> q;
	while(!q.empty()) q.pop();
	memset(path,-1,sizeof(path));
	path[st]=0;
	flow[st]=inf;
	q.push(st);
	while(!q.empty()){
		int cur=q.front();q.pop();
		if(cur==ed) break;
		for(int i=0;i<=n;i++){
			if(i!=st&&path[i]==-1&&g[cur][i]){
				flow[i]=flow[cur]<g[cur][i]?flow[cur]:g[cur][i];
				q.push(i);
				path[i]=cur;
			}
		}
	}
	if(path[ed]==-1) return -1;
	return flow[ed];
}
int Edmonds_karps()
{
	int max_flow=0;
	int step,now,pre;
	while((step=bfs())!=-1){
		max_flow+=step;
		now=ed;
		while(now!=st){
			pre=path[now];
			g[pre][now]-=step;
			g[now][pre]+=step;
			now=pre;
		}
	}
	return max_flow;
}

void get_map()
{
	memset(g,0,sizeof(g));
	st=0;ed=n1+m1+1;
	n=ed;
	for(int i=1;i<=n1;i++){
		g[st][i]=b;
		for(int j=n1+1;j<=n1+m1;j++){
			g[i][j]=1;
		}
	}
	for(int i=n1+1;i<=n1+m1;i++)
		g[i][ed]=a;
}
void test()
{
	printf("������ ��ί�� ÿƪ������Ҫ����ί���� ÿ����ί��������������\n");
	scanf("%d%d%d%d",&m1,&n1,&a,&b);
	get_map();
	int tot=Edmonds_karps()/a;
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
//int cur=0; 
//for(int k=1;k<=tot;k++){
//	printf("��%dƪ���İ��ŵ���ʦ: ",k);
//	for(int i=1;i<=a;i++){
//		printf("%d ",cur+1);
//		cur=(cur+1)%n1;
//	}
//	printf("\n");
//}
