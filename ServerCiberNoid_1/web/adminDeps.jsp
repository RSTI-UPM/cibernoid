<%-- 
    Document   : admin
    Created on : 21-feb-2017, 9:39:55
    Author     : Sol
--%>

<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page import="java.sql.DriverManager"%>
<%@page import="java.sql.PreparedStatement"%>
<%@page import="java.sql.Connection"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
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
  height: 114px;
  min-height: calc(200px + 1 px);
  /*use calc for fixed ie9 & <*/
  overflow-Y: scroll;
}
tr {
  display: block;
  overflow: hidden;
}

th, td {
  width: 20%;
  float:left;
}
td {
  padding: .5rem 0 .5rem 1rem;
}
        </style>
        
        <script language="Javascript">

    </script>    
    </head>
    <body>
        <div id=deps class="container">
        <div><h2>Administración de departamentos</h2></div>
        <div><h3>Lista de departamentos</h3>
        <table id="table" class='table table-striped' style= 'cellspacing'='1'>
        <thead>
        <tr class='info'>
        <th class='text-center'> NOMBRE </th>
        <th class='text-center'> ID </th> 
        <th class='text-center'> HORA DE INICIO </th>
        <th class='text-center'> JORNADA </th>
        <th class='text-center'> DURACIÓN FICHEROS </th>
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
                ResultSet rs= stmt.executeQuery("SELECT * FROM departamentos");
                Integer a = null;
                try{
                while(rs.next()){
                    //out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                    out.println("<tr class='info'>");
                    out.println("<td class='text-center'>"+rs.getString("nombre")+"</td>");
                    out.println("<td class='text-center'>"+rs.getInt("id")+"</td>");
                    out.println("<td class='text-center'>"+rs.getString("horario")+"</td>");                   
                    out.println("<td class='text-center'>"+rs.getInt("mascara_hora")+" horas"+"</td>");
                    out.println("<td class='text-center'>"+((double)rs.getInt("mascara_fecha"))/2+ " meses"+"</td>");
                    out.println("</tr>");
                    a=rs.getInt("id");

                }
                
                stmt.close();
                rs.close();
                }catch(Exception e){
                    out.println(e);
                }

               
                
                connection.close();
            }
        }%>
        </tbody>
        </table>
            </div>
        <br/>
        <div class="col-md-4"><form id="formularioNewDept" action="http://localhost:8084/ServerCiberNoid_1/webresources/deps/newdept" method="post">
            
        <fieldset>
        <legend>Nuevo departamento</legend><br/>
            <label>ID del departamento</label>
                <input class="btn btn-default" id="id" name="id" type="number" value="0" step="1"/><br/><br/>
            <label>Nombre del departamento</label>
                <input class="btn btn-default" id="nombre" name="nombre" value="departamento" type="text" /><br/><br/>
            <label>Hora de inicio</label>
                <input class="btn btn-default" id="hora" name="hora" type="time" value="08:00" step="1800"/><br/><br/>
            <label>Horas de trabajo</label><br/>
                <input class="btn btn-default" type="Radio" name="timeMask" value="1" checked> 1 hora
                <input class="btn btn-default" type="Radio" name= "timeMask" value="2"> 2 horas
                <input class="btn btn-default" type="Radio" name= "timeMask" value="4"> 4 horas
                <input class="btn btn-default" type="Radio" name= "timeMask" value="8"> 8 horas<br/><br/>
            <label>Duración de fichero</label><br/>
                <input class="btn btn-default" type="Radio" name="dateMask" value="1" checked> 2 semanas
                <input class="btn btn-default" type="Radio" name= "dateMask" value="2"> 1 mes
                <input class="btn btn-default" type="Radio" name= "dateMask" value="4"> 2 meses
                <input class="btn btn-default" type="Radio" name= "dateMask" value="8"> 4 meses<br/><br/>
            <label>Comprueba los parametros y envia</label>
                <!--input class="btn btn-success" id="enviar" name="enviar" type="submit" value="Nuevo departamento" /-->
                <input class="btn btn-success" type=button onclick=newDep() value="Nuevo departamento">
    </fieldset>
</form></div>
        
        <div class="col-md-4"><form id="formularioEditDept" action="http://localhost:8084/ServerCiberNoid_1/webresources/deps/editdept" method="post">
        <fieldset>
        <legend>Editar departamento con ID</legend><br/>
            <label>ID del departamento</label>
                <input class="btn btn-warning" id="id" name="id" type="number" value="0" step="1"/><br/><br/>
            <label>Nombre del departamento</label>
                <input class="btn btn-default" id="nombre" name="nombre" value="departamento" type="text" /><br/><br/>
            <label>Hora de inicio</label>
                <input class="btn btn-default" id="hora" name="hora" type="time" value="08:00" step="1800"/><br/><br/>
            <label>Horas de trabajo</label><br/>
                <input class="btn btn-default" type="Radio" name="timeMask" value="1" checked> 1 hora
                <input class="btn btn-default" type="Radio" name= "timeMask" value="2"> 2 horas
                <input class="btn btn-default" type="Radio" name= "timeMask" value="4"> 4 horas
                <input class="btn btn-default" type="Radio" name= "timeMask" value="8"> 8 horas<br/><br/>
            <label>Duración de fichero</label><br/>
                <input class="btn btn-default" type="Radio" name="dateMask" value="1" checked> 2 semanas
                <input class="btn btn-default" type="Radio" name= "dateMask" value="2"> 1 mes
                <input class="btn btn-default" type="Radio" name= "dateMask" value="4"> 2 meses
                <input class="btn btn-default" type="Radio" name= "dateMask" value="8"> 4 meses<br/><br/>
            <label>Comprueba los parametros y envia</label>
                <!--input class="btn btn-success" id="enviar" name="enviar" type="submit" value="Editar departamento" /-->
                <input class="btn btn-warning" type=button onclick=editDep() value="Editar departamento">
    </fieldset>
</form></div>
        
        <div class="col-md-4"><form id="formularioDeleteDept" action="http://localhost:8084/ServerCiberNoid_1/webresources/deps/deletedept" method="post">
            <fieldset>
        <legend>Eliminar departamento</legend><br/>
             <label>ID del departamento</label>
                <input class="btn btn-default" id="id" name="id" type="number" value="0" step="1"/><br/><br/>
            <!--input class="btn btn-danger" id="enviar" name="enviar" type="submit" value="Borrar departamento" /-->
            <input class="btn btn-danger" type=button onclick=deleteDep() value="Eliminar departamento">
            </fieldset>    
        </form></div>
        <br/></div>
    </body>
</html>
