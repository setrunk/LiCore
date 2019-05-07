#pragma once

#include "licore_global.h"

namespace DXTC
{
    // DXT compressor (scalar version).
    void CompressImageDXT1(const quint8* inBuf, quint8* outBuf, int width, int height, unsigned int rowPitch = 0);
    void CompressImageDXT5(const quint8* inBuf, quint8* outBuf, int width, int height, unsigned int rowPitch = 0);
    quint16 ColorTo565(const quint8* color);
    void EmitByte(quint8*& dest, quint8 b);
    void EmitWord(quint8*& dest, quint16 s);
    void EmitDoubleWord(quint8*& dest, quint32 i);
    void ExtractBlock(const quint8* inPtr, int width, quint8* colorBlock);
    void GetMinMaxColors(const quint8* colorBlock, quint8* minColor, quint8* maxColor);
    void GetMinMaxColorsWithAlpha(const quint8* colorBlock, quint8* minColor, quint8* maxColor);
    void EmitColorIndices(const quint8* colorBlock, quint8*& outBuf, const quint8* minColor, const quint8* maxColor);
    void EmitAlphaIndices(const quint8* colorBlock,  quint8*& outBuf, const quint8 minAlpha, const quint8 maxAlpha);

    // DXT compressor (SSE2 version).
    void CompressImageDXT1SSE2(const quint8* inBuf, quint8* outBuf, int width, int height, unsigned int rowPitch = 0);
    void CompressImageDXT5SSE2(const quint8* inBuf, quint8* outBuf, int width, int height, unsigned int rowPitch = 0);
    void ExtractBlock_SSE2(const quint8* inPtr, int width, quint8* colorBlock);
    void GetMinMaxColors_SSE2(const quint8* colorBlock, quint8* minColor, quint8* maxColor);
    void EmitColorIndices_SSE2(const quint8* colorBlock, quint8*& outBuf, const quint8* minColor, const quint8* maxColor);
    void EmitAlphaIndices_SSE2(const quint8* colorBlock, quint8*& outBuf, const quint8 minAlpha, const quint8 maxAlpha);
}
