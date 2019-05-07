#ifndef QGSMAPPROJECTION_H
#define QGSMAPPROJECTION_H

#include "liextrasglobal.h"
#include "mapprojection.h"
#include "qgscoordinatereferencesystem.h"
#include "qgscoordinatetransform.h"

class QgsMapProjection : public MapProjection
{
public:
    explicit QgsMapProjection(const QgsCoordinateReferenceSystem &crs);

    Cartesian3 project(const Cartographic &cartographic) const;
    Cartographic unproject(const Cartesian3 &cartesian) const;

private:
    QgsCoordinateReferenceSystem m_crs;
};

#endif // QGSMAPPROJECTION_H
