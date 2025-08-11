#include "userdefinejsonmanager.h"
#include <QCheckBox>
#include <QFile>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QTableWidgetItem>

UserDefineJsonManager::UserDefineJsonManager(QTableWidget *table_widget,
                                            QWidget *parent)
    : table_widget(table_widget), json_path("./Custom Json"), QWidget{parent}
{
    const QFileInfoList &file_list = findJsonFiles();
    LoadJson(file_list);
}

const QFileInfoList UserDefineJsonManager::findJsonFiles() {
    QDir json_dir(json_path);
    QStringList filters = {"*.cfg.json"};

    QFileInfoList file_list =
        json_dir.entryInfoList(filters, QDir::Files | QDir::NoSymLinks);
    return file_list;
}

void UserDefineJsonManager::LoadJson(const QFileInfoList &FilePath) {
    for (auto file : FilePath) {
        const QString path = file.filePath();
        QFile file_obj(path);
        if (!file_obj.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("BMS Configure Editor"),
                                 tr("%1 reading error").arg(path), QMessageBox::Ok);
        } else {
            QTextStream file_text(&file_obj);
            QString json_string = file_text.readAll();
            QByteArray json_bytes = json_string.toUtf8();
            const QJsonDocument &json_doc = QJsonDocument::fromJson(json_bytes);
            if (json_doc.isArray()) {
                JsonToTable(json_doc.array());
            } else {
                if (json_doc.isEmpty() || json_doc.isNull()) {
                    QMessageBox::warning(this, tr("BMS Configure Editor"),
                                         tr("%1 is empty").arg(path), QMessageBox::Ok);
                }
                if (json_doc.isObject()) {
                    QMessageBox::warning(this, tr("BMS Configure Editor"),
                                         tr("%1 format error").arg(path),
                                         QMessageBox::Ok);
                }
            }
        }
    }
}

void UserDefineJsonManager::JsonToTable(const QJsonArray &array) {
    int end_number = table_widget->rowCount();
    if (!array.isEmpty()) {
        for (int i = 0; i < array.size(); i++) {

            const QJsonObject &obj = array.at(i).toObject();
            const QString &key = obj["key"].toString();
            const QString &value = obj["value"].toString();
            const QString &comment = obj["comment"].toString();

            if (key.isEmpty() || comment.isEmpty())
                QMessageBox::warning(
                    this, "BMS Configure",
                    QString("The key or comment of {1}th object in json not found")
                        .arg(i),
                    QMessageBox::Ok);
            else {
                end_number = table_widget->rowCount();
                table_widget->insertRow(1);

                QCheckBox *checkbox = new QCheckBox();
                QWidget *checkWidget = new QWidget();
                QHBoxLayout *layout = new QHBoxLayout(checkWidget);
                layout->addWidget(checkbox);
                layout->setAlignment(Qt::AlignCenter);
                table_widget->setCellWidget(end_number, 0, checkWidget);

                QTableWidgetItem *comment_item = new QTableWidgetItem();
                comment_item->setText(comment);
                comment_item->setFlags(Qt::ItemIsEnabled);
                table_widget->setItem(end_number, 1, comment_item);

                QTableWidgetItem *edit_item = new QTableWidgetItem(0);
                if (!value.isEmpty()) {
                    edit_item->setText(value);
                }
                table_widget->setItem(end_number, 2, edit_item);

                key_set.append(key);
            }
        }
    }
}

const QMap<QString, QString> UserDefineJsonManager::GetKeyValue() {
    QMap<QString,QString> key_value;

    const int &row_count=table_widget->rowCount();
    for(int row=0;row<row_count;row++)
    {
        const QCheckBox *checkbox=table_widget->cellWidget(row,0)->findChild<QCheckBox *>();
        if(checkbox->isChecked())
        {
            const QString key= key_set[row];
            const QString value=table_widget->item(row,2)->text();
            key_value[key]=value;
        }
    }
    return key_value;
}
