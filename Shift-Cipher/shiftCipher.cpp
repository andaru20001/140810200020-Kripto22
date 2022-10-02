#include <iostream>

int main() {
    char text[100];
    int key, pil;

    std::cout << "Input Plaintext/Ciphertext : ";
    std::cin.getline(text, 100);

    std::cout << "Input key : ";
    std::cin >> key;

    std::cout << "\nPilih metode : \n1. Enkripsi \n2. Dekripsi\n";
    std::cout << "Pilihan : ";
    std::cin >> pil;

    if(pil == 1) {
        char a;
        for(int i = 0; text[i] != '\0'; i++) {
            a = text[i];

            if(a >= 'a' && a <= 'z') {
                a = (a + key - 97)% 26 + 97;
                text[i] = a;
            } else if (a >= 'A' && a <= 'Z') {
                a = (a + key - 65)% 26 + 65;
                text[i] = a;
            }
        }
        std::cout << "\nEnkripsi : " << text;
    } 
    
    else if (pil == 2) {
        char a;
        for(int i = 0; text[i] != '\0'; i++) {
            a = text[i];

            if(a >= 'a' && a <= 'z') {
                if (a - 97 - key < 0) {
                    a = (a - 97 - key + 26) % 26 + 97;
                    text[i] = a;
                } 
                else {
                    a = (a - 97 - key) % 26 + 97;
                    text[i] = a;
                }
            } 
            
            else if (a >= 'A' && a <= 'Z') {
                if (a - 65 - key < 0){
                    a = (a - 65 - key + 26) % 26 + 65;
                    text[i] = a;
                } 
                else {
                    a = (a - 65 - key) % 26 + 65;
                    text[i] = a;
                }
            }
        }
        std::cout << "\nDekripsi : " << text;
    }
}