open Belt.Result;

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

module Promise = {
  let return = x => return(x) |> Js.Promise.resolve;
  let error = x => error(x) |> Js.Promise.resolve;
  let isOk = promise =>
    promise |> Js.Promise.then_(x => isOk(x) |> Js.Promise.resolve);
  let isError = promise =>
    promise |> Js.Promise.then_(x => isError(x) |> Js.Promise.resolve);
  let ap = (pResult, pfResult) =>
    Js.Promise.all2((pResult, pfResult))
    |> Js.Promise.then_(((result, fResult)) =>
         ap(result, fResult) |> Js.Promise.resolve
       );
  let map = (fn, promise) =>
    promise
    |> Js.Promise.then_(result => map(fn, result) |> Js.Promise.resolve);
  let fold = (error, ok, promise) =>
    promise |> Js.Promise.then_(fold(error, ok));
  let bimap = (fnError, fnOk, promise) =>
    promise
    |> Js.Promise.then_(result =>
         bimap(fnError, fnOk, result) |> Js.Promise.resolve
       );
  let andThen = (fn, promise) =>
    promise
    |> Js.Promise.then_(
         fun
         | Error(e) => Error(e) |> Js.Promise.resolve
         | Ok(v) => fn(v),
       );
  let flatMap = (fn, promise) =>
    promise
    |> Js.Promise.then_(result => flatMap(fn, result) |> Js.Promise.resolve);
  let unsafeResolve = promise =>
    promise
    |> Js.Promise.then_(result => result |> unsafeGet |> Js.Promise.resolve);
  let unsafeMapResolve = (fn, promise) =>
    promise |> map(fn) |> unsafeResolve;
  let unsafeFlatMapResolve = (fn, promise) =>
    promise |> flatMap(fn) |> unsafeResolve;
};
