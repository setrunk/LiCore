#ifndef LIPICKID_H
#define LIPICKID_H

#include "licore_global.h"

class LICORE_EXPORT LiPickId
{
public:
    explicit LiPickId(uint id = 0);

    uint id() const { return m_id; }
    bool isNull() const { return m_id == 0; }
    QColor color() const;
    static LiPickId fromColor(const QColor &color);

private:
    uint m_id = 0;
};

Q_DECLARE_METATYPE(LiPickId)

#endif // LIPICKID_H
