
// Stephen Chen
// May 15, 2021
// Distribution creation program for purpose of tethered space net sensitivity study

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <tuple>
#include <random>
#include "./matplotlibcpp.h"

namespace plt = matplotlibcpp;

using namespace std;

// Generates normal distribution of n points within the bounds given
vector<double> GenerateNorm(int pts, tuple<double, double> bounds) { //vector<double>
    vector<double> points;
    double upper = get<1>(bounds);
    double lower = get<0>(bounds);
    double mean = 0.5*(lower + upper);
    double variance = pow(((upper-mean)/3),2);

    cout << "mean: " << mean << endl;
    cout << "var: " << variance << endl;

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

// Function to plot and show the distribution for one parameter.
void Show1D() {

    auto pts = GenerateNorm(50000, make_tuple(0,10));
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0, count10 = 0;
    
    // cout << "count7" << count7 << endl;

    for (int i = 0; i < pts.size(); i++) {
        // cout << pts[i] << endl;
        if (pts[i] <= 1) {
            count1++;
        } else if (pts[i] <= 2) {
            count2++;
        } else if (pts[i] <= 3) {
            count3++;
        } else if (pts[i] <= 4) {
            count4++;
        } else if (pts[i] <= 5) {
            count5++;
        } else if (pts[i] <= 6) {
            count6++;
        } else if (pts[i] <= 7) {
            count7++;
        } else if (pts[i] <= 8) {
            count8++;
        } else if (pts[i] <= 9) {
            count9++;
        } else if (pts[i] <= 10) {
            count10++;
        }
    }

    // cout << "count7" << count7 << endl;

    vector<int> nums;
    nums.push_back(count1);
    nums.push_back(count2);
    nums.push_back(count3);
    nums.push_back(count4);
    nums.push_back(count5);
    nums.push_back(count6);
    nums.push_back(count7);
    nums.push_back(count8);
    nums.push_back(count9);
    nums.push_back(count10);

    vector<int> labels;
    labels.push_back(0);
    labels.push_back(1);
    labels.push_back(2);
    labels.push_back(3);
    labels.push_back(4);
    labels.push_back(5);
    labels.push_back(6);
    labels.push_back(7);
    labels.push_back(8);
    labels.push_back(9);
    labels.push_back(10);

    plt::bar(nums);
    plt::xlabel("Ranges (0-10)");
    plt::ylabel("# of Occurances");
    plt::title("Normal Distribution of One Parameter 50,000 Points");
    plt::xticks(labels);
    plt::show();

}


int main()
{
    Show1D();
}

