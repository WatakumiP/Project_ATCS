## ブール演算
ブール式は、意思決定を行うさまざまなSCLステートメントタイプ（たとえば、if、loop、whileなど）で使用されます。これらの式は常にブール値（trueまたはfalse）に評価されます。

```scl
boolVar              // ブール変数boolVarがtrueの場合はtrue
RA1 == '1'           // ピンRA1が高い場合はtrue
RA1 <= 3500 mv       // ピンRA1が3.5 V以下の場合はtrue
intVar > 123         // int変数intVarが123より大きい場合はtrue
intVar - 34 < 123    // int変数intVarから34を引いた値が123より小さい場合はtrue
ADCON0.ADCS == "10"  // ADCON0.ADCSが2の場合はtrue
```

論理演算子AND、OR、XORなどは現在のところSCLでサポートされていないことに注意してください。