<?php  
	header("Access-Control-Allow-Origin: *");
	include "config.php";

	$volt = $_GET['volt'];
	$ampere = $_GET['ampere'];
	$watt = $_GET['watt'];
	$result = mysqli_query($mysqli, "update sensor set volt = $volt, ampere = $ampere, watt = $watt where id = 1");
	if ($result) {
		echo "{\"status\": \"success\"}";
	}
	else {
		echo "{\"status\": \"error\"}";
	}
?>
