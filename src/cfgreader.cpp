#include "cfgreader.h"
#include <QMessageBox>

CfgReader::CfgReader(const QString &file_path)
{
    json_doc=QJsonDocument::fromJson(loadCfg(file_path));
}

QByteArray CfgReader::loadCfg(const QString &file_path)
{
    QFile file_obj(file_path);
    if(!file_obj.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, tr("BMS Configure Editor"),
                             tr("Json Not Found"),
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
