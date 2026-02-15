#include "const.h"

// Xifrar una lletra a través d'un rotor (endavant)
wchar_t xifrarRotorEndavant(wchar_t lletra, const std::wstring& rotor, int posicio) {
    if (lletra < L'A' || lletra > L'Z') return lletra;

    // Ajustar per la posició del rotor
    int index = (lletra - L'A' + posicio) % 26;
    wchar_t sortida = rotor[index];

    // Ajustar sortida per la posició
    sortida = (sortida - L'A' - posicio + 26) % 26 + L'A';

    return sortida;
}

// Xifrar un caràcter complet passant pels 3 rotors
wchar_t xifrarCaracter(wchar_t lletra) {
    if (lletra < L'A' || lletra > L'Z') return lletra;

    // Avançar rotors ABANS de xifrar
    avanzarRotores();

    // Passar pels rotors: R1 -> R2 -> R3
    wchar_t resultat = lletra;
    resultat = xifrarRotorEndavant(resultat, r1, posR1);
    resultat = xifrarRotorEndavant(resultat, r2, posR2);
    resultat = xifrarRotorEndavant(resultat, r3, posR3);

    return resultat;
}

// Xifrar text complet
std::wstring xifrarTexto(const std::wstring& texto) {
    std::wstring xifrat;
    for (wchar_t c : texto) {
        if (c >= L'A' && c <= L'Z') {
            xifrat.push_back(xifrarCaracter(c));
        }
    }
    return xifrat;
}

void xifrarMissatge() {
    std::wcout << L"\n=== XIFRAR MISSATGE ===" << std::endl;

    // Demanar posicions inicials
    std::wcout << L"Introdueix 3 lletres per les posicions inicials (ex: A B C): ";
    wchar_t p1, p2, p3;
    std::wcin >> p1 >> p2 >> p3;
    std::wcin.ignore(10000, L'\n');

    establecerPosiciones(p1, p2, p3);
    std::wcout << L"[OK] Posicions establertes: " << p1 << L" " << p2 << L" " << p3 << std::endl;

    // Llegir missatge
    std::wcout << L"\nIntrodueix el missatge a xifrar: ";
    std::wstring missatge;
    std::getline(std::wcin, missatge);

    if (missatge.empty()) {
        std::wcout << L"[ERROR] Missatge buit." << std::endl;
        return;
    }

    // Processar
    std::wcout << L"\n[INFO] Missatge original: " << missatge << std::endl;

    std::wstring processat = preprocessarTexto(missatge);
    std::wcout << L"[INFO] Missatge processat: " << processat << std::endl;

    if (processat.empty()) {
        std::wcout << L"[ERROR] Després de processar, el missatge està buit." << std::endl;
        return;
    }

    // Xifrar
    std::wstring xifrat = xifrarTexto(processat);
    std::wstring xifratAgrupat = agruparEnCinco(xifrat);

    std::wcout << L"[INFO] Missatge xifrat: " << xifratAgrupat << std::endl;

    // Guardar en fitxer
    std::wofstream arxiu(L"Xifrat.txt");
    if (arxiu.is_open()) {
        arxiu << xifratAgrupat;
        arxiu.close();
        int numGrups = (xifrat.length() + 4) / 5;
        std::wcout << L"[OK] Missatge xifrat guardat a \"Xifrat.txt\" ("
            << xifrat.length() << L" lletres, "
            << numGrups << L" grups de 5)" << std::endl;
    }
    else {
        std::wcout << L"[ERROR] No s'ha pogut crear el fitxer Xifrat.txt" << std::endl;
    }
}