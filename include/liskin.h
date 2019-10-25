#ifndef LISKIN_H
#define LISKIN_H

#include "licomponent.h"
#include "matrix4.h"

class LiEntity;
class LiSkinPrivate;

class LICORE_EXPORT LiSkin : public LiComponent
{
    Q_OBJECT
public:
    explicit LiSkin(LiNode *parent = nullptr);

    LiEntity *skeleton() const;
    void setSkeleton(LiEntity *skeleton);

    Matrix4 bindShapeMatrix() const;
    void setBindShapeMatrix(const Matrix4 &matrix);

    QVector<Matrix4> offsetMatrices() const;
    void setOffsetMatrices(const QVector<Matrix4> &matrices);

    QVector<LiEntity *> joints() const;
    void setJoints(const QVector<LiEntity *> &joints);

    QVector<LiEntity *> targets() const;
    void addTarget(LiEntity *target);
    void removeTarget(LiEntity *target);

signals:
    void skeletonChanged();
    void bindShapeMatrixChanged();
    void offsetMatricesChanged();
    void jointsChanged();
    void targetsChanged();

private:
    Q_DECLARE_PRIVATE(LiSkin)
};

#endif // LISKIN_H
