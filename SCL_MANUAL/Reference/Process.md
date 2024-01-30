## プロセス

プロセスは、SCLにおける基本的なコード要素です。これは実行されるイベントのシーケンスを表します。

以下は、プロセスの基本的な構文です。

```scl
process is
   begin
      // プロセスのステートメントはここに入ります
   end process;
```

テストベンチには複数のプロセスが含まれることがあります。

```scl
testbench for "PIC32MX360F512L" is
   process is -- 1つ目のプロセス
      begin
      end process;

   process is -- 2つ目のプロセス
      begin
      end process;
end testbench;
```

最後に、プロセスには名前が付けられることがあります。

```scl
processName: process is
   begin
   end process processName;
```

または、代わりに

```scl
processName: is process is
   begin
   end process processName;
```

プロセス名は装飾用であり、ユニークである必要があります。将来のSCLのバージョンでプロセス名が使用される可能性があります。