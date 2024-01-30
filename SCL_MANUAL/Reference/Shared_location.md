## 共有位置

SCLでは、汎用メモリの読み書きが可能ですが、そのためには構成セクションで共有されたロケーションを宣言する必要があります。

```scl
shared location varName := locationAddress;
```

例を示します。

```scl
configuration for "PIC16F877" is

   shared location loc70 := 16#70#;

end configuration;

testbench for "PIC16F877" is

   begin

   process is

      begin

      wait on loc70;

      if loc70 == 0 then

         loc70 <= 1;

      else

         loc70 <= 0;

      end if;

      end process;

   end testbench;
```

この例では、"PIC16F877"の構成で`loc70`という共有ロケーションを宣言しています。その後のテストベンチのプロセスでは、`loc70`が待機し、その値に基づいてトグル動作を行っています。`loc70`の値が0なら1に、それ以外なら0に切り替わります。