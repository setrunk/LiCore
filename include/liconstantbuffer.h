#ifndef LICONSTANTBUFFER_H
#define LICONSTANTBUFFER_H

#include "linode.h"

class LiConstantBufferPrivate;
class LiParameter;
class LiBuffer;

class LiConstantBuffer : public LiNode
{
    Q_OBJECT
public:
    explicit LiConstantBuffer(LiNode *parent = 0);

    QString bufferName() const;
    void setBufferName(const QString &name);

    void addParameter(LiParameter *param);
    void removeParameter(LiParameter *param);
    QVector<LiParameter *> parameters() const;

    LiNodeChangeBasePtr createChangePtr() const Q_DECL_OVERRIDE;

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(LiConstantBuffer)
};

#endif // LICONSTANTBUFFER_H
