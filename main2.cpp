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
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

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
void MidpointLine(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color)
{
    int dx = xe - xs;
    int dy = ye - ys;
    if (abs(dx) >= abs(dy))
    {
        if (xs > xe)swap(xs, ys, xe, ye);
        int x = xs;
        int y = ys;
        int d = dx - 2 * dy;
        int d1 = 2 * dx - 2 * dy;
        int d2 = -2 * dy;
        while (x < xe)
        {
            if (d <= 0)
            {
                y++;
                x++;
                d += d1;
            }
            else
            {
                x++;
                d += d2;
            }
            SetPixel(hdc, x, y, RGB(0, 100, 255));
        }
    }
    else
    {
        if (ys > ye)swap(xs, ys, xe, ye);
        int x = xs;
        int y = ys;
        int d = 2 * dx - dy;
        int d1 = 2 * dx - 2 * dy;
        int d2 = 2 * dx;
        while (y < ye) {

            if (d <= 0) {
                x++;
                y++;
                d += d1;
            }
            else {
                y++;
                d += d2;
            }
            SetPixel(hdc, x, y, RGB(0, 100, 255));
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
void Draw2Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color, int quarter)
{
    if (quarter == 4)
    {
        SetPixel(hdc, xc + b, yc + a, RGB(0, 0, 0)); // 4
        SetPixel(hdc, xc + a, yc + b, RGB(0, 0, 0));
    }
    else if (quarter == 3)
    {
        SetPixel(hdc, xc - a, yc + b, RGB(0, 0, 0)); // 3
        SetPixel(hdc, xc - b, yc + a, RGB(0, 0, 0));
    } // 3
    else if (quarter == 2)
    {
        SetPixel(hdc, xc - a, yc - b, RGB(0, 0, 0)); // 2
        SetPixel(hdc, xc - b, yc - a, RGB(0, 0, 0));
    } // 2
    else if (quarter == 1)
    {
        SetPixel(hdc, xc + a, yc - b, RGB(0, 0, 0)); // 1
        SetPixel(hdc, xc + b, yc - a, RGB(0, 0, 0));
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
void DrawEllipseIterativePolar(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{
    double x = A, y = 0, dtheta = 1.0 / max(A, B), cos_dtheta = cos(dtheta), sin_dtheta = sin(dtheta);
    Draw4Points(hdc, xc, yc, x, y, color);
    while (x > y)
    {
        double x1 = x * cos_dtheta - ((double)A / B) * y * sin_dtheta;
        y = y * cos_dtheta + ((double)B / A) * x * sin_dtheta;
        x = x1;
        Draw4Points(hdc, xc, yc, Round(x), Round(y), color);
    }
    while (x < y)
    {
        double x1 = x * cos_dtheta - ((double)A / B) * y * sin_dtheta;
        y = y * cos_dtheta + ((double)B / A) * x * sin_dtheta;
        x = x1;
        Draw4Points(hdc, xc, yc, Round(x), Round(y), color);
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

void DrawHermiteCurve(HDC hdc, Vector2& P0, Vector2& T0, Vector2& P1, Vector2& T1, int
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

void DrawCardinalSpline(HDC hdc, Vector2 P[], int n, double c, int numpix)
{
    double c1 = 1 - c;
    Vector2 T0(c1 * (P[2].x - P[0].x), c1 * (P[2].y - P[0].y));
    for (int i = 2; i < n - 1; i++)
    {
        Vector2 T1(c1 * (P[i + 1].x - P[i - 1].x), c1 * (P[i + 1].y - P[i - 1].y));
        DrawHermiteCurve(hdc, P[i - 1], T0, P[i], T1, numpix);
        T0 = T1;
    }
}
void drawBezierCurve(HDC hdc, int x1, int y1, int x2, int y2, int u1, int u2, int u3, int u4, COLORREF c, int cx, int cy, int RR2)
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
        if (x >= cx && x <= (cx + RR2) && y >= cy && y <= (cy + RR2)) {
            SetPixel(hdc, Round(x), Round(y), c);
        }


    }
}
void drawbetzer(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color, int cx, int cy, int RR) {
    int dx = xe - xs;
    int dy = ye - ys;
    int xa = xs + RR;
    int t1 = 50, t2 = 60, t3 = 30, t4 = 60;
    drawBezierCurve(hdc, xs, ys, xa, ys, t1, t2, t3, t4, color, cx, cy, RR);
    if (abs(dx) >= abs(dy))
    {
        int x = xs, xinc = dx > 0 ? 1 : -1;
        double y = ys, yinc = (double)dy / dx * xinc;
        while (x != xe)
        {
            x += xinc;
            y += yinc;

            xa = x + RR;

            drawBezierCurve(hdc, xs, round(y), xa, round(y), t1, t2, t3, t4, color, cx, cy, RR);
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
            xa = round(x) + RR;
            //drawbetzercurve( hdc, round(x), y,xa,y,color, cx, cy , RR );
            drawBezierCurve(hdc, round(x), y, xa, y, t1, t2, t3, t4, color, cx, cy, RR);
        }
    }
}
void DrawRec(HDC hdc, int xc, int yc, int dist, int dist1, COLORREF c)
{
    int x1, y1;

    x1 = xc + dist;
    y1 = yc + dist1;
    DrawLine1(hdc, xc, yc, x1, yc, c);
    drawbetzer(hdc, xc, yc, xc, y1, c, xc, yc, dist);

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
    DrawHermiteCurve(hdc, xs, ys, xs, yy, color, cx, cy, RR);
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
            DrawHermiteCurve(hdc, x, round(y), x, yy, color, cx, cy, RR);
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

void UpdateEdgeToTable(Point p1, Point p2, edgeTable table)
{

    if (p1.y == p2.y)
        return;
    if (p1.y > p2.y)
        swap(p1.x, p1.y, p2.x, p2.y);
    int slopeInverse = (p2.x - p1.x) / (double)(p2.y - p1.y);
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

void PolygonToTable(Point PolygonPoints[], int n, edgeTable table)
{
    Point p1 = PolygonPoints[n - 1];
    for (int i = 0; i < n; i++)
    {
        Point p2 = PolygonPoints[i];
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

void FillConvexPolygon(HDC hdc, Point PolygonPoints[], int n, COLORREF color)
{
    edgeTable table;
    Initialize(table);
    PolygonToTable(PolygonPoints, n, table);
    TableToScreen(hdc, table, color);
}
//nonConvix//
struct Edgerec {
    double x, ymax, minv;
    Edgerec(double x = 0.0, double ymax = 0.0, double minv = 0.0) :x(x), ymax(ymax), minv(minv) {}
};
typedef list<Edgerec> EdgeTable[800];
void scanEdge(POINT v1, POINT v2, EdgeTable tbl) {
    if (v1.y == v2.y) return;
    if (v1.y > v2.y) swap(v1, v2);
    Edgerec rec(v1.x, v2.y, (double)(v2.x - v1.x) / (v2.y - v1.y));
    tbl[v1.y].push_back(rec);
}

void polygon2table(POINT p[], int n, EdgeTable tbl) {
    POINT v1 = p[n - 1];
    for (int i = 0; i < n; i++) {
        POINT v2 = p[i];
        scanEdge(v1, v2, tbl);
        v1 = v2;
    }
}
void table2screen(HDC hdc, EdgeTable tbl, COLORREF c) {
    int y = 0;


    list<Edgerec>::iterator it;

    while (tbl[y].size() == 0) y++;
    list<Edgerec> activeList = tbl[y];
    while (activeList.size() != 0) {

        activeList.sort([](Edgerec& a, Edgerec& b) {return a.x < b.x; });

        for (it = activeList.begin(); it != activeList.end(); it++) {
            Edgerec& node1 = *it;
            it++;
            if (it == activeList.end()) break;
            Edgerec& node2 = *it;
            DrawLine1(hdc, ceil(node1.x), y, floor(node2.x), y, c);
        }

        y++;

        for (it = activeList.begin(); it != activeList.end();) {
            if (it->ymax == y) {
                it = activeList.erase(it);
            }
            else it++;
        }

        for (it = activeList.begin(); it != activeList.end(); it++) {
            it->x = it->x + it->minv;
        }

        if (tbl[y].size() != 0) {
            activeList.splice(activeList.end(), tbl[y]);
        }
    }
}

void fillPolygon(HDC hdc, POINT p[], int n, COLORREF c)
{
    EdgeTable tbl;

    polygon2table(p, n, tbl);
    table2screen(hdc, tbl, c);

}
void SwapPoints(POINT& v1, POINT& v2)
{
    POINT tmp = v1;
    v1 = v2;
    v2 = tmp;
}


HMENU list_;


void AddMenus(HWND hwnd)
{
    list_ = CreateMenu();
    HMENU color_list = CreateMenu();
    HMENU circle_list = CreateMenu();
    HMENU line_list = CreateMenu();
    HMENU Ellipse_list = CreateMenu();
    HMENU Filling_list = CreateMenu();
    HMENU Quarter_list = CreateMenu();
    HMENU clipping_list = CreateMenu();
    HMENU Clear_list = CreateMenu();

    AppendMenu(color_list, MF_STRING, 0, L"RED");
    AppendMenu(color_list, MF_STRING, 1, L"Green");
    AppendMenu(color_list, MF_STRING, 2, L"Blue");              // colors
    AppendMenu(color_list, MF_STRING, 3, L"Yellow");
    AppendMenu(color_list, MF_STRING, 4, L"Black");
    AppendMenu(color_list, MF_STRING, 5, L"Orange");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)color_list, L"Color");

    /////////////////////////////////////
    AppendMenu(circle_list, MF_STRING, 6, L"Direct");
    AppendMenu(circle_list, MF_STRING, 7, L"Polar");
    AppendMenu(circle_list, MF_STRING, 8, L"Iterative Polar");
    AppendMenu(circle_list, MF_STRING, 9, L"MidPoint");                    //circles
    AppendMenu(circle_list, MF_STRING, 10, L" MidPoint Modification");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)circle_list, L"Circle");
    /////////////////////////////////////
    AppendMenu(line_list, MF_STRING, 11, L"DDA");
    AppendMenu(line_list, MF_STRING, 12, L"MidPoint");
    AppendMenu(line_list, MF_STRING, 13, L"Parametric");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)line_list, L"Lines");
    /////////////////////////////////////

    AppendMenu(Ellipse_list, MF_STRING, 14, L"Direct");
    AppendMenu(Ellipse_list, MF_STRING, 15, L"Polar");
    AppendMenu(Ellipse_list, MF_STRING, 16, L"MidPoint");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)Ellipse_list, L"Ellipse");

    AppendMenu(Quarter_list, MF_STRING, 17, L"1");
    AppendMenu(Quarter_list, MF_STRING, 18, L"2");
    AppendMenu(Quarter_list, MF_STRING, 19, L"3");
    AppendMenu(Quarter_list, MF_STRING, 20, L"4");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)Quarter_list, L"Quarters");


    AppendMenu(Filling_list, MF_STRING, 21, L"Filling quarter with lines");
    AppendMenu(Filling_list, MF_STRING, 22, L"Filling quarter with circles");
    AppendMenu(Filling_list, MF_STRING, 23, L"Filling Square with Hermit Curve");
    AppendMenu(Filling_list, MF_STRING, 24, L"Filling Rectangle with Bezier Curve");
    AppendMenu(Filling_list, MF_STRING, 25, L"flood fill - recursive");//flood fill
    AppendMenu(Filling_list, MF_STRING, 26, L"flood fill - non recursive");//flood fill
    AppendMenu(Filling_list, MF_STRING, 27, L"Filling General Polygon");
    AppendMenu(Filling_list, MF_STRING, 28, L"Filling Convex Polygon");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)Filling_list, L"Fillings");

    AppendMenu(clipping_list, MF_STRING, 29, L"Clipping polygon with ractangle window");
    AppendMenu(clipping_list, MF_STRING, 30, L"Clipping line with ractangle window");
    AppendMenu(clipping_list, MF_STRING, 31, L"Clipping point with ractangle window");
    AppendMenu(clipping_list, MF_STRING, 32, L"Clipping line with square window");
    AppendMenu(clipping_list, MF_STRING, 33, L"Clipping point with square window");
    AppendMenu(list_, MF_POPUP, (UINT_PTR)clipping_list, L"clipping");




    AppendMenu(Clear_list, MF_STRING, 34, L"Clear");
    AppendMenu(Clear_list, MF_STRING, 35, L"Save");
    AppendMenu(Clear_list, MF_STRING, 36, L"Load");

    AppendMenu(list_, MF_POPUP, (UINT_PTR)Clear_list, L"Clear");

    SetMenu(hwnd, list_);


}




