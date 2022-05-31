#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
#include<math.h>
#include <iostream>
#include <vector>
#include <string>
#include<list>
#include<stack>
#include<cmath>
#include<algorithm>
#include<fstream>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)RGB(255, 255, 0);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("Code::Blocks Template Windows App"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        544,                 /* The programs width */
        375,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
        );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
int Round(double num)
{
    return (int)(num + 0.5);
}
void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}

void swapPoints(POINT& p1, POINT& p2)
{
    int tmp = p1.x;
    p1.x = p2.x;
    p2.x = tmp;
    tmp = p1.y;
    p1.y = p2.y;
    p2.y = tmp;
}

void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{

    SetPixel(hdc, xc + a, yc + b, c);
    SetPixel(hdc, xc - a, yc + b, c);
    SetPixel(hdc, xc - a, yc - b, c);
    SetPixel(hdc, xc + a, yc - b, c);
    SetPixel(hdc, xc + b, yc + a, c);
    SetPixel(hdc, xc - b, yc + a, c);
    SetPixel(hdc, xc - b, yc - a, c);
    SetPixel(hdc, xc + b, yc - a, c);


}
void Draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc - x, yc + y, color);
}

void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
void DrawLineParametric(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color)
{
    int dx = xe - xs;
    int dy = ye - ys;
    double slope = (double)dy / dx;
    if (xs > xe)
    {
        swap(xs, xe);
        swap(ys, ye);
    }
    for (int x = xs; x <= xe; x++)
    {
        int y = round(ys + (x - xs) * slope);
        SetPixel(hdc, x, y, color);
    }
}
struct Point
{
    int x, y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
void SimpleDDA(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color)
{
    int dx = xe - xs;
    int dy = ye - ys;
    SetPixel(hdc, xs, ys, color);
    if (abs(dx) >= abs(dy))
    {
        int x = xs, xinc = dx > 0 ? 1 : -1;
        double y = ys, yinc = (double)dy / dx * xinc;
        while (x != xe)
        {
            x += xinc;
            y += yinc;
            SetPixel(hdc, x, Round(y), color);
        }
    }
    else
    {
        int y = ys, yinc = dy > 0 ? 1 : -1;
        double x = xs, xinc = (double)dx / dy * yinc;
        while (y != ye)
        {
            x += xinc;
            y += yinc;
            SetPixel(hdc, Round(x), y, color);
        }
    }
}
void DrawLineBresenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int x = x1, y = y1;
    double dx = x2 - x1, dy = y2 - y1;
    SetPixel(hdc, x, y, c);
    if ((dx == 0 || dy / dx > 1) && dy > 0 && dx >= 0)
    {
        int d = 2 * dx - dy, d1 = 2 * dx, d2 = 2 * dx - 2 * dy;
        while (y != y2)
        {
            if (d <= 0)
            {
                y++;
                d += d1;
            }
            else
            {
                x++;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx >= 0 && dy / dx <= 1 && dy >= 0 && dx > 0)
    {
        int d = dx - 2 * dy, d1 = -2 * dy, d2 = 2 * dx - 2 * dy;
        while (x != x2)
        {
            if (d > 0)
            {
                x++;
                d += d1;
            }
            else
            {
                x++;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx < 0 && dy / dx >= -1 && dy <= 0 && dx>0)
    {
        int d = -dx - 2 * dy, d1 = -2 * dy, d2 = -2 * dx - 2 * dy;
        while (x != x2)
        {
            if (d <= 0)
            {
                x++;
                d += d1;
            }
            else
            {
                x++;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if ((dx == 0 || dy / dx < -1) && dy < 0 && dx >= 0)
    {
        int d = -2 * dx - dy, d1 = -2 * dx, d2 = -2 * dx - 2 * dy;
        while (y != y2)
        {
            if (d > 0)
            {
                y--;
                d += d1;
            }
            else
            {
                x++;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if ((dx == 0 || dy / dx > 1) && dy < 0 && dx <= 0)
    {
        int d = -2 * dx + dy, d1 = -2 * dx, d2 = -2 * dx + 2 * dy;
        while (y != y2)
        {
            if (d <= 0)
            {
                y--;
                d += d1;
            }
            else
            {
                x--;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx >= 0 && dy / dx <= 1 && dy <= 0 && dx < 0)
    {
        int d = -dx + 2 * dy, d1 = 2 * dy, d2 = -2 * dx + 2 * dy;
        while (x != x2)
        {
            if (d > 0)
            {
                x--;
                d += d1;
            }
            else
            {
                x--;
                y--;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if (dy / dx < 0 && dy / dx >= -1 && dy >= 0 && dx < 0)
    {
        int d = dx + 2 * dy, d1 = 2 * dy, d2 = 2 * dx + 2 * dy;
        while (x != x2)
        {
            if (d <= 0)
            {
                x--;
                d += d1;
            }
            else
            {
                x--;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else if ((dx == 0 || dy / dx < -1) && dy > 0 && dx <= 0)
    {
        int d = 2 * dx + dy, d1 = 2 * dx, d2 = 2 * dx + 2 * dy;
        while (y != y2)
        {
            if (d > 0)
            {
                y++;
                d += d1;
            }
            else
            {
                x--;
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, c);
        }
    }
}
void CircleDirect(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int R2 = R * R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        x++;
        y = Round(sqrt((double)(R2 - x * x)));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}
void CircleBresenham(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        if (d < 0)
            d += 2 * x + 2;
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}
void CircleFasterBresenham(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {
            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        x++;
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}
void CirclePolar(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = R, y = 0;
    double theta = 0, dtheta = 1.0 / R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x > y)
    {
        theta += dtheta;
        x = round(R * cos(theta));
        y = round(R * sin(theta));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}

void CircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    double x = R, y = 0;
    double dtheta = 1.0 / R;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    Draw8Points(hdc, xc, yc, R, 0, color);
    while (x > y)
    {
        double x1 = (x * cdtheta) - (y * sdtheta);
        y = (x * sdtheta) + (y * cdtheta);
        x = x1;
        Draw8Points(hdc, xc, yc, round(x), round(y), color);
    }
}

void Draw2Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color, int quarter)
{
    if (quarter == 4)
    {
        SetPixel(hdc, xc + b, yc + a, color); // 4
        SetPixel(hdc, xc + a, yc + b, color);
    }
    else if (quarter == 3)
    {
        SetPixel(hdc, xc - a, yc + b, color); // 3
        SetPixel(hdc, xc - b, yc + a, color);
    } // 3
    else if (quarter == 2)
    {
        SetPixel(hdc, xc - a, yc - b, color); // 2
        SetPixel(hdc, xc - b, yc - a, color);
    } // 2
    else if (quarter == 1)
    {
        SetPixel(hdc, xc + a, yc - b, color); // 1
        SetPixel(hdc, xc + b, yc - a, color);
    } // 1
}
void DrawCircleAndFillItWithCircles(HDC hdc, int xc, int yc, int R, COLORREF color, int quarter)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {
            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        x++;
        Draw8Points(hdc, xc, yc, x, y, color);
    }
    R--;
    while (R != 0)
    {
        int x = 0, y = R;
        int d = 1 - R;
        int c1 = 3, c2 = 5 - 2 * R;
        Draw2Points(hdc, xc, yc, x, y, color, quarter);
        while (x < y)
        {
            if (d < 0)
            {
                d += c1;
                c2 += 2;
            }
            else
            {
                d += c2;
                c2 += 4;
                y--;
            }
            c1 += 2;
            x++;
            Draw2Points(hdc, xc, yc, x, y, color, quarter);
        }
        R -= .00000000001;
    }
}
void DrawLine1(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);
        int x = x1;
        while (x < x2)
        {
            x++;
            double y = y1 + (double)(x - x1) * dy / dx;
            SetPixel(hdc, x, Round(y), c);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);
        int y = y1;
        while (y < y2)
        {
            y++;
            double x = x1 + (double)(y - y1) * dx / dy;
            SetPixel(hdc, Round(x), y, c);
        }
    }
}
void Draw8PointsFillCircleWithLine(HDC hdc, int xc, int yc, int a, int b, COLORREF color, int Quarter)
{
    if (Quarter == 1)
    {
        SetPixel(hdc, xc + a, yc + b, color);
        SetPixel(hdc, xc - a, yc + b, color);
        SetPixel(hdc, xc - a, yc - b, color);
        SetPixel(hdc, xc + a, yc - b, color);
        DrawLine1(hdc, xc, yc, xc + a, yc - b, color);
        SetPixel(hdc, xc + b, yc + a, color);
        SetPixel(hdc, xc - b, yc + a, color);
        SetPixel(hdc, xc - b, yc - a, color);
        SetPixel(hdc, xc + b, yc - a, color);
        DrawLine1(hdc, xc, yc, xc + b, yc - a, color);
    }
    else if (Quarter == 2)
    {
        SetPixel(hdc, xc + a, yc + b, color);
        SetPixel(hdc, xc - a, yc + b, color);
        SetPixel(hdc, xc - a, yc - b, color);
        DrawLine1(hdc, xc, yc, xc - a, yc - b, color);
        SetPixel(hdc, xc + a, yc - b, color);
        SetPixel(hdc, xc + b, yc + a, color);
        SetPixel(hdc, xc - b, yc + a, color);
        SetPixel(hdc, xc - b, yc - a, color);
        DrawLine1(hdc, xc, yc, xc - b, yc - a, color);
        SetPixel(hdc, xc + b, yc - a, color);
    }
    else if (Quarter == 3)
    {
        SetPixel(hdc, xc + a, yc + b, color);
        SetPixel(hdc, xc - a, yc + b, color);
        DrawLine1(hdc, xc, yc, xc - a, yc + b, color); // 3
        SetPixel(hdc, xc - a, yc - b, color);
        SetPixel(hdc, xc + a, yc - b, color);
        SetPixel(hdc, xc + b, yc + a, color);
        SetPixel(hdc, xc - b, yc + a, color);
        DrawLine1(hdc, xc, yc, xc - b, yc + a, color); // 3
        SetPixel(hdc, xc - b, yc - a, color);
        SetPixel(hdc, xc + b, yc - a, color);
    }
    else if (Quarter == 4)
    {
        SetPixel(hdc, xc + a, yc + b, color);
        DrawLine1(hdc, xc, yc, xc + a, yc + b, color); // 4
        SetPixel(hdc, xc - a, yc + b, color);
        SetPixel(hdc, xc - a, yc - b, color);
        SetPixel(hdc, xc + a, yc - b, color);
        SetPixel(hdc, xc + b, yc + a, color);
        DrawLine1(hdc, xc, yc, xc + b, yc + a, color); // 4
        SetPixel(hdc, xc - b, yc + a, color);
        SetPixel(hdc, xc - b, yc - a, color);
        SetPixel(hdc, xc + b, yc - a, color);
    }
}
void DrawCircleAndFillItWithLines(HDC hdc, int xc, int yc, int R, COLORREF color, int quarter)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    Draw8PointsFillCircleWithLine(hdc, xc, yc, x, y, color, quarter);
    while (x < y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {
            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        x++;
        Draw8PointsFillCircleWithLine(hdc, xc, yc, x, y, color, quarter);
    }
}

void DrawEllipseCartesian(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{
    int x = 0;
    double y = B;
    Draw4Points(hdc, xc, yc, x, y, color);
    while (x * B * B < y * A * A)
    {
        x++;
        y = B * sqrt(1 - (double)(x * x) / (A * A));
        Draw4Points(hdc, xc, yc, x, Round(y), color);
    }
    int y2 = 0;
    double x2 = A;
    Draw4Points(hdc, xc, yc, x2, y2, color);
    while (x2 * B * B > y2 * A * A)
    {
        y2++;
        x2 = A * sqrt(1 - (double)(y2 * y2) / (B * B));
        Draw4Points(hdc, xc, yc, Round(x2), y2, color);
    }
}
void DrawEllipseBresenham(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{


    float dx, dy, d1, d2, x, y;
    x = 0;
    y = B;
    d1 = (B * B) - (A * A * B) + (0.25 * A * A);
    dx = 2 * B * B * x;
    dy = 2 * A * A * y;
    while (dx < dy)
    {
        Draw4Points(hdc, xc, yc, x, y, color);
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * B * B);
            d1 = d1 + dx + (B * B);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * B * B);
            dy = dy - (2 * A * A);
            d1 = d1 + dx - dy + (B * B);
        }
    }
    d2 = ((B * B) * ((x + 0.5) * (x + 0.5))) +
        ((A * A) * ((y - 1) * (y - 1))) -
        (A * A * B * B);
    while (y >= 0)
    {
        Draw4Points(hdc, xc, yc, x, y, color);
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * A * A);
            d2 = d2 + (A * A) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * B * B);
            dy = dy - (2 * A * A);
            d2 = d2 + dx - dy + (A * A);
        }
    }

}
void DrawEllipsePolar(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{

    double x = A, y = 0, theta = 0;
    Draw4Points(hdc, xc, yc, x, y, color);
    while (x > y)
    {
        theta += 1.0 / max(A, B);
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y), color);
    }
    while (x < y)
    {
        theta += 1.0 / max(A, B);
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y), color);
    }
}
class Vector4
{
    double v[4];
public:
    Vector4(double a = 0, double b = 0, double c = 0, double d = 0)
    {
        v[0] = a; v[1] = b; v[2] = c; v[3] = d;
    }
    Vector4(double a[])
    {
        memcpy(v, a, 4 * sizeof(double));
    }
    double& operator[](int i)
    {
        return v[i];
    }
};

double DotProduct(Vector4& a, Vector4& b) //multiplying a raw vector by a column vector
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

struct Vector2
{
    double x, y;
    Vector2(double a = 0, double b = 0)
    {
        x = a; y = b;
    }
};

struct Vector8 {
    double v[2];
    Vector8(double x = 0, double y = 0)
    {
        v[0] = x; v[1] = y;
    }
    double& operator[](int i) {
        return v[i];
    }
};

class Matrix4
{
    Vector4 M[4];
public:
    Matrix4(double A[])
    {
        memcpy(M, A, 16 * sizeof(double));
    }
    Vector4& operator[](int i)
    {
        return M[i];
    }
};

Vector4 operator*(Matrix4 M, Vector4& b) // right multiplication of M by b
{
    Vector4 res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res[i] += M[i][j] * b[j];
    return res;
}

Vector4 GetHermiteCoeff(double x0, double s0, double x1, double s1)
{
    static double H[16] = { 2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0 };
    static Matrix4 basis(H);
    Vector4 v(x0, s0, x1, s1);
    return basis * v;
}

void DrawHermiteCurve1(HDC hdc, Vector2& P0, Vector2& T0, Vector2& P1, Vector2& T1, int
    numpoints)
{
    Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
    Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
    if (numpoints < 2)return;
    double dt = 1.0 / (numpoints - 1);
    for (double t = 0; t <= 1; t += dt)
    {
        Vector4 vt;
        vt[3] = 1;
        for (int i = 2; i >= 0; i--)vt[i] = vt[i + 1] * t;
        int x = round(DotProduct(xcoeff, vt));
        int y = round(DotProduct(ycoeff, vt));
        if (t == 0)MoveToEx(hdc, x, y, NULL); else LineTo(hdc, x, y);
    }
}

void DrawHermiteCurve2(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c, int cx, int cy, int RR2)
{
    int a, b;
    double a0 = x1, a1 = 5,
        a2 = -3 * x1 - 2 * 5 + 3 * x2 - 5,
        a3 = 2 * x1 + 5 - 2 * x2 + 5;
    double b0 = y1, b1 = 5,
        b2 = -3 * y1 - 2 * 5 + 3 * y2 - 5,
        b3 = 2 * y1 + 5 - 2 * y2 + 5;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;
        a = cx - x;
        b = cy - y;
        if (x >= cx && x <= (cx + RR2) && y >= cy && y <= (cy + RR2)) {
            SetPixel(hdc, Round(x), Round(y), c);
        }


    }
}
void DrawHermiteCurve4(HDC hdc, Vector8& p1, Vector8& T1, Vector8& p2, Vector8& T2, COLORREF c)
{
    double a0 = p1[0], a1 = T1[0],
        a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
        a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];
    double b0 = p1[1], b1 = T1[1],
        b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
        b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;
        SetPixel(hdc, Round(x), Round(y), c);
    }
}
void DrawCardinalSpline(HDC hdc, Vector8 P[], int n, double c, COLORREF C)
{
    double c1 = 1 - c;
    Vector8 T0 = c1 * ((P[2][0] - P[0][0]), (P[2][1] - P[0][1]));
    for (int i = 0; i < n - 1; i++)
    {
        Vector8 T1 = c1 * ((P[i + 1][0] - P[i - 1][0]), (P[i + 1][1] - P[i - 1][1]));
        DrawHermiteCurve4(hdc, P[i], T0, P[i + 1], T1, C);
        T0 = T1;
    }

}
void drawBezierCurve(HDC hdc, int x1, int y1, int x2, int y2, int u1, int u2, int u3, int u4, COLORREF c, int cx, int cy, int RR2, int RR3)
{
    int a, b;
    // int u1=50;int u2=60;int u3=30;int u4=60;
    double a0 = x1, a1 = u1,
        a2 = -3 * x1 - 2 * u1 + 3 * x2 - u2,
        a3 = 2 * x1 + u1 - 2 * x2 + u2;
    double b0 = y1, b1 = u3,
        b2 = -3 * y1 - 2 * u3 + 3 * y2 - u4,
        b3 = 2 * y1 + u3 - 2 * y2 + u4;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;
        a = cx - x;
        b = cy - y;
        if (x >= cx && x <= (cx + RR2) && y >= cy && y <= (cy + RR3)) {
            SetPixel(hdc, Round(x), Round(y), c);
        }


    }
}
void drawbetzer(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color, int cx, int cy, int RR, int RR1) {
    int dx = xe - xs;
    int dy = ye - ys;
    int xa = xs + RR;
    int t1 = 5, t2 = 6, t3 = 3, t4 = 1;
    drawBezierCurve(hdc, xs, ys, xa, ys, t1, t2, t3, t4, color, cx, cy, RR, RR1);
    if (abs(dx) >= abs(dy))
    {
        int x = xs, xinc = dx > 0 ? 1 : -1;
        double y = ys, yinc = (double)dy / dx * xinc;
        while (x != xe)
        {
            x += xinc;
            y += yinc;

            xa = round(x) + RR;

            drawBezierCurve(hdc, xs, round(y), xa, round(y), t1, t2, t3, t4, color, cx, cy, RR, RR1);
        }
    }
    else
    {
        int y = ys, yinc = dy > 0 ? 1 : -1;
        double x = xs, xinc = (double)dx / dy * yinc;
        while (y != ye)
        {
            x += xinc;
            y += yinc;
            xa = round(x) + RR;
            SetPixel(hdc, round(x), y, color);
            //drawbetzercurve( hdc, round(x), y,xa,y,color, cx, cy , RR );
            drawBezierCurve(hdc, round(x), y, xa, y, t1, t2, t3, t4, color, cx, cy, RR, RR1);
        }
    }
}
void DrawRec(HDC hdc, int xc, int yc, int dist, int dist1, COLORREF c)
{
    int x1, y1;

    x1 = xc + dist;
    y1 = yc + dist1;
    DrawLine1(hdc, xc, yc, x1, yc, c);
    drawbetzer(hdc, xc, yc, xc, y1, c, xc, yc, dist, dist1);

    DrawLine1(hdc, xc, yc, xc, y1, c);

    DrawLine1(hdc, xc, y1, x1, y1, c);

    DrawLine1(hdc, x1, yc, x1, y1, c);

}
struct Vector
{
    double v[2];
    Vector(double x = 0, double y = 0)
    {
        v[0] = x;
        v[1] = y;
    }
    double& operator[](int i)
    {
        return v[i];
    }
};

//floodfill recursive//
void RecursiveFloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF newColor)
{
    COLORREF colorOfPoint = GetPixel(hdc, x, y);
    if (colorOfPoint == borderColor || colorOfPoint == newColor)
        return;
    SetPixel(hdc, x, y, newColor);
    RecursiveFloodFill(hdc, x + 1, y, borderColor, newColor);
    RecursiveFloodFill(hdc, x - 1, y, borderColor, newColor);
    RecursiveFloodFill(hdc, x, y + 1, borderColor, newColor);
    RecursiveFloodFill(hdc, x, y - 1, borderColor, newColor);
}
//non recursve floodfill
void NonRecursiveFloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF newColor)
{
    stack<Point> stack;
    stack.push(Point(x, y));
    while (!stack.empty())
    {
        Point p = stack.top();
        stack.pop();
        COLORREF PointColor = GetPixel(hdc, p.x, p.y);
        if (PointColor == borderColor || PointColor == newColor)
            continue;
        else
        {
            SetPixel(hdc, p.x, p.y, newColor);
            stack.push(Point(p.x + 1, p.y));
            stack.push(Point(p.x - 1, p.y));
            stack.push(Point(p.x, p.y + 1));
            stack.push(Point(p.x, p.y - 1));
        }
    }

}
//hermite square//
void DrawHermiteCurve(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c, int cx, int cy, int RR2)
{
    int a, b;
    double a0 = x1, a1 = 50,
        a2 = -3 * x1 - 2 * 50 + 3 * x2 - 50,
        a3 = 2 * x1 + 50 - 2 * x2 + 50;
    double b0 = y1, b1 = 100,
        b2 = -3 * y1 - 2 * 100 + 3 * y2 - 150,
        b3 = 2 * y1 + 100 - 2 * y2 + 150;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;
        a = cx - x;
        b = cy - y;
        if (x >= cx && x <= (cx + RR2) && y >= cy && y <= (cy + RR2)) {
            SetPixel(hdc, Round(x), Round(y), c);
        }


    }
}
void drawhermite(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color, int cx, int cy, int RR) {
    int dx = xe - xs;
    int dy = ye - ys;
    int yy = ye + RR;
    //SetPixel(hdc,xs,ys,color);
    DrawHermiteCurve2(hdc, xs, ys, xs, yy, color, cx, cy, RR);
    if (abs(dx) >= abs(dy))
    {
        int x = xs, xinc = dx > 0 ? 1 : -1;
        double y = ys, yinc = (double)dy / dx * xinc;
        while (x != xe)
        {
            x += xinc;
            y += yinc;
            SetPixel(hdc, x, round(y), color);
            yy = round(y) + RR;
            DrawHermiteCurve2(hdc, x, round(y), x, yy, color, cx, cy, RR);
        }
    }
    else
    {
        int y = ys, yinc = dy > 0 ? 1 : -1;
        double x = xs, xinc = (double)dx / dy * yinc;
        while (y != ye)
        {
            x += xinc;
            y += yinc;
            SetPixel(hdc, round(x), y, color);
        }
    }
}
void DrawSquare(HDC hdc, int xc, int yc, int dist, COLORREF c)
{
    int x1, y1;
    //dist=100;
    //cout<<"enter the square size "<<endl;
    //cin>>dist;
    x1 = xc + dist;
    y1 = yc + dist;
    DrawLine1(hdc, xc, yc, x1, yc, c);
    drawhermite(hdc, xc, yc, x1, yc, c, xc, yc, dist);
    DrawLine1(hdc, xc, yc, xc, y1, c);

    DrawLine1(hdc, xc, y1, x1, y1, c);

    DrawLine1(hdc, x1, yc, x1, y1, c);

}
//ConvixFilling//
typedef struct
{
    int xLeft, xRight;
}edgeTable[800];
void Initialize(edgeTable table)
{
    for (int i = 0; i < 800; i++)
    {
        table[i].xLeft = INT_MAX;
        table[i].xRight = -INT_MAX;
    }
}

