#include "cfgreader.h"
#include <QMessageBox>
#include <QApplication>

CfgReader::CfgReader(const QString &file_path,QObject *parent):
    QObject(parent)
{
    json_doc=QJsonDocument::fromJson(loadCfg(file_path));
}

CfgReader::~CfgReader()
{

}

QByteArray CfgReader::loadCfg(const QString &file_path)
{
    QFile file_obj(file_path);
    if(!file_obj.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(QApplication::activeWindow(), tr("BMS Configure Editor"),
                             tr("%1 Not Found").arg(file_path),
                             QMessageBox::Ok);
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string=file_text.readAll();
    file_obj.close();
    QByteArray json_bytes=json_string.toUtf8();
    return json_bytes;
}

QJsonArray CfgReader::getParsedArray()
{
    return json_doc.array();
}

QJsonObject CfgReader::getParsedObjects()
{
    return json_doc.object();
}
