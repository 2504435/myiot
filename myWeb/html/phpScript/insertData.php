<?php

require('dbconnect.php');
// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $sensor = $location = $temp = $humid = "";

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $api_key = test_input($_GET["api_key"]);
    if($api_key == $api_key_value) {
        $sensor = test_input($_GET["sensor"]);
        $location = test_input($_GET["location"]);
        $temp = test_input($_GET["temp"]);
        $humid = test_input($_GET["humid"]);
        
        $sql = "INSERT INTO SensorData (sensor, location, temp, humid)
        VALUES ('" . $sensor . "', '" . $location . "', '" . $temp . "', '" . $humid . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        // check whether temp value exceed or not
        if($temp > 35){
            require("../phpLineNotify/notify.php");
        }
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}