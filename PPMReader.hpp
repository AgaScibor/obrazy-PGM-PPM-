#ifndef _PPMREADER_HPP_
#define _PPMREADER_HPP_

#include "ImageReader.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


// Deklaracja klasy PPMReader dziedziczącej po ImageReader
class PPMReader : public ImageReader {
private:

    std::ifstream imageFile;
    int width;
    int height;
    int maxColor;
    std::vector<std::vector<int>> imageData;

public:
    // Konstruktor klasy PPMReader
    PPMReader(std::string imagePath);

    // Metody wirtualne dziedziczone po ImageReader
    void printImageInfo() override;
    void printMostFrequentColor() override;
    int calcualteNumberOfUniqueColors() override;
    

    // Metoda do znajdowania najczęściej występującego koloru
    int getMostFrequentColors();
   
};

#endif // _PPMREADER_HPP_