void UpdateEdgeToTable(POINT p1, POINT p2, edgeTable table)
{

    if (p1.y == p2.y)
        return;
    if (p1.y > p2.y)
        swapPoints(p1, p2);
    double slopeInverse = (p2.x - p1.x) / (double)(p2.y - p1.y);
    double x = p1.x;
    int y = p1.y;
    while (y < p2.y)
    {
        if (x < table[y].xLeft)
            table[y].xLeft = (int)ceil(x);
        if (x > table[y].xRight)
            table[y].xRight = (int)floor(x);
        y++;
        x += slopeInverse;
    }
}

void PolygonToTable(POINT PolygonPoints[], int n, edgeTable table)
{
    POINT p1 = PolygonPoints[n - 1];
    for (int i = 0; i < n; i++)
    {
        POINT p2 = PolygonPoints[i];
        UpdateEdgeToTable(p1, p2, table);
        p1 = p2;
    }
}

void TableToScreen(HDC hdc, edgeTable table, COLORREF color)
{

    for (int i = 0; i < 800; i++)
    {
        if (table[i].xLeft < table[i].xRight)
        {
            SimpleDDA(hdc, table[i].xLeft, i, table[i].xRight, i, color);
        }
    }
}

void FillConvexPolygon(HDC hdc, POINT PolygonPoints[], int n, COLORREF color)
{
    edgeTable table;
    Initialize(table);
    PolygonToTable(PolygonPoints, n, table);
    TableToScreen(hdc, table, color);
}
//nonConvix//
struct EdgeRec {
    double x, y_max, slopeInverse;
    EdgeRec(double x = 0.0, double y_max = 0.0, double slopeInverse = 0.0)
    {
        this->x = x;
        this->y_max = y_max;
        this->slopeInverse = slopeInverse;
    }
};
typedef list<EdgeRec> EdgeTable[800];
void scanEdge(POINT point1, POINT point2, EdgeTable table) {
    if (point1.y == point2.y)
    {
        return;
    }
    if (point1.y > point2.y)
    {
        swap(point1, point2);
    }
    EdgeRec rec(point1.x, point2.y, (double)(point2.x - point1.x) / (point2.y - point1.y));
    table[point1.y].push_back(rec);
}
void polygon2table(POINT point[], int n, EdgeTable table) {
    POINT point1 = point[n - 1];
    for (int i = 0; i < n; i++)
    {
        POINT point2 = point[i];
        scanEdge(point1, point2, table);
        point1 = point2;
    }
}

