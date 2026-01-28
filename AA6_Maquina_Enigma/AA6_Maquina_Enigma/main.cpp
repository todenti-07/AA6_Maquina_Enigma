#include <iostream>
#include <string>

//Rotor 1:
std::string r1 = "HNFJHBWFJFBJKBFJFWE";
char notchR1 = 'A';

//Rotor 2:
std::string r2 = "HWFIERQWNEKBVFBNJCH";
char notchR2 = 'B';

//Rotor 3:
std::string r3 = "NASBNDEJKHESDBEVDFJ";
char notchR3 = 'C';

int main() {
	std::string mensajeParaCifrar; 

	std::cout << "Dame un mensaje para cifrar: "; 
	std::getline (std::cin, mensajeParaCifrar); 

	//1. Quitar puntos, comas, y simbolos especiales. 
	std::string simbolosEsp = "',.¡!¿?:;ñç";
	for (size_t i = 0; i < mensajeParaCifrar.size(); i++) //Por cada letra.. 
	{
		for (size_t j = 0; j < simbolosEsp.size(); j++) //...y por cada símbolo especial
		{
			if (mensajeParaCifrar[i] == simbolosEsp[j]) { //...comparo si la letra es un símbolo especial
				mensajeParaCifrar.erase(i,1);
				i--;
			}
		}
	}
	std::cout <<"[INFO] Quitar puntos, comas y simbolos especiales." << mensajeParaCifrar;

	//2. Quitar acentos
	std::string acentos = "áàäâéèëêíìïîóòöôúùüûÁÀÄÂÉÈËÊÍÌÏÎÓÒÖÔÚÙÜÛ"; 

	for (size_t i = 0; i < mensajeParaCifrar.size(); i++) {

		for (size_t j = 0; j < acentos.size(); j++) {

			if (mensajeParaCifrar[i] == acentos[j]) { // Si la lletra té accent...
				mensajeParaCifrar.erase(i, 1); 
				i--; 
			}
		}
	}
	std::cout << "\n[INFO] Quitar acentos: " << mensajeParaCifrar;
	
	//3. Todo en mayúsculas
	//4. Separar en grupos de 5
}