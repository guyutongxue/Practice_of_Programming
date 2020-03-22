#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "bmp_util.h"

const char* helpMessage =
    "Usage: %s <src-file.bmp> <dst-file.bmp> [/V]\n"
    "Arguments:\n"
    "/V\t- Verbose output.\n";

void printInfoHeader(BITMAPINFOHEADER header) {
    puts("DIB Header Infos:");
    printf("DIB Header Size      : %d\n", header.biSize);
    printf("Image Width          : %d\n", header.biWidth);
    printf("Image Height         : %d\n", header.biHeight);
    printf("Planes               : %hd\n", header.biPlanes);
    printf("Bits per Pixel       : %hd\n", header.biBitCount);
    const char* compressionTypes[] = {"BI_RGB",       "BI_RLE8", "BI_RLE4",
                                      "BI_BITFIELDS", "BI_JPEG", "BI_PNG"};
    printf("Compression Type     : %s\n", compressionTypes[header.biCompression]);
    printf("Image Size           : %d\n", header.biSizeImage);
    printf("X Pixels per Meter   : %ld\n", header.biXPelsPerMeter);
    printf("Y Pixels per Meter   : %ld\n", header.biYPelsPerMeter);
    printf("Colors in Color Table: %d\n", header.biClrUsed);
}

void printV4Header(BITMAPV4HEADER header) {
    puts("DIB Header Infos:");
    printf("DIB Header Size: %d\n", header.bV4Size);
    printf("Image Width: %d\n", header.bV4Width);
    printf("Image Height: %d\n", header.bV4Height);
    printf("Planes: %hd\n", header.bV4Planes);
    printf("Bits per Pixel: %hd\n", header.bV4BitCount);
    const char* compressionTypes[] = {"BI_RGB",       "BI_RLE8", "BI_RLE4",
                                      "BI_BITFIELDS", "BI_JPEG", "BI_PNG"};
    printf("Compression Type: %s\n", compressionTypes[header.bV4V4Compression]);
    printf("Image Size: %d\n", header.bV4SizeImage);
    printf("X Pixels per Meter: %ld\n", header.bV4XPelsPerMeter);
    printf("Y Pixels per Meter: %ld\n", header.bV4YPelsPerMeter);
    printf("Colors in Color Table: %d\n", header.bV4ClrUsed);
    printf("Important Color Count: %d\n", header.bV4ClrImportant);
    printf("Red Channel Bitmask: %d\n", header.bV4RedMask);
    printf("Green Channel Bitmask: %d\n", header.bV4GreenMask);
    printf("Blue Channel Bitmask: %d\n", header.bV4BlueMask);
    printf("Alpha Channel Bitmask: %d\n", header.bV4AlphaMask);
    const char* colorSpaceType = NULL;
    switch (header.bV4CSType) {
        case LCS_CALIBRATED_RGB: colorSpaceType = "LCS_CALIBRATED_RGB"; break;
        case LCS_sRGB: colorSpaceType = "LCS_sRGB"; break;
        case LCS_WINDOWS_COLOR_SPACE: colorSpaceType = "LCS_WINDOWS_COLOR_SPACE"; break;
        case PROFILE_LINKED: colorSpaceType = "PROFILE_LINKED"; break;
        case PROFILE_EMBEDDED: colorSpaceType = "PROFILE_EMBEDDED"; break;
        default: colorSpaceType = "Unknown"; break;
    }
    printf("Color Space Type: %s\n", colorSpaceType);
    printf(
        "Color Space Endpoints:\n\tRed: (%ld,%ld,%ld)\n\tGreen: (%ld,%ld,%ld)\n\tBlue: "
        "(%ld,%ld,%ld)\n",
        header.bV4Endpoints.ciexyzRed.ciexyzX, header.bV4Endpoints.ciexyzRed.ciexyzY,
        header.bV4Endpoints.ciexyzRed.ciexyzZ, header.bV4Endpoints.ciexyzGreen.ciexyzX,
        header.bV4Endpoints.ciexyzGreen.ciexyzY, header.bV4Endpoints.ciexyzGreen.ciexyzZ,
        header.bV4Endpoints.ciexyzBlue.ciexyzX, header.bV4Endpoints.ciexyzBlue.ciexyzY,
        header.bV4Endpoints.ciexyzBlue.ciexyzZ);
    printf("Gamma for Red Channel: %d\n", header.bV4GammaRed);
    printf("Gamma for Green Channel: %d\n", header.bV4GammaGreen);
    printf("Gamma for Blue Channel: %d\n", header.bV4GammaBlue);
}