void table2screen(HDC hdc, EdgeTable table, COLORREF c) {
    int y = 0;
    list<EdgeRec>::iterator iterator;

    while (table[y].size() == 0)
    {
        y++;
    }
    list<EdgeRec> active = table[y];
    while (active.size() != 0) {

        active.sort([](EdgeRec& a, EdgeRec& b) {return a.x < b.x; });

        for (iterator = active.begin(); iterator != active.end(); iterator++) {
            EdgeRec& firstNode = *iterator;
            iterator++;
            if (iterator == active.end())
            {
                break;
            }
            EdgeRec& secondNode = *iterator;
            DrawLine1(hdc, ceil(firstNode.x), y, floor(secondNode.x), y, c);
        }
        y++;

        for (iterator = active.begin(); iterator != active.end();)
        {
            if (iterator->y_max == y)
            {
                iterator = active.erase(iterator);
            }
            else
            {
                iterator++;
            }
        }

        for (iterator = active.begin(); iterator != active.end(); iterator++)
        {
            iterator->x = iterator->x + iterator->slopeInverse;
        }

        if (table[y].size() != 0)
        {
            active.splice(active.end(), table[y]);
        }
    }
}

void fillPolygon(HDC hdc, POINT point[], int n, COLORREF c)
{
    EdgeTable table;
    polygon2table(point, n, table);
    table2screen(hdc, table, c);

}
void SwapPoints(POINT& v1, POINT& v2)
{
    POINT tmp = v1;
    v1 = v2;
    v2 = tmp;
}
////////////////////// clipping /////////////////////////

