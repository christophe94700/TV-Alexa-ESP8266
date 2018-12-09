
function submitVal(name, val) {
	var xhttp = new XMLHttpRequest();
	xhttp.open('GET', 'set?' + name + '=' + val, true);
	xhttp.send();
	if (val=='off'){
		if (name=='device1') {
			document.getElementById("m1").style.color="green";
			document.getElementById("a1").style.color="#454545";
			
		}
		if (name=='device2') {
			document.getElementById("m2").style.color="green";
			document.getElementById("a2").style.color="#454545";
			
		}
		
	}
	if (val=='on'){
		if (name=='device1') {
			document.getElementById("m1").style.color="#454545";
			document.getElementById("a1").style.color="red";
		}
		if (name=='device2') {
			document.getElementById("m2").style.color="#454545";
			document.getElementById("a2").style.color="red";
		}
		
		
	}
}

function rafraichir() { 
	var date = new Date(),secondes = date.getSeconds(); 
	
	/* Fonction ' SECONDES ' */
	if (secondes <= 9) {
		secondes = '0' + secondes;
	}
	
	ntp();
	
}

setInterval(rafraichir, 1000);

function ntp() {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (xhttp.readyState == 4 && xhttp.status == 200) {
			document.getElementById('dateheure').innerHTML = xhttp.responseText;
		}
	};
	xhttp.open('GET', 'DateHeure', true);
	xhttp.send();
}

