#ifndef LI_GLOBAL_H
#define LI_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore>
#include <QtGui>

# if defined(LIENGINE_LIBRARY)
#   define LICORE_EXPORT Q_DECL_EXPORT
# else
#   define LICORE_EXPORT Q_DECL_IMPORT
# endif

#define SAFE_DELETE(p)          { if (p) { delete (p);		(p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] (p);	(p)=NULL; } }
#define SAFE_RELEASE(p)         { if (p) { (p)->release();	(p)=NULL; } }

#endif // LI_GLOBAL_H
