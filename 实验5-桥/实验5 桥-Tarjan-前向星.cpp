#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<fstream>
#include<algorithm>
#include<set>
#include<windows.h>
#define inf 0x3f3f3f3f
using namespace std;
#pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize(2)
const int maxn=1000010;
const int maxm=8000010*2;
/*
1000000
7586063
*/ 
int n,m;
struct Edge{
	int v,next;
	bool flag;
}e[maxm];
int head[maxn],tot,cnt;
void addedge(int u,int v)
{
	e[tot].v=v;e[tot].flag=0;
	e[tot].next=head[u];
	head[u]=tot++;
}
int dfn[maxn],low[maxn];
struct node{
	int u,v;
	bool operator <(const node &a) const{
		return u==a.u?v<a.v : u<a.u;
	}
}cut[maxm],tmp;
int cu;
void tarjan(int u,int p)
{
	low[u]=dfn[u]=++cnt;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].v;
		if(e[i].flag) continue;
		e[i].flag=e[i^1].flag=1;//注意有重边不同权值的情况 ，不能用v!=p	
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v]){
				cut[cu].u=u;
				cut[cu].v=v;
				if(cut[cu].u>cut[cu].v)
					swap(cut[cu].u,cut[cu].v);
				cu++;
			}
		}else{
			low[u]=min(low[u],dfn[v]);
		}
	}
}
multiset<node> st,st2;
void init()
{
	st.clear();
	st2.clear();
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(head,-1,sizeof(head));
	cu=tot=cnt=0;
}
bool cmp(const node& a,const node& b)
{
	if(a.u==b.u) return a.v<b.v;
	return a.u<b.u; 
}
void test1()
{
	LARGE_INTEGER t1,t2,tc;//
	//ifstream fin("data.txt");
	//ifstream fin("mediumDG.txt");
	ifstream fin("largeG.txt");
	int x,y;
	fin>>n>>m;
	printf("n:%d m:%d\n",n,m);
	init();
	int num_edge=0;
	for(int i=0;i<m;i++){
		fin>>x>>y;
		x++;y++;//
		if(x>y) swap(x,y);
//		tmp.u=x;tmp.v=y;
//		if(st.find(tmp)!=st.end()){
//			st2.insert(tmp); 
//			continue;
//		}
//		st.insert(tmp);
		num_edge++;
		addedge(x,y);addedge(y,x);
	}
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	m=num_edge;
	printf("over\n");//
	int k=0;
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,-1),k++;
	QueryPerformanceCounter(&t2);
	double time2=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	
	printf("num:%d\n",k);
	printf("The number of bridges:%d Used Time:%.3fms\n",cu,time2);
	sort(cut,cut+cu,cmp);
//	for(int i=0;i<cu;i++){
//		printf("Bridge %d: %d--%d\n",i+1,cut[i].u-1,cut[i].v-1);
//	}
}
string s[20]={"test1.txt","test2.txt","test3.txt","test4.txt","test5.txt","test6.txt","test7.txt","test8.txt","test9.txt","test10.txt","test11.txt","test12.txt"};
void test2()
{
	LARGE_INTEGER t1,t2,tc;//
	for(int i=0;i<12;i++){
		ifstream fin(s[i]);
		int x,y;
		fin>>n>>m;
		printf("test%d: n:%d m:%d\n",i+1,n,m);
		init();
//		int num_edge=0;
		for(int i=0;i<m;i++){
			fin>>x>>y;
			x++;y++;//
			if(x>y) swap(x,y);
//			tmp.u=x;tmp.v=y;
//			if(st.find(tmp)!=st.end()){
//				st2.insert(tmp); 
//				continue;
//			}
//			st.insert(tmp);
//			num_edge++;
			addedge(x,y);addedge(y,x);
		}
//		m=num_edge;
		QueryPerformanceFrequency(&tc);
    	QueryPerformanceCounter(&t1);
		int k=0;
		for(int i=1;i<=n;i++)
			if(!dfn[i]) tarjan(i,-1),k++;
		QueryPerformanceCounter(&t2);
		double time2=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
		printf("num:%d\n",k);
		printf("The number of bridges:%d Used Time:%.3fms\n",cu,time2);
//		sort(cut,cut+cu,cmp);
//		for(int i=0;i<cu;i++){
//			printf("Bridge %d: %d--%d\n",i+1,cut[i].u-1,cut[i].v-1);
//		}
		
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
	return 0;
}//

/*
data:
n:16 m:15
num:4
The number of bridges:6
Bridge 1: 0--1
Bridge 2: 2--3
Bridge 3: 2--6
Bridge 4: 6--7
Bridge 5: 9--10
Bridge 6: 12--13

mediumDG:
n:50 m:147
num:1
The number of bridges:0



n:1000000 m:1000000
num:161926
The number of bridges:365250

n:1000000 m:7586063
over
num:1
The number of bridges:8
Bridge 1: 95760--773903
Bridge 2: 148837--372243
Bridge 3: 317390--589095
Bridge 4: 461822--548437
Bridge 5: 467595--630627
Bridge 6: 467595--907820
Bridge 7: 639238--969090
Bridge 8: 658123--724640


*/
