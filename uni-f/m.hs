and' :: [Bool]->Bool
and' [] = True
and' (x:xs) = foldr (&&) True (x:xs)

f x
  | x==1 = True
  | otherwise = False

all' :: (a->Bool)->[a]->Bool
all' p (x:xs) = foldr (&&) True (p x:map p xs)
