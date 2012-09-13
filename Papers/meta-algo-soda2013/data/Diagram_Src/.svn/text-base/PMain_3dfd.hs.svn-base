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

module Main_3dfd where

import System
import IO hiding (try) -- "try" is also defined in Parsec
import Data.List
import System.Directory 
import System.Cmd (rawSystem)
import Data.Char (isSpace)
import qualified Data.Map as Map
import Text.ParserCombinators.Parsec (runParser, parseFromFile)

import PData_3dfd
import PMainParser_3dfd

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
          hClose outh

whilst :: Bool -> IO () -> IO ()
whilst True action = action
whilst False action = return () 

rename :: String -> String
rename fname = name ++ ".mdat"
    where (name, suffix) = break ('.' ==) fname

parseArgs :: (String, String) -> [String] -> (String, String)
parseArgs (inFile, outFile) [] = (inFile, outFile)
parseArgs (inFile, outFile) aL = 
        let (inFile, outFile) = fineFile aL ([], [])
        in  (inFile, outFile) 

fineFile :: [String] -> (String, String) -> (String, String)
fineFile [] (l_file, l_dir) = (l_file, l_dir)
fineFile (a:as) (l_file, l_dir)
    | isSuffixOf ".out" a = 
        let l_file' = drop (1 + (pLast $ findIndices (== '/') a)) a
            l_dir'  = take (1 + (pLast $ findIndices (== '/') a)) a
            pLast [] = -1
            pLast aL@(a:as) = last aL
            l_pochoir_file = rename l_file' 
        in  (l_dir' ++ l_file', l_dir' ++ l_pochoir_file)
    | otherwise = fineFile as (l_file, l_dir)

pProcess :: Handle -> Handle -> IO ()
pProcess inh outh = 
    do ls <- hGetContents inh
       let ppState = ParserState { pState = "" }
       case runParser pParser ppState "" ls of
           Left err -> print err
           Right runTimeL -> hPutStrLn outh $ showRunTime runTimeL
