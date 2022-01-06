<?php
$sensor = $_POST['data'];
$dataSensor = json_decode($sensor, true);
if (!in_array(null, $dataSensor)) {
    $file = file_get_contents("device.json");
    $data = json_decode($file, true);
    $data[] = array(
        'port1' => array(
            "voltage" => $dataSensor[0][0],
            "current" => $dataSensor[0][1],
            "power" => $dataSensor[0][2],
            "energy" => $dataSensor[0][3],
            "frequency" => $dataSensor[0][4],
            "pf" => $dataSensor[0][5]
        ),
        'port2' => array(
            "voltage" => $dataSensor[1][0],
            "current" => $dataSensor[1][1],
            "power" => $dataSensor[1][2],
            "energy" => $dataSensor[1][3],
            "frequency" => $dataSensor[1][4],
            "pf" => $dataSensor[1][5]
        ),
        'port3' => array(
            "voltage" => $dataSensor[2][0],
            "current" => $dataSensor[2][1],
            "power" => $dataSensor[2][2],
            "energy" => $dataSensor[2][3],
            "frequency" => $dataSensor[2][4],
            "pf" => $dataSensor[2][5]
        ),
        'waktu' => array(
            "tanggal" => date('Y/m/d'),
            "jam" => date('H:i:s')
        )
    );
    $dataSave = json_encode($data, JSON_PRETTY_PRINT);
    $save = file_put_contents("device.json", $dataSave);
}

$port = file_get_contents("../Relay/port.json");
$dataPort = json_decode($port, true);
echo json_encode($dataPort[count($dataPort) - 1], JSON_PRETTY_PRINT);
