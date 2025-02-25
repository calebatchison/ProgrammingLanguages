function _isPrime(num) {
    if (num == 2) {
        return true;
    }
    var limit = Math.ceil(Math.sqrt(num)) + 1;
    for (var i = 2; i < limit; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
function containsZero(s) {
    return s.indexOf("0") != -1;
}
function isTruncatableLR(n) {
    var s = "" + n;
    while (s.length >= 1) {
        if (!_isPrime(parseInt(s))) {
            return false;
        }
        if (s.length == 1) {
            s = "";
        }
        else {
            s = s.substring(1);
        }
    }
    return true;
}
function isTruncatableRL(n) {
    var s = "" + n;
    while (s.length >= 1) {
        if (!_isPrime(parseInt(s))) {
            return false;
        }
        if (s.length == 1) {
            s = "";
        }
        else {
            s = s.substring(0, s.length - 1);
        }
    }
    return true;
}
function solve1() {
    var sum = 0;
    for (var i = 1000; i <= 9999; i++) {
        if (_isPrime(i) &&
            !containsZero("" + i) &&
            isTruncatableLR(i) &&
            isTruncatableRL(i)) {
            sum += i;
            console.log(i);
        }
    }
    return sum;
}
console.log(solve1());
function sortString(s) {
    return s.split("").sort().join(""); //.replace(/\,/g, "");//replaceAll(",","");
}
function isPandigital(s) {
    if (s.length != 9) {
        return false;
    }
    s = sortString(s);
    if (s != "123456789") {
        return false;
    }
    return true;
}
function solve2() {
    var max = 0;
    for (var n = 2; n <= 9; n++) {
        for (var i = 1; i < Math.pow(10, 9 / n); i++) {
            var concat = "";
            for (var j = 1; j <= n; j++) {
                concat += ("" + (j * i));
            }
            if (isPandigital(concat)) {
                max = Math.max(parseInt(concat), max);
            }
        }
    }
    return max;
}
console.log(solve2());
function triangleSolutions(n) {
    var count = 0;
    for (var a = 1; a <= n; a++) {
        for (var b = a; b <= n; b++) {
            for (var c = b + 1; c <= n; c++) {
                if (a + b + c != n) {
                    continue;
                }
                if (Math.pow(a, 2) + Math.pow(b, 2) != Math.pow(c, 2)) {
                    continue;
                }
                count++;
            }
        }
    }
    return count;
}
console.log(triangleSolutions(120));
