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
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script type="text/javascript" src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
        <script src="http://code.jquery.com/jquery-latest.js"></script>

        
        <title>JSP Page</title>
    </head>
    <body>
        <div class="container">
        <div><h2>Administración de GPS</h2></div>
        <div><h3>Parámetros GPS</h3>
        <table id="table" class='table table-striped' style= 'cellspacing'='1'>
        <thead>
        <tr class='info'>
        <th class='text-center'> LATITUD </th>
        <th class='text-center'> LONGITUD </th>
        <th class='text-center'> RADIO </th>
        </tr>
        </thead>
        <tbody>
        <%if (true) { 
        Class.forName("org.postgresql.Driver");
        
        String url ="jdbc:postgresql://localhost:5432/postgres";
        String usuario="postgres";
        String contraseña="123";

        Connection connection = DriverManager.getConnection(url, usuario, contraseña);
        
        if(!connection.isClosed()){
            Statement stmt = connection.createStatement();
            ResultSet rs= stmt.executeQuery("SELECT * FROM coordenadas");
            
            while(rs.next()){
                //out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                out.println("<tr class='info'>");
		out.println("<td class='text-center'>"+rs.getFloat(2)+"</td>");			
		out.println("<td class='text-center'>"+rs.getFloat(3)+"</td>");
		out.println("<td class='text-center'>"+rs.getInt(4)+"</td>");
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
        <br/>
        <div class="col-md-4"><form id="formularioEditCoord" action="http://localhost:8084/ServerCiberNoid_1/webresources/coord/editcoord" method="post">
            <fieldset>
        <legend>Modificación de coordenadas</legend><br/>
             <label>Latitud</label>
                <input class="btn btn-default" id="latitud" name="latitud" type="number" value="0" step="0.0001"/><br/><br/>
            <label>Longitud</label>
                <input class="btn btn-default" id="longitud" name="longitud" type="number" value="0" step="0.0001"/><br/><br/>
            <label>Radio</label>
                <input class="btn btn-default" id="radio" name="radio" value="20" type="number" /><br/><br/>
            <input class="btn btn-warning" type=button onclick=editCoord() value="Editar parámetros GPS">
            </fieldset>    
        </form></div>
    <br/></div>
    </body>
</html>
