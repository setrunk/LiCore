#ifndef __LI_TEXTURE_H_INCLUDED__
#define __LI_TEXTURE_H_INCLUDED__

#include "linode.h"

class LiTextureImage;
class LiTexturePrivate;

/**
 * @brief
 * LiTexture时渲染模块的核心类，提供操作OpenGL纹理的封装。
 */
class LICORE_EXPORT LiTexture : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(Target target READ target CONSTANT)
    Q_PROPERTY(TextureFormat format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(int layers READ layers WRITE setLayers NOTIFY layersChanged)
    Q_PROPERTY(int samples READ samples WRITE setSamples NOTIFY samplesChanged)
    Q_PROPERTY(bool generateMipMaps READ generateMipMaps WRITE setGenerateMipMaps NOTIFY generateMipMapsChanged)
    Q_PROPERTY(float maximumAnisotropy READ maximumAnisotropy WRITE setMaximumAnisotropy NOTIFY maximumAnisotropyChanged)
    Q_PROPERTY(WrapMode wrapModeS READ wrapModeS WRITE setWrapModeS NOTIFY wrapModeSChanged)
    Q_PROPERTY(WrapMode wrapModeT READ wrapModeT WRITE setWrapModeT NOTIFY wrapModeTChanged)
    Q_PROPERTY(Filter magnificationFilter READ magnificationFilter WRITE setMagnificationFilter NOTIFY magnificationFilterChanged)
    Q_PROPERTY(Filter minificationFilter READ minificationFilter WRITE setMinificationFilter NOTIFY minificationFilterChanged)
    Q_PROPERTY(ComparisonFunction comparisonFunction READ comparisonFunction WRITE setComparisonFunction NOTIFY comparisonFunctionChanged)
    Q_PROPERTY(ComparisonMode comparisonMode READ comparisonMode WRITE setComparisonMode NOTIFY comparisonModeChanged)
    Q_PROPERTY(QQmlListProperty<LiTextureImage> textureImages READ qmlTextureImages)

public:
    /**
     * @brief
     * 对象当前的内部状态
     */
    enum Status {
        None = 0, // 未初始化
        Loading, // 正在加载外部资源
        Ready, // 完成状态
        Error
    };
    Q_ENUM(Status) // LCOV_EXCL_LINE

    /**
     * @brief
     * 纹理目标的类型，对应OpenGL的目标类型
     */
    enum Target {
        TargetAutomatic            = 0,         // Target will be determined by the engine
        Target1D                   = 0x0DE0,    // GL_TEXTURE_1D
        Target1DArray              = 0x8C18,    // GL_TEXTURE_1D_ARRAY
        Target2D                   = 0x0DE1,    // GL_TEXTURE_2D
        Target2DArray              = 0x8C1A,    // GL_TEXTURE_2D_ARRAY
        Target3D                   = 0x806F,    // GL_TEXTURE_3D
        TargetCubeMap              = 0x8513,    // GL_TEXTURE_CUBE_MAP
        TargetCubeMapArray         = 0x9009,    // GL_TEXTURE_CUBE_MAP_ARRAY
        Target2DMultisample        = 0x9100,    // GL_TEXTURE_2D_MULTISAMPLE
        Target2DMultisampleArray   = 0x9102,    // GL_TEXTURE_2D_MULTISAMPLE_ARRAY
        TargetRectangle            = 0x84F5,    // GL_TEXTURE_RECTANGLE
        TargetBuffer               = 0x8C2A     // GL_TEXTURE_BUFFER
    };
    Q_ENUM(Target) // LCOV_EXCL_LINE

    /**
     * @brief
     * 纹理格式，对应OpenGL纹理格式
     */
    enum TextureFormat {
        NoFormat               = 0,         // GL_NONE
        Automatic              = 1,         // The engine automatically determines the best format

        // Unsigned normalized formats
        R8_UNorm               = 0x8229,    // GL_R8
        RG8_UNorm              = 0x822B,    // GL_RG8
        RGB8_UNorm             = 0x8051,    // GL_RGB8
        RGBA8_UNorm            = 0x8058,    // GL_RGBA8

        R16_UNorm              = 0x822A,    // GL_R16
        RG16_UNorm             = 0x822C,    // GL_RG16
        RGB16_UNorm            = 0x8054,    // GL_RGB16
        RGBA16_UNorm           = 0x805B,    // GL_RGBA16

        // Signed normalized formats
        R8_SNorm               = 0x8F94,    // GL_R8_SNORM
        RG8_SNorm              = 0x8F95,    // GL_RG8_SNORM
        RGB8_SNorm             = 0x8F96,    // GL_RGB8_SNORM
        RGBA8_SNorm            = 0x8F97,    // GL_RGBA8_SNORM

        R16_SNorm              = 0x8F98,    // GL_R16_SNORM
        RG16_SNorm             = 0x8F99,    // GL_RG16_SNORM
        RGB16_SNorm            = 0x8F9A,    // GL_RGB16_SNORM
        RGBA16_SNorm           = 0x8F9B,    // GL_RGBA16_SNORM

        // Unsigned integer formats
        R8U                    = 0x8232,    // GL_R8UI
        RG8U                   = 0x8238,    // GL_RG8UI
        RGB8U                  = 0x8D7D,    // GL_RGB8UI
        RGBA8U                 = 0x8D7C,    // GL_RGBA8UI

        R16U                   = 0x8234,    // GL_R16UI
        RG16U                  = 0x823A,    // GL_RG16UI
        RGB16U                 = 0x8D77,    // GL_RGB16UI
        RGBA16U                = 0x8D76,    // GL_RGBA16UI

        R32U                   = 0x8236,    // GL_R32UI
        RG32U                  = 0x823C,    // GL_RG32UI
        RGB32U                 = 0x8D71,    // GL_RGB32UI
        RGBA32U                = 0x8D70,    // GL_RGBA32UI

        // Signed integer formats
        R8I                    = 0x8231,    // GL_R8I
        RG8I                   = 0x8237,    // GL_RG8I
        RGB8I                  = 0x8D8F,    // GL_RGB8I
        RGBA8I                 = 0x8D8E,    // GL_RGBA8I

        R16I                   = 0x8233,    // GL_R16I
        RG16I                  = 0x8239,    // GL_RG16I
        RGB16I                 = 0x8D89,    // GL_RGB16I
        RGBA16I                = 0x8D88,    // GL_RGBA16I

        R32I                   = 0x8235,    // GL_R32I
        RG32I                  = 0x823B,    // GL_RG32I
        RGB32I                 = 0x8D83,    // GL_RGB32I
        RGBA32I                = 0x8D82,    // GL_RGBA32I

        // Floating point formats
        R16F                   = 0x822D,    // GL_R16F
        RG16F                  = 0x822F,    // GL_RG16F
        RGB16F                 = 0x881B,    // GL_RGB16F
        RGBA16F                = 0x881A,    // GL_RGBA16F

        R32F                   = 0x822E,    // GL_R32F
        RG32F                  = 0x8230,    // GL_RG32F
        RGB32F                 = 0x8815,    // GL_RGB32F
        RGBA32F                = 0x8814,    // GL_RGBA32F

        // Packed formats
        RGB9E5                 = 0x8C3D,    // GL_RGB9_E5
        RG11B10F               = 0x8C3A,    // GL_R11F_G11F_B10F
        RG3B2                  = 0x2A10,    // GL_R3_G3_B2
        R5G6B5                 = 0x8D62,    // GL_RGB565
        RGB5A1                 = 0x8057,    // GL_RGB5_A1
        RGBA4                  = 0x8056,    // GL_RGBA4
        RGB10A2                = 0x906F,    // GL_RGB10_A2UI

        // Depth formats
        D16                    = 0x81A5,    // GL_DEPTH_COMPONENT16
        D24                    = 0x81A6,    // GL_DEPTH_COMPONENT24
        D24S8                  = 0x88F0,    // GL_DEPTH24_STENCIL8
        D32                    = 0x81A7,    // GL_DEPTH_COMPONENT32
        D32F                   = 0x8CAC,    // GL_DEPTH_COMPONENT32F
        D32FS8X24              = 0x8CAD,    // GL_DEPTH32F_STENCIL8

        // Compressed formats
        RGB_DXT1               = 0x83F0,    // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
        RGBA_DXT1              = 0x83F1,    // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        RGBA_DXT3              = 0x83F2,    // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        RGBA_DXT5              = 0x83F3,    // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        R_ATI1N_UNorm          = 0x8DBB,    // GL_COMPRESSED_RED_RGTC1
        R_ATI1N_SNorm          = 0x8DBC,    // GL_COMPRESSED_SIGNED_RED_RGTC1
        RG_ATI2N_UNorm         = 0x8DBD,    // GL_COMPRESSED_RG_RGTC2
        RG_ATI2N_SNorm         = 0x8DBE,    // GL_COMPRESSED_SIGNED_RG_RGTC2
        RGB_BP_UNSIGNED_FLOAT  = 0x8E8F,    // GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB
        RGB_BP_SIGNED_FLOAT    = 0x8E8E,    // GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB
        RGB_BP_UNorm           = 0x8E8C,    // GL_COMPRESSED_RGBA_BPTC_UNORM_ARB
        R11_EAC_UNorm          = 0x9270,    // GL_COMPRESSED_R11_EAC
        R11_EAC_SNorm          = 0x9271,    // GL_COMPRESSED_SIGNED_R11_EAC
        RG11_EAC_UNorm         = 0x9272,    // GL_COMPRESSED_RG11_EAC
        RG11_EAC_SNorm         = 0x9273,    // GL_COMPRESSED_SIGNED_RG11_EAC
        RGB8_ETC2              = 0x9274,    // GL_COMPRESSED_RGB8_ETC2
        SRGB8_ETC2             = 0x9275,    // GL_COMPRESSED_SRGB8_ETC2
        RGB8_PunchThrough_Alpha1_ETC2 = 0x9276, // GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
        SRGB8_PunchThrough_Alpha1_ETC2 = 0x9277, // GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
        RGBA8_ETC2_EAC         = 0x9278,    // GL_COMPRESSED_RGBA8_ETC2_EAC
        SRGB8_Alpha8_ETC2_EAC  = 0x9279,    // GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
        RGB8_ETC1              = 0x8D64,    // GL_ETC1_RGB8_OES

        // sRGB formats
        SRGB8                  = 0x8C41,    // GL_SRGB8
        SRGB8_Alpha8           = 0x8C43,    // GL_SRGB8_ALPHA8
        SRGB_DXT1              = 0x8C4C,    // GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
        SRGB_Alpha_DXT1        = 0x8C4D,    // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
        SRGB_Alpha_DXT3        = 0x8C4E,    // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
        SRGB_Alpha_DXT5        = 0x8C4F,    // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
        SRGB_BP_UNorm          = 0x8E8D,    // GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB

        // ES 2 formats
        DepthFormat            = 0x1902,    // GL_DEPTH_COMPONENT
        AlphaFormat            = 0x1906,    // GL_ALPHA
        RGBFormat              = 0x1907,    // GL_RGB
        RGBAFormat             = 0x1908,    // GL_RGBA
        LuminanceFormat        = 0x1909,    // GL_LUMINANCE
        LuminanceAlphaFormat   = 0x190A
    };
    Q_ENUM(TextureFormat) // LCOV_EXCL_LINE

    /**
     * @brief
     * 纹理重复的方式
     */
    enum WrapMode {
        Repeat         = 0x2901, // GL_REPEAT
        MirroredRepeat = 0x8370, // GL_MIRRORED_REPEAT
        ClampToEdge    = 0x812F, // GL_CLAMP_TO_EDGE
        ClampToBorder  = 0x812D  // GL_CLAMP_TO_BORDER
    };
    Q_ENUM(WrapMode) // LCOV_EXCL_LINE

    /**
     * @brief
     * 纹理采样的方式
     */
    enum Filter {
        Nearest                 = 0x2600,   // GL_NEAREST
        Linear                  = 0x2601,   // GL_LINEAR
        NearestMipMapNearest    = 0x2700,   // GL_NEAREST_MIPMAP_NEAREST
        NearestMipMapLinear     = 0x2702,   // GL_NEAREST_MIPMAP_LINEAR
        LinearMipMapNearest     = 0x2701,   // GL_LINEAR_MIPMAP_NEAREST
        LinearMipMapLinear      = 0x2703    // GL_LINEAR_MIPMAP_LINEAR
    };
    Q_ENUM(Filter) // LCOV_EXCL_LINE

    /**
     * @brief
     * CubeMap的6个面
     */
    enum CubeMapFace {
        CubeMapPositiveX = 0x8515,  // GL_TEXTURE_CUBE_MAP_POSITIVE_X
        CubeMapNegativeX = 0x8516,  // GL_TEXTURE_CUBE_MAP_NEGATIVE_X
        CubeMapPositiveY = 0x8517,  // GL_TEXTURE_CUBE_MAP_POSITIVE_Y
        CubeMapNegativeY = 0x8518,  // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
        CubeMapPositiveZ = 0x8519,  // GL_TEXTURE_CUBE_MAP_POSITIVE_Z
        CubeMapNegativeZ = 0x851A,  // GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        AllFaces
    };
    Q_ENUM(CubeMapFace) // LCOV_EXCL_LINE

    /**
     * @brief
     * 纹理采样比较操作的函数
     */
    enum ComparisonFunction {
        CompareLessEqual    = 0x0203,   // GL_LEQUAL
        CompareGreaterEqual = 0x0206,   // GL_GEQUAL
        CompareLess         = 0x0201,   // GL_LESS
        CompareGreater      = 0x0204,   // GL_GREATER
        CompareEqual        = 0x0202,   // GL_EQUAL
        CommpareNotEqual    = 0x0205,   // GL_NOTEQUAL
        CompareAlways       = 0x0207,   // GL_ALWAYS
        CompareNever        = 0x0200    // GL_NEVER
    };
    Q_ENUM(ComparisonFunction) // LCOV_EXCL_LINE

    /**
     * @brief
     * 纹理采样比较操作的方式
     */
    enum ComparisonMode {
        CompareRefToTexture = 0x884E,   // GL_COMPARE_REF_TO_TEXTURE
        CompareNone         = 0x0000    // GL_NONE
    };
    Q_ENUM(ComparisonMode) // LCOV_EXCL_LINE

    /**
     * @brief
     * 深度纹理当作普通纹理采样时的方式
     */
    enum DepthStencilMode {
        DepthMode   = 0x1902,   // GL_DEPTH_COMPONENT
        StencilMode = 0x1901    // GL_STENCIL_INDEX
    };
    Q_ENUM(DepthStencilMode)

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiTexture(LiNode *parent = nullptr);

    /**
     * @brief
     * 构造函数
     * @param target
     * 指定哪种目标类型
     * @param parent
     */
    explicit LiTexture(Target target, LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiTexture();

    /**
     * @brief
     * 返回对象当前的状态
     * @return Status
     */
    Status status() const;

    /**
     * @brief
     * 返回对象目标的类型
     * @return Target
     */
    Target target() const;

    /**
     * @brief
     * 返回对象当前的纹理格式
     * @return TextureFormat
     */
    TextureFormat format() const;

    /**
     * @brief
     * 返回该纹理是否有Alpha通道
     * @return bool
     */
    bool hasAlpha() const;

    /**
     * @brief
     * 返回纹理的宽度
     * @return int
     */
    int width() const;

    /**
     * @brief
     * 返回纹理的高度
     * @return int
     */
    int height() const;

    /**
     * @brief
     * 返回纹理的大小尺寸
     * @return QSize
     */
    QSize size() const;

    /**
     * @brief
     * 返回3D纹理的深度，2D纹理深度为1
     * @return int
     */
    int depth() const;

    /**
     * @brief
     * 返回纹理阵列的层数，一般纹理层数为1
     * @return int
     */
    int layers() const;

    /**
     * @brief
     * 返回纹理的超级采样数量
     * @return int
     */
    int samples() const;

    /**
     * @brief
     * 返回纹理是否自动生成MipMap链
     * @return bool
     */
    bool generateMipMaps() const;

    /**
     * @brief
     * 返回纹理采样时的最大各向异性值
     * @return float
     */
    float maximumAnisotropy() const;

    /**
     * @brief
     * 返回纹理S方向的重复方式
     * @return WrapMode
     */
    WrapMode wrapModeS() const;

    /**
     * @brief
     * 返回纹理T方向的重复方式
     * @return WrapMode
     */
    WrapMode wrapModeT() const;

    /**
     * @brief
     * 返回纹理R方向的重复方式
     * @return WrapMode
     */
    WrapMode wrapModeR() const;

    /**
     * @brief
     * 返回纹理缩小采样的方式
     * @return Filter
     */
    Filter minificationFilter() const;

    /**
     * @brief
     * 返回纹理放大采样的方式
     * @return Filter
     */
    Filter magnificationFilter() const;

    /**
     * @brief
     * 返回纹理比较操作的函数
     * @return ComparisonFunction
     */
    ComparisonFunction comparisonFunction() const;

    /**
     * @brief
     * 返回纹理比较操作的方式
     * @return ComparisonMode
     */
    ComparisonMode comparisonMode() const;

    /**
     * @brief
     * 返回深度纹理采样的方式
     * @return DepthStencilMode
     */
    DepthStencilMode depthStencilMode() const;

    /**
     * @brief
     * 添加纹理图像数据
     * @param image
     */
    void addTextureImage(LiTextureImage *image);

    /**
     * @brief
     * 移除纹理图像数据
     * @param image
     */
    void removeTextureImage(LiTextureImage *image);

    /**
     * @brief
     * 返回纹理所有的图像数据合集
     * @return QVector<LiTextureImage *>
     */
    QVector<LiTextureImage *> textureImages() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return QQmlListProperty<LiTextureImage>
     */
    QQmlListProperty<LiTextureImage> qmlTextureImages();

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    virtual LiNodeChangeBasePtr createChangePtr() const Q_DECL_OVERRIDE;

public slots:
    /**
     * @brief
     * 设置纹理的尺寸
     * @param width
     * 纹理宽度
     * @param height
     * 纹理高度
     * @param depth
     * 纹理深度，创建3D纹理时使用的参数
     */
    void setSize(int width, int height, int depth=1);

    /**
     * @brief
     * 设置纹理的尺寸
     * @param size
     */
    void setSize(const QSize &size);

    /**
     * @brief
     * 设置纹理的格式
     * @param format
     */
    void setFormat(TextureFormat format);

    /**
     * @brief
     * 设置纹理是否自动生成MipMap链
     * @param gen
     */
    void setGenerateMipMaps(bool gen);

    /**
     * @brief
     * 设置纹理的宽度
     * @param width
     */
    void setWidth(int width);

    /**
     * @brief
     * 设置纹理的高度
     * @param height
     */
    void setHeight(int height);

    /**
     * @brief
     * 设置纹理的深度
     * @param depth
     */
    void setDepth(int depth);

    /**
     * @brief
     * 设置纹理的层数
     * @param layers
     */
    void setLayers(int layers);

    /**
     * @brief
     * 设置纹理的超级采样数量
     * @param samples
     */
    void setSamples(int samples);

    /**
     * @brief
     * 设置纹理采样S方向的重复方式
     * @param wrapMode
     */
    void setWrapModeS(WrapMode wrapMode);

    /**
     * @brief
     * 设置纹理采样T方向的重复方式
     * @param wrapMode
     */
    void setWrapModeT(WrapMode wrapMode);

    /**
     * @brief
     * 设置纹理采样R方向的重复方式
     * @param wrapMode
     */
    void setWrapModeR(WrapMode wrapMode);

    /**
     * @brief
     * 设置纹理缩小采样方式
     * @param f
     */
    void setMinificationFilter(Filter f);

    /**
     * @brief
     * 设置纹理放大采样方式
     * @param f
     */
    void setMagnificationFilter(Filter f);

    /**
     * @brief
     * 设置纹理各向异性采样的最大值
     * @param anisotropy
     */
    void setMaximumAnisotropy(float anisotropy);

    /**
     * @brief
     * 设置纹理比较操作的函数
     * @param function
     */
    void setComparisonFunction(ComparisonFunction function);

    /**
     * @brief
     * 设置纹理比较操作的方式
     * @param mode
     */
    void setComparisonMode(ComparisonMode mode);

    /**
     * @brief
     * 设置深度纹理采样的方式
     * @param mode
     */
    void setDepthStencilMode(DepthStencilMode mode);

signals:
    /**
     * @brief
     * 纹理内部状态改变时，发出该信号
     * @param status
     */
    void statusChanged(Status status);

    /**
     * @brief
     * 纹理格式改变时，发出该信号
     * @param format
     */
    void formatChanged(TextureFormat format);

    /**
     * @brief
     * 纹理自动生成MipMap链属性值改变时，发出该信号
     * @param generateMipMaps
     */
    void generateMipMapsChanged(bool generateMipMaps);

    /**
     * @brief
     * 纹理宽度改变时，发出该信号
     * @param width
     */
    void widthChanged(int width);

    /**
     * @brief
     * 纹理高度改变时，发出该信号
     * @param height
     */
    void heightChanged(int height);

    /**
     * @brief
     * 纹理深度改变时，发出该信号
     * @param depth
     */
    void depthChanged(int depth);

    /**
     * @brief
     * 纹理采样S方向重复方式改变时，发出该信号
     * @param mode
     */
    void wrapModeSChanged(WrapMode mode);

    /**
     * @brief
     * 纹理采样T方向重复方式改变时，发出该信号
     * @param mode
     */
    void wrapModeTChanged(WrapMode mode);

    /**
     * @brief
     * 纹理采样R方向重复方式改变时，发出该信号
     * @param mode
     */
    void wrapModeRChanged(WrapMode mode);

    /**
     * @brief
     * 纹理缩小采样方式改变时，发出该信号
     * @param magnificationFilter
     */
    void magnificationFilterChanged(Filter magnificationFilter);

    /**
     * @brief
     * 纹理放大采样方式改变时，发出该信号
     * @param minificationFilter
     */
    void minificationFilterChanged(Filter minificationFilter);

    /**
     * @brief
     * 纹理各向异性采样最大值改变时，发出该信号
     * @param maximumAnisotropy
     */
    void maximumAnisotropyChanged(float maximumAnisotropy);

    /**
     * @brief
     * 纹理比较操作函数改变时，发出该信号
     * @param comparisonFunction
     */
    void comparisonFunctionChanged(ComparisonFunction comparisonFunction);

    /**
     * @brief
     * 纹理比较操作方式改变时，发出该信号
     * @param comparisonMode
     */
    void comparisonModeChanged(ComparisonMode comparisonMode);

    /**
     * @brief
     * 纹理层数改变时，发出该信号
     * @param layers
     */
    void layersChanged(int layers);

    /**
     * @brief
     * 纹理超级采样数量改变时，发出该信号
     * @param samples
     */
    void samplesChanged(int samples);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiTexture(LiTexturePrivate &dd, LiNode *parent = nullptr);

    /**
     * @brief
     * 设置纹理内部状态
     * @param status
     */
    void setStatus(Status status);

private:
    Q_DECLARE_PRIVATE(LiTexture)
};


/**
 * @brief
 * 一维纹理
 */
class LICORE_EXPORT LiTexture1D : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTexture1D(LiNode *parent = nullptr);
    ~LiTexture1D();
};

