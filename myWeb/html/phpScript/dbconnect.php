<?php

    $servername = "db";
    // REPLACE with your Database name
    $dbname = "surapong_db";
    // REPLACE with Database user
    $username = "surapong";
    // REPLACE with Database user password
    $password = "kali";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 
        
?>