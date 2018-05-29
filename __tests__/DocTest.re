open Jest;

describe("Documentatino example tests", () =>
  describe("Usage", () => {
    test("Generate a new result.", () => {
      let actual =
        Result.return(20)
        |> Result.map(x => x + 20)
        |> Result.flatMap(x => Result.return(x + 2))
        |> Result.getOrElse(-1);
      Expect.expect(actual) |> Expect.toEqual(42);
    });
    test("Using a Belt.Result", () => {
      let actual =
        Belt.Result.Ok(x => x + 10)
        |> Result.ap(Result.return(20))
        |> Belt.Result.map(_, x => x + 10)
        |> Result.flatMap(x => Belt.Result.Ok(x + 2))
        |> Belt.Result.getWithDefault(_, -1);
      Expect.expect(actual) |> Expect.toEqual(42);
    });
    testPromise("Js.Promise integration.", () =>
      Js.Promise.resolve(20)
      |> Js.Promise.then_(x => Result.Promise.return(x))
      |> Result.Promise.flatMap(x => Result.return(x + 10))
      |> Result.Promise.map(x => x + 10)
      |> Result.Promise.andThen(x =>
           x + 2 |> Result.return |> Js.Promise.resolve
         )
      |> Result.Promise.unsafeResolve
      |> Js.Promise.then_(actual =>
           Expect.expect(actual) |> Expect.toEqual(42) |> Js.Promise.resolve
         )
    );
  })
);
