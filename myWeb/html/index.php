<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
  <script src="https://code.jquery.com/jquery-3.6.0.slim.min.js" integrity="sha256-u7e5khyithlIdTpu22PHhENmPcRdFiHRjhAuHcs05RI=" crossorigin="anonymous"></script>
  <title>Monitoring System</title>
</head>
<body>
  <div class="container">
      <div>
      <?php
        require('phpScript/dbconnect.php');
        $sql = "SELECT id, sensor, location, temp, humid, reading_time FROM SensorData ORDER BY id DESC";
        $tatalRow = mysqli_num_rows($conn->query($sql));
        $countLoop = 1;
        // echo "tatal row is : " . $tatalRow;

        echo '<table class="table table-info">
              <tr class="table-dark"> 
                <td>ID</td> 
                <td>Sensor</td> 
                <td>Location</td> 
                <td>Temp</td> 
                <td>Humid</td>
                <td>Timestamp</td> 
              </tr>';
        
        if ($result = $conn->query($sql)) {
            while ($row = $result->fetch_assoc()) {
                
                if($countLoop < $tatalRow-($tatalRow-11)) {
                // $row_id = $row["id"];
                $row_sensor = $row["sensor"];
                $row_location = $row["location"];
                $row_temp = $row["temp"];
                $row_humid = $row["humid"]; 
                $row_reading_time = $row["reading_time"];

                echo '<tr> 
                        <td>' . $countLoop . '</td> 
                        <td>' . $row_sensor . '</td> 
                        <td>' . $row_location . '</td> 
                        <td>' . $row_temp . '</td> 
                        <td>' . $row_humid . '</td>
                        <td>' . $row_reading_time . '</td> 
                      </tr>';
                }
                if($countLoop == 1){
                  echo '<h1 class="text-center my-4">"Current Temp and Humid is : ' . $row_temp . ' C and ' . $row_humid . ' % </h1>';
                }
                $countLoop++;
            }
            $result->free();
        }
        $conn->close();
      ?> </table>
      <!-- End of table -->
    </div>
  </div>

</body>
</html>