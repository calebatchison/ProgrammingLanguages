-- Caleb Atchison
-- Assignment 1

import Data.Maybe

-- 1 Function that multiplies two numbers
multTwo x y = x * y

-- 2 Function that multiplies three numbers
multThree x y z = x * y * z

-- 3 first_a function using list comprehension
first_a n = [x | x <- [1..n], (mod x 6 == 0) || (mod x 11 == 0)]

-- 4 first_b using helper function
isMult6Or11 n = (mod n 6 == 0) || (mod n 11 == 0)
first_b n = [x | x <- [1..n], isMult6Or11 x]

-- 5 second_a function using list comprehension
second_a n = [x | x <- [1..n], let firstDigit = listToMaybe (show x) in ((firstDigit == Just '3') && (reverse (show x) == (show x)))]

-- 6 second_b using helper function
isPalindromeThatStartsWithDigit3 x = let firstDigit = listToMaybe (show x) in ((firstDigit == Just '3') && (reverse (show x) == (show x)))
second_b n = [x | x <- [1..n], isPalindromeThatStartsWithDigit3 x]