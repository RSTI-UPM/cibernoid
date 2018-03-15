<%-- 
    Document   : index
    Created on : 20-feb-2017, 14:06:13
    Author     : Sol
--%>
<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page import="java.sql.DriverManager"%>
<%@page import="java.sql.Connection"%>
<%@page import="java.util.*" %> 
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>CiberNoid</title>
        <meta charset="UTF-8">
        <link rel="shortcut icon" href="favicon.ico">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <script type="text/javascript" src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
        
        <script language="Javascript">
	$(document).ready(function() {
		$('#submitsearchusers').click(function(event) {
			var nombreVar = $('#nombresearchuser').val();
			// Si en vez de por post lo queremos hacer por get, cambiamos el $.post por $.get
			$.post('SearchUser', {
				nombresearch : nombreVar
			}, function(responseText) {
				$('#buscadorusers').html(responseText);
			});
		});
	});
        </script>
      
<script language="Javascript">    

function limpiar(){
document.getElementById('buscadorusers').innerHTML="";
document.getElementById('nombresearchuser').innerHTML="";
$('#nombresearchuser').empty();
}
function mostrar(){
document.getElementById('buscarusers').style.display = 'block';
document.getElementById('buscadorusers').style.display = 'block';}
function ocultar(){
document.getElementById('buscarusers').style.display = 'none';
document.getElementById('buscadorusers').style.display = 'none';
document.getElementById('formularioparametros').style.display = 'none';
document.getElementById('formulario').style.display = 'none';}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

function xmlhttpPost(strURL, queryStr) {
    var xmlHttpReq = false;
    var self = this;
    // Mozilla/Safari, opera etc
    if (window.XMLHttpRequest) {
        self.xmlHttpReq = new XMLHttpRequest();
    }
    // IE
    else if (window.ActiveXObject) {
        self.xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
    }else{
        alert("no ajax");
        return;
    }
    self.xmlHttpReq.open('POST', strURL, true);
    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    self.xmlHttpReq.onreadystatechange = function() {
        if (self.xmlHttpReq.readyState === 4) {
            updatepageConfirm(self.xmlHttpReq.responseText);
        }
    };
    self.xmlHttpReq.send(queryStr);
}

function updatepageConfirm(str){
    document.getElementById("adminSpan").innerHTML = str;
}
function adminUsers(){
ocultar();  
mostrar();
limpiar();
xmlhttpPost("adminUsers.jsp");
}

