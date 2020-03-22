#ifdef _WIN32
#include <windows.h>
#else
#include <stdint.h>
#define __LONG32 int32_t
#define __ULONG32 uint32_t

typedef char CHAR;
typedef short SHORT;
typedef __LONG32 LONG;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef __ULONG32 DWORD;
typedef float FLOAT;
typedef FLOAT *PFLOAT;
typedef BYTE *PBYTE;
typedef BYTE *LPBYTE;
typedef __LONG32 *PINT;
typedef __LONG32 *LPINT;
typedef WORD *PWORD;
typedef WORD *LPWORD;
typedef __LONG32 *LPLONG;
typedef DWORD *PDWORD;
typedef DWORD *LPDWORD;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef __LONG32 LONG;
typedef __ULONG32 UINT;
typedef __ULONG32 *PUINT;


#define LCS_SIGNATURE 'PSOC'

#define LCS_sRGB 'sRGB'
#define LCS_WINDOWS_COLOR_SPACE 'Win '
  typedef LONG LCSCSTYPE;
#define LCS_CALIBRATED_RGB (long)0x00000000

  typedef LONG LCSGAMUTMATCH;
#define LCS_GM_BUSINESS (long)0x00000001
#define LCS_GM_GRAPHICS (long)0x00000002
#define LCS_GM_IMAGES (long)0x00000004
#define LCS_GM_ABS_COLORIMETRIC 0x00000008

#define PROFILE_LINKED 'LINK'
#define PROFILE_EMBEDDED 'MBED'

typedef __LONG32 FXPT16DOT16, *LPFXPT16DOT16;
typedef __LONG32 FXPT2DOT30, *LPFXPT2DOT30;

typedef struct tagCIEXYZ {
    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct tagICEXYZTRIPLE {
    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

#pragma pack(2)
typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack()

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct {
    DWORD bV4Size;
    LONG bV4Width;
    LONG bV4Height;
    WORD bV4Planes;
    WORD bV4BitCount;
    DWORD bV4V4Compression;
    DWORD bV4SizeImage;
    LONG bV4XPelsPerMeter;
    LONG bV4YPelsPerMeter;
    DWORD bV4ClrUsed;
    DWORD bV4ClrImportant;
    DWORD bV4RedMask;
    DWORD bV4GreenMask;
    DWORD bV4BlueMask;
    DWORD bV4AlphaMask;
    DWORD bV4CSType;
    CIEXYZTRIPLE bV4Endpoints;
    DWORD bV4GammaRed;
    DWORD bV4GammaGreen;
    DWORD bV4GammaBlue;
} BITMAPV4HEADER, *LPBITMAPV4HEADER, *PBITMAPV4HEADER;

typedef struct {
    DWORD bV5Size;
    LONG bV5Width;
    LONG bV5Height;
    WORD bV5Planes;
    WORD bV5BitCount;
    DWORD bV5Compression;
    DWORD bV5SizeImage;
    LONG bV5XPelsPerMeter;
    LONG bV5YPelsPerMeter;
    DWORD bV5ClrUsed;
    DWORD bV5ClrImportant;
    DWORD bV5RedMask;
    DWORD bV5GreenMask;
    DWORD bV5BlueMask;
    DWORD bV5AlphaMask;
    DWORD bV5CSType;
    CIEXYZTRIPLE bV5Endpoints;
    DWORD bV5GammaRed;
    DWORD bV5GammaGreen;
    DWORD bV5GammaBlue;
    DWORD bV5Intent;
    DWORD bV5ProfileData;
    DWORD bV5ProfileSize;
    DWORD bV5Reserved;
} BITMAPV5HEADER, *LPBITMAPV5HEADER, *PBITMAPV5HEADER;

#pragma pack(1)
typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGBTRIPLE;
#pragma pack()

typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;
#endif