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
    MPItemModel(QString json_name,QTableWidget *table,QWidget *parent=nullptr);
    ~MPItemModel();
    bool keyIsInList(const QString &key,const QString &value);
    QMap<QString,QString> getKeyValue();
    QJsonObject getKeyComment();
    QString getJsonFileName();

private:
    QTableWidget *table;
    QString json_name;
    QString json_path;
    QJsonArray raw_MP_Cfg;
    QVariantMap I18nMap;
    QMap<QString,int> index_of_options;
    QMap<QString,QString> Options_For_Write;
    QJsonObject Key_Comment;

    void initTable();
    QJsonObject LoadI18nFile() const;
};

#endif // MPITEMMODEL_H
