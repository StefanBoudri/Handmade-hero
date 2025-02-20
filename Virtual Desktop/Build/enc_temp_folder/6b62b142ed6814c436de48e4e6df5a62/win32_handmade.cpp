#include <windows.h>

LRESULT CALLBACK MainWindowCallBack(HWND window,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    LRESULT result = 0;

    switch(message)
    {
        case WM_SIZE: 
        {
            OutputDebugStringA("WM_SIZE\n");
        } break;

        case WM_DESTROY: 
        {
            OutputDebugStringA("WM_DESTROY\n");
        } break;
        
        case WM_CLOSE: 
        {
            OutputDebugStringA("WM_CLOSE\n");
        } break;
        
        case WM_ACTIVATEAPP: 
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC deviceContext = BeginPaint(window, &paint);
            int x = paint.rcPaint.left;
            int y = paint.rcPaint.top;
            int height = paint.rcPaint.bottom - paint.rcPaint.top;
            int width = paint.rcPaint.right - paint.rcPaint.left;
            PatBlt(deviceContext, x, y, width, height, WHITENESS);
            EndPaint(window, &paint);
        }

        default:
        {
//            OutputDebugStringA("default");
            result = DefWindowProc(window, message, wParam, lParam);
        }
    }

    return(result);
}

int CALLBACK WinMain(HINSTANCE instance,
                     HINSTANCE prevInstance,
                     LPSTR commandLine,
                     int showCode)
{
    WNDCLASS windowClass = {};
    windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    windowClass.lpfnWndProc = MainWindowCallBack;
    windowClass.hInstance = instance;
 // windowClass.hIcon;
    windowClass.lpszClassName = "HandmadeHeroWindowClass" ;
    if(RegisterClass(&windowClass))
    {
        HWND windowHandle =
            CreateWindowEx(
                0, 
                windowClass.lpszClassName, 
                "Handmade Hero", 
                WS_OVERLAPPEDWINDOW|WS_VISIBLE, 
                CW_USEDEFAULT, 
                CW_USEDEFAULT, 
                CW_USEDEFAULT, 
                CW_USEDEFAULT, 
                0, 
                0, 
                instance, 
                0);
        if(windowHandle != NULL)
        {
            MSG message;
            for(;;)
            {
                BOOL messageResult = GetMessage(&message, 0, 0, 0);
                if(messageResult > 0)
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                else
                {
                    break;
                }
            }

        }
        else
        {
            
        }
    }
    else
    {
    }

    return 0;
}