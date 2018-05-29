[![Build Status](https://www.travis-ci.org/scull7/bs-result.svg?branch=master)](https://www.travis-ci.org/scull7/bs-result)
[![Coverage Status](https://coveralls.io/repos/github/scull7/bs-result/badge.svg?branch=master)](https://coveralls.io/github/scull7/bs-result?branch=master)

# bs-result
Monadic interface for [Belt.Result][belt-result]

This implementation is inspired by [JavaScript Fantasy Land][fantasy-land]
and closely follows the [Funfix.org Either][funfix-either] implementation.

## Installation
1. Install the `bs-result` package.
```sh
yarn add bs-result
```
2. Add `bs-result` to your `bsconfig.json`
```json
{
  "dependencies": [
    "bs-result"
  ]
}
```

### Usage

### Basic
```reason
let r =
  Result.return(20)
  |> Result.map(x => x + 20)
  |> Result.flatMap(x => Result.return(x + 2))
  |> Result.getOrElse(-1);
Js.log2("Result: ", r);
```

### Integrations

#### [Belt.Result][belt-result]
```reason
let r =
  Belt.Result.Ok(x => x + 10)
  |> Result.ap(Result.return(20))
  |> Belt.Result.map(_, x => x + 10)
  |> Result.flatMap(x => Belt.Result.Ok(x + 2))
  |> Belt.Result.getWithDefault(_, -1);
Js.log2("Result: ", r);
```

#### [Js.Promise][js-promise]
```reason
  Js.Promise.resolve(20)
  |> Js.Promise.then_(x => Result.Promise.return(x))
  |> Result.Promise.flatMap(x => Result.return(x + 10))
  |> Result.Promise.map(x => x + 10)
  |> Result.Promise.andThen(x =>
       x + 2 |> Result.return |> Js.Promise.resolve
     )
  |> Result.Promise.unsafeResolve
  |> Js.Promise.then_(result => {
       Js.log2("Result: ", result);
       Js.Promise.resolve();
     })
```

### [Full API Docs](api/Result.html)

## TODO
* [ ] Integration with [reason-future].
* [ ] Comonad implementation - functions are mis-named.


[funfix-core]: https://funfix.org/api/core/classes/either.html
[funfix-either]: https://funfix.org/api/core/classes/either.html
[sanctuaryjs-either]: https://sanctuary.js.org/#either-type
[fluture]: https://github.com/fluture-js/Fluture
[elm-task]: http://package.elm-lang.org/packages/elm-lang/core/latest/Task
[fantasy-land]: https://github.com/fantasyland/fantasy-land
[belt-result]: https://bucklescript.github.io/bucklescript/api/Belt.Result.html
[js-promise]: https://bucklescript.github.io/bucklescript/api/Js.Promise.html
[reason-future]: https://github.com/rationaljs/future
