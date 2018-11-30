module TTGen where
import Prelude hiding (isEven)

check :: String->String
check (x:xs) = displayMess (isEven ((sumlist (map f (x:xs))) `rem` 2))

displayMess :: Bool->String
displayMess True = "Valid Compound Proposition"
displayMess False = "Invalid Compound Proposition"

isEven :: Int->Bool
isEven n
  | n==0 = True
  | otherwise = False

sumlist :: [Int]->Int
sumlist (x:xs) = foldr (+) 0 (x:xs)

f :: Char->Int
f x
  | x=='('     = 1
  | x==')'     = 1
  | otherwise = 0
