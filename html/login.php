<?php
	session_start(); //starting session
	$error=''; // variable for error mssg

	if(isset($_POST['username'])) {
		if(empty($_POST['username']) || empty($_POST['password'])) {
			$error = "Give a username and password. . .";
		} else {
			$username=$_POST['username'];
			$password=$_POST['password'];

			if($username == "admin" && $password == "admin") {
				$_SESSION['login_user'] = $username;
				header("Location: index.php?p=Home");
			} else {
				$error = "Username or password is incorrect!";
			}
		}
		if(!empty($error)) {
			header("Location: loginForm.php?p=Login&err={$error}");
		}
	}


?>
