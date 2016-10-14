# Load library to plot the bar graph
library(gplots)

# Load the data from a csv file
data <- read.csv("data.csv", header=T)

# Produce result summaries of the results of various model fitting functions
summary(data)

# File name where the graph will be plotted
png(filename="results-barplot.png", bg="white")

# Self-descriptive
legend <- c("Synchronous", "Asynchronous")
colors <- c("lightblue", "mistyrose")

# Performs one and two sample t-tests on vectors of data
# These variables are the averages and confidence intervals
sampleTTestSync <- t.test(data[1])
sampleTTestAsync <- t.test(data[2])

# Create the matrix with averages to plot the bars
averages <- matrix(c(sampleTTestSync$estimate, sampleTTestAsync$estimate), ncol = 2, nrow = 1)

# Create the matrix with upper confidence interval
ic.lower <- matrix(c(sampleTTestSync$conf.int[1], sampleTTestAsync$conf.int[1]), ncol = 2, nrow = 1)

# Create the matrix with lower confidence interval
ic.upper <- matrix(c(sampleTTestSync$conf.int[2], sampleTTestAsync$conf.int[2]), ncol = 2, nrow = 1)

# Important: The matrices created above (averages, ic.lower and ic.upper)
# must have the same dimensions.

barplot2(averages, # The matrix to be plotted
         beside=TRUE, # Plot the side-by-side bars
         col=colors, # The colors of the bars
         legend=legend, # The legend
         ylim=c(0, 0.004), # The maximum y-axis
         main="Synchronous and Asynchronous B-multicast", # Main title
         ylab="Time in seconds", # Label the y-axis
         plot.ci=TRUE, # TRUE, Must plot the confidence intervals
         ci.l=ic.lower, # The matrix of the lower limits of the confidence intervals
         ci.u=ic.upper, # The matrix of the upper limits of the confidence intervals
         font.main=4, cex.axis=1.2, cex.lab=1.5, cex.names=1.5 # Visual adjusts
)
