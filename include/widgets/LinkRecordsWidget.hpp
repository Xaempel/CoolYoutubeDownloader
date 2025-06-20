/*******************************************************************************
**                                                                            **
**  Copyright (C) [2025] [Xaempel]                                            **
**                                                                            **
**  This file is part of [CoolYoutubeDowloader].                              **
**  [CoolYoutubeDowloader] is free software: you can redistribute it and/or   **
**  modify it under the terms of the GNU General Public License as published  **
**  by the Free Software Foundation, either version 2 of the License, or any  **
**  later version.                                                            **
**                                                                            **
**  [CoolYoutubeDowloader] is distributed in the hope that it will be         **
**  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of    **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             **
**  GNU General Public License for more details.                              **
**                                                                            **
**  You should have received a copy of the GNU General Public License along   **
**  with [CoolYoutubeDowloader].  If not, see <https://www.gnu.org/licenses/>.**
**                                                                            **
**  This project uses the Qt framework, which is licensed under the GNU       **
**  General Public License (GPL) version 2 or later. The full text of the     **
**  GPL license can be found in the LICENSE file.                             **
**                                                                            **
**  Qt is a cross-platform application framework maintained by The Qt Company.**
**  You can find more information about Qt and its licensing at               **
**  https://www.qt.io/.                                                       **
**                                                                            **
******************************************************************************/
#pragma once

#include <QWidget>
#include <QFrame>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
   class LinkRecordsWidget;
};
QT_END_NAMESPACE

class LinkRecordsWidget : public QFrame {
   Q_OBJECT
   public:
   LinkRecordsWidget(QWidget* parent = nullptr,const QString record = "");

   int getRecordsID();
   void setRecordsID(int ID);


   private slots:
   void emitDeleteRecord();

   signals:
   void deletingRecord(LinkRecordsWidget* instanceToDelete);

   private:
   Ui::LinkRecordsWidget *ui {nullptr};
   int RecordsID {1};
};