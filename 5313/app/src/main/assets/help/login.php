<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<?php

define("debug", 0);
//----MY-sql数据库连接设置-----
/************start*************/
// define("mysql_db_addr", "localhost");
// define("mysql_port", "3306");
// define("mysql_user", "root");
// define("mysql_pwd", "laomao");

define("mysql_db_addr", "w.rdc.sae.sina.com.cn");
define("mysql_port", "3306");
define("mysql_user", "nw1ml5yow0");
define("mysql_pwd", "502h1yhl3x12mlww241y35y23mlz3k5izlxk1jmj");

define("mysql_db_name", "app_laomao");

/************end*************/



$user_name = '' ;
$user_pwd = '' ;

function show_debug_info($str)
{
  if(debug > 0)
  {
    echo "$str";
  }
}

show_debug_info("start check ~~~");


if (!(isset($_GET['user']) && isset($_GET['passwd']))) {
  show_debug_info("error:request fail\n");
  return ;
}
else
{
  $user_name = $_GET['user'] ;
  $user_pwd = $_GET['passwd'];
}


$con = mysql_connect(mysql_db_addr . ':' . mysql_port, mysql_user, mysql_pwd);
if (!$con) {
  echo "error:fail connect mysql";
  return ;
}

mysql_select_db(mysql_db_name , $con); //要改成相应的数据库名

show_debug_info ("</br> db selected !!</br>");

$result = mysql_query("select * from login where user='$user_name' and passwd='$user_pwd' ");
if(mysql_num_rows($result))
{
  echo "result-ok" ;
  // while ($row = mysql_fetch_array($result)) {
  // //找到需要的数据的记录，并读出状态值
  // show_debug_info ("find user:".$row["user"]);
  // }
}
else
{
  echo "result-false" ;
show_debug_info ("result:ok");
}
mysql_close($con);

?>