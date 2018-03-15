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
@Path("coord")
public class CoordResource {

    @Context
    private UriInfo context;
    public static boolean cambioCoord = false;
    /**
     * Creates a new instance of UsersResource
     */
    public CoordResource() {

    }

    /**
     * Retrieves representation of an instance of Admin.UsersResource
     * @return an instance of java.lang.String
     */
    @POST
    @Path("editcoord")
    public void editCoord(@FormParam("latitud")float latitud,@FormParam("longitud")float longitud, 
           @FormParam("radio")int radio) throws ClassNotFoundException, SQLException{
        Connection connection = null;
        try{
            Class.forName("org.postgresql.Driver");

            String url ="jdbc:postgresql://localhost:5432/postgres";
            String usuario="postgres";
            String contraseña="123";

            connection = DriverManager.getConnection(url, usuario, contraseña);

            if(!connection.isClosed()){
                String query = "Update coordenadas Set latitud=? , longitud=? , radio=? Where id=1";
                //String query = "INSERT INTO coordenadas(id,latitud,longitud,radio) VALUES (5,'6.02','6.03',2)";
                // create the mysql insert preparedstatement
   
                PreparedStatement preparedStmt = connection.prepareStatement(query);
                //preparedStmt.setInt (1, 1);
                preparedStmt.setFloat (1, latitud);
                preparedStmt.setFloat (2, longitud);
                preparedStmt.setInt(3, radio);

                preparedStmt.execute();
                preparedStmt.close();
                connection.close();
            }
            cambioCoord=true;
            } catch (Exception e) {
                e.printStackTrace();
                    System.err.println(e.getClass().getName()+": "+e.getMessage());
                    System.exit(0);
            } 
    }
    
    
}