/**
 * @brief
 * 一维纹理阵列
 */
class LICORE_EXPORT LiTexture1DArray : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTexture1DArray(LiNode *parent = nullptr);
    ~LiTexture1DArray();
};

/**
 * @brief
 * 二维纹理
 */
class LICORE_EXPORT LiTexture2D : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTexture2D(LiNode *parent = nullptr);
    ~LiTexture2D();
};

/**
 * @brief
 * 二维纹理阵列
 */
class LICORE_EXPORT LiTexture2DArray : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTexture2DArray(LiNode *parent = nullptr);
    ~LiTexture2DArray();
};

/**
 * @brief
 * 立方体纹理
 */
class LICORE_EXPORT LiTextureCubeMap : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTextureCubeMap(LiNode *parent = nullptr);
    ~LiTextureCubeMap();
};

/**
 * @brief
 * 三维纹理
 */
class LICORE_EXPORT LiTexture3D : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTexture3D(LiNode *parent = nullptr);
    ~LiTexture3D();
};

/**
 * @brief
 * 缓存纹理
 */
class LICORE_EXPORT LiTextureBuffer : public LiTexture
{
    Q_OBJECT
public:
    explicit LiTextureBuffer(LiNode *parent = nullptr);
    ~LiTextureBuffer();
};

#endif
