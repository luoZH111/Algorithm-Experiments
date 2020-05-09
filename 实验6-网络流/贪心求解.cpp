#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f

int n1,m1,a,b;

void test()
{
	printf("论文数 评委数 每篇论文需要的评委人数 每个评委能评的论文数：\n");
	scanf("%d%d%d%d",&m1,&n1,&a,&b);
	int tot=n1*b/a;
	//printf("能评的论文数：%d\n",tot);
	if(tot<m1||n1<a){
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
/*
论文数 评委数 每篇论文需要的评委人数 每个评委能评的论文数
10  3  2  4

10  5  2  4
*/
