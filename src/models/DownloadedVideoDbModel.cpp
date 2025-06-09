#include "../include/models/DownloadedVideoDbModel.hpp"

sqlite3* DownloadedVideoDbModel::db = nullptr;
const char * DownloadedVideoDbModel::dbName {"linksRecords.db"};