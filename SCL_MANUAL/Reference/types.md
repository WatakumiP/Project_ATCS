## Types

SCLでは、その後に変数を定義するために使用できる型を定義することができます。いくつかのタイプの定義があります。

列挙型

列挙型の定義は、その型が許容する特定の値を示します。

```scl
type color is (red, blue, green);
```

範囲

範囲定義は、その型が許容する値の範囲を示します。

```scl
type Byte is range 0 to #16#FF#;
```

範囲定義には、その型に関連付けられた単位のオプション定義が含まれることがあります。

```scl
type voltage is range -9223372036854775807 to 9223372036854775807
   units mV;
      V  = 1000 mV;
      kV = 1000 V;
   end units;
```

配列

以下は、配列型の例です。

```scl
type bit_vector is array (integer range <>) of bit;
```

これらの型の定義を使用して、SCLで変数をより具体的に定義できます。