int ct = 0;
int rad, x_c, y_c;

struct point
{
    int x;
    int y;
};
struct Vertex
{
    double x, y;
    Vertex(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
};
struct shape
{
    int type;
    vector<point> ptss;
    COLORREF color;
};
point spefic_pt;
shape spefic_shape;
vector<shape> shapes;
typedef vector<Vertex> VertexList;
typedef bool (*IsInFunc)(Vertex& v, int edge);
typedef Vertex(*IntersectFunc)(Vertex& v1, Vertex& v2, int edge);
enum algorithms { pointClip, lineClip, drawCPt, drawCline };
int clipping = pointClip;


void add_point(int x, int y)
{
    spefic_pt.x = x;
    spefic_pt.y = y;
    spefic_shape.ptss.push_back(spefic_pt);
}

void add_shape(int shape_type, COLORREF shape_color)
{
    spefic_shape.type = shape_type;
    spefic_shape.color = shape_color;
    shapes.push_back(spefic_shape);
    spefic_shape.ptss.clear();
}
int r;
int x_1, y_1, x_2, y_2;
int X_left, Y_top, X_right, Y_bottom;
int X_start, Y_start, X_end, Y_end;

void parametric(HDC hdc, double x1, double y1, double x2, double y2, COLORREF color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    for (double t = 0; t < 1; t += 0.001)
    {
        int x = x1 + (dx * t);
        int y = y1 + (dy * t);
        SetPixel(hdc, x, y, color);
    }
}


///////////////////////////////////////////////////// Circle ///////////////////

void replace(int& x1, int& y1, int& x2, int& y2)
{
    int t = x1;
    x1 = x2;
    x2 = t;
    t = y1;
    y1 = y2;
    y2 = t;
}
void Draw8points(HDC hdc, int x, int y, int xc, int yc, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}
void myCircle(HDC hdc, int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    double d = 1 - r;
    Draw8points(hdc, x, y, xc, yc, RGB(10, 10, 10));
    while (x < y)
    {
        if (d <= 0)
        {
            d = d + 2 * x + 3;
        }
        else
        {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        Draw8points(hdc, x, y, xc, yc, RGB(10, 10, 10));
    }
}

///////////////////////////////////// line clipping using CIRCLE ///////////////////////////////////////
void DrawlineCircleClipping(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c, int cx, int cy, int RR2)
{
    int a, b;
    int dx = x2 - x1; // Different of x
    int dy = y2 - y1;// Different of y
    if (abs(dy) <= abs(dx))// if the M<1
    {
        if (x1 > x2)replace(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);//the center
        int x = x1;
        while (x < x2)
        {
            x++;
            double y = y1 + (double)(x - x1) * dy / dx; //y=y+m
            a = cx - x;
            b = cy - y;
            if (sqrt(a * a + b * b) <= RR2)
            {
                SetPixel(hdc, x, Round(y), c);
            }
        }
    }
    else
    {
        if (y1 > y2)replace(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);
        int y = y1;

        while (y < y2)
        {
            y++;
            double x = x1 + (double)(y - y1) * dx / dy;//x+=1/m
            a = cx - x;
            b = cy - y;
            if (sqrt(a * a + b * b) <= RR2)
            {
                SetPixel(hdc, Round(x), y, c);
            }
        }
    }

}

//////////////////////////////////////// point clipping using CIRCLE ///////////////////////////////////////
void DrawPointCircleClipping(HDC hdc, int x1, int y1, COLORREF c, int cx, int cy, int RR2)
{
    int a, b;
    a = cx - x1;
    b = cy - y1;
    if (sqrt(a * a + b * b) <= RR2)
    {
        SetPixel(hdc, x1, y1, c);
    }
}


void Square(HDC hdc, int x, int y, int w, int z)
{
    Rectangle(hdc, x, y, w, z);
}

//////////////////////////////// Point clipping using RECTANGLE //////////////////////////////////////
void pointClippping(HDC hdc, int x, int y, int xleft, int ytop, int xright, int ybottom, COLORREF color)
{
    if (x >= xleft && x <= xright && y >= ytop && y <= ybottom)

        SetPixel(hdc, x, y, color);
}

///////////////////////////////// line clipping using RECTANGLE ///////////////////////////////////
union OutCode
{
    unsigned All : 4;
    struct
    {
        unsigned left : 1, top : 1, right : 1, bottom : 1;
    };
};

OutCode GetOutCode(double x, double y, int xleft, int ytop, int xright, int ybottom)
{
    OutCode obj;
    obj.All = 0;
    if (x > xright)
        obj.right = 1;
    else if (x < xleft)
        obj.left = 1;
    if (y < ytop)
        obj.top = 1;
    else if (y > ybottom)
        obj.bottom = 1;
    return obj;
}

void VIntersect(double xs, double ys, double xe, double ye, int x, double* xi, double* yi)
{
    *xi = x;
    *yi = ys + (x - xs) * (ye - ys) / (xe - xs);
}

void HIntersect(double xs, double ys, double xe, double ye, int y, double* xi, double* yi)
{
    *yi = y;
    *xi = xs + (y - ys) * (xe - xs) / (ye - ys);
}

void lineClippping(HDC hdc, int xs, int ys, int xe, int ye, int xleft, int ytop, int xright, int ybottom, COLORREF color)
{
    double x1 = xs, y1 = ys, x2 = xe, y2 = ye;
    OutCode out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
    OutCode out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
    while ((out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi, yi;
        if (out1.All)
        {
            if (out1.left)
                VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out1.top)
                HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out1.right)
                VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else
                HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x1 = xi;
            y1 = yi;
            out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
        }
        else
        {
            if (out2.left)
                VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out2.top)
                HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out2.right)
                VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else
                HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x2 = xi;
            y2 = yi;
            out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
        }
    }
    if (!out1.All && !out2.All)
    {
        parametric(hdc, round(x1), round(y1), round(x2), round(y2), color);
    }
}
void draw_ptss(HDC hdc)
{
    for (int i = 0; i < shapes.size(); ++i)
    {
        switch (shapes[i].type)
        {
        case pointClip:
        {
            X_left = shapes[i].ptss[0].x;
            Y_top = shapes[i].ptss[0].y;
            X_right = shapes[i].ptss[1].x;
            Y_bottom = shapes[i].ptss[1].y;

            Rectangle(hdc, X_left, Y_top, X_right, Y_bottom);
            break;
        }

        case drawCPt:
        {
            pointClippping(hdc, shapes[i].ptss[0].x, shapes[i].ptss[0].y, X_left, Y_top, X_right, Y_bottom, shapes[i].color);
            break;
        }

        case lineClip:
        {
            X_left = shapes[i].ptss[0].x;
            Y_top = shapes[i].ptss[0].y;
            X_right = shapes[i].ptss[1].x;
            Y_bottom = shapes[i].ptss[1].y;

            Rectangle(hdc, X_left, Y_top, X_right, Y_bottom);
            break;
        }

        case drawCline:
        {
            X_start = shapes[i].ptss[0].x;
            Y_start = shapes[i].ptss[0].y;
            X_end = shapes[i].ptss[1].x;
            Y_end = shapes[i].ptss[1].y;

            lineClippping(hdc, X_start, Y_start, X_end, Y_end, X_left, Y_top, X_right, Y_bottom, shapes[i].color);
            break;
        }


        default:
            break;
        }
    }
}

