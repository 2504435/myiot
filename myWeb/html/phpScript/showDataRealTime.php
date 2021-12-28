<!DOCTYPE html>
<html>
<head>
<title>ThaiCreate.Com</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
<script src="http://code.jquery.com/jquery-latest.js"></script>
<meta charset=utf-8 />
<script>
  
function getDataFromDb()
{
	$.ajax({ 
				url: "phpGetData.php" ,
				type: "POST",
				data: ''
			})
			.success(function(result) { 
				var obj = jQuery.parseJSON(result);
					if(obj != '')
					{
						  //$("#myTable tbody tr:not(:first-child)").remove();
						  $("#myBody").empty();
						  $.each(obj, function(key, val) {
									var tr = "<tr>";
									tr = tr + "<td align='center'>" + val["id"] + "</td>";
									tr = tr + "<td align='center'>" + val["sensor"] + "</td>";
									tr = tr + "<td align='center'>" + val["location"] + "</td>";
									tr = tr + "<td align='center'>" + val["temp"] + "</td>";
									tr = tr + "<td align='center'>" + val["humid"] + "</td>";
									tr = tr + "<td align='center'>" + val["reading_time"] + "</td>";
									tr = tr + "</tr>";
									$('#myTable > tbody:last').append(tr);
						  });
					}

			});

}

setInterval(getDataFromDb, 1);   // 1000 = 1 second
</script>
</head>
<body>
<div class="container">
    <h1 align="center">My Web</h1>
    <table class="table table-info" width="600" border="1" id="myTable">
    <!-- head table -->
    <thead>
    <tr class="table-dark">
        <td> <div align="center">ID </div></td>
        <td> <div align="center">Sensor </div></td>
        <td> <div align="center">Location </div></td>
        <td> <div align="center">Temperature </div></td>
        <td> <div align="center">Humidity </div></td>
        <td> <div align="center">TimeRead </div></td>
    </tr>
    </thead>
    <!-- body dynamic rows -->
    <tbody id="myBody"></tbody>
    </table>
</div>

</body>
</html>