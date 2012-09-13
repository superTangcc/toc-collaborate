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
module PData_3dfd where

import Text.ParserCombinators.Parsec
import Control.Monad

import Data.Char
import Data.List
import qualified Data.Map as Map

data ParserState = ParserState {
    pState :: String
} deriving Show

breakline :: String
breakline = "\n"

showRunTime :: [[Float]] -> String
showRunTime [] = ""
showRunTime (x:xs) = showFloatList x ++ breakline ++ showRunTime xs
    where showFloatList [] = ""
          showFloatList (f:fs) = show f ++ "\t" ++ showFloatList fs
