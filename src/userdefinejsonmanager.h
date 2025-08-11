#ifndef USERDEFINEJSONMANAGER_H
#define USERDEFINEJSONMANAGER_H

#include <QTableWidget>
#include <QJsonDocument>
#include <QWidget>
#include <QDir>

class UserDefineJsonManager : public QWidget
{
public:
    explicit UserDefineJsonManager(QTableWidget *table_widget,QWidget *parent = nullptr);
    const QMap<QString,QString> GetKeyValue();

private:
    QString json_path;
    QTableWidget *table_widget;
    QList<QString> key_set;

    const QFileInfoList findJsonFiles();
    void LoadJson(const QFileInfoList &FilePath);
    void JsonToTable(const QJsonArray& array);
};

#endif // USERDEFINEJSONMANAGER_H
