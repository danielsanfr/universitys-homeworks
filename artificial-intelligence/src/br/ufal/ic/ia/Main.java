package br.ufal.ic.ia;

import com.lagodiuk.ga.Fitness;
import com.lagodiuk.ga.GeneticAlgorithm;
import com.lagodiuk.ga.IterartionListener;
import com.lagodiuk.ga.Population;

public class Main {

    public static void main(String[] args) {
        CitiesMap.readMap("/home/daniel/programming-workspaces/java-IntelliJ/TravelingSalesman/traveling_salesman.txt");
//        CitiesMap.printLocation();

		Population<CityChromosome> population = createInitialPopulation(5);

		Fitness<CityChromosome, Double> fitness = new CityFitness();

		GeneticAlgorithm<CityChromosome, Double> ga = new GeneticAlgorithm<CityChromosome, Double>(population, fitness);

		addListener(ga);

		ga.evolve(500);

    }

    private static Population<CityChromosome> createInitialPopulation(int populationSize) {
        Population<CityChromosome> population = new Population<CityChromosome>();
        CityChromosome base = new CityChromosome();
        for (int i = 0; i < populationSize; i++) {
            // each member of initial population
            // is mutated clone of base chromosome
            CityChromosome chr = base.mutate();
            population.addChromosome(chr);
        }
        return population;
    }

	/**
	 * After each iteration Genetic algorithm notifies listener
	 */
    private static void addListener(GeneticAlgorithm<CityChromosome, Double> ga) {
        // just for pretty print
        System.out.println(String.format("%s\t%s\t%s", "iter", "fit", "chromosome"));

        // Lets add listener, which prints best chromosome after each iteration
        ga.addIterationListener(new IterartionListener<CityChromosome, Double>() {

            private final double threshold = 1e-5;

            @Override
            public void update(GeneticAlgorithm<CityChromosome, Double> ga) {

                CityChromosome best = ga.getBest();
                double bestFit = ga.fitness(best);
                int iteration = ga.getIteration();

                // Listener prints best achieved solution
                System.out.println(String.format("%s\t%s\t%s", iteration, bestFit, best));

                // If fitness is satisfying - we can stop Genetic algorithm
                if (bestFit < this.threshold) {
                    ga.terminate();
                }
            }
        });
    }
}
