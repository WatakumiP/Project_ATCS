 ## 共有ラベル

SCLでは、プロセッサ上で実行されているソフトウェアから、プログラムメモリの場所に付けられたラベル名を読み書きすることができます。これらのラベルにアクセスするには、構成セクションで共有ラベルを宣言してSCLにそのラベルについて教える必要があります。

```scl
shared label labelName;
```

"main"はよく使われるラベルです。以下に例を示します。

```scl
configuration for "PIC16F877" is

   shared label main;

end configuration;

testbench for "PIC16F877" is

   begin

   process is

      begin

      wait until PC == main;

      report("reached main");

      end process;

   end testbench;
```

この例では、"PIC16F877"の構成で`main`という共有ラベルを宣言し、その後のテストベンチでプロセスが`main`のPCに到達するまで待機し、その後 "reached main" というメッセージを出力しています。