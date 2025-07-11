#ifndef USERCFGREADER_H
#define USERCFGREADER_H

#include "mpitemmodel.h"

#include <QString>
#include <QWidget>

class UserCfgReader : public QWidget
{
public:
    UserCfgReader(QVector<MPItemModel *> table_list,QWidget *parent=nullptr);
    QMap<QString,QString> getUserDefineOptions() const;
    const QStringList getLauncherDefineOptions() const;
    QMap<QString,QString> getUnknownOptions() const;

private:
    QString CfgPath;
    QMap<QString,QString> UserDefineOptions;
    QStringList LauncherDefineOptions;
    QMap<QString,QString> UnknownOptions;
    QVector<MPItemModel *> table_list;

    void loadUserCfg();
    void initEachTableStatus();
};

#endif // USERCFGREADER_H
