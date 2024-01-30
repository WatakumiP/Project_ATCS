## 共有変数

SCLは、プロセッサ上で実行されているソフトウェアが変数を名前で読み書きできるようにします。これらの変数にアクセスするには、構成セクションで共有変数を宣言してSCLにその変数について教える必要があります。

```scl
shared variable varName;
```

現時点では、共有変数はグローバルかつ静的である必要があります。

以下は例です。

```scl
configuration for "PIC16F877" is

   shared variable stateVar;

end configuration;

testbench for "PIC16F877" is

   begin

   process is

      begin

         if stateVar == 0 then

            RD0 <= '1';

         else

            RD1 <= '0';

         end if;

      end process;

   end testbench;
```

この例では、"PIC16F877"デバイスの構成で`stateVar`という共有変数が宣言されています。その後のテストベンチのプロセスでは、`stateVar`の値に基づいて条件に応じてRD0およびRD1への代入が制御されています。