package com.company;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import static java.lang.Math.*;

public class Main {
    private double a = 0, b = 0, x = 0;

    public static void main(String[] args) {
        Main app = new Main();
        app.run();
    }
    
    private void run() {
        inputStartData();

        double s = calcS(a, b, x);
        double q = calcQ(a, b, x);

        printResult(s, q);
        printCurrentDate();
    }

    private void inputStartData() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Input a: ");
        a = scanner.nextDouble();

        System.out.println("Input b: ");
        b = scanner.nextDouble();

        System.out.println("Input x: ");
        x = scanner.nextDouble();
    }

    private void printResult(double s, double q) {
        System.out.println("Input data:");
        System.out.println("a: " + a);
        System.out.println("b: " + b);
        System.out.println("x: " + x + "\n");

        System.out.println("Results:");
        System.out.println("s: " + s);
        System.out.println("q: " + q);
    }

    private void printCurrentDate() {
        LocalDate currentDate = LocalDate.now();

        System.out.print("Current Date: ");
        System.out.println(currentDate.format(DateTimeFormatter.ofPattern("dd MM uuuu")));
    }

    private double calcS(double a, double b, double x) {
        return pow(x, 3) * pow(tan(pow(x + b, 2)), 2)
                + a / sqrt(x + b);
    }

    private double calcQ(double a, double b, double x) {
        return (b * pow(x, 2) - a) / (exp(a * x) - 1);
    }

}