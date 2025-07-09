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
    MPItemModel(QString json_Path,QTableWidget *table);
    void initTable(QMap<QString,QString>UserDefinitions);
    QMap<QString,QString> getOptionForWrite();

private:
    QTableWidget *table;
    QJsonArray raw_MP_Cfg;
    QMap<QString,QString> OptionsForWrite;

    void parseRawJson();
};

#endif // MPITEMMODEL_H
