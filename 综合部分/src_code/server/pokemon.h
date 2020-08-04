#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

// 调试参数
#define DEBUG 0
#define RACE_NUM 4

// 四个基础种族
enum PokemonRace { Pow, Shi, Def, Spe };

// 成长曲线
struct growth_curve
{
	int up_atk;
	int up_dfs;
	int up_hp;
	int up_speed;
};



class Pokemon;//声明

class PokemonBase
{
public:
	PokemonBase(PokemonRace race);
	virtual void attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf)const{}
	virtual bool dodge(int skill_accuraccy,int attack_speed, int opponent_speed, string &sendbuf) const;

	// getter
	string racename() const { return _racename; }
	PokemonRace race() const { return _race; }
	int baseAtk() const { return _baseAtk; }
	int baseDfs() const { return _baseDfs; }
	int baseHp() const { return _baseHp; }
	int baseSpeed() const { return _baseSpeed; }
	string skillname(int n) const;
	string skilldesc(int n) const;
	int pp(int n) const{ return _pp[n]; }
	growth_curve baseCurve() const { return _baseCurve; }
	growth_curve raceCurve() const { return _raceCurve; }


	void changeRacename(const string & racename)
	{
		_racename = racename;
	}

protected:
	string _racename;
	PokemonRace _race;
	
	int _baseHp;
	int _baseAtk;
	int _baseDfs;
	int _baseSpeed;

	string _skillNames[4];
	string _skillDesc[4];

	//baseCurve是每个小精灵的基本成长曲线
	//raceCurve根据种族不同，采用随机数的方式
	growth_curve _baseCurve,_raceCurve;

	// 技能使用次数，第一项默认为INT_MAX；
	int _pp[4];
	   
};



// 每个小精灵动态的属性
class Pokemon
{
public:
	Pokemon(int raceIndex,const string &name = "");
	Pokemon(int pokemonid,int raceIndex, const string &name, int atk, int def, int HP, int speed, int lv, int ep);
	// 普通状态下的getter和setter
	// const成员函数
	string name()const { return _name; }
	int race()const { return _raceIndex;}
	int atk() const { return _atk; }
	int dfs() const { return _dfs; }
	int hp() const { return _hp; }
	int speed() const { return _speed; }
	int ep()const { return _ep; }
	int lv()const { return _lv; }
	int pokemonid()const { return _pokemonid; }
	void setAtk(int atk);
	void setDfs(int dfs);
	void setHp(int hp);
	void setSpeed(int speed);
	void addEp(int ep);
	// 和种族有关的
	string racename()const { return races[_raceIndex]->racename(); }
	string skillname(int skillIndex) const { return races[_raceIndex]->skillname(skillIndex); }
	string skilldesc(int skillIndex) const { return races[_raceIndex]->skilldesc(skillIndex); }

	// 战斗状态下的getter
	int battleAtk() const { return _battleAtk; }
	int battleDfs() const { return _battleDfs; }
	int battleHp() const { return _battleHp; }
	int battleSpeed() const { return _battleSpeed; }
	int battlePp(int i)const { return _battlepp[i]; }
	// 战斗开始前恢复所有属性
	void restoreAll();

	// 攻击,返回伤害值
	void attack(Pokemon& opponent, string &sendbuf,int autofight);

	// 遭受伤害
	void takeDamage(int damage);

	// 吸收经验
	void gainEp(int ep);


private:
	static const PokemonBase *races[RACE_NUM];
	int _raceIndex;
	string _name;
	int _pokemonid;
	int _ep;
	int _lv;
	// 分为正常的属性和战斗状态属性

	// 正常属性
	int _atk;
	int _dfs;
	int _hp;
	int _speed;

	// 战斗状态属性
	int _battleAtk;
	int _battleDfs;
	int _battleHp;
	int _battleSpeed;
	int _battlepp[4];
};

template<int N>
class Race :public PokemonBase
{
public:
	Race();
	void attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const;
};

