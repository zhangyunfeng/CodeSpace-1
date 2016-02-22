<?php
require_once("contact_db_util.php");

$name = $_GET["name"];

if ($name == "*") {
    $db = new ContactDbUtil();
    $db->query_contact_telnumber($name);
}
?>