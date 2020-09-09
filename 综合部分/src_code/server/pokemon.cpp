#include "pokemon.h"

const PokemonBase *Pokemon::races[4] = { new Race<0>(),new Race<1>(), new Race<2>(), new Race<3>() };


// ѧϰ���ܵȼ�
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
	// ����С�����˺���ʽ���������ȼ� �� 2 �� 5 + 2�� �� �������� �� ������������ �� ������������ �� 50 + 2
	// 
	int damage = (attacker_lv + 2)*skillpower*atk / dfs / 10 + 2;
	return damage;
}

PokemonBase::PokemonBase(PokemonRace race)
{
	// �趨��������
	
	_baseAtk = 10;
	_baseDfs = 10;
	_baseHp = 100;
	_baseSpeed = 20;

	_race = race;

	_baseCurve.up_atk = 5;
	_baseCurve.up_dfs = 5;
	_baseCurve.up_hp = 50;
	_baseCurve.up_speed = 10;

	// ÿ������Ļ�������������ͬ
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

// �����ж�
bool PokemonBase::dodge(int skill_accuraccy ,int attack_speed, int opponent_speed, string &sendbuf)const
{
	// A = B * C / D
	//B����ʽ�����о�����C�ɹ������ٶȾ�����D�ɷ������ٶȾ���
	//B������ʽ��������ʽ������Խ����ֵԽ�����Ϊ255,�������Ϊ�ٷֱ�
	//����һ��1~255֮�����������������С��Aʱ��Ϊ���У�����Ϊ����
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
		cout << "���о�Ȼ�������ˣ�" << endl;
		sendbuf += "1 0\n";
		return true;
	}
	else
	{
		sendbuf += "0 0\n";
		return false;
	}
}

// �𱬺��������
template<>
Race<0>::Race() :PokemonBase(Pow)
{
	changeRacename("Primeape");
	_skillNames[0] = "��";
	_skillDesc[0] = "Normal attack with low damage";
	_skillNames[1] = "���ֵ���";
	_skillDesc[1] = "Normal attack with high damage";
	_skillNames[2] = "����ˤ";
	_skillDesc[2] = "Cause damage and decrease enemy's dfs";
	_skillNames[3] = "����Ͷ";
	_skillDesc[3] = "Cause twice damage of its own atk";
	_pp[0] = INT_MAX;
	_pp[1] = 10;
	_pp[2] = 5;
	_pp[3] = 3;

	//����ɳ�����
	_raceCurve.up_atk = 15;
	_raceCurve.up_dfs = 5;
	_raceCurve.up_hp = 20;
	_raceCurve.up_speed = 5;
	
}

// �𱬺＼��
template<>
void Race<0>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex ,string& sendbuf) const
{
	cout << attacker.name() << "ʹ����:" <<  attacker.skillname(skillIndex)<<"!\n" << endl;
	
	int atk, dfs, damage,skillPower,lv;

	// ȫ���Ǹı�Է���
	switch (skillIndex)
	{
	case 0:

		if (dodge(85,attacker.battleSpeed(), opponent.battleSpeed(), sendbuf))
		{
			return;
		}

		// Ŀǰ�����Ǳ���
		// ����ֱ����dodge������Ϊ0

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

// ������--�����
template<>
Race<1>::Race() :PokemonBase(Shi)
{
	changeRacename("Snorlax");
	_skillNames[0] = "ˤ��";
	_skillDesc[0] = "Normal attack";
	_skillNames[1] = "���Ӵ��";
	_skillDesc[1] = "Increase dfs";
	_skillNames[2] = "˯��";
	_skillDesc[2] = "IncreaseHP";
	_skillNames[3] = "̩ɽѹ��";
	_skillDesc[3] = "Cause HUGE damage";
	_pp[0] = INT_MAX;
	_pp[1] = 5;
	_pp[2] = 5;
	_pp[3] = 10;
	
	//����ɳ�����
	_raceCurve.up_atk = 10;
	_raceCurve.up_dfs = 5;
	_raceCurve.up_hp = 50;
	_raceCurve.up_speed = 5;
}
// �����޼���
template<>
void Race<1>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const
{
	cout << attacker.name() << "ʹ����:" << attacker.skillname(skillIndex) << "!\n" << endl;
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

// ������--������
template<>
Race<2>::Race() :PokemonBase(Def)
{
	changeRacename("Onix");
	_skillNames[0] = "��ײ";
	_skillDesc[0] = "Common attack";
	_skillNames[1] = "Ӳ��";
	_skillDesc[1] = "Increase defense";
	_skillNames[2] = "��ʯ����";
	_skillDesc[2] = "Cause damage��and slightly slow down your enemy";
	_skillNames[3] = "ɳ����";
	_skillDesc[3] = "Cause damage and decrease enemy's atk,dfs and speed";
	_pp[0] = INT_MAX;
	_pp[1] = 5;
	_pp[2] = 10;
	_pp[3] = 2;

	//����ɳ�����
	_raceCurve.up_atk = 10;
	_raceCurve.up_dfs = 10;
	_raceCurve.up_hp = 20;
	_raceCurve.up_speed = 5;
}

// �����߼���
template<>
void Race<2>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const
{
	cout << attacker.name() << "ʹ����:" << attacker.skillname(skillIndex) << "!\n" << endl;
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

// ����--�ٶ���
template<>
Race<3>::Race() :PokemonBase(Spe)
{
	changeRacename("Pidgey");
	_skillNames[0] = "��ײ";
	_skillDesc[0] = "Common attack";
	_skillNames[1] = "�����ƶ�";
	_skillDesc[1] = "Speed UP!";
	_skillNames[2] = "����ն";
	_skillDesc[2] = "Cause HUGE damage";
	_skillNames[3] = "쫷�";
	_skillDesc[3] = "Cause damage and slow down your enemy��speed up";
	_pp[0] = INT_MAX;
	_pp[1] = 5;
	_pp[2] = 10;
	_pp[3] = 5;

	//����ɳ�����
	_raceCurve.up_atk = 10;
	_raceCurve.up_dfs = 5;
	_raceCurve.up_hp = 20;
	_raceCurve.up_speed = 10;
}

// ��������
template<>
void Race<3>::attack(Pokemon &attacker, Pokemon &opponent, int skillIndex, string &sendbuf) const
{
	cout << attacker.name() << "ʹ����:" << attacker.skillname(skillIndex) << "!\n" << endl;

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
		cout << "�µĳ���С���鵮���ˣ�" << endl;
		cout << "�����Ϣ:" << endl;
		cout << "*********************************************" << endl;
		cout << "����:" << _name << endl;
		cout << "����:" << races[_raceIndex]->racename() << endl;
		cout << "����:" << endl;
		cout << "ATK:\t" << _atk<<"\tDFS:\t"<<_dfs<<endl;
		cout << "HP:\t" << _hp << "\tSPEED:\t" << _speed<< endl;
		cout << "����:" << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << "\t��������:\t" << races[_raceIndex]->skillname(i) <<endl<<
				"\t��������:\t" << races[_raceIndex]->skilldesc(i) << endl <<
				"\tʹ�ô���:\t"<< races[_raceIndex]->pp(i)<<endl;
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
		// ���Գɳ�
		int prev_atk = _atk, prev_dfs = _dfs, prev_hp = _hp, prev_speed = _speed;

		// ÿһ���ɳ�һ��
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
			cout << _name << "����Ϊ:LV" << _lv << endl;
			cout << "\tATK:\t" << prev_atk << "\t->\t" << _atk << endl;
			cout << "\tDFS:\t" << prev_dfs << "\t->\t" << _dfs << endl;
			cout << "\tHP:\t" << prev_hp << "\t->\t" << _hp  << endl;
			cout << "\tSPEED:\t" << prev_speed << "\t->\t" << _speed << endl;
		}
	}
}

void Pokemon::attack(Pokemon& opponent,string &sendbuf, int autofight)
{
	// ѡ����ʽ
	cout << "�ֵ�" << _name << "�����ˣ�" << endl;
	// �ֶ�ѡ��
	int chosen_skill=0;
	if (!autofight)
	{
		cout << _name << "����ʹ�õ���ʽ:" << endl;
		for (int i = 0; i < 4; i++)
		{
			if (_battlepp[i] > 0)
				cout << "\t" << i << ":" << races[_raceIndex]->skillname(i) << "\n\t��������:" << races[_raceIndex]->skilldesc(i)
				<< "\n\tʹ�ô���:" << battlePp(i) << endl;
		}
		cout << "�����뼼�ܱ��:";
		cin >> chosen_skill;
		_battlepp[chosen_skill]--;
	}
	// �Զ�ѡ��
	else
	{
		// �ҳ����õ���ʽ
		bool usable_skill[4] = { 1 };
		for (int i = 1; i < 4; i++)
		{
			if (_battlepp[i] > 0)
			{
				usable_skill[i] = true;
			}
		}
		// �ӿ��õ���ʽ���ѡ��һ��
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
	cout << _name << "�ܵ���" << damage << "���˺���\n";
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
		cout << _name << "��ATK+" << atk<<"!\n";
	}
	else if (!atk)
	{
		cout << _name << "��ATKû�б仯!\n";
	}
	else
	{
		cout << _name << "��ATK" << atk << "!\n";
	}
	cout << _name << "��ǰ��ATKΪ" << _battleAtk << endl << endl;
}

void Pokemon::setDfs(int dfs)
{
	_battleDfs += dfs;
	if (_battleDfs < 0)
		_battleDfs = 1;
	if (dfs > 0)
	{
		cout << _name << "��DFS+" << dfs << "!\n";
	}
	else if (!dfs)
	{
		cout << _name << "��DFSû�б仯!\n";
	}
	else
	{
		cout << _name << "��DFS" << dfs << "!\n";
	}
	cout << _name << "��ǰ��DFSΪ" << _battleDfs << endl << endl;
}

void Pokemon::setHp(int hp)
{
	_battleHp+= hp;
	if (_battleHp < 0)
		_battleHp = 0;
	if (hp > 0)
	{
		cout << _name << "��HP+" << hp << "!\n";
	}
	else if (!hp)
	{
		cout << _name << "��HPû�б仯!\n";
	}
	else
	{
		cout << _name << "��HP" << hp << "!\n";
	}
	cout << _name << "��ǰ��HPΪ" << _battleHp << endl << endl;
}

void Pokemon::setSpeed(int speed)
{
	_battleSpeed += speed;
	if (_battleSpeed < 0)
		_battleSpeed = 1;
	if (speed > 0)
	{
		cout << _name << "��SPEED+" << speed << "!\n";
	}

	else if (!speed)
	{
		cout << _name << "��SPEEDû�б仯!\n";
	}
	else
	{
		cout << _name << "��SPEED" << speed << "!\n";
	}
	cout << _name << "��ǰ��SPEEDΪ" << _battleSpeed << endl << endl;
}

void Pokemon::addEp(int ep)
{
	_ep += ep;
	cout << _name << "��EP������" << ep << "!\n";
	cout << _name << "��ǰ��EPΪ" << _ep << endl << endl;
}


