## Wait

`wait`文は、SCLに対して、含まれるプロセスからの命令の実行を停止するよう指示します。

SCLはプロセス内の文を実行し、`wait`文に遭遇するまで続けます。プロセスの終端に到達した場合、SCLは単純にプロセスの最初に戻り、再開します。そのため、すべてのプロセスには少なくとも1つの`wait`文が必要です。それがないと、プロセスは無限ループを行い、シミュレータを停止させます。幸運なことに、SCLパーサは`wait`文のないプロセスを検出し、次の警告を発行してロードを拒否します。

```
SIM004: Failed to parse SCL SCL022: Process contains neither a wait statement nor a sensitivity list line(#)
```

`wait`文には4つの形式があります。

- `wait;`  // 無修飾
- `wait on sensitivity;`  // センシティビティ`wait`
- `wait until condition;`  // 条件`wait`
- `wait for timeout;`  // タイムアウト`wait`

**無修飾の`wait`**

最も単純な`wait`は引数なしの無修飾のものです。これはSCLに対して、プロセスの文の実行を停止し、プロセスが完了していることを伝えます。

```scl
process is
   begin
      wait;  -- プロセスを即座に終了させる！
   end process;
```

**センシティビティ`wait`**

センシティビティ`wait`文は値の変更を待ちます。いくつかの種類の値があります。

```scl
wait on RD1;          -- RD1ピンの変更を待つ
wait on userVar;      -- ユーザー変数の変更を待つ
wait on STATUS;       -- STATUS SFRの変更を待つ
wait on PORTD.RD0;    -- PORTDのRD0ビットの変更を待つ
```

**条件`wait`**

条件`wait`文は、式が`true`になるのを待ちます。

```scl
wait until PORTA == 128;          -- SFR PORTAが128（0x80）に等しくなるまで待つ
wait until RD1 == '1';            -- RD1ピンがHighになるまで待つ
wait until ADCON.ADON == '1';     -- SFR ADCONのADONフィールドが1になるまで待つ
wait until PC == 4;               -- PCが4になるまで待つ
```

条件`wait`は、実際にはブール式内のレジスタやピンの値の変更を待ってからブール式をテストします。これは、プロセス内に他の`wait`文がない場合に発生する無限ループプロセスを防ぐためです。例えば：

```scl
process is;
   begin
   wait until RC6 == '1';   -- もしSCLがここでRC6の値の変更を待っていないなら...
   report("RC6 was '1'");   -- ...このプロセスはこの報告文を無限に実行します！
   end process;
```

このように、ブール式がすでに`true`の場合、条件`wait`文が実行されるとプロセスが「停止」し、レジスタやピンの変更を待機します。

```scl
process is;
   begin
   RC6 <= '1';             -- 次のブール式がtrueになるようにする
   wait until RC6 == '1';  -- ...プロセスはまずRC6の値の変更を待ってから実行されます
   report("RC6 was '1'");  -- ...この行は実行されません
   end process;
```

これを回避するには、`wait`の前に`if`文を使用します。

```scl
process is;
   begin
   if RC6 != '1' then          -- このプロセスは停止せず、無限ループしません
      wait until RC6 == '1';
   end if;
   report("RC6 was '1'");
   end process;
```

**タイムアウト`wait`**

タイムアウト`wait`文は、指定された時間だけ待ちます。

```scl
wait for 10 ic;        -- 10命令サイクル待つ
wait for 10 ms;        -- 10ミリ秒待つ
```

タイムアウト`wait`は、センシティビティまたは条件`wait`と組み合わせることが