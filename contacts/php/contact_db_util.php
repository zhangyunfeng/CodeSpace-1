<?php
require_once("db_util.php");
require_once("contact_model.php");
require_once("create_contact_db.php");

class ContactDbUtil {
    private $contact_db_creator;
    public function __construct() {
               $this->contact_db_creator = new ContactDbCreator();
               $this->contact_db_creator->createContactsTable();
               
               DbUtil::getInstance()->init("localhost", "root", "root", $this->contact_db_creator->getContactsDbName());
           }


    // FIXME: 没有增加image字段， 图片功能暂时不实现
    function insert_contact($name, $tel_number, $email)
    {
        if (DbUtil::getInstance()->connect()) {

            $field_name = $this->contact_db_creator->getContactsField_Name();
            $field_phone = $this->contact_db_creator->getContactsField_Phone();
            $field_image = $this->contact_db_creator->getContactsField_Image();
            $field_email = $this->contact_db_creator->getContactsField_Email();
            $table_name = $this->contact_db_creator->getContactsTableName();
            
            $query = "insert into {$table_name} ({$field_name}, {$field_phone}, {$field_email}) values (\"{$name}\",\"{$tel_number}\",\"{$email}\");";
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                // do nothing 
            } else {
                echo "insert failed Error: " . mysql_error();
            }
        }
    }

    function delete_contact($name)
    {
        if (DbUtil::getInstance()->connect()) {
            $table_name = $this->contact_db_creator->getContactsTableName();
            $query = "delete from ${table_name} where Name=\'" . $name . "\.;";
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                echo "Delete " . $name . " successed.";
            } else {
                echo "Delete " . $name . " failed.";
            }
        }
        
    }

    function update_contact($name, $tel_number, $email) {
        if (DbUtil::getInstance()->connect()) {
            $field_name = $this->contact_db_creator->getContactsField_Name();
            $field_phone = $this->contact_db_creator->getContactsField_Phone();
            $field_image = $this->contact_db_creator->getContactsField_Image();
            $field_email = $this->contact_db_creator->getContactsField_Email();
            $table_name = $this->contact_db_creator->getContactsTableName();
            $query = "update {$table_name} set {$field_phone}=\'{$tel_number}\', {$field_email}=\'{$email}\' where Name=\'{$name}\';";
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
            $field_name = $this->contact_db_creator->getContactsField_Name();
            $field_phone = $this->contact_db_creator->getContactsField_Phone();
            $field_image = $this->contact_db_creator->getContactsField_Image();
            $field_email = $this->contact_db_creator->getContactsField_Email();
            $table_name = $this->contact_db_creator->getContactsTableName();
            $query = "select * from {$table_name} where {$field_name}=\"{$name}\"";
            $contacts_arr = array();
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                if ($result->num_rows > 0) {
                    while($row = $result->fetch_array()) {
                        array_push($contacts_arr, new ContactModel("", $row[0], $row[1], ""));
                    }
                }
            } else {
                return "{code:404, data:{}}";
            }
            $result = array("contacts" => $contacts_arr);
            return json_encode($result);
        }
        
    }

    ## query contacts
    function query_contacts() {
        $contacts_arr = array();
        if (DbUtil::getInstance()->connect()) {
            $field_name = $this->contact_db_creator->getContactsField_Name();
            $field_phone = $this->contact_db_creator->getContactsField_Phone();
            $field_image = $this->contact_db_creator->getContactsField_Image();
            $field_email = $this->contact_db_creator->getContactsField_Email();
            $table_name = $this->contact_db_creator->getContactsTableName();
            $query = "select * from {$table_name}";
            #print ($query);
            $result = DbUtil::getInstance()->getMySQLI()->query($query);
            if ($result) {
                while ($row = $result->fetch_array()) {
                    #echo ($row[0]) . "<br>";
                    #echo ($row[1]) . "<br>";
                    array_push($contacts_arr, new ContactModel($row[$field_name], $row[$field_phone], $row[$field_email]));
                }
            } else {
                return "{code:404, data:{}}";
            }
            $result = array("contacts" => $contacts_arr);
            return json_encode($result);
        }
    }
    
}
?>