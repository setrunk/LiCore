#ifndef LIPICKID_H
#define LIPICKID_H

#include "licore_global.h"

class LICORE_EXPORT LiPickId
{
public:
    explicit LiPickId(uint key = 0);

    uint key() const { return m_key; }
    QColor color() const;

private:
    uint m_key = 0;
};

Q_DECLARE_METATYPE(LiPickId)

#endif // LIPICKID_H
