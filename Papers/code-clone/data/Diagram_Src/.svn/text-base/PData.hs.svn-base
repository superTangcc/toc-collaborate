{-
 ----------------------------------------------------------------------------------
 -  Copyright (C) 2010  Massachusetts Institute of Technology
 -  Copyright (C) 2010  Yuan Tang <yuantang@csail.mit.edu>
 - 		                Charles E. Leiserson <cel@mit.edu>
 - 	 
 -   This program is free software: you can redistribute it and/or modify
 -   it under the terms of the GNU General Public License as published by
 -   the Free Software Foundation, either version 3 of the License, or
 -   (at your option) any later version.
 -
 -   This program is distributed in the hope that it will be useful,
 -   but WITHOUT ANY WARRANTY; without even the implied warranty of
 -   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 -   GNU General Public License for more details.
 -
 -   You should have received a copy of the GNU General Public License
 -   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -
 -   Suggestsions:                  yuantang@csail.mit.edu
 -   Bugs:                          yuantang@csail.mit.edu
 -
 --------------------------------------------------------------------------------
 -}

{-# LANGUAGE TypeSynonymInstances #-}
module PData where

import Text.ParserCombinators.Parsec
import Control.Monad

import Text.Printf
import Data.Char
import Data.List
import qualified Data.Map as Map

data ParserState = ParserState {
    pState :: String
} deriving Show

breakline :: String
breakline = "\n"

blank :: String
blank = "\t\t"

showRunTime :: [[(Either Int Float)]] -> String
showRunTime [] = ""
showRunTime (x:xs) = showIFList x ++ breakline ++ showRunTime xs

showIFList :: [(Either Int Float)] -> String
showIFList [] = ""
showIFList (a:b:c:d:e) = showIF b ++ blank ++ showIF a ++ blank ++ showIF c ++ blank ++ showIF d ++ showIFList e
    where showIF (Left i) = printf "%-16d" i
          showIF (Right f) = printf "%.6e" f


