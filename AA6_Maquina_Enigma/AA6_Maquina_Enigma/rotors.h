#pragma once
#include <string>


// DECLARACIONS amb extern
extern std::wstring r1;
extern wchar_t notchR1;

extern std::wstring r2;
extern wchar_t notchR2;

extern std::wstring r3;
extern wchar_t notchR3;

extern int posR1, posR2, posR3;

// Funcions
void avanzarRotores();
void establecerPosiciones(wchar_t p1, wchar_t p2, wchar_t p3);
void editarRotors();