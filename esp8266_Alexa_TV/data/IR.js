window.onload=function(){
	
	function clicked(){
		
		var cl = this.className;
		if (this.id=="ir") {
			if (/selected/.test(cl)) {
				this.className = cl.replace(" selected", "");
				selected=removeByValue(selected, this.innerHTML);
				}else {
				this.className += " selected";
				selected.push(this.innerHTML);
				
			}
			console.log(selected[0]); // Visualisation de la sélection
			console.log(selected[1]);
			console.log(selected[2]);
			console.log(selected[3]);
			console.log(selected[4]);
			}else{
			valeurIR=ircode.innerHTML.split(" ");
			console.log(this.id);
			var valid="IR "+(this.id)+1;
			document.getElementById(valid).value=valeurIR[0] ; 
			var valid="IR "+(this.id)+0;
			document.getElementById(valid).value=valeurIR[2].substring(2) ;
			var valid="IR "+(this.id)+2;
			document.getElementById(valid).value=valeurIR[4] ; 
		}
	}
	
	function valider(e){
		e.preventDefault();
		
		var i = 0,
		l = selected.length;
		
		for( ; i<l; i+=1) {
			
			envoie="";
			num=0;
			//Code IR
			if ((document.getElementById(selected[i]+0).value)!=null) envoie=envoie+document.getElementById(selected[i]+0).value+",";	
			// Sélection du Protocole
			if ((document.getElementById(selected[i]+1).value)!=null) envoie=envoie+document.getElementById(selected[i]+1).value+",";
			// Sélection du Nbit
			if ((document.getElementById(selected[i]+2).value)!=null) envoie=envoie+document.getElementById(selected[i]+2).value+",";
			// Sélection de la répétition
			if ((document.getElementById(selected[i]+3).value)!=null) envoie=envoie+document.getElementById(selected[i]+3).value+",";
			// Sélection de la commande en mode marche ou arrêt ou marche et arrêt 
			num=(ListIndex("marche", (selected[i]+4)));
			envoie=envoie+num;
			valeur=selected[i].split(" ");
			submitVal("ircode", (((valeur[1]).toString())+","+envoie));
		}
		
		l == 0 && alert( "Vous n'avez rien choisi :(");
	}
	
	var tr = document.querySelectorAll("#table td "),
	a = document.querySelector("a"),
	selected = [],
	i = 0,
	l = tr.length;
	
	for ( ; i<l; i++) tr[i].addEventListener("click", clicked, false);
	
	a.addEventListener("click", valider, false);
	
	function ListIndex(Liste, Input) {
		// Index dans liste de choix
		datalist = document.getElementById (Liste);
		input = document.getElementById (Input);
		for (var j=0;j<datalist.options.length;j++){
			if (datalist.options[j].value == input.value){ 
				console.log(j);
			break;}
		}
		return j
	}
	
	function submitVal(name, val) {
		var xhttp = new XMLHttpRequest();
		xhttp.open('GET', 'set?' + name + '=' + val, true);
		xhttp.send();
	}
	function removeByValue(array, value){
		return array.filter(function(elem, _index){
			return value != elem;
		});
	}
	function enforce_maxlength(event) {
		var t = event.target;
		if (t.hasAttribute('maxlength')) {
			t.value = t.value.slice(0, t.getAttribute('maxlength'));
		}
	}
	
	// Global Listener for anything with an maxlength attribute.
	// I put the listener on the body, put it on whatever.
	document.body.addEventListener('input', enforce_maxlength);
}

setInterval(IrCode, 500);

function IrCode() {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (xhttp.readyState == 4 && xhttp.status == 200) {
			document.getElementById('ircode').innerHTML = xhttp.responseText;
		}
	};
	xhttp.open('GET', 'IrCode', true);
	xhttp.send();
}			