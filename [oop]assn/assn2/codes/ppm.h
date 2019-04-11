#pragma once
#ifndef __PPM_H__
#define __PPM_H__

struct Frame;//ppm파일선언의 헤더
void writePPMImage(const Frame* frame, const char *filename);

#endif
