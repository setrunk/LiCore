#ifndef LITEXTUREUTIL_H
#define LITEXTUREUTIL_H

#include "licore_global.h"

struct TextureImageData;

/**
 * @brief
 * 提供对纹理和纹理图像数据的操作函数
 */
class LICORE_EXPORT LiTextureUtil
{
public:

    /**
     * @brief
     * 计算图像的最大MipMap链数量
     * @param width
     * 图像的宽度
     * @param height
     * 图像的高度
     * @return int
     */
    static int maximumMipLevels(int width, int height);

    /**
     * @brief
     * 计算图像第level层MipMap数据的字节大小
     * @param width
     * 图像的宽度
     * @param height
     * 图像的高度
     * @param level
     * 第level层MipMap
     * @param compressed
     * 图像数据是否有DXT压缩
     * @param blockSize
     * 每个像素或压缩块的字节大小
     * @return 数据的字节大小
     */
    static int mipmapLevelSize(int width, int height, int level, bool compressed, int blockSize);

    /**
     * @brief
     *
     * @param width
     * @param height
     * @param mipLevels
     * @param compressed
     * @param blockSize
     * @return int
     */
    static int faceSize(int width, int height, int mipLevels, bool compressed, int blockSize);

    /**
     * @brief
     *
     * @param width
     * @param height
     * @param mipLevels
     * @param faces
     * @param compressed
     * @param blockSize
     * @return int
     */
    static int layerSize(int width, int height, int mipLevels, int faces, bool compressed, int blockSize);

    /**
     * @brief
     *
     * @param image
     * @param skipCount
     * @return QImage
     */
    static QImage skipMipLevels(const QImage &image, int skipCount);

    /**
     * @brief
     *
     * @param image
     * @param autoMipMaps
     * @return QSharedPointer<TextureImageData>
     */
    static QSharedPointer<TextureImageData> compressImageDXT(const QImage &image, bool autoMipMaps = true);

    /**
     * @brief
     *
     * @param data
     * @param skipMipLevels
     * @return QSharedPointer<TextureImageData>
     */
    static QSharedPointer<TextureImageData> loadDDS(const QByteArray &data, int skipMipLevels = 0);

    /**
     * @brief
     * DXT1图像压缩（SSE2版本）
     * @param inBuf
     * 源图像数据（RGBA）
     * @param outBuf
     * 压缩完成后的数据
     * @param width
     * 图像宽度
     * @param height
     * 图像高度
     * @param rowPitch
     * 一行图像数据的字节大小
     */
    static void CompressImageDXT1SSE2(const quint8* inBuf, quint8* outBuf, int width, int height, unsigned int rowPitch = 0);

    /**
     * @brief
     * DXT5图像压缩（SSE2版本）
     * @param inBuf
     * 源图像数据（RGBA）
     * @param outBuf
     * 压缩完成后的数据
     * @param width
     * 图像宽度
     * @param height
     * 图像高度
     * @param rowPitch
     * 一行图像数据的字节大小
     */
    static void CompressImageDXT5SSE2(const quint8* inBuf, quint8* outBuf, int width, int height, unsigned int rowPitch = 0);
};

#endif // LITEXTUREUTIL_H
