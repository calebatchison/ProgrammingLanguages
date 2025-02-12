// Java Script assignment 1
// Caleb Atchison

// 1: Longest Collatz Sequence

const collatzMap = new Map();
collatzMap.set(1, 1);  // Base case: the chain length of 1 is 1

function getCollatzLength(n) {
    return getCollatzRecursive(n);
}

function getCollatzRecursive(n) {
  if (collatzMap.has(n)) {
    return collatzMap.get(n);
  }
  
  // Compute the next number in the sequence
  let next;
  if (n % 2 === 0) {
    next = n / 2;
  } else {
    next = 3 * n + 1;
  }

  const length = 1 + getCollatzRecursive(next);
  
  collatzMap.set(n, length);
  
  return length;
}

function findLongestCollatzSequence(limit) {
  let maxLength = 0;
  let numberWithMaxLength = 1;

  for (let i = 1; i < limit; i++) {
    const currentLength = getCollatzLength(i);
    if (currentLength > maxLength) {
      maxLength = currentLength;
      numberWithMaxLength = i;
    }
  }

  return numberWithMaxLength;
}
let result1 = findLongestCollatzSequence(1_000_000);
console.log(`Problem 1: ${result1}`);


// 2: Factorial Digit Sum

function factorialSum(n) {
  let factorial = BigInt(1);
  for (let i = 1; i <= n; i++) {
    factorial *= BigInt(i);
  }

  const sum = factorial.toString().split('').reduce((acc, digit) => acc + parseInt(digit), 0);
  return sum;
}

let result2 = factorialSum(100)
console.log(`Problem 2: ${result2}`);