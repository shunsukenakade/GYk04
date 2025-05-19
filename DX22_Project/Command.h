#pragma once
#include "Input.h"
#include <list>
#include "Texture.h"
#include "Sprite.h"
class ActionBase;

class Command
{
public:

	// 入力状態
	struct COMMAND {
		unsigned int direction;		// 方向入力（テンキー表記）
		bool LP, MP, HP;			// 弱中強パンチ
		bool LK, MK, HK;			// 弱中強キック

		bool operator==(COMMAND val) {
			return (direction == val.direction &&
				LP == val.LP && MP == val.MP && HP == val.HP &&
				LK == val.LK && MK == val.MK && HK == val.HK);
		}

		// コマンド判定用
		// valの入力を満たしているか
		bool Check(COMMAND val) {
			if (val.direction != 0 &&		// directionの0は方向の指定がないことを表す
				direction != val.direction)
			{ return false; }
			if (!LP == val.LP) { return false; }
			if (!MP == val.MP) { return false; }
			if (!HP == val.HP) { return false; }
			if (!LK == val.LK) { return false; }
			if (!MK == val.MK) { return false; }
			if (!HK == val.HK) { return false; }

			return true;
		}
	} ;

	// 入力ログ用のデータ構造体
	struct INPUT_DATA {
		COMMAND command;
		unsigned int frame;	// 継続フレーム
	};

	// キーコンフィグ(キーボード)
	struct  KEY_CONFIG {
		BYTE UP, DOWN, LEFT, RIGHT;	// 上下左右
		BYTE LP, MP, HP;			// 弱中強パンチ
		BYTE LK, MK, HK;			// 弱中強キック
	};

public:
	Command();
	~Command();
	void Update();
	void Draw();

	void SetAction(ActionBase* action) { m_actionList.push_back(action); }

private:
	std::list<INPUT_DATA> m_inputLog;
	KEY_CONFIG m_keyConfig;

	// 技のリスト
	std::list<ActionBase*> m_actionList;

	// ----- UI -----
	Texture* m_pArrowTex;	// 矢印テクスチャ
};

