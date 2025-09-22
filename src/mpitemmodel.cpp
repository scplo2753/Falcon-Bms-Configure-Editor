#include "mpitemmodel.h"
#include "cfgreader.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <utility>


MPItemModel::MPItemModel(const char* json_name, QTableWidget *table, QObject *parent)
    : json_name(json_name),
    json_path(std::move(":/cfg/resource/" + QString(json_name))),
    table(table),
    QObject(parent)
{
    CfgReader MP_CFG_READER(json_path);
    raw_MP_Cfg = MP_CFG_READER.getParsedArray();
    initTable();
}

MPItemModel::~MPItemModel()
{}

void MPItemModel::initTable() {
    table->setRowCount(raw_MP_Cfg.size());
    table->setColumnCount(3);

    QFile i18nFile("./Localization/" + json_name);
    if (i18nFile.exists() == true) {
        QJsonObject I18nObject = LoadI18nFile();
        I18nMap = I18nObject.toVariantMap();
        i18nFile.close();
    }

    for (int index = 0; index < raw_MP_Cfg.size(); index++) {
        auto iterator_object = raw_MP_Cfg[index].toObject();

        Key_Comment[iterator_object["key"].toString()]=iterator_object["comment"].toString();

        index_of_options[iterator_object["key"].toString()]=index;

        QWidget *checkWidget = new QWidget(table);
        QHBoxLayout *layout = new QHBoxLayout(checkWidget);
        QCheckBox *checkbox = new QCheckBox(table);
        layout->addWidget(checkbox);
        layout->setAlignment(Qt::AlignCenter);
        table->setCellWidget(index, 0, checkWidget);

        //---------------------------------------------------------

        QTableWidgetItem *comment_item = new QTableWidgetItem();
        if (!I18nMap.isEmpty() && I18nMap[iterator_object["key"].toString()].isValid())
        {
            QString LocalizationString=I18nMap[iterator_object["key"].toString()].toString();
            comment_item->setText(LocalizationString);
        }
        else
        {
            comment_item->setText(iterator_object["comment"].toString());
        }
        comment_item->setFlags(Qt::ItemIsEnabled);
        table->setItem(index, 1, comment_item);

        //------------------------value Widget---------------------------

        QString valueType=iterator_object["valueType"].toString();
        QTableWidgetItem *editWidget = new QTableWidgetItem(QString::number(iterator_object["value"].toDouble()), 'f');
        table->setItem(index, 2, editWidget);
    }

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setDefaultSectionSize(40);

    table->setColumnWidth(0, 40);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->setColumnWidth(2, 50);
}

QJsonObject MPItemModel::LoadI18nFile() const {
    QString file_Path = "./Localization/" + json_name;
    CfgReader I18nLoader(file_Path);
    QJsonObject raw_objects = I18nLoader.getParsedObjects();
    return raw_objects;
}

bool MPItemModel::keyIsInList(const QString &key,const QString &value)
{
    if(index_of_options.contains(key))
    {
        int index=index_of_options[key];
        table->cellWidget(index,0)->findChild<QCheckBox *>()->setChecked(true);
        table->cellWidget(index,0);
        table->item(index,2)->setText(value);
        return true;
    }
    return false;
}

QJsonObject MPItemModel::getKeyComment()
{
    return Key_Comment;
}

QString MPItemModel::getJsonFileName()
{
    return json_name;
}

QMap<QString, QString> MPItemModel::getKeyValue() {
    QMap<QString, QString> Qmap_options;
    for (int row = 0; row < table->rowCount(); row++) {
        QCheckBox *checkbox = table->cellWidget(row, 0)->findChild<QCheckBox *>();
        if (checkbox->isChecked()) {
            QJsonObject Obj_option = raw_MP_Cfg[row].toObject();
            QString key = Obj_option["key"].toString();
            QString value = table->item(row, 2)->text();
            Qmap_options[key] = value;
        }
    }
    return Qmap_options;
}

QWidget* MPItemModel::TypeBool()
{
    QWidget* check_widget=new QWidget(table);
    QHBoxLayout* check_layout=new QHBoxLayout(check_widget);
    QCheckBox* check_box=new QCheckBox(table);
    check_layout->addWidget(check_box);
    check_layout->setAlignment(Qt::AlignCenter);
    return check_widget;
}
