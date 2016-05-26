
 #include <mysql/plugin.h>

 // From 5.6 we use the audit plugin interface
#include <mysql/plugin_audit.h>

#include <sql_parse.h>
#include <sql_class.h>
#include <my_global.h>
#include <sql_connect.h>
//#include <sql/sql_base.h>
//#include <sql/sql_table.h>
#include <sql_table.h>
//#include <sql/sql_view.h>
#include <sql_view.h>

#include <sql_base.h>
 // TODO: use mysql mutex instead of pthread
 /*
 #define pthread_mutex_lock  mysql_mutex_lock
 #define pthread_mutex_unlock  mysql_mutex_unlock
 #define pthread_mutex_init mysql_mutex_init
 #define pthread_mutex_destroy mysql_mutex_destroy
 #define pthread_mutex_t mysql_mutex_t
 */

// #include <sql/log.h>
#include <log.h>
