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

module PMainParser where

import Text.ParserCombinators.Parsec

import Control.Monad

import Data.List
import PBasicParser
-- import PParser2
-- import PUtils
import PData
-- import PShow
import qualified Data.Map as Map

pParser :: GenParser Char ParserState [[Float]]
pParser = do tokens0 <- many $ pToken
             eof
             let tokens = pcut (filter pPositive tokens0) []
             -- let tokens = filter pPositive tokens0
             return $ tokens
             -- return tokens

pPositive :: Float -> Bool
pPositive x = (x >= 0)

pcut :: [Float] -> [[Float]] -> [[Float]]
pcut [] l = l
pcut l_tokens l = pcut (drop 3 l_tokens) (l ++ [take 3 l_tokens]) 

pToken :: GenParser Char ParserState Float
pToken = 
         try pParseNormalTime
     <|> try pParseLCSTime
     <|> do ch <- anyChar
            return (-1.0)
     <?> "line"

pParseLCSTime :: GenParser Char ParserState Float
pParseLCSTime = 
    do reserved "time"
       colon
       l_time <- number
       case l_time of
            Left a -> return $ fromIntegral(a)
            Right b -> return $ realToFrac(b)

pParseNormalTime :: GenParser Char ParserState Float
pParseNormalTime = 
    do reserved "time"
       colon
       l_time <- number
       reserved "ms"
       case l_time of
            Left a -> return $ fromIntegral(a)/1000
            Right b -> return $ fromIntegral(round $ b)/1000


