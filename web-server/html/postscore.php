<?php
    $conn = mysqli_connect('localhost','minions','bonehead','Minions') or die("Could not connect to server");

    $sql = "INSERT INTO scores (score, initials) VALUES (" . $_GET["score"] . ", '" . $_GET["initials"] . "');";

    print $sql;

    mysqli_query($conn, $sql) or die("Could not execute insert statement");
?>
