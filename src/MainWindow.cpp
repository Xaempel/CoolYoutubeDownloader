#include "include/MainWindow.hpp"

#include "../include/models/DownloadedVideoDbModel.hpp"
#include "frontend/ui_MainWindow.h"
#include "include/widgets/LinkRecordsWidget.hpp"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <qfiledialog.h>
#include <qobject.h>

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

   QObject::connect(multiDownloadingFromFileButton, &QPushButton::clicked, this, [this]() {
      QString filePath = QFileDialog::getOpenFileName(nullptr, "Select file for downloading operation", QDir::homePath(), "Text Files (*.txt)");
      QFileInfo fileInfo(filePath);
      multiDownloadingSelectedFileLabel->setText("Your file name " + fileInfo.fileName());

      downloadController.DownloadVideosBasedOnFile(filePath);
   });

   ui->MultiDownloadingMainLayoutEnabled->addWidget(multiDownloadingFromFileButton);
   multiDownloadingFromFileButton->hide();
   ui->MultiDownloadingMainLayoutEnabled->addWidget(multiDownloadingSelectedFileLabel);
   multiDownloadingSelectedFileLabel->hide();
   DownloadedVideoDbModel::initDownloadedVideoDb();
}

void MainWindow::changeMultiDownloadingfromFile()
{
   if (multiDownloadingModeState == false) {
      multiDownloadingFromFileButton->show();
      multiDownloadingSelectedFileLabel->show();

      multiDownloadingModeState = true;
   }
   else {
      multiDownloadingFromFileButton->hide();
      multiDownloadingSelectedFileLabel->hide();

      multiDownloadingModeState = false;
   }
}

void MainWindow::showUsedLinkRecords(int tabIndex)
{
   if (downloadController.getRecordsWidgetUpdatedState() == false) {
      const int recordsTabIndex {1};

      if (tabIndex == recordsTabIndex) {
         QVector<Record> usedLinks = DownloadedVideoDbModel::getRecords();  

         QLayoutItem* item;
         while ((item = ui->RecordsAreaContentLayout->takeAt(0)) != nullptr) {
            if (QWidget* widget = item->widget()) {
               widget->deleteLater();
            }
            delete item;
         }

         for (const Record& rec : usedLinks) {
            LinkRecordsWidget* newRecords = new LinkRecordsWidget(this, rec.link);
            newRecords->setRecordsID(rec.id);  
            
            ui->RecordsAreaContentLayout->addWidget(newRecords);

            QObject::connect(newRecords, &LinkRecordsWidget::deletingRecord,
                             this, &MainWindow::deleteRecordWidget);
         }
      }

      downloadController.setRecordsWidgetUpdatedState(true);
   }
}

void MainWindow::initConvertFile()
{
   QString outputFormat = ui->OutputFileFormat->currentText();

   const char* outputMP3Format = "MP3";
   const char* outputWAVFormat = "WAV";

   QString filePath = QFileDialog::getOpenFileName(nullptr, "Audio file to convert");

   if (outputFormat == outputMP3Format) {
      convertingController.convertVideotoMP3(filePath);
   }
   else if (outputFormat == outputWAVFormat) {
      convertingController.convertVideotoWAV(filePath);
   }
}

void MainWindow::deleteRecordWidget(LinkRecordsWidget* instanceToDelete)
{
   DownloadedVideoDbModel::deleteRecordFromDB(instanceToDelete->getRecordsID());
   instanceToDelete->deleteLater();
}

void MainWindow::showMultiDownloadingInfo(){
   multiDownloadingInfoWidget->show();
}