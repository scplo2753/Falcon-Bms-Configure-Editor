#ifndef CFGREADER_H
#define CFGREADER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QWidget>

class CfgReader:public QObject
{
    Q_OBJECT
public:
    CfgReader(const QString &File_Path,QObject *parent=nullptr);
    ~CfgReader();
    QJsonArray getParsedArray();
    QJsonObject getParsedObjects();
private:
    QJsonDocument json_doc;

    QByteArray loadCfg(const QString &File_Path);

signals:
    void fileNotFound(QString str);
};

#endif // CFGREADER_H
