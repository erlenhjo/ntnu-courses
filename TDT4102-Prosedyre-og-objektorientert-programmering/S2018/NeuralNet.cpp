#include "NeuralNet.h"

using namespace std;


Layer::Layer(int N,int M)
    :N{N},M{M},a{vector<double>(N,0)},w(M*N,1) {}

double Layer::getWeight(int j,int i){
    return w[i+j*M];
}
void Layer::setWeight(int j, int i, double weight){
    w[i+j*M]=weight;
}

void Layer::forward(const vector<double> &input){
    if(input.size()!=M){
        throw "Wrong size of input vector";
    }
    double sum{0};
    for(int j{0};j<N;++j){
        sum=0;
        for(int i{0};i<M;++i){
            sum+=getWeight(j,i)*input[i];
        }
        a[j]=fn(sum);
    }
}

void Layer::forward(Layer* input){
    forward(input->a);
}

void NeuralNet::addLayer(Layer *layer){
    if(layers.size()>0){
        assert(layers[layers.size()-1]->getSize()==layer->getInputSize());
    }
    layers.push_back(layer);
}

Layer* NeuralNet::forward(const vector<double> &input){
    layers[0]->forward(input);
    for(int n{1};n<layers.size();++n){
        layers[n]->forward(layers[n-1]);
    }
    return layers[layers.size()-1];
}