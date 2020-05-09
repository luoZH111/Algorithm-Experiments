#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
const int maxn=1010;
double r;//��ֵ 
int dp[maxn][maxn];//���ڼ���lcs��dp���� 
int mp[maxn][maxn];//01���� ����Ŀ˵��D���� 
vector<int> ve[maxn];//�ڽӱ���mp������Ϣ����mp[i][j]Ϊ1�ĵ����� 
int lcs(string s1,string s2)//�������ַ�����������Ӵ� ����������Ӵ��ĳ��� 
{
	int len1=s1.size(),len2=s2.size();
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=len1;i++){
		for(int j=1;j<=len2;j++){
			if(s1[i-1]==s2[j-1]){
				dp[i][j]=dp[i-1][j-1]+1;
			}else{
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}
	return dp[len1][len2];
}
int lcs2(int n,int m)//��mp[][]������ƥ���ظ����������������� 
{
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i-1][j-1]){
				dp[i][j]=dp[i-1][j-1]+1;
			}else{
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}
	return dp[n][m];
}
int judge(string s1,string s2)//���ڼ��������ַ����Ƿ��ظ� ������D(i,j) 
{
	int len=lcs(s1,s2);
	int len1=s1.length(),len2=s2.length();
	if((double)len>=1.0*min(len1,len2)*r)
		return 1;
	return 0;
}
//����ͼ���ƥ��-HK�㷨 
int um[maxn],vm[maxn];
int dx[maxn],dy[maxn],dis;
bool vis[maxn];

bool searchP(int n)
{
	queue<int> q;
	dis=inf;
	memset(dx,-1,sizeof(dx));//·����� ��ʼΪ-1 
	memset(dy,-1,sizeof(dy));
	
	for(int i=1;i<=n;i++)//��ߵ㼯��Ϊƥ��㶼��ӣ������Ϊ0 
		if(um[i]==-1){
			q.push(i);
			dx[i]=0;
		}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(dx[u]>dis) break;//���·�����ȴ���dis�������һ������ 
		for(int i=0;i<ve[u].size();i++){
			int v=ve[u][i];
			if(dy[v]==-1){
				dy[v]=dx[u]+1;
				if(vm[v]==-1) dis=dy[v];//�ҵ�δƥ��� ֹͣ���� 
				else{//v��ƥ��㣬�������� 
					dx[vm[v]]=dy[v]+1;
					q.push(vm[v]);
				}
			}
		}
	}
	return dis!=inf;//��disΪinf˵���ұߵ㼯û��δƥ��� 
}
bool dfs(int u)//��dfs��������bfs�γɵ�����· �ҵ��򷵻�true 
{
	for(int i=0;i<ve[u].size();i++){
		int v=ve[u][i];
		if(!vis[v]&&dy[v]==dx[u]+1){
			vis[v]=1;
			if(vm[v]!=-1&&dy[v]==dis) continue;
			if(vm[v]==-1||dfs(vm[v])){
				vm[v]=u;
				um[u]=v;
				return 1;
			}
		}
	}
	return 0;
}
int maxMatch(int n,int m)//����ͼ���ƥ�� 
{
	int res=0;
	memset(um,-1,sizeof(um));//ÿ����ƥ��㿪ʼΪ-1 
	memset(vm,-1,sizeof(vm));
	while(searchP(n)){//BFS������· 
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){//DFS������· �ҵ���ƥ����+1 
			if(um[i]==-1&&dfs(i)) res++;
		}
	}
//	for(int i=1;i<=n;i++){
//		printf("um[%d]:%d\n",i,um[i]-n);
//	} 
	return res; 
}

void printmp(int n,int m)//��ӡD���� 
{
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",mp[i][j]);
		}
		printf("\n");
	}
}
void printdata(string s[],int n)//��ӡ��ȡ�Ĵ����ļ� 
{
	for(int i=0;i<n;i++){
		cout<<s[i]<<endl;
	}
}
bool ok(string s)//ȥ���� ��� ����Ϊ���У�����false 
{
	int len=s.length();
	if(len>2&&s[0]=='/'&&s[1]=='/')
		return false;
	for(int i=0;i<len;i++){
		if(s[i]!=' '&&s[i]!='\n')
			return true;
	}
	return false;
}
string s1[maxn],s2[maxn];//�ֱ𴢴�A��B���� 
string text1[10]={"A0.c++.txt","A1.c++.txt","A2.c++.txt","4.txt"};
string text2[10]={"B0.c++.txt","B1.c++.txt","B2.c++.txt","5.txt"};
void input(int &n,int &m,int id)//�ļ����� 
{
	int ed;
	ifstream f1(text1[id]);
	while(getline(f1,s1[n])){
		if(ok(s1[n])){
			ed=s1[n].find("//");
			if(ed!=s1[n].npos)//ȥע�� 
				s1[n]=s1[n].substr(0,ed-1);
			n++;
		}
	}
	f1.close();
	ifstream f2(text2[id]);
	while(getline(f2,s2[m])){
		if(ok(s2[m])){
			ed=s2[m].find("//");
			if(ed!=s2[m].npos)//ȥע�� 
				s2[m]=s2[m].substr(0,ed-1);
			m++;
		}
	}
	f2.close();
//	printdata(s1,n);
//	printf("=--=-=-===================\n");
//	printdata(s2,m);
}
double rr[4]={0.5,0.9};//��ֵ�趨 
void solve(int n,int m)
{
	for(int k=0;k<2;k++){
		r=rr[k];
		for(int i=0;i<n+m;i++) ve[i].clear();
		//�����ڽӾ����ڽӱ� 
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				mp[i+1][j+1]=judge(s1[i],s2[j]);
				if(mp[i+1][j+1]){//��һ�ݴ�������Ϊ1 - n, �ڶ��ݴ�������Ϊ n+1 - n+m 
					ve[i+1].push_back(j+1+n);
					ve[j+1+n].push_back(i+1);
				}
			}
		}
//		printmp(n,m);
		printf("r:%.2f n:%d m:%d\n",r,n,m);
		int com=lcs2(n,m);
		printf("Using lcs,The common lines of two texts:%d\n",com);
		com=maxMatch(n,m);
		printf("Using bipartite graph maxinum matching,The common lines of two texts:%d\n",com);
	}
}
void test1()
{
	int n,m;
	for(int i=3;i<4;i++){//
		n=0,m=0;
		cout<<"For files: "<<text1[i]<<" and "<<text2[i]<<endl;
		input(n,m,i);
		solve(n,m);
		cout<<endl;
	}
}
int main()
{
	test1();
	return 0;
}

