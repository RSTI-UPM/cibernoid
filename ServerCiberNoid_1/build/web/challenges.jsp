<%-- 
    Document   : admin
    Created on : 21-feb-2017, 9:39:55
    Author     : Sol
--%>

<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page import="java.sql.DriverManager"%>
<%@page import="java.sql.Connection"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
        
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
        
    </head>
    <body>
        <div class="container">
        <div><h2>Challenges</h2></div>
        <form id="formularioparametros" target="_blank">
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
    </body>
</html>
