#include "PPMReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

// Konstruktor klasy PPMReader
PPMReader::PPMReader(std::string imagePath) : width(0), height(0), maxColor(0) {
    imageFile.open(imagePath);

    // Sprawdzenie czy plik jest poprawny
    if (imageFile.good()) 
    {
        std::string fileType;
        std::string line;
        int pixelValue;
       
        try 
        {
            // Odczytanie  numeru obrazu
            getline(imageFile, fileType);
            if (fileType == "P3") 
            {
                
                while (getline(imageFile, line)) 
                {
                    if (line.empty() || line[0] != '#') 
                    {
                        std::istringstream iss(line);
                        iss >> width >> height;
                        break;
                    }
                }

                // Odczytanie maksymalnej wartości koloru
                imageFile >> maxColor;

                
                imageData.resize(height, std::vector<std::vector<int>>(width, std::vector<int>(3)));
                for (int y = 0; y < height; ++y) 
                {
                    for (int x = 0; x < width; ++x) 
                    {
                        for (int i = 0; i < 3; ++i) 
                        {
                            imageFile >> pixelValue;
                            imageData[y][x][i] = pixelValue;
                        }
                    }
                }
            }
            else 
            {
                std::cout << "Plik jest innego typu niz PPM: " << imagePath << "\n";
            }
        }
        catch (std::exception& e) 
        {
            std::cout << e.what() << "\n";
        }

    }
    else 
    {
        std::cout << "Nie mozna otworzyc pliku: " << imagePath << "\n";
    }
}

// wyświetlanie informacji o obrazie
void PPMReader::printImageInfo() {
    std::cout << "Rozmiar obrazu: " << width << "x" << height << "\n";
    std::cout << "Maksymalna wartosc koloru: " << maxColor << "\n";
    std::cout << "Unikalnych kolorow: " << calcualteNumberOfUniqueColors() << "\n";
    printMostFrequentColor();
    printImageData();
}

// wyświetlanie najczęściej występującego koloru
void PPMReader::printMostFrequentColor() {
    auto mostFrequentColors = getMostFrequentColors();

    std::cout << "Najczestsze kolory: ";
    for (const auto& color : mostFrequentColors) {
        std::cout << "(";
        for (size_t i = 0; i < color.size(); ++i) {
            std::cout << color[i];
            if (i < color.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ")";
    }
    std::cout << "\n";
}

//  obliczanie liczby unikalnych kolorów
int PPMReader::calcualteNumberOfUniqueColors() {
    std::set<std::vector<int>> uniqueColors;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uniqueColors.insert(imageData[y][x]);
        }
    }
    return uniqueColors.size();
}

// wyznaczanie najczęściej występującego koloru
std::vector<std::vector<int>> PPMReader::getMostFrequentColors() {
    std::map<std::vector<int>, int> colorFrequency;

    // Obliczanie częstotliwości kolorów
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            colorFrequency[imageData[y][x]]++;
        }
    }

    // Znalezienie maksymalnej częstotliwości
    int maxFrequency = 0;
    for (const auto& pair : colorFrequency) {
        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
        }
    }

    // Zapisanie pełnych informacji o kolorach o maksymalnej częstotliwości
    std::vector<std::vector<int>> mostFrequentColors;
    for (const auto& pair : colorFrequency) {
        if (pair.second == maxFrequency) {
            mostFrequentColors.push_back(pair.first);
        }
    }

    return mostFrequentColors;
}

// wyświetlanie danych pikseli obrazu
void PPMReader::printImageData() {
    std::set<std::vector<int>> uniqueColors;

    // Zbieranie unikalnych kolorów
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uniqueColors.insert(imageData[y][x]);
        }
    }

    
    std::cout << "Unikalne kolory na obrazie:\n";
    for (const auto& color : uniqueColors) {
        std::cout << " ";
        for (int i = 0; i < 3; ++i) {
            std::cout << color[i];
            if (i < 2) std::cout << ", ";
        }
        std::cout << "\n";
    }
}
