<?php
require_once("db_util.php");

class ContactDbUtil {

    public function __construct() {
               DbUtil::getInstance()->init("localhost", "root", "root", "contacts_db");
           }
    
    function insert_contact($name, $tel_number)
    {
        if (DbUtil::getInstance()->connect()) {
            $query = "insert into contacts values(\"" . $name . "\",\"" . $tel_number . "\");";
            print($query);
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                echo "insert succeed";
            } else {
                echo "insert failed Error: " . mysql_error();
            }
        }
    }

    function delete_contact($name)
    {
        if (DbUtil::getInstance()->connect()) {
            $query = "delete from contacts where Name=\'" . $name . "\.;";
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                echo "Delete " . $name . " successed.";
            } else {
                echo "Delete " . $name . " failed.";
            }
        }
        
    }

    function update_contact($name, $tel_number) {
        if (DbUtil::getInstance()->connect()) {
            $query = "update contacts set Name=\'" . $tel_number . "\' where Name=\'" . $name . "\';";
            print($query);
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                echo "Update success.";
            } else {
                echo "Update failed.";
            }
        }
    }

    function query_contact_telnumber($name) {
        if (DbUtil::getInstance()->connect()) {
            $query = "select * from contacts where Name=\"" . $name . "\"";
            print($query);
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                if ($result->num_rows > 0) {
                    while($row = $result->fetch_array()) {
                        echo ($row[0]) . "<br>";
                        echo ($row[1]) . "<br>";
                    }
                }
            } else {
                echo "query failed.";
            }
        }
        
    }

    
}
?>