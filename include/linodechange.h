#ifndef LINODECHANGE_H
#define LINODECHANGE_H

#include "linodeid.h"

class LiNode;
class LiNodeChangeBasePrivate;

class LICORE_EXPORT LiNodeChangeBase
{
public:
    explicit LiNodeChangeBase(const LiNode *node);
    ~LiNodeChangeBase();

    LiNodeId subjectId() const;

private:
    LiNodeChangeBasePrivate *d;
};

typedef QSharedPointer<LiNodeChangeBase> LiNodeChangeBasePtr;

template<typename T>
class LICORE_EXPORT LiNodeChange : public LiNodeChangeBase
{
public:
    explicit LiNodeChange(const LiNode *node)
        : LiNodeChangeBase(node)
        , data()
    {
    }

    T data;
};

template<typename T>
using LiNodeChangePtr = QSharedPointer<LiNodeChange<T>>;

#endif // LINODECHANGE_H
