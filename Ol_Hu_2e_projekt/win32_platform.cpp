#include <windows.h>

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsgm, WPARAM wParam, LPARAM lParam)
{

}
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmfLine, int nShowCmd)
{
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = "Game Window Class";

}