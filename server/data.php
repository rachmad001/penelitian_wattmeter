<?php  
	header("Access-Control-Allow-Origin: *");
	include "config.php";

	$result = mysqli_query($mysqli, "select * from sensor");
	$hasil = mysqli_fetch_assoc($result);
	$myObj = array(
		"volt" => $hasil["volt"],
		"ampere" => $hasil["ampere"],
		"watt" => $hasil["watt"]
	);
	$myJson = json_encode($myObj);
	echo $myJson;
?>