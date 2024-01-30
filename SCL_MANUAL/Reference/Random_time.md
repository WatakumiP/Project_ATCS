## random_time

`random_time()`はランダムな時間値を生成します。

```scl
random_time(
   lower,       -- ランダム値の下限
   upper,       -- ランダム値の上限
   units,       -- 望ましい時間値の単位（ns、ms、sなど）
   seed1,       -- ランダムジェネレータのシード＃1
   seed2,       -- ランダムジェネレータのシード＃2
   result       -- 結果の変数
);
```

例として、1から100ミリ秒のランダムな待機を生成するコードを示します。

```scl
-- 1から100ミリ秒のランダムな待機
variable lower    : integer := 1;
variable upper    : integer := 100;
variable units    : string  := "ms";
variable seed1    : integer := 13457;
variable seed2    : integer := 24563;
variable randTime : time;

random_time(lower, upper, units, seed1, seed2, randTime);

wait for randTime;
```

この例では、`random_time`関数を使用してランダムな時間を生成し、その時間だけ待機しています。