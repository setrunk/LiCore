#ifndef LISCENE_H
#define LISCENE_H

#include "licore_global.h"
#include "lipickid.h"
#include "lifeature.h"
#include "ray.h"
#include "plane.h"

class LiNode;
class LiScenePrivate;
class LiRenderSystem;
class LiEntity;
class LiCamera;
class Globe;
class MapProjection;
class LiWidget;
class LiSkybox;
class LiLight;
class LiIndirectLight;
class LiFog;
class LiSun;
class LiAtmosphere;
class LiRaycastHit;

class LICORE_EXPORT LiScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LiWidget* canvas READ canvas)
    Q_PROPERTY(LiEntity* root READ rootEntity)
    Q_PROPERTY(LiCamera* mainCamera READ mainCamera)
    Q_PROPERTY(LiSkybox* skybox READ skybox)
    Q_PROPERTY(LiSun* sun READ sun)
    Q_PROPERTY(LiIndirectLight* indirectLight READ indirectLight)
    Q_PROPERTY(LiAtmosphere* atmosphere READ atmosphere)
    Q_PROPERTY(Globe* globe READ globe)
    Q_PROPERTY(LiFog* fog READ fog)
    Q_PROPERTY(double terrainExaggeration READ terrainExaggeration)
    Q_PROPERTY(Mode sceneMode READ sceneMode WRITE setSceneMode NOTIFY sceneModeChanged)
    Q_PROPERTY(bool pickPositionSupported READ pickPositionSupported)
public:
    enum Mode
    {
        MORPHING = 0,
        COLUMBUS_VIEW = 1,
        SCENE2D = 2,
        SCENE3D = 3,
        UNDERGROUND = 4
    };
    Q_ENUM(Mode)

    explicit LiScene(QObject *parent = 0);
    virtual ~LiScene();

    LiEntity *rootEntity() const;
    LiCamera *mainCamera() const;
    LiSkybox *skybox() const;
    LiSun *sun() const;
    LiIndirectLight *indirectLight() const;
    Globe *globe() const;
    LiFog *fog() const;
    LiAtmosphere *atmosphere() const;
    LiEntity *underground() const;

    LiWidget *canvas() const;
    void setCanvas(LiWidget *canvas);

    Q_INVOKABLE void addEntity(LiEntity *entity);
    Q_INVOKABLE LiEntity *addEntity(const QString &name = QString());

    Mode sceneMode() const;
    void setSceneMode(Mode mode);

    bool dayNightLighting() const;
    void setDayNightLighting(bool lighting);

    bool isClipPlaneEnabled(int index = 0) const;
    void enableClipPlane(bool enabled, int index = 0);
    int numClipPlanesEnabled() const;

    Plane clipPlane(int index = 0) const;
    void setClipPlane(const Plane &plane, int index = 0);

    MapProjection *mapProjection() const;
    bool pickPositionSupported() const;
    double terrainExaggeration() const;

    LiPickId createPickId(LiFeature *feature);
    LiFeature *getFeatureByPickId(const LiPickId &pickId);
    QFuture<LiPickId> pickFeature(int x, int y); // window position
    QFuture<LiPickId> pickFeature(const QPoint &windowPosition); // window position

    Q_INVOKABLE bool raycast(const Ray &ray, LiRaycastHit *hit) const;
    Q_INVOKABLE QJSValue pickPositionWorldCoordinates(const QJSValue &windowPosition, QJSValue result) const;

signals:
    void sceneModeChanged();
    void enterPicked(uint pickId);
    void leavePicked(uint pickId);
    void clipPlaneEnabledChanged(int index);
    void clipVolumeChanged();

public slots:
    void addEventListener(const QString &type, const QJSValue &listener, bool useCapture = false);
    void removeEventListener(const QString &type, const QJSValue &listener, bool useCapture = false);

private:
    Q_DECLARE_PRIVATE(LiScene)
    friend class LiRenderSystem;
};

#endif // LISCENE_H
