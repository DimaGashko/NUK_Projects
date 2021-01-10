package chi

import (
	"errors"
	"math"
)

var critical5 = []float64{3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067, 15.507, 16.919, 18.307, 19.675, 21.026, 22.362, 23.685, 24.996, 26.296, 27.587, 28.869, 30.144, 31.410, 32.671, 33.924, 35.172, 36.415, 37.652, 38.885, 40.113, 41.337, 42.557, 43.773}

func GetCritical(df int, p float64) (float64, error) {
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

func CalculateChi2Distribution(frequencies []float64, total int) float64 {
	res := 0.0
	expected := float64(total) / float64(len(frequencies))

	for _, f := range frequencies {
		res += (f - expected) * (f - expected) / expected
	}

	return res
}

func GetAbsoluteFrequencies(intervals [][]float64) []float64 {
	frequencies := make([]float64, len(intervals))

	for i, interval := range intervals {
		frequencies[i] = float64(len(interval))
	}

	return frequencies
}

func MakeIntervals(sample []float64) [][]float64 {
	intervals := make([][]float64, GetNumberOfIntervals(len(sample)))
	min, max := minMax(sample)
	dataRange := max - min
	intevalLen := math.Ceil(dataRange / float64(len(intervals)))

	for _, n := range sample {
		index := int((n - min) / intevalLen)
		intervals[index] = append(intervals[index], n)
	}

	return intervals
}

func GetNumberOfIntervals(n int) int {
	return 1 + int(math.Log2(float64(n)))
}

func minMax(arr []float64) (float64, float64) {
	max := arr[0]
	min := arr[0]
	for _, n := range arr {
		if max < n {
			max = n
		}
		if min > n {
			min = n
		}
	}
	return min, max
}