void printV5Header(BITMAPV5HEADER header) {
    puts("DIB Header Infos:");
    printf("DIB Header Size: %d\n", header.bV5Size);
    printf("Image Width: %d\n", header.bV5Width);
    printf("Image Height: %d\n", header.bV5Height);
    printf("Planes: %hd\n", header.bV5Planes);
    printf("Bits per Pixel: %hd\n", header.bV5BitCount);
    const char* compressionTypes[] = {"BI_RGB",       "BI_RLE8", "BI_RLE4",
                                      "BI_BITFIELDS", "BI_JPEG", "BI_PNG"};
    printf("Compression Type: %s\n", compressionTypes[header.bV5Compression]);
    printf("Image Size: %d\n", header.bV5SizeImage);
    printf("X Pixels per Meter: %ld\n", header.bV5XPelsPerMeter);
    printf("Y Pixels per Meter: %ld\n", header.bV5YPelsPerMeter);
    printf("Colors in Color Table: %d\n", header.bV5ClrUsed);
    printf("Important Color Count: %d\n", header.bV5ClrImportant);
    printf("Red Channel Bitmask: %d\n", header.bV5RedMask);
    printf("Green Channel Bitmask: %d\n", header.bV5GreenMask);
    printf("Blue Channel Bitmask: %d\n", header.bV5BlueMask);
    printf("Alpha Channel Bitmask: %d\n", header.bV5AlphaMask);
    const char* colorSpaceType = NULL;
    switch (header.bV5CSType) {
        case LCS_CALIBRATED_RGB: colorSpaceType = "LCS_CALIBRATED_RGB"; break;
        case LCS_sRGB: colorSpaceType = "LCS_sRGB"; break;
        case LCS_WINDOWS_COLOR_SPACE: colorSpaceType = "LCS_WINDOWS_COLOR_SPACE"; break;
        case PROFILE_LINKED: colorSpaceType = "PROFILE_LINKED"; break;
        case PROFILE_EMBEDDED: colorSpaceType = "PROFILE_EMBEDDED"; break;
        default: colorSpaceType = "Unknown"; break;
    }
    printf("Color Space Type: %s\n", colorSpaceType);
    printf(
        "Color Space Endpoints:\n\tRed: (%ld,%ld,%ld)\n\tGreen: (%ld,%ld,%ld)\n\tBlue: "
        "(%ld,%ld,%ld)\n",
        header.bV5Endpoints.ciexyzRed.ciexyzX, header.bV5Endpoints.ciexyzRed.ciexyzY,
        header.bV5Endpoints.ciexyzRed.ciexyzZ, header.bV5Endpoints.ciexyzGreen.ciexyzX,
        header.bV5Endpoints.ciexyzGreen.ciexyzY, header.bV5Endpoints.ciexyzGreen.ciexyzZ,
        header.bV5Endpoints.ciexyzBlue.ciexyzX, header.bV5Endpoints.ciexyzBlue.ciexyzY,
        header.bV5Endpoints.ciexyzBlue.ciexyzZ);
    printf("Gamma for Red Channel: %d\n", header.bV5GammaRed);
    printf("Gamma for Green Channel: %d\n", header.bV5GammaGreen);
    printf("Gamma for Blue Channel: %d\n", header.bV5GammaBlue);
    const char* intent[] = {"",
                            "Graphic (Saturation)",
                            "Proof (Relative Colorimetric)",
                            "",
                            "Picture (Perceptual)",
                            "",
                            "",
                            "",
                            "Match (Absolute Colorimetric)"};
    printf("Intent: %s\n", intent[header.bV5Intent]);
    printf("Profile Data: %d\n", header.bV5ProfileData);
    printf("Profile Size: %d\n", header.bV5ProfileSize);
    printf("Reserved: %d\n", header.bV5Reserved);
}

void convertV52Info(BITMAPV5HEADER* v5Header, BITMAPINFOHEADER* infoHeader) {
    infoHeader->biSize = v5Header->bV5Size;
    infoHeader->biWidth = v5Header->bV5Width;
    infoHeader->biHeight = v5Header->bV5Height;
    infoHeader->biPlanes = v5Header->bV5Planes;
    infoHeader->biBitCount = v5Header->bV5BitCount;
    infoHeader->biCompression = v5Header->bV5Compression;
    infoHeader->biSizeImage = v5Header->bV5SizeImage;
    infoHeader->biXPelsPerMeter = v5Header->bV5XPelsPerMeter;
    infoHeader->biYPelsPerMeter = v5Header->bV5YPelsPerMeter;
    infoHeader->biClrUsed = v5Header->bV5ClrUsed;
    infoHeader->biClrImportant = v5Header->bV5ClrImportant;
}

