{-# LANGUAGE OverloadedStrings #-}

import           Data.List
import           Servant.Reason
import           Data.Text hiding (intercalate, map)
import           Reason

import           Api

main :: IO ()
main = do
  let code = defReasonImports :
            toReasonTypeSource (Proxy :: Proxy Item) :
            toReasonDecoderSource (Proxy :: Proxy Item) :
            generateReasonForAPI api
  writeFile "client/src/Api.re" $ intercalate "\n\n" $ map unpack code
