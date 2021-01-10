package random

var next int64 = 1

func Lcg() int {
	next = (next*1103515245 + 12345) % 2147483648
	return int(next)
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