////////////////////////////////////////////// POLYGOOOOOOOOON clipping using RECTANGLE  ////////////////////////////


VertexList ClipWithEdge(VertexList p, int edge, IsInFunc In, IntersectFunc Intersect)
{
    VertexList OutList;
    Vertex v1 = p[p.size() - 1];
    bool v1_in = In(v1, edge);
    for (int i = 0; i < (int)p.size(); i++)
    {
        Vertex v2 = p[i];
        bool v2_in = In(v2, edge);
        if (!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1, v2, edge));
            OutList.push_back(v2);
        }
        else if (v1_in && v2_in) OutList.push_back(v2);
        else if (v1_in) OutList.push_back(Intersect(v1, v2, edge));
        v1 = v2;
        v1_in = v2_in;
    }
    return OutList;
}

bool InLeft(Vertex& v, int edge)
{
    return v.x >= edge;
}
bool InRight(Vertex& v, int edge)
{
    return v.x <= edge;
}
bool InTop(Vertex& v, int edge)
{
    return v.y >= edge;
}
bool InBottom(Vertex& v, int edge)
{
    return v.y <= edge;
}

Vertex VIntersect(Vertex& v1, Vertex& v2, int xedge)
{
    Vertex res;
    res.x = xedge;
    res.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return res;
}
Vertex HIntersect(Vertex& v1, Vertex& v2, int yedge)
{
    Vertex res;
    res.y = yedge;
    res.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return res;
}

void PolygonClip(HDC hdc, POINT* p, int n, int xleft, int ytop, int xright, int ybottom, COLORREF color)
{
    VertexList vlist;
    for (int i = 0; i < n; i++)vlist.push_back(Vertex(p[i].x, p[i].y));
    vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);
    Vertex v1 = vlist[vlist.size() - 1];
    for (int i = 0; i < (int)vlist.size(); i++)
    {
        Vertex v2 = vlist[i];
        MoveToEx(hdc, Round(v1.x), Round(v1.y), NULL);
        LineTo(hdc, Round(v2.x), Round(v2.y));
        v1 = v2;
    }
}
////////////////////// End of Clipping ////////////////////

/*--------------------save and load----------------------*/
bool HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel)
{
    uint32_t Width = Area.right - Area.left;
    uint32_t Height = Area.bottom - Area.top;

    BITMAPINFO Info;
    BITMAPFILEHEADER Header;
    memset(&Info, 0, sizeof(Info));
    memset(&Header, 0, sizeof(Header));
    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = BitsPerPixel;
    Info.bmiHeader.biCompression = BI_RGB;
    Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
    Header.bfType = 0x4D42;
    Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    char* Pixels = NULL;
    HDC MemDC = CreateCompatibleDC(Context);
    HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
    DeleteObject(SelectObject(MemDC, Section));
    BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
    DeleteDC(MemDC);

    std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
    if (hFile.is_open())
    {
        hFile.write((char*)&Header, sizeof(Header));
        hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
        hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
        hFile.close();
        DeleteObject(Section);
        return true;
    }

    DeleteObject(Section);
    return false;
}

