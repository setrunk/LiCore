#ifndef NODECONNECTIONS_H
#define NODECONNECTIONS_H

#include "licore_global.h"

class LICORE_EXPORT NodeConnections
{
public:
    NodeConnections() {}

    ~NodeConnections()
    {
        auto it = connections.cbegin();
        for (; it != connections.cend(); ++it)
        {
            const auto &l = it.value();
            for (const auto &c : l)
            {
                QObject::disconnect(c);
            }
        }
    }

    void insert(void* key, const QMetaObject::Connection &c)
    {
        if (connections.contains(key)) {
            connections[key].append(c);
        } else {
            QList<QMetaObject::Connection> l;
            l.append(c);
            connections.insert(key, l);
        }
    }

    void remove(void* key, const QMetaObject::Connection &c)
    {
        QObject::disconnect(c);
        connections[key].removeOne(c);
    }

    void removeAll(void* key)
    {
        const auto l = connections.take(key);
        for (const auto &c : l)
            QObject::disconnect(c);
    }

private:
    QHash<void*, QList<QMetaObject::Connection>> connections;
};

#endif // NODECONNECTIONS_H
