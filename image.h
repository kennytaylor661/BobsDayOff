// Image class definition

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string.h>
#include <unistd.h>

class Image {
public:
    int width, height;
    unsigned char *data;
    ~Image();
    Image(const char*);
};

#endif
