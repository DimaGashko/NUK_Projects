package random

import "math"

const RAND_MAX = 32767

var next int64 = 1

var gaussianHasCalculated = false
var gaussianCalculated = 0.0

func Lcg() int {
	next = (next*1103515245 + 12345) % 2147483648
	return int(next>>16) % (RAND_MAX + 1)
}

func Gaussian(stdDev, mean float64) float64 {
	if gaussianHasCalculated {
		gaussianHasCalculated = false
		return gaussianCalculated*stdDev + mean
	}

	x := float64(Lcg())/RAND_MAX*2 - 1
	y := float64(Lcg())/RAND_MAX*2 - 1
	s := x*x + y*y

	if s == 0 || s > 1 {
		return Gaussian(mean, stdDev)
	}

	c := math.Sqrt(-2 * math.Log10(s) / s)
	z0 := x * c
	z1 := y * c

	gaussianHasCalculated = true
	gaussianCalculated = z1

	return z0*stdDev + mean
}

func SetSeed(seed int64) {
	next = seed
}

func GenRandomSlice(len int) []float64 {
	res := make([]float64, len)

	for i := 0; i < len; i++ {
		res[i] = float64(Lcg())
	}

	return res
}

func GenNormallyRandomSlice(stdDev, mean float64, len int) []float64 {
	res := make([]float64, len)

	for i := 0; i < len; i++ {
		res[i] = Gaussian(stdDev, mean)
	}

	return res
}
