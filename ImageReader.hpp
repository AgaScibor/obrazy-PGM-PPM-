#ifndef _IMAGE_READER_HPP_
#define _IMAGE_READER_HPP_

#include <string>

class ImageReader {
public:
    virtual ~ImageReader() {}

    virtual void printImageInfo() = 0;
    virtual void printMostFrequentColor() = 0;
    virtual int calcualteNumberOfUniqueColors() = 0;
};

#endif // _IMAGE_READER_HPP_
