#ifndef LISCRIPTENGINE_H
#define LISCRIPTENGINE_H

#include "licore_global.h"
#include <QQmlEngine>

class LiScriptEnginePrivate;

class LICORE_EXPORT LiScriptEngine : public QObject
{
    Q_OBJECT
public:
    explicit LiScriptEngine(QObject *parent = nullptr);
    ~LiScriptEngine();

    static LiScriptEngine *instance();

    QQmlEngine *qmlEngine() const;
    QV4::ExecutionEngine *v4Engine() const;

    QJSValue newObject();
    QJSValue newArray(uint length = 0);
    QJSValue newQObject(QObject *object);

    QObject *loadQmlObject(const QUrl &url, QObject *parent = nullptr);
    QJSValue evaluateFile(const QString &fileName);
    void setGlobalObject(const QString &name, QObject *object);
    Q_INVOKABLE void setGlobalObject(const QString &name, const QJSValue &value);
    QByteArray convertToRawData(const QJSValue &property);

    QJSValue property(const QString &name) const;
    void setProperty(const QString &name, const QJSValue &value);

    static QJSValue call(const QJSValue &value, const QJSValueList &args = QJSValueList());
    static QJSValue call(const QJSValue &value, const QString &func, const QJSValueList &args = QJSValueList());
    static QJSValue call(const QJSValue &value, const QJSValue &func, const QJSValueList &args = QJSValueList());

private:
    QSharedPointer<LiScriptEnginePrivate> d;
};

#endif // LISCRIPTENGINE_H
