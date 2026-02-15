#pragma once

// Xifrar una lletra a través d'un rotor (endavant)
wchar_t xifrarRotorEndavant(wchar_t lletra, const std::wstring& rotor, int posicio);

// Xifrar un caràcter complet passant pels 3 rotors
wchar_t xifrarCaracter(wchar_t lletra);

// Xifrar text complet
std::wstring xifrarTexto(const std::wstring& texto);

void xifrarMissatge();