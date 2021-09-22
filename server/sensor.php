<?php  
	header("Access-Control-Allow-Origin: *");
	include "config.php";

	$volt = $_GET['volt'];
	$ampere = $_GET['ampere'];
	$watt = $_GET['watt'];
	$ampere1 = $_GET['ampere1'];
	$watt1 = $_GET['watt1'];
	$ampere2 = $_GET['ampere2'];
	$watt2 = $_GET['watt2'];
	$result = mysqli_query($mysqli, "update sensor set volt = $volt, ampere = $ampere, watt = $watt where id = 1");
	$result1 = mysqli_query($mysqli, "update sensor set volt = $volt, ampere = $ampere1, watt = $watt1 where id = 2");
	$result2 = mysqli_query($mysqli, "update sensor set volt = $volt, ampere = $ampere2, watt = $watt2 where id = 3");
	if ($result && $result1 && $result2) {
		echo "{\"status\": \"success\"}";
	}
	else {
		echo "{\"status\": \"error\"}";
	}
?>