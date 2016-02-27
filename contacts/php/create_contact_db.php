<?php
require_once("db_util.php");
class ContactDbCreator {
    private $db_name;
    private $table_name;
    private $field_name;
    private $field_image;
    private $field_phone;
    private $field_email;
    
    public function __construct($db_name="contacts_db") {
               $this->db_name = $db_name;
               $this->table_name = "contacts";
               $this->field_name = "Name";
               $this->field_image = "Image";
               $this->field_phone = "Phone";
               $this->field_email = "Email";
           }

    public function createContactDb() {
               DbUtil::getInstance()->init("localhost", "root", "root", $this->db_name);
               DbUtil::getInstance()->connect();
               $sql = "CREATE DATABASE IF NOT EXISTS {$this->db_name}";
               $result = DbUtil::getInstance()->getMySQLI()->query($sql);
               return $result;
           }

    public function createContactsTable() {
               $result = $this->createContactDb();
               if (!$result) {
                   // echo mysql_error();
               }
    
               $sql = "create table {$this->table_name} ({$this->field_image} varchar(50),
{$this->field_name} varchar(30) not null primary key,
{$this->field_phone} varchar(20) not null,
{$this->field_email} varchar(50),
insert_date TIMESTAMP)";

               $result = DbUtil::getInstance()->getMySQLI()->query($sql);
               if ($result) {
                   // TODO:
               } else {
                   // TODO:
               }
           }

    public function getContactsDbName() {
               return $this->db_name;
           }
    public function getContactsTableName() {
               return $this->table_name;
           }
    
    public function getContactsField_Name() {
               return $this->field_name;
           }

    public function getContactsField_Phone() {
               return $this->field_phone;
           }

    public function getContactsField_Email() {
               return $this->field_email;
           }

    public function getContactsField_Image() {
               return $this->field_image;
           }
    
}
?>