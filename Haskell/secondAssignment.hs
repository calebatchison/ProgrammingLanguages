-- Recursion and Type Classes Assignment
-- Caleb Atchison

-- PROBLEM 1
isPrime n = n > 1 && null [x | x <- [2..(n-1)], n `mod` x == 0]
problem1 n = take n [x | (x,i) <- zip [p | p <- [2..], isPrime p] [0..], even i]

-- PROBLEM 2
endsIn3 n = n `mod` 10 == 3
problem2 n = go n 1 1
    where
    go n f s
        | (f+s) > n = []
        | otherwise = if endsIn3 (f+s) 
                    then (f+s): go n s (f+s)
                    else go n s (f+s)

-- PROBLEM 3
mult5 n = n `mod` 5 == 0
factors3 n = length [x | x <- [1..n], n `mod` x == 0] == 3
problem3 n = [ x | x <- [1..n], (mult5 x || factors3 x)]