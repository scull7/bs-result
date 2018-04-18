type result('bad, 'good) =
  | Error('bad)
  | Ok('good);

let of_ = x => Ok(x);

let pure = of_;

let error = x => Error(x);

let isOk =
  fun
  | Error(_) => false
  | Ok(_) => true;

let isError =
  fun
  | Error(_) => true
  | Ok(_) => false;

let ap = (x, result) =>
  switch (result) {
  | Error(bad) => Error(bad)
  | Ok(fn) => fn(x) |> pure
  };

let map = (fn, result) =>
  switch (result) {
  | Error(bad) => Error(bad)
  | Ok(good) => good |> fn |> pure
  };

let fold = (error, ok, result) =>
  switch (result) {
  | Error(bad) => error(bad)
  | Ok(good) => ok(good)
  };

let bimap = (fnError, fnOk, result) =>
  switch (result) {
  | Error(bad) => bad |> fnError |> error
  | Ok(good) => good |> fnOk |> pure
  };

let toOption =
  fun
  | Error(_) => None
  | Ok(good) => Some(good);

let swap =
  fun
  | Error(bad) => pure(bad)
  | Ok(good) => error(good);

let chain = (fn, result) =>
  switch (result) {
  | Error(bad) => Error(bad)
  | Ok(good) => fn(good)
  };

let flatMap = chain;

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
  let of_ = x => pure(x) |> Js.Promise.resolve;
  let pure = of_;
  let error = x => error(x) |> Js.Promise.resolve;
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
  let chain = (fn, promise) =>
    promise
    |> Js.Promise.then_(result => chain(fn, result) |> Js.Promise.resolve);
};
