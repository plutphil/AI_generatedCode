#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_INPUTS 2
#define NUM_OUTPUTS 1

// This AI can solve (N)OR and (N)AND gates

double input[NUM_INPUTS];
double weights1[NUM_INPUTS][NUM_OUTPUTS];
double bias1[NUM_OUTPUTS];
double output[NUM_OUTPUTS];

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

void feedforward() {
    for (int i = 0; i < NUM_OUTPUTS; i++) {
        double sum = bias1[i];
        for (int j = 0; j < NUM_INPUTS; j++) {
            sum += input[j] * weights1[j][i];
        }
        output[i] = sigmoid(sum);
    }
}

int expr(){
    return !((input[0]>0.5) && (input[1]>0.5));
}
int main() {
    // initialize weights and biases
    for (int i = 0; i < NUM_INPUTS; i++) {
        for (int j = 0; j < NUM_OUTPUTS; j++) {
            weights1[i][j] = 2 * rand() / RAND_MAX - 1;
        }
    }
    for (int i = 0; i < NUM_OUTPUTS; i++) {
        bias1[i] = 2 * rand() / RAND_MAX - 1;
    }

    // training loop
    for (int i = 0; i < 10000; i++) {
        // generate input and expected output for XOR
        input[0] = rand() % 2;
        input[1] = rand() % 2;
        double expected = expr();

        feedforward();

        // backpropagation
        double error = expected - output[0];
        for (int j = 0; j < NUM_OUTPUTS; j++) {
            double delta = error * output[j] * (1 - output[j]);
            bias1[j] += delta;
            for (int k = 0; k < NUM_INPUTS; k++) {
                weights1[k][j] += delta * input[k];
            }
        }
    }

    // test
    input[0] = 0;
    input[1] = 0;
    feedforward();
    printf("0 xor 0 = %i %i\n", output[0]>0.5,expr());
    input[0] = 0;
    input[1] = 1;
    feedforward();
    printf("0 xor 1 = %i %i\n", output[0]>0.5,expr());
    input[0] = 1;
    input[1] = 0;
    feedforward();
    printf("1 xor 0 = %i %i\n", output[0]>0.5,expr());
    input[0] = 1;
    input[1] = 1;
    feedforward();
    printf("1 xor 1 = %i %i\n", output[0]>0.5,expr());

    return 0;
}
