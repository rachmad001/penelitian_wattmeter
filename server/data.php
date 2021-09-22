<?php  
	header("Access-Control-Allow-Origin: *");
	include "config.php";

	$result = mysqli_query($mysqli, "select * from sensor");
	$start = 0;
	while ($hasil = mysqli_fetch_assoc($result)){
    	$myObj[$start] = array(
    		"volt" => $hasil["volt"],
    		"ampere" => $hasil["ampere"],
    		"watt" => $hasil["watt"]
    	);
    	$start++;
	}
	$myJson = json_encode($myObj);
	echo $myJson;
?>