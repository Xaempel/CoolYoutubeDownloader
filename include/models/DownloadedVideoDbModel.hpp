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

#include <QStringList>
#include <sqlite3.h>
#include <stdexcept>
#include <QByteArray>

class DownloadedVideoDbModel {
   public:
   static void initDownloadedVideoDb()
   {
      int rc = sqlite3_open(dbName, &db);
      if (rc != SQLITE_OK) {
         throw std::runtime_error("Db isn't opening");
      }

      const char* createTableQuery = "CREATE TABLE IF NOT EXISTS used_link(id INTEGER PRIMARY KEY AUTOINCREMENT,link TEXT NOT NULL)";
      rc                           = sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
      if (rc != SQLITE_OK) {
         throw std::runtime_error("When table was creating someting went wrong");
      }
      sqlite3_close(db);
   }

   static void saveRecord(QString Records)
   {
      int rc = sqlite3_open(dbName, &db);
      if (rc != SQLITE_OK) {
         throw std::runtime_error("Db isn't opening");
      }

      sqlite3_stmt* stmt = nullptr;
      const char* query  = "INSERT INTO used_link (link) VALUES (?);";
      sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);

      QByteArray utfData = Records.toUtf8();
      const char* recordsUtfData = utfData.constData();

      sqlite3_bind_text(stmt,1,recordsUtfData, -1, SQLITE_STATIC);
      sqlite3_step(stmt);
      sqlite3_finalize(stmt);

      sqlite3_close(db);
   }

   static QStringList getRecords(){
      QStringList records;
      sqlite3_open(dbName,&db);

      sqlite3_stmt * stmt {nullptr};
      const char* query = "SELECT link FROM used_link";
      sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);;

      while (sqlite3_step(stmt) == SQLITE_ROW) {
         const unsigned char *text = sqlite3_column_text(stmt, 0);
         if(text){
            records.append(QString((const char*)text));
         }
      }

      sqlite3_finalize(stmt);
      sqlite3_close(db);
      return records;
   }

   private:
   static sqlite3* db;
   static const char *dbName;
};