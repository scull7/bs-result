/**
   * # Result.Promise
   *
   * Integration with the [Js.Promise][js-promise] module.
   *
   * [js-promise]: https://bucklescript.github.io/bucklescript/api/Js.Promise.html
   */;
let return: 'a => Js.Promise.t(Belt.Result.t('a, 'b));
let error: 'a => Js.Promise.t(Belt.Result.t('b, 'a));
let isOk: Js.Promise.t(Belt.Result.t('a, 'b)) => Js.Promise.t(bool);
let isError: Js.Promise.t(Belt.Result.t('a, 'b)) => Js.Promise.t(bool);
let ap:
  (
    Js.Promise.t(Belt.Result.t('a, 'b)),
    Js.Promise.t(Belt.Result.t('a => 'c, 'b))
  ) =>
  Js.Promise.t(Belt.Result.t('c, 'b));
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
let unsafeResolve: Js.Promise.t(Belt.Result.t('a, exn)) => Js.Promise.t('a);
let unsafeMapResolve:
  ('a => 'b, Js.Promise.t(Belt.Result.t('a, exn))) => Js.Promise.t('b);
let unsafeFlatMapResolve:
  ('a => Belt.Result.t('b, exn), Js.Promise.t(Belt.Result.t('a, exn))) =>
  Js.Promise.t('b);
