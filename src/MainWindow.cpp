#include "include/MainWindow.hpp"

#include "frontend/ui_MainWindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
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
        QDir::homePath()
      );
      QString outputTemplate = selectedPath + "/%(title)s.%(ext)s";

      arguments << url
                << "-f" << "best"
                << "-o" << outputTemplate;
      process.start("yt-dlp", arguments);

      if (!process.waitForStarted()) {
         qDebug() << "Failed to start yt-dlp!";
      }

      process.waitForFinished(-1); 
   }
   else {
      QMessageBox::warning(nullptr, "Bad link was input", "You inputted incorrect link");
   }
}