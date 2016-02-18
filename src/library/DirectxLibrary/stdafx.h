// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。

#define DIRECTINPUT_VERSION 0x0800

// #pragma comment (lib, "d3d9.lib")
// #pragma comment (lib, "d3dx9.lib")
// #pragma comment(lib,"dinput8.lib")
// #pragma comment(lib,"dxguid.lib")
// TODO: プログラムに必要な追加ヘッダーをここで参照してください。

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <mmsystem.h>
#include <dinput.h>	//dinput8.lib dxguid.libのリンクも必要
#include <XInput.h>
