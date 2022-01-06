<?php
    // $port1 = $_POST['port1'];
    // $port2 = $_POST['port2'];
    // $port3 = $_POST['port3'];
    $port = $_POST['port'];
    $status = $_POST['status'];
    $file = file_get_contents("port.json");
    $data = json_decode($file, true);

    if($port == 1) {
        $data [] = array (
            'port1' => $status,
            'port2' => $data[count($data)-1]["port2"],
            'port3' => $data[count($data)-1]["port3"],
            'waktu' => array(
                'tanggal' => date('Y/m/d'),
                'jam' => date('H:i:s')
            )
        );
    }
    if($port == 2) {
        $data [] = array (
            'port1' => $data[count($data)-1]["port1"],
            'port2' => $status,
            'port3' => $data[count($data)-1]["port3"],
            'waktu' => array(
                'tanggal' => date('Y/m/d'),
                'jam' => date('H:i:s')
            )
        );
    }
    if($port == 3) {
        $data [] = array (
            'port1' => $data[count($data)-1]["port1"],
            'port2' => $data[count($data)-1]["port2"],
            'port3' => $status,
            'waktu' => array(
                'tanggal' => date('Y/m/d'),
                'jam' => date('H:i:s')
            )
        );
    }
    
    $saveData = json_encode($data, JSON_PRETTY_PRINT);
    $save = file_put_contents("port.json", $saveData);
    if ($save) {
        $respon [] = array(
            'status' => true,
            'msg' => 'success update relay'
        );
        echo json_encode($respon, JSON_PRETTY_PRINT);
    } else {
        $respon [] = array(
            'status' => false,
            'msg' => 'fail update relay'
        );
        echo json_encode($respon, JSON_PRETTY_PRINT);
    }
?>