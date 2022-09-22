g++ -fPIC -O3 -c -g NeuralNets.c
g++ -no-pie -fPIC -O3 -g *.o -lm -o NeuralNets