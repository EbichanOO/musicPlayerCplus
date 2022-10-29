#include <windows.h>
#include <string>
#include <experimental/filesystem>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "keyboard";	// ウィンドウクラス
BOOL bStart = FALSE, bSeikai = TRUE;


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,LPSTR lpsCmdLine, int nCmdShow){
	MSG msg;
	BOOL bRet;
	if (!InitApp(hCurInst))return FALSE;
	if (!InitInstance(hCurInst, nCmdShow))return FALSE;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		}else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

//ウィンドウ・クラスの登録

ATOM InitApp(HINSTANCE hInst){
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//プロシージャ名
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//インスタンス
	wc.hIcon = NULL;
	wc.hCursor = (HCURSOR)LoadImage(NULL,IDC_ARROW,IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCSTR)szClassName;
	wc.hIconSm = NULL;
	return (RegisterClassEx(&wc));
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow){
	HWND hWnd;

	hWnd = CreateWindow(szClassName,"KeyBoard", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,240,180,NULL,NULL, hInst, NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
	HDC hdc;
	PAINTSTRUCT ps;
	MMTIME mm;

	char tcRe[32];
	char *str = "Please Press some key...";
	char *str2 = "--> A key was pressed!!";
    std::experimental::filesystem::path path_path = std::experimental::filesystem::current_path();
    std::string pwd = path_path.string();
    char pwd_c[500];

	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, str, (int)strlen(str));
		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:
		switch(wp){
			case VK_ESCAPE:
				PostQuitMessage(0);
			return 0;

            case 'b':
                sprintf(pwd_c, "%s%s", pwd.c_str(), "\\musics\\mVGVYd1B8Oc.wav");
				/*
                hdc = GetDC(hWnd);
				SetTextColor(hdc, RGB(30, 30, 30));  //文字の色を設定
				SetBkColor(hdc, RGB(255, 255, 0));  //文字の背景色を設定
				TextOut(hdc, 10, 60, pwd_c, strlen(pwd_c));
				ReleaseDC(hWnd, hdc);*/
                
                PlaySound(pwd_c, NULL, (SND_ASYNC|SND_FILENAME) );
            case 'A': //SHIFT + Aキーが押された時に実行される
				hdc = GetDC(hWnd);
				SetTextColor(hdc, RGB(30, 30, 30));  //文字の色を設定
				SetBkColor(hdc, RGB(255, 255, 0));  //文字の背景色を設定
				TextOut(hdc, 10, 40, str2, lstrlen(str2));
				ReleaseDC(hWnd, hdc);
				break;

			default:
				hdc = GetDC(hWnd);
				wsprintf(tcRe, "%d", (int)wp);
				SetTextColor(hdc, RGB(200, 200, 200));  //文字の色を設定
				SetBkColor(hdc, RGB(0, 0, 0));  //文字の背景色を設定
				TextOut(hdc, 10, 80, tcRe, lstrlen(tcRe));
				ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_KEYUP:
		//何らかのキーが押されたときに発生するイベント
		break;

	case WM_KEYDOWN:
		switch (wp)	{
			//  エスケープキーの場合
		case VK_ESCAPE:
			// ウィンドウの閉じるメッセージ送信
			MessageBox(hWnd, "エスケープキーが押されたよ", "あああああ", MB_OK);
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}