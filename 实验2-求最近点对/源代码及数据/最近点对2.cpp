#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<ctime>
#include<windows.h>
#include<stdlib.h> 
#include<cmath>
using namespace std;
#pragma GCC optimize(2) //
const double inf=1e20;//
const int maxn=1000100;
const double eps=0.00000001;

struct Point{
	double x,y;
}p[maxn],tmp[maxn];
int n;
double ans;
Point p1,p2,L[maxn],R[maxn];

double getdis(Point a,Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));//
}

bool equal(const Point &a,const Point &b)
{
	return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps;
}
double Random()
{
	int num=0;
	num=rand()%100+((rand()%100)*100)+((rand()%100)*10000)+((rand()%100)*1000000);
	int mod=n*1000;//
	num=(num%mod+1); 
	return (double)num/100;
}
void process()
{
	for(int i=0;i<n;i++){
		p[i].x=Random();
		p[i].y=Random();/*
		for(int j=0;j<i;j++){
			if(equal(p[i],p[j])){
				i--;break;
			}
		}*/
	}
}
Point tmp2[maxn];
void process2()
{
	for(int i=0;i<n;i++){
		tmp2[i].x=Random();
		tmp2[i].y=Random();/*
		for(int j=0;j<i;j++){
			if(equal(p[i],p[j])){
				i--;break;
			}
		}*/
	}
}
void process3()
{
	for(int i=0;i<n;i++)
		p[i]=tmp2[i];
}
double violence()
{
	double ans=inf;
	Point a,b; 
	//用QueryPerformanceFrequency函数来计时，需要用到头文件<windows.h> 
	LARGE_INTEGER t1,t2,tc;// 用于记录暴力寻找最近点对所耗时间的频率 
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			double dis=getdis(p[i],p[j]);
			if(dis<ans){
				ans=dis;
				a=p[i];
				b=p[j];
			}
		}
	}
	QueryPerformanceCounter(&t2);
	double t=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	if(b.x<a.x||(fabs(b.x-a.x)<eps&&b.y<a.y)) swap(a,b);//
	printf("p(%.2f,%.2f) to p(%.2f,%.2f)   Dis:%.4f      time(violence):%.4fms\n",a.x,a.y,b.x,b.y,sqrt(ans),t);//
	return t;
}


/*
void merge(int l,int r)
{
	int m=(l+r)/2;
	int n1=m-l,n2=r-m;
	for(int i=0;i<n1;i++) L[i]=p[l+i];
	for(int i=0;i<n2;i++) R[i]=p[m+i];
	L[n1].y=R[n2].y=inf;
	int i=0,j=0;
	for(int k=l;k<r;k++){
		if(L[i].y<R[j].y)
			p[k]=L[i++];
		else
			p[k]=R[j++];
	}
}*/
void merge(int l,int r)
{
	int m=(l+r)/2,i=l,j=m+1,k=l;
	while(i<=m&&j<=r){
		if(p[i].y<p[j].y)
			L[k++]=p[i++];
		else
			L[k++]=p[j++];
	}
	while(i<=m)
		L[k++]=p[i++];
	while(j<=r)
		L[k++]=p[j++];
	for(int i=l;i<=r;i++)
		p[i]=L[i];
}