COLORREF color = RGB(0, 0, 0);
int case_number;
int A, B, x, x2, x3, y, y2, y3, counter = 0;
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
            color = RGB(255, 0, 0);
            cout << "You are use Red color " << endl;
            break;
        case  (1):
            color = RGB(0, 110, 0);
            cout << "You are use Green color" << endl;
            break;
        case  (2):
            color = RGB(0, 0, 255);
            cout << "You are use Blue color" << endl;
            break;
        case  (3):
            color = RGB(255, 255, 0);
            cout << "You are use Yellow color" << endl;
            break;
        case  (4):
            color = RGB(0, 0, 0);
            cout << "You are use Black color" << endl;
            break;

        case  (5):
            color = RGB(255, 165, 0);
            cout << "You are use Orange color" << endl;
            break;

        case  (6):
            case_number = 6;
            cout << "You can Draw circle using Direct Algorithm...." << endl;
            break;
        case  (7):
            case_number = 7;
            cout << "You can Draw circle using Polar Algorithm...." << endl;
            break;

        case  (8):
            case_number = 8;
            cout << "You can Draw circle using Iterative Polar Algorithm...." << endl;

            break;
        case  (9):
            case_number = 9;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (10):
            case_number = 10;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (11):
            case_number = 11;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (12):
            case_number = 12;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (13):
            case_number = 13;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (14):
            case_number = 14;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (15):
            case_number = 15;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (16):
            case_number = 16;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (17):
            case_number = 17;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;

        case  (18):
            case_number = 18;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (19):
            case_number = 19;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (20):
            case_number = 20;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (21):
            case_number = 21;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (22):
            case_number = 22;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (23):
            case_number = 23;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (24):
            case_number = 24;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (25):
            case_number = 25;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (26):
            case_number = 26;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (27):
            case_number = 27;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (28):
            case_number = 28;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (29):
            case_number = 29;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (30):
            case_number = 30;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (31):
            case_number = 31;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (32):
            case_number = 32;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (33):
            case_number = 33;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (34):
            case_number = 34;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (35):
            case_number = 35;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (36):
            case_number = 36;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        }
    case WM_LBUTTONDOWN:
        if (case_number >= 6 && case_number <= 16 || (case_number >= 21 && case_number <= 26)) //  (Direct, Polar, iterative Polar, midpoint and modified Midpoint)
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
        }
        break;

    case WM_RBUTTONDOWN:
        if (case_number >= 14 && case_number <= 16) //ellipse
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
                if (case_number == 14)
                    DrawEllipseCartesian(hdc, x, y, A, B, color);
                else if (case_number == 15)
                    DrawEllipsePolar(hdc, x, y, A, B, color);
                //else
                    //TODO: midpoint 
                counter = 0;
            }
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