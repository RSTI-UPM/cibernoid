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
        <style type="text/css" >

table * {height: auto; min-height: none;} /* fixed ie9 & <*/
table {
  table-layout: fixed;
  margin: 1rem auto;
  width: 100%;
}
thead {
  text-align: center;
  z-index: 2;
}
thead tr {
  z-index: 2;
}
th {
  padding: .7rem 0;
}
tbody {
  display: block;
  height: 76px;
  min-height: calc(200px + 1 px);
  /*use calc for fixed ie9 & <*/
  overflow-Y: scroll;
}
tr {
  display: block;
  overflow: hidden;
}

th, td {
  width: 50%;
  float:left;
}
td {
  padding: .5rem 0 .5rem 1rem;
}
        </style>
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
        
    </head>
    <body>
        <div class="container">
        <div><h2>Administración de redes wifi</h2></div>
        <div><h3>Lista de redes wifi</h3>
        <table class='table table-striped' style= 'cellspacing'='1'>
        <thead>
        <tr class='info'>
        <th class='text-center'> SSID </th>
        <th class='text-center'> Potencia </th>            
        </tr>
        </thead>
        <tbody>
        <% if (true) { 
        Class.forName("org.postgresql.Driver");
        
        String url ="jdbc:postgresql://localhost:5432/postgres";
        String usuario="postgres";
        String contraseña="123";

        Connection connection = DriverManager.getConnection(url, usuario, contraseña);
        
        if(!connection.isClosed()){
            Statement stmt = connection.createStatement();
            ResultSet rs= stmt.executeQuery("SELECT * FROM wifis");

            while(rs.next()){
                //out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                out.println("<tr class='info'>");
                out.println("<td class='text-center'>"+rs.getString("ssid")+"</td>");
		out.println("<td class='text-center'>"+rs.getInt("potencia")+"</td>");
		out.println("</tr>");
            }

            stmt.close();
            rs.close();
            connection.close();
        }
        }%>
        </tbody>
        </table>
        </div>
            </div>
        <br/>
        <div class="col-md-4"><form id="formularioNewWifi" action="http://localhost:8084/ServerCiberNoid_1/webresources/wifis/newwifi" method="post">
            <fieldset>
        <legend>Nueva red wifi</legend><br/>
             <label>SSID de la red</label>
                <input class="btn btn-default" id="ssid" name="ssid" type="text" value="ssid"/><br/><br/>
            <label>Potencia</label>
                <input class="btn btn-default" id="potencia" name="potencia" type="number" value="-80" step="1"/><br/><br/>
            <!--input class="btn btn-success" id="enviar" name="enviar" type="submit" value="Nueva red wifi" /-->
            <input class="btn btn-success" type=button onclick=newWifi() value="Nueva red wifi">
            </fieldset>    
        </form></div>
        
        <div class="col-md-4"><form id="formularioEditWifi" action="http://localhost:8084/ServerCiberNoid_1/webresources/wifis/editwifi" method="post">
            <fieldset>
        <legend>Modificar red wifi</legend><br/>
             <label>SSID de la red</label>
                <input class="btn btn-warning" id="ssid" name="ssid" type="text" value="ssid"/><br/><br/>
            <label>Potencia</label>
                <input class="btn btn-default" id="potencia" name="potencia" type="number" value="-80" step="1"/><br/><br/>
            <!--input class="btn btn-warning" id="enviar" name="enviar" type="submit" value="Editar red wifi" /-->
            <input class="btn btn-warning" type=button onclick=editWifi() value="Editar red wifi">
            </fieldset>    
        </form></div>
        
        <div class="col-md-4"><form id="formularioDeleteWifi" action="http://localhost:8084/ServerCiberNoid_1/webresources/wifis/deletewifi" method="post">
            <fieldset>
        <legend>Eliminar red wifi</legend><br/>
             <label>SSID de la red</label>
                <input class="btn btn-default" id="ssid" name="ssid" type="text" value="ssid"/><br/><br/>
            <!--input class="btn btn-danger" id="enviar" name="enviar" type="submit" value="Eliminar red wifi" /-->
            <input class="btn btn-danger" type=button onclick=deleteWifi() value="Eliminar red wifi">
            </fieldset>    
        </form></div><br/>
    
</div></body>
</html>
