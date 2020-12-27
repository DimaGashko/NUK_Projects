package main

import "fmt"

func main() {
	fmt.Println("Calculating Float Epsilon:")
	fEps := calcFloatEps()

	fmt.Println("\nCalculating Double Epsilon:")
	dEps := calcDoubleEps()

	fmt.Println("\nResults:")
	fmt.Printf("Float Epsilon: %v\n", fEps)
	fmt.Printf("Double Epsilon: %v\n", dEps)
}

func calcFloatEps() float32 {
	eps := float32(1)

	for ; eps+1 > 1; eps /= 2 {
		fmt.Printf("1 + %v = %v\n", eps, eps+1)
	}

	fmt.Printf("1 + %v = %v\n", eps, eps+1)

	return eps * 2
}

func calcDoubleEps() float64 {
	eps := float64(1)

	for ; eps+1 > 1; eps /= 2 {
		fmt.Printf("1 + %v = %v\n", eps, eps+1)
	}

	fmt.Printf("1 + %v = %v\n", eps, eps+1)

	return eps * 2
}
