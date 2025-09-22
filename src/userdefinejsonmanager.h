#ifndef USERDEFINEJSONMANAGER_H
#define USERDEFINEJSONMANAGER_H

#include <QTableWidget>
#include <QJsonDocument>
#include <QDir>

class UserDefineJsonManager : public QObject
{
    Q_OBJECT
public:
    explicit UserDefineJsonManager(QTableWidget *table_widget,QObject *parent = nullptr);
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
