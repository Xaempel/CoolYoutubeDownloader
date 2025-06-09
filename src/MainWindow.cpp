#include "include/MainWindow.hpp"

#include "../include/models/DownloadedVideoDbModel.hpp"
#include "../include/widgets/LinkRecordsWidget.hpp"
#include "frontend/ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <qlayoutitem.h>
#include <stdexcept>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QObject::connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::showUsedLinkRecords);

   DownloadedVideoDbModel::initDownloadedVideoDb();
}

bool MainWindow::isValidLink(QString link)
{
   if (link.startsWith("https://www.youtube.com/watch?v=") || link.startsWith("youtube.com/watch?v=")) {
      return true;
   }
   else {
      return false;
   }
}

void MainWindow::showUsedLinkRecords(int tabIndex)
{
   if (recordsWidgetsUpdated == false) {
      const int recordsTabIndex {1};

      if (tabIndex == recordsTabIndex) {
         QStringList usedLinks {DownloadedVideoDbModel::getRecords()};

         // ! This method is not the most effective and This is very costed but is a very simple and ! 
         // ! I don't want create more effective method for this today so !
         // ! I create quick solution for this feature so please don't kill me !
         QLayoutItem* item;
         while ( (item = ui->RecordsAreaContentLayout->takeAt(0)) != nullptr) {
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
      recordsWidgetsUpdated = true;
   }
}

void MainWindow::downloadVideo()
{
   QString url = ui->urlInputBox->text();
   ui->urlInputBox->setText("");
   bool linkState = isValidLink(url);

   if (linkState) {
      QProcess process;
      QStringList arguments;

      QString selectedPath = QFileDialog::getExistingDirectory(
       this,
       "",
       QDir::homePath());
      QString outputTemplate = selectedPath + "/%(title)s.%(ext)s";

      arguments << url
                << "-f" << "best"
                << "-o" << outputTemplate;
      process.start("yt-dlp", arguments);

      if (!process.waitForStarted()) {
         throw std::runtime_error("Failed to start yt-dlp!");
      }
      process.waitForFinished(-1);

      DownloadedVideoDbModel::saveRecord(url);

      recordsWidgetsUpdated = false;
   }
   else {
      QMessageBox::warning(nullptr, "Bad link was input", "You inputted incorrect link");
   }
}