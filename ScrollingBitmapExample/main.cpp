#include <windows.h>
#include "ScrollingBitmapExample.h"

HBITMAP hBitmap = NULL;
HDC hdcMem = NULL;
const int WIDTH = 256;
const int HEIGHT = 300;
RECT dirtyRect = { 0, 0, WIDTH, HEIGHT };

// Initialize bitmap and memory DC
void InitBitmap(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    hdcMem = CreateCompatibleDC(hdc);

    hBitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
    SelectObject(hdcMem, hBitmap);
    ReleaseDC(hwnd, hdc);

    if (!hBitmap) {
        MessageBox(hwnd, L"Failed to create bitmap!", L"Error", MB_OK);
    }
}

// Shift all rows up by one and draw new data at the bottom using SetPixel
void UpdateBitmapData() {
    // Scroll the bitmap by moving pixels up
    BitBlt(hdcMem, 0, 0, WIDTH, HEIGHT - 1, hdcMem, 0, 1, SRCCOPY);

    // Draw new row at the bottom using SetPixel
    for (int x = 0; x < WIDTH; ++x) {
        COLORREF color = RGB(rand() % 256, (rand() - 1) % 256, ((rand() + HEIGHT - 1) / 2) % 256);
        SetPixel(hdcMem, x, HEIGHT - 1, color);
    }

    // Set the modified area (the entire bitmap)
    dirtyRect.left = 0;
    dirtyRect.right = WIDTH;
    dirtyRect.top = 0;
    dirtyRect.bottom = HEIGHT;
}

// Draw using BitBlt from the memory device context
void PaintBitmap(HWND hwnd, HDC hdc) {
    BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0, SRCCOPY);
}
