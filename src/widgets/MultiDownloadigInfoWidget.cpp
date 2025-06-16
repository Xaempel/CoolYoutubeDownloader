#include "../include/widgets/MultiDownloadigInfoWidget.hpp"

#include "../frontend/ui_MultiDownloadigInfoWidget.h"

MultiDownloadigInfoWidget::MultiDownloadigInfoWidget(QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::MultiDownloadigInfoWidget)
{
   ui->setupUi(this);
}