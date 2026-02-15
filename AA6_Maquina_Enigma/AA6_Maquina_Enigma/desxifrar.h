#pragma once
// Desxifrar una lletra a través d'un rotor (enrere)
wchar_t xifrarRotorEnrere(wchar_t lletra, const std::wstring& rotor, int posicio);

// Desxifrar un caràcter passant pels 3 rotors en ordre invers
wchar_t desxifrarCaracter(wchar_t lletra);

// Desxifrar text complet
std::wstring desxifrarTexto(const std::wstring& texto);

void desxifrarMissatge();