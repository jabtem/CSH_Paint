// 리소스를 사용하기 위해서 resource.h 파일을 include해 주어야 한다.
#include "resource.h"
// API 함수들을 사용하려면 windows.h 파일을 include해 주어야 한다.
#include <windows.h>
// C 언어에서 자주 사용하였던 표준 입출력 헤더 추가
#include <stdio.h>

// 메시지의 처리를 위해 콜 백 함수를 선언한다.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetColor(int,HPEN&,HBRUSH&);
// 프로그램의 시작점을 지정한다.
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	// 윈도우의 핸들이 저장될 변수를 만든다.
	HWND hWnd;
	// 메시지 구조체를 선언한다.
	MSG mSg;

	// 윈도우의 캡션을 지정한다.
	WCHAR szTitle[] = L"그림판";
	// 윈도우의 클래스를 지정한다.
	WCHAR szClass[] = L"Class";


	// 추가적인 아이콘 셋팅 법/////////////////////////////////////
	HICON hIcon1;   // icon handle 
	HICON hIcon2;   // icon handle 

	// 기본 아이콘 생성
	hIcon1 = LoadIcon(NULL, IDI_QUESTION);

	// 사용자 정의 아이콘 생성 
	hIcon2 = LoadIcon(hInstance, MAKEINTRESOURCE(101));
	///////////////////////////////////////////////////////////////

	// WNDCLASSEX 구조체를 선언한다. 참고로 창은 하나의 윈도우 클래스를 기반으로 생성된다.
	WNDCLASSEX WndEx;

	// WNDCLASSEX 구조체의 크기를 지정한다.
	WndEx.cbSize = sizeof(WndEx);

	// 윈도우의 스타일을 지정한다.
	WndEx.style = NULL;

	// 메시지를 처리할 함수를 지정한다. 즉 메시지가 발생하면 그 메시지를 WndProc 함수에서 처리한다.
	WndEx.lpfnWndProc = WndProc;

	// 추가 클래스를 지정한다. 추가 클래스가 없기 때문에 NULL 값으로 지정한다.
	WndEx.cbClsExtra = 0;

	// 추가 윈도우를 지정한다. 추가 윈도우가 없기 때문에 NULL 값으로 지정한다.
	WndEx.cbWndExtra = 0;

	// 인스턴스 핸들을 지정한다.
	WndEx.hInstance = hInstance;

	// 실행 파일에 쓰일 아이콘을 지정한다. LoadIcon() 함수는 리소스에서 아이콘을 불러와 반환한다.
	WndEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	// 윈도우에서 쓰일 커서를 지정한다. LoadCursor() 함수는 미리 예약된 커서 값을 반환한다.
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);

	// 윈도우의 배경색을 지정한다. GetStockObject() 함수는 흰색을 반환한다.
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// 윈도우에 사용될 메뉴를 지정한다. 메뉴가 없기 때문에 NULL 값으로 지정하였다.
	WndEx.lpszMenuName = NULL;

	// 클래스를 지정한다. 참고로 이 클래스는 CreateWindowEx() 함수에서 지정될 클래스와 동일해야 한다.
	WndEx.lpszClassName = szClass;

	// 윈도우의 캡션이 쓰일 아이콘을 지정한다. LoadIcon() 함수는 리소스에서 아이콘을 불러와 반환한다.
	WndEx.hIconSm = LoadIcon(hInstance, /*L"IDI_ICON"*/MAKEINTRESOURCE(101));
	//WndEx.hIconSm = hIcon2;



	// WNDCLASSEX에 지정된 값들을 레지스터에 등록한다.
	RegisterClassEx(&WndEx);

	// 윈도우를 생성한다.
	hWnd = CreateWindowEx(NULL,				// 윈도우의 스타일을 지정한다.
		szClass,				// 윈도우의 클래스를 지정한다.
		szTitle,				// 윈도우의 캡션을 지정한다.
		WS_OVERLAPPEDWINDOW,	// 윈도우의 스타일을 지정한다.
		CW_USEDEFAULT,			// 윈도우의 x좌표 위치를 지정한다. CW_USEDEFAULT 값으로 지정하였으므로 컴퓨터가 알아서 지정한다.
		CW_USEDEFAULT,			// 윈도우의 y좌표 위치를 지정한다. CW_USEDEFAULT 값으로 지정하였으므로 컴퓨터가 알아서 지정한다.
		800,					// 윈도우의 넓이를 320으로 지정하였다.
		600,					// 윈도우의 높이를 240으로 지정하였다.
		NULL,					// 윈도우를 포함하고 있는 다른 윈도우가 없으므로 NULL 값으로 지정하였다.
		NULL,					// 메뉴가 없으므로 NULL 값으로 지정하였다.
		hInstance,				// 인스턴스 핸들을 지정한다.
		NULL);					// 잘 쓰이지 않는다.

