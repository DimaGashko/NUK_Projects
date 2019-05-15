package com.company;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Locale;
import java.util.Scanner;
import static java.lang.Math.*;

public class Main {
    private double a = 0, b = 0, x = 0;

    public static void main(String[] args) {
        Main app = new Main();
        app.run();
    }

    private double getA() { return a; }
    private double getB() { return b; }
    private double getX() { return x; }

    private void setA(double a) { this.a = a; }
    private void setB(double b) { this.b = b; }
    private void setX(double x) { this.x = x; }

    private void run() {
        inputStartData();

        double s = calcS(getA(), getB(), getX());
        double q = calcQ(getA(), getB(), getX());

        printResult(s, q);

        printCurrentDate("dd MMM yyyy", "uk");
        printCurrentDate("dd MMM yyyy", "ru");
        printCurrentDate("dd MMM yyyy", "en");
    }

    private void inputStartData() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Input a: ");
        setA(scanner.nextDouble());

        System.out.println("Input b: ");
        setB(scanner.nextDouble());

        System.out.println("Input x: ");
        setX(scanner.nextDouble());
    }

    private void printResult(double s, double q) {
        System.out.println("Input data:");
        System.out.println("a: " + getA());
        System.out.println("b: " + getB());
        System.out.println("x: " + getX() + "\n");

        System.out.println("Results:");
        System.out.println("s: " + s);
        System.out.println("q: " + q + "\n");
    }

    private void printCurrentDate(String format, String lan) {
        LocalDate currentDate = LocalDate.now();

        System.out.print("Current Date: ");

        System.out.println(currentDate.format(
                DateTimeFormatter.ofPattern(format, new Locale(lan))
        ));
    }

    private double calcS(double a, double b, double x) {
        double t = tan((x + b) * (x + b));
        return (x*x*x) * (t*t) + a / sqrt(x + b);
    }

    private double calcQ(double a, double b, double x) {
        return (b * x*x - a) / (exp(a * x) - 1);
    }



}
