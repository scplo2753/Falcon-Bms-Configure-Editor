#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

void ensureI18nFolderExists()
{
    QString app_dir=QCoreApplication::applicationDirPath();
    QDir dir(app_dir);

    QString dir_Name("Localization");
    if(!dir.exists(dir_Name))
    {
        if(dir.mkdir(dir_Name))
            qDebug()<<"Localization folder has been created";
        else
            qWarning()<<"Unable to create Localization folder";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ensureI18nFolderExists();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "BMSConfigure_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
