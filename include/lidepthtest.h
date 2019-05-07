#ifndef LIDEPTHTEST_H
#define LIDEPTHTEST_H

#include "lirenderstate.h"

class LiDepthTestPrivate;

class LICORE_EXPORT LiDepthTest : public LiRenderState
{
    Q_OBJECT
    Q_PROPERTY(DepthFunction depthFunction READ depthFunction WRITE setDepthFunction NOTIFY depthFunctionChanged)
public:

    enum DepthFunction {
        Never = 0x0200,
        Always = 0x0207,
        Less = 0x0201,
        LessOrEqual = 0x0203,
        Equal = 0x0202,
        GreaterOrEqual = 0x0206,
        Greater = 0x0204,
        NotEqual = 0x0205
    };
    Q_ENUM(DepthFunction) // LCOV_EXCL_LINE

    explicit LiDepthTest(LiNode *parent = nullptr);
    ~LiDepthTest();

    DepthFunction depthFunction() const;

public Q_SLOTS:
    void setDepthFunction(DepthFunction depthFunction);

Q_SIGNALS:
    void depthFunctionChanged(DepthFunction depthFunction);

private:
    Q_DECLARE_PRIVATE(LiDepthTest)
};

#endif // LIDEPTHTEST_H
