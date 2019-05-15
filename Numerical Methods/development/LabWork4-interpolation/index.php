<?php

require_once 'LagrangeInterpolation.php';

$lagrangeInterpolation = new LagrangeInterpolation();

$a = 0;
$b = 4;
$n = 5;
$h = 0.1;

$steps = ($b - $a) / $h;

$xs = [];
$ys = [];

$tabulateXs = [];
$tabulateYs = [];
$lagrangeYs = [];

for ($i = 0; $i < $n; $i++) {
    $x = $a + $i * ($b - $a) / ($n - 1);

    $xs[] = $x;
    $ys[] = func($x);
}

for ($i = 0; $i <= $steps; $i++) {
    $tabulateXs[] = $a + $i * $h;
}

foreach ($tabulateXs as $x) {
    $tabulateYs[] = func($x);
    $lagrangeYs[] = $lagrangeInterpolation->calc($xs, $ys, $x);
}

$file = fopen('interpolation.csv', 'w');
fputcsv($file, ['x', 'F(x)', 'L(x)'], ';');

foreach ($tabulateXs as $i => $x) {
    $rowData = [
        $x,
        $tabulateYs[$i],
        $lagrangeYs[$i]
    ];

    fputcsv($file, $rowData, ';');
}

echo "Done!" . PHP_EOL;

function func($x)
{
    return exp(0.5 * $x);
}
