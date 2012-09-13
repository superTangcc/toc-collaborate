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
import PData
import qualified Data.Map as Map

pParser :: GenParser Char ParserState [[(Either Int Float)]]
pParser = do tokens0 <- many $ pToken
             eof
             let tokens = pcut (filter pPositive tokens0) []
             -- let tokens = filter pPositive tokens0
             return $ tokens
             -- return tokens

pPositive :: (Either Int Float) -> Bool
pPositive (Left x) = (x >= 0)
pPositive (Right x) = (x >= 0)

pcut :: [(Either Int Float)] -> [[(Either Int Float)]] -> [[(Either Int Float)]]
pcut [] l = l
pcut l_tokens l = pcut (drop 4 l_tokens) (l ++ [take 4 l_tokens]) 

pToken :: GenParser Char ParserState (Either Int Float)
pToken = 
         try pParseArraySize
     <|> try pParsePPTime
     <|> try pParseMetaQueryTime
     <|> try pParseScanQueryTime
     <|> do ch <- anyChar
            return $ Right (-1.0)
     <?> "line"

pParseArraySize :: GenParser Char ParserState (Either Int Float)
pParseArraySize =
    do reserved "array_size"
       l_sizes <- parens (sepBy1 natural (symbol "x"))
       let l_size = foldr (*) 1 l_sizes
       return $ Left $ fromIntegral l_size

pParsePPTime :: GenParser Char ParserState (Either Int Float)
pParsePPTime = 
    do reserved "preprocessing"
       symbol "takes"
       colon
       l_time <- number
       reserved "ms"
       case l_time of
            Left a -> return $ Left (fromIntegral $ a)
            Right b -> return $ Right (realToFrac $ b)

pParseMetaQueryTime :: GenParser Char ParserState (Either Int Float)
pParseMetaQueryTime = 
    do reserved "query"
       symbol "takes"
       colon
       l_time <- number
       reserved "ms"
       case l_time of
            Left a -> return $ Left (fromIntegral $ a)
            Right b -> return $ Right (realToFrac $ b)

pParseScanQueryTime :: GenParser Char ParserState (Either Int Float)
pParseScanQueryTime = 
    do reserved "scan"
       symbol "takes"
       colon
       l_time <- number
       reserved "ms"
       case l_time of
            Left a -> return $ Left (fromIntegral $ a)
            Right b -> return $ Right (realToFrac $ b)

{-
pParseNormalTime :: GenParser Char ParserState Float
pParseNormalTime = 
    do reserved "time"
       colon
       l_time <- number
       reserved "ms"
       case l_time of
            Left a -> return $ fromIntegral(a)/1000
            Right b -> return $ fromIntegral(round $ b)/1000
-}

