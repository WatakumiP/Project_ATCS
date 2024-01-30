## While ループ

`while`ループは、ループ内の真偽の終了条件がループの開始時に与えられる Loop 文のバリエーションです。

```scl
while booleanExpression loop

   -- SCL文

   exit when booleanExpression;  -- オプション

end loop;
```

真偽式は期待されるものです。以下はいくつかの例です。

```scl
-- 無限ループ

while true loop

   RD1 <= '0';

   wait on RD1;

end loop;


-- PC > 0x2000になるまでループ

while PC <= #16#2000# loop

   PIR3.ADIF <= 1;

   wait 200 us;

end loop;
```

`while`文には独自の真偽の式があるにもかかわらず、ループ内には依然として `exit when` 文を含めることができます。

```scl
-- PIR2.EEIFがクリアされるまでループ

while PIR2.EEIF == 1 loop

   RD1 <= '1';

   wait on RD0;

   exit when PC == 0;   -- デバイスのリセット

end loop;
```

`exit when`文を使うことで、`while`ループ内で特定の条件が満たされた場合にループを脱出することができます。
