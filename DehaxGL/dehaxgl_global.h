#ifndef DEHAXGL_GLOBAL_H
#define DEHAXGL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEHAXGL_LIBRARY)
#  define DEHAXGLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DEHAXGLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DEHAXGL_GLOBAL_H
