#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <algorithm>
#include <fcntl.h>
#include <io.h>


// -------------------------- CONFIGURACI” DELS ROTORS --------------------------
// Aquests cablejats sÛn EXEMPLES. Haurien de tenir 26 lletres ˙niques A-Z
std::wstring r1 = L"EKMFLGDQVZNTOWYHXUSPAIBRCJ";  // Rotor I
wchar_t notchR1 = L'Q';

std::wstring r2 = L"AJDKSIRUXBLHWTMCQGZNPYFVOE";  // Rotor II
wchar_t notchR2 = L'E';

std::wstring r3 = L"BDFHJLCPRTXVZNYEIWGAKMUSQO";  // Rotor III
wchar_t notchR3 = L'V';

// Posicions actuals dels rotors (0-25)
int posR1 = 0, posR2 = 0, posR3 = 0;

// -------------------------- FUNCIONS AUXILIARS --------------------------

// Quitar acentos para std::wstring
std::wstring quitarAcentos(const std::wstring& s) {
    const std::wstring acentos = L"·‡‰‚ÈËÎÍÌÏÔÓÛÚˆÙ˙˘¸˚¡¿ƒ¬…»À ÕÃœŒ”“÷‘⁄Ÿ‹€Ò—Á«";
    const std::wstring sinAcentos = L"aaaaeeeeiiiioooouuuuAAAAEEEEIIIIOOOOUUUUnNcC";
    std::wstring r;
    r.reserve(s.size());
    for (wchar_t ch : s) {
        std::size_t pos = acentos.find(ch);
        if (pos != std::wstring::npos)
            r.push_back(sinAcentos[pos]);
        else
            r.push_back(ch);
    }
    return r;
}

// Preprocessar text: eliminar sÌmbols, accents, convertir a maj˙scules
std::wstring preprocessarTexto(const std::wstring& texto) {
    std::wstring resultado = texto;

    // 1. Eliminar sÌmbols i espais
    std::wstring simbolosEsp = L"',.°!ø?:;\"()[]{}0123456789 \t\n\r";
    for (size_t i = 0; i < resultado.size(); ++i) {
        for (size_t j = 0; j < simbolosEsp.size(); ++j) {
            if (resultado[i] == simbolosEsp[j]) {
                resultado.erase(i, 1);
                --i;
                break;
            }
        }
    }

    // 2. Eliminar accents
    resultado = quitarAcentos(resultado);

    // 3. Convertir a maj˙scules
    for (wchar_t& c : resultado) {
        c = std::toupper(c);
    }

    return resultado;
}

// Agrupar en grups de 5 lletres
std::wstring agruparEnCinco(const std::wstring& texto) {
    std::wstring agrupado;
    for (size_t i = 0; i < texto.size(); i++) {
        agrupado.push_back(texto[i]);
        if ((i + 1) % 5 == 0 && i != texto.size() - 1)
            agrupado.push_back(L' ');
    }
    return agrupado;
}

// --------------------- L“GICA D'ENIGMA -------------------------

// AvanÁar els rotors segons la lÚgica ENIGMA
void avanzarRotores() {
    // Double-stepping: si rotor 2 est‡ al notch
    bool r2EnNotch = (L'A' + posR2 == notchR2);

    if (r2EnNotch) {
        posR2 = (posR2 + 1) % 26;
        posR3 = (posR3 + 1) % 26;
    }

    // Sempre avanÁar rotor 1
    bool r1LlegaAlNotch = (L'A' + posR1 == notchR1);
    posR1 = (posR1 + 1) % 26;

    // Si rotor 1 arriba al notch, avanÁa rotor 2
    if (r1LlegaAlNotch && !r2EnNotch) {
        bool r2LlegaAlNotch = (L'A' + posR2 == notchR2);
        posR2 = (posR2 + 1) % 26;

        // Si rotor 2 arriba al notch, avanÁa rotor 3
        if (r2LlegaAlNotch) {
            posR3 = (posR3 + 1) % 26;
        }
    }
}

// Xifrar una lletra a travÈs d'un rotor (endavant)
wchar_t xifrarRotorEndavant(wchar_t lletra, const std::wstring& rotor, int posicio) {
}

// Desxifrar una lletra a travÈs d'un rotor (enrere)
wchar_t xifrarRotorEnrere(wchar_t lletra, const std::wstring& rotor, int posicio) {
    if (lletra < L'A' || lletra > L'Z') return lletra;

    // Ajustar per la posiciÛ del rotor
    wchar_t ajustada = (lletra - L'A' + posicio) % 26 + L'A';

    // Buscar la lletra al rotor (operaciÛ inversa)
    int index = -1;
    for (int i = 0; i < 26; i++) {
        if (rotor[i] == ajustada) {
            index = i;
            break;
        }
    }

    if (index == -1) return lletra;

    // Ajustar sortida per la posiciÛ
    wchar_t sortida = (index - posicio + 26) % 26 + L'A';

    return sortida;
}

// Xifrar un car‡cter complet passant pels 3 rotors
wchar_t xifrarCaracter(wchar_t lletra) {
}

