#include "mpitemmodel.h"
#include "cfgreader.h"
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>

MPItemModel::MPItemModel(QString json_path, QTableWidget *table):
    table(table)
{
    CfgReader MP_CFG_READER(json_path);
    raw_MP_Cfg=MP_CFG_READER.get_parsed_data();
    parseRawJson();
}

void MPItemModel::parseRawJson()
{
    table->setRowCount(raw_MP_Cfg.size());
    table->setColumnCount(3);
    for(int index=0;index<raw_MP_Cfg.size();index++)
    {
        auto iterator_object=raw_MP_Cfg[index].toObject();

        QCheckBox *checkbox=new QCheckBox();
        QWidget *checkWidget=new QWidget();
        QHBoxLayout *layout=new QHBoxLayout(checkWidget);
        layout->addWidget(checkbox);
        layout->setAlignment(Qt::AlignCenter);
        table->setCellWidget(index,0,checkWidget);

        QTableWidgetItem *comment_item=new QTableWidgetItem(iterator_object["comment"].toString());
        comment_item->setFlags(Qt::ItemIsEnabled);
        table->setItem(index,1,comment_item);

        QTableWidgetItem *editWidget=new QTableWidgetItem(QString::number(iterator_object["value"].toDouble()));
        table->setItem(index,2,editWidget);
    }

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setDefaultSectionSize(40);

    table->setColumnWidth(0,40);
    table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    table->setColumnWidth(2,50);
}

void MPItemModel::initTable(QMap<QString,QString> UserDefinitions)
{
}

QMap<QString,QString> MPItemModel::getOptionForWrite()
{
    QMap<QString,QString> Qmap_options;
    for(int row=0;row<table->rowCount();row++)
    {
        QWidget *checkboxWidget=table->cellWidget(row,0);
        QCheckBox *checkbox=checkboxWidget->findChild<QCheckBox *>();
        if(checkbox->isChecked())
        {
            QJsonObject Obj_option=raw_MP_Cfg[row].toObject();
            QString key=Obj_option["key"].toString();
            QString value=table->item(row,2)->text();
            Qmap_options[key]=value;
        }
    }
    return Qmap_options;
}
