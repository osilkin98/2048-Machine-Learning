# 2048ML
Machine Learning project to teach a computer to play 2048

# What is this?
This was my first ever attempt at making a neural network using the Genetic Algorithm.
I wrote my own version of 2048 to be run in a CLI for Linux (and windows if using <time.h> instead of <ctime>)
I made sure that the game was as optimized as can be in order for the genetic algorithm to perform more efficiently.
Overall, it turned out to be successful, and was able to reach a score of 32,486 before coming to a halt over the course of a 72 hour learning session.

# Things I need to improve on:
### 1.  Code efficiency. 
A lot of this code is unoptimized, there is no usage of register variables. 
neuralnet.cpp has some pretty redundant routines as well, and in the future I need to
make sure to modulize every routine available, for debugging as well as proper organization.

### 2.  A Better Algorithm.
This project was not written off the basis of any paper, simply my basic knowledge of how neural networks function
as well as the idea of genetic programming. I feel as though the approach I took is quite cumbersome and inefficient.

### 3. CUDA Acceleration.
The training of this algorithm took 72 hours before it was able to get a good score. This time could be cut down
significiantly to just a couple of minutes, should I parallize the generations of neural networks to train on their 
own CPU thread, which could then in turn use its own block on the GPU to carry out all the redundant matrix operations.

