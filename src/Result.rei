let return: 'a => Belt.Result.t('a, 'b);

let error: 'b => Belt.Result.t('a, 'b);

let isOk: Belt.Result.t('a, 'b) => bool;

let isError: Belt.Result.t('a, 'b) => bool;

let ap: ('a, Belt.Result.t('a => 'c, 'b)) => Belt.Result.t('c, 'b);

let map: ('a => 'b, Belt.Result.t('a, 'c)) => Belt.Result.t('b, 'c);

let map2:
  (('a, 'b) => 'c, Belt.Result.t('a, 'd), Belt.Result.t('b, 'd)) =>
  Belt.Result.t('c, 'd);

let map3:
  (
    ('a, 'b, 'c) => 'd,
    Belt.Result.t('a, 'e),
    Belt.Result.t('b, 'e),
    Belt.Result.t('c, 'e)
  ) =>
  Belt.Result.t('d, 'e);

let fold: ('a => 'c, 'b => 'c, Belt.Result.t('a, 'b)) => 'c;

let bimap:
  ('a => 'c, 'b => 'd, Belt.Result.t('a, 'b)) => Belt.Result.t('c, 'd);

let toOption: Belt.Result.t('a, 'b) => option('a);

let fromOption: (unit => 'b, option('a)) => Belt.Result.t('a, 'b);

let swap: Belt.Result.t('a, 'b) => Belt.Result.t('b, 'a);

let flatMap:
  ('a => Belt.Result.t('b, 'c), Belt.Result.t('a, 'c)) =>
  Belt.Result.t('b, 'c);

let flatMap2:
  (
    ('a, 'b) => Belt.Result.t('c, 'd),
    Belt.Result.t('a, 'd),
    Belt.Result.t('b, 'd)
  ) =>
  Belt.Result.t('c, 'd);

let flatMap3:
  (
    ('a, 'b, 'c) => Belt.Result.t('d, 'e),
    Belt.Result.t('a, 'e),
    Belt.Result.t('b, 'e),
    Belt.Result.t('c, 'e)
  ) =>
  Belt.Result.t('d, 'e);

let forAll: ('a => bool, Belt.Result.t('a, 'b)) => bool;

let forEach: ('a => unit, Belt.Result.t('a, 'b)) => unit;

let getOrElse: ('a, Belt.Result.t('a, 'b)) => 'a;

let getOrElseThunk: ('b => 'a, Belt.Result.t('a, 'b)) => 'a;

let unsafeGet: Belt.Result.t('a, exn) => 'a;

module Promise: {
  let return: 'a => Js.Promise.t(Belt.Result.t('a, 'b));
  let error: 'a => Js.Promise.t(Belt.Result.t('b, 'a));
  let isOk: Js.Promise.t(Belt.Result.t('a, 'b)) => Js.Promise.t(bool);
  let isError: Js.Promise.t(Belt.Result.t('a, 'b)) => Js.Promise.t(bool);
  let ap:
    ('a, Belt.Result.t('a => 'c, 'b)) => Js.Promise.t(Belt.Result.t('c, 'b));
  let map:
    ('a => 'b, Js.Promise.t(Belt.Result.t('a, 'c))) =>
    Js.Promise.t(Belt.Result.t('b, 'c));
  let fold:
    (
      'a => Js.Promise.t('c),
      'b => Js.Promise.t('c),
      Js.Promise.t(Belt.Result.t('a, 'b))
    ) =>
    Js.Promise.t('c);
  let bimap:
    ('a => 'c, 'b => 'd, Js.Promise.t(Belt.Result.t('a, 'b))) =>
    Js.Promise.t(Belt.Result.t('c, 'd));
  let andThen:
    (
      'a => Js.Promise.t(Belt.Result.t('b, 'c)),
      Js.Promise.t(Belt.Result.t('a, 'c))
    ) =>
    Js.Promise.t(Belt.Result.t('b, 'c));
  let flatMap:
    ('a => Belt.Result.t('b, 'c), Js.Promise.t(Belt.Result.t('a, 'c))) =>
    Js.Promise.t(Belt.Result.t('b, 'c));
  let unsafeResolve:
    Js.Promise.t(Belt.Result.t('a, exn)) => Js.Promise.t('a);
  let unsafeMapResolve:
    ('a => 'b, Js.Promise.t(Belt.Result.t('a, exn))) => Js.Promise.t('b);
  let unsafeFlatMapResolve:
    ('a => Belt.Result.t('b, exn), Js.Promise.t(Belt.Result.t('a, exn))) =>
    Js.Promise.t('b);
};
