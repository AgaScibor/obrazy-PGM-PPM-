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

    // Wyświetlanie unikalnych kolorów w formie RGB
    set<vector<int>> uniqueColors;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width * 3; x += 3) {
            vector<int> color = { imageData[y][x], imageData[y][x + 1], imageData[y][x + 2] };
            uniqueColors.insert(color);
        }
    }
    cout << "Unikalne kolory:";
    for (const auto& color : uniqueColors) {
        cout << " (" << color[0] << ", " << color[1] << ", " << color[2] << ")";
    }
    cout << "\n";
}

void PPMReader::printMostFrequentColor() {
    map<vector<int>, int> colorFrequency;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width * 3; x += 3) {
            vector<int> color = { imageData[y][x], imageData[y][x + 1], imageData[y][x + 2] };
            colorFrequency[color]++;
        }
    }

    auto mostFrequent = std::max_element(colorFrequency.begin(), colorFrequency.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
        });

    if (mostFrequent != colorFrequency.end()) {
        cout << "Najczestszy kolor: (R=" << mostFrequent->first[0]
            << ", G=" << mostFrequent->first[1]
            << ", B=" << mostFrequent->first[2]
            << ") (ile razy wystapil: " << mostFrequent->second << ")\n";
    }
    else {
        cout << "Brak kolorów.\n";
    }
}

int PPMReader::calculateNumberOfUniqueColors() {
    set<vector<int>> uniqueColors;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width * 3; x += 3) {
            vector<int> color = { imageData[y][x], imageData[y][x + 1], imageData[y][x + 2] };
            uniqueColors.insert(color);
        }
    }
    return uniqueColors.size();
}
