<?php
if (!empty( $_GET['temp'] ))
{
 $temp1=$_GET['temp'];
}else{
 $temp1=-1;
}

$_GET=array();
$_POST=array();

//get date now time
$date = new DateTime();
//file name or you can use database
$file = 'temperature.txt';
//get txt file content
$current = file_get_contents($file);
//add string to txt file
$current .= $temp1." ".$date."\n";
//save txt file
file_put_contents($file, $current);
}
?>