function sendForm(){
xhr = new XMLHttpRequest();
var url = "/webresources/claves";
xhr.open("POST", url, true);
xhr.setRequestHeader("Content-type", "application/json");
xhr.onreadystatechange = function () { 
    if (xhr.readyState == 4 && xhr.status == 200) {
        var json = JSON.parse(xhr.responseText);
        console.log(json)
    }
}
var idFile = document.getElementById('idFile').value;
var idUser = document.getElementById('idUser').value;
var grupo = document.querySelector('input[id="grupo"]:checked').value;
var operador = document.getElementById('operador').value;
var longitud = document.getElementById('lon').value;
var latitud = document.getElementById('lat').value;
var hora = document.getElementById('hora').value;
var dateMask = document.querySelector('input[id="dateMask"]:checked').value;
var fecha = document.getElementById('fecha').value;
var timeMask = document.querySelector('input[id="timeMask"]:checked').value;
var wifis = document.getElementById('wifis').value;
var data = JSON.stringify({"idFile":idFile,"idUser":idUser,"grupo":grupo,"operador":operador,"lat":latitud,"lon":longitud,"hora":hora,"dateMask":dateMask,"fecha":fecha,"timeMask":timeMask,"wifis":wifis});
xhr.send(data);
}
function adminDeps(){
ocultar();
limpiar();
xmlhttpPost("adminDeps.jsp");

}
function challenges(){
    ocultar();
limpiar();
xmlhttpPost("challenges.jsp");

}
function adminWifis(){
    ocultar();
limpiar();
xmlhttpPost("adminWifis.jsp");

}
function adminCoord(){
    ocultar();
limpiar();
xmlhttpPost("adminCoord.jsp");

}
async function newDep(){
    document.getElementById("formularioNewDept").submit();
    await sleep(500);
xmlhttpPost("adminDeps.jsp");
}
async function editDep(){
    document.getElementById("formularioEditDept").submit();
    await sleep(500);
xmlhttpPost("adminDeps.jsp");
}
async function deleteDep(){
    document.getElementById("formularioDeleteDept").submit();
    await sleep(500);
xmlhttpPost("adminDeps.jsp");
}
async function newUser(){
    document.getElementById("formularioNewUser").submit();
    await sleep(500);
xmlhttpPost("adminUsers.jsp");
}
async function editUser(){
    document.getElementById("formularioEditUser").submit();
    await sleep(500);
xmlhttpPost("adminUsers.jsp");
}
async function deleteUser(){
    document.getElementById("formularioDeleteUser").submit();
    await sleep(500);
xmlhttpPost("adminUsers.jsp");
}
async function newWifi(){
    document.getElementById("formularioNewWifi").submit();
    await sleep(500);
xmlhttpPost("adminWifis.jsp");
}
async function editWifi(){
    document.getElementById("formularioEditWifi").submit();
    await sleep(500);
xmlhttpPost("adminWifis.jsp");
}
async function deleteWifi(){
    document.getElementById("formularioDeleteWifi").submit();
    await sleep(500);
xmlhttpPost("adminWifis.jsp");
}
async function editCoord(){
    document.getElementById("formularioEditCoord").submit();
    await sleep(500);
xmlhttpPost("adminCoord.jsp");
}
</script>
        
    </head>
    <body>
        <div class="container">
        <div><h1>Servidor de retos de CiberNoid</h1></div>
        <form  id="search" method="get">
            <input class="btn btn-info" type=button onclick=challenges() value="Verificar retos">
            <input class="btn btn-info" type=button onclick=adminUsers() value="Administrar usuarios">
            <input class="btn btn-info" type=button onclick=adminDeps() value="Administrar departamentos">
            <input class="btn btn-info" type=button onclick=adminWifis() value="Administrar redes wifi">
            <input class="btn btn-info" type=button onclick=adminCoord() value="Administrar coordenadas">
        </form>
        
        <hr color="blue" size=2>
        <div id=adminSpan></div>
        <div class="container">
        <div id="formulario" style='display:block;'><h2>Challenges</h2></div>
        <form id="formularioparametros" style='display:block;'>
    <fieldset>
        <legend>Envio de parametros</legend><br/>
            <label>idFile</label>
                <input class="btn btn-default" id="idFile" name="idFile" type="number" value="0" step="1"/>
            <label>idUser</label>
                <input class="btn btn-default" id="idUser" name="idUser" type="number" value="0" step="1"/>
            <label>Grupo</label>
                <input class="btn btn-default" type="Radio" id="grupo" name="grupo" value="false" checked> No
                <input class="btn btn-default" type="Radio" id="grupo" name="grupo" value="true"> Sí <br/><br/>
            <label>Operador</label>
                <input class="btn btn-default" id="operador" name="operador" value="operador" type="text" /><br/><br/>

            <label>Lat</label>
                <input class="btn btn-default" id="lat" name="lat" type="number" value="0.0000" step="0.0001"/>
            <label>Lon</label>
                <input class="btn btn-default" id="lon" name="lon" type="number" value="0.0000" step="0.0001"/>
            <br/><br/>
            <label>Hora de inicio</label>
                <input class="btn btn-default" id="hora" name="hora" type="time" value="08:00" step="1800"/>
            <label>Horas de trabajo</label>
                <input class="btn btn-default" type="Radio" id="timeMask" name="timeMask" value="1" checked> 1 hora
                <input class="btn btn-default" type="Radio" id="timeMask" name= "timeMask" value="2"> 2 horas
                <input class="btn btn-default" type="Radio" id="timeMask" name= "timeMask" value="4"> 4 horas
                <input class="btn btn-default" type="Radio" id="timeMask" name= "timeMask" value="8"> 8 horas<br/><br/>
            <label>Fecha de creación</label>
                <input class="btn btn-default" id="fecha" name="fecha" type="date" value="2017-01-01" step="1"/>
            <label>Duración de fichero</label>
                <input class="btn btn-default" type="Radio" id="dateMask" name="dateMask" value="1" checked> 2 semanas
                <input class="btn btn-default" type="Radio" id="dateMask" name= "dateMask" value="2"> 1 mes
                <input class="btn btn-default" type="Radio" id="dateMask" name= "dateMask" value="4"> 2 meses
                <input class="btn btn-default" type="Radio" id="dateMask" name= "dateMask" value="8"> 4 meses<br/><br/>
            <label>Redes wifis</label>
                <input class="btn btn-default" id="wifis" name="wifis" value="wifi1,canal,potencia;wifi2,..." type="text" /><br/><br/>
            <label>Comprueba los parametros y envia</label>
                <input class="btn btn-success" type=button onclick=sendForm() value="Enviar">
    </fieldset>
        </form><br/></div>
        <form id="buscarusers" method="post" onsubmit="return false;" style='display:none;'>
            <h3>Buscar usuario</h3><br/>
            <label>Nombre</label>
                <input class="btn btn-default" id="nombresearchuser" name="nombresearchuser" value="" type="text" />
            <input class="btn btn-success" id="submitsearchusers" name="submitsearchusers" type="submit" value="Buscar usuario" />
        </form>
        </br></br>
        <div id="buscadorusers" style='display:none;'></div>
        <br/>
        </div>
    </body>
</html>
