## 定数
SCLでは、コード内で定数を表現するための多くの方法があります。

```scl
intVar    = 1;              // 10進数1
intVar    = B"10";          // 2進数10
intVar    = 8#70#;          // 8進数70
intVar    = 10#10#;         // 10進数10
intVar    = 16#FFFFFFFF#;   // 16進数FFFFFFFF
intVar    = 16#FFFF_FFFF#;  // '_'は無視されます
intVar    = 1e9;            // 科学的記法での10進数10億
charVar   = 'a';            // 文字'a'
stringVar = "SCL";          // 文字列の例
boolVar   = true;           // 列挙型の例
pin       = '1';            // ピンをHighに設定
pin       = '0';            // ピンをLowに設定
sfr.field = '0';            // 単一ビットのSFRフィールド (0/1)
sfr.field = "101";          // マルチビットのSFRフィールド (バイナリ文字列)
```

SCLは10進数または浮動小数点型をサポートしていないことに注意してください。これはいくつか奇妙な状況を引き起こす可能性があります。たとえば、VDDを3.5 Vに設定するには次のようにします。

```scl
VDD = 3500 mv;
```