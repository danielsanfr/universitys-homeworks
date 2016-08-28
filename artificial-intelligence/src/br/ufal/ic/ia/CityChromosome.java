package br.ufal.ic.ia;

import com.lagodiuk.ga.Chromosome;

import java.util.*;

/**
 * Created by daniel on 30/10/14.
 */
public class CityChromosome implements Chromosome<CityChromosome>, Cloneable {

    private static final Random random = new Random();

    private final int[] path = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    @Override
    public List<CityChromosome> crossover(CityChromosome anotherChromosome) {
        return Arrays.asList(this, anotherChromosome);
        /*CityChromosome thisClone = this.clone();
        CityChromosome anotherClone = anotherChromosome.clone();

	    int i = getValidRandomIndex();
	    int j = getValidRandomIndex();

        int aux = thisClone.path[i];
        thisClone.path[i] = anotherClone.path[i];
        anotherClone.path[i] = aux;

        aux = thisClone.path[j];
        thisClone.path[j] = anotherClone.path[j];
        anotherClone.path[j] = aux;

		return Arrays.asList(thisClone, anotherClone);*/
    }

    @Override
    public CityChromosome mutate() {
        CityChromosome auxClone = this.clone();
        CityChromosome thisClone = auxClone;

	    int i = getValidRandomIndex();
        int j = getValidRandomIndex();
        int length = this.path.length;
        List<Integer> list = new ArrayList<Integer>();
        for (int w = 0; w < 30; w++) {
            int aux = thisClone.path[i];
            thisClone.path[i] = thisClone.path[j];
            thisClone.path[j] = aux;

            list.clear();
            for (int x = 0; x < length; x++) {
                list.add(x);
            }
            if (hasPath(thisClone.getVector()) && !hasRepeatedCities(list, thisClone.getVector())) {
                return thisClone;
            }

//            thisClone = auxClone;
            i = getValidRandomIndex();
            j = getValidRandomIndex();
        }
        return this;
    }

    @Override
    protected CityChromosome clone() {
        CityChromosome clone = new CityChromosome();
        System.arraycopy(this.path, 0, clone.path, 0, this.path.length);
        return clone;
    }

    private boolean hasPath(int[] v) {
        int length = v.length - 1;
        for (int i = 0; i < length; i++) {
            if (!CitiesMap.hasPath(v[i], v[i + 1])) {
                return false;
            }
        }
        return CitiesMap.hasPath(v[length], v[0]);
    }

    private boolean hasRepeatedCities(List<Integer> list, int[] v) {
        int length = v.length;
        int visitedCities = 0;
        for (int i = 0; i < length; i++) {
            visitedCities += list.get(v[i]);
            Collections.replaceAll(list, v[i], 0);
        }
        return (visitedCities != 45);
    }

    private int getValidRandomIndex() {
        return 1 + random.nextInt(this.path.length - 1);
    }

    public int[] getVector() {
        return this.path;
    }

    @Override
    public String toString() {
        return Arrays.toString(this.path);
    }
}
