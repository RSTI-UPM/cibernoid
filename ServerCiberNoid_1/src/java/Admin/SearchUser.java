/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Admin;

import java.io.IOException;
import java.io.PrintWriter;
import static java.lang.System.out;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Sol
 */
/**
 * Servlet implementation
 */
@WebServlet("/searchuser")
public class SearchUser extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public SearchUser() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType( "text/html; charset=iso-8859-1" );
            PrintWriter out = response.getWriter();
            try{
            
            Class.forName("org.postgresql.Driver");
        
            Connection connection = null;
            try{
                Class.forName("org.postgresql.Driver");

                String url ="jdbc:postgresql://localhost:5432/postgres";
                String usuario="postgres";
                String contraseña="123";

                connection = DriverManager.getConnection(url, usuario, contraseña);
                String nombre = request.getParameter("nombresearch");
                if(!connection.isClosed()){
                    Statement stmt = connection.createStatement();
                    ResultSet rs= stmt.executeQuery("SELECT usuarios.id,usuarios.nombre,departamentos.nombre,usuarios.departamento FROM usuarios INNER JOIN departamentos ON usuarios.departamento=departamentos.id WHERE usuarios.nombre LIKE '%"+nombre+"%'");
                    out.println("<table id='table' class='table table-striped' style= 'cellspacing'='1'>");
                    out.println("<thead>");
                    out.println("<tr class='info'>");
                    out.println("<th class='text-center'> ID </td>");			
                    out.println("<th class='text-center'>NOMBRE</td>");
                    out.println("<th class='text-center'>DEPARTAMENTO</td>");
                    out.println("<th class='text-center'>ID DEPARTAMENTO</td>");
                    out.println("</tr>");
                    out.println("</thead>");
                    out.println("<tbody>");
                    while(rs.next()){
                        //out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                        out.println("<tr class='info'>");
                        out.println("<td class='text-center'>"+rs.getInt(1)+"</td>");
                        out.println("<td class='text-center'>"+rs.getString(2)+"</td>");			
                        out.println("<td class='text-center'>"+rs.getString(3)+"</td>");
                        out.println("<td class='text-center'>"+rs.getInt(4)+"</td>");
                        out.println("</tr>");
                    }
                    out.println("</tbody>");
                    out.println("</table>");
                    stmt.close();
                    rs.close();
                    connection.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
                    System.err.println(e.getClass().getName()+": "+e.getMessage());
                    System.exit(0);
            }
            }catch(Exception e){
                out.println("hola");
            }
	}

}