#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<ctime>
#include<windows.h>
#include<stdlib.h> 
#include<ctime>
using namespace std;
#define inf 0x3f3f3f3f
const int maxn=1010000;

int a[maxn],n;
void bubbleSort()//ð������ 
{
	//ע�͵������Ϊð��������Ż����򣬿�ʹ�õ�����������ʱ����ǰ��ֹѭ�� 
	for(int i=0;i<n-1;i++){//���±�Ϊ0��ʼð�ݱ��� 
		int tmp;
		//bool flag=1;
		for(int j=0;j<n-i-1;j++){
			if(a[j]>a[j+1]){//������ڵ�Ԫ���±���Ԫ��Ȩֵ��С��������ǽ��н��� 
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				//flag=0;
			}
		}
		//if(flag) break;
	}
}
void sellectSort()//ѡ������ 
{
	//ע�͵������Ϊѡ��������Ż����򣬿�ʹ�õ�����������ʱ����ǰ��ֹѭ�� 
	for(int i=0;i<n-1;i++){//���±�Ϊ0������ʼ���� 
		int pos=i,tmp;
		//bool flag=1;
		for(int j=i+1;j<n;j++){//��������±��i����Ȩֵ��С���������������λ�� 
			if(a[j]<a[pos])
				pos=j;
			//if(a[j]<a[j-1]) flag=0;
		}
		//if(flag) break;
		if(pos!=i){//��iλ�ú��±�Ϊpos��λ�ý��н�����ʹ��iλ�õ����ǵ�ǰ������С�� 
			tmp=a[pos];
			a[pos]=a[i];
			a[i]=tmp;
		}
	}
}

