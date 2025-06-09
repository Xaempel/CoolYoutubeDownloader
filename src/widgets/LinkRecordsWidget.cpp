#include "../include/widgets/LinkRecordsWidget.hpp"

#include "../frontend/ui_LinkRecordsWidget.h"

#include <QLabel>

LinkRecordsWidget::LinkRecordsWidget(QWidget* parent, const QString record)
    : QFrame(parent)
    , ui(new Ui::LinkRecordsWidget)
{
   ui->setupUi(this);

   ui->RecordsDataLayout->addWidget(new QLabel(record));
}