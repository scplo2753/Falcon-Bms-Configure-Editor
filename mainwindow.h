#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/mpitemmodel.h"
#include <QJsonObject>
#include <QTableWidget>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_OpenCfg_clicked();

private:
    QJsonObject MP_Obj;
    Ui::MainWindow *ui;
    QStringList LauncherDefinitionOptions;
    QMap<QString,QString> UserDefinitionOptions;
    QMap<QString,QString> UnknownOptions;
    QString Cfg_Path;

    MPItemModel *MP_Manager;
    MPItemModel *Comm_Manager;
    MPItemModel *Graphic_Manager;
    MPItemModel *VR_Manager;
    MPItemModel *Other_Manager;
    MPItemModel *HotasNkey_Manager;

    QStringList QMapToQString(QMap<QString,QString> qmap);
};
#endif // MAINWINDOW_H
