// Triangle numbers

function triangleNumbers(n) {
    var sum = 0;

    for (var i = 1; i <= n; i++) {
        sum += i;
    }
}

function factorsOf(n) {
    var factors = [];

    for (var i = 1; i <= n; i++) {
        if (n % i === 0) {
            factors.push(i);
        }
    }

    return factors;
}

function solveProblem1(n) {
    var triangleNum = triangleNumbers(n);
    var factors = factorsOf(triangleNum);

    return factors.length;
}

console.log(solveProblem1(100));