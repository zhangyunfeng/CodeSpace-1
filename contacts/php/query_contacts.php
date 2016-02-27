<?php
require_once("contact_db_util.php");

@$name = $_GET["name"];

$db = new ContactDbUtil();

$result = "{code:404, data:{}}";
if (!$name) {
    $result = $db->query_contacts();
} else {
    $result = $db->query_contact_telnumber($name);    
}
echo $result;
?>