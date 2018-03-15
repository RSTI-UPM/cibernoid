/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Admin;

import Admin.*;
import Claves.Fichero;
import com.google.gson.Gson;
import java.awt.Graphics;
import java.awt.Shape;
import java.io.IOException;
import static java.lang.System.out;
import java.net.URI;
import java.net.URISyntaxException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Time;
import static java.time.Clock.system;
import java.time.LocalTime;
import java.time.MonthDay;
import java.time.Year;
import java.time.YearMonth;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collection;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Random;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.swing.text.BadLocationException;
import javax.swing.text.Position;
import javax.swing.text.View;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.UriInfo;
import javax.ws.rs.Produces;
import javax.ws.rs.Consumes;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import static javax.ws.rs.HttpMethod.POST;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PUT;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;


/**
 * REST Web Service
 *
 * @author Sol
 */
@Path("users")
public class UsersResource {

    @Context
    private UriInfo context;

    /**
     * Creates a new instance of UsersResource
     */
    public UsersResource() {

    }

    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("newuser")
    public void newUser(@FormParam("id")int id,@FormParam("nombre")String nombre, 
           @FormParam("departamento")int idDep) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
        String url ="jdbc:postgresql://localhost:5432/postgres";
        String usuario="postgres";
        String contraseña="123";

        Connection connection = DriverManager.getConnection(url, usuario, contraseña);
        
        if(!connection.isClosed()){
            String query = " insert into usuarios " + " values (?, ?, ?)";

            // create the mysql insert preparedstatement
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setInt (1, id);
            preparedStmt.setString (2, nombre);
            preparedStmt.setInt(3, idDep);

            // execute the preparedstatement
            preparedStmt.execute();
            connection.close();
        }
       }
    
    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("edituser")
    public void editUser(@FormParam("id")int id,@FormParam("nombre")String nombre, 
           @FormParam("departamento")int idDep) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";

        Connection connection = DriverManager.getConnection(url, usuario, contraseña);
        
        if(!connection.isClosed()){
            String query = "Update usuarios Set nombre=? , departamento=? Where id=?";

            // create the mysql insert preparedstatement
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString (1, nombre);
            preparedStmt.setInt (2, idDep);
            preparedStmt.setInt(3, id);

            preparedStmt.execute();
            preparedStmt.close();
            connection.close();
        }
       }
    
    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("deleteuser")
    public void deleteUser(@FormParam("id")int id) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";

        Connection connection = DriverManager.getConnection(url, usuario, contraseña);
        
        if(!connection.isClosed()){
            String query = "Delete From usuarios Where id=?";

            // create the mysql insert preparedstatement
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setInt(1, id);

            preparedStmt.execute();
            preparedStmt.close();
            connection.close();
        }
       }
    
    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("searchuser")
    public void searchUser(@FormParam("nombresearch")String nombre) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
        Connection connection = null;
        try{
            Class.forName("org.postgresql.Driver");

            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";
            connection = DriverManager.getConnection(url, usuario, contraseña);
        
            if(!connection.isClosed()){
                Statement stmt = connection.createStatement();
                ResultSet rs= stmt.executeQuery("SELECT * FROM usuarios WHERE nombre LIKE '%"+nombre+"%'");
                while(rs.next()){
                    out.println("Nombre: "+ rs.getString("nombre")+" ; Id: "+rs.getInt("id")+ " ; Departamento: "+rs.getInt("departamento"));
                }
                stmt.close();
                rs.close();
                connection.close();
            }
        } catch (Exception e) {
                e.printStackTrace();
                    System.err.println(e.getClass().getName()+": "+e.getMessage());
                    System.exit(0);
             
        }
    }
    
}

