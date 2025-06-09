#include "../include/controllers/DownloadController.hpp"

#include "../include/models/DownloadedVideoDbModel.hpp"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <stdexcept>

void DownloadController::DownloadVideo(QString url)
{
   bool linkState = isValidLink(url);

   if (linkState) {
      QProcess process;
      QStringList arguments;

      QString selectedPath = QFileDialog::getExistingDirectory(
       nullptr,
       "",
       QDir::homePath());
      QString outputTemplate = selectedPath + "/%(title)s.%(ext)s";

      arguments << url
                << "-f" << "bestvideo+bestaudio"
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

bool DownloadController::isValidLink(QString link)
{
   if (link.startsWith("https://www.youtube.com/watch?v=") || link.startsWith("youtube.com/watch?v=")) {
      return true;
   }
   else {
      return false;
   }
}

bool DownloadController::getRecordsWidgetUpdatedState()
{
   return recordsWidgetsUpdated;
}

void DownloadController::setRecordsWidgetUpdatedState(bool newValue){
   recordsWidgetsUpdated = newValue;
}