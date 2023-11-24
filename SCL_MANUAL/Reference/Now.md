## now
`now()`は現在のシミュレーションサイクルを返します。

```scl
variable timeMark : cycle;
timeMark := now();
```
例：

```scl
if (now() > timeMark + 20 ic) then
    -- 現在の時刻がtimeMarkよりも少なくとも20サイクル遅れている場合にこれを行わないでください
    -- (20 ic後になるまで実行しない)
```