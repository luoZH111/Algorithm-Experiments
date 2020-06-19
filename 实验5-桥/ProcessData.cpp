#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<fstream>
#include<algorithm>
#include<set>
#define inf 0x3f3f3f3f
using namespace std;

string s[10]={"test1.txt","test2.txt","test3.txt","test4.txt","test5.txt","test6.txt","test7.txt","test8.txt","test9.txt"};
int a[10]={100,200,200,800,1000,1000,1000,1000,1000,1000};
int b[10]={100,200,400,800,1000,2000,4000,8000,10000,10000};
int Rand()
{
	return (rand()%100)*10000+(rand()%100)*100+(rand()%100);
}
int n,m;
void fun1()
{
	for(int i=0;i<9;i++){
		ofstream fout(s[i]);
		n=a[i];m=b[i];
		fout<<n<<" "<<m<<endl;
		while(m--){
			fout<<Rand()%n<<" "<<Rand()%n<<endl; 
			
		}
		fout.close();
	}
}
string s2[10]={"test10.txt","test11.txt","test12.txt"}; 
int a2[10]={100000,1000000,10000};
int b2[10]={100000,1000000,10000};
void fun2()
{
	for(int i=2;i<3;i++){
		ofstream fout(s2[i]);
		n=a2[i];m=b2[i];
		
		fout<<n<<" "<<m<<endl;
		while(m--){
			fout<<Rand()%n<<" "<<Rand()%n<<endl; 
			
		}
		fout.close();
	}
}
int main()
{
	fun2();
}
