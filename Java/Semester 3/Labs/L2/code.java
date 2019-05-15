package com.company;

import java.util.Scanner;
import static java.lang.Math.*;

public class Main {
    private double askDouble(String title) {
        Scanner scanner = new Scanner(System.in);

        System.out.println(title);
        return scanner.nextDouble();
    }

    public void printEl(double[] arr, int index) {
        System.out.println("arr[" + index + "]" + " = " + arr[index]);
    }

    public double getAverage(double[] arr) {
        return getSumOfElements(arr) / arr.length;
    }

    public double getSumOfElements(double[] arr) {
        double res = 0;

        for (double item : arr) {
            res += item;
        }

        return res;
    }

    public int getIndexOfMin(double[] arr) {
        double min = arr[0];
        int index = 0;

        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
                index = i;
            }
        }

        return index;
    }

    public int getIndexOfMax(double[] arr) {
        double max = arr[0];
        int index = 0;

        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
                index = i;
            }
        }

        return index;
    }

    public double[] getAllX(double start, double end, double step) {
        int steps = getTabulationStepsCount(start, end, step);
        double[] allX = new double[steps];

        for (int i = 0; i < steps; i++) {
            double res = start + i * step;
            allX[i] = round(res * 10000.0) / 10000.0;
        }

        return allX;
    }

    public double[] getAllY(double[] allX, double a) {
        double[] allY = new double[allX.length];

        for (int i = allX.length - 1; i >= 0; i--) {
            allY[i] = calcY(allX[i], a);
        }

        return allY;
    }

    public int getTabulationStepsCount(double start, double end, double step) {
        return (int)((end - start) / step + 0.000001) + 1;
    }

    public double calcY(double x, double a, double epsilon) {
        if (x - 0.3 <= epsilon) {
            return 1.5 * a * cos(x) * cos(x);

        } else if (x - 2.3 <= epsilon) {
            return (x - 2) * (x - 2) + (6 * a);

        } else {
            return 3 * a * tan(x);
        }
    }

    public double calcY(double x, double a) {
        return calcY(x, a, 0.001);
    }

}





