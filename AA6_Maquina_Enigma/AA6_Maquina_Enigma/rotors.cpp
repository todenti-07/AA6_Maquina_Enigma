#include "const.h"
#include <cwctype>

// Definicions globals (una sola vegada)
std::wstring r1 = L"EKMFLGDQVZNTOWYHXUSPAIBRCJ";  // Rotor I
wchar_t notchR1 = L'Q';

std::wstring r2 = L"AJDKSIRUXBLHWTMCQGZNPYFVOE";  // Rotor II
wchar_t notchR2 = L'E';

std::wstring r3 = L"BDFHJLCPRTXVZNYEIWGAKMUSQO";  // Rotor III
wchar_t notchR3 = L'V';

int posR1 = 0, posR2 = 0, posR3 = 0;

// Establir posicions inicials dels rotors
void establecerPosiciones(wchar_t p1, wchar_t p2, wchar_t p3) {
    posR1 = std::toupper(p1) - L'A'; // Convertir a índex (0-25)
    posR2 = std::toupper(p2) - L'A'; // Convertir a índex (0-25)
    posR3 = std::toupper(p3) - L'A'; // Convertir a índex (0-25)

    // Assegurar que estan en el rang 0-25
    if (posR1 < 0 || posR1 > 25) posR1 = 0;
    if (posR2 < 0 || posR2 > 25) posR2 = 0;
    if (posR3 < 0 || posR3 > 25) posR3 = 0;
}

// Avançar els rotors segons la lògica ENIGMA
void avanzarRotores() {
    // Double-stepping: si rotor 2 està al notch
    bool r2EnNotch = (L'A' + posR2 == notchR2);

    if (r2EnNotch) {
        posR2 = (posR2 + 1) % 26;
        posR3 = (posR3 + 1) % 26;
    }

    // Sempre avançar rotor 1
    bool r1LlegaAlNotch = (L'A' + posR1 == notchR1);
    posR1 = (posR1 + 1) % 26;

    // Si rotor 1 arriba al notch, avança rotor 2
    if (r1LlegaAlNotch && !r2EnNotch) {
        bool r2LlegaAlNotch = (L'A' + posR2 == notchR2);
        posR2 = (posR2 + 1) % 26;

        // Si rotor 2 arriba al notch, avança rotor 3
        if (r2LlegaAlNotch) {
            posR3 = (posR3 + 1) % 26;
        }
    }
}

void editarRotors() {
    std::wcout << L"\n--- EDITAR ROTORS ---" << std::endl;
    std::wcout << L"Quin rotor vols editar? (1-3): "; // Demanar número de rotor
    int num;
    std::wcin >> num;
    std::wcin.ignore(10000, L'\n');

    if (num < 1 || num > 3) { // Validar número de rotor
        std::wcout << L"[ERROR] Número de rotor invàlid." << std::endl;
        return;
    }

    std::wcout << L"\nIntrodueix el nou cablejat (26 lletres úniques A-Z): ";
    std::wstring nouCablejat;
    std::getline(std::wcin, nouCablejat);

    nouCablejat = preprocessarTexto(nouCablejat); // Eliminar espais, accents i convertir a majúscules

    // Validar
    if (nouCablejat.length() != 26) { // Comprovar longitud
        std::wcout << L"[ERROR] El cablejat ha de tenir exactament 26 lletres." << std::endl;
        return;
    }

    // Verificar que no hi hagi lletres repetides
    bool trobades[26] = { false }; // Per marcar quines lletres s'han trobat
    for (wchar_t c : nouCablejat) {
        if (c < L'A' || c > L'Z') { // Caràcter no vàlid
            std::wcout << L"[ERROR] El cablejat només pot contenir lletres A-Z." << std::endl;
            return;
        }
        int idx = c - L'A';
        if (trobades[idx]) { // Ja s'ha trobat aquesta lletra abans
            std::wcout << L"[ERROR] Hi ha lletres repetides al cablejat." << std::endl;
            return;
        }
        trobades[idx] = true;
    }

    std::wcout << L"Introdueix la lletra notch (A-Z, per defecte Z): ";
    std::wstring notchStr;
    std::getline(std::wcin, notchStr);

    wchar_t notch = L'Z';
    if (!notchStr.empty()) { // Si s'ha introduït una lletra, validar-la
        notch = std::toupper(notchStr[0]);
        if (notch < L'A' || notch > L'Z') {
            notch = L'Z';
        }
    }

    // Actualitzar rotor
    if (num == 1) {
        r1 = nouCablejat;
        notchR1 = notch;
    }
    else if (num == 2) {
        r2 = nouCablejat;
        notchR2 = notch;
    }
    else {
        r3 = nouCablejat;
        notchR3 = notch;
    }

    std::wcout << L"[OK] Rotor " << num << L" actualitzat!" << std::endl;
    std::wcout << L"     Cablejat: " << nouCablejat << std::endl;
    std::wcout << L"     Notch: " << notch << std::endl;
}