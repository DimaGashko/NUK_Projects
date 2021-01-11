package chi

import (
	"errors"
	"math"
)

var critical5 = []float64{3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067, 15.507, 16.919, 18.307, 19.675, 21.026, 22.362, 23.685, 24.996, 26.296, 27.587, 28.869, 30.144, 31.410, 32.671, 33.924, 35.172, 36.415, 37.652, 38.885, 40.113, 41.337, 42.557, 43.773}

func CalcChi2Uni(frequencies []float64, total int) float64 {
	res := 0.0
	expected := float64(total) / float64(len(frequencies))

	for _, f := range frequencies {
		res += (f - expected) * (f - expected) / expected
	}

	return res
}

func CalcChi2Gaussian(frequencies, borders []float64, total int, intervalLen, stdDev, mean float64) float64 {
	sum := 0.0

	for i, f := range frequencies {
		it := 200
		x := make([]float64, it+1)
		h := intervalLen / float64(it)

		for j := 0; j < it+1; j++ {
			x[int(j)] = borders[i] + h*float64(j)
		}

		integral := calcIntegral(x, stdDev, mean) * h
		sum += math.Pow(f-(integral*float64(total)), 2) / (integral * float64(total))
	}
	return sum
}

func GetChi2Critical(df int, p float64) (float64, error) {
	var critical *[]float64 = nil

	switch p {
	case 0.05:
		critical = &critical5
	}

	if critical == nil || df <= 0 || len(*critical) < df {
		return 0, errors.New("Unsupported parameters")
	}

	return (*critical)[df-1], nil
}

func calcIntegral(interval []float64, stdDev, mean float64) float64 {
	sum := 0.0

	for i := 1; i < len(interval); i++ {
		f := calcLaplasFunction(interval[i], stdDev, mean)
		if !math.IsNaN(f) {
			sum += f
		}
	}

	a := calcLaplasFunction(interval[0], stdDev, mean)
	b := calcLaplasFunction(interval[len(interval)-1], stdDev, mean)
	sum += (a + b) / 2

	return sum
}

func calcLaplasFunction(x, stdDev, mean float64) float64 {
	return 1.0 / (stdDev * math.Sqrt(2*math.Pi)) *
		math.Exp(-math.Pow(x-mean, 2)/(2*stdDev*stdDev))
}

func GetAbsoluteFrequencies(intervals [][]float64) []float64 {
	frequencies := make([]float64, len(intervals))

	for i, interval := range intervals {
		frequencies[i] = float64(len(interval))
	}

	return frequencies
}

func MakeIntervals(sample []float64) ([][]float64, float64, float64, float64) {
	intervals := make([][]float64, GetNumberOfIntervals(len(sample)))
	min, max := minMax(sample)
	dataRange := max - min
	intervalLen := dataRange / float64(len(intervals))

	for _, n := range sample {
		index := int(math.Min((n-min)/intervalLen, float64(len(intervals)-1)))
		intervals[index] = append(intervals[index], n)
	}

	return intervals, intervalLen, min, max
}

func GetIntervalBorders(min, intevalLen float64, intervals int) []float64 {
	borders := make([]float64, intervals+1)

	for i := 0; i < intervals+1; i++ {
		borders[i] = intevalLen*float64(i) + min
	}

	return borders
}

func GetNumberOfIntervals(n int) int {
	return 1 + int(math.Log2(float64(n)))
}

func minMax(arr []float64) (float64, float64) {
	max := arr[0]
	min := arr[0]
	for _, n := range arr {
		if n > max {
			max = n
		}
		if n < min {
			min = n
		}
	}
	return min, max
}
