#pragma once
#include "const.h"

// Quitar acentos para std::wstring
std::wstring quitarAcentos(const std::wstring& s);

// Preprocessar text: eliminar símbols, accents, convertir a majúscules
std::wstring preprocessarTexto(const std::wstring& texto);

// Agrupar en grups de 5 lletres
std::wstring agruparEnCinco(const std::wstring& texto);