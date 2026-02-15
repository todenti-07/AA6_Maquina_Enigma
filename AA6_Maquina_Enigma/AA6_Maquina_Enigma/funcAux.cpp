#include "const.h"

// Quitar acentos para std::wstring
std::wstring quitarAcentos(const std::wstring& s) {
    const std::wstring acentos = L"áàäâéèëêíìïîóòöôúùüûÁÀÄÂÉÈËÊÍÌÏÎÓÒÖÔÚÙÜÛñÑçÇ";
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

// Preprocessar text: eliminar símbols, accents, convertir a majúscules
std::wstring preprocessarTexto(const std::wstring& texto) {
    std::wstring resultado = texto;

    // 1. Eliminar símbols i espais
    std::wstring simbolosEsp = L"',.¡!¿?:;\"()[]{}0123456789 \t\n\r";
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

    // 3. Convertir a majúscules
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