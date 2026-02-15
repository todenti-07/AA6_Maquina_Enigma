#include "const.h"

// Desxifrar una lletra a través d'un rotor (enrere)
wchar_t xifrarRotorEnrere(wchar_t lletra, const std::wstring& rotor, int posicio) {
    if (lletra < L'A' || lletra > L'Z') return lletra;

    // Ajustar per la posició del rotor
    wchar_t ajustada = (lletra - L'A' + posicio) % 26 + L'A';

    // Buscar la lletra al rotor (operació inversa)
    int index = -1;
    for (int i = 0; i < 26; i++) {
        if (rotor[i] == ajustada) {
            index = i;
            break;
        }
    }

    if (index == -1) return lletra;

    // Ajustar sortida per la posició
    wchar_t sortida = (index - posicio + 26) % 26 + L'A';

    return sortida;
}

// Desxifrar un caràcter passant pels 3 rotors en ordre invers
wchar_t desxifrarCaracter(wchar_t lletra) {
    if (lletra < L'A' || lletra > L'Z') return lletra;

    // Avançar rotors ABANS de desxifrar (igual que al xifrar)
    avanzarRotores();

    // Passar pels rotors en ordre invers: R3 -> R2 -> R1
    wchar_t resultat = lletra;
    resultat = xifrarRotorEnrere(resultat, r3, posR3);
    resultat = xifrarRotorEnrere(resultat, r2, posR2);
    resultat = xifrarRotorEnrere(resultat, r1, posR1);

    return resultat;
}

// Desxifrar text complet
std::wstring desxifrarTexto(const std::wstring& texto) {
    std::wstring desxifrat;
    for (wchar_t c : texto) { // Només processar lletres A-Z
        if (c >= L'A' && c <= L'Z') { // Si és una lletra vàlida, desxifrar-la
            desxifrat.push_back(desxifrarCaracter(c)); // Desxifrar i afegir al resultat
        }
    }
    return desxifrat;
}

void desxifrarMissatge() {
    std::wcout << L"\n--- DESXIFRAR MISSATGE ---" << std::endl;

    // Demanar posicions inicials
    std::wcout << L"Introdueix 3 lletres per les posicions inicials (ex: A B C): ";
    wchar_t p1, p2, p3;
    std::wcin >> p1 >> p2 >> p3;
    std::wcin.ignore(10000, L'\n');

    establecerPosiciones(p1, p2, p3); // Establir posicions inicials dels rotors
    std::wcout << L"[OK] Posicions establertes: " << p1 << L" " << p2 << L" " << p3 << std::endl;

    // Llegir fitxer
    std::wifstream arxiu(L"Xifrat.txt");
    if (!arxiu.is_open()) {
        std::wcout << L"[ERROR] No s'ha pogut obrir el fitxer Xifrat.txt" << std::endl;
        return;
    }

    std::wstring xifrat;
    std::wstring linia;
    while (std::getline(arxiu, linia)) {
        xifrat += linia;
    }
    arxiu.close();

    // Eliminar espais
    std::wstring xifratNet = preprocessarTexto(xifrat);

    std::wcout << L"[INFO] Missatge xifrat llegit: " << xifrat << std::endl;
    std::wcout << L"[INFO] Total lletres: " << xifratNet.length() << std::endl;

    // Desxifrar
    std::wstring desxifrat = desxifrarTexto(xifratNet);

    std::wcout << L"[INFO] Missatge desxifrat: " << desxifrat << std::endl;

    // Guardar
    std::wofstream arxiuOut(L"Desxifrat.txt");
    if (arxiuOut.is_open()) {
        arxiuOut << desxifrat;
        arxiuOut.close();
        std::wcout << L"[OK] Missatge desxifrat guardat a \"Desxifrat.txt\" (" << desxifrat.length() << L" lletres)" << std::endl;
    }
    else {
        std::wcout << L"[ERROR] No s'ha pogut crear el fitxer Desxifrat.txt" << std::endl;
    }
}