-- Count from 1 to n and create a list of prime factors for each number. 
-- (For factors do not include 1 or the number itself.) Find the sum of all prime factors when you count from 1 to n.

-- For instance, if n is 10 then the list of numbers is [2,3,4,5,6,7,8,9]. 
-- Then the list of all prime factors is [[],[],[2],[],[2,3],[],[2],[3]]. 
-- Note that 9 has two factors of 3 but only counts a single instance of 3--factors are distinct. The sum of this is 12.

-- Solve this with recursion. (Helper functions can be recursive or list comprehensions).

-- solveProblem3 n

-- solveProblem3 10
-- 12
-- solveProblem3 100
-- 1040
-- solveProblem3 1000
-- 64366

-- Now solve for 3000

import Data.List (nub, concat)

primeFactors :: Int -> [Int]
primeFactors n = factors n 2
  where
    factors n i
      | i * i > n = if n > 1 then [n] else []
      | n `mod` i == 0 = i : factors (n `div` i) i
      | otherwise = factors n (i + 1)

generateLists :: Int -> [[Int]]
generateLists n = map (nub . primeFactors) [2..n-1]

solveProblem3 :: Int -> Int
solveProblem3 n = sum (concat (generateLists n))

