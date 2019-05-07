#ifndef SAMPLE_H
#define SAMPLE_H

#include <QtCore>
#include <liscene.h>

class Li3DTileset;

//////////////////////////////////////////////////////
// tileset
void load3DTileset(LiScene *scene); // 加载3DTiles
void flytoTileset(Li3DTileset *tileset); // 摄像机飞到3DTiles包围盒
void flattenMaskTileset(Li3DTileset *tileset); // 压平遮罩
void highlightTileset(Li3DTileset *tileset); // 透明叠加效果
void moveTilesetByMouse(Li3DTileset *tileset); // 设置3DTiles的位置
//////////////////////////////////////////////////////

void loadDEM(LiScene *scene);
void loadDOM(LiScene *scene);
void loadModel(LiScene *scene, const QString &path);
void loadTrees(LiScene *scene);
void loadCarAnimation(LiScene *scene);
void loadQuadtreeTileset();
void raycast(LiScene *scene);
void createTextureProjection();
void pickFeature(LiScene *scene);
void createViewshed(LiScene *scene);
void createPlane(LiScene *scene);
void createFire(LiScene *scene);
void createHeatmap(LiScene *scene);
void createGisImageryProvider(LiScene *scene);
void createLights(LiScene *scene);
void createClipPlane(LiScene *scene);
void createClipVolume(LiScene *scene);
void createWaterMaterial(LiScene *scene);
void controlTime();

void loadWms();

#endif // SAMPLE_H
