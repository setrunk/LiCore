#include <QApplication>
#include <QtCore>
#include <QtQml>
#include <QMainWindow>

#include <liviewer.h>
#include <liwidget.h>
#include <liengine.h>
#include <liscene.h>
#include <globe.h>
#include <terrainprovider.h>
#include <terrainsurfacelayer.h>
#include <imagerylayer.h>
#include <asyncfuture.h>
#include <litimesystem.h>

#include <lientity.h>
#include <licomponent.h>
#include <libehavior.h>
#include <litransform.h>
#include <ligeometryrenderer.h>
#include <licamera.h>
#include <lilight.h>
#include <lisun.h>

#include <libuffer.h>
#include <ligeometry.h>
#include <ligeometryattribute.h>
#include <liboxgeometry.h>

#include <liparameter.h>
#include <limaterial.h>
#include <lishaderprogram.h>
#include <lirenderstate.h>

#include <litexture.h>
#include <litextureimage.h>
#include <lirendertarget.h>
#include <lirendertargetoutput.h>
#include <lipostprocess.h>
#include <lifullscreenquad.h>
#include <liraycasthit.h>
#include <liframeaction.h>
#include <liambientocclusion.h>
#include <litonemapping.h>
#include <litextureprojection.h>

#include <lisceneiofactory.h>
#include <lisceneloader.h>
#include <li3dtileset.h>
#include <liforest.h>

#include <liinputsystem.h>
#include <liscriptengine.h>

// LiExtras
#include <qgsfeature.h>
#include <gisimageryprovider.h>
#include <wmsimageryprovider.h>
#include <transformhelper.h>

#include "sample.h"
#include "orthographicfrustum.h"
#include "perspectivefrustum.h"