void insertSort()//�������� 
{
	for(int i=1;i<n;i++){//���±�Ϊ1������ʼ���� 
		int tmp=a[i],j=i-1;
		while(tmp<a[j]&&j>=0){//����±��i��������ֵ��a[i]�� �������� 
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=tmp;//��a[i]���뵽j+1���λ���� 
	}
} 

//�鲢���� 
int L[maxn],R[maxn];
void merge(int left,int mid,int right){
	int n1=mid-left;
	int n2=right-mid;
	for(int i=0;i<n1;i++) L[i]=a[left+i];//����������д洢��L���� 
	for(int i=0;i<n2;i++) R[i]=a[mid+i];//���ұ������д洢��R���� 
	L[n1]=R[n2]=inf;//�߽���Ϊ����� 
	int i=0,j=0;
	//L �� R���鶼���������� 
	for(int k=left;k<right;k++){
		if(L[i]<R[j])//���L��ǰԪ�رȽ�С ��ȡL��ǰԪ�� 
			a[k]=L[i++];
		else //����ȡR��ǰԪ�� 
			a[k]=R[j++]; 
	}
}
void mergeSort(int left,int right){
	if(left+1<right){
		int mid=(left+right)/2;//�ѵ�ǰ�����Ϊ������ 
		mergeSort(left,mid);//����벿������ 
		mergeSort(mid,right);//���Ұ벿������ 
		merge(left,mid,right);//���ź�������������� ����һ�𣬵õ�������������� 
	}
}


void quickSort(int l,int r)//�������� 
{
	int m,l1,r1;
	if(l<r){
		//��a[l]Ϊ��� �����黮��Ϊ����a[l]���Ұ�� ��С��a[l]������ 
		l1=l;r1=r;
		int v=a[l1];
		while(l1<r1){
			while(l1<r1&&a[r1]>=v)	r1--;//���ұ�Ԫ��ֵ����a[l]ʱ�����ý���λ�� 
			a[l1]=a[r1];
			while(l1<r1&&a[l1]<=v) l1++;//�����Ԫ��ֵС��a[l]ʱ�����ý���λ�� 
			a[r1]=a[l1];
		}
		a[l1]=v;
		m=l1;
		//�Ե�ǰ�Ļ��ֺõ����������зֱ�ݹ������ͬ�Ĳ��� 
		quickSort(l,m-1);
		quickSort(m+1,r);
		
	}
}


int Random()//�ú��������������0��10^8���� 
{
	const int mod=100;
	return rand()%mod+(rand()%mod)*100+(rand()%mod)*10000+(rand()%mod)*1000000; 
} 
void process()//�ú�������������������ģΪn������������������a�� 
{
	for(int i=0;i<n;i++){
		int x=Random();//
		//int x=random(100000);
		if(!x) x++;//
		a[i]=x;
	}
}
// c�������ڴ���������ģ�Ĵ�С tΪ���ݵĲ��Դ��� ȡ20�� 
int c[10]={10000,20000,30000,40000,50000,60000},t=20;
double b[30];//b�������ڴ���ÿ�����õ�ʱ�� msΪ��λ 
void solve1()
{
	//��QueryPerformanceFrequency��������ʱ����Ҫ�õ�ͷ�ļ�<windows.h> 
	LARGE_INTEGER t1,t2,tc;// ���ڼ�¼��������ʱ���Ƶ�� 
	for(int i=0;i<5;i++){
		n=c[i];
		double sum=0;//ͳ����ʱ��
		for(int j=0;j<t;j++){
			process();
			QueryPerformanceFrequency(&tc);
    		QueryPerformanceCounter(&t1);
			sellectSort();//�����ݽ���ѡ������ 
			QueryPerformanceCounter(&t2);
			b[j]=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;//������������ʱ�� 
			sum+=b[j];//ͳ����ʱ�� 
		}
		//��������Ե�����ʱ�� 
		printf("���ݹ�ģΪ%dʱ��\n",n);
		printf("20������ʱ�䣺\n");
		for(int i=0;i<10;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		for(int i=10;i<t;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		//���ƽ������ʱ�� 
		printf("ƽ������ʱ��Ϊ: %.2f\n",sum/t);
		printf("\n\n"); 
	}
}//����solve����������solve1��ͬ�����ظ�˵�� 
void solve2()
{
	LARGE_INTEGER t1,t2,tc;
	for(int i=0;i<5;i++){
		n=c[i];
		double sum=0;
		for(int j=0;j<t;j++){
			process();
			QueryPerformanceFrequency(&tc);
    		QueryPerformanceCounter(&t1);
			bubbleSort();//�����ݽ���ð������ 
			QueryPerformanceCounter(&t2);
			b[j]=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;//
			sum+=b[j];
		}
		printf("���ݹ�ģΪ%dʱ��\n",n);
		printf("20������ʱ�䣺\n");
		for(int i=0;i<10;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		for(int i=10;i<t;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		printf("ƽ������ʱ��Ϊ: %.2f\n",sum/t);
		printf("\n\n"); 
	}
}
void solve3()
{
	LARGE_INTEGER t1,t2,tc;
	for(int i=0;i<5;i++){
		n=c[i];
		double sum=0;
		for(int j=0;j<t;j++){
			process();
			QueryPerformanceFrequency(&tc);
    		QueryPerformanceCounter(&t1);
			mergeSort(0,n);//�����ݽ��кϲ����� 
			QueryPerformanceCounter(&t2);
			b[j]=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;//
			sum+=b[j];
		}
		printf("���ݹ�ģΪ%dʱ��\n",n);
		printf("20������ʱ�䣺\n");
		for(int i=0;i<10;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		for(int i=10;i<t;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		printf("ƽ������ʱ��Ϊ: %.2f\n",sum/t);
		printf("\n\n"); 
	}
}
void solve4()
{
	LARGE_INTEGER t1,t2,tc;
	for(int i=0;i<5;i++){
		n=c[i];
		double sum=0;
		for(int j=0;j<t;j++){
			process();
			QueryPerformanceFrequency(&tc);
    		QueryPerformanceCounter(&t1);
			insertSort();//�����ݽ��в������� 
			QueryPerformanceCounter(&t2);
			b[j]=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;//
			sum+=b[j];
		}
		printf("���ݹ�ģΪ%dʱ��\n",n);
		printf("20������ʱ�䣺\n");
		for(int i=0;i<10;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		for(int i=10;i<t;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		printf("ƽ������ʱ��Ϊ: %.2f\n",sum/t);
		printf("\n\n"); 
	}
}
void solve5()
{
	LARGE_INTEGER t1,t2,tc;
	for(int i=0;i<5;i++){
		n=c[i];
		double sum=0;//
		for(int j=0;j<t;j++){
			process();
			QueryPerformanceFrequency(&tc);
    		QueryPerformanceCounter(&t1);
			quickSort(0,n-1);//�����ݽ��п������� 
			QueryPerformanceCounter(&t2);
			b[j]=(t2.QuadPart-t1.QuadPart)*1000.0/tc.QuadPart;//
			sum+=b[j];
		}
		printf("���ݹ�ģΪ%dʱ��\n",n);
		printf("20������ʱ�䣺\n");
		for(int i=0;i<10;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		for(int i=10;i<t;i++)
			printf("%.2f ",b[i]);
		printf("\n");
		printf("ƽ������ʱ��Ϊ: %.2f\n",sum/t);
		printf("\n\n"); 
	}
}
int main()
{
	while(1){
		//��ӡ�˵� 
		printf("������Ҫ���Ե���������\n");
		printf("0���˳� 1��ѡ������ 2��ð������ 3���ϲ����� 4���������� 5����������\n");
		int k;
		scanf("%d",&k); 
		if(!k) break; 
		//���Բ�ͬk���в�ͬ���� 
		switch(k){
			case 1:solve1();break;
			case 2:solve2();break;
			case 3:solve3();break;
			case 4:solve4();break;
			case 5:solve5();break;
		}
		
		printf("\n�����������...\n");
	}
}

