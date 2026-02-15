#include <iostream>
#include <string>
#include <locale>

#include <fcntl.h>
#include <io.h>

//Rotor 1:
std::wstring r1 = L"HNFJHBWFJFBJKBFJFWE";
wchar_t notchR1 = L'A';

//Rotor 2:
std::wstring r2 = L"HWFIERQWNEKBVFBNJCH";
wchar_t notchR2 = L'B';

//Rotor 3:
std::wstring r3 = L"NASBNDEJKHESDBEVDFJ";
wchar_t notchR3 = L'C';



int main() {

    _setmode(_fileno(stdout), _O_U16TEXT); //
    _setmode(_fileno(stdin), _O_U16TEXT); //

    // IMPORTANTE para que funcionen tildes en consola en Debug
    std::locale::global(std::locale(""));

    std::wstring mensajeParaCifrar;

    std::wcout << L"Dame un mensaje para cifrar: ";
    std::getline(std::wcin, mensajeParaCifrar);

    // 1. Quitar puntos, comas y símbolos
    std::wstring simbolosEsp = L"',.¡!¿?:;\"()[]{}";

    for (size_t i = 0; i < mensajeParaCifrar.size(); ++i) {
        for (size_t j = 0; j < simbolosEsp.size(); ++j) {
            if (mensajeParaCifrar[i] == simbolosEsp[j]) {
                mensajeParaCifrar.erase(i, 1);
                --i;
                break;
            }
        }
    }

    std::wcout << L"[INFO] Sin símbolos: " << mensajeParaCifrar << std::endl;

    // 2. Quitar acentos
    mensajeParaCifrar = quitarAcentos(mensajeParaCifrar);
    std::wcout << L"[INFO] Sin acentos: " << mensajeParaCifrar << std::endl;

    // 3. Pasar a mayúsculas 
    for (wchar_t& c : mensajeParaCifrar) {
        c = std::toupper(c); 
    }
    
    std::wcout << L"[INFO] Mayúsculas: " << mensajeParaCifrar << std::endl; 

    // 4. Separar en grupos de 5 
    std::wstring agrupado; 
    for (size_t i = 0; i < mensajeParaCifrar.size(); i++) {
        agrupado.push_back(mensajeParaCifrar[i]); 

        if ((i + 1) % 5 == 0 && i != mensajeParaCifrar.size() - 1)
            agrupado.push_back(L' '); 
    }


    std::wcout << L"[INFO] Grupos de 5: " << agrupado << std::endl; 

    return 0;
}
