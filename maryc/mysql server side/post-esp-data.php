<?php

$api_key_value = "12345";
$hostname = "localhost";
$username = "root";
$password = "Admin123!";

$dbname = "example_esp_data";

$api_key = "";
$value = "";
$x = "";
$y = "";
$z = "";
$time = "";
$table_name = "";
$sensor_name = "";

echo "Getting started.";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
$api_key = find_input($_POST["api_key"]);
    
    if($api_key == $api_key_value) {
    
    	$table_name = find_input($_POST["table_name"]);
        $conn = new mysqli($hostname, $username, $password, $dbname);
        if ($conn->connect_error) {
        	echo "Connection failed...";
        	die("Connection failed: " . $conn->connect_error);
        	
        } 
    	if($table_name == "Heart")
    	{
    		$sensor_name = find_input($_POST["sensor_name"]);
        	$value = find_input($_POST["value"]);
        	$time = find_input($_POST["time"]);

        
        $sql = "INSERT INTO Heart (sensor_name,value,time)
        VALUES ('" . $sensor_name . "','" . $value . "', '" . $time . "')";
        }
        if($table_name == "Oxygen")
    	{
    		$sensor_name = find_input($_POST["sensor_name"]);
        	$value = find_input($_POST["value"]);
        	$time = find_input($_POST["time"]);

        
        $sql = "INSERT INTO Oxygen (sensor_name,value,time)
        VALUES ('" . $sensor_name . "','" . $value . "', '" . $time . "')";
        }
        if($table_name == "Accelerometer")
    	{
    		$sensor_name = find_input($_POST["sensor_name"]);
        	$x = find_input($_POST["x"]);
        	$y = find_input($_POST["y"]);
        	$z = find_input($_POST["z"]);
        	$time = find_input($_POST["time"]);

        
        $sql = "INSERT INTO Accelerometer (sensor_name, x, y, z, time)
        VALUES ('" . $sensor_name . "','" . $x . "', '" . $y . "','" . $z . "','" . $time . "')";
        }
        $conn->query($sql);
        $conn->close();
    	
	}
	echo "Data received.";	
    
}



function find_input($data) {

    $data = trim($data);
    
    $data = stripslashes($data);
    
    $data = htmlspecialchars($data);
    
    return $data;
}
?>
