#ifndef LIIMAGEDATA_H
#define LIIMAGEDATA_H

#include "licore_global.h"
#include <QOpenGLTexture>

class LICORE_EXPORT LiImageData
{
public:
    int width;
    int height;
    int depth;
    int faces;
    int layers;
    int mipLevels;
    int blockSize;
    bool hasAlpha;
    bool isCompressed;
    QOpenGLTexture::Target target;
    QOpenGLTexture::TextureFormat textureFormat;
    QOpenGLTexture::PixelFormat pixelFormat;
    QOpenGLTexture::PixelType pixelType;
    QByteArray imageData;
};

#endif // LIIMAGEDATA_H
