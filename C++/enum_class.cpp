#include<iostream>
using namespace std;
enum class myEnum { //�⺻ int
	num1,num2,num3,num4=10,num5
};
enum class myEnum2: long { // Ÿ�� ����
	num1,num2,num3,num4,num5
};

void main(){
	/*
	������ ����Ÿ���� ���� Ÿ������ ��޵Ǿ� ���� ���� ������ ���� Ÿ�԰��� �� ���굵 ����
	������ enum Ŭ������ ���� ���� �ٸ� ���� Ÿ�� ������ �ڵ� ĳ���� ���� ����.
	if(myEnum::num1 == 1){ // x

	}
	*/
	myEnum em;
	if(myEnum::num1 != myEnum::num2) cout<< "enum class" <<endl;
	if(myEnum::num1 == myEnum::num1) cout<< "enum class" <<endl;

	em=myEnum::num1;
	switch(em){
		//case 1 : �ȵ�
		case myEnum::num1:
			cout<<"switch num1"<<endl;
			break;
	}
}