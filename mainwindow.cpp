#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/usercfgreader.h"
#include <QProcess>
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

    MP_Manager=new MPItemModel("MP.cfg.json",ui->tableWidget_MP,this);
    Comm_Manager=new MPItemModel("Comm.cfg.json",ui->tableWidget_Comm,this);
    Graphic_Manager=new MPItemModel("Graphic.cfg.json",ui->tableWidget_Graphic,this);
    VR_Manager=new MPItemModel("VR.cfg.json",ui->tableWidget_VR,this);
    Other_Manager=new MPItemModel("Other.cfg.json",ui->tableWidget_Other,this);
    HotasNkey_Manager=new MPItemModel("HotasAndKey.cfg.json",ui->tableWidget_HotasAndKey,this);
    UserDefine_Manager=new UserDefineJsonManager(ui->tableWidget_UserDefine,this);

    QVector<MPItemModel *> table_list={MP_Manager,Comm_Manager,Graphic_Manager,VR_Manager,Other_Manager,HotasNkey_Manager};
    UserCfgReader cfgreader(table_list);
    UserDefinitionOptions=cfgreader.getUserDefineOptions();
    LauncherDefinitionOptions=cfgreader.getLauncherDefineOptions();
    UnknownOptions=cfgreader.getUnknownOptions();

    QSettings registry("\\HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Benchmark Sims\\Falcon BMS 4.38",
                       QSettings::NativeFormat);
    QString baseDir = registry.value("baseDir").toString();
    Cfg_Path = baseDir + "\\User\\Config\\Falcon BMS User.cfg";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_OK_clicked()
{
    QMap<QString,QString> KeyValueNeedToSave;
    KeyValueNeedToSave.insert(MP_Manager->getKeyValue());
    KeyValueNeedToSave.insert(Comm_Manager->getKeyValue());
    KeyValueNeedToSave.insert(Graphic_Manager->getKeyValue());
    KeyValueNeedToSave.insert(VR_Manager->getKeyValue());
    KeyValueNeedToSave.insert(Other_Manager->getKeyValue());
    KeyValueNeedToSave.insert(HotasNkey_Manager->getKeyValue());
    KeyValueNeedToSave.insert(UserDefine_Manager->GetKeyValue());

    QStringList UserDefineStrList=QMapToQString(KeyValueNeedToSave);
    UserDefineStrList.append(""); //add blank row
    UserDefineStrList.append(QMapToQString(UnknownOptions));
    UserDefineStrList.append(""); //add blank row

    QStringList ContentToWrite=UserDefineStrList+LauncherDefinitionOptions;

    QFile file(Cfg_Path);
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
    QMessageBox::information(this,tr("BMS Configure Editor"),tr("Options save successfully"),QMessageBox::Ok);
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


void MainWindow::on_pushButton_OpenCfg_clicked()
{
    if(!QProcess::startDetached("C:\\Windows\\System32\\notepad.exe",{Cfg_Path}))
    {
        QMessageBox::warning(this,tr("BMS Configure Editor"),tr("Unable to open Falcon Bms User.cfg using notepad"),QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_OutputL18N_clicked()
{
    QVector<MPItemModel *> table_list={MP_Manager,Comm_Manager,Graphic_Manager,VR_Manager,Other_Manager,HotasNkey_Manager};
    for(auto manager_ptr:table_list)
    {
        const QJsonObject &JsonObj=manager_ptr->getKeyComment();
        const QJsonDocument JsonDoc(JsonObj);
        const QByteArray data(JsonDoc.toJson());
        QFile JSON_File("./Localization/"+manager_ptr->getJsonFileName());
        if(!JSON_File.exists())
        {
            JSON_File.open(QIODevice::WriteOnly);
            JSON_File.write(data);
        }
    }
    QMessageBox::information(this,tr("BMS Configure Editor"),tr("Output localization JSON successful"));
}
