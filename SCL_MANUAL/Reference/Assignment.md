## 代入
おそらく最も一般的なSCLステートメントの1つは、代入文です。これは、ピン、SFR、SFRフィールド、またはメモリ位置に値を代入するために使用されます。

```scl
RA1 <= '1';                 // ピンRA1を高に設定
AN0 <= 3500 mv;             // ピンAN0を3.5 Vに設定
RA0 <= RA1;                 // ピンRA0をピンRA1の値に設定
ADDRESH <= 128;             // SFR ADDRESHを128に設定
ADDRESH <= 16#80#;          // SFR ADDRESHを0x80に設定
ADDRESH <= B"10000000";     // SFR ADDRESHをバイナリ10000000に設定
ADDRESH <= ADDRESL;         // SFR ADDRESHをADDRESLに設定
PORTA <= intVar;            // SFR PORTAをintVar変数の値に設定
SSPCON1.CKP <= '1';         // フィールドSSPCON1.CKPを1に設定
ADCON0.ADCS <= "10";        // フィールドADCON0.ADCSを2に設定
```

ユーザー変数への代入は異なる構文を使用します。もちろん、ユーザー変数のタイプに依存します。

```scl
intVar  := 123;             // intVarを123に設定
timeVar := 10 ms;           // timeVarを10 msに設定
strVar  := "test";          // strVarを"test"に設定
intVar  := PORTA;           // intVarをSFR PORTAの値に設定
```