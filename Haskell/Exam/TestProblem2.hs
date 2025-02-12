-- Count from 1 to n and keep all primes that are palindromes. 
-- Some of the numbers remaining in the list have even digits. 
-- Add up all of the even digits. Remember, just the digit values. 
-- For instance the number 541 has a digit of 4 so you would add 4 from that number (not 40). 
-- Submit this as TestProblem2.hs. You can solve this recursively or with recursion.

-- solveProblem2 n

-- solveProblem2 10
-- 2
-- solveProblem2 100
-- 2
-- solveProblem2 1000
-- 30
-- solveProblem2 10000
-- 30

--  Now solve for n=100000 and n=1000000

-- creating list
isPrime n
  | n < 2     = False
  | otherwise = not (hasDivisor n 2)
  where
    hasDivisor n d
      | d * d > n      = False
      | n `mod` d == 0 = True
      | otherwise      = hasDivisor n (d + 1)
isPalindrome n = (show n) == (reverse (show n))
allPrimePalindromes n = [ x | x <- [1..n], isPrime x && isPalindrome x]

-- list processing  stuff
digits :: Int -> [Int]
digits n = reverse (extractDigits (abs n))
  where
    extractDigits 0 = []
    extractDigits x = (x `mod` 10) : extractDigits (x `div` 10)

flattenDigits :: [Int] -> [Int]
flattenDigits [] = []
flattenDigits (x:xs) = digits x ++ flattenDigits xs

-- THIS TOOK FOREVER TO RUN FOR n=100000 BUT IT GOT THERE AND RETURNED 608
solveProblem2 n = sum [x | x <- flattenDigits (allPrimePalindromes n), even x]