// 윈도우가 실제로 보여질 형태를 지정한다.
	ShowWindow(hWnd, nShowCmd);
	// 윈도우를 갱신하고 WM_PAINT 메시지를 호출한다.
	UpdateWindow(hWnd);

	// 메시지 처리를 위한 반복문 시작
	while (TRUE)
	{
		// 메시지 큐에 들어온 메시지가 있는지 확인한다.
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			// 만약 메시지가 있으면 MSG 구조체에서 메시지를 읽어온다.
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;	// 메시지 중에 WM_QUIT메시지가 있으면 빠져나간다.
			// 가상키가 발생하면 그 메시지를 받아와서 WM_CHAR에 해당하는 코드를 응용 프로그램의 메시지 큐에 넣어 둔다.
			TranslateMessage(&mSg);
			// 그 메시지들을 처리하기 위해 WndProc() 함수로 보낸다.
			DispatchMessage(&mSg);
		}
	}

	// 기타 부수적인 메시지를 반환한다.
	return mSg.wParam;
}

// 메시지를 처리하기 위해서 메시지 처리 함수를 정의한다.
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	// 디바이스 컨텍스트를 정의한다.
	HDC hDC;
	// 펜 객체를 가리키기 위함.
	HPEN hPen,hOldPen;
	HBRUSH hBrush,hOldBrush;
	// 윈도우의 갱신 영역에 관한 정보가 저장될 구조체 변수
	PAINTSTRUCT ps;

	static int butt = -1;//버튼구분용 변수
	static int color = -1;
	static HWND hButtPen;
	static HWND hButtLine;
	static HWND hButtCircle1, hButtCircle2;
	static HWND hButtRect, hButtRect2;
	static HWND hRed, hGreen, hBlue, hDefault;
	// 스태틱 변수 설정
	static int nAx=0, nAy=0, nBx=0, nBy=0;

	// x, y 좌표 값 저장을 위한 구조체
	static POINT pOint;
	// 선을 그리기 위한 변수
	static BOOL bSw = FALSE;

	// 윈도우에 출력될 문자열을 저장하기 위한 문자열 변수 선언
	TCHAR szText[100];
	WCHAR szText6[100] = L"~";
	WCHAR szText1[100] = L"/";
	WCHAR szText2[100] = L"○";
	WCHAR szText3[100] = L"●";
	WCHAR szText4[100] = L"□";
	WCHAR szText5[100] = L"■";

	// uMsg 변수에는 DispatchMessage() 함수에서 보낸 메시지들이 저장되어 있다.
	switch (uMsg)
	{
		static HBRUSH butt_Brush;
	case WM_CREATE:
		hButtPen = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			szText6,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 버튼의 스타일
			0,										// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)6,								// 버튼의 아이디				
			NULL,
			NULL);

		hButtLine = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			szText1,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 버튼의 스타일
			30,										// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)1,								// 버튼의 아이디				
			NULL,
			NULL);
		hButtCircle1 = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			szText2,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 버튼의 스타일
			60,										// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)2,								// 버튼의 아이디				
			NULL,
			NULL);
		hButtCircle2 = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			szText3,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 버튼의 스타일
			90,										// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)3,								// 버튼의 아이디				
			NULL,
			NULL);
		hButtRect = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			szText4,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 버튼의 스타일
			120,										// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)4,								// 버튼의 아이디				
			NULL,
			NULL);
		hButtRect2 = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			szText5,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // 버튼의 스타일
			150,									// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)5,								// 버튼의 아이디				
			NULL,
			NULL);

		hRed = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			L" " ,								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // 버튼의 스타일
			180,									// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)7,								// 버튼의 아이디				
			NULL,
			NULL);

		hGreen = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			L" ",								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // 버튼의 스타일
			210,									// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)8,								// 버튼의 아이디				
			NULL,
			NULL);
		hBlue = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			L" ",								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // 버튼의 스타일
			240,									// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)9,								// 버튼의 아이디				
			NULL,
			NULL);
		hDefault = CreateWindow(L"BUTTON",		// 버튼의 클래스를 지정한다.(정해져있음)
			L" ",								// 버튼의 캡션
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,  // 버튼의 스타일
			270,									// 버튼의 x 좌표 위치
			0,										// 버튼의 y 좌표 위치
			30,										// 버튼의 넓이
			30,										// 버튼의 높이
			hWnd,									// 부모 윈도우 핸들
			(HMENU)10,								// 버튼의 아이디				
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
			color = 1;//빨강
			break;
		case 8:
			color = 2;//초록
			break;
		case 9:
			color = 3;//파랑
			break;
		case 10:
			color = 0;//검정
			break;
		}
		return FALSE;
		// 마우스 왼쪽 버튼 클릭시...
	case WM_LBUTTONDOWN:
		// 마우스 버튼이 클릭되면 선이 그려지지 않게 한다.
		bSw = TRUE;
		// 마우스 좌표를 얻어온다.(단지 마우스가 클릭된 곳의 x, y 좌표 값만 저장한다.)
		nAx = LOWORD(lParam); // nAx에는 마우스의 x좌표가 들어간다.
		nAy = HIWORD(lParam); // nAy에는 마우스의 y좌표가 들어간다.
		return FALSE;

		// 마우스 왼쪽 버튼이 떨어지면...
	case WM_LBUTTONUP:
		// 마우스 버튼이 떨어진 곳을 기준으로 하여 선을 그리게 한다.
		bSw = FALSE;

		// 마우스 좌표를 얻어온다.(떨어진 곳의 x, y 좌표 값을 저장한다.)
		nBx = LOWORD(lParam); // nBx에는 마우스의 x좌표가 들어간다.
		nBy = HIWORD(lParam); // nBy에는 마우스의 y좌표가 들어간다.

		// 윈도우를 갱신한다. 참고로 윈도우를 갱신할 때는 UpdateWindow()함수와 같이 쓰는 것이 좋다.
		InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
		return FALSE;

	case WM_RBUTTONDOWN:
		bSw = TRUE;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		bSw = FALSE;
		return FALSE;
		// WM_PAINT 메시지 발생시(다시 그려야할 상황이 발생시 전달된다.)

	case WM_MOUSEMOVE:
		//hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		//hBrush = CreateSolidBrush(RGB(0, 0, 0));

		hDC = GetDC(hWnd);
		SetColor(color, hPen, hBrush);
		if (bSw == TRUE && butt==6)
		{
			SelectObject(hDC, hPen);
			MoveToEx(hDC, nAx, nAy, &pOint);
			nAx = LOWORD(lParam); // nAx에는 마우스의 x좌표가 들어간다.
			nAy = HIWORD(lParam); // nAy에는 마우스의 y좌표가 들어간다.

			LineTo(hDC, nAx, nAy);
			ReleaseDC(hWnd, hDC);
		}
		break;

	case WM_PAINT:
		// 우선 펜을 생성하고...굵기가 0이면 디폴트 크기...
		//hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		//hBrush = CreateSolidBrush(RGB(0, 0, 0));
		// WM_PAINT 메시지의 시작을 알린다.
		hDC = BeginPaint(hWnd, &ps);

		SetColor(color, hPen, hBrush);

		// bSw 값이 FALSE이면 즉 아까 마우스 버튼이 떨어지면 아래의 소스가 처리된다.
		if (bSw == FALSE)
		{
			// 펜을 디바이스 컨텍스트에 넣는다.
			SelectObject(hDC, hPen);

			switch (butt)
			{
			case 1:

				// 마우스 버튼이 클릭된 곳으로 커서를 옮긴다.
				MoveToEx(hDC, nAx, nAy, &pOint);
				// 그리고 마우스 버튼이 클릭된 곳을 기준으로 하여 떨어진 곳까지
				// 선을 그린다.
				LineTo(hDC, nBx, nBy);
				break;
			case 2:
				//원그림
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

		// 객체를 삭제한다.
		DeleteObject(hPen);
		DeleteObject(hBrush);
		// 디바이스 컨텍스트를 반납한다.
		//ReleaseDC(hWnd, hDC);

		// WM_PAINT 메시지의 끝을 알린다.
		EndPaint(hWnd, &ps);
		return FALSE;

		// uMsg 변수에 WM_DESTROY메시지가 있으면
	case WM_DESTROY:
		PostQuitMessage(0);	// 윈도우를 종료한다.
		return FALSE;
	}
	// 미처 처리하지 못한 메시지들을 WndProc함수로 보내어 확실히 처리되어지도록 한다.
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