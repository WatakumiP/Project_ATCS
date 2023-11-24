`file_open`
`file_open()`は、後続の読み取りのためにファイルを開きます。

```scl
file_open(fileOpenStatus,     // file_open_status変数
          fileVar,            // ファイル変数
          fileName,           // ファイル名、String変数
          fileMode)           // ファイルモード（read_modeである必要があります）
```

`fileOpenStatus`は`file_open_status`型の変数で、ファイルオープン操作のステータス結果を受け取ります。その値は以下の通りです：
```
    mode_error                  // もはや使用されません
    name_error                  // ファイルが見つかりません
    open_ok                     // ファイルが正常に開かれました
    status_error                // ファイルがすでに開かれています
```

`fileVar`は`file`型の変数で、ファイルの状態を追跡する内部変数です。`endfile`や`file_close`などの他のファイルメソッドで使用されます。

`fileName`はファイル名を含む文字列です。完全な絶対パスを含んでいる必要があります。

`fileMode`は`file_mode`型の定数ですが、この時点では値は"read_mode"である必要があります。