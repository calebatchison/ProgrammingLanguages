-- Count from 1 to n. Each number that is even and a multiple of 5 and has a leading digit of 6 should be added to a list. 
-- Submit this as TestProblem1.hs
-- solveProblem1 n. Solve with list comprehension. (Helper functions can be recursive or list comprehensions).

-- solveProblem1 10
-- []
-- solveProblem1 100
-- [60]
-- solveProblem1 1000
-- [60,600,610,620,630,640,650,660,670,680,690]

-- Now solve for n=10000 amd n=100000

isMult5orEven n = (n `mod` 2 == 0 && n `mod` 5 == 0)

solveProblem1 n = [x | x <- [1..n], isMult5orEven x, head (show x) == '6']
