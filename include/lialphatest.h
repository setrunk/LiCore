#ifndef LIALPHATEST_H
#define LIALPHATEST_H

#include "lirenderstate.h"

class LiAlphaTestPrivate;

class LICORE_EXPORT LiAlphaTest : public LiRenderState
{
    Q_OBJECT
    Q_PROPERTY(AlphaFunction alphaFunction READ alphaFunction WRITE setAlphaFunction NOTIFY alphaFunctionChanged)
    Q_PROPERTY(float referenceValue READ referenceValue WRITE setReferenceValue NOTIFY referenceValueChanged)
public:

    enum AlphaFunction {
        Never = 0x0200,
        Always = 0x0207,
        Less = 0x0201,
        LessOrEqual = 0x0203,
        Equal = 0x0202,
        GreaterOrEqual = 0x0206,
        Greater = 0x0204,
        NotEqual = 0x0205
    };
    Q_ENUM(AlphaFunction) // LCOV_EXCL_LINE

    explicit LiAlphaTest(LiNode *parent = nullptr);
    ~LiAlphaTest();

    AlphaFunction alphaFunction() const;
    float referenceValue() const;

public Q_SLOTS:
    void setAlphaFunction(AlphaFunction alphaFunction);
    void setReferenceValue(float referenceValue);

Q_SIGNALS:
    void alphaFunctionChanged(AlphaFunction alphaFunction);
    void referenceValueChanged(float referenceValue);

private:
    Q_DECLARE_PRIVATE(LiAlphaTest)
};

#endif // LIALPHATEST_H
