#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/usercfgreader.h"
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <qsettings.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MP_Manager=new MPItemModel(":/cfg/resource/MP.cfg.json",ui->tableWidget_MP);
    Comm_Manager=new MPItemModel(":/cfg/resource/Comm.cfg.json",ui->tableWidget_Comm);
    Graphic_Manager=new MPItemModel(":/cfg/resource/Graphic.cfg.json",ui->tableWidget_Graphic);
    VR_Manager=new MPItemModel(":/cfg/resource/VR.cfg.json",ui->tableWidget_VR);

    UserCfgReader cfgreader;
    UserDefinitions=cfgreader.getUserDefineOptions();
    LauncherDefinitions=cfgreader.getLauncherDefineOptions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_OK_clicked()
{
    QMap<QString,QString> KeyValueNeedToSave;
    KeyValueNeedToSave.insert(MP_Manager->getOptionForWrite());
    KeyValueNeedToSave.insert(Comm_Manager->getOptionForWrite());
    KeyValueNeedToSave.insert(Graphic_Manager->getOptionForWrite());
    KeyValueNeedToSave.insert(VR_Manager->getOptionForWrite());

    QStringList UserDefineStrList=QMapToQString(KeyValueNeedToSave);
    QStringList ContentToWrite=UserDefineStrList+LauncherDefinitions;

    QSettings registry("\\HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Benchmark Sims\\Falcon BMS 4.38",
                       QSettings::NativeFormat);
    QString baseDir = registry.value("baseDir").toString();
    QString CfgPath = baseDir + "\\User\\Config\\Falcon BMS User.cfg";

    QFile file(CfgPath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, tr("BMS Configure Editor"),
                             tr("Cannot write to Falcon BMS User.cfg"),
                             QMessageBox::Ok | QMessageBox::Cancel);
    }
    else
    {
        QTextStream out(&file);
        for (const auto &line : std::as_const(ContentToWrite)) {
            out << line<<Qt::endl;
        }
    }
    file.close();
    exit(0);
}

QStringList MainWindow::QMapToQString(QMap<QString,QString> qmap)
{
    QStringList lines;
    for(auto it=qmap.begin();it!=qmap.end();it++)
    {
        lines<<"set "+it.key()+" "+it.value();
    }
    return lines;
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    exit(0);
}

