package com.company;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MainTest {
    Main main;

    @BeforeEach
    void setUp() {
        main = new Main();
    }

    // - - - CalcY - - -
    @Test
    void testCalcYX1() {
        double expected = 7.20397873;
        double result = main.calcY(0.2, 5);
        assertEquals(expected, result, 0.001, "По первому уравнению: caclY(0.2, 5)");
    }

    @Test
    void testCalcYX2() {
        double expected = -27.44;
        double result = main.calcY(0.4, -5);
        assertEquals(expected, result, 0.001, "По второму уравнению: caclY(0.4, -5)");
    }

    @Test
    void testCalcYX3() {
        double expected = -0.855279258;
        double result = main.calcY(3, 2);
        assertEquals(expected, result, 0.001, "По третьему уравнению: caclY(0.4, -5)");
    }

    @Test
    void testCalcYBorder1() {
        double expected = 1.369;
        double result = main.calcY(0.3, 1);
        assertEquals(expected, result, 0.001, "x == 0.3 должен считаться по первому уравнению");
    }

    @Test
    void testCalcYBorder2() {
        double expected = 6.09;
        double result = main.calcY(2.3, 1);
        assertEquals(expected, result, 0.001, "x == 2.3 должен считаться по второму уравнению");
    }

    // - - - TabulationSteps - - -
    @Test
    void testGetTabulationStepsInt() {
        double expected = 10;
        double result = main.getTabulationStepsCount(1, 10, 1);
        assertEquals(expected, result, 0.001, "start: 1, end: 10, step: 1 -> 10");
    }

    @Test
    void testGetTabulationStepsFloat() {
        double expected = 11;
        double result = main.getTabulationStepsCount(0.1, 1.1, 0.1);
        assertEquals(expected, result, 0.001, "start: 0.1, end: 1.1, step: 0.1 -> 11");
    }

    @Test
    void testGetTabulationStepsOut() {
        double expected = 6;
        double result = main.getTabulationStepsCount(1, 12, 2);
        assertEquals(expected, result, 0.001, "start: 1, end: 12, step: 2 -> 6");
    }

    @Test
    void testGetTabulationStepsNegative() {
        double expected = 5;
        double result = main.getTabulationStepsCount(-10, -1, 2);
        assertEquals(expected, result, 0.001, "start: -10, end: -1, step: 2 -> 5");
    }

    // - - - getX - - -
    @Test
    void testGetAllX() {
        double[] expected = {1, 2, 3, 4, 5};
        double[] result = main.getAllX(1, 5, 1);
        assertArrayEquals(expected, result, 0.001, "getAllX(1, 5, 1) -> {1,2,3,4,5}");
    }

    @Test
    void testGetAllY() {
        double a = 2.3;
        double[] allX = {1, 2};

        double[] expected = {main.calcY(allX[0], a), main.calcY(allX[1], a)};
        double[] result = main.getAllY(allX, a);
        assertArrayEquals(expected, result, 0.001, "getAllY({1,2}, 2.3)");
    }

    // - - - Tabulation - - -
    @Test
    void testGetAllY50() {
        double a = 2.3, start = 0.2, end = 2.8, step = 0.002;
        double[] allX = main.getAllX(start, end, step);
        double[] allY = main.getAllY(allX, a);

        double expected = 3.1487; //x = 0.3
        double result = allY[50];
        assertEquals(expected, result, 0.001, "allY[50]");
    }

    @Test
    void testGetAllY1050() {
        double a = 2.3, start = 0.2, end = 2.8, step = 0.002;
        double[] allX = main.getAllX(start, end, step);
        double[] allY = main.getAllY(allX, a);

        double expected = 13.89;
        double result = allY[1050];
        assertEquals(expected, result, 0.001, "allY[1050]");
    }

    @Test
    void testGetAllY1300() {
        double a = 2.3, start = 0.2, end = 2.8, step = 0.002;
        double[] allX = main.getAllX(start, end, step);
        double[] allY = main.getAllY(allX, a);

        double expected = -2.4532;
        double result = allY[1300];
        assertEquals(expected, result, 0.001, "allY[1300]");
    }

    // - - - getMinMax - - -
    @Test
    void testGetIndexOfMin() {
        double[] arr = {1, -2, 2};

        double expected = 1;
        double result = main.getIndexOfMin(arr);
        assertEquals(expected, result, 0.001, "getIndexOfMin({1,-2,2}) -> 1");
    }

    @Test
    void testGetIndexOfMax() {
        double[] arr = {1, 2, -2};

        double expected = 1;
        double result = main.getIndexOfMax(arr);
        assertEquals(expected, result, 0.001, "getIndexOfMax({1,2,-2}) -> 1");
    }

    // - - - Average - - -
    @Test
    void testGetSumOfElements() {
        double[] arr = {1,2,3,4};
        double expected = 10;
        double result = main.getSumOfElements(arr);
        assertEquals(expected, result, 0.001, "getSumOfElements({1,2,3,4}) -> 10");
    }

    @Test
    void testGetAverage() {
        double[] arr = {1,2,3,4};
        double expected = 2.5;
        double result = main.getAverage(arr);
        assertEquals(expected, result, 0.001, "getAverage({1,2,3,4}) -> 2.5");
    }
}