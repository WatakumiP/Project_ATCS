## if
If ステートメントは、条件に基づいた分岐を提供します。

```scl
if booleanExpression then
   -- SCLステートメント
else   -- オプション
   -- SCLステートメント
end if;
```

ブール式は期待通りです。以下はいくつかの例です。

```scl
-- RD0の反転をRD1にエコーする
wait on RD0;
if RD0 == '1' then
   RD1 <= '0';
else
   RD1 <= '1';
end if;

-- ピン電圧のテスト
if RD0 > 2500 mv then
   RD1 <= '0';
   RD2 <= '0';
end if;

-- SFRフィールドのテスト
if ADCON.ADCS == "00" then
   ADCON.ADON = '1';
end if;

-- ブール変数のテスト
if testBool then
   RD1 <= '0';
   RD2 <= '0';
end if;
```