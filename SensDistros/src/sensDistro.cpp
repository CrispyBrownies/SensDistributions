
// Stephen Chen
// May 15, 2021
// Distribution creation program for purpose of tethered space net sensitivity study

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <tuple>
#include <random>
#include "../../vcpkg/installed/x64-linux/include/matplotlibcpp.h"

using namespace std;

// Generates normal distribution of n points within the bounds given
vector<double> GenerateNorm(int pts, tuple<double, double> bounds) { //vector<double>
    vector<double> points;
    double upper = get<1>(bounds);
    double lower = get<0>(bounds);
    double mean = 0.5*(lower + upper);
    double variance = pow(((upper-mean)/3),2);

    default_random_engine generator;
    normal_distribution<double> distribution(mean, variance);

    for (int i = 0; i < pts; i++) {
        double newPt = distribution(generator);
        if (newPt > lower && newPt < upper) {
            points.push_back(newPt);
        }
        else {
            i -= 1;
        }
    }
    return points;
}

// Creates normal distribution for two parameters
vector<tuple<double, double>> CreatePermDistro2(int points, vector<tuple<double, double>> bounds) {
    if (2 != bounds.size()) {
        cout << "Mismatched dimensions/input array size!" << endl;
        //exit
    }

    vector<tuple<double, double>> newDist;

    auto dist1 = GenerateNorm(points, bounds.at(0));
    auto dist2 = GenerateNorm(points, bounds.at(1));

    for (int i = 0; i < dist1.size(); i++) {
        for (int j = 0; j < dist2.size(); i++) {
            newDist.push_back(make_tuple(dist1.at(i), dist2.at(j)));
        }
    }

    return newDist;
}

// Creates normal distribution for three parameters
vector<tuple<double, double, double>> CreatePermDistro3(int points, vector<tuple<double, double>> bounds) {
    if (3 != bounds.size()) {
        cout << "Mismatched dimensions/input array size!" << endl;
        //exit
    }

    vector<tuple<double, double, double>> newDist;

    auto dist1 = GenerateNorm(points, bounds.at(0));
    auto dist2 = GenerateNorm(points, bounds.at(1));
    auto dist3 = GenerateNorm(points, bounds.at(2));

    for (int i = 0; i < dist1.size(); i++) {
        for (int j = 0; j < dist2.size(); j++) {
            for (int k = 0; k < dist3.size(); k++) {
            newDist.push_back(make_tuple(dist1.at(i), dist2.at(j), dist3.at(k)));
            }
        }
    }

    return newDist;
}

int main()
{
    auto pts = GenerateNorm(10, make_tuple(0,10));
    for (int i = 0; i < pts.size(); i++) {
        cout << pts[i] << endl;
    }
}

