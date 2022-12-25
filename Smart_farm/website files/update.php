<?php
header("Access-Control-Allow-Origin: *");
$servername = "localhost";
$username = "id18526731_value";
$password = "H4Qw^?TM?9fi\Dd6";
$dbname = "id18526731_moisturesensor";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

if(isset($_GET['temp'])){
    $temp = $_GET['temp'];
    
    $sql = "UPDATE iot_moist SET temp= $temp";
    $result = $conn->query($sql);
}
if(isset($_GET['hum'])){
    $hum= $_GET['hum'];
    
    $sql = "UPDATE iot_moist SET hum= $hum";
    $result = $conn->query($sql);
}
if(isset($_GET['moisture'])){
    $moisture = $_GET['moisture'];
    
    $sql = "UPDATE iot_moist SET moisture= $moisture";
    $result = $conn->query($sql);
}

if(isset($_GET['air'])){
  $air= $_GET['air'];
  
  $sql = "UPDATE iot_moist SET air= $air";
  $result = $conn->query($sql);
}

if ($conn->query($sql) === TRUE) {
  echo "Record updated successfully";
} else {
  echo "Error updating record: " . $conn->error;
}

$conn->close();
?>