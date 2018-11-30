import Data.Char

delta :: Int->Int
dirac :: Int->(Int->Int)
delta n
  | n == 0 = 1
  | otherwise = 0
dirac n = delta.subtract n

factorial :: Int->Int
factorial n
  | n==0 = 1
  | otherwise = n*factorial(n-1)

fromJusts :: [Maybe a]->[a]
fromJusts [] = []
fromJusts (Just x:xs) = x:fromJusts xs

cart :: [a]->[b]->[(a,b)]
cart xs ys = [(w,z) | w<-xs, z<-ys]

zipWith' :: (a->b->c)->[a]->[b]->[c]
zipWith' f [] [] = []
zipWith' f (x:xs) (y:ys) = f x y:zipWith' f xs ys
