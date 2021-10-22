package nl.avans.arduinobluetooth;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.ParcelUuid;
import android.view.View;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;

import static java.lang.Thread.sleep;

public class MainActivity extends AppCompatActivity {

    private BluetoothSocket socket;
    private OutputStream outputStream;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void sendSignal(View view) {
        // verbind met bluetooth apparaat en maak een outputstream om data te verzenden
        connect();

        try {
            // zend bytes via outputStream naar verbonden bluetooth apparaat
            outputStream.write(1); // zend een 1, in arduino geprogrammeerd om bij een 1 de cyclus te doorlopen
            sleep(100); // wacht 100 ms
            outputStream.write(0); // zend een andere waarde, omdat de module de waarde onthoud, door hem te updaten/resetten blijft hij niet dezelfde waarde en kan ik de knop meerdere keren gebruiken/heeft hij het door als de waarde opnieuw veranderd
        } catch (IOException | InterruptedException e) {
            System.out.println("Error occurred when sending data");
        }

        // safely stop the connection after the signal is send
        stopConnection();
    }

    public void connect() {
        // haal de bluetooth adapter op
        BluetoothAdapter blueAdapter = BluetoothAdapter.getDefaultAdapter();
        if (blueAdapter != null) {
            if (blueAdapter.isEnabled()) {
                // vraag alle verbonden apparaten op
                Set<BluetoothDevice> bondedDevices = blueAdapter.getBondedDevices();
                // als er verbonden apparaten zijn
                if(bondedDevices.size() > 0) {
                    // zet apparaten in array
                    Object[] devices = bondedDevices.toArray();
                    // pak de eerste (ervan uitgaande dat er maar 1 apparaat gekoppeld is)
                    BluetoothDevice device = (BluetoothDevice) devices[0];
                    // backup optie
//                    BluetoothDevice device = blueAdapter.getRemoteDevice("98:D3:51:FD:AE:B5"); // hc05
                    // id dat je nodig hebt om te verbinden en een prive connectie te maken zodat alleen jouw apparaten met elkaar communiceren
                    ParcelUuid[] uuids = device.getUuids();

                    try {
                        // krijg socket om te verbinden
                        socket = device.createRfcommSocketToServiceRecord(uuids[0].getUuid());
                        System.out.println(socket);
                        // verbind
                        socket.connect();
                        System.out.println(socket.isConnected());
                        // krijg outputstream om signalen te verzenden
                        outputStream = socket.getOutputStream();
                        System.out.println(outputStream);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    public void stopConnection() {
        try {
            socket.close();
            System.out.println(socket.isConnected());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
