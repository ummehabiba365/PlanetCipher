#include <iostream>
#include <string>
using namespace std;


string planets[8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
int planetLens[8] = {7, 5, 5, 4, 7, 6, 6, 7};

int getAlphaPos(char ch) {
    if (ch >= 'a' && ch <= 'z')
        ch -= 32;
    return ch - 'A' + 1;
}


string rotateLeft(string str, int shift) {
    int len = str.length();
    shift = shift % len;
    return str.substr(shift) + str.substr(0, shift);
}


string encryptLetter(char ch) {
    int alphaPos = getAlphaPos(ch);
    int planetIndex = (alphaPos - 1) % 8;
    string planet = planets[planetIndex];
    int len = planet.length();
    int shift = (alphaPos - 1) % len;
    return rotateLeft(planet, shift);
}


char decryptChunk(string chunk, string planet) {
    int len = planet.length();
    for (int i = 1; i <= 26; i++) {
        int shift = (i - 1) % len;
        string rotated = rotateLeft(planet, shift);  
        if (rotated == chunk) {
            return char('A' + i - 1);
        }
    }
    return '?';  
}

int main() {
    string name;
    cout << "?? Enter your name (case-insensitive): ";
    cin >> name;

    string encrypted = "";
    string usedPlanets[100];
    int lens[100];


    for (int i = 0; i < name.length(); i++) {
        char ch = name[i];
        int alphaPos = getAlphaPos(ch);
        int planetIndex = (alphaPos - 1) % 8;
        string planet = planets[planetIndex];
        string cipher = encryptLetter(ch);

        encrypted += cipher;
        usedPlanets[i] = planet;
        lens[i] = planet.length();
    }

    cout << "\n?? Encrypted Name: " << encrypted << endl;

    
    string decrypted = "";
    int pos = 0;

    for (int i = 0; i < name.length(); i++) {
        string planet = usedPlanets[i];
        int len = lens[i];
        string chunk = encrypted.substr(pos, len);
        char original = decryptChunk(chunk, planet);
        decrypted += original;
        pos += len;
    }

    cout << "?? Decrypted Name: " << decrypted << endl;

    return 0;
}

