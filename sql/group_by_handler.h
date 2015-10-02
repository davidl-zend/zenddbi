/*
   Copyright (c) 2014, 2015 SkySQL Ab & MariaDB Foundation

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*
  This file implements the group_by_handler interface. This interface
  can be used by storage handlers that can intercept summary or GROUP
  BY queries from MariaDB and itself return the result to the user or
  upper level. It is part of the Storage Engine API

  Both main and sub queries are supported. Here are some examples of what the
  storage engine could intersept:

  SELECT count(*) FROM t1;
  SELECT a,count(*) FROM t1 group by a;
  SELECT a,count(*) as sum FROM t1 where b > 10 group by a, order by sum;
  SELECT a,count(*) FROM t1,t2;
  SELECT a, (select sum(*) from t2 where t1.a=t2.a) from t2;
*/

/**
  The structure describing various parts of the query

  The engine is supposed to take out parts that it can do internally.
  For example, if the engine can return results sorted according to
  the specified order_by clause, it sets Query::order_by=NULL before
  returning.

  At the moment the engine must take group_by (or return an error), and
  optionally can take distinct, where, order_by, and having.

  The engine should not modify the select list. It is the extended SELECT
  clause (extended, because it has more items than the original
  user-specified SELECT clause) and it contains all aggregate functions,
  used in the query.
*/
struct Query
{
  List<Item> *select;
  bool        distinct;
  TABLE_LIST *from;
  Item       *where;
  ORDER      *group_by;
  ORDER      *order_by;
  Item       *having;
  // LIMIT
};

class group_by_handler
{
public:
  THD *thd;
  handlerton *ht;

  /*
    Temporary table where all results should be stored in record[0]
    The table has a field for every item from the Query::select list.
  */
  TABLE *table;

  group_by_handler(THD *thd_arg, handlerton *ht_arg)
    : thd(thd_arg), ht(ht_arg), table(0) {}
  virtual ~group_by_handler() {}

  /*
    Store pointer to temporary table and objects modified to point to
    the temporary table.  This will happen during the optimize phase.

    We provide new 'having' and 'order_by' elements here. The differ from the
    original ones in that these are modified to point to fields in the
    temporary table 'table'.

    Return 1 if the storage handler cannot handle the GROUP BY after all,
    in which case we have to give an error to the end user for the query.
    This is becasue we can't revert back the old having and order_by elements.
  */

  virtual bool init(Item *having_arg, ORDER *order_by_arg)
  {
    return 0;
  }

  bool ha_init(TABLE *temporary_table, Item *having_arg, ORDER *order_by_arg)
  {
    table= temporary_table;
    return init(having_arg, order_by_arg);
  }

  /*
    Functions to scan data. All these returns 0 if ok, error code in case
    of error
  */

  /*
    Initialize group_by scan, prepare for next_row().
    If this is a sub query with group by, this can be called many times for
    a query.
  */
  virtual int init_scan()= 0;

  /*
    Return next group by result in table->record[0].
    Return 0 if row found, HA_ERR_END_OF_FILE if last row and other error
    number in case of fatal error.
   */
  virtual int next_row()= 0;

  /* End scanning */
  virtual int end_scan()=0;

  /* Report errors */
  virtual void print_error(int error, myf errflag);
};
