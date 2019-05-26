../assets/index.html: src/Api.re src/Main.re
	yarn build
	node_modules/.bin/webpack --module-bind 'svg=file-loader'
	rsync -Pavz --delete build/ ../assets/

src/Api.re: GenerateReason.hs ../server/src/Api.hs
	(cd ../ ; stack exec -- runhaskell -iserver/src client/GenerateReason.hs)
