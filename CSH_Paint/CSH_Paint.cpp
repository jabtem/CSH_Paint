// ���ҽ��� ����ϱ� ���ؼ� resource.h ������ include�� �־�� �Ѵ�.
#include "resource.h"
// API �Լ����� ����Ϸ��� windows.h ������ include�� �־�� �Ѵ�.
#include <windows.h>
// C ���� ���� ����Ͽ��� ǥ�� ����� ��� �߰�
#include <stdio.h>

// �޽����� ó���� ���� �� �� �Լ��� �����Ѵ�.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetColor(int,HPEN&,HBRUSH&);
// ���α׷��� �������� �����Ѵ�.
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	// �������� �ڵ��� ����� ������ �����.
	HWND hWnd;
	// �޽��� ����ü�� �����Ѵ�.
	MSG mSg;

	// �������� ĸ���� �����Ѵ�.
	WCHAR szTitle[] = L"�׸���";
	// �������� Ŭ������ �����Ѵ�.
	WCHAR szClass[] = L"Class";


	// �߰����� ������ ���� ��/////////////////////////////////////
	HICON hIcon1;   // icon handle 
	HICON hIcon2;   // icon handle 

	// �⺻ ������ ����
	hIcon1 = LoadIcon(NULL, IDI_QUESTION);

	// ����� ���� ������ ���� 
	hIcon2 = LoadIcon(hInstance, MAKEINTRESOURCE(101));
	///////////////////////////////////////////////////////////////

	// WNDCLASSEX ����ü�� �����Ѵ�. ����� â�� �ϳ��� ������ Ŭ������ ������� �����ȴ�.
	WNDCLASSEX WndEx;

	// WNDCLASSEX ����ü�� ũ�⸦ �����Ѵ�.
	WndEx.cbSize = sizeof(WndEx);

	// �������� ��Ÿ���� �����Ѵ�.
	WndEx.style = NULL;

	// �޽����� ó���� �Լ��� �����Ѵ�. �� �޽����� �߻��ϸ� �� �޽����� WndProc �Լ����� ó���Ѵ�.
	WndEx.lpfnWndProc = WndProc;

	// �߰� Ŭ������ �����Ѵ�. �߰� Ŭ������ ���� ������ NULL ������ �����Ѵ�.
	WndEx.cbClsExtra = 0;

	// �߰� �����츦 �����Ѵ�. �߰� �����찡 ���� ������ NULL ������ �����Ѵ�.
	WndEx.cbWndExtra = 0;

	// �ν��Ͻ� �ڵ��� �����Ѵ�.
	WndEx.hInstance = hInstance;

	// ���� ���Ͽ� ���� �������� �����Ѵ�. LoadIcon() �Լ��� ���ҽ����� �������� �ҷ��� ��ȯ�Ѵ�.
	WndEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	// �����쿡�� ���� Ŀ���� �����Ѵ�. LoadCursor() �Լ��� �̸� ����� Ŀ�� ���� ��ȯ�Ѵ�.
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);

	// �������� ������ �����Ѵ�. GetStockObject() �Լ��� ����� ��ȯ�Ѵ�.
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// �����쿡 ���� �޴��� �����Ѵ�. �޴��� ���� ������ NULL ������ �����Ͽ���.
	WndEx.lpszMenuName = NULL;

	// Ŭ������ �����Ѵ�. ����� �� Ŭ������ CreateWindowEx() �Լ����� ������ Ŭ������ �����ؾ� �Ѵ�.
	WndEx.lpszClassName = szClass;

	// �������� ĸ���� ���� �������� �����Ѵ�. LoadIcon() �Լ��� ���ҽ����� �������� �ҷ��� ��ȯ�Ѵ�.
	WndEx.hIconSm = LoadIcon(hInstance, /*L"IDI_ICON"*/MAKEINTRESOURCE(101));
	//WndEx.hIconSm = hIcon2;



	// WNDCLASSEX�� ������ ������ �������Ϳ� ����Ѵ�.
	RegisterClassEx(&WndEx);

	// �����츦 �����Ѵ�.
	hWnd = CreateWindowEx(NULL,				// �������� ��Ÿ���� �����Ѵ�.
		szClass,				// �������� Ŭ������ �����Ѵ�.
		szTitle,				// �������� ĸ���� �����Ѵ�.
		WS_OVERLAPPEDWINDOW,	// �������� ��Ÿ���� �����Ѵ�.
		CW_USEDEFAULT,			// �������� x��ǥ ��ġ�� �����Ѵ�. CW_USEDEFAULT ������ �����Ͽ����Ƿ� ��ǻ�Ͱ� �˾Ƽ� �����Ѵ�.
		CW_USEDEFAULT,			// �������� y��ǥ ��ġ�� �����Ѵ�. CW_USEDEFAULT ������ �����Ͽ����Ƿ� ��ǻ�Ͱ� �˾Ƽ� �����Ѵ�.
		800,					// �������� ���̸� 320���� �����Ͽ���.
		600,					// �������� ���̸� 240���� �����Ͽ���.
		NULL,					// �����츦 �����ϰ� �ִ� �ٸ� �����찡 �����Ƿ� NULL ������ �����Ͽ���.
		NULL,					// �޴��� �����Ƿ� NULL ������ �����Ͽ���.
		hInstance,				// �ν��Ͻ� �ڵ��� �����Ѵ�.
		NULL);					// �� ������ �ʴ´�.