auto clamp(int v, int minV, int maxV) -> int {
    if (v < minV) return minV;
    if (v > maxV) return maxV;
    return v;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    PerspectiveFrustum frus;
//    frus.setNearPlane(100);
//    frus.setFarPlane(1000);
//    Vector3 v1(10, 20, -100.0001);
//    v1 = frus.projectionMatrix() * v1;
//    Vector3 v2(10, 20, -99.9);
//    v2 = frus.projectionMatrix() * v2;
//    Vector3 v3(10, 20, -1001);
//    v3 = frus.projectionMatrix() * v3;
//    Vector3 v4(10, 20, -500);
//    v4 = frus.projectionMatrix() * v4;

    qRegisterMetaType<QgsFeature>("QgsFeature");
    QgsApplication::init();
    QgsApplication::initQgis();

    const char *uri = "LiQuick.Core";
    qmlRegisterUncreatableType<LiNode>(uri, 1, 0, "Node", QLatin1String("Node is a base class"));
    qmlRegisterUncreatableType<LiComponent>(uri, 1, 0, "Component3D", QLatin1String("Component3D is a base class"));
    qmlRegisterUncreatableType<LiAmbientOcclusion>(uri, 1, 0, "AmbientOcclusion", QLatin1String("AmbientOcclusion is a base class"));
    qmlRegisterUncreatableType<LiToneMapping>(uri, 1, 0, "HDRToneMap", QLatin1String("HDRToneMap is a base class"));
    qmlRegisterType<LiEntity>(uri, 1, 0, "Entity");
    qmlRegisterType<LiBehavior>(uri, 1, 0, "Behavior3D");
    qmlRegisterType<LiFrameAction>(uri, 1, 0, "FrameAction");
    qmlRegisterType<LiTransform>(uri, 1, 0, "Transform3D");
    qmlRegisterType<LiCamera>(uri, 1, 0, "Camera");
    qmlRegisterType<LiLight>(uri, 1, 0, "Light");
    qmlRegisterType<LiBuffer>(uri, 1, 0, "Buffer");
    qmlRegisterType<LiGeometry>(uri, 1, 0, "Geometry");
    qmlRegisterType<LiBoxGeometry>(uri, 1, 0, "BoxGeometry");
    qmlRegisterType<LiGeometryAttribute>(uri, 1, 0, "GeometryAttribute");
    qmlRegisterType<LiGeometryRenderer>(uri, 1, 0, "GeometryRenderer");
    qmlRegisterType<LiParameter>(uri, 1, 0, "Parameter");
    qmlRegisterType<LiMaterial>(uri, 1, 0, "Material");
    qmlRegisterType<LiShaderProgram>(uri, 1, 0, "ShaderProgram");
    qmlRegisterType<LiRenderState>(uri, 1, 0, "RenderState");
    qmlRegisterType<LiTexture>(uri, 1, 0, "Texture");
    qmlRegisterType<LiTextureImage>(uri, 1, 0, "TextureImage");
    qmlRegisterType<LiRenderTarget>(uri, 1, 0, "RenderTarget");
    qmlRegisterType<LiRenderTargetOutput>(uri, 1, 0, "RenderTargetOutput");
    qmlRegisterType<LiPostProcess>(uri, 1, 0, "PostProcess");
    qmlRegisterType<LiFullscreenQuad>(uri, 1, 0, "FullscreenQuad");
    qmlRegisterType<LiRaycastHit>(uri, 1, 0, "RaycastHit");
    qmlRegisterType<LiTextureProjection>(uri, 1, 0, "TextureProjection");

    LiViewer viewer;

//    QObject::connect(viewer.engine()->inputSystem(), &LiInputSystem::leftButtonDown, []{
//        QPoint p = GlobalViewer()->engine()->inputSystem()->mousePosition();
//        Ray ray = GlobalViewer()->scene()->mainCamera()->screenPointToRay(p);

//        LiRaycastHit hit;
//        if (GlobalViewer()->scene()->raycast(ray, &hit)) {
//            qDebug() << "hit:" << hit.entity();
//        }
//    });

    loadDOM(viewer.scene());
//    loadTrees(viewer.scene());
    load3DTileset(viewer.scene());
//    loadCarAnimation(viewer.scene());
//    loadModel(viewer.scene(), "http://61.144.226.45:8084/Tile3D/CZNS_zch/Data/Tile_+0_0_1/root.b3dm");
//    loadModel(viewer.scene(), "D:/download/Cesium-1.40/Apps/SampleData/models/CesiumBalloon/CesiumBalloon.dae");
//    loadModel(viewer.scene(), "D:/download/Dayunzhan/181105_DY SU Model.dae");
//    loadQuadtreeTileset();
//    raycast(viewer.scene());
//    pickFeature(viewer.scene());
    createTextureProjection();
//    createViewshed(viewer.scene());
//    createPlane(viewer.scene());
//    createFire(viewer.scene());
//    createHeatmap(viewer.scene());
    createGisImageryProvider(viewer.scene());
    createLights(viewer.scene());
//    createClipPlane(viewer.scene());
//    createClipVolume(viewer.scene());

    LiInputSystem *input = viewer.engine()->inputSystem();
    QObject::connect(input, &LiInputSystem::keyDown, [&](int key) {
        if (key == Qt::Key_F7) {
            loadDOM(viewer.scene());
        }
        if (key == Qt::Key_F3) {
            bool b = viewer.scene()->dayNightLighting();
            viewer.scene()->setDayNightLighting(!b);
        }
        if (key == Qt::Key_F4) {
            bool b = viewer.scene()->sun()->castShadow();
            viewer.scene()->sun()->setCastShadow(!b);
        }
        if (key == Qt::Key_F5) {
            LiTimeSystem *ts = viewer.engine()->timeSystem();
            QDateTime dt = ts->dateTime();
            if (!dt.isValid())
            {
                dt = QDateTime::currentDateTime();
            }
            QTime t = dt.time();
            int h = t.hour() - 1;
            if (h < 0)
                h += 24;
            qDebug() << h;
            int m = t.minute();
            t = QTime(h, m);
            dt = QDateTime(dt.date(), t);
            ts->setDateTime(dt);
        }
        if (key == Qt::Key_F6) {
            LiTimeSystem *ts = viewer.engine()->timeSystem();
            QDateTime dt = ts->dateTime();
            if (!dt.isValid())
            {
                dt = QDateTime::currentDateTime();
            }
            QTime t = dt.time();
            int h = t.hour() + 1;
            if (h >= 24)
                h -= 24;
            qDebug() << h;
            int m = t.minute();
            t = QTime(h, m);
            dt = QDateTime(dt.date(), t);
            ts->setDateTime(dt);
        }
        if (key == Qt::Key_F) {
            viewer.scene()->mainCamera()->flyTo(Cartesian3::fromDegrees(114.054494, 22.540745, 1000));
        }
        if (key == Qt::Key_F1) {
            QDate date;
            QTime t;
            QDateTime dt = viewer.engine()->timeSystem()->dateTime();
            if (dt.isValid()) {
                date = dt.date();
                t = dt.time();
            } else {
                date = QDate::currentDate();
                t = QTime::currentTime();
            }
            if (input->getKey(Qt::Key_Shift)) {
                int month = date.month() + 1;
                month = clamp(month, 1, 12);
                date = QDate(date.year(), month, date.day());
            } else {
                int hour = t.hour() + 1;
                t = QTime(hour, t.minute(), t.second());
            }
            viewer.engine()->timeSystem()->setDateTime(QDateTime(date, t));
        }
        if (key == Qt::Key_F2) {
            QDate date;
            QTime t;
            QDateTime dt = viewer.engine()->timeSystem()->dateTime();
            if (dt.isValid()) {
                date = dt.date();
                t = dt.time();
            } else {
                date = QDate::currentDate();
                t = QTime::currentTime();
            }
            if (input->getKey(Qt::Key_Shift)) {
                int month = date.month() - 1;
                month = clamp(month, 1, 12);
                date = QDate(date.year(), month, date.day());
            } else {
                int hour = t.hour() - 1;
                t = QTime(hour, t.minute(), t.second());
            }
            viewer.engine()->timeSystem()->setDateTime(QDateTime(date, t));
        }
    });
    viewer.scene()->mainCamera()->flyTo(Cartesian3::fromDegrees(114.054494, 22.540745, 1000));

    viewer.show();

    return a.exec();
}
