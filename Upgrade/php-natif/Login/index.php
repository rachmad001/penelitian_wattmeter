<?php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $db = "pa";
    $port = "3307";
    $conn = mysqli_connect($servername, $username, $password, $db, $port);

    $user = $_POST['username'];
    $pass = $_POST['password'];

    $query = "select * from user where username = '$user' and password = '$pass'";
    $result = mysqli_query($conn, $query);
    if (mysqli_num_rows($result) > 0){
        $respon [] = array(
            'status' => true,
            'msg' => 'success login'
        );
        echo json_encode($respon, JSON_PRETTY_PRINT);
    }
    else {
        $respon [] = array(
            'status' => false,
            'msg' => 'fail login, username or password is wrong'
        );
        echo json_encode($respon, JSON_PRETTY_PRINT);
    }
?>