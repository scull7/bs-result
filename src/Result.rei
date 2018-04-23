type result('bad, 'good) =
  | Error('bad)
  | Ok('good);

let of_: 'a => result('b, 'a);

let pure: 'a => result('b, 'a);

let error: 'a => result('a, 'b);

let isOk: result('a, 'b) => bool;

let isError: result('a, 'b) => bool;

let ap: ('a, result('b, 'a => 'c)) => result('b, 'c);

let map: ('a => 'b, result('c, 'a)) => result('c, 'b);

let fold: ('a => 'b, 'c => 'b, result('a, 'c)) => 'b;

let bimap: ('a => 'b, 'c => 'd, result('a, 'c)) => result('b, 'd);

let toOption: result('a, 'b) => option('b);

let swap: result('a, 'b) => result('b, 'a);

let chain: ('a => result('b, 'c), result('b, 'a)) => result('b, 'c);

let flatMap: ('a => result('b, 'c), result('b, 'a)) => result('b, 'c);

let forAll: ('a => bool, result('b, 'a)) => bool;

let forEach: ('a => unit, result('b, 'a)) => unit;

let getOrElse: ('a, result('b, 'a)) => 'a;

let getOrElseThunk: ('a => 'b, result('a, 'b)) => 'b;

let unsafeGet: result(exn, 'a) => 'a;

module Promise: {
  let of_: 'a => Js.Promise.t(result('b, 'a));
  let pure: 'a => Js.Promise.t(result('b, 'a));
  let error: 'a => Js.Promise.t(result('a, 'b));
  let map:
    ('a => 'b, Js.Promise.t(result('c, 'a))) =>
    Js.Promise.t(result('c, 'b));
  let fold:
    (
      'a => Js.Promise.t('b),
      'c => Js.Promise.t('b),
      Js.Promise.t(result('a, 'c))
    ) =>
    Js.Promise.t('b);
  let bimap:
    ('a => 'b, 'c => 'd, Js.Promise.t(result('a, 'c))) =>
    Js.Promise.t(result('b, 'd));
  let chain:
    ('a => result('b, 'c), Js.Promise.t(result('b, 'a))) =>
    Js.Promise.t(result('b, 'c));
};
