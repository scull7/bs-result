let return = x => Belt.Result.Ok(x) |> Js.Promise.resolve;

let error = x => Belt.Result.Error(x) |> Js.Promise.resolve;

let isOk = promise =>
  promise
  |> Js.Promise.then_(x =>
       (
         switch (x) {
         | Belt.Result.Ok(_) => true
         | Belt.Result.Error(_) => false
         }
       )
       |> Js.Promise.resolve
     );

let isError = promise =>
  promise
  |> Js.Promise.then_(x =>
       (
         switch (x) {
         | Belt.Result.Ok(_) => false
         | Belt.Result.Error(_) => true
         }
       )
       |> Js.Promise.resolve
     );

let map = (fn, promise) =>
  promise
  |> Js.Promise.then_(result =>
       switch (result) {
       | Belt.Result.Ok(v) => fn(v) |> return
       | Belt.Result.Error(e) => e |> error
       }
     );

let fold = (ok, error, promise) =>
  promise
  |> Js.Promise.then_(result =>
       switch (result) {
       | Belt.Result.Ok(v) => ok(v)
       | Belt.Result.Error(e) => error(e)
       }
     );

let bimap = (fnOk, fnError, promise) =>
  promise
  |> Js.Promise.then_(result =>
       switch (result) {
       | Belt.Result.Ok(v) => fnOk(v) |> return
       | Belt.Result.Error(e) => fnError(e) |> error
       }
     );

let andThen = (fn, promise) =>
  promise
  |> Js.Promise.then_(
       fun
       | Belt.Result.Error(e) => error(e)
       | Belt.Result.Ok(v) => fn(v),
     );

let flatMap = (fn, promise) =>
  promise
  |> Js.Promise.then_(result =>
       switch (result) {
       | Belt.Result.Ok(v) => fn(v) |> Js.Promise.resolve
       | Belt.Result.Error(e) => error(e)
       }
     );

let ap = (pResult, pfResult) =>
  pfResult
  |> Js.Promise.then_(fResult =>
       switch (fResult) {
       | Belt.Result.Ok(fn) => map(fn, pResult)
       | Belt.Result.Error(e) => error(e)
       }
     );

let unsafeResolve = promise =>
  promise
  |> Js.Promise.then_(result =>
       switch (result) {
       | Belt.Result.Ok(v) => Js.Promise.resolve(v)
       | Belt.Result.Error(e) => raise(e)
       }
     );

let unsafeMapResolve = (fn, promise) => promise |> map(fn) |> unsafeResolve;

let unsafeFlatMapResolve = (fn, promise) =>
  promise |> flatMap(fn) |> unsafeResolve;
