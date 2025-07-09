#ifndef USERCFGREADER_H
#define USERCFGREADER_H

#include <QString>
#include <QWidget>

class UserCfgReader : public QWidget
{
public:
    UserCfgReader();
    QMap<QString,QString> getUserDefineOptions() const;
    const QStringList getLauncherDefineOptions() const;

private:
    QString CfgPath;
    QMap<QString,QString> UserDefineOptions;
    QStringList LauncherDefineOptions;

    void loadUserCfg();
};

#endif // USERCFGREADER_H
