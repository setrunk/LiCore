#include "pmtscapabilities.h"
#include "lifilesystem.h"
#include "vector3.h"
#include "axisalignedboundingbox.h"

struct PMTSLayer
{
    QString identifier;
    QString title;
    QStringList infoformat;
    QStringList matrixsetlink;
};
typedef QList<PMTSLayer> PMTSLayers;

struct PMTSResourceUrl
{
    QString format;
    QString type;
    QString url;
};
typedef QHash<QString, PMTSResourceUrl> PMTSResourceUrls;

struct PMTSMatrix
{
    QString identifier;
    QString title;
    QString uid;
    QString url;
    Vector3 position;
    Vector3 localrotate;
    Vector3 localscale;
    AABB localbounds;
};
typedef QHash<QString, PMTSMatrix> PMTSMatrices;

struct PMTSMatrixSet
{
    QString identifier;
    QString title;
    QString format;
    QString uid;
    QString propstoragetype;
    PMTSMatrices matrices;
    PMTSResourceUrls resourceUrls;
    bool compressed;
};
typedef QHash<QString, PMTSMatrixSet> PMTSMatrixSets;

static PMTSLayers parseLayers(const QVariantList &data)
{
    PMTSLayers layers;

    for (const QVariant &v : data)
    {
        QVariantHash layerData = v.toHash();

        PMTSLayer layer;
        layer.identifier = layerData[QStringLiteral("identifier")].toString();
        layer.title = layerData[QStringLiteral("title")].toString();

        for (const QVariant &i : layerData[QStringLiteral("infoformat")].toList())
        {
            layer.infoformat << i.toString();
        }

        for (const QVariant &i : layerData[QStringLiteral("matrixsetlink")].toList())
        {
            layer.matrixsetlink << i.toString();
        }

        layers << layer;
    }

    return layers;
}

static PMTSMatrixSets parseMatrixSets(const QVariantList &data)
{
    PMTSMatrixSets matrixSets;

    for (const QVariant &v : data)
    {
        QVariantHash matrixSetData = v.toHash();

        PMTSMatrixSet matrixSet;
        matrixSet.identifier = matrixSetData[QStringLiteral("identifier")].toString();
        matrixSet.title = matrixSetData[QStringLiteral("title")].toString();
        matrixSet.format = matrixSetData[QStringLiteral("format")].toString();
        matrixSet.uid = matrixSetData[QStringLiteral("uid")].toString();
        matrixSet.propstoragetype = matrixSetData[QStringLiteral("propstoragetype")].toString();
        matrixSet.compressed = matrixSetData[QStringLiteral("compressed")].toBool();

        for (const QVariant &i : matrixSetData[QStringLiteral("matrix")].toList())
        {
            QVariantHash matrixData = i.toHash();
            PMTSMatrix matrix;
            matrix.identifier = matrixData[QStringLiteral("identifier")].toString();
            matrix.title = matrixData[QStringLiteral("title")].toString();
            matrix.uid = matrixData[QStringLiteral("uid")].toString();
            matrix.url = matrixData[QStringLiteral("url")].toString();
            matrixSet.matrices[matrix.identifier] = matrix;
        }

        for (const QVariant &i : matrixSetData[QStringLiteral("resourceurl")].toList())
        {
            QVariantHash resourceUrlData = i.toHash();
            PMTSResourceUrl resourceUrl;
            resourceUrl.format = resourceUrlData[QStringLiteral("format")].toString();
            resourceUrl.type = resourceUrlData[QStringLiteral("type")].toString();
            resourceUrl.url = resourceUrlData[QStringLiteral("template")].toString();
            matrixSet.resourceUrls[resourceUrl.type] = resourceUrl;
        }

        matrixSets[matrixSet.identifier] = matrixSet;
    }

    return matrixSets;
}

static QStringList parseModelUrls(const QVariantHash &data)
{
    QVariantHash contents = data[QStringLiteral("contents")].toHash();
    PMTSLayers layers = parseLayers(contents[QStringLiteral("layers")].toList());
    PMTSMatrixSets matrixSets = parseMatrixSets(contents[QStringLiteral("matrixsets")].toList());

    QStringList pModelUrls;

    for (const auto &layer : layers)
    {
        for (const auto &linkName : layer.matrixsetlink)
        {
            const PMTSMatrixSet matrixSet = matrixSets[linkName];
            for (auto i = matrixSet.matrices.begin(); i != matrixSet.matrices.end(); ++i)
            {
                const PMTSMatrix &matrix = i.value();
                if (matrix.url.size())
                {
                    pModelUrls << matrix.url;
                }
                else
                {
                    QString url = matrixSet.resourceUrls[QStringLiteral("file")].url;
                    url = url.replace(QStringLiteral("{matrixset}"), matrixSet.identifier);
                    url = url.replace(QStringLiteral("{matrix}"), matrix.identifier);
                    url = url.replace(QStringLiteral("{filepath}"), matrix.identifier + QStringLiteral("/tileset.json"));
                    pModelUrls << url;
                }
            }
        }
    }

    return pModelUrls;
}

PMTSCapabilities::PMTSCapabilities(const QString &url)
{
    auto promise = LiFileSystem::readJson(url);

    observe(promise).subscribe([=](QJsonValue data) {

        m_modelUrls = parseModelUrls(data.toObject().toVariantHash());
        m_defer.complete();

    }, [=] {

        qDebug() << "Failed to parse PMTSCapabilities:" << url;
        m_defer.cancel();

    });
}
