#include "include/MainWindow.hpp"

#include "../include/models/DownloadedVideoDbModel.hpp"
#include "../include/widgets/LinkRecordsWidget.hpp"
#include "frontend/ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QObject::connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::showUsedLinkRecords);
   QObject::connect(ui->DowloadButton, &QPushButton::clicked, this, [this]() {
      downloadController.DownloadVideo(ui->urlInputBox->text());
      ui->urlInputBox->setText("");
   });
   DownloadedVideoDbModel::initDownloadedVideoDb();
}

void MainWindow::showUsedLinkRecords(int tabIndex)
{
   if (downloadController.getRecordsWidgetUpdatedState() == false) {
      const int recordsTabIndex {1};

      if (tabIndex == recordsTabIndex) {
         QStringList usedLinks {DownloadedVideoDbModel::getRecords()};

         // ! This method is not the most effective and This is very costed but is a very simple and !
         // ! I don't want create more effective method for this today so !
         // ! I create quick solution for this feature so please don't kill me !
         QLayoutItem* item;
         while ((item = ui->RecordsAreaContentLayout->takeAt(0)) != nullptr) {
            if (QWidget* widget = item->widget()) {
               widget->deleteLater();
            }
            delete item;
         }

         for (auto i : usedLinks) {
            LinkRecordsWidget* newRecords {new LinkRecordsWidget(this, i)};
            ui->RecordsAreaContentLayout->addWidget(newRecords);
         }
      }
      downloadController.setRecordsWidgetUpdatedState(true);
   }
}
