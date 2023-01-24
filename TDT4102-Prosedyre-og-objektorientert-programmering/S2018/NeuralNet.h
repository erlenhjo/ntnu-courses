#pragma once

#include <vector>
#include <cmath>
#include <cassert>

class Layer{
    int N;
    int M;
    std::vector<double> a;
    std::vector<double> w;

public:
    Layer(int N,int M);
    int getSize(){return N;}
    int getInputSize(){return M;}
    double getWeight(int j,int i);
    void setWeight(int j, int i, double weight);
    virtual double fn(double x) { return x; } //Virtual is necessary so that we may override it in a subclass later, as we want to do.
    void forward(const std::vector<double> &input);
    void forward(Layer* input);


};

class SigmoidLayer:public Layer{
public:
    SigmoidLayer(int N,int M):Layer{N,M}{}
    double fn(double x) override{return 1/(1+exp(-x));} 
};

class NeuralNet {
protected:
    std::vector<Layer*> layers;
public:
    NeuralNet() {}
    void addLayer(Layer *layer);
    Layer* forward(const std::vector<double> &input);
};