open Jest;

exception UnsafeGetFailure(string);

describe("Basic Result Utilities", () => {
  test("of_", () => {
    let actual = Result.of_(1);
    let expected = Result.Ok(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("pure", () => {
    let actual = Result.pure(1);
    let expected = Result.Ok(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("error", () => {
    let actual = Result.error("boom");
    let expected = Result.Error("boom");
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("isOk", () => {
    let actual = (
      Result.isOk(Result.pure(1)),
      Result.isOk(Result.error("boom")),
    );
    let expected = (true, false);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("isError", () => {
    let actual = (
      Result.isError(Result.pure(1)),
      Result.isError(Result.error("boom")),
    );
    let expected = (false, true);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("ap - Ok", () => {
    let actual = Result.ap(40, Result.pure(x => x + 2));
    let expected = Result.pure(42);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("ap - Error", () => {
    let actual = Result.ap(40, Result.error("boom"));
    let expected = Result.error("boom");
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("map - Ok", () => {
    let actual = Result.map(x => x + 1, Result.pure(1));
    let expected = Result.pure(2);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("map - Error", () => {
    let actual = Result.map(x => x + 1, Result.error(1));
    let expected = Result.error(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("map2 - Ok", () => {
    let actual =
      Result.map2((x, y) => x + y, Result.pure(1), Result.pure(2));
    let expected = Result.pure(3);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("map2 - Error", () => {
    let actual =
      Result.map2((x, y) => x + y, Result.error(1), Result.error(2));
    let expected = Result.error(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("fold - Ok", () => {
    let actual = Result.fold(x => x + 2, x => x + 1, Result.pure(1));
    let expected = 2;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("fold - Error", () => {
    let actual = Result.fold(x => x + 2, x => x + 1, Result.error(1));
    let expected = 3;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("bimap - Ok", () => {
    let actual = Result.bimap(x => x + 2, x => x + 1, Result.pure(1));
    let expected = Result.pure(2);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("bimap - Error", () => {
    let actual = Result.bimap(x => x + 2, x => x + 1, Result.error(1));
    let expected = Result.error(3);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("toOption - Ok", () => {
    let actual = Result.toOption(Result.pure(1));
    let expected = Some(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("toOption - Error", () => {
    let actual = Result.toOption(Result.error(1));
    let expected = None;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("fromOption - Ok", () => {
    let fromOptionWithError = Result.fromOption(() => ());
    let actual = fromOptionWithError(Some(42));
    let expected = Result.pure(42);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("fromOption - Error", () => {
    let fromOptionWithError = Result.fromOption(() => ());
    let actual = fromOptionWithError(None);
    let expected = Result.error();
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("swap - Ok", () => {
    let actual = Result.swap(Result.pure(1));
    let expected = Result.error(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("swap - Error", () => {
    let actual = Result.swap(Result.error(1));
    let expected = Result.pure(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("chain - Ok", () => {
    let actual = Result.pure(1) |> Result.chain(x => Result.pure(x + 1));
    let expected = Result.pure(2);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("chain - Error", () => {
    let actual = Result.error(1) |> Result.chain(x => Result.pure(x + 1));
    let expected = Result.error(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("chain2 - Ok", () => {
    let actual =
      Result.chain2(
        (x, y) => Result.pure(x + y),
        Result.pure(2),
        Result.pure(40),
      );
    let expected = Result.pure(42);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("flatMap - Ok", () => {
    let actual = Result.pure(1) |> Result.flatMap(x => Result.pure(x + 1));
    let expected = Result.pure(2);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("flatMap - Error", () => {
    let actual = Result.error(1) |> Result.flatMap(x => Result.pure(x + 1));
    let expected = Result.error(1);
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("forAll - Ok (true)", () => {
    let actual = Result.pure(1) |> Result.forAll(x => x == 1);
    let expected = true;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("forAll - Ok (false)", () => {
    let actual = Result.pure(1) |> Result.forAll(x => x == 2);
    let expected = false;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("forAll - Error (pass)", () => {
    let actual = Result.error(2) |> Result.forAll(x => x == 2);
    let expected = true;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("forAll - Error (fail)", () => {
    let actual = Result.error(1) |> Result.forAll(x => x == 2);
    let expected = true;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("forEach - Ok", () => {
    let actual = ref(1);
    Result.pure(1) |> Result.forEach(x => actual := x + actual^);
    let expected = 2;
    Expect.expect(actual^) |> Expect.toEqual(expected);
  });
  test("forEach - Error", () => {
    let actual = ref(1);
    Result.error(1) |> Result.forEach(x => actual := x + actual^);
    let expected = 1;
    Expect.expect(actual^) |> Expect.toEqual(expected);
  });
  test("getOrElse - Ok", () => {
    let actual = Result.getOrElse("foo", Result.pure("bar"));
    let expected = "bar";
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("getOrElse - Error", () => {
    let actual = Result.getOrElse("foo", Result.error("baz"));
    let expected = "foo";
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("getOrElseThunk - Ok", () => {
    let actual = Result.getOrElseThunk(_ => "foo", Result.pure("bar"));
    let expected = "bar";
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("getOrElseThunk - Error", () => {
    let actual = Result.getOrElseThunk(_ => "foo", Result.error("baz"));
    let expected = "foo";
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("unsafeGet - Ok", () => {
    let actual =
      try (Result.pure(42) |> Result.unsafeGet) {
      | UnsafeGetFailure(_) => 0
      };
    let expected = 42;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
  test("unsafeGet - Error", () => {
    let actual =
      try (Result.error(UnsafeGetFailure("bad")) |> Result.unsafeGet) {
      | UnsafeGetFailure(_) => 17
      };
    let expected = 17;
    Expect.expect(actual) |> Expect.toEqual(expected);
  });
});

describe("Result.Promise based utilities", () => {
  testPromise("of_", () =>
    Result.Promise.of_(42)
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(42))
         |> Js.Promise.resolve
       )
  );
  testPromise("pure", () =>
    Result.Promise.pure(42)
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(42))
         |> Js.Promise.resolve
       )
  );
  testPromise("error", () =>
    Result.Promise.error("boom")
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.error("boom"))
         |> Js.Promise.resolve
       )
  );
  testPromise("isOk - true", () =>
    Result.pure(1)
    |> Result.Promise.isOk
    |> Js.Promise.then_(actual => {
         let expected = true;
         Expect.expect(actual)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve;
       })
  );
  testPromise("isOk - false", () =>
    Result.error("error")
    |> Result.Promise.isOk
    |> Js.Promise.then_(actual => {
         let expected = false;
         Expect.expect(actual)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve;
       })
  );
  testPromise("isError - true", () =>
    Result.error("error")
    |> Result.Promise.isError
    |> Js.Promise.then_(actual => {
         let expected = true;
         Expect.expect(actual)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve;
       })
  );
  testPromise("isError - false", () =>
    Result.pure(1)
    |> Result.Promise.isError
    |> Js.Promise.then_(actual => {
         let expected = false;
         Expect.expect(actual)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve;
       })
  );
  testPromise("ap - Ok", () =>
    Result.Promise.ap(40, Result.pure(x => x + 2))
    |> Js.Promise.then_(actual => {
         let expected = Result.pure(42);
         Expect.expect(actual)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve;
       })
  );
  testPromise("ap - Error", () =>
    Result.Promise.ap(40, Result.error("error"))
    |> Js.Promise.then_(actual => {
         let expected = Result.error("error");
         Expect.expect(actual)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve;
       })
  );
  testPromise("map - Ok", () =>
    Result.Promise.pure(42)
    |> Result.Promise.map(x => x + 1)
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(43))
         |> Js.Promise.resolve
       )
  );
  testPromise("map - Error", () =>
    Result.Promise.error("boom")
    |> Result.Promise.map(x => x + 1)
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.error("boom"))
         |> Js.Promise.resolve
       )
  );
  testPromise("fold - Ok", () =>
    Result.Promise.pure(42)
    |> Result.Promise.fold(
         x => Js.String.toUpperCase(x) |> Js.Promise.resolve,
         x => string_of_int(x) |> Js.Promise.resolve,
       )
    |> Js.Promise.then_(actual =>
         Expect.expect(actual) |> Expect.toEqual("42") |> Js.Promise.resolve
       )
  );
  testPromise("fold - Error", () =>
    Result.Promise.error("boom")
    |> Result.Promise.fold(
         x => Js.String.toUpperCase(x) |> Js.Promise.resolve,
         x => string_of_int(x) |> Js.Promise.resolve,
       )
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual("BOOM")
         |> Js.Promise.resolve
       )
  );
  testPromise("bimap - Ok", () =>
    Result.Promise.pure(42)
    |> Result.Promise.bimap(x => Js.String.toUpperCase(x), x => x + 1)
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(43))
         |> Js.Promise.resolve
       )
  );
  testPromise("bimap - Error", () =>
    Result.Promise.error("boom")
    |> Result.Promise.bimap(x => Js.String.toUpperCase(x), x => x + 1)
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.error("BOOM"))
         |> Js.Promise.resolve
       )
  );
  testPromise("andThen - Ok", () =>
    Result.Promise.pure(42)
    |> Result.Promise.andThen(x => Result.Promise.pure(x + 1))
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(43))
         |> Js.Promise.resolve
       )
  );
  testPromise("andThen - Error", () =>
    Result.Promise.error(42)
    |> Result.Promise.andThen(x => Result.Promise.error(x + 1))
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.error(42))
         |> Js.Promise.resolve
       )
  );
  testPromise("chain - Ok", () =>
    Result.Promise.pure(42)
    |> Result.Promise.chain(x => Result.pure(x + 1))
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(43))
         |> Js.Promise.resolve
       )
  );
  testPromise("unsafeResolve - Ok", () =>
    Result.Promise.pure(42)
    |> Js.Promise.then_(result =>
         Result.Promise.pure(result) |> Result.Promise.unsafeResolve
       )
    |> Js.Promise.then_(actual =>
         Expect.expect(actual)
         |> Expect.toEqual(Result.pure(42))
         |> Js.Promise.resolve
       )
  );
  testPromise("unsafeMapResolve - Ok", () => {
    let actual = 42;
    let expected = 43;
    Result.Promise.pure(actual)
    |> Result.Promise.unsafeMapResolve(x => x + 1)
    |> Js.Promise.then_(result =>
         Expect.expect(result)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve
       );
  });
  testPromise("unsafeChainResolve - Ok", () => {
    let actual = 42;
    let expected = 43;
    Result.Promise.pure(actual)
    |> Result.Promise.unsafeChainResolve(x => Result.pure(x + 1))
    |> Js.Promise.then_(result =>
         Expect.expect(result)
         |> Expect.toEqual(expected)
         |> Js.Promise.resolve
       );
  });
});
