#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define inf 0x3f3f3f3f

const int maxn=1010000;

int a[maxn],n;
void bubbleSort()
{
	for(int i=0;i<n-1;i++){
		int tmp;
		for(int j=0;j<n-i-1;j++){
			if(a[j]>a[j+1]){
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
			}
		}
	}
}
void sellectSort()
{
	for(int i=0;i<n-1;i++){
		int pos=i,tmp;
		for(int j=i+1;j<n;j++){
			if(a[j]<a[pos])
				pos=j;
		}
		if(pos!=i){
			tmp=a[pos];
			a[pos]=a[i];
			a[i]=tmp;
		}
	}
}
void insertSort()
{
	for(int i=1;i<n;i++){
		int tmp=a[i],j=i-1;
		while(tmp<a[j]&&j>=0){
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=tmp;
	}
} 

/*
void merge(int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + i];
    L[n1] = R[n2] = maxnum;
    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
        cnt++;
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
}*/
int L[maxn],R[maxn];
void merge(int left,int mid,int right){
	int n1=mid-left;
	int n2=right-mid;
	for(int i=0;i<n1;i++) L[i]=a[left+i];
	for(int i=0;i<n2;i++) R[i]=a[mid+i];
	L[n1]=R[n2]=inf;//
	int i=0,j=0;
	for(int k=left;k<right;k++){
		if(L[i]<R[j])
			a[k]=L[i++];
		else 
			a[k]=R[j++]; 
	}
}
void mergeSort(int left,int right){
	if(left+1<right){
		int mid=(left+right)/2;
		mergeSort(left,mid);
		mergeSort(mid,right);
		merge(left,mid,right);
	}
}
int partition(int l,int r)
{
	int v=a[l];
	while(l<r){
		while(l<r&&a[r]>=v)	r--;
		a[l]=a[r];
		while(l<r&&a[l]<=v) l++;
		a[r]=a[l];
	}
	a[l]=v;
	return l;
}

void quickSort(int l,int r)
{
	int m;
	if(l<r){
		m=partition(l,r);
		//print();
		quickSort(l,m-1);
		quickSort(m+1,r);
		
	}
}
void print()
{
	int c=0;
	for(int i=0;i<n;i++){
		c++;
		printf("%d ",a[i]);
		if(c%10==0)
			printf("\n");
	}
	printf("\n");
	//printf("%d\n",a[n-1]);
}
void process()
{
	for(int i=0;i<n;i++){
		int x=rand()%n+1;//
		a[i]=x;
	}
}
int main()
{
	while(~scanf("%d",&n)){
		//for(int i=0;i<n;i++)
		//	scanf("%d",&a[i]);
		process(); 
		print();
		//mergeSort(0,n);
		quickSort(0,n-1);
		//bubbleSort();
		print();
	}
}

