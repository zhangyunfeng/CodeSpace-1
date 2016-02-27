<?php
require_once("contact_db_util.php");

$contact_name = $_POST["name"];
$contact_tel = $_POST["tel_number"];
$contact_email = $_POST["email"];

$db = new ContactDbUtil();
$db->insert_contact($contact_name, $contact_tel, $contact_email);
echo "{}";  // avoid ajax run error()
?>