// Desxifrar un car‡cter passant pels 3 rotors en ordre invers
wchar_t desxifrarCaracter(wchar_t lletra) {
    if (lletra < L'A' || lletra > L'Z') return lletra;

    // AvanÁar rotors ABANS de desxifrar (igual que al xifrar)
    avanzarRotores();

    // Passar pels rotors en ordre invers: R3 -> R2 -> R1
    wchar_t resultat = lletra;
    resultat = xifrarRotorEnrere(resultat, r3, posR3);
    resultat = xifrarRotorEnrere(resultat, r2, posR2);
    resultat = xifrarRotorEnrere(resultat, r1, posR1);

    return resultat;
}

// Xifrar text complet
std::wstring xifrarTexto(const std::wstring& texto) {
}

// Desxifrar text complet
std::wstring desxifrarTexto(const std::wstring& texto) {
    std::wstring desxifrat;
    for (wchar_t c : texto) { // NomÈs processar lletres A-Z
        if (c >= L'A' && c <= L'Z') { // Si Ès una lletra v‡lida, desxifrar-la
            desxifrat.push_back(desxifrarCaracter(c)); // Desxifrar i afegir al resultat
        }
    }
    return desxifrat;
}

// Establir posicions inicials dels rotors
void establecerPosiciones(wchar_t p1, wchar_t p2, wchar_t p3) {
    posR1 = std::toupper(p1) - L'A'; // Convertir a Ìndex (0-25)
    posR2 = std::toupper(p2) - L'A'; // Convertir a Ìndex (0-25)
    posR3 = std::toupper(p3) - L'A'; // Convertir a Ìndex (0-25)

    // Assegurar que estan en el rang 0-25
    if (posR1 < 0 || posR1 > 25) posR1 = 0;
    if (posR2 < 0 || posR2 > 25) posR2 = 0;
    if (posR3 < 0 || posR3 > 25) posR3 = 0;
}

// -------------------------- FUNCIONS DEL MEN⁄ --------------------------

void xifrarMissatge() {
    std::wcout << L"\n--- XIFRAR MISSATGE ---" << std::endl;
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
    std::wifstream arxiu("Xifrat.txt");
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
    std::wofstream arxiuOut("Desxifrat.txt");
    if (arxiuOut.is_open()) {
        arxiuOut << desxifrat;
        arxiuOut.close();
        std::wcout << L"[OK] Missatge desxifrat guardat a \"Desxifrat.txt\" (" << desxifrat.length() << L" lletres)" << std::endl;
    }
    else {
        std::wcout << L"[ERROR] No s'ha pogut crear el fitxer Desxifrat.txt" << std::endl;
    }
}

void editarRotors() {
    std::wcout << L"\n--- EDITAR ROTORS --- << std::endl";
    std::wcout << L"Quin rotor vols editar? (1-3): "; // Demanar n˙mero de rotor
    int num;
    std::wcin >> num;
    std::wcin.ignore(10000, L'\n');

    if (num < 1 || num > 3) { // Validar n˙mero de rotor
        std::wcout << L"[ERROR] N˙mero de rotor inv‡lid." << std::endl;
        return;
    }

    std::wcout << L"\nIntrodueix el nou cablejat (26 lletres ˙niques A-Z): ";
    std::wstring nouCablejat;
    std::getline(std::wcin, nouCablejat);

    nouCablejat = preprocessarTexto(nouCablejat); // Eliminar espais, accents i convertir a maj˙scules

    // Validar
    if (nouCablejat.length() != 26) { // Comprovar longitud
        std::wcout << L"[ERROR] El cablejat ha de tenir exactament 26 lletres." << std::endl;
        return;
    }

    // Verificar que no hi hagi lletres repetides
    bool trobades[26] = { false }; // Per marcar quines lletres s'han trobat
    for (wchar_t c : nouCablejat) {
        if (c < L'A' || c > L'Z') { // Car‡cter no v‡lid
            std::wcout << L"[ERROR] El cablejat nomÈs pot contenir lletres A-Z." << std::endl;
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
    if (!notchStr.empty()) { // Si s'ha introduÔt una lletra, validar-la
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

void menu() {
    std::wcout << L"\tENIGMA" << std::endl;
    std::wcout << L"-------------------------------" << std::endl;
    std::wcout << L"1. Xifrar missatge" << std::endl;
    std::wcout << L"2. Desxifrar missatge" << std::endl;
    std::wcout << L"3. Editar rotors" << std::endl;
    std::wcout << L"4. Sortir" << std::endl;
    std::wcout << L"-------------------------------" << std::endl;
    std::wcout << L"Tria una opciÛ: ";
}

// -------------------------- PROGRAMA PRINCIPAL --------------------------

int main() {

    _setmode(_fileno(stdout), _O_U16TEXT); // Permet imprimir car‡cters Unicode a la consola
    _setmode(_fileno(stdin), _O_U16TEXT); // Permet llegir car‡cters Unicode des de la consola

    std::locale::global(std::locale(""));

    int opcio;
    do {
        menu();
        std::wcin >> opcio;
        std::wcin.ignore(10000, L'\n'); // Netejar "buffer" per evitar problemes amb getline desprÈs de cin

        switch (opcio) {
        case 1:
            xifrarMissatge();
            break;
        case 2:
            desxifrarMissatge();
            break;
        case 3:
            editarRotors();
            break;
        case 4:
            std::wcout << L"\nSortint del programa. AdÈu!" << std::endl;
            break;
        default:
            std::wcout << L"[ERROR] OpciÛ no v‡lida." << std::endl;
        }

    } while (opcio != 4);

    return 0;
}