fac :: Int -> Int
fac n = foldr (*) 1 $ take n [1 ..]

yuan_rec :: Int -> Int -> Int
yuan_rec 1 _ = 1
yuan_rec 2 n = n+1
yuan_rec m n = foldr (+) 0 $ map (yuan_rec (m-1)) $ take (n+1) [0, 1 ..]

rezaul_rec :: Int -> Int -> Int
rezaul_rec m n = 
    let max = if n > (m-1) then n else (m-1)
        min = if n > (m-1) then (m-1) else n
        c' = foldr (*) 1 $ take (m+n-1 - max) [m+n-1, m+n-2 ..]
        c = fac min
    in  div c' c
