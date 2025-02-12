import Prelude ()

-- isPrime
isPrime n = ip n [2..(isqrt (n))] 
    where 
    ip _ [] = True 
    ip n (x:xs)
        | n `mod` x == 0 = False
        | otherwise = ip n xs

fiboinacci
    fibList n = go n 1 1 
    where 
    go n f s =
    | (f+s) > n = [] 
    | otherwise = (f+s) : go n s (f+s)
