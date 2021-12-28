<?php
    require("dbconnect.php");
    $sql = "SELECT id, sensor, location, temp, humid, reading_time FROM SensorData ORDER BY id DESC";
	$result = mysqli_query($conn, $sql);
	$intNumField = mysqli_num_fields($result);
	$resultArray = array();
	while($row = mysqli_fetch_array($result, MYSQLI_ASSOC))
	{
		array_push($resultArray,$row);
	}
    $conn->close();
    // echo '<h1>' . "Test JSON Output : " . '</h1>';
	echo json_encode($resultArray);
?>