void LoadWindow(HWND hWnd, HDC& hdc)
{
    string fileName = "picture.bmp";
    if (fileName == "")
        return;
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)::LoadImage(NULL, L"picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC hLocalDC;
    hLocalDC = CreateCompatibleDC(hdc);
    BITMAP qBitmap;
    int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
    BOOL qRetBlit = BitBlt(hdc, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
    SelectObject(hLocalDC, hOldBmp);
    DeleteDC(hLocalDC);
    DeleteObject(hBitmap);
}


HMENU list_;


void AddMenus(HWND hwnd)
{
    list_ = CreateMenu();
    HMENU ListOfColors = CreateMenu();
    HMENU ListOfCircles = CreateMenu();
    HMENU ListOfLines = CreateMenu();
    HMENU ListOfEllipse = CreateMenu();
    HMENU ListOfFillings = CreateMenu();
    HMENU QuarterNo = CreateMenu();
    HMENU ListOfClipping = CreateMenu();
    HMENU Spline_menu = CreateMenu();
    HMENU ListOfTools = CreateMenu();

    AppendMenu(ListOfColors, MF_STRING, 0, L"Orange");
    AppendMenu(ListOfColors, MF_STRING, 1, L"Black");
    AppendMenu(ListOfColors, MF_STRING, 2, L"Yellow");              // colors
    AppendMenu(ListOfColors, MF_STRING, 3, L"Blue");
    AppendMenu(ListOfColors, MF_STRING, 4, L"Green");
    AppendMenu(ListOfColors, MF_STRING, 5, L"Red");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfColors, L"COLOR");

    /////////////////////////////////////
    AppendMenu(ListOfCircles, MF_STRING, 6, L"Direct");
    AppendMenu(ListOfCircles, MF_STRING, 7, L"Polar");
    AppendMenu(ListOfCircles, MF_STRING, 8, L"Iterative Polar");
    AppendMenu(ListOfCircles, MF_STRING, 9, L"MidPoint");                    //circles
    AppendMenu(ListOfCircles, MF_STRING, 10, L" MidPoint Modification");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfCircles, L"CIRCLE");
    /////////////////////////////////////
    AppendMenu(ListOfLines, MF_STRING, 11, L"DDA");
    AppendMenu(ListOfLines, MF_STRING, 12, L"MidPoint");
    AppendMenu(ListOfLines, MF_STRING, 13, L"Parametric");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfLines, L"LINES");
    /////////////////////////////////////

    AppendMenu(ListOfEllipse, MF_STRING, 14, L"Direct");
    AppendMenu(ListOfEllipse, MF_STRING, 15, L"Polar");
    AppendMenu(ListOfEllipse, MF_STRING, 16, L"MidPoint");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfEllipse, L"ELLIPSE");

    AppendMenu(QuarterNo, MF_STRING, 17, L"first quarter");
    AppendMenu(QuarterNo, MF_STRING, 18, L"second quarter");
    AppendMenu(QuarterNo, MF_STRING, 19, L"third quarter");
    AppendMenu(QuarterNo, MF_STRING, 20, L"fourth quarter");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)QuarterNo, L"QUARTERS");



    AppendMenu(ListOfFillings, MF_STRING, 21, L"Filling Circle Quarter with lines");
    AppendMenu(ListOfFillings, MF_STRING, 22, L"Filling Circle Quarter with circles");
    AppendMenu(ListOfFillings, MF_STRING, 23, L"Filling Square with Hermit Curve");
    AppendMenu(ListOfFillings, MF_STRING, 24, L"Filling Rectangle with Bezier Curve");
    AppendMenu(ListOfFillings, MF_STRING, 25, L"recursive flood fill");//flood fill
    AppendMenu(ListOfFillings, MF_STRING, 26, L" Non Recursive flood fill");//flood fill
    AppendMenu(ListOfFillings, MF_STRING, 27, L"Non convex Polygon filling");
    AppendMenu(ListOfFillings, MF_STRING, 28, L"Convex Polygon filling");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfFillings, L"FILLINGS");

    AppendMenu(ListOfClipping, MF_STRING, 29, L"Clipping polygon with ractangle window");
    AppendMenu(ListOfClipping, MF_STRING, 30, L"Clipping line with ractangle window");
    AppendMenu(ListOfClipping, MF_STRING, 31, L"Clipping point with ractangle window");
    AppendMenu(ListOfClipping, MF_STRING, 32, L"Clipping line with square window");
    AppendMenu(ListOfClipping, MF_STRING, 33, L"Clipping point with square window");
    AppendMenu(ListOfClipping, MF_STRING, 34, L"Clipping line with circle window");
    AppendMenu(ListOfClipping, MF_STRING, 35, L"Clipping point with circle window");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfClipping, L"CLIPPING");

    AppendMenu(Spline_menu, MF_STRING, 36, L"spline curve");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)Spline_menu, L"Splines");


    AppendMenu(ListOfTools, MF_STRING, 37, L"Clear");
    AppendMenu(ListOfTools, MF_STRING, 38, L"Save");
    AppendMenu(ListOfTools, MF_STRING, 39, L"Load");

    AppendMenu(list_, MF_POPUP, (UINT_PTR)ListOfTools, L"TOOLS");

    SetMenu(hwnd, list_);


}




