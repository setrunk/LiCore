#ifndef LIEXTRASGLOBAL_H
#define LIEXTRASGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore>
#include <QtGui>

# if defined(LIEXTRAS_LIBRARY)
#   define LIEXTRAS_EXPORT Q_DECL_EXPORT
# else
#   define LIEXTRAS_EXPORT Q_DECL_IMPORT
# endif

#endif // LIEXTRASGLOBAL_H
