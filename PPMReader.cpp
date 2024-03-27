#include "PPMReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Konstruktor klasy PPMReader
PPMReader::PPMReader(string imagePath) : width(0), height(0), maxColor(0) 
{
    imageFile.open(imagePath);

    // Sprawdzenie czy plik jest poprawny
    if (imageFile.good()) 
    {
        string fileType;
        string line;
        int pixelValue;

        try {
            // Odczytanie numeru obrazu
            getline(imageFile, fileType);
            if (fileType == "P3") 
            {
                while (getline(imageFile, line)) 
                {
                    if (line.empty() || line[0] != '#') 
                    {
                        istringstream iss(line);
                        iss >> width >> height;
                        break;
                    }
                }

                // Odczytanie maksymalnej wartości koloru
                imageFile >> maxColor;

                // Przechowywanie kolorów jako pojedyncze wartości
                imageData.resize(height, std::vector<int>(width * 3));
                for (int y = 0; y < height; ++y) 
                {
                    for (int x = 0; x < width * 3; ++x) 
                    {
                        imageFile >> pixelValue;
                        imageData[y][x] = pixelValue;
                    }
                }
            }
            else 
            {
                cout << "Plik jest innego typu niz PPM: " << imagePath << "\n";
            }
        }
        catch (std::exception& e) 
        {
            cout << e.what() << "\n";
        }
    }
    else 
    {
        cout << "Nie mozna otworzyc pliku: " << imagePath << "\n";
    }
}

void PPMReader::printImageInfo() {
    cout << "Rozmiar obrazu: " << width << "x" << height << "\n";
    cout << "Maksymalna wartosc koloru: " << maxColor << "\n";
   
    printMostFrequentColor();

    // Wyświetlanie unikalnych kolorów
    set<int> uniqueColors;
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width * 3; ++x) 
        {
            uniqueColors.insert(imageData[y][x]);
        }
    }
    cout << "Unikalne kolory:";
    for (int color : uniqueColors) 
    {
        cout << " " << color;
    }
    cout << "\n";
}

void PPMReader::printMostFrequentColor() 
{
    auto mostFrequentColor = getMostFrequentColors();
    cout << "Najczestszy kolor: " << mostFrequentColor << "\n";
}

int PPMReader::calcualteNumberOfUniqueColors() 
{
    set<int> uniqueColors;
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width * 3; ++x) 
        {
            uniqueColors.insert(imageData[y][x]);
        }
    }
    return uniqueColors.size();
}

int PPMReader::getMostFrequentColors()
{
    map<int, int> colorFrequency;

    // Obliczanie częstości występowania kolorów
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width * 3; ++x) 
        {
            colorFrequency[imageData[y][x]]++;
        }
    }

    // Znalezienie koloru o najwyższej częstości
    int maxFrequency = 0;
    int mostFrequentColor = 0;
    for (const auto& pair : colorFrequency)
    {
        if (pair.second > maxFrequency) 
        {
            maxFrequency = pair.second;
            mostFrequentColor = pair.first;
        }
    }

    return mostFrequentColor;
}
