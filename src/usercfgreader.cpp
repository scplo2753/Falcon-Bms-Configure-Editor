#include "usercfgreader.h"
#include <QFile>
#include <QMessageBox>
#include <QSettings>

UserCfgReader::UserCfgReader(QVector<MPItemModel *> table_list,QWidget *parent):
    QWidget(parent),
    table_list(table_list)
{
    QSettings registry("\\HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Benchmark Sims\\Falcon BMS 4.38",
                       QSettings::NativeFormat);
    QString baseDir = registry.value("baseDir").toString();
    CfgPath = baseDir + "\\User\\Config\\Falcon BMS User.cfg";
    loadUserCfg();
    initEachTableStatus();
}

void UserCfgReader::loadUserCfg() {
    QStringList lines;
    QFile cfgFile(CfgPath);
    if (cfgFile.exists() == false) {
        QMessageBox::warning(this, tr("BMS Configure Editor"),
                             tr("Falcon BMS User.cfg not found"),
                             QMessageBox::Ok | QMessageBox::Cancel);
        exit(1);
    }
    if (cfgFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&cfgFile);
        while (!in.atEnd()) {
            lines << in.readLine();
        }
        cfgFile.close();
    }

    int LAUNCHER_DEFINE_BEGINE_LINES=-1;
    for(int index=0;index<lines.size();index++)
    {
        if(lines[index]=="// LAUNCHER OVERRIDES BEGIN HERE - DO NOT EDIT OR ADD BELOW THIS LINE")
        {
            LAUNCHER_DEFINE_BEGINE_LINES=index;
            break;
        }
        if(lines[index]!="" & lines[index].startsWith("set"))
        {
            QString key,value;
            auto temp=lines[index].split(" ");
            key=temp[1];
            value=temp[2];
            UserDefineOptions[key]=value;
        }
    }
    LauncherDefineOptions=lines.mid(LAUNCHER_DEFINE_BEGINE_LINES);
}

void UserCfgReader::initEachTableStatus()
{
    for(auto iterator=UserDefineOptions.cbegin();iterator!=UserDefineOptions.cend();iterator++)
    {
        const QString &key=iterator.key();
        const QString &value=iterator.value();

        bool key_in_table=false;
        for(auto table_itor:table_list)
        {
            if(table_itor->keyIsInList(key,value))
            {
                key_in_table=true;
                break;
            }
        }
        if (!key_in_table)
        {
            UnknownOptions[key]=value;
        }
    }
}



QMap<QString,QString> UserCfgReader::getUserDefineOptions() const
{
    return UserDefineOptions;
}

const QStringList UserCfgReader::getLauncherDefineOptions() const
{
    return LauncherDefineOptions;
}

QMap<QString,QString> UserCfgReader::getUnknownOptions() const
{
    return UnknownOptions;
}