// �����찡 ������ ������ ���¸� �����Ѵ�.
	ShowWindow(hWnd, nShowCmd);
	// �����츦 �����ϰ� WM_PAINT �޽����� ȣ���Ѵ�.
	UpdateWindow(hWnd);

	// �޽��� ó���� ���� �ݺ��� ����
	while (TRUE)
	{
		// �޽��� ť�� ���� �޽����� �ִ��� Ȯ���Ѵ�.
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			// ���� �޽����� ������ MSG ����ü���� �޽����� �о�´�.
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;	// �޽��� �߿� WM_QUIT�޽����� ������ ����������.
			// ����Ű�� �߻��ϸ� �� �޽����� �޾ƿͼ� WM_CHAR�� �ش��ϴ� �ڵ带 ���� ���α׷��� �޽��� ť�� �־� �д�.
			TranslateMessage(&mSg);
			// �� �޽������� ó���ϱ� ���� WndProc() �Լ��� ������.
			DispatchMessage(&mSg);
		}
	}

	// ��Ÿ �μ����� �޽����� ��ȯ�Ѵ�.
	return mSg.wParam;
}

// �޽����� ó���ϱ� ���ؼ� �޽��� ó�� �Լ��� �����Ѵ�.
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	// ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	HDC hDC;
	// �� ��ü�� ����Ű�� ����.
	HPEN hPen,hOldPen;
	HBRUSH hBrush,hOldBrush;
	// �������� ���� ������ ���� ������ ����� ����ü ����
	PAINTSTRUCT ps;

	static int butt = -1;//��ư���п� ����
	static int color = -1;
	static HWND hButtPen;
	static HWND hButtLine;
	static HWND hButtCircle1, hButtCircle2;
	static HWND hButtRect, hButtRect2;
	static HWND hRed, hGreen, hBlue, hDefault;
	// ����ƽ ���� ����
	static int nAx=0, nAy=0, nBx=0, nBy=0;

	// x, y ��ǥ �� ������ ���� ����ü
	static POINT pOint;
	// ���� �׸��� ���� ����
	static BOOL bSw = FALSE;

	// �����쿡 ��µ� ���ڿ��� �����ϱ� ���� ���ڿ� ���� ����
	TCHAR szText[100];
	WCHAR szText6[100] = L"~";
	WCHAR szText1[100] = L"/";
	WCHAR szText2[100] = L"��";
	WCHAR szText3[100] = L"��";
	WCHAR szText4[100] = L"��";
	WCHAR szText5[100] = L"��";

	// uMsg �������� DispatchMessage() �Լ����� ���� �޽������� ����Ǿ� �ִ�.
	switch (uMsg)
	{
		static HBRUSH butt_Brush;
	case WM_CREATE:
		hButtPen = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			szText6,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // ��ư�� ��Ÿ��
			0,										// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)6,								// ��ư�� ���̵�				
			NULL,
			NULL);

		hButtLine = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			szText1,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // ��ư�� ��Ÿ��
			30,										// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)1,								// ��ư�� ���̵�				
			NULL,
			NULL);
		hButtCircle1 = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			szText2,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // ��ư�� ��Ÿ��
			60,										// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)2,								// ��ư�� ���̵�				
			NULL,
			NULL);
		hButtCircle2 = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			szText3,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // ��ư�� ��Ÿ��
			90,										// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)3,								// ��ư�� ���̵�				
			NULL,
			NULL);
		hButtRect = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			szText4,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // ��ư�� ��Ÿ��
			120,										// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)4,								// ��ư�� ���̵�				
			NULL,
			NULL);
		hButtRect2 = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			szText5,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // ��ư�� ��Ÿ��
			150,									// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)5,								// ��ư�� ���̵�				
			NULL,
			NULL);

		hRed = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			L" " ,								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // ��ư�� ��Ÿ��
			180,									// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)7,								// ��ư�� ���̵�				
			NULL,
			NULL);

		hGreen = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			L" ",								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // ��ư�� ��Ÿ��
			210,									// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)8,								// ��ư�� ���̵�				
			NULL,
			NULL);
		hBlue = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			L" ",								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // ��ư�� ��Ÿ��
			240,									// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)9,								// ��ư�� ���̵�				
			NULL,
			NULL);
		hDefault = CreateWindow(L"BUTTON",		// ��ư�� Ŭ������ �����Ѵ�.(����������)
			L" ",								// ��ư�� ĸ��
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // ��ư�� ��Ÿ��
			270,									// ��ư�� x ��ǥ ��ġ
			0,										// ��ư�� y ��ǥ ��ġ
			30,										// ��ư�� ����
			30,										// ��ư�� ����
			hWnd,									// �θ� ������ �ڵ�
			(HMENU)10,								// ��ư�� ���̵�				
			NULL,
			NULL);
		return FALSE;

	case WM_CTLCOLORBTN:
		if ((HWND)lParam == hRed)
			butt_Brush = CreateSolidBrush(RGB(255, 0, 0));
		else if ((HWND)lParam == hGreen)
			butt_Brush = CreateSolidBrush(RGB(0, 255, 0));
		else if ((HWND)lParam == hBlue)
			butt_Brush = CreateSolidBrush(RGB(0, 0, 255));
		else
			butt_Brush = CreateSolidBrush(RGB(0, 0, 0));
		return (LRESULT)butt_Brush;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 6:
			butt = 6;
			break;
		case 1:
			butt = 1;
			break;
		case 2:
			butt = 2;
			break;
		case 3:
			butt = 3;
			break;
		case 4:
			butt = 4;
			break;
		case 5:
			butt = 5;
			break;
		case 7:
			color = 1;//����
			break;
		case 8:
			color = 2;//�ʷ�
			break;
		case 9:
			color = 3;//�Ķ�
			break;
		case 10:
			color = 0;//����
			break;
		}
		return FALSE;
		// ���콺 ���� ��ư Ŭ����...
	case WM_LBUTTONDOWN:
		// ���콺 ��ư�� Ŭ���Ǹ� ���� �׷����� �ʰ� �Ѵ�.
		bSw = TRUE;
		// ���콺 ��ǥ�� ���´�.(���� ���콺�� Ŭ���� ���� x, y ��ǥ ���� �����Ѵ�.)
		nAx = LOWORD(lParam); // nAx���� ���콺�� x��ǥ�� ����.
		nAy = HIWORD(lParam); // nAy���� ���콺�� y��ǥ�� ����.
		return FALSE;

		// ���콺 ���� ��ư�� ��������...
	case WM_LBUTTONUP:
		// ���콺 ��ư�� ������ ���� �������� �Ͽ� ���� �׸��� �Ѵ�.
		bSw = FALSE;

		// ���콺 ��ǥ�� ���´�.(������ ���� x, y ��ǥ ���� �����Ѵ�.)
		nBx = LOWORD(lParam); // nBx���� ���콺�� x��ǥ�� ����.
		nBy = HIWORD(lParam); // nBy���� ���콺�� y��ǥ�� ����.

		// �����츦 �����Ѵ�. ����� �����츦 ������ ���� UpdateWindow()�Լ��� ���� ���� ���� ����.
		InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
		return FALSE;

	case WM_RBUTTONDOWN:
		bSw = TRUE;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		bSw = FALSE;
		return FALSE;
		// WM_PAINT �޽��� �߻���(�ٽ� �׷����� ��Ȳ�� �߻��� ���޵ȴ�.)

	case WM_MOUSEMOVE:
		//hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		//hBrush = CreateSolidBrush(RGB(0, 0, 0));

		hDC = GetDC(hWnd);
		SetColor(color, hPen, hBrush);
		if (bSw == TRUE && butt==6)
		{
			SelectObject(hDC, hPen);
			MoveToEx(hDC, nAx, nAy, &pOint);
			nAx = LOWORD(lParam); // nAx���� ���콺�� x��ǥ�� ����.
			nAy = HIWORD(lParam); // nAy���� ���콺�� y��ǥ�� ����.

			LineTo(hDC, nAx, nAy);
			ReleaseDC(hWnd, hDC);
		}
		break;

	case WM_PAINT:
		// �켱 ���� �����ϰ�...���Ⱑ 0�̸� ����Ʈ ũ��...
		//hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		//hBrush = CreateSolidBrush(RGB(0, 0, 0));
		// WM_PAINT �޽����� ������ �˸���.
		hDC = BeginPaint(hWnd, &ps);

		SetColor(color, hPen, hBrush);

		// bSw ���� FALSE�̸� �� �Ʊ� ���콺 ��ư�� �������� �Ʒ��� �ҽ��� ó���ȴ�.
		if (bSw == FALSE)
		{
			// ���� ����̽� ���ؽ�Ʈ�� �ִ´�.
			SelectObject(hDC, hPen);

			switch (butt)
			{
			case 1:

				// ���콺 ��ư�� Ŭ���� ������ Ŀ���� �ű��.
				MoveToEx(hDC, nAx, nAy, &pOint);
				// �׸��� ���콺 ��ư�� Ŭ���� ���� �������� �Ͽ� ������ ������
				// ���� �׸���.
				LineTo(hDC, nBx, nBy);
				break;
			case 2:
				//���׸�
				Ellipse(hDC, nAx, nAy, nBx, nBy);
				break;
			case 3:
				SelectObject(hDC, hBrush);
				Ellipse(hDC, nAx, nAy, nBx, nBy);
				break;
			case 4:
				Rectangle(hDC, nAx, nAy, nBx, nBy);
				break;
			case 5:
				SelectObject(hDC, hBrush);
				Rectangle(hDC, nAx, nAy, nBx, nBy);
				break;
			}
			
		}

		// ��ü�� �����Ѵ�.
		DeleteObject(hPen);
		DeleteObject(hBrush);
		// ����̽� ���ؽ�Ʈ�� �ݳ��Ѵ�.
		//ReleaseDC(hWnd, hDC);

		// WM_PAINT �޽����� ���� �˸���.
		EndPaint(hWnd, &ps);
		return FALSE;

		// uMsg ������ WM_DESTROY�޽����� ������
	case WM_DESTROY:
		PostQuitMessage(0);	// �����츦 �����Ѵ�.
		return FALSE;
	}
	// ��ó ó������ ���� �޽������� WndProc�Լ��� ������ Ȯ���� ó���Ǿ������� �Ѵ�.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void SetColor(int color ,HPEN& hPen, HBRUSH &hBrush)
{
	switch (color)
	{
	case 1:
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case 2:
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		break;
	case 3:
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		break;
	case 0:
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	}
}