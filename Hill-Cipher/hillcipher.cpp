#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//Function to print matrix
void print(vector<vector<int>> key, int keysize)
{
    for (int i = 0; i < keysize; i++)
    {
        for (int j = 0; j < keysize; j++)
        {
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
}

//Function to encrypt the message
string encrypt(string message, vector<vector<int>> key, int keysize)
{
    string encrypted = "";
    int i = 0;
    while (i < message.length())
    {
        vector<int> temp;
        for (int j = 0; j < keysize; j++)
        {
            if (i < message.length())
            {
                temp.push_back(message[i] - 97);
                i++;
            }
            else
                temp.push_back(0);
        }
        for (int j = 0; j < keysize; j++)
        {
            int sum = 0;
            for (int k = 0; k < keysize; k++)
            {
                sum += key[j][k] * temp[k];
            }
            encrypted += (sum % 26) + 97;
        }
    }
    return encrypted;
}

//Function to decrypt the message by using inverse matrix key and ciphertext matrix
string decrypt(string message, vector<vector<int>> key, int keysize)
{
    string decrypted = "";
    int i = 0;

    while (i < message.length())
    {
        vector<int> temp;
        for (int j = 0; j < keysize; j++)
        {
            if (i < message.length())
            {
                temp.push_back(message[i] - 97);
                i++;
            }
            else
                temp.push_back(0);
        }
        for (int j = 0; j < keysize; j++)
        {
            int sum = 0;
            for (int k = 0; k < keysize; k++)
            {
                sum += key[j][k] * temp[k];
            }
            decrypted += (sum % 26) + 97;
        }
    }
    return decrypted;
}

//Function to find determinant of matrix
int determinant(vector<vector<int>> key, int keysize)
{
    int det = 0;
    if (keysize == 1)
        return key[0][0];
    else if (keysize == 2)
        return (key[0][0] * key[1][1]) - (key[0][1] * key[1][0]);
    else
    {
        for (int i = 0; i < keysize; i++)
        {
            vector<vector<int>> temp;
            for (int j = 1; j < keysize; j++)
            {
                vector<int> temp2;
                for (int k = 0; k < keysize; k++)
                {
                    if (k != i)
                        temp2.push_back(key[j][k]);
                }
                temp.push_back(temp2);
            }
            det += pow(-1, i) * key[0][i] * determinant(temp, keysize - 1);
        }
    }
    return det;
}

//Function to find cofactor of matrix
vector<vector<int>> cofactor(vector<vector<int>> key, int keysize)
{
    vector<vector<int>> cof;
    if (keysize == 2)
    {
        cof.push_back({key[1][1], -key[1][0]});
        cof.push_back({-key[0][1], key[0][0]});
    }
    else
    {
        for (int i = 0; i < keysize; i++)
        {
            vector<int> temp;
            for (int j = 0; j < keysize; j++)
            {
                vector<vector<int>> temp2;
                for (int k = 0; k < keysize; k++)
                {
                    if (k != i)
                    {
                        vector<int> temp3;
                        for (int l = 0; l < keysize; l++)
                        {
                            if (l != j)
                                temp3.push_back(key[k][l]);
                        }
                        temp2.push_back(temp3);
                    }
                }
                temp.push_back(pow(-1, i + j) * determinant(temp2, keysize - 1));
            }
            cof.push_back(temp);
        }
    }
    return cof;
}

// function to find matrix modular inverse
vector<vector<int>> inverse(vector<vector<int>> key, int keysize)
{
    int det = determinant(key, keysize);

    //If the determinant is negative, add 26 to it until it is positive
    while (det < 0){
        det += 26;
    }

    //Find the cofactor of the matrix
    vector<vector<int>> cof = cofactor(key, keysize);
    vector<vector<int>> inv;
    for (int i = 0; i < keysize; i++)
    {
        vector<int> temp;
        for (int j = 0; j < keysize; j++)
        {
            temp.push_back(cof[i][j]);
        }
        inv.push_back(temp);
    }

    //Find the transpose of the cofactor matrix
    for (int i = 0; i < keysize; i++)
    {
        for (int j = 0; j < keysize; j++)
        {
            cof[i][j] = inv[j][i];
        }
    }

    //Find the modular inverse of the determinant
    int modinv = 0;
    for (int i = 1; i < 26; i++)
    {
        if ((det * i) % 26 == 1)
        {
            modinv = i;
            break;
        }
    }

    //Multiply the cofactor matrix by the modular inverse of the determinant
    for (int i = 0; i < keysize; i++)
    {
        for (int j = 0; j < keysize; j++)
        {
            if ((inv[i][j] * modinv) % 26 < 0){
                inv[i][j] = (inv[i][j] * modinv) % 26 + 26;
            }
            else{
                inv[i][j] = (inv[i][j] * modinv) % 26;
            }
        }
    }

    //Transpose the matrix
    vector<vector<int>> transpose(keysize, vector<int>(keysize));
    for (int i = 0; i < keysize; i++)
    {
        for (int j = 0; j < keysize; j++)
        {
            transpose[i][j] = inv[j][i];
        }
    }
    return transpose;
}

//Function to find encryption key by multiplying ciphertext and the inverse modular of 26 of plaintext
vector<vector<int>> keygen(string message, string encrypted, int keysize)
{
    //Convert message to numbers and then put the first keysize x keysize numbers into a keysize x keysize matrix
    vector<vector<int>> ptext;
    for (int i = 0; i < keysize; i++)
    {
        vector<int> temp;
        for (int j = 0; j < keysize; j++)
        {
            temp.push_back(message[j * keysize + i] - 97);
        }
        ptext.push_back(temp);
    }
    //Convert encrypted to numbers and then put the first keysize x keysize numbers into a keysize x keysize matrix
    vector<vector<int>> ctext;
    for (int i = 0; i < keysize; i++)
    {
        vector<int> temp;
        for (int j = 0; j < keysize; j++)
        {
            temp.push_back(encrypted[j * keysize + i] - 97);
        }
        ctext.push_back(temp);
    }
    
    //Find the inverse of the plaintext
    vector<vector<int>> inv = inverse(ptext, keysize);
    
    //Multiply the inverse of plaintext and the encrypted matrix
    vector<vector<int>> keygen;
    for (int i = 0; i < keysize; i++)
    {
        vector<int> temp;
        for (int j = 0; j < keysize; j++)
        {
            int sum = 0;
            for (int k = 0; k < keysize; k++)
            {
                sum += ctext[i][k] * inv[k][j];
            }
            temp.push_back(sum % 26);
        }
        keygen.push_back(temp);
    }
    return keygen;
}

int main()
{
    cout << "1. Encrypt\n2. Decrypt\n3. Find Key\nEnter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1 || choice == 2){
        string message;
        cout << "Enter message: ";
        cin >> message;
        int keysize;
        cout << "Enter key size: ";
        cin >> keysize;
        vector<vector<int>> key;
        cout << "Enter key matrix: " << endl;

        for (int i = 0; i < keysize; i++)
        {
            vector<int> temp;
            for (int j = 0; j < keysize; j++)
            {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            key.push_back(temp);
        }

        if (choice == 1)
        {
            string encrypted = encrypt(message, key, keysize);
            cout << "Encrypted message: " << encrypted << endl;
        }
        else if (choice == 2)
        {
            vector<vector<int>> inv = inverse(key, keysize);
            string decrypted = decrypt(message, inv, keysize);
            cout << "Decrypted message: " << decrypted << endl;
        }
    }
    else if (choice == 3){
        string message;
        cout << "Enter message: ";
        cin >> message;

        string encrypted;
        cout << "Enter encrypted message: ";
        cin >> encrypted;

        int keysize;
        cout << "Enter key size: ";
        cin >> keysize;
        
        vector<vector<int>> key = keygen(message, encrypted, keysize);
        cout << "Key: " << endl;
        print(key, keysize);
    }
    else
        cout << "Invalid choice" << endl;
}