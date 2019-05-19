#ifndef PMTSCAPABILITIES_H
#define PMTSCAPABILITIES_H

#include "liextrasglobal.h"
#include "asyncfuture.h"

class LIEXTRAS_EXPORT PMTSCapabilities
{
public:
    explicit PMTSCapabilities(const QString &url);

    QFuture<void> readyPromise() const { return m_defer.future(); }

    QStringList modelUrls() const { return m_modelUrls; }

private:
    Deferred<void> m_defer;
    QStringList m_modelUrls;
};

#endif // PMTSCAPABILITIES_H
