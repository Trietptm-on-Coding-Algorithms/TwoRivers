#include<iostream>
using namespace std;
void main(){
	int n;
	int *arr;
	
	cout<<"input : ";
	cin>>n;

	arr=new int[n];
	memset(arr,0,n);
	
	//�����佺�׳׽��� ü
	arr[0]=arr[1]=-1; //-1 �� �Ҽ��� �ƴ�.
	for(int i=2,j=0;i<=n;i++){
		if(arr[i]==-1) continue; // i �� �Ҽ��� �ƴϹǷ� ����
		j=i;
		while((j+=i)<=n) arr[j]=-1; // j �� ����� �Ҽ��� �ƴ�. (ex j=2; 4,6,8, ...)
	}

	for(int i=0;i<=n;i++){
		if(arr[i]!=-1) cout<<i<<" ";
	}
	cout<<endl;
}