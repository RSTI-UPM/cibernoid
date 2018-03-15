package remoto.cibernoid.api;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStreamWriter;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        //WifiManager wifiManager = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);


        //wifiManager.setWifiEnabled(!wifiManager.isWifiEnabled());

        final Switch simpleSwitch = (Switch) findViewById(R.id.grupo); // initiate Switch

        final Spinner horas = (Spinner) findViewById(R.id.horas);
        ArrayAdapter<CharSequence> adapterH = ArrayAdapter.createFromResource(this,
                R.array.horas_trabajo, android.R.layout.simple_spinner_item);
        adapterH.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        horas.setAdapter(adapterH);

        final EditText reloj = (EditText) findViewById(R.id.reloj);

        final Spinner duracion = (Spinner) findViewById(R.id.duracion);
        ArrayAdapter<CharSequence> adapterD = ArrayAdapter.createFromResource(this,
                R.array.duracion_fichero, android.R.layout.simple_spinner_item);
        adapterD.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        duracion.setAdapter(adapterD);


        Button submit = (Button) findViewById(R.id.submitButton);

        submit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                /*if(!wifiManager.isWifiEnabled()){
                    wifiManager.setWifiEnabled(true);
                }*/
                //adb shell svc wifi enable
                //adb shell settings put secure location_providers_allowed gps
                //adb shell settings put secure location_providers_allowed gps,network
                //https://es.androids.help/q11843
                //https://android.stackexchange.com/questions/40147/is-it-possible-to-enable-location-services-via-shell


                String statusSwitch;
                if (simpleSwitch.isChecked()){
                    statusSwitch = simpleSwitch.getTextOn().toString();
                }else {
                    statusSwitch = simpleSwitch.getTextOff().toString();
                }
                String h = "Error";
                switch(String.valueOf(horas.getSelectedItem())){
                    case "1 hora":  h = "1";
                                    break;
                    case "2 horas": h = "2";
                                    break;
                    case "4 horas": h = "4";
                                    break;
                    case "8 horas": h="8";
                                    break;
                    default:
                                    h = "Error";
                }
                String d = "Error";
                switch(String.valueOf(duracion.getSelectedItem())){
                    case "2 semanas":  d = "1";
                        break;
                    case "1 mes": d = "2";
                        break;
                    case "2 meses": d = "4";
                        break;
                    case "4 meses": d="8";
                        break;
                    default:
                        d = "Error";
                }


                String r = validarHora(reloj.getText().toString());
                String str = statusSwitch+","+h+","+d+","+r+",";
                writeToFile(str,getApplicationContext());
                Toast.makeText(getApplicationContext(), "Otro:" +str + "\n", Toast.LENGTH_LONG).show(); // display the current state for switch's
            }

        });
    }

    private void writeToFile(String str, Context context) {
        try {
            OutputStreamWriter outputStreamWriterW = new OutputStreamWriter(context.openFileOutput("str.txt", Context.MODE_PRIVATE));
            outputStreamWriterW.write(str);
            outputStreamWriterW.close();
        }
        catch (IOException e) {
            Log.e("Exception", "File write failed: " + e.toString());
        }
    }

    public String validarHora(String hora){
        if (hora.length()>5) {
            Toast.makeText(getApplicationContext(), "No es una hora valida", Toast.LENGTH_LONG).show();
            return "Error";
        }
        if (hora.length()!=5) {
            Toast.makeText(getApplicationContext(), "Introducir HH:MM 24h 1", Toast.LENGTH_LONG).show();
            return "Error";
        }
        int a= (int) hora.charAt(0);
        int b= (int) hora.charAt(1);
        char p = hora.charAt(2);
        int c= (int) hora.charAt(3);
        int d= (int) hora.charAt(4);
        if(p!=':'){
            Toast.makeText(getApplicationContext(), "Introducir :", Toast.LENGTH_LONG).show();
            return "Error";
        }

        if (hora.charAt(0)!='0'&&hora.charAt(0)!='1') {
            Toast.makeText(getApplicationContext(), "Introducir HH:MM 24h", Toast.LENGTH_LONG).show();
            return "Error";

        }
        if ((int) hora.charAt(3)>53||(int) hora.charAt(3)<48) {
            Toast.makeText(getApplicationContext(), "Introducir HH:MM 24h", Toast.LENGTH_LONG).show();
            return "Error";
        }
        if((int) hora.charAt(1)<58&&(int) hora.charAt(1)>47&& (int) hora.charAt(4)<58&&(int) hora.charAt(4)>47){
            return hora;
        }
        return "Error";
    }
}


