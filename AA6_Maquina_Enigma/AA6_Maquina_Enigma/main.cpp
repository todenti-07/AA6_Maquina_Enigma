#include "const.h"


int main() {

    _setmode(_fileno(stdout), _O_U16TEXT); // Permet imprimir caràcters Unicode a la consola
    _setmode(_fileno(stdin), _O_U16TEXT); // Permet llegir caràcters Unicode des de la consola

    std::locale::global(std::locale(""));

    int opcio;
    do {
        menu();
        std::wcin >> opcio;
        std::wcin.ignore(10000, L'\n'); // Netejar "buffer" per evitar problemes amb getline després de cin

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
            std::wcout << L"\nSortint del programa. Adéu!" << std::endl;
            break;
        default:
            std::wcout << L"[ERROR] Opció no vàlida." << std::endl;
        }

    } while (opcio != 4);

    return 0;
}