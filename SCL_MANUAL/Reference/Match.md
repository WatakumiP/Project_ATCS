## match
`match()`は、指定された文字列に指定された部分文字列が含まれている場合にtrueを返します。

```scl
match(inString,      // 検索対象の文字列
      subString)     // マッチさせるパターン
```

例:

```scl
if match("Mississippi", "is") then     // trueが返されます
```