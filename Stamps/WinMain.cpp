#include <windows.h>

#include "EllipticalStamp.h"
#include "RectangularStamp.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex; HWND hWnd; MSG msg;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = "ObjectMovingClass";
	wcex.hIconSm = wcex.hIcon;

	RegisterClassEx(&wcex);

	hWnd = CreateWindow("ObjectMovingClass", "Lab #2 OSiSP",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	//HDC hdc = GetWindowDC(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	{
		HDC hdc = GetWindowDC(hWnd);
		EllipticalStamp stamp1 = EllipticalStamp(hdc, L"Всё неправильно, уважаемый! ", FF_MODERN , POINT{ 300, 150 });
		stamp1.Print(POINT{ 500, 150 });
		EllipticalStamp stamp2 = EllipticalStamp(hdc, L"Всё неправильно, уважаемый! ", FF_ROMAN, POINT{ 150, 150 });
		stamp2.Print(POINT{ 100, 250 });

		RectangularStamp stamp3 = RectangularStamp(hdc, L"Ладно, что-то похоже на правду ", FF_DECORATIVE, POINT{ 200, 200 });
		stamp3.Print(POINT{ 50, 50 });
	}
	while (GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		exit(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}