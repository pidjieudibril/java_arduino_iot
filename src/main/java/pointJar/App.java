package pointJar;
/*
  Titre      : arduino java 
  Auteur     : Pidjieu dibril
  Date       : 28/10/2023
  Description: afficher les valeur du capteur dans le moniteur serie en utilisant java 
  Version    : 0.0.1
*/
 

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import com.fazecast.jSerialComm.SerialPort;

/**
 * Classe principale pour l'initialisation et la boucle de lecture de données depuis le port série.
 */

public class App 
{
    public static void main(String[] args) {
        String portName = "COM4";
        String databaseURL = "jdbc:postgresql://localhost:5432/appJava";
        String databaseUser = "postgres";
        String databasePassword = "admin";

        SerialPort serialPort = SerialPort.getCommPort(portName);
        serialPort.openPort();
        serialPort.setBaudRate(9600);
        serialPort.setNumDataBits(8);
        serialPort.setNumStopBits(1);
        serialPort.setParity(SerialPort.NO_PARITY);

        try {
            while (true) {
                byte[] readBuffer = new byte[1024];
                int bytesRead = serialPort.readBytes(readBuffer, readBuffer.length);

                // Vérifiez que des données ont été lues avant de les traiter
                if (bytesRead > 0) {
                    String data = new String(readBuffer, 0, bytesRead);

                    Connection connection = DriverManager.getConnection(databaseURL, databaseUser, databasePassword);

                    saveDataToDatabase.saveData(connection, data);
                    System.out.println("Donnée reçue et stockée : " + data);

                    connection.close();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            serialPort.closePort();
        }
    }


}
 