double Pair(int l,int r)
{
	if(l==r) 
		return inf;
	if(l+1==r){
		merge(l,r);//
		double dis=getdis(p[l],p[r]);
		if(dis<ans){
			ans=dis;
			p1=p[l];p2=p[r];
		}
		return dis;//
	}
	
	int m=(l+r)/2;
	double middle=p[m].x;
	double d1=Pair(l,m);
	double d2=Pair(m+1,r);
	double d=min(d1,d2);
	Point h1=p1,h2=p2;
	int k=0;
	merge(l,r);
	for(int i=l;i<=r;i++){
		if(fabs(middle-p[i].x)<=d)//
			tmp[k++]=p[i];
	}
	for(int i=0;i<k;i++){
		for(int j=i+1;j<k&&tmp[j].y-tmp[i].y<d;j++){
			double dis=getdis(tmp[i],tmp[j]);
			if(dis<d){
				d=dis;//
				h1=tmp[i];
				h2=tmp[j];
			}
		}
	}
	if(d<ans){
		ans=d;
		p1=h1;
		p2=h2;
	}
	return d;//
}
double Pair2(int l,int r)
{
	if(l==r) 
		return inf;
	if(l+1==r){
		merge(l,r);//
		double dis=getdis(p[l],p[r]);
		if(dis<ans){
			ans=dis;
			p1=p[l];p2=p[r];
		}
		return dis;//
	}
	
	int m=(l+r)/2;
	double middle=p[m].x;
	double d1=Pair2(l,m);
	double d2=Pair2(m+1,r);
	double d=min(d1,d2);
	Point h1=p1,h2=p2;
	int k=0;
	merge(l,r);
	for(int i=l;i<=r;i++){
		if(fabs(middle-p[i].x)<d)//
			tmp[k++]=p[i];
	}
	for(int i=0;i<k;i++){
		for(int j=i+1;j<k&&tmp[j].y-tmp[i].y<d;j++){
			double dis=getdis(tmp[i],tmp[j]);
			if(dis<d){
				d=dis;//
				h1=tmp[i];
				h2=tmp[j];
			}
		}
	}
	if(d<ans){
		ans=d;
		p1=h1;
		p2=h2;
	}
	return d;//
}
bool cmp(const Point &a,const Point &b)
{
	//if(a.x!=b.x) 
	return a.x<b.x;
	//return a.y<b.y;
}


double divide_conquer()
{
	ans=inf;
	//用QueryPerformanceFrequency函数来计时，需要用到头文件<windows.h> 
	LARGE_INTEGER t1,t2,tc;// 用于记录分治法寻找最近点对所耗时间的频率 
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	sort(p,p+n,cmp);//
	Pair(0,n-1);
	QueryPerformanceCounter(&t2);
	double t=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	if(p2.x<p1.x||(fabs(p2.x-p1.x)<eps&&p2.y<p2.y)) swap(p1,p2); 
	printf("p(%.2f,%.2f) to p(%.2f,%.2f)   Dis:%.4f      time(div):%.4fms \n",p1.x,p1.y,p2.x,p2.y,ans,t);//
	return t;
}
double divide_conquer2()
{
	ans=inf;
	//用QueryPerformanceFrequency函数来计时，需要用到头文件<windows.h> 
	LARGE_INTEGER t1,t2,tc;// 用于记录分治法寻找最近点对所耗时间的频率 
	QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	sort(p,p+n,cmp);//
	Pair2(0,n-1);
	QueryPerformanceCounter(&t2);
	double t=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;
	if(p2.x<p1.x||(fabs(p2.x-p1.x)<eps&&p2.y<p2.y)) swap(p1,p2); 
	printf("p(%.2f,%.2f) to p(%.2f,%.2f)   Dis:%.4f      time(div2):%.4fms \n",p1.x,p1.y,p2.x,p2.y,ans,t);//
	return t;
}
void print()
{
	for(int i=0;i<n;i++){
		printf("p[%d]:(%.2f , %.2f)\n",i,p[i].x,p[i].y);
	}
}
int e[10]={100000,200000,300000,400000,500000};
int d[10]={10000,20000,30000,40000,50000}; 
int c[10]={1000,2000,3000,4000,5000};//
int b[10]={100,200,300,400,500};
int a[10]={10,20,30,40,50};

int main()
{
	//freopen("out.txt","w",stdout);//
	for(int i=0;i<5;i++){//
		double t1=0,t2=0,t3=0; 
		n=e[i];
		printf("N:%d\n",n);
		int num=10;//
		for(int j=0;j<num;j++){//
			process2();
			//t1+=violence();
			process3();
			t2+=divide_conquer();
			process3();
			t3+=divide_conquer2();
		} 
		//t1/=num;
		t2/=num;
		t3/=num;//
		printf("To calculate the shortest distance of %d points.\n",n);
		//printf("The average time of violence is %.4fms\n",t1);
		printf("The average time of divide_conquer is %.4fms\n",t2);
		printf("The average time of divide_conquer2 is %.4fms\n",t3);
		printf("\n");
	}
	//fclose(stdout);//
	return 0;
} 

