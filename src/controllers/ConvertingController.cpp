#include "../include/controllers/ConvertingController.hpp"

#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QStringList>

auto convertVideo = [](QStringList arguments) {
   QProcess convertProcess;
   convertProcess.start("ffmpeg", arguments);

   if (!convertProcess.waitForStarted()) {
      return;
   }

   if (!convertProcess.waitForFinished(-1)) {
      return;
   }
};

void ConvertingController::convertVideotoMP3(QString filePath)
{
   QFile inputFile(filePath);
   QFileInfo inputFileInfo(inputFile);
   QString outputFilePath = inputFileInfo.absolutePath() + "/" + inputFileInfo.completeBaseName() + ".mp3";

   QStringList arguments;
   arguments << "-i" << filePath
             << "-vn"
             << "-acodec" << "libmp3lame"
             << "-b:a" << "192k"
             << outputFilePath;

   convertVideo(arguments);
}

void ConvertingController::convertVideotoWAV(QString filePath)
{
   QFile inputFile(filePath);
   QFileInfo inputFileInfo(inputFile);
   QString outputFilePath = inputFileInfo.absolutePath() + "/" + inputFileInfo.completeBaseName() + ".wav";

   QStringList arguments;
   arguments << "-i" << filePath << "-vn" << "-acodec" << "pcm_s16le"
             << "-ar" << "44100"
             << "-ac" << "2"
             << outputFilePath;

   convertVideo(arguments);
}