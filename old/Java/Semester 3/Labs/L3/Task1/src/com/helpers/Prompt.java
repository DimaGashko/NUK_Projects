package com.helpers;

import java.util.Scanner;

public class Prompt {
    static private Scanner scanner = new Scanner(System.in);

    public Prompt() {

    }

    public int getInt(String title) {
        printTitle(title);
        int res = scanner.nextInt();
        scanner.nextLine();
        return res;
    }

    public double getDouble(String title) {
        printTitle(title);
        double res = scanner.nextDouble();
        scanner.nextLine();
        return res;
    }

    public String getLine(String title) {
        printTitle(title);
        String res = scanner.nextLine();
        return  res;
    }

    private void printTitle(String title) {
        System.out.println(title);
    }

}
