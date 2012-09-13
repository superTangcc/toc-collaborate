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

module Main where

import System
import IO hiding (try) -- "try" is also defined in Parsec
import Data.List
import System.Directory 
import System.Cmd (rawSystem)
import Data.Char (isSpace)
import qualified Data.Map as Map
import Text.ParserCombinators.Parsec (runParser, parseFromFile)

import PData
import PMainParser

main :: IO ()
main = do args <- getArgs
          let (inFile, outFile) 
                = parseArgs ([], []) args
          fileExist <- doesFileExist $ inFile
          whilst (not fileExist) $ do
             putStrLn (inFile ++ " doesn't exist!")
             exitFailure
          putStrLn ("inFile = " ++ inFile ++ "; Pochoir outFile = " ++ outFile)
          inh <- openFile inFile ReadMode
          outh <- openFile outFile WriteMode
          pProcess inh outh
          hClose inh
          hClose outh

whilst :: Bool -> IO () -> IO ()
whilst True action = action
whilst False action = return () 

rename :: String -> String -> String
rename pSuffix fname = name ++ pSuffix ++ ".mdat"
    where (name, suffix) = break ('.' ==) fname

parseArgs :: (String, String) -> [String] -> (String, String)
parseArgs (inFile, outFile) [] = (inFile, outFile)
parseArgs (inFile, outFile) aL = 
        let (inFile, outFile) = findFile aL ([], [])
        in  (inFile, outFile) 

findFile :: [String] -> (String, String) -> (String, String)
findFile [] (l_file, l_dir) = (l_file, l_dir)
findFile (a:as) (l_file, l_dir)
    | isSuffixOf ".dat" a = 
        let l_file' = drop (1 + (pLast $ findIndices (== '/') a)) a
            l_dir'  = take (1 + (pLast $ findIndices (== '/') a)) a
            pLast [] = -1
            pLast aL@(a:as) = last aL
            l_out_file = rename "" l_file'
        in  (l_dir' ++ l_file', l_dir' ++ l_out_file)
    | otherwise = findFile as (l_file, l_dir)

pProcess :: Handle -> Handle -> IO ()
pProcess inh outh = 
    do ls <- hGetContents inh
       let ppState = ParserState { pState = "" }
       case runParser pParser ppState "" ls of
           Left err -> print err
           Right runTimeL -> hPutStrLn outh $ showRunTime runTimeL
{-
           Right runTimeL -> 
                let fl_sl = transpose $ flip pcut [] $ findList [] (drop 0 runTimeL)
                    fl_pl = transpose $ flip pcut [] $ findList [] (drop 1 runTimeL)
                    fl_pochoir = transpose $ flip pcut [] $ findList [] (drop 2 runTimeL)
                in  do
                        hPutStrLn outhSl $ showRunTime fl_sl 
                        hPutStrLn outhPl $ showRunTime fl_pl 
                        hPutStrLn outhPochoir $ showRunTime fl_pochoir 
-}

findList :: [Float] -> [Float] -> [Float]
findList fl [] = fl
findList fl l = 
    let fl' = fl ++ [head l]
    in  findList fl' (drop 3 l)
