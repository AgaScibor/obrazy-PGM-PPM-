#include "PGMReader.hpp"
#include "PPMReader.hpp"
#include <iostream>
using namespace std;

int main() {
    // Tworzenie obiektu klasy PGMReader
    PGMReader p("prague.CED.pgm");

    // Wczytanie obrazu i wyświetlenie jego informacji
    p.printImageInfo();

    // Wyświetlenie najczęściej występującego koloru
    p.printMostFrequentColor();

    // Obliczenie i wyświetlenie liczby unikalnych kolorów
    int uniqueColors = p.calculateNumberOfUniqueColors();
    cout << "Liczba unikalnych kolorow w obrazie PGM: " << uniqueColors << endl;

    cout << "\n";

    // Tworzenie obiektu klasy PPMReader
    PPMReader b("blocks.ppm");

    // Wczytanie obrazu PPM i wyświetlenie jego informacji
    b.printImageInfo();

    // Wyświetlenie najczęściej występującego koloru w obrazie PPM
    b.printMostFrequentColor();

    // Obliczenie i wyświetlenie liczby unikalnych kolorów w obrazie PPM
    int uniqueColorsPPM = b.calculateNumberOfUniqueColors();
    cout << "Liczba unikalnych kolorow w obrazie PPM: " << uniqueColorsPPM << endl;

    return 0;
}
