package main

import (
	"fmt"
	"log"
	"random-module/chi"
	"random-module/random"
)

func main() {
	random.SetSeed(6 * 100)
	size := 10000
	stdDev := 6.0
	mean := 6.0

	fmt.Println("- - - Linear Distribution Generator - - -")
	//calcLcgPeriod()
	testLcg(size)

	fmt.Println("- - - Gaussian Distribution Generator - - -")
	testGaussian(stdDev, mean, size)
}

func testLcg(size int) {
	sample := random.GenRandomSlice(size)
	intervals, _, _, _ := chi.MakeIntervals(sample)
	frequencies := chi.GetAbsoluteFrequencies(intervals)
	critical, _ := chi.GetChi2Critical(len(intervals)-1, 0.05)
	actual := chi.CalcChi2Uni(frequencies, len(sample))
	ok := actual < critical

	strOk := "PASSED"
	if !ok {
		strOk = "FAILED"
	}

	printFrequencies(frequencies)
	fmt.Printf("Chi-square distribution (actual): %.3f\n", actual)
	fmt.Printf("Chi-square distribution (critical): %.3f\n", critical)
	fmt.Printf("\n%s\n\n", strOk)
}

func testGaussian(stdDev, mean float64, size int) {
	sample := random.GenNormallyRandomSlice(stdDev, mean, size)
	intervals, intervalLen, min, _ := chi.MakeIntervals(sample)
	borders := chi.GetIntervalBorders(min, intervalLen, len(intervals))
	frequencies := chi.GetAbsoluteFrequencies(intervals)
	critical, _ := chi.GetChi2Critical(len(intervals)-3, 0.05)

	actual := chi.CalcChi2Gaussian(frequencies, borders, len(sample), intervalLen, stdDev, mean)
	ok := actual < critical

	strOk := "PASSED"
	if !ok {
		strOk = "FAILED"
	}

	printFrequencies(frequencies)
	fmt.Printf("Chi-square distribution (actual): %.3f\n", actual)
	fmt.Printf("Chi-square distribution (critical): %.3f\n", critical)
	fmt.Printf("\n%s\n\n", strOk)
}

func printFrequencies(frequencies []float64) {
	fmt.Println("Frequencies:")

	for _, item := range frequencies {
		fmt.Printf("%.0f ", item)
	}

	fmt.Println()
}

func calcLcgPeriod() int {
	fmt.Println("Calculating the generator period:")

	first := random.Lcg()
	i := 1

	for ; random.Lcg() != first; i++ {
		if i%1e8 == 0 {
			fmt.Print(".")
		}
	}

	fmt.Printf("\nPeriod: %d\n", i)
	return i
}

func checkError(message string, err error) {
	if err != nil {
		log.Fatal(message, err)
	}
}
