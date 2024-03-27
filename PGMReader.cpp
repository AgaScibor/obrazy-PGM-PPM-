#include "PGMReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>


using namespace std;

PGMReader::PGMReader(string imagePath) : width(0), height(0) 
{
    imageFile.open(imagePath);
    if (imageFile.good()) 
    {
        string fileType;
        string line;
        int pixelValue;

        try {
            // Read the magic number
            getline(imageFile, fileType);
            if (fileType == "P2") 
            {
                // Ignore comments
                while (getline(imageFile, line)) {
                    if (line.empty() || line[0] != '#')
                    {
                        istringstream iss(line);
                        iss >> width >> height;
                        break;
                    }
                }

                // Read pixel data
                for (int i = 0; i < width * height; ++i)
                {
                    imageFile >> pixelValue;
                    imageData.push_back(pixelValue);
                }
            }
            else 
            {
                cout << "Plik jest innego typu niz PGM: " << imagePath << "\n";
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

void PGMReader::printImageInfo() 
{
    cout << "Rozmiar obrazu: " << width << "x" << height << "\n";
    cout << "Unikalnych kolorow: " << calcualteNumberOfUniqueColors() << "\n";
    printMostFrequentColor();

    // Wyświetlanie unikalnych kolorów
    set<int> uniqueColors(imageData.begin(), imageData.end());
    cout << "Unikalne kolory:";
    for (int color : uniqueColors) 
    {
        cout << " " << color;
    }
    cout << "\n";
}

void PGMReader::printMostFrequentColor() 
{
    auto mostFrequentColor = getMostFrequentColor();
    cout << "Najczestszy kolor: " << mostFrequentColor.first << " (Ile razy: " << mostFrequentColor.second << ")\n";
}

int PGMReader::calcualteNumberOfUniqueColors() 
{
    set<int> uniqueColors(imageData.begin(), imageData.end());
    return uniqueColors.size();
}

pair<int, int> PGMReader::getMostFrequentColor() 
{
    map<int, int> colorFrequency;

    // Obliczanie częstości występowania kolorów
    for (int color : imageData)
    {
        colorFrequency[color]++;
    }

    // Znajdowanie koloru o najwyższej częstości
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

    return make_pair(mostFrequentColor, maxFrequency);
}
