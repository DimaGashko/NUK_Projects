<?php

class LagrangeInterpolation {

    public function calc(array $xs, array $ys, float $x) {
        $res = 0;

        foreach ($ys as $i => $y) {
            $res += $y * $this->calcOne($xs, $i, $x);
        }

        return $res;
    }

    private function calcOne(array $xs, $i, $x) {
        $p1 = 1;
        $p2 = 1;

        foreach ($xs as $j => $xi) {
            if ($j === $i) continue;

            $p1 *= $x - $xi;
            $p2 *= $xs[$i] - $xi;
        }

        return $p1 / $p2;
    }

}