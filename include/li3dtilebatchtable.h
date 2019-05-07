#ifndef LI3DTILEBATCHTABLE_H
#define LI3DTILEBATCHTABLE_H

#include "libatchtable.h"
#include "vector4.h"
#include "binaryaccessor.h"

class Li3DTileContent;
class LiTexture;

class LICORE_EXPORT Li3DTileBatchTable : public LiBatchTable
{
    Q_OBJECT
public:
    Li3DTileBatchTable(Li3DTileContent *content,
                       int featuresLength,
                       const QJsonObject &batchTableJson,
                       const QByteArray &batchTableBinary,
                       LiNode *parent = nullptr);
    ~Li3DTileBatchTable();

    bool hasProperty(int batchId, const QString &name) const;
    QVariant getProperty(int batchId, const QString &name) const;
    QStringList propertyNames(int batchId) const;

private:
    struct Hierarchy
    {
        QJsonArray classes;
        QVector<int> classIds;
        QVector<int> classIndexes;
        QVector<int> parentCounts;
        QVector<int> parentIndexes;
        QVector<int> parentIds;
    };
    typedef QSharedPointer<Hierarchy> HierarchyPtr;

    QJsonObject initializeProperties(const QJsonObject &jsonHeader);
    QJsonObject getBinaryProperties(const QJsonObject &properties, const QByteArray &binary);

    HierarchyPtr initializeHierarchy(const QJsonObject &jsonHeader, const QByteArray &binaryBody);
    HierarchyPtr initializeHierarchyValues(const QJsonObject &hierarchyJson, const QByteArray &binaryBody);

    void getPropertyNamesInHierarchy(int batchId, QStringList &results) const;
    bool hasPropertyInHierarchy(int batchId, const QString &name) const;
    QJsonObject getInstancesInHierarchy(int instanceIndex) const;

    QVariant getHierarchyProperty(int batchId, const QString &name) const;
    QVariant getBinaryProperty(const QJsonObject &json, int index) const;

    typedef std::function<QVariant(int)> TraverseCallback;
    QVariant traverseHierarchy(int instanceIndex, TraverseCallback endConditionCallback) const;
    QVariant traverseHierarchyMultipleParents(int instanceIndex, TraverseCallback endConditionCallback) const;
    QVariant traverseHierarchySingleParent(int instanceIndex, TraverseCallback endConditionCallback) const;

    Li3DTileContent *_content;
    int _featuresLength;
    int _translucentFeaturesLength = 0; // Number of features in the tile that are translucent
    QJsonObject _batchTableJson;
    QByteArray _batchTableBinary;

    QJsonObject _extensions;
    QJsonObject _properties;
    HierarchyPtr _batchTableHierarchy;
    QJsonObject _batchTableBinaryProperties;

    // PERFORMANCE_IDEA: These parallel arrays probably generate cache misses in get/set color/show
    // and use A LOT of memory.  How can we use less memory?
    bool _showAlphaProperties; // [Show (0 or 255), Alpha (0 to 255)] property for each feature
    uint _batchValues;  // Per-feature RGBA (A is based on the color's alpha and feature's show property)

    bool _batchValuesDirty = false;
    LiTexture *_batchTexture = nullptr;
    LiTexture *_defaultTexture = nullptr;
    LiTexture *_pickTexture = nullptr;
    QVector<uint> _pickIds;

    Vector2 _textureDimensions;
    float _textureStep;
};

#endif // LI3DTILEBATCHTABLE_H
