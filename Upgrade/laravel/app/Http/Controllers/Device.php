<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class Device extends Controller
{
    //
    public function addData(Request $req){
        $sensor = json_decode($req->input('data'), true);
        $checkdata = true;
        for ($i = 0; $i < count($sensor); $i++){
            if (isset($sensor[$i])){
                for ($j = 0; $j < count($sensor[$i]); $j++){
                    if (!isset($sensor[$i][$j])){
                        $checkdata = false;
                        break;
                    }
                }
            }
            else {
                $checkdata = false;
                break;
            }
            if (!$checkdata){
                break;
            }
        }
        if($checkdata){
            $jsonFile = file_get_contents("device.json");
            $data = json_decode($jsonFile, true);
            $data []= array(
                'port1' => array(
                    'voltage' => $sensor[0][0],
                    'current' => $sensor[0][1],
                    'power' => $sensor[0][2],
                    'energy' => $sensor[0][3],
                    'frequency' => $sensor[0][4],
                    'pf' => $sensor[0][5]
                ),
                'port2' => array(
                    'voltage' => $sensor[1][0],
                    'current' => $sensor[1][1],
                    'power' => $sensor[1][2],
                    'energy' => $sensor[1][3],
                    'frequency' => $sensor[1][4],
                    'pf' => $sensor[1][5]
                ),
                'port3' => array(
                    'voltage' => $sensor[2][0],
                    'current' => $sensor[2][1],
                    'power' => $sensor[2][2],
                    'energy' => $sensor[2][3],
                    'frequency' => $sensor[2][4],
                    'pf' => $sensor[2][5]
                ),
                'waktu' => array(
                    'tanggal' => date("Y/m/d"),
                    'jam' => date('H:i:s')
                )
            );
            $jsondata = json_encode($data, JSON_PRETTY_PRINT);
            $jsondatasensor = file_put_contents("device.json", $jsondata);
        }
        $relay = file_get_contents("relay.json");
        $relaydata = json_decode($relay, true);
        return $relaydata;
    }
}
