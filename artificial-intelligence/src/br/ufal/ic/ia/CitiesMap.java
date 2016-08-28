package br.ufal.ic.ia;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by daniel on 30/10/14.
 */
public class CitiesMap {
    private static int[][] locations;

    public static void readMap(String filePath) {
        try {
            BufferedReader in = new BufferedReader(new FileReader(filePath));
            List<int[]> points = new ArrayList<int[]>();
            String currentLine = in.readLine();
            int length = currentLine.split(" ").length;
            locations = new int[length][length];
            String[] lineDists;
            for (int i = 0; i < length; i++) {
                lineDists = currentLine.split(" ");
                for (int j = 0; j < length; j++) {
                    locations[i][j] = Integer.parseInt(lineDists[j]);
                }
                currentLine = in.readLine();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int distance(int a, int b) {
        return locations[a][b];
    }

    public static boolean hasPath(int a, int b) {
        return locations[a][b] > 0;
    }

    public static int[][] getLocations() {
        return locations;
    }
    public static int getLocationCount() {
        return locations.length;
    }

    public static void printLocation() {
        int length = locations.length;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                System.out.print(locations[i][j] + " ");
            }
            System.out.println();
        }
    }

}
