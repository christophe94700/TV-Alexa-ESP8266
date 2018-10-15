function addLoadEvent(func) {  
      var oldonload = window.onload;  
      if (typeof window.onload != 'function') {  
        window.onload = func;  
      } else {  
        window.onload = function() {  
          if (oldonload) {  
            oldonload();  
          }  
          func();  
        }  
      }  
    } 
// Para1 variable requête Para2 variable requête item id du label	
function etat(para1,para2,item) {
 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
 if (xhttp.readyState == 4 && xhttp.status == 200) {
 document.getElementById(item).innerHTML = xhttp.responseText;
 }
 };
 xhttp.open('GET', 'Etat?'+para1+'='+para2, true);
 xhttp.send();
}   
 addLoadEvent(function() {
etat('wifi','ssid','ssid');
etat('wifi','ip','iplocal');
etat('wifi','routeur','iprouteur');
etat('wifi','host','host');
etat('wifi','ipdns','ipdns');
etat('wifi','mask','mask');
etat('conf','gmt','gmt');
etat('conf','alexa1','alexa1');
etat('conf','alexa2','alexa2');
    });  