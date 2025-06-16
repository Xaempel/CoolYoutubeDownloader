#include "../include/widgets/LinkRecordsWidget.hpp"

#include "../frontend/ui_LinkRecordsWidget.h"

#include <QLabel>
#include <qtmetamacros.h>

LinkRecordsWidget::LinkRecordsWidget(QWidget* parent, const QString record)
    : QFrame(parent)
    , ui(new Ui::LinkRecordsWidget)
{
   ui->setupUi(this);

   ui->RecordsDataLayout->addWidget(new QLabel(record));
}

int LinkRecordsWidget::getRecordsID()
{
   return RecordsID;
}

void LinkRecordsWidget::setRecordsID(int ID)
{
   RecordsID = ID;
}

void LinkRecordsWidget::emitDeleteRecord()
{
   emit deletingRecord(this);
}