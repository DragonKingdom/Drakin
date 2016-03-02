// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include <vector>

// Libraryが提供するヘッダファイル
#include "3DModel.h"
#include "3DVertex.h"
#include "anim3DModel.h"
#include "animation.h"
#include "animVertex.h"
#include "BillBoard.h"
#include "camera.h"
#include "DirectxLibrary.h"
#include "Font.h"
#include "graphicsDevice.h"
#include "Input.h"
#include "Model.h"
#include "texture.h"
#include "vertex.h"
#include "XAudio.h"

// ゲーム側共通ヘッダファイル
#include "CommonDeclaration.h"
