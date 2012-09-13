module Bag where

-- This version implements bag as a Data.Map, next version, probably be in Data.List
import Data.List
import qualified Data.Map as Map

data PType = PFull | PNull deriving (Show, Eq)

data Pennent = PNode {
    root :: PType,
    key :: Int, -- key is the number of elements stored in the pennant 2^key
    left :: Pennent,
    right :: Pennent
} | PRoot {
    root :: PType,
    key :: Int, -- key is the number of elements stored in the pennant 2^key
    child :: Pennent
} | PVal {
    val :: Int
} deriving (Eq)

data PBag = PBag {
    keys :: [Int],
    bag :: Map.Map Int Pennent
} 

instance Show Pennent where
    show (PNode roo k l r) = "root = " ++ show roo ++ ", key = " ++ show k ++ 
                             ", left = [" ++ show l ++ "], right = [" ++ show r ++ "]\n"
    show (PRoot roo k c) = "root = " ++ show (roo) ++ ", key = " ++ show (k) ++
                           ", child = " ++ show (c)
    show (PVal n) = "val = " ++ show n

instance Show PBag where
    show (PBag k b) = "keys = " ++ show (k) ++ "\n" ++
                      (concatMap pennant_show $ map (flip bag_lookup b) k)

pennant_create :: Int -> Pennent
pennant_create n = PRoot { root = PFull, key = 0, child = PVal {val = n} }

pennant_union :: Pennent -> Pennent -> Pennent
pennant_union a b =
    let a' = PNode { 
                root = root a, 
                -- should throw an exception when key a /= key b
                key = if key a == key b then (key a) + 1 else -(key a + key b),
                left = child a, right = child b }
        b' = PRoot { root = root b, key = key a', child = a' }
    in  b'

pennant_show :: Maybe Pennent -> String
pennant_show penn = 
    case penn of
        Just p -> show p
        Nothing -> ""

bag_lookup :: Int -> Map.Map Int Pennent -> Maybe Pennent
bag_lookup k b = Map.lookup k b 

bag_create :: PBag
bag_create = PBag { keys = [], bag = Map.empty }

bag_delete :: Int -> PBag -> PBag
bag_delete k b = b { keys = delete k $ keys b, bag = Map.delete k $ bag b }

bag_insert :: Pennent -> PBag -> PBag
bag_insert penn b =
    let k = key penn
    in  case Map.lookup k (bag b) of
            Just penn' -> let penn'' = pennant_union penn penn'
                              b' = bag_delete k b 
                          in  bag_insert penn'' b'
            Nothing -> b { keys = (keys b) ++ [k],
                           bag = Map.insert k penn (bag b) }

-- replace the original pennant in the position
bag_replace :: Pennent -> PBag -> PBag
bag_replace penn pb =
    let k = key penn
        f x = Just penn
        b' = Map.update f k $ bag pb
        keys' = if elem k (keys pb) then keys pb else (keys pb) ++ [k]
    in  pb { keys = keys', bag = b' }

-- (x, y, z) -> (s, c)
f :: (Int, Maybe Pennent, Maybe Pennent, Maybe Pennent, PBag, PBag) -> (Maybe Pennent, Maybe Pennent, PBag, PBag)
f (k, Nothing, Nothing, Nothing, b1, b2) = (Nothing, Nothing, b1, b2)
f (k, Just x, Nothing, Nothing, b1, b2) = 
    let b1' = bag_delete k b1
        b2' = bag_insert x b2
    in  (Just x, Nothing, b1', b2')
f (k, Nothing, Just y, Nothing, b1, b2) = (Just y, Nothing, b1, b2)
f (k, Nothing, Nothing, Just z, b1, b2) = 
    let b2' = bag_insert z b2
    in  (Just z, Nothing, b1, b2')
f (k, Just x, Just y, Nothing, b1, b2) = 
    let b1' = bag_delete k b1
        b2' = bag_delete k b2
    in  (Nothing, Just $ pennant_union x y, b1', b2')
f (k, Just x, Nothing, Just z, b1, b2) = 
    let b1' = bag_delete k b1
    in  (Nothing, Just $ pennant_union x z, b1', b2)
f (k, Nothing, Just y, Just z, b1, b2) = 
    let b2' = bag_delete k b2
    in  (Nothing, Just $ pennant_union y z, b1, b2')
f (k, Just x, Just y, Just z, b1, b2) = 
    let b1' = bag_delete k b1
        b2' = bag_replace x b2
    in  (Just x, Just $ pennant_union y z, b1', b2')

-- moving elements from b1 to b2
bag_merge :: PBag -> PBag -> PBag
bag_merge b1 b2 = 
    let key1 = (last . sort . keys) b1
        key2 = (last . sort . keys) b2
        end = if key1 >= key2 then key1 else key2 
    in  bag_merge' 0 end b1 b2 Nothing

bag_merge' :: Int -> Int -> PBag -> PBag -> Maybe Pennent -> PBag
bag_merge' hk tk b1 b2 carry =
    let key1 = keys b1
        penn1 = Map.lookup hk (bag b1)
        penn2 = Map.lookup hk (bag b2)
        (s, c, b1', b2') = f (hk, penn1, penn2, carry, b1, b2)
    in  if hk == tk || (null $ keys b1')
           then b2'
           else bag_merge' (hk + 1) tk b1' b2' c

bag_walk :: PBag -> String
bag_walk b = show b


