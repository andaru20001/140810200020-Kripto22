//Vigenere cipher program
#include <iostream>
#include <string>

//Function to encrypt the message
std::string encrypt(std::string message, std::string key){
    std::string encrypted_message = "";
    int key_length = key.length();
    int message_length = message.length();
    int key_index = 0;
    for (int i = 0; i < message_length; i++){
        if (message[i] == ' '){
            encrypted_message += ' ';
            continue;
        }
        else if (message[i] > 96){
            if (key[key_index] > 96){
                encrypted_message += (message[i] + key[key_index] - 194 + 26) % 26 + 97;
            }
            else{
                encrypted_message += (message[i] + key[key_index] - 162 + 26) % 26 + 97;
            }
        }
        else if (message[i] > 64){
            if (key[key_index] > 96){
                encrypted_message += (message[i] + key[key_index] - 162 + 26) % 26 + 65;
            }
            else{
                encrypted_message += (message[i] + key[key_index] - 130 + 26) % 26 + 65;
            }
        }
        key_index = (key_index + 1) % key_length;
    }
    return encrypted_message;
}

//Function to decrypt the message
std::string decrypt(std::string message, std::string key){
    std::string decrypted_message = "";
    int key_length = key.length();
    int message_length = message.length();
    int key_index = 0;
    for (int i = 0; i < message_length; i++)
    {
        if (message[i] == ' '){
            decrypted_message += ' ';
            continue;
        }
        else if (message[i] > 96){
            if (key[key_index] > 96){
                if (message[i] - key[key_index] < 0){
                    decrypted_message += ((message[i] - 97) - (key[key_index] - 97) + 26) % 26 + 97;
                }
                else{
                    decrypted_message += ((message[i] - 97) - (key[key_index] - 97)) % 26 + 97;
                }
            }
            else{
                if (message[i] - key[key_index] < 0){
                    decrypted_message += ((message[i] - 97) - (key[key_index] - 65) + 26) % 26 + 97;
                }
                else{
                    decrypted_message += ((message[i] - 97) - (key[key_index] - 65)) % 26 + 97;
                }
            }
        }
        else if (message[i] > 64){
            if (key[key_index] > 96){
                if (message[i] - key[key_index] < 0){
                    decrypted_message += ((message[i] - 65) - (key[key_index] - 97) + 26) % 26 + 65;
                }
                else{
                    decrypted_message += ((message[i] - 65) - (key[key_index] - 65)) % 26 + 65;
                }
            }
            else{
                if (message[i] - key[key_index] < 0){
                    decrypted_message += ((message[i] - 65) - (key[key_index] - 65) + 26) % 26 + 65;
                }
                else{
                    decrypted_message += ((message[i] - 65) - (key[key_index] - 65)) % 26 + 65;
                }
            }
        }
        key_index = (key_index + 1) % key_length;
    }
    return decrypted_message;
}

int main(){
    bool check = 1;
    while (check){
        //Menu
        std::cout << "1. Encrypt\n2. Decrypt\n3. Exit\nEnter choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        //Exit
        if (choice == 3){
            check = 0;
            continue;
        }

        //Input message and key
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        std::cout << "Enter key: ";
        std::string key;
        std::getline(std::cin, key);

        //Encrypt the message
        if (choice == 1){
            std::string encrypted_message = encrypt(message, key);
            std::cout << "Encrypted message: " << encrypted_message << "\n=============================================" << std::endl;
        }

        //Decrypt the message
        else if (choice == 2){
            std::string decrypted_message = decrypt(message, key);
            std::cout << "Decrypted message: " << decrypted_message << "\n=============================================" << std::endl;
        }

        //Else
        else{
            std::cout << "Invalid choice" << "\n=============================================" << std::endl;
        }
    }
}