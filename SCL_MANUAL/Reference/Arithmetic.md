## 算術演算
数学演算は、SFRや整数変数などのワードサイズの整数値に対して実行できます。

```c
intVal <= intVal [+ | - | * | /] intVal;
```

整数値は、SFR、整数変数、整数定数、またはワードサイズの共有変数になります。

```c
TMR1 <= TMR1 + 1;
intVar := WREG / 5;
sharedVar <= intVar + RCREG * 3 - 1;
```

上記の例では、整数演算が行われています。`intVal`、`TMR1`、`intVar`、`sharedVar`などの変数が、加算、減算、乗算、除算などの算術演算子を使用して操作されています。これらの変数は、SFR（Special Function Register）、整数変数、または共有変数など、様々な形式の整数値を表します。