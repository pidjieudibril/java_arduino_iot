package pointJar;

/*
  Titre      : arduino java 
  Auteur     : Pidjieu dibril
  Date       : 28/10/2023
  Description: afficher les valeur du capteur dans le moniteur serie en utilisant java 
  Version    : 0.0.1
*/


import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.text.DecimalFormat;

/**
 * Classe pour la sauvegarde des données dans la base de données.
 */
public class saveDataToDatabase {

    /**
     * Sauvegarde les données dans la base de données.
     *
     * @param connection Connexion à la base de données.
     * @param data       Donnée à sauvegarder.
     * @throws SQLException En cas d'erreur lors de la sauvegarde.
     */
    public static void saveData(Connection connection, String data) throws SQLException {
        String insertQuery = "INSERT INTO sensor_data (value) VALUES (?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(insertQuery)) {
            try {
                // Convertit la chaîne de caractères en double
                double doubleValue = Double.parseDouble(data);

                // Insère la valeur double dans la base de données
                preparedStatement.setDouble(1, doubleValue);
                preparedStatement.executeUpdate();

                // Utilisation de DecimalFormat pour formater la valeur double
                DecimalFormat df = new DecimalFormat("#.##"); // Format avec deux décimales
                String formattedValue = df.format(doubleValue);

                System.out.println("Donnée reçue et stockée (convertie en double) : " + formattedValue);
            } catch (NumberFormatException e) {
                System.err.println("La chaîne n'est pas un nombre valide : " + data);
            }
        }
    }
}

/* 
    private static void saveDataToDatabase(Connection connection, String data) throws SQLException {
        String insertQuery = "INSERT INTO sensor_data (value) VALUES (?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(insertQuery)) {
            preparedStatement.setString(1, data);
            preparedStatement.executeUpdate();
        }
    }*/
 