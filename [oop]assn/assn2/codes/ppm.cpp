#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include<string>
#include<iostream>
#include "frame.h"
using namespace std;
struct Frame;
// writePPMImage --
//
// assumes input pixels are float4
// write 3-channel (8 bit --> 24 bits per pixel) ppm
void writePPMImage(const Frame* frame, const char *filename)
{
    FILE *fp = fopen(filename, "wb");

    if (!fp) {
        fprintf(stderr, "Error: could not open %s for write\n", filename);
        exit(1);
    }

    // write ppm header
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", frame->width, frame->height);
    fprintf(fp, "255\n");

    for (int j=frame->height-1; j>=0; j--) {
        for (int i=0; i<frame->width; i++) {

            // [TO DO] Get ptr to data
			float ptr[3];
			ptr[0] = frame->data[i][j][0];//ppm파일을 보면 RGB가 순서대로 픽셀마다 할당된것을 알 수 있는데, 따라서 아까 지정해준 frame의 color값들을 출력하도록 한다.
			ptr[1] = frame->data[i][j][1];
			ptr[2] = frame->data[i][j][2];

            // printf("p");

            fputc(ptr[0], fp);
            fputc(ptr[1], fp);
            fputc(ptr[2], fp);
        }
    }


    fclose(fp);
    printf("Wrote frame to image file %s\n", filename);
}
