<?php
class DbUtil {
    private $hasInited = FALSE;
    private $mHost = "localhost";
    private $user = "";
    private $passwd = "";
    private $db = "";
    private $mysqli = null;
    private static $instance;
    
    private function __construct()
            {
                
            }

    public function __destruct()
            {
                if (!is_null($this->mysqli)) {
                    $this->mysqli->close();
                }
            }

    private function __clone()
            {
                
            }

    public static function getInstance()
                  {
                      if (!(self::$instance instanceof self)) {
                          self::$instance = new self();
                      }
                      return self::$instance;
                  }

    public function init($host_="localhost", $user_="", $passwd_="", $db_="")
           {
               if (!$this->hasInited) {
                   $this->mHost = $host_;
                   $this->user = $user_;
                   $this->passwd = $passwd_;
                   $this->db = $db_;
                   $this->hasInited = TRUE;
               }
           }

    public function connect()
           {
               if (!$this->hasInited) {
                   throw new Exception("Please Init first.");
               }
               if ($this->isConnected()) {
                   return TRUE;
               }
               // create mysqli object, and connect mysql
               $this->mysqli = new mysqli($this->mHost, $this->user, $this->passwd, $this->db);
               // check connecting success
               if (mysqli_connect_errno()) {
                   // failed
                   die("Connect to MySQL failed.") . mysqli_connect_error();
                   return FALSE;
               }
               $this->mysqli->set_charset("utf8");
               return TRUE;
           }

    public function isConnected()
           {
               if (is_null($this->mysqli)) {
                   return FALSE;
               }
               return TRUE;
           }

    public function getMySQLI()
           {
               return $this->mysqli;
           }
    
}

?>