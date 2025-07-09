#include "cfgreader.h"
#include <QMessageBox>

CfgReader::CfgReader(const QString &file_path)
{
    parseByte(file_path);
}

QJsonArray CfgReader::get_parsed_data() const{
    return parsed_Data;
}

QByteArray CfgReader::loadCfg(const QString &file_path)
{
    QFile file_obj(file_path);
    if(!file_obj.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, tr("BMS Configure Editor"),
                             tr("Cfg Not Found"),
                             QMessageBox::Ok);
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string=file_text.readAll();
    file_obj.close();
    QByteArray json_bytes=json_string.toUtf8();
    return json_bytes;
}

void CfgReader::parseByte(const QString &file_path)
{
    QJsonDocument json_doc=QJsonDocument::fromJson(loadCfg(file_path));
    parsed_Data=json_doc.array();
}
