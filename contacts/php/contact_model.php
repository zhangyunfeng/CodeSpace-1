<?php

class ContactModel {
    public $imguri;
    public $name;
    public $tel;
    public $email;

    public function __construct() {
        $args_num = func_num_args();
        $args = func_get_args();
        switch ($args_num) {
            case 3:
                $this->ContactModel_("imgs/default.png", $args[0], $args[1], $args[2]);
                break;
            case 4:
                $this->ContactModel_($args[0], $args[1], $args[2], $args[3]);
                break;
        }
    }
    
    public function ContactModel_($img_uri = "imgs/default.png", $name="", $tel="", $email="") {
               $this->imguri = $img_uri;
               $this->name = $name;
               $this->tel = $tel;
               $this->email = $email;        
    }
    
    
    
    public function toString() {
               echo "[$this->imguri, $this->name, $this->tel, $this->email]";
           }
}
?>