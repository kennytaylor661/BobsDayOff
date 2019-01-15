<?php
    $conn = mysqli_connect('localhost','minions','bonehead','Minions') or die("Could not connect to server");

    $sql = "SELECT score, initials FROM scores ORDER BY score DESC LIMIT 5";

    $result = mysqli_query($conn, $sql) or die("Could not fetch scores");

    while($row = mysqli_fetch_assoc($result)) {
        print $row["score"] . "         " . $row["initials"] . "\n";
    }

	//print "JAK	17,400\n\n";
	//print "KEN	12,700\n";
	//print "BIL	11,800\n";
	//print "DER	9.300\n";
	//print "MEL	5,400\n";
?>
