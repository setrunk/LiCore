#ifndef LINODEID_H
#define LINODEID_H

#include "licore_global.h"

class LiNodeId
{
    explicit LiNodeId(quint64 i)
        : m_id(i)
    {}
public:
    LiNodeId()
        : m_id(0)
    {}

    LICORE_EXPORT static LiNodeId createId();

    bool isNull() const
    {
        return m_id == 0;
    }

    bool operator ==(LiNodeId other) const
    {
        return other.m_id == m_id;
    }

    bool operator !=(LiNodeId other) const
    {
        return !operator ==(other);
    }

    bool operator <(LiNodeId other) const
    {
        return m_id < other.m_id;
    }

    bool operator >(LiNodeId other) const
    {
        return m_id > other.m_id;
    }

    quint64 id() const
    {
        return m_id;
    }

    operator bool() const
    {
        return m_id != 0;
    }

private:
    quint64 m_id;
};

Q_DECLARE_METATYPE(LiNodeId)
Q_DECLARE_TYPEINFO(LiNodeId, Q_PRIMITIVE_TYPE);

typedef QVector<LiNodeId> LiNodeIdVector;

inline uint qHash(LiNodeId id, uint seed = 0)
{
    using QT_PREPEND_NAMESPACE(qHash);
    return qHash(id.id(), seed);
}

#endif // LINODEID_H
