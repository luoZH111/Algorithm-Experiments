#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f

int n1,m1,a,b;

void test()
{
	printf("������ ��ί�� ÿƪ������Ҫ����ί���� ÿ����ί��������������\n");
	scanf("%d%d%d%d",&m1,&n1,&a,&b);
	int tot=n1*b/a;
	//printf("��������������%d\n",tot);
	if(tot<m1||n1<a){
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

10  5  2  4
*/
