#pragma once


//
// Standard-library-based metaprogramming utiltities
//

// EnableIf
template<bool B, typename T = void>
struct EnableIfStruct {};
template<typename T>
struct EnableIfStruct<true, T> {
  using Type = T;
};
template<bool B, typename T = void>
using EnableIf = typename EnableIfStruct<B, T>::Type;

// isAggregate
template<typename T>
constexpr auto isAggregate = __is_aggregate(T);

// isLvalueReference
template<typename T>
constexpr auto isLvalueReference = false;
template<typename T>
constexpr auto isLvalueReference<T &> = true;

// RemoveReference
template<typename T>
struct RemoveReferenceStruct {
  using Type = T;
};
template<typename T>
struct RemoveReferenceStruct<T &> {
  using Type = T;
};
template<typename T>
struct RemoveReferenceStruct<T &&> {
  using Type = T;
};
template<typename T>
using RemoveReference = typename RemoveReferenceStruct<T>::Type;

// RemoveCV
template<typename T>
struct RemoveCVStruct {
  using Type = T;
};
template<typename T>
struct RemoveCVStruct<const T> {
  using Type = T;
};
template<typename T>
struct RemoveCVStruct<volatile T> {
  using Type = T;
};
template<typename T>
struct RemoveCVStruct<const volatile T> {
  using Type = T;
};
template<typename T>
using RemoveCV = typename RemoveCVStruct<T>::Type;

// forward
template<typename T>
constexpr T &&forward(RemoveReference<T> &t) {
  return static_cast<T &&>(t);
}
template<typename T>
constexpr T &&forward(RemoveReference<T> &&t) {
  static_assert(!isLvalueReference<T>);
  return static_cast<T &&>(t);
}

// IndexSequence
template<int... Index>
struct IndexSequence {
  static constexpr int size() noexcept {
    return sizeof...(Index);
  }
};

// Void
template<typename...>
using Void = void;

// declval
template<typename T, typename U = T &&>
U declval(int);
template<typename T>
T declval(long);
template<typename T>
auto declval() -> decltype(declval<T>(0)) {
  return declval<T>(0);
}


//
// Props
//

template<typename Value_, typename Internal>
struct Prop {
  template<typename Value2_ = Value_, EnableIf<!isAggregate<Value2_>, int> = 0, typename... Args>
  Prop(Args &&...args) // NOLINT(google-explicit-constructor)
      : value(forward<Args>(args)...) {
  }

  template<typename Value2_ = Value_, EnableIf<isAggregate<Value2_>, int> = 0, typename... Args>
  Prop(Args &&...args) // NOLINT(google-explicit-constructor)
      : value { forward<Args>(args)... } {
  }

  Value_ &operator()() {
    return value;
  }

  const Value_ &operator()() const {
    return value;
  }

  static constexpr const char *name = Internal::name;

  using Value = Value_;

private:
  Value_ value;
};

#define PROP(type, name_, ...) PROP_NAMED(#name_, type, name_, __VA_ARGS__)
#define PROP_NAMED(nameStr, type, name_, ...)                                                      \
private:                                                                                           \
  struct INTERNAL_##name_ {                                                                        \
    static constexpr const char *name = nameStr;                                                   \
  };                                                                                               \
                                                                                                   \
public:                                                                                            \
  Prop<PROP_PARENS_1(PROP_PARENS_3 type), INTERNAL_##name_> name_
#define PROP_PARENS_1(...) PROP_PARENS_2(__VA_ARGS__)
#define PROP_PARENS_2(...) NO##__VA_ARGS__
#define PROP_PARENS_3(...) PROP_PARENS_3 __VA_ARGS__
#define NOPROP_PARENS_3

struct CanConvertToAnything {
  template<typename Type>
  operator Type() const; // NOLINT(google-explicit-constructor)
};

template<typename Aggregate, typename Base = IndexSequence<>, typename = void>
struct countReflectableFieldsImpl : Base {};

template<typename Aggregate, int... Indices>
struct countReflectableFieldsImpl<Aggregate, IndexSequence<Indices...>,
    Void<decltype(Aggregate { (static_cast<void>(Indices), declval<CanConvertToAnything>())...,
        declval<CanConvertToAnything>() })>>
    : countReflectableFieldsImpl<Aggregate, IndexSequence<Indices..., sizeof...(Indices)>> {};

template<typename T>
constexpr int countReflectableFields() {
  return countReflectableFieldsImpl<RemoveCV<RemoveReference<T>>>().size();
}

template<typename T>
inline constexpr auto isProp = false;
template<typename... Params>
inline constexpr auto isProp<Prop<Params...>> = true;
template<typename... Params>
inline constexpr auto isProp<Prop<Params...> &> = true;
template<typename... Params>
inline constexpr auto isProp<const Prop<Params...> &> = true;

template<typename T, typename F>
void forEachProp(T &val, F &&func) {
  const auto C = [&](auto &field) {
    if constexpr (isProp<decltype(field)>) {
      func(field);
    }
  };
  constexpr auto n = countReflectableFields<T>();
  static_assert(n <= 24, "forEachProp: only up to 24 fields supported");
  if constexpr (n == 1) {
    auto &[a] = val;
    (C(a));
  } else if constexpr (n == 2) {
    auto &[a, b] = val;
    (C(a), C(b));
  } else if constexpr (n == 3) {
    auto &[a, b, c] = val;
    (C(a), C(b), C(c));
  } else if constexpr (n == 4) {
    auto &[a, b, c, d] = val;
    (C(a), C(b), C(c), C(d));
  } else if constexpr (n == 5) {
    auto &[a, b, c, d, e] = val;
    (C(a), C(b), C(c), C(d), C(e));
  } else if constexpr (n == 6) {
    auto &[a, b, c, d, e, f] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f));
  } else if constexpr (n == 7) {
    auto &[a, b, c, d, e, f, g] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g));
  } else if constexpr (n == 8) {
    auto &[a, b, c, d, e, f, g, h] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h));
  } else if constexpr (n == 9) {
    auto &[a, b, c, d, e, f, g, h, i] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i));
  } else if constexpr (n == 10) {
    auto &[a, b, c, d, e, f, g, h, i, j] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j));
  } else if constexpr (n == 11) {
    auto &[a, b, c, d, e, f, g, h, i, j, k] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k));
  } else if constexpr (n == 12) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l));
  } else if constexpr (n == 13) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m));
  } else if constexpr (n == 14) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n));
  } else if constexpr (n == 15) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o));
  } else if constexpr (n == 16) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o),
        C(p));
  } else if constexpr (n == 17) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q));
  } else if constexpr (n == 18) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r));
  } else if constexpr (n == 19) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r), C(s));
  } else if constexpr (n == 20) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r), C(s), C(t));
  } else if constexpr (n == 21) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r), C(s), C(t), C(u));
  } else if constexpr (n == 22) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r), C(s), C(t), C(u), C(v));
  } else if constexpr (n == 23) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r), C(s), C(t), C(u), C(v), C(w));
  } else if constexpr (n == 24) {
    auto &[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x] = val;
    (C(a), C(b), C(c), C(d), C(e), C(f), C(g), C(h), C(i), C(j), C(k), C(l), C(m), C(n), C(o), C(p),
        C(q), C(r), C(s), C(t), C(u), C(v), C(w), C(x));
  }
}
