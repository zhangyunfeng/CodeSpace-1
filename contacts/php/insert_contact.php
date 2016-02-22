<?php
require_once("contact_db_util.php");

$contact_name = $_POST["name"];
$contact_tel = $_POST["tel_number"];

$db = new ContactDbUtil();
$db->insert_contact($contact_name, $contact_tel);

?>