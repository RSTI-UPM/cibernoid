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
  width: 25%;
  float:left;
}
td {
  padding: .5rem 0 .5rem 1rem;
}

        </style>
        
        <title>JSP Page</title>
    </head>
    <body>
        <div class="container">
        <div><h2>Administración de usuarios</h2></div>
        <div><h3>Lista de usuarios</h3>
        <table id="table" class='table table-striped' style= 'cellspacing'='1'>
        <thead>
        <tr class='info'>
        <th class='text-center'> ID </th>
        <th class='text-center'> NOMBRE </th>
        <th class='text-center'> DEPARTAMENTO </th>
        <th class='text-center'> ID DEPARTAMENTO </th>
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
            ResultSet rs= stmt.executeQuery("SELECT usuarios.id,usuarios.nombre,departamentos.nombre,usuarios.departamento FROM usuarios INNER JOIN departamentos ON usuarios.departamento=departamentos.id");
            while(rs.next()){
                //out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                out.println("<tr class='info'>");
                out.println("<td class='text-center'>"+rs.getInt(1)+"</td>");
		out.println("<td class='text-center'>"+rs.getString(2)+"</td>");			
		out.println("<td class='text-center'>"+rs.getString(3)+"</td>");
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
        <!--form id="buscar" action="/searchuser" method="post" >
            <h3>Buscar usuario</h3><br/>
            <label>Nombre</label>
                <input id="nombresearch" name="nombresearch" value="" type="text" /><br/><br/>
            <input id="submitsearch" name="submitsearch" type="submit" value="Buscar usuario" />
        </form>
        <div id="buscador"></div>
        <br/-->
        <div class="col-md-4"><form id="formularioNewUser" action="http://localhost:8084/ServerCiberNoid_1/webresources/users/newuser" method="post">
            <fieldset>
        <legend>Nuevo usuario</legend><br/>
             <label>ID del usuario</label>
                <input class="btn btn-default" id="id" name="id" type="number" value="0" step="1"/><br/><br/>
            <label>ID del departamento</label>
                <input class="btn btn-default" id="departamento" name="departamento" type="number" value="0" step="1"/><br/><br/>
            <label>Nombre</label>
                <input class="btn btn-default" id="nombre" name="nombre" value="nombre" type="text" /><br/><br/>
            <!--input class="btn btn-success" id="enviar" name="enviar" type="submit" value="Nuevo usuario" /-->
            <input class="btn btn-success" type=button onclick=newUser() value="Nuevo usuario">
            </fieldset>    
        </form></div>
        
        <div class="col-md-4"><form id="formularioEditUser" action="http://localhost:8084/ServerCiberNoid_1/webresources/users/edituser" method="post">
            <fieldset>
        <legend>Modificación de usuario con ID</legend><br/>
             <label>ID de usuario</label>
                <input class="btn btn-warning" id="id" name="id" type="number" value="0" step="1"/><br/><br/>
            <label>ID del departamento</label>
                <input class="btn btn-default" id="departamento" name="departamento" type="number" value="0" step="1"/><br/><br/>
            <label>Nombre</label>
                <input class="btn btn-default" id="nombre" name="nombre" value="nombre" type="text" /><br/><br/>
            <!--input class="btn btn-success" id="enviar" name="enviar" type="submit" value="Editar usuario" /-->
            <input class="btn btn-warning" type=button onclick=editUser() value="Editar usuario">
            </fieldset>    
        </form></div>
        
        <div class="col-md-4"><form id="formularioDeleteUser" action="http://localhost:8084/ServerCiberNoid_1/webresources/users/deleteuser" method="post">
            <fieldset>
        <legend>Eliminar usuario</legend><br/>
             <label>ID del usuario</label>
                <input class="btn btn-default" id="id" name="id" type="number" value="0" step="1"/><br/><br/>
            <!--input class="btn btn-danger" id="enviar" name="enviar" type="submit" value="Eliminar usuario" /-->
            <input class="btn btn-danger" type=button onclick=deleteUser() value="Eliminar usuario">
            </fieldset>    
        </form></div>
    <br/></div>
    </body>
</html>
