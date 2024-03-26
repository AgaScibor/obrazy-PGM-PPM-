#include "PGMReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

PGMReader::PGMReader(std::string imagePath) : width(0), height(0) {
    imageFile.open(imagePath);
    if (imageFile.good()) {
        std::string fileType;
        std::string line;
        int pixelValue;

        try {
            // Read the magic number
            getline(imageFile, fileType);
            if (fileType == "P2") {
                // Ignore comments
                while (getline(imageFile, line)) {
                    if (line.empty() || line[0] != '#') {
                        std::istringstream iss(line);
                        iss >> width >> height;
                        break;
                    }
                }

                // Read pixel data
                for (int i = 0; i < width * height; ++i) {
                    imageFile >> pixelValue;
                    imageData.push_back(pixelValue);
                }
            }
            else {
                std::cout << "Plik jest innego typu niż PGM: " << imagePath << "\n";
            }
        }
        catch (std::exception& e) {
            std::cout << e.what() << "\n";
        }

    }
    else {
        std::cout << "Nie można otworzyć pliku: " << imagePath << "\n";
    }
}

void PGMReader::printImageInfo() {
    std::cout << "Rozmiar obrazu: " << width << "x" << height << "\n";
    std::cout << "Unikalnych kolorów: " << calcualteNumberOfUniqueColors() << "\n";
    printMostFrequentColor();
    printImageData();
}

void PGMReader::printMostFrequentColor() {
    auto mostFrequentColor = getMostFrequentColor();
    std::cout << "Najczęstszy kolor: " << mostFrequentColor.first << " (Ile razy: " << mostFrequentColor.second << ")\n";
}

int PGMReader::calcualteNumberOfUniqueColors() {
    std::set<int> uniqueColors(imageData.begin(), imageData.end());
    return uniqueColors.size();
}

std::pair<int, int> PGMReader::getMostFrequentColor() {
    std::map<int, int> colorFrequency;

    // Obliczanie częstości występowania kolorów
    for (int color : imageData) {
        colorFrequency[color]++;
    }

    // Znajdowanie koloru o najwyższej częstości
    int maxFrequency = 0;
    int mostFrequentColor = 0;
    for (const auto& pair : colorFrequency) {
        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
            mostFrequentColor = pair.first;
        }
    }

    return std::make_pair(mostFrequentColor, maxFrequency);
}

void PGMReader::printImageData() {
    std::set<int> uniqueColors(imageData.begin(), imageData.end());

    std::cout << "Unikalne kolory na obrazie:\n";
    for (int color : uniqueColors) {
        std::cout << color << " ";
    }
    std::cout << "\n";
}
