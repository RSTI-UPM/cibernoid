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
@Path("wifis")
public class WifisResource {

    @Context
    private UriInfo context;

    /**
     * Creates a new instance of UsersResource
     */
    public WifisResource() {

    }

    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("newwifi")
    public void newWifi(@FormParam("ssid")String ssid,@FormParam("potencia")int potencia) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
        Connection connection = null;
        try{
            Class.forName("org.postgresql.Driver");

            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";

            connection = DriverManager.getConnection(url, usuario, contraseña);
        
            if(!connection.isClosed()){
                String query = " insert into wifis " + " values (?, ?)";

                // create the mysql insert preparedstatement
                PreparedStatement preparedStmt = connection.prepareStatement(query);
                preparedStmt.setString (1, ssid);
                preparedStmt.setInt (2, potencia);

                // execute the preparedstatement
                preparedStmt.execute();
                connection.close();
            }
        } catch (Exception e) {
                e.printStackTrace();
                    System.err.println(e.getClass().getName()+": "+e.getMessage());
                    System.exit(0);
             
        }
    }
    
    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("editwifi")
    public void editWifi(@FormParam("ssid")String ssid,@FormParam("potencia")int potencia) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
        Connection connection = null;
        try{
            Class.forName("org.postgresql.Driver");

            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";
            connection = DriverManager.getConnection(url, usuario, contraseña);
        
            if(!connection.isClosed()){
                String query = "Update wifis Set potencia=? Where ssid=?";

                // create the mysql insert preparedstatement
                PreparedStatement preparedStmt = connection.prepareStatement(query);
                preparedStmt.setInt (1, potencia);
                preparedStmt.setString (2, ssid);

                preparedStmt.execute();
                preparedStmt.close();
                connection.close();
            }
        } catch (Exception e) {
                e.printStackTrace();
                    System.err.println(e.getClass().getName()+": "+e.getMessage());
                    System.exit(0);
             
        }
        
    }
    
    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("deletewifi")
    public void deleteWifi(@FormParam("ssid")String ssid) throws ClassNotFoundException, SQLException{
        Class.forName("org.postgresql.Driver");
        
        Connection connection = null;
        try{
            Class.forName("org.postgresql.Driver");

            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";
            connection = DriverManager.getConnection(url, usuario, contraseña);
        
            if(!connection.isClosed()){
                String query = "Delete From wifis Where ssid=?";

                // create the mysql insert preparedstatement
                PreparedStatement preparedStmt = connection.prepareStatement(query);
                preparedStmt.setString(1, ssid);

                preparedStmt.execute();
                preparedStmt.close();
                connection.close();
            }
        } catch (Exception e) {
                e.printStackTrace();
                    System.err.println(e.getClass().getName()+": "+e.getMessage());
                    System.exit(0);
             
        }
        
    }

}
