open Belt.Result;

module Promise = Result_promise;

let return = x => Ok(x);

let error = x => Error(x);

let isOk =
  fun
  | Error(_) => false
  | Ok(_) => true;

let isError =
  fun
  | Error(_) => true
  | Ok(_) => false;

let map = (fn, result) =>
  switch (result) {
  | Error(bad) => Error(bad)
  | Ok(good) => good |> fn |> return
  };

let fold = (ok, error, result) =>
  switch (result) {
  | Error(bad) => error(bad)
  | Ok(good) => ok(good)
  };

let bimap = (fnOk, fnError, result) =>
  switch (result) {
  | Error(bad) => bad |> fnError |> error
  | Ok(good) => good |> fnOk |> return
  };

let toOption =
  fun
  | Error(_) => None
  | Ok(good) => Some(good);

let fromOption = (errFn, option) =>
  switch (option) {
  | None => errFn() |> error
  | Some(v) => v |> return
  };

let swap =
  fun
  | Ok(good) => error(good)
  | Error(bad) => return(bad);

let flatMap = (fn, result) =>
  switch (result) {
  | Ok(good) => fn(good)
  | Error(bad) => Error(bad)
  };

let flatMap2 = (fn, fst, snd) =>
  fst |> flatMap(x => snd |> flatMap(y => fn(x, y)));

let flatMap3 = (fn, a, b, c) =>
  a |> flatMap(x => b |> flatMap(y => c |> flatMap(z => fn(x, y, z))));

let map2 = (fn, fst, snd) => fst |> flatMap(x => snd |> map(y => fn(x, y)));

let map3 = (fn, a, b, c) =>
  a |> flatMap(x => b |> flatMap(y => c |> map(z => fn(x, y, z))));

let ap = (result, fResult) =>
  switch (result) {
  | Error(bad) => Error(bad)
  | Ok(v) => map(f => f(v), fResult)
  };

let forAll = (fn, result) =>
  switch (result) {
  | Error(_) => true
  | Ok(good) => fn(good)
  };

let forEach = (fn, result) =>
  switch (result) {
  | Error(_) => ()
  | Ok(good) => fn(good)
  };

let getOrElse = (default, result) =>
  switch (result) {
  | Error(_) => default
  | Ok(good) => good
  };

let getOrElseThunk = (fn, result) =>
  switch (result) {
  | Error(bad) => fn(bad)
  | Ok(good) => good
  };

let unsafeGet =
  fun
  | Error(bad) => raise(bad)
  | Ok(good) => good;
