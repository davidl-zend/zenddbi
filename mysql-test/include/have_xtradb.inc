--source include/have_innodb.inc
if (!`SELECT count(*) FROM information_schema.plugins WHERE
      plugin_name = 'innodb' AND plugin_status = 'active' AND
      plugin_description LIKE '%xtradb%'`){
  skip Needs XtraDB engine;
}