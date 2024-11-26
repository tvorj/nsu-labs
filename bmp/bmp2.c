#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#pragma pack(push,1)


typedef struct {
    uint8_t signature[2]; //BM
    uint32_t filesize; // razmer faila
    uint32_t reserved; // zarazervirovannoe pole
    uint32_t fileoffset_to_pixelarray; // smeshenie bitovogo massiva otnositelno na4ala fayla
} fileheader;


typedef struct {
    uint32_t dibheadersize; // razmer structuri
    uint32_t width; // shirina
    uint32_t height; // visota
    uint16_t planes; // = 1 kolvo ploskostey
    uint16_t bitsperpixel; // glubina color v bitax na pixel
    uint32_t compression; // tip sjazhitiya BI_RGB
    uint32_t imagesize; // ramer izobrajeniya v baytax
    uint32_t ypixelpermeter; // 
    uint32_t xpixelpermeter; //
    uint32_t numcolorspallette; // = 0 dlya max kolvo cvetov
    uint32_t mostimpcolor; // = 0 using all colors
} bitmapinfoheader;


typedef struct {
    fileheader fileheader;
    bitmapinfoheader bitmapinfoheader;
} bitmap;
#pragma pack(pop)


int main(int argc, char* argv[]) {
    FILE* fp = fopen("test.bmp", "wb");
    bitmap* pbitmap = (bitmap*)calloc(1, sizeof(bitmap));
    uint8_t* pixelbuffer = (uint8_t*)malloc(1000 * 1000 * 3);

    if (pbitmap == NULL || pixelbuffer == NULL) {
        return 0;
    }
    strcpy(pbitmap->fileheader.signature, "BM");
    pbitmap->fileheader.filesize = 1000 * 1000 * 3 + sizeof(bitmap);
    pbitmap->fileheader.fileoffset_to_pixelarray = sizeof(bitmap);
    pbitmap->bitmapinfoheader.dibheadersize = sizeof(bitmapinfoheader);
    pbitmap->bitmapinfoheader.width = 1000;
    pbitmap->bitmapinfoheader.height = 1000;
    pbitmap->bitmapinfoheader.planes = 1;
    pbitmap->bitmapinfoheader.bitsperpixel = 24; //truecolor
    pbitmap->bitmapinfoheader.compression = 0;
    pbitmap->bitmapinfoheader.imagesize = 1000 * 1000 * 3;
    pbitmap->bitmapinfoheader.ypixelpermeter = 0x130B;
    pbitmap->bitmapinfoheader.xpixelpermeter = 0x130B;
    pbitmap->bitmapinfoheader.numcolorspallette = 0;
    fwrite(pbitmap, 1, sizeof(bitmap), fp);
    srand(0);
    for (int i = 0; i < 1000 * 1000 * 3; i++) {
        pixelbuffer[i] = 0xFF;
    }
    for (int x = -500; x < 500; x++) {
        for (int y = -500; y < 500; y++) {
            if (x * x + y * y < 252004) {
                pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3] = 0x00;
                pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 1] = 0x00;
                pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 2] = 0x00;
            }
        }
    }
    for (int x = -500; x < 500; x++) {
        for (int y = -500; y < 500; y++) {
            if (x * x + y * y < 250000) {
                pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3] = 0xff;
                pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 1] = 0xff;
                pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 2] = 0xff;
            }
        }
    }
    /*for (int i = 0; i < 1000 * 1000; i++) {
        int x = i / 1000 - 500;
        int y = i % 1000 - 500;
        if (x * x + y * y < 252004) {
            pixelbuffer[(i + 500) * 3] = 0x00;
            pixelbuffer[(i + 500) * 3 + 1] = 0x00;
            pixelbuffer[(i + 500) * 3 + 2] = 0x00;
        }
    }
    for (int i = 0; i < 1000 * 1000; i++) {
        int x = i / 1000 - 500;
        int y = i % 1000 - 500;
        if (x * x + y * y < 250000) {
            pixelbuffer[(i + 500) * 3] = 0xff;
            pixelbuffer[(i + 500) * 3 + 1] = 0xff;
            pixelbuffer[(i + 500) * 3 + 2] = 0xff;
        }
    }*/
    int in_circle = 0;
    int all = 100000;
    for (int i = 0; i < all; i++) {
        int x = rand() % (1000)-500;
        int y = rand() % (1000)-500;
        if (x * x + y * y < 250000) {
            pixelbuffer[((y+500) * 1000 + (x+500)) * 3] = 0x00;
            pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 1] = 0x66;
            pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 2] = 0xbb;
            in_circle++;
        }
        else {
            pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3] = 0xee;
            pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 1] = 0x33;
            pixelbuffer[((y + 500) * 1000 + (x + 500)) * 3 + 2] = 0x33;
        }
    }
    float p = 4*(float)in_circle / (float)all;
    printf("%f", p);
    /* memset(pixelbuffer, pixel, _pixelbytesize);*/ // gde, 4em zapolnyat', skolko shtuk v baytax
    fwrite(pixelbuffer, 1, 1000 * 1000 * 3, fp); // massive, count, 
    fclose(fp);
    free(pbitmap);
    free(pixelbuffer);
    return 0;
}
