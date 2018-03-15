/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Claves;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author Sol
 */
@XmlRootElement
public class Parametros {
    @XmlElement Integer idFile;
    @XmlElement Integer idUser;
    @XmlElement boolean grupo;
    @XmlElement String operador;
    @XmlElement float lon;
    @XmlElement float lat;
    @XmlElement String hora;
    @XmlElement String dateMask;
    @XmlElement String fecha;
    @XmlElement String timeMask;
    @XmlElement String wifis;
    
    public Parametros(){
    
}
}
