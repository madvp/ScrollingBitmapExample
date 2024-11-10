#pragma once
#include "resource.h"
#include <windows.h>

// Declare bitmap functions
void InitBitmap(HWND hwnd);
void UpdateBitmapData();
void PaintBitmap(HWND hwnd, HDC hdc);

// Declare global variables as extern to share across files
extern HBITMAP hBitmap;
extern HDC hdcMem;    // Memory device context for drawing
extern RECT dirtyRect;
