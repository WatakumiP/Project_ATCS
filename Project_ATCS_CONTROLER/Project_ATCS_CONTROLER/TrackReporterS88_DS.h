/*********************************************************************
 * Railuino - Hacking your Märklin
 *
 * Copyright (C) 2012 Joerg Pleumann
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * LICENSE file for more details.
 */

#include <Arduino.h>


// ===================================================================
// === TrackReporterS88 DS ==============================================
// ===================================================================

/**
 * ---線路状態検知のためのS88バスプロトコルの実装---
 * S88は基本的に長いシフトレジスタで、各ビットがトラック上の1つの接点に対応しています。
 * 各S88ボード上のフリップフロップは、 確実に電車の状態が保存されるようにするため、 
 * 電車が線路を通過したタイミングで接点に問い合わせる必要はありません。
 *	この実装では、最大で512ビットまたは、32機のフルワイド(16bit)のS88ボードを使用できます。
 * なお、S88は推奨するボード数が30機なので、問題はないと言えます。
 */
class TrackReporterS88_DS {

  private:
	// 使用するモジュールの大きさ
	int mSize;

	//直近の線路データの格納位置
	byte mSwitches[32];

  public:

	/**
	* 指定された数のモジュールがアタッチされた新規 TrackReporter を作成します。
	* この値は安全に最大値の32に設定することができますが、 
	* 実際に使用するだけの数値を指定することを推奨します。 
	* この方法はフルワイド(16bit)のモジュールを想定しています。
	* 代わりに8ビットモジュールを使う場合（あるいはその両方）には、  自分で計算する必要があります。
	*/
	TrackReporterS88_DS(int modules);
  
	/**
	* すべての接点の現在の状態を TrackReporter 
	* に読み込み、すべての S88 ボード上のフリップフロップをクリアします。このメソッドを 
	* 定期的に呼び出すことで、最新の値を得ることができます。
	*/
	void refresh();
	void refresh(int inMaxSize);

	//個々のコンタクトの状態を返します。有効なインデックス値は1～512です。
	boolean getValue(int index);

	// コンタクトの状態を返します。有効なインデックス値は0～63です。
	byte getByte(int index);

};
