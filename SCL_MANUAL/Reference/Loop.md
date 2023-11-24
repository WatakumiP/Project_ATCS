## loop
Loop ステートメントは、ループ機能を提供します。

```scl
loop
   -- SCLステートメント
   exit when booleanExpression     -- オプション
end loop;
```


ブール式は期待通りです。以下はいくつかの例です。

```scl
-- 無限ループ（exit whenなし）
loop
   RD1 <= '0';
   wait on RD1;
end loop;

-- PCがfooラベルになるまでクロック
loop
   RD0 <= '0';
   wait 4 ic;
   RD0 <= '1';
   wait 4 ic;
   exit when PC == foo;
end loop;

-- 修飾なしの終了（これは無理やりですが！）
loop
   AN1 <= 3500 mv;
   exit;             -- 無条件の終了
end loop;
```

注意点として、ループには複数の `exit when` 条件がある可能性があることです。

```scl
-- 複数の終了条件
loop
   wait on RD1;
   RD0 <= '0';
   exit when STATUS.Z == 0;
   exit when RD2 == '0';
end loop;
```