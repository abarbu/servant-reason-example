# Haskell Servant and Reason Example

<img src="https://cdn.svgporn.com/logos/reasonml.svg" alt="reason" height="40"/>
<img src="https://www.haskell.org/img/haskell-logo.svg" alt="reason" height="40"/>

Based off of [example-servant-elm](https://github.com/haskell-servant/example-servant-elm)

Uses [reason-export](https://github.com/abarbu/reason-export) and
[servant-reason](https://github.com/abarbu/servant-reason).

You'll see how to use Servant with Reason, how to generate Reason from a Servant API and
how it all fits together in the end.

## Makefile

There's a `Makefile` included with the following targets:

- `setup` -- Set up everything: install ghc and dependencies. (Needs `stack`, `npm`, and `yarn`.)
- `build` -- Build the server and the client.
- `server-start` -- Start the server here: <http://localhost:3000/>..

## Caveats

- This project uses <https://travis-ci.org/soenkehahn/wai-make-assets>, which is
  experimental. E.g. there's no support for serving the assets in a production setting.