COLORREF color = RGB(0, 0, 0);
int number_of_rule, quarter = 1;
int R, A, B, x, x2, x3, y, y2, y3, counter = 0;
int Num_of_Points = 0;
POINT P[5];
Vector8 Pt[4];
bool poly = true;
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    static int index = 0;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        AddMenus(hwnd);
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case  (0):
            color = RGB(255, 160, 0);
            cout << "Orange color is being used" << endl;
            break;
        case  (1):
            color = RGB(0, 0, 0);
            cout << "Black color is being used" << endl;
            break;
        case  (2):
            color = RGB(255, 255, 0);
            cout << "Yellow color is being used" << endl;
            break;
        case  (3):
            color = RGB(0, 0, 255);
            cout << "Blue color is being used" << endl;
            break;
        case  (4):
            color = RGB(0, 115, 0);
            cout << "Green color is being used" << endl;
            break;
        case  (5):
            color = RGB(255, 0, 0);
            cout << "Red color is being used" << endl;
            break;
        case  (6):
            number_of_rule = 6;
            cout << "Drawing circle using Direct Algorithm...." << endl;
            break;
        case  (7):
            number_of_rule = 7;
            cout << "Drawing circle using Polar Algorithm...." << endl;
            break;

        case  (8):
            number_of_rule = 8;
            cout << "Drawing circle using Iterative Polar Algorithm...." << endl;

            break;
        case  (9):
            number_of_rule = 9;
            cout << "Drawing circle using MidPoint Algorithm....." << endl;

            break;
        case  (10):
            number_of_rule = 10;
            cout << "Drawing circle using MidPoint faster Algorithm....." << endl;

            break;
        case  (11):
            number_of_rule = 11;
            cout << "Drawing circle using DDA Algorithm....." << endl;

            break;
        case  (12):
            number_of_rule = 12;
            cout << "Drawing line using midpoint Algorithm....." << endl;

            break;
        case  (13):
            number_of_rule = 13;
            cout << "Drawing line using parametric Algorithm....." << endl;

            break;
        case  (14):
            number_of_rule = 14;
            cout << "Drawing ellipse using direct Algorithm....." << endl;

            break;
        case  (15):
            number_of_rule = 15;
            cout << "Drawing ellipse using polar Algorithm....." << endl;

            break;
        case  (16):
            number_of_rule = 16;
            cout << "Drawing ellipse using midpoint Algorithm....." << endl;

            break;
        case  (17):
            quarter = 1;
            cout << "choose first quarter of a circle....." << endl;

            break;

        case  (18):
            quarter = 2;
            cout << "choose second quarter of a circle....." << endl;

            break;
        case  (19):
            quarter = 3;
            cout << "choose third quarter of a circle....." << endl;

            break;
        case  (20):
            quarter = 4;
            cout << "choose fourth quarter of a circle....." << endl;

            break;
        case  (21):
            number_of_rule = 21;
            cout << "filling quarter with lines....." << endl;
            break;
        case  (22):
            number_of_rule = 22;
            cout << "filling quarter with circles....." << endl;

            break;
        case  (23):
            number_of_rule = 23;
            cout << "filling square with hermite curve....." << endl;

            break;
        case  (24):
            number_of_rule = 24;
            cout << "filling rectangle with bezier curve....." << endl;

            break;
        case  (25):
            number_of_rule = 25;
            cout << "recursive flood filling....." << endl;

            break;
        case  (26):
            number_of_rule = 26;
            cout << "non recursive flood filling....." << endl;

            break;
        case  (27):
            number_of_rule = 27;
            cout << "non convex filling....." << endl;

            break;
        case  (28):
            number_of_rule = 28;
            cout << "convex filling....." << endl;

            break;
        case  (29):
            number_of_rule = 29;
            cout << "clipping polygons in a rectangle window....." << endl;

            break;
        case  (30):
            number_of_rule = 30;
            cout << "clipping lines in a rectangle window....." << endl;

            break;
        case  (31):
            number_of_rule = 31;
            cout << "clipping points in a rectangle window....." << endl;

            break;
        case  (32):
            number_of_rule = 32;
            cout << "clipping lines in a square window....." << endl;

            break;
        case  (33):
            number_of_rule = 33;
            cout << "clipping points in a square window....." << endl;

            break;
        case  (34):
            number_of_rule = 34;
            cout << "clipping line in a circle window....." << endl;

            break;
        case  (35):
            number_of_rule = 35;
            cout << "clipping points in a circle window....." << endl;

            break;
        case  (36):
            number_of_rule = 36;
            cout << "drawing spline....." << endl;

            break;
        case  (37):
            InvalidateRect(hwnd, NULL, TRUE);
            cout << "Window is clear now ...." << endl;

            break;
        case  (38):
            RECT rectangle;
            if (GetWindowRect(hwnd, &rectangle)) {

                rectangle.top += 10;
                rectangle.left += 10;
                HDCToFile("picture.bmp", hdc, rectangle, 24);
                ReleaseDC(hwnd, hdc);
            }
            break;
        case  (39):
            LoadWindow(hwnd, hdc);
            break;
        }
    case WM_LBUTTONDOWN:
        if ((number_of_rule >= 6 && number_of_rule <= 16) || (number_of_rule >= 21 && number_of_rule <= 26)) //  (Direct, Polar, iterative Polar, midpoint and modified Midpoint)
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
        }
        break;

    case WM_RBUTTONDOWN:
        if (number_of_rule >= 14 && number_of_rule <= 16) //ellipse
        {
            if (counter == 0) {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                A = Round(std::sqrt(std::pow(x2 - x, 2.0) + pow(y2 - y, 2.0)));
                counter++;
            }
            else if (counter == 1) {
                x3 = LOWORD(lParam);
                y3 = HIWORD(lParam);
                B = Round(std::sqrt(std::pow(x3 - x, 2.0) + pow(y3 - y, 2.0)));
                if (number_of_rule == 14)
                    DrawEllipseCartesian(hdc, x, y, A, B, color);
                else if (number_of_rule == 15)
                    DrawEllipsePolar(hdc, x, y, A, B, color);
                else
                    DrawEllipseBresenham(hdc, x, y, A, B, color);
                counter = 0;
            }
        }
        if (number_of_rule == 11)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            SimpleDDA(hdc, x, y, x2, y2, color);
        }
        if (number_of_rule == 12)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            DrawLineBresenham(hdc, x, y, x2, y2, color);
        }
        if (number_of_rule == 13)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            DrawLineParametric(hdc, x, y, x2, y2, color);
        }
        if (number_of_rule == 6) {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            x2 = (x2 - x) * (x2 - x);
            y2 = (y2 - y) * (y2 - y);
            R = sqrt(x2 + y2);

            CircleDirect(hdc, x, y, R, color);
        }
        if (number_of_rule == 7)//circleiter
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            x2 = (x2 - x) * (x2 - x);
            y2 = (y2 - y) * (y2 - y);
            R = sqrt(x2 + y2);
            CirclePolar(hdc, x, y, R, color);

        }
        if (number_of_rule == 8)//circleitrativepolar
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            x2 = (x2 - x) * (x2 - x);
            y2 = (y2 - y) * (y2 - y);
            R = sqrt(x2 + y2);
            CircleIterativePolar(hdc, x, y, R, color);

        }
        if (number_of_rule == 9)//circleBresenham
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            x2 = (x2 - x) * (x2 - x);
            y2 = (y2 - y) * (y2 - y);
            R = sqrt(x2 + y2);
            CircleBresenham(hdc, x, y, R, color);
        }
        if (number_of_rule == 10)// circleFasterVresenhamfaster
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            x2 = (x2 - x) * (x2 - x);
            y2 = (y2 - y) * (y2 - y);
            R = sqrt(x2 + y2);
            CircleFasterBresenham(hdc, x, y, R, color);
        }
        if (number_of_rule == 21 || number_of_rule == 22)// circle with quarter
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            x2 = (x2 - x) * (x2 - x);
            y2 = (y2 - y) * (y2 - y);
            R = sqrt(x2 + y2);
            if (number_of_rule == 21)
                DrawCircleAndFillItWithLines(hdc, x, y, R, color, quarter);
            else
                DrawCircleAndFillItWithCircles(hdc, x, y, R, color, quarter);
        }
        if (number_of_rule == 23)
        {
            x2 = LOWORD(lParam) - x;
            y2 = HIWORD(lParam) - y;
            R = sqrt(x2 * x2 + y2 * y2);
            DrawSquare(hdc, x, y, R, color);
        }
        if (number_of_rule == 24)
        {
            x2 = LOWORD(lParam) - x;
            y2 = HIWORD(lParam) - y;
            DrawRec(hdc, x, y, x2, y2, color);
        }
        if (number_of_rule == 25)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            RecursiveFloodFill(hdc, x2, y2, color, RGB(255, 0, 0));
        }
        if (number_of_rule == 26)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            NonRecursiveFloodFill(hdc, x2, y2, color, RGB(255, 0, 0));
        }
        else if (number_of_rule == 27 || number_of_rule == 28)
        {
            if (Num_of_Points == 0)
            {
                P[0].x = LOWORD(lParam);
                P[0].y = HIWORD(lParam);
                Num_of_Points++;
            }
            else if (Num_of_Points == 1)
            {
                P[1].x = LOWORD(lParam);
                P[1].y = HIWORD(lParam);
                Num_of_Points++;
            }
            else if (Num_of_Points == 2)
            {
                P[2].x = LOWORD(lParam);
                P[2].y = HIWORD(lParam);
                Num_of_Points++;
            }
            else if (Num_of_Points == 3)
            {
                P[3].x = LOWORD(lParam);
                P[3].y = HIWORD(lParam);
                Num_of_Points++;
            }
            else if (Num_of_Points == 4)
            {
                P[4].x = LOWORD(lParam);
                P[4].y = HIWORD(lParam);
                Num_of_Points++;
                //change pen color//
                SelectObject(hdc, GetStockObject(DC_PEN));
                SetDCPenColor(hdc, color);
                Polygon(hdc, P, 5);
            }
            else if (Num_of_Points == 5)
            {
                //fill polygon
                if (number_of_rule == 27)
                    fillPolygon(hdc, P, 5, color);
                else
                    FillConvexPolygon(hdc, P, 5, color);
                Num_of_Points = 0;
            }
        }
        else if (number_of_rule == 29) //rectangle window
        {
            if (ct == 0)
            {
                // code for start point of rectangular
                X_left = LOWORD(lParam);
                Y_top = HIWORD(lParam);
                add_point(X_left, Y_top);
                ct++;
            }
            else if (ct == 1)
            {
                // code for end point of rectangular
                X_right = LOWORD(lParam);
                Y_bottom = HIWORD(lParam);
                add_point(X_right, Y_bottom);
                Rectangle(hdc, X_left, Y_top, X_right, Y_bottom);
                add_shape(clipping, color);
                ct++;
            }
            else {
                P[ct - 2].x = LOWORD(lParam);
                P[ct - 2].y = HIWORD(lParam);
                if (ct == 6)
                {
                    PolygonClip(hdc, P, 5, X_left, Y_top, X_right, Y_bottom, color);
                    ct = 0;
                    poly = false;
                }
                else ct++;
            }
        }
        else if (number_of_rule == 30)
        {
            if (ct == 0)
            {
                // code for start point of rectangular
                X_left = LOWORD(lParam);
                Y_top = HIWORD(lParam);
                add_point(X_left, Y_top);
                ct++;
            }
            else if (ct == 1)
            {
                // code for end point of rectangular
                X_right = LOWORD(lParam);
                Y_bottom = HIWORD(lParam);
                add_point(X_right, Y_bottom);
                Rectangle(hdc, X_left, Y_top, X_right, Y_bottom);
                add_shape(clipping, RGB(0, 0, 0));
                ct++;

            }
            else if (ct == 2)
            {
                // code for start point of lines
                X_start = LOWORD(lParam);
                Y_start = HIWORD(lParam);
                add_point(X_start, Y_start);
                ct++;

            }
            else if (ct == 3)
            {
                // code for end point of lines
                X_end = LOWORD(lParam);
                Y_end = HIWORD(lParam);
                add_point(X_end, Y_end);
                lineClippping(hdc, X_start, Y_start, X_end, Y_end, X_left, Y_top, X_right, Y_bottom, color);
                // resets by default when changing the algorithm (many lines)
                add_shape(drawCline, color);
                ct = 0;

            }
        }
        else if (number_of_rule == 31)
        {
            if (ct == 0)
            {
                // code for start point of rectangular
                X_left = LOWORD(lParam);
                Y_top = HIWORD(lParam);
                add_point(X_left, Y_top);
                ct++;
            }
            else if (ct == 1)
            {
                // code for end point of rectangular
                X_right = LOWORD(lParam);
                Y_bottom = HIWORD(lParam);
                add_point(X_right, Y_bottom);
                Rectangle(hdc, X_left, Y_top, X_right, Y_bottom);
                add_shape(clipping, color);
                ct++;
            }
            else if (ct == 2)
            {
                // code for points
                x_1 = LOWORD(lParam);
                y_1 = HIWORD(lParam);
                add_point(x_1, y_1);
                pointClippping(hdc, x_1, y_1, X_left, Y_top, X_right, Y_bottom, color);
                add_shape(drawCPt, color);
                ct = 0;
                // resets by default when changing the clippingorithm (many points)
            }
        }
        else if (number_of_rule == 32)
        {
            if (ct == 0)
            {
                // code for start point of square
                X_left = LOWORD(lParam);
                Y_top = HIWORD(lParam);
                add_point(X_left, Y_top);
                ct++;
            }
            else if (ct == 1)
            {
                // code for end point of square
                X_right = LOWORD(lParam) + 100;
                Y_bottom = HIWORD(lParam) + 100;
                add_point(X_right, Y_bottom);
                Square(hdc, X_left, Y_top, X_right, Y_bottom);
                add_shape(clipping, color);
                ct++;

            }
            else if (ct == 2)
            {
                // code for start point of lines
                X_start = LOWORD(lParam);
                Y_start = HIWORD(lParam);
                add_point(X_start, Y_start);
                ct++;

            }
            else if (ct == 3)
            {
                // code for end point of lines
                X_end = LOWORD(lParam);
                Y_end = HIWORD(lParam);
                add_point(X_end, Y_end);
                lineClippping(hdc, X_start, Y_start, X_end, Y_end, X_left, Y_top, X_right, Y_bottom, color);
                // resets by default when changing the algorithm (many lines)
                add_shape(drawCline, color);
                ct = 0;

            }
        }
        else if (number_of_rule == 33)
        {
            if (ct == 0)
            {
                // code for start point of rectangular
                X_left = LOWORD(lParam);
                Y_top = HIWORD(lParam);
                add_point(X_left, Y_top);
                ct++;
            }
            else if (ct == 1)
            {
                // code for end point of square
                X_right = LOWORD(lParam) + 100;
                Y_bottom = HIWORD(lParam) + 100;
                add_point(X_right, Y_bottom);
                Square(hdc, X_left, Y_top, X_right, Y_bottom);
                add_shape(clipping, color);
                ct++;
            }
            else if (ct == 2)
            {
                // code for points
                x_1 = LOWORD(lParam);
                y_1 = HIWORD(lParam);
                add_point(x_1, y_1);
                pointClippping(hdc, x_1, y_1, X_left, Y_top, X_right, Y_bottom, color);
                add_shape(drawCPt, color);
                ct = 0;
                // resets by default when changing the clippingorithm (many points)
            }
        }
        else if (number_of_rule == 34)
        {
            if (ct == 0)
            {
                x_c = LOWORD(lParam);
                y_c = HIWORD(lParam);
                add_point(x_c, y_c);
                ct++;
            }

            else if (ct == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                add_point(x2, y2);
                rad = sqrt(pow((x2 - x_c), 2) + pow((y2 - y_c), 2));
                myCircle(hdc, x_c, y_c, rad);
                add_shape(clipping, color);
                ct++;
            }
            else if (ct == 2)
            {
                // code for start point of lines
                X_start = LOWORD(lParam);
                Y_start = HIWORD(lParam);
                add_point(X_start, Y_start);
                ct++;
            }
            else if (ct == 3)
            {
                // code for end point of lines
                X_end = LOWORD(lParam);
                Y_end = HIWORD(lParam);
                add_point(X_end, Y_end);
                DrawlineCircleClipping(hdc, X_start, Y_start, X_end, Y_end, color, x_c, y_c, rad);
                // resets by default when changing the algorithm (many lines)
                add_shape(drawCline, color);
                ct = 0;
            }
        }
        else if (number_of_rule == 35)
        {
            if (ct == 0)
            {
                x_c = LOWORD(lParam);
                y_c = HIWORD(lParam);
                add_point(x_c, y_c);
                ct++;
            }

            else if (ct == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                add_point(x2, y2);
                rad = sqrt(pow((x2 - x_c), 2) + pow((y2 - y_c), 2));
                myCircle(hdc, x_c, y_c, rad);
                add_shape(clipping, color);
                ct++;
            }
            else if (ct == 2)
            {
                // code for points
                x_1 = LOWORD(lParam);
                y_1 = HIWORD(lParam);
                add_point(x_1, y_1);
                DrawPointCircleClipping(hdc, x_1, y_1, color, x_c, y_c, rad);
                add_shape(drawCPt, color);
                ct = 0;
            }

        }
        else if (number_of_rule == 36)
        {
            Pt[index] = Vector8(LOWORD(lParam), HIWORD(lParam));
            if (index == 3) {
                hdc = GetDC(hwnd);
                DrawCardinalSpline(hdc, Pt, 4, 0.5, RGB(255, 0, 0));
                ReleaseDC(hwnd, hdc);
                swap(Pt[3], Pt[0]);
                index = 1;
            }
            else index++;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}