#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef unsigned char byte;

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "lodepng.h"

using std::size_t;
using std::uint8_t;

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    Pixel() {
        this->red   = 0;
        this->green = 0;
        this->blue  = 0;
        this->alpha = 0;
    }
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
        this->red   = red;
        this->green = green;
        this->blue  = blue;
        this->alpha = alpha;
    }
};

// some common colors
namespace CommonColors {
    Pixel BLACK(0, 0, 0, 255);
    Pixel WHITE(255, 255, 255, 255);
    Pixel RED(255, 0, 0, 255);
    Pixel GREEN(0, 255, 0, 255);
    Pixel BLUE(0, 0, 255, 255);
}

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.red   == rhs.red
        && lhs.blue  == rhs.blue
        && lhs.green == rhs.green
        && lhs.alpha == rhs.alpha;
}

bool operator!=(const Pixel& lhs, const Pixel& rhs) {
    return !(lhs == rhs);
}

class Image {
private:
    size_t width;
    size_t height;
    std::vector<Pixel> data;

public:
    Image(size_t width = 0, size_t height = 0) {
        this->width  = width;
        this->height = height;
        this->data.resize(width * height);
    }

    Image(std::string filename) {
        try {
            this->read_from_file(filename);
        }
        catch (std::runtime_error err) {
            this->width = 0;
            this->height = 0;
            this->data.resize(0);
        }
    }

    void read_from_file(std::string filename) {

        std::vector<byte> raw_data = std::vector<byte>();
        
        unsigned temp_width, temp_height;
        unsigned error = lodepng::decode(raw_data, 
                                         temp_width, 
                                         temp_height, 
                                         filename.c_str());
        
        if (error) throw std::runtime_error(lodepng_error_text(error));
        
        size_t idx = 0;
        
        this->width  = (size_t)temp_width;
        this->height = (size_t)temp_height;
        this->data.resize(this->width * this->height);

        for (size_t x = 0; x < this->width; x++) {
            for (size_t y = 0; y < this->height; y++) {
                
                Pixel read_pixel = Pixel();
                read_pixel.red   = raw_data[idx++];
                read_pixel.green = raw_data[idx++];
                read_pixel.blue  = raw_data[idx++];
                read_pixel.alpha = raw_data[idx++];
                
                this->set(x, y, read_pixel);
            }
        }
    }

    void write_to_file(std::string filename) const {
        
        std::vector<byte> raw_data = std::vector<byte>();
        raw_data.resize(4 * this->width * this->height);

        size_t idx = 0;

        for (size_t x = 0; x < this->width; x++) {
            for (size_t y = 0; y < this->height; y++) {

                Pixel cursor = this->get(x, y);
                
                raw_data[idx++] = cursor.red;
                raw_data[idx++] = cursor.green;
                raw_data[idx++] = cursor.blue;
                raw_data[idx++] = cursor.alpha;
            }
        }

        unsigned error = lodepng::encode(filename.c_str(), 
                                         raw_data, 
                                         this->width, 
                                         this->height);

        if (error) throw std::runtime_error(lodepng_error_text(error));
    }

    size_t get_width() const {
        return width;
    }

    size_t get_height() const {
        return height;
    }

    void set(size_t x, size_t y, Pixel& updated_item) {
        if ((x >= this->width) || (y >= this->height)) {
            throw std::out_of_range("Image: Invalid location in get(x, y)");
        }
        data[(y * this->width) + x] = updated_item;
    }

    Pixel get(size_t x, size_t y) const {
        if ((x >= this->width) || (y >= this->height)) {
            throw std::out_of_range("Image: Invalid location in get(x, y)");
        }
        return data[(y * this->width) + x];
    }
};

#endif // _IMAGE_H_
