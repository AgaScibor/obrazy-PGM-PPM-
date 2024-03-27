#ifndef _PGMREADER_HPP_
#define _PGMREADER_HPP_

#include "ImageReader.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

class PGMReader : public ImageReader {
private:
    std::ifstream imageFile;
    int width;
    int height;
    std::vector<int> imageData;

public:
    PGMReader(std::string imagePath);
    void printImageInfo() override;
    void printMostFrequentColor() override;
    int calcualteNumberOfUniqueColors() override;
    

    std::pair<int, int> getMostFrequentColor();
};

#endif // _PGMREADER_HPP_
