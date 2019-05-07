#ifndef LITREE_H
#define LITREE_H

#include "licomponent.h"

class LiTreePrivate;

class LICORE_EXPORT LiTree : public LiComponent
{
    Q_OBJECT
public:
    explicit LiTree(LiNode *parent = nullptr);

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(LiTree)
};

#endif // LITREE_H