void convertV42Info(BITMAPV4HEADER* v4Header, BITMAPINFOHEADER* infoHeader) {
    infoHeader->biSize = v4Header->bV4Size;
    infoHeader->biWidth = v4Header->bV4Width;
    infoHeader->biHeight = v4Header->bV4Height;
    infoHeader->biPlanes = v4Header->bV4Planes;
    infoHeader->biBitCount = v4Header->bV4BitCount;
    infoHeader->biCompression = v4Header->bV4V4Compression;
    infoHeader->biSizeImage = v4Header->bV4SizeImage;
    infoHeader->biXPelsPerMeter = v4Header->bV4XPelsPerMeter;
    infoHeader->biYPelsPerMeter = v4Header->bV4YPelsPerMeter;
    infoHeader->biClrUsed = v4Header->bV4ClrUsed;
    infoHeader->biClrImportant = v4Header->bV4ClrImportant;
}

typedef struct RGBPixel {
    BYTE b;
    BYTE g;
    BYTE r;
} RGBPixel;

typedef struct RGBAPixel {
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;
} RGBAPixel;

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Bad arguments.\n");
        printf(helpMessage, argv[0]);
        return EXIT_FAILURE;
    }
    bool verbose = false;
    if (argc > 3 && strcmp(argv[3], "/V") == 0) {
        verbose = true;
    }
    FILE* fin = fopen(argv[1], "rb");
    if (!fin) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    FILE* fout = fopen(argv[2], "wb");
    BITMAPFILEHEADER bitmapFileHeader;
    fread(&bitmapFileHeader, sizeof(bitmapFileHeader), 1, fin);
    if (verbose) {
        puts("Bitmap File Header:");
        printf("Signature                 : %#hx\n", bitmapFileHeader.bfType);
        printf("File Size                 : %d\n", bitmapFileHeader.bfSize);
        /* printf("Reserved1                 : %hd\n", bitmapFileHeader.bfReserved1); */
        /* printf("Reserved2                 : %hd\n", bitmapFileHeader.bfReserved2); */
        printf("File Offset to Pixel Array: %#hx\n", bitmapFileHeader.bfOffBits);
    }

    fpos_t dibHeaderPos = 0;
    /* Seek for the size of DIB Header (for different version) */
    fgetpos(fin, &dibHeaderPos);
    DWORD dibHeaderSize = 0;
    fread(&dibHeaderSize, sizeof(DWORD), 1, fin);
    const char* dibHeaderName;
    switch (dibHeaderSize) {
        case 12: dibHeaderName = "Bitmap Core Header"; break;
        case 40: dibHeaderName = "Bitmap Info Header"; break;
        case 52: dibHeaderName = "Bitmap V2 Info Header"; break;
        case 56: dibHeaderName = "Bitmap V3 Info Header"; break;
        case 108: dibHeaderName = "Bitmap V4 Header"; break;
        case 124: dibHeaderName = "Bitmap V5 Header"; break;
        default: dibHeaderName = "Unknown Header"; break;
    }
    if (verbose)
        printf("DIB Header Type: %s\n", dibHeaderName);
    fsetpos(fin, &dibHeaderPos);

    BITMAPINFOHEADER bitmapInfoHeader;
    BITMAPV4HEADER bitmapV4Header;
    BITMAPV5HEADER bitmapV5Header;

    if (dibHeaderSize < 40) {
        printf("Unsupported DIB Header. Try another file.");
        return EXIT_FAILURE;
    } else if (dibHeaderSize < 108) {
        fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fin);
        if (verbose)
            printInfoHeader(bitmapInfoHeader);
    } else if (dibHeaderSize < 124) {
        fread(&bitmapV4Header, sizeof(BITMAPV4HEADER), 1, fin);
        if (verbose)
            printV4Header(bitmapV4Header);
        convertV42Info(&bitmapV4Header, &bitmapInfoHeader);
    } else {
        fread(&bitmapV5Header, sizeof(BITMAPV5HEADER), 1, fin);
        if (verbose)
            printV5Header(bitmapV5Header);
        convertV52Info(&bitmapV5Header, &bitmapInfoHeader);
    }
    if (bitmapInfoHeader.biClrUsed) {
        RGBQUAD* rgbQuad = (RGBQUAD*)malloc(bitmapInfoHeader.biClrUsed * sizeof(RGBQUAD));

        fread(rgbQuad, sizeof(RGBQUAD), bitmapInfoHeader.biClrUsed, fin);
        puts("This program doesn't support under-24-bit image now.");
        free(rgbQuad);
        fclose(fin);
        fclose(fout);
        return EXIT_FAILURE;
    }
    fpos_t pixelArrayPos = bitmapFileHeader.bfOffBits;
    fsetpos(fin, &pixelArrayPos);
    if (bitmapInfoHeader.biBitCount == 24) {
        RGBPixel* rgbPixel = (RGBPixel*)malloc(bitmapInfoHeader.biWidth *
                                               bitmapInfoHeader.biHeight * sizeof(RGBPixel));
        int i, j, k;
        if (verbose)
            printf("Reading pixel array...");
        for (i = 0; i < bitmapInfoHeader.biHeight; ++i) {
            for (j = 0; j < bitmapInfoHeader.biWidth; ++j) {
                fread(rgbPixel + i * bitmapInfoHeader.biWidth + j, sizeof(RGBPixel), 1, fin);
            }
            fpos_t current = 0;
            fgetpos(fin, &current);
            if ((current - pixelArrayPos) % 4)
                current += 4 - (current - pixelArrayPos) % 4;
            fsetpos(fin, &current);
        }
        if (verbose)
            puts("Finished.");
        /* Print all pixels, take too long time */
        /* if (verbose) {
            for (i = 0; i < bitmapInfoHeader.biHeight; ++i) {
                for (j = 0; j < bitmapInfoHeader.biWidth; ++j) {
                    RGBPixel* now = rgbPixel + i * bitmapInfoHeader.biWidth + j;
                    printf("#%02x%02x%02x ", now->r, now->g, now->b);
                }
                puts("");
            }
        } */
        /* First write Pixel Array */
        /* Adjust the position of stream */
        for (i = 0; i < pixelArrayPos; ++i)
            fputc(0, fout);
        /* switch width and height */
        int height = bitmapInfoHeader.biWidth;
        int width = bitmapInfoHeader.biHeight;
        if (verbose)
            printf("Writing pixel array...");
        for (i = height - 1; i >= 0; i--) {
            for (j = 0; j < width; j++) {
                fwrite(rgbPixel + i + height * j, sizeof(RGBPixel), 1, fout);
            }
            fpos_t current = 0;
            fgetpos(fout, &current);
            if ((current - pixelArrayPos) % 4) {
                for (k = 0; k < (4 - (current - pixelArrayPos) % 4); ++k) {
                    fputc(0, fout);
                }
            }
        }
        if (verbose)
            puts("Finished.");

        /* Then write the DIB Header */
        /* Calculate necessary attribs */
        fpos_t current;
        fgetpos(fout, &current);
        DWORD imageSize = current - pixelArrayPos;
        fsetpos(fout, &dibHeaderPos);
        bitmapInfoHeader.biHeight = height;
        bitmapInfoHeader.biWidth = width;
        bitmapInfoHeader.biSizeImage = imageSize;
        fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fout);
        if (verbose)
            puts("DIB Header written.");

        /* Last write the BMP Header */
        bitmapFileHeader.bfSize = current;
        current = 0;
        fsetpos(fout, &current);
        fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fout);
        if (verbose)
            puts("BMP File Header written. Finished.");

        free(rgbPixel);
    } else if (bitmapInfoHeader.biBitCount == 32) {
        RGBAPixel* rgbaPixel = (RGBAPixel*)malloc(bitmapInfoHeader.biWidth *
                                                  bitmapInfoHeader.biHeight * sizeof(RGBAPixel));
        int i, j, k;
        if (verbose)
            printf("Reading pixel array...");
        for (i = 0; i < bitmapInfoHeader.biHeight; ++i) {
            for (j = 0; j < bitmapInfoHeader.biWidth; ++j) {
                fread(rgbaPixel + i * bitmapInfoHeader.biWidth + j, sizeof(RGBAPixel), 1, fin);
            }
            /* Because RGBA is aligned as 4, so no need for padding*/
        }
        if (verbose)
            puts("Finished.");
        /* First write Pixel Array */
        /* Adjust the position of stream */
        for (i = 0; i < pixelArrayPos; ++i)
            fputc(0, fout);
        /* switch width and height */
        int height = bitmapInfoHeader.biWidth;
        int width = bitmapInfoHeader.biHeight;
        if (verbose)
            printf("Writing pixel array...");
        for (i = height - 1; i >= 0; i--) {
            for (j = 0; j < width; j++) {
                fwrite(rgbaPixel + i + height * j, sizeof(RGBAPixel), 1, fout);
            }
        }
        if (verbose)
            puts("Finished");

        /* Then write the DIB Header */
        /* Calculate necessary attribs */
        fpos_t current;
        fgetpos(fout, &current);
        DWORD imageSize = current - pixelArrayPos;
        fsetpos(fout, &dibHeaderPos);
        bitmapInfoHeader.biHeight = height;
        bitmapInfoHeader.biWidth = width;
        bitmapInfoHeader.biSizeImage = imageSize;
        fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fout);
        if (verbose)
            puts("DIB Header written.");

        /* Last write the BMP Header */
        bitmapFileHeader.bfSize = current;
        current = 0;
        fsetpos(fout, &current);
        fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fout);
        if (verbose)
            puts("BMP File Header written. Finished.");

        free(rgbaPixel);
    } else {
        puts("Error: I don't know how to deal with this bit size.");
        fclose(fin);
        fclose(fout);
        return EXIT_FAILURE;
    }
    fclose(fin);
    fclose(fout);
    return EXIT_SUCCESS;
}