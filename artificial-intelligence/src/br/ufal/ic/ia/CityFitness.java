package br.ufal.ic.ia;

import com.lagodiuk.ga.Fitness;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Created by daniel on 30/10/14.
 */
public class CityFitness  implements Fitness<CityChromosome, Double> {

    @Override
    public Double calculate(CityChromosome chromosome) {
        double totalDist = 0;
        int[] v = chromosome.getVector();
        int length = v.length - 1;
        List<Integer> list = new ArrayList<Integer>();
        for (int i = 0; i < length; i++) {
            list.add(i);
            int dist = CitiesMap.distance(v[i], v[i + 1]);
            if (dist == -1) {
                return (double) Integer.MAX_VALUE;
            }
            totalDist += dist;
        }
        list.add(length);
        // Checks for the path to start and if don't have repeated cities
        int dist = CitiesMap.distance(v[length], v[0]);
        if (dist == -1 || hasRepeatedCities(list, v)) {
            return (double) Integer.MAX_VALUE;
        }
        totalDist += dist;

        return totalDist;
    }

    private boolean hasRepeatedCities(List<Integer> list, int[] v) {
        boolean has;
        int length = v.length;
        int visitedCities = 0;
        for (int i = 0; i < length; i++) {
            visitedCities += list.get(v[i]);
            Collections.replaceAll(list, v[i], 0);
        }
        has = (visitedCities != 45);
//        System.out.println(">>> " + Arrays.toString(v) + list.toString() + visitedCities + has);
        return has;
    }


}
