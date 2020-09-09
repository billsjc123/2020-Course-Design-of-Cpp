#include "pokemon.h"

const PokemonBase *Pokemon::races[4] = { new Race<0>(),new Race<1>(), new Race<2>(), new Race<3>() };


// 学习技能等级
int learn_level[4] = { 0,0,6,10 };

int random(int n)
{
	return rand() % (n+1);
}

int bi_random(int n)
{
	if(rand()%2==0)
		return -1*rand() % (n + 1);
	else
		return rand() % (n + 1);
}

int damageFunction(int atk, int dfs,int attacker_lv,int skillpower)
{
	// 宠物小精灵伤害公式（攻击方等级 × 2 ÷ 5 + 2） × 技能威力 × 攻击方攻击力 ÷ 防御方防御力 ÷ 50 + 2
	// 
	int damage = (attacker_lv + 2)*skillpower*atk / dfs / 10 + 2;
	return damage;
}

PokemonBase::PokemonBase(PokemonRace race)
{
	// 设定基础属性
	
	_baseAtk = 10;
	_baseDfs = 10;
	_baseHp = 100;
	_baseSpeed = 20;

	_race = race;

	_baseCurve.up_atk = 5;
	_baseCurve.up_dfs = 5;
	_baseCurve.up_hp = 50;
	_baseCurve.up_speed = 10;

	// 每个种类的基础属性有所不同
	switch (race)
	{
	case Pow:
		_baseAtk += 5;
		break;
	case Shi:
		_baseHp += 50;
		break;
	case Def:
		_baseDfs += 5;
		break;
	case Spe:
		_baseSpeed += 5;
		break;
	default:
		break;
	}
}

string PokemonBase::skillname(int n) const
{
	if (n >= 0 && n <= 3)
	{
		return _skillNames[n];
	}
	else return "";
}

string PokemonBase::skilldesc(int n) const
{
	if (n >= 0 && n <= 3)
	{
		return _skillDesc[n];
	}
	else return "";
}

// 闪避判定
bool PokemonBase::dodge(int skill_accuraccy ,int attack_speed, int opponent_speed, string &sendbuf)const
{
	// A = B * C / D
	//B由招式的命中决定、C由攻击方速度决定、D由防御方速度决定
	//B根据招式决定，招式命中率越高数值越大，最大为255,传入参数为百分比
	//产生一个1~255之间的随机数，该随机数小于A时则为命中，否则为闪避
	int rand_int = rand() % 255 + 1;
	int B;
	switch (skill_accuraccy)
	{
	case 100:
		B = 255;
		break;
	case 95:
		B = 242;
		break;
	case 90:
		B = 229;
		break;
	case 85:
		B = 216;
		break;
	case 80:
		B = 204;
		break;
	case 75:
		B = 191;
		break;
	case 70:
		B = 78;
		break;
	default:
		break;
	}
	int A = B* attack_speed / opponent_speed;

	if (rand_int >= A)
	{
		cout << "这招居然被闪避了！" << endl;
		sendbuf += "1 0\n";
		return true;
	}
	else
	{
		sendbuf += "0 0\n";
		return false;
	}
}

// 火爆猴——力量型
template<>
Race<0>::Race() :PokemonBase(Pow)
{
	changeRacename("Primeape");
	_skillNames[0] = "挠";
	_skillDesc[0] = "Normal attack with low damage";
	_skillNames[1] = "空手道切";
	_skillDesc[1] = "Normal attack with high damage";
	_skillNames[2] = "过肩摔";
	_skillDesc[2] = "Cause damage and decrease enemy's dfs";
	_skillNames[3] = "地球投";
	_skillDesc[3] = "Cause twice damage of its own atk";
	_pp[0] = INT_MAX;
	_pp[1] = 10;
	_pp[2] = 5;
	_pp[3] = 3;

	//种族成长曲线
	_raceCurve.up_atk = 15;
	_raceCurve.up_dfs = 5;
	_raceCurve.up_hp = 20;
	_raceCurve.up_speed = 5;
	
}

