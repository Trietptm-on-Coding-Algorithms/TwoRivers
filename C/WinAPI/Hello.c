#include<Windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); // ����ڿ� �ý����� �������� �޽����� ó����.�߿�.
HINSTANCE g_hInst; //WinMain �Լ��� hInstance ���� ���������� ����.���÷� ����ϱ⶧��.
LPCTSTR lpszClass=TEXT("Hello");  // ������ Ŭ������ �����ϴµ� ���.

//hInstance : ���α׷� �ν��Ͻ� �ڵ�
//hPrevInstance : �ٷ� �տ� ����� ���α׷��� �ν��Ͻ� �ڵ�. ���� ��� NULL.16��Ʈ ȣȯ�� ���� �μ�.���
//lpszCmdParam : ��������� �Էµ� ���α׷� �μ�. argv �� �ش�.��� ���� ���� �� ������ ��� ����.
//nCmdShow : ���α׷��� ����� ����.�ּ�ȭ,���� ������ ����.
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow){

	HWND hWnd;
	MSG Message; //�޽����� ���� ����.
	//hwnd : �޽����� ���� ������ �ڵ�
	//message : � ������ �޽����ΰ��� ��Ÿ��.
	//wParam : ���޵� �޽����� ���� �ΰ����� ����.
	//lParam : ���޵� �޽����� ���� �ΰ����� ����.
	//time : �޽����� �߻��� �ð�.
	//pt : �޽����� �߻����� ���� ���콺 ��ġ.
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0; //���� ����.������� ���� �� 0���� ����.
	WndClass.cbWndExtra=0; //���� ����.������� ���� �� 0���� ����.
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//������ ��� ���� ����.�������� ��� ������ ä���� �귯�ø� ����.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW); //���콺 Ŀ�� ����.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION); //������ ����.
	WndClass.hInstance=hInstance; //������ Ŭ���� ���.
	WndClass.lpfnWndProc=WndProc;// ������ �޽��� ó�� �Լ��� ����.
	WndClass.lpszClassName=lpszClass;// ������ Ŭ������ �̸��� ���ڿ��� ����.
	WndClass.lpszMenuName=NULL; //�޴� ����.�޴��� ���α׷� �ڵ忡�� ���� �� ����°� �ƴ϶� ���ҽ� �����Ϳ� ���� ������ ������� ��ũ�� ������.
	WndClass.style=CS_HREDRAW|CS_VREDRAW; // ������ ��Ÿ�� ����.CS_HREDRAW,CS_VREDRAW �ɼ����� �������� ũ�Ⱑ ���� ��� �����츦 �ٽ� �׸�.
	RegisterClass(&WndClass); //������ Ŭ���� ���.

	//������ ����.
	//������ �ڵ� ����.
	//�޸𸮻� �����쿡 ���� ������ ����.ȭ�� ���x.
	//lpszClassName : �����ϰ��� �ϴ� �������� Ŭ������ �����ϴ� ���ڿ�.
	//lpszWindowName : �������� Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�.
	//dwStyle : �������� ���� ����.
	//X,Y,nWidth,nHeight : �������� ũ��� ��ġ�� �����ϸ� �ȼ� ������ ���.CW_USEDEFAULT �� ����ϸ� �ü���� ȭ�� ũ�⿡ �°� ũ��� ��ġ ����.
	//hWndParent : �θ� �����찡 ���� ��� �θ� �������� �ڵ��� ����.������� NULL.NULL�̸� ����ũž�� �θ� �Ǿ� ����ȭ�� ���� �̵�����.
	//hmenu : �����쿡�� ����� �޴��� �ڵ��� ����.������ Ŭ�������� ������ �޴��� �� ������ Ŭ���� ��������ϴ� ��� �����쿡�� ���������� ���Ǵ�
	//�ݸ� �� ���ڷ� ������ �޴��� ���� CreateWindow�� ��������� �����쿡�� ���.NULL�� �����ϸ� ������ Ŭ�������� ������ ������ ���.
	//hinst : �����츦 ����� ��ü.���α׷��� �ڵ��� ����.
	//lpvParam : CREATESTRUCT��� ����ü�� �ּ�. ���� ���� �����츦 ���� �� �� �����쿡 ������ �Ķ���͸� �����ϴ� ����.
	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow); //�޸𸮿� ������� �����츦 ȭ�鿡 ���.nCmdShow�� �����츦 ȭ�鿡 ����ϴ� ��� ����.
	
	//�޽��� ����.�޽����� ó���ϴ� �κ�.
	//���� �ݺ�.
	//�������� ��Ƽ�½�ŷ�� �����ϴ� ����.
	while(GetMessage(&Message,NULL,0,0)){ //�޽��� ť���� �޽����� ����.���� �޽����� MSG ����ü�� ����.WM_QUIT ��� False �����Ͽ� ���� ����.
		TranslateMessage(&Message); //Ű���� �Է� �޽����� �����Ͽ� ���α׷����� ���� �� �� �ֵ��� ��.
		DispatchMessage(&Message); //�޽����� ������ �޽��� ó�� �Լ�(WndProc)���� ����.
	}
	return (int)Message.wParam; //WM_QUIT �� ���� ���޵� Ż���ڵ�
}
//�ü���� ���� ȣ��.
//hWnd : �ڵ�
//iMessage : � ������ �޽���.� ��ȭ�� �߻��ߴ°�.
//wParam,lParam : iMessgae�� �ΰ����� ����.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam){
	switch(iMessage){
		case WM_DESTROY:
			PostQuitMessage(0);//WM_QUIT �޽����� ����.GetMessage �Լ� ���� ���� False �Ǿ� �ݺ����� Ż�� �Ͽ� WinMain ����.
			return 0; //���� ó�� �Ǿ����� 0�� ����.
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));//WndProc ���� ó������ ���� ������ �޽����� ���� ó���� ��.
														//ex) �ý��� �޴��� ����Ŭ���ϸ� ���α׷��� ���� �Ǵµ�, �̴� ������ ó������ �ʰ� DefWindowProc �Լ����� ó��.
														//�׷��� �������� �̵��̳� ũ�� ���� ���� ó���� DefWindowProc ���� �ѱ�⸸ �ϸ��.
}