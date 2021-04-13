#include <fstream>
#include <iostream>

#include "bmp_util.h"

class DibHeader {
    enum { INFO, V4, V5 } type;
    union {
        BITMAPINFOHEADER info;
        BITMAPV4HEADER v4;
        BITMAPV5HEADER v5;
    } data;

public:
    DibHeader(std::istream& ifs) {
        auto p{ifs.tellg()};
        DWORD dibSize;
        ifs.read(reinterpret_cast<char*>(&dibSize), sizeof(dibSize));
        ifs.seekg(p);
        switch (dibSize) {
            case sizeof(BITMAPINFOHEADER): type = INFO; break;
            case sizeof(BITMAPV4HEADER): type = V4; break;
            case sizeof(BITMAPV5HEADER): type = V5; break;
            default: throw std::runtime_error("Error type");
        }
        ifs.read(reinterpret_cast<char*>(&data), dibSize);
    }

    DWORD& size() {
        switch (type) {
            case INFO: return data.info.biSize;
            case V4: return data.v4.bV4Size;
            case V5: return data.v5.bV5Size;
            default: throw std::runtime_error("Error type");
        }
    }

    LONG& width() {
        switch (type) {
            case INFO: return data.info.biWidth;
            case V4: return data.v4.bV4Width;
            case V5: return data.v5.bV5Width;
            default: throw std::runtime_error("Error type");
        }
    }

    LONG& height() {
        switch (type) {
            case INFO: return data.info.biHeight;
            case V4: return data.v4.bV4Height;
            case V5: return data.v5.bV5Height;
            default: throw std::runtime_error("Error type");
        }
    }

    DWORD& sizeImage() {
        switch (type) {
            case INFO: return data.info.biSizeImage;
            case V4: return data.v4.bV4SizeImage;
            case V5: return data.v5.bV5SizeImage;
            default: throw std::runtime_error("Error type");
        }
    }

    WORD& bitCount() {
        switch (type) {
            case INFO: return data.info.biBitCount;
            case V4: return data.v4.bV4BitCount;
            case V5: return data.v5.bV5BitCount;
            default: throw std::runtime_error("Error type");
        }
    }

    bool write(std::ostream& ofs) {
        switch (type) {
            case INFO: ofs.write(reinterpret_cast<char*>(&data), sizeof(BITMAPINFOHEADER)); break;
            case V4: ofs.write(reinterpret_cast<char*>(&data), sizeof(BITMAPV4HEADER)); break;
            case V5: ofs.write(reinterpret_cast<char*>(&data), sizeof(BITMAPV5HEADER)); break;
            default: throw std::runtime_error("Error type");
        }
        return static_cast<bool>(ofs);
    }
};

int main() {
    std::ifstream ifs("./5.bmp");
    ifs.seekg(sizeof(BITMAPFILEHEADER));
    DibHeader dib(ifs);
    std::cout << dib.width();
}