// 火爆猴技能
template<>
void Race<0>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex ,string& sendbuf) const
{
	cout << attacker.name() << "使用了:" <<  attacker.skillname(skillIndex)<<"!\n" << endl;
	
	int atk, dfs, damage,skillPower,lv;

	// 全都是改变对方的
	switch (skillIndex)
	{
	case 0:

		if (dodge(85,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
		{
			return;
		}

		// 目前不考虑暴击
		// 暴击直接在dodge里面置为0

		skillPower = rand() % attacker.battleAtk()*0.2+ attacker.battleAtk()*0.6;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs,lv,skillPower);
		opponent.takeDamage(damage);
		break;
	case 1:
		if (dodge(90,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
		{
			return;
		}
		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.8;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.takeDamage(damage);
		break;
	case 2:
		if (dodge(90,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
		{
			return;
		}
		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.8;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.setDfs(-5);
		opponent.takeDamage(damage);
		break;
	case 3:
		if (dodge(90,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
		{
			return;
		}
		skillPower = attacker.battleAtk()*2;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.takeDamage(damage);
		break;
	default:
		break;
	}

	// self 
	sendbuf += to_string(attacker.pokemonid()) + ' ' + attacker.name() + ' ' + to_string(attacker.race()) + ' ';
	sendbuf += to_string(attacker.battleAtk()) + ' ';
	sendbuf += to_string(attacker.battleDfs()) + ' ';
	sendbuf += to_string(attacker.battleHp()) + ' ';
	sendbuf += to_string(attacker.battleSpeed()) + ' ';
	sendbuf += to_string(attacker.lv()) + ' ' + to_string(attacker.hp())+' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(attacker.battlePp(i)) + ' ';
	}
	// opponent 
	sendbuf += '\n' + to_string(opponent.pokemonid()) + ' ' +
		opponent.name() + ' ' + to_string(opponent.race()) + ' ';
	sendbuf += to_string(opponent.battleAtk()) + ' ';
	sendbuf += to_string(opponent.battleDfs()) + ' ';
	sendbuf += to_string(opponent.battleHp()) + ' ';
	sendbuf += to_string(opponent.battleSpeed()) + ' ';
	sendbuf += to_string(opponent.lv()) + ' ' + to_string(opponent.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(opponent.battlePp(i)) + ' ';
	}

}

// 卡比兽--肉盾型
template<>
Race<1>::Race() :PokemonBase(Shi)
{
	changeRacename("Snorlax");
	_skillNames[0] = "摔跤";
	_skillDesc[0] = "Normal attack";
	_skillNames[1] = "肚子大鼓";
	_skillDesc[1] = "Increase dfs";
	_skillNames[2] = "睡觉";
	_skillDesc[2] = "IncreaseHP";
	_skillNames[3] = "泰山压顶";
	_skillDesc[3] = "Cause HUGE damage";
	_pp[0] = INT_MAX;
	_pp[1] = 5;
	_pp[2] = 5;
	_pp[3] = 10;
	
	//种族成长曲线
	_raceCurve.up_atk = 10;
	_raceCurve.up_dfs = 5;
	_raceCurve.up_hp = 50;
	_raceCurve.up_speed = 5;
}
// 卡比兽技能
template<>
void Race<1>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const
{
	cout << attacker.name() << "使用了:" << attacker.skillname(skillIndex) << "!\n" << endl;
	int atk, dfs, damage, skillPower, lv;

	switch (skillIndex)
	{
	case 0:
		if (dodge(80,attacker.battleSpeed(), opponent.battleSpeed(),sendbuf))
			return;
		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.6;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.takeDamage(damage);
		break;
	case 1:
		sendbuf += "0 0\n";
		attacker.setDfs(attacker.battleDfs() / 10);
		break;
	case 2:
		sendbuf += "0 0\n";
		attacker.setHp(attacker.battleHp() / 5);
		break;
	case 3:
		if (dodge(90,attacker.battleSpeed(), opponent.battleSpeed(),sendbuf))
			return;
		skillPower = attacker.battleAtk() * 1.5;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.takeDamage(damage);
		break;
	default:
		break;
	}
	// self 
	sendbuf += to_string(attacker.pokemonid()) + ' ' + attacker.name() + ' ' + to_string(attacker.race()) + ' ';
	sendbuf += to_string(attacker.battleAtk()) + ' ';
	sendbuf += to_string(attacker.battleDfs()) + ' ';
	sendbuf += to_string(attacker.battleHp()) + ' ';
	sendbuf += to_string(attacker.battleSpeed()) + ' ';
	sendbuf += to_string(attacker.lv()) + ' ' + to_string(attacker.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(attacker.battlePp(i)) + ' ';
	}
	// opponent 
	sendbuf += '\n' + to_string(opponent.pokemonid()) + ' ' +
		opponent.name() + ' ' + to_string(opponent.race()) + ' ';
	sendbuf += to_string(opponent.battleAtk()) + ' ';
	sendbuf += to_string(opponent.battleDfs()) + ' ';
	sendbuf += to_string(opponent.battleHp()) + ' ';
	sendbuf += to_string(opponent.battleSpeed()) + ' ';
	sendbuf += to_string(opponent.lv()) + ' ' + to_string(opponent.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(opponent.battlePp(i)) + ' ';
	}

}

// 大岩蛇--防御型
template<>
Race<2>::Race() :PokemonBase(Def)
{
	changeRacename("Onix");
	_skillNames[0] = "冲撞";
	_skillDesc[0] = "Common attack";
	_skillNames[1] = "硬化";
	_skillDesc[1] = "Increase defense";
	_skillNames[2] = "岩石封锁";
	_skillDesc[2] = "Cause damage，and slightly slow down your enemy";
	_skillNames[3] = "沙尘暴";
	_skillDesc[3] = "Cause damage and decrease enemy's atk,dfs and speed";
	_pp[0] = INT_MAX;
	_pp[1] = 5;
	_pp[2] = 10;
	_pp[3] = 2;

	//种族成长曲线
	_raceCurve.up_atk = 10;
	_raceCurve.up_dfs = 10;
	_raceCurve.up_hp = 20;
	_raceCurve.up_speed = 5;
}

// 大岩蛇技能
template<>
void Race<2>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const
{
	cout << attacker.name() << "使用了:" << attacker.skillname(skillIndex) << "!\n" << endl;
	int atk, dfs, damage,skillPower,lv;

	switch (skillIndex)
	{
	case 0:
		if (dodge(80,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
			return;

		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.5;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.takeDamage(damage);
		break;
	case 1:
		sendbuf += "0 0\n";
		attacker.setDfs(attacker.battleDfs() / 8);
		break;
	case 2:
		if (dodge(85,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
			return;

		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.8;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.setSpeed(opponent.battleSpeed()/-8);
		opponent.takeDamage(damage);
		break;
	case 3:
		if (dodge(90,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
			return;

		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk();
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.setSpeed(opponent.battleSpeed() / -10);
		opponent.setAtk(opponent.battleAtk() / -10);
		opponent.setDfs(opponent.battleDfs() / -10);
		opponent.takeDamage(damage);
		break;
	default:
		break;
	}

	// self 
	sendbuf += to_string(attacker.pokemonid()) + ' ' + attacker.name() + ' ' + to_string(attacker.race()) + ' ';
	sendbuf += to_string(attacker.battleAtk()) + ' ';
	sendbuf += to_string(attacker.battleDfs()) + ' ';
	sendbuf += to_string(attacker.battleHp()) + ' ';
	sendbuf += to_string(attacker.battleSpeed()) + ' ';
	sendbuf += to_string(attacker.lv()) + ' ' + to_string(attacker.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(attacker.battlePp(i)) + ' ';
	}
	// opponent 
	sendbuf += '\n' + to_string(opponent.pokemonid()) + ' ' +
		opponent.name() + ' ' + to_string(opponent.race()) + ' ';
	sendbuf += to_string(opponent.battleAtk()) + ' ';
	sendbuf += to_string(opponent.battleDfs()) + ' ';
	sendbuf += to_string(opponent.battleHp()) + ' ';
	sendbuf += to_string(opponent.battleSpeed()) + ' ';
	sendbuf += to_string(opponent.lv()) + ' ' + to_string(opponent.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(opponent.battlePp(i)) + ' ';
	}

}

// 波波--速度型
template<>
Race<3>::Race() :PokemonBase(Spe)
{
	changeRacename("Pidgey");
	_skillNames[0] = "冲撞";
	_skillDesc[0] = "Common attack";
	_skillNames[1] = "快速移动";
	_skillDesc[1] = "Speed UP!";
	_skillNames[2] = "空气斩";
	_skillDesc[2] = "Cause HUGE damage";
	_skillNames[3] = "飓风";
	_skillDesc[3] = "Cause damage and slow down your enemy，speed up";
	_pp[0] = INT_MAX;
	_pp[1] = 5;
	_pp[2] = 10;
	_pp[3] = 5;

	//种族成长曲线
	_raceCurve.up_atk = 10;
	_raceCurve.up_dfs = 5;
	_raceCurve.up_hp = 20;
	_raceCurve.up_speed = 10;
}

// 波波技能
template<>
void Race<3>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const
{
	cout << attacker.name() << "使用了:" << attacker.skillname(skillIndex) << "!\n" << endl;

	int atk, dfs, damage,skillPower,lv;

	switch (skillIndex)
	{
	case 0:
		if (dodge(85,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
			return;

		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.5;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);		opponent.takeDamage(damage);
		break;
	case 1:
		sendbuf += "0 0\n";
		attacker.setSpeed(attacker.battleSpeed()/8);
		break;
	case 2:
		if (dodge(95,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
			return;
		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk()*0.7;
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);		opponent.setDfs(-5);
		opponent.takeDamage(damage);
		break;
	case 3:
		if (dodge(95,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
			return;
		skillPower = rand() % attacker.battleAtk()*0.2 + attacker.battleAtk();
		atk = attacker.battleAtk();
		dfs = opponent.battleDfs();
		lv = attacker.lv();
		damage = damageFunction(atk, dfs, lv, skillPower);
		opponent.takeDamage(damage);
		attacker.setSpeed(attacker.battleSpeed() / 8);
		opponent.setSpeed(opponent.battleSpeed() / -8);
		break;
	default:
		break;
	}

	// self 
	sendbuf += to_string(attacker.pokemonid()) + ' ' + attacker.name() + ' ' + to_string(attacker.race()) + ' ';
	sendbuf += to_string(attacker.battleAtk()) + ' ';
	sendbuf += to_string(attacker.battleDfs()) + ' ';
	sendbuf += to_string(attacker.battleHp()) + ' ';
	sendbuf += to_string(attacker.battleSpeed()) + ' ';
	sendbuf += to_string(attacker.lv()) + ' ' + to_string(attacker.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(attacker.battlePp(i)) + ' ';
	}
	// opponent 
	sendbuf += '\n' + to_string(opponent.pokemonid()) + ' ' +
		opponent.name() + ' ' + to_string(opponent.race()) + ' ';
	sendbuf += to_string(opponent.battleAtk()) + ' ';
	sendbuf += to_string(opponent.battleDfs()) + ' ';
	sendbuf += to_string(opponent.battleHp()) + ' ';
	sendbuf += to_string(opponent.battleSpeed()) + ' ';
	sendbuf += to_string(opponent.lv()) + ' ' + to_string(opponent.hp()) + ' ';
	for (int i = 1; i < 4; i++)
	{
		sendbuf += to_string(opponent.battlePp(i)) + ' ';
	}

}

Pokemon::Pokemon(int raceIndex, const string &name) 
{
	_raceIndex = raceIndex;
	if (name != "")
		_name = name;
	else
		_name = races[raceIndex]->racename();

	_atk = races[raceIndex]->baseAtk();
	_dfs = races[raceIndex]->baseDfs();
	_hp = races[raceIndex]->baseHp();
	_speed = races[raceIndex]->baseSpeed();
	_lv = 1;
	_ep = 0;

	

	if (DEBUG)
	{
		cout << "新的宠物小精灵诞生了！" << endl;
		cout << "相关信息:" << endl;
		cout << "*********************************************" << endl;
		cout << "名字:" << _name << endl;
		cout << "种族:" << races[_raceIndex]->racename() << endl;
		cout << "属性:" << endl;
		cout << "ATK:\t" << _atk<<"\tDFS:\t"<<_dfs<<endl;
		cout << "HP:\t" << _hp << "\tSPEED:\t" << _speed<< endl;
		cout << "技能:" << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << "\t技能名称:\t" << races[_raceIndex]->skillname(i) <<endl<<
				"\t技能描述:\t" << races[_raceIndex]->skilldesc(i) << endl <<
				"\t使用次数:\t"<< races[_raceIndex]->pp(i)<<endl;
		}
			
	}

}

Pokemon::Pokemon(int pokemonid,int raceIndex, const string &name, int atk, int dfs, int hp, int speed, int lv, int ep)
{
	_pokemonid = pokemonid;
	_raceIndex = raceIndex;
	if (name != "")
		_name = name;
	else
		_name = races[_raceIndex]->racename();
	_atk = atk;
	_dfs = dfs;
	_hp = hp;
	_speed = speed;
	_lv = lv;
	_ep = ep;
}

void Pokemon::gainEp(int ep)
{
	if (_lv == 15)
		return;

	addEp(ep);
	if (_ep / 100 > _lv - 1)
	{
		int newLV = (_ep / 100)+1;
		// 属性成长
		int prev_atk = _atk, prev_dfs = _dfs, prev_hp = _hp, prev_speed = _speed;

		// 每一级成长一次
		for (int i = 0; i < newLV-_lv; i++)
		{
			_atk += races[_raceIndex]->baseCurve().up_atk + random(races[_raceIndex]->raceCurve().up_atk);
			_dfs += races[_raceIndex]->baseCurve().up_dfs + random(races[_raceIndex]->raceCurve().up_dfs);
			_hp += races[_raceIndex]->baseCurve().up_hp + random(races[_raceIndex]->raceCurve().up_hp);
			_speed += races[_raceIndex]->baseCurve().up_speed + random(races[_raceIndex]->raceCurve().up_speed);
		}
		_lv = newLV;

		if (DEBUG)
		{
			cout << _name << "升级为:LV" << _lv << endl;
			cout << "\tATK:\t" << prev_atk << "\t->\t" << _atk << endl;
			cout << "\tDFS:\t" << prev_dfs << "\t->\t" << _dfs << endl;
			cout << "\tHP:\t" << prev_hp << "\t->\t" << _hp  << endl;
			cout << "\tSPEED:\t" << prev_speed << "\t->\t" << _speed << endl;
		}
	}
}

void Pokemon::attack(Pokemon& opponent,string &sendbuf, int autofight)
{
	// 选择招式
	cout << "轮到" << _name << "出招了！" << endl;
	// 手动选择
	int chosen_skill=0;
	if (!autofight)
	{
		cout << _name << "可以使用的招式:" << endl;
		for (int i = 0; i < 4; i++)
		{
			if (_battlepp[i] > 0)
				cout << "\t" << i << ":" << races[_raceIndex]->skillname(i) << "\n\t技能描述:" << races[_raceIndex]->skilldesc(i)
				<< "\n\t使用次数:" << battlePp(i) << endl;
		}
		cout << "请输入技能编号:";
		cin >> chosen_skill;
		_battlepp[chosen_skill]--;
	}
	// 自动选择
	else
	{
		// 找出可用的招式
		bool usable_skill[4] = { 1 };
		for (int i = 1; i < 4; i++)
		{
			if (_battlepp[i] > 0)
			{
				usable_skill[i] = true;
			}
		}
		// 从可用的招式随机选择一个
		do
		{
			chosen_skill = rand() % 4;
		} while (!usable_skill[chosen_skill]);
		_battlepp[chosen_skill]--;
	}
	sendbuf += races[_raceIndex]->skillname(chosen_skill);
	sendbuf += " ";
	races[_raceIndex]->attack(*this, opponent, chosen_skill,sendbuf);

	//return damage;

}

void Pokemon::takeDamage(int damage)
{
	cout << _name << "受到了" << damage << "点伤害！\n";
	setHp(-damage);
}

void Pokemon::restoreAll()
{
	_battleAtk = _atk;
	_battleDfs = _dfs;
	_battleHp = _hp;
	_battleSpeed = _speed;

	for (int i = 0; i <4; i++)
	{
		if (_lv >= learn_level[i])
			_battlepp[i] = races[_raceIndex]->pp(i);
		else
			_battlepp[i] = 0;
	}
}

void Pokemon::setAtk(int atk)
{
	_battleAtk += atk;
	if (_battleAtk < 0)
		_battleAtk = 1;
	if (atk>0)
	{
		cout << _name << "的ATK+" << atk<<"!\n";
	}
	else if (!atk)
	{
		cout << _name << "的ATK没有变化!\n";
	}
	else
	{
		cout << _name << "的ATK" << atk << "!\n";
	}
	cout << _name << "当前的ATK为" << _battleAtk << endl << endl;
}

void Pokemon::setDfs(int dfs)
{
	_battleDfs += dfs;
	if (_battleDfs < 0)
		_battleDfs = 1;
	if (dfs > 0)
	{
		cout << _name << "的DFS+" << dfs << "!\n";
	}
	else if (!dfs)
	{
		cout << _name << "的DFS没有变化!\n";
	}
	else
	{
		cout << _name << "的DFS" << dfs << "!\n";
	}
	cout << _name << "当前的DFS为" << _battleDfs << endl << endl;
}

void Pokemon::setHp(int hp)
{
	_battleHp+= hp;
	if (_battleHp < 0)
		_battleHp = 0;
	if (hp > 0)
	{
		cout << _name << "的HP+" << hp << "!\n";
	}
	else if (!hp)
	{
		cout << _name << "的HP没有变化!\n";
	}
	else
	{
		cout << _name << "的HP" << hp << "!\n";
	}
	cout << _name << "当前的HP为" << _battleHp << endl << endl;
}

void Pokemon::setSpeed(int speed)
{
	_battleSpeed += speed;
	if (_battleSpeed < 0)
		_battleSpeed = 1;
	if (speed > 0)
	{
		cout << _name << "的SPEED+" << speed << "!\n";
	}

	else if (!speed)
	{
		cout << _name << "的SPEED没有变化!\n";
	}
	else
	{
		cout << _name << "的SPEED" << speed << "!\n";
	}
	cout << _name << "当前的SPEED为" << _battleSpeed << endl << endl;
}

void Pokemon::addEp(int ep)
{
	_ep += ep;
	cout << _name << "的EP增加了" << ep << "!\n";
	cout << _name << "当前的EP为" << _ep << endl << endl;
}


