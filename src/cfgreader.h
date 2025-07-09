#ifndef CFGREADER_H
#define CFGREADER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>
#include <QWidget>

class CfgReader:public QWidget
{
public:
    CfgReader(const QString &File_Path);
    QJsonArray get_parsed_data() const;
private:
    QJsonArray parsed_Data;

    QByteArray loadCfg(const QString &File_Path);
    void parseByte(const QString &File_Path);
};

#endif // CFGREADER_H
