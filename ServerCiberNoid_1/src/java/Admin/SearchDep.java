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
 * Servlet implementation class HolaMundo
 */
@WebServlet("/searchdep")
public class SearchDep extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public SearchDep() {
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
                    String url ="jdbc:postgresql://localhost:5432/postgres";
                    String usuario="postgres";
                    String contraseña="123";

                    connection = DriverManager.getConnection(url, usuario, contraseña);
                    String nombre = request.getParameter("nombresearch");
                    if(!connection.isClosed()){
                        Statement stmt = connection.createStatement();
                        ResultSet rs= stmt.executeQuery("SELECT * FROM departamentos WHERE nombre LIKE '%"+nombre+"%'");
                        out.println("<table id='table' class='table table-striped' style= 'cellspacing'='1'");
                        out.println("<thead>");
                        out.println("<tr class='info'>");
                        out.println("<th class='text-center'> NOMBRE </td>");			
                        out.println("<th class='text-center'>ID </td>");
                        out.println("<th class='text-center'>HORA DE INICIO</td>");
                        out.println("<th class='text-center'>JORNADA </td>");
                        out.println("<th class='text-center'>DURACIÓN FICHEROS</td>");
                        out.println("</tr>");
                        out.println("</thead>");
                        out.println("<tbody>");
                        while(rs.next()){
                            //out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                            out.println("<tr class='info'>");
                            out.println("<td class='text-center'>"+rs.getString("nombre")+"</td>");
                            out.println("<td class='text-center'>"+rs.getInt("id")+"</td>");
                            out.println("<td class='text-center'>"+rs.getString("horario")+"</td>");			
                            out.println("<td class='text-center'>"+rs.getInt("mascara_hora")+" horas"+"</td>");
                            out.println("<td class='text-center'>"+((double)rs.getInt("mascara_fecha"))/2+ " meses"+"</td>");
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