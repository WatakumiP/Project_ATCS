# SFR（Special Function Register）
SCLは、現在のデバイス上の各SFRに対応する変数を自動的に作成します。変数名はSFRと同じになります。その後、SFR変数は割り当て、テストなどが可能です。

```vhdl
ADC1BUF0 <= #16#15F#;
if STATUS = '0' then
```

SCL内のSFRは、SFRフィールドがレコードフィールドになるようにモデル化されます。これにより、ユーザーは手動でマスクやシフトを行わずに、名前でフィールドに参照することができます。

```vhdl
PIR3.ADIF <= '1';
if ADCON0.ADCS = "10" then
```

一部のデバイス（例：AVR、SAM）では、異なるペリフェラルに対して同じレジスタ名が複数使用されることがあります。この場合、SCLはSFR名の前にペリフェラル名を付け加えます。

```vhdl
ADC0_CTRLA.EN <= '1';
if TCC0_CTRLA = "5" then
```