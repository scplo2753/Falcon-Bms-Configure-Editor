#ifndef MPITEMMODEL_H
#define MPITEMMODEL_H

#include <QStandardItemModel>
#include <QHeaderView>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>

class MPItemModel : public QStandardItemModel
{
public:
    MPItemModel(QString json_name,QTableWidget *table);
    QMap<QString,QString> getOptionForWrite();

private:
    QTableWidget *table;
    QString json_name;
    QString json_path;
    QJsonArray raw_MP_Cfg;
    QVariantMap I18nMap;
    QMap<QString,QString> OptionsForWrite;

    void initTable();
    QJsonObject LoadI18nFile();
};

#endif // MPITEMMODEL_H
