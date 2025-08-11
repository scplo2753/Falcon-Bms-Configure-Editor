#ifndef CFGREADER_H
#define CFGREADER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QWidget>

class CfgReader:public QWidget
{
public:
    CfgReader(const QString &File_Path,QWidget *parent=nullptr);
    ~CfgReader();
    QJsonArray getParsedArray();
    QJsonObject getParsedObjects();
private:
    QJsonDocument json_doc;

    QByteArray loadCfg(const QString &File_Path);
};

#endif // CFGREADER_H
