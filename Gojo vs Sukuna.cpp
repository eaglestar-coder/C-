#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Gojo;

class Sukuna {
public:
    int cursedenergy, maxenergy, health, maxhp, stunnedturns = 0, skillimit = 0;
    int evasion = 70;
    bool evasionDisabled = false;
    bool domainamp = false;
    int domainampturnsleft = 0;
    int failedattacksongojo= 0;

    Sukuna(int e, int max, int h, int hp) : cursedenergy(e), maxenergy(max), health(h), maxhp(hp) {}

    void takedamage(int dmg) {
        if (!evasionDisabled && (rand() % 100) > evasion) {
            cout << "Attack dodged!" << endl;
            return;
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << "Remaining HP: " << health << endl;
    }

    void stun(int limit) {
        stunnedturns = limit;
        cout << "Sukuna is stunned for " << limit << " turn(s)!" << endl;
    }

    void limit(int limit) {
        skillimit = limit;
    }

    void attack(Gojo &target, bool &sukunausedDomain);
    void shrine (Gojo &target, bool &sukunausedDomain);
    void cleave (Gojo &target, bool &sukunausedDomain);
    void firearrow (Gojo &target, bool &sukunausedDomain);
    void malevolentshrine(Gojo &target, int &dot, bool &gojoUsed, int &gojoLvl, bool &sukunaUsed, int &sukunaLvl);
    void regenerate();
    void recharge(int e, int max);
    void launchRandomAttack(Gojo &target, int &dot, bool &gojoUsed, int &gojoLvl, bool &sukunaUsed, int &sukunaLvl);
};

class Gojo {
public:
    int cursedenergy, maxenergy, health, maxhp, skillimit = 0;
    int evasion = 70;
    bool evasionDisabled = false;
    bool simpleDomainActive = false;
    int simpledomainturnsleft = 0;
    bool infinityActive = true;

    Gojo(int e, int max, int h, int hp) : cursedenergy(e), maxenergy(max), health(h), maxhp(hp) {}

    bool disableinfinity(Sukuna &target, bool &sukunausedDomain, int hpThreshold = 300) {
		if (health > hpThreshold && cursedenergy >= 500 && infinityActive && !sukunausedDomain) {
			return (rand()% 100 < 70);
		} else if (target.health <= 300 && cursedenergy >= 500 && infinityActive && !sukunausedDomain) {
			return true;
		}
		return false;
	}
    
    
    bool takedamage(int dmg, bool &sukunausedDomain) {
        
        if (infinityActive && skillimit == 0 && !sukunausedDomain ) {
			cursedenergy -= 200;
			cout << "Infinity Blocks the Attack" << endl;
			return false;
        }
        
        if (!evasionDisabled && (rand() % 100) > evasion) {
            cout << "Attack dodged!" << endl;
            return false;
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << "Remaining HP: " << health << endl;
        return true;
    }

    void limit(int limit) {
        skillimit = limit;
    }

    void stun(int) {}
    
    void infinityOverrideTakedamage(int dmg) {
		if (!evasionDisabled && (rand () %100) > evasion) {
			cout<<"Attack dodged"<<endl;
			return;
		}
		health -=dmg;
		if (health < 0) health = 0;
		cout << "Infinity Bypassed! Remaining HP: "<<health<<endl;
	}

    void attack(Sukuna &target) {
        target.takedamage(50);
        cout << "Gojo Attacks Sukuna!" << endl;
        if (rand() % 10 == 0) {
            cout << "Black Flash" << endl;
            target.takedamage(150);
        }
    }

    
    void launchBlue(Sukuna &target, bool &infinityActive) {
    if (cursedenergy >= 200 && !infinityActive) {
        cout << "Phase, Twilight, Eyes of Wisdom\nCursed Technique Lapse Maximum Output: Blue" << endl;
        cursedenergy -= 200;
        target.takedamage(80);
    } else if (cursedenergy >= 50 && infinityActive) {
        cout << "Cursed Technique Lapse: Blue" << endl;
        cursedenergy -= 50;
        target.takedamage(180);
    } else cout << "Not enough energy for Blue." << endl;
}

void launchRed(Sukuna &target, bool &infinityActive) {
    if (cursedenergy >= 400 && !infinityActive) {
        cout << "Phase, Paramita, Pillar of Light\nCursed Technique Reversal Maximum Output: Red" << endl;
        cursedenergy -= 400;
        target.takedamage(120);
    } else if (cursedenergy >= 100 && infinityActive) {
        cout << "Cursed Technique Reversal: Red" << endl;
        cursedenergy -= 100;
        target.takedamage(250);
    } else cout << "Not enough energy for Red." << endl;
}

void launchHollowPurple(Sukuna &target, bool &infinityActive) {
    if (cursedenergy >= 800 && !infinityActive) {
        cout << "Nine Ropes, Polarized Light, Crow and Declaration, The Gap Between Within and Without\n200% Hollow Purple" << endl;
        cursedenergy -= 800;
        target.takedamage(400);
    } else if (cursedenergy >= 200 && !infinityActive) {
          cout << "Cursed Technique Lapse: Blue" << endl;
          cout << "Cursed Technique Reversal: Red" << endl;
          cout << "Hollow Purple" << endl;
        cursedenergy -= 200;
        target.takedamage(600);
    } else cout << "Not enough energy for Hollow Purple." << endl;
}
    
    
    
    void domainExpansion(Sukuna &target, bool &gojoUsed, int &gojoLvl, bool &sukunaUsed, int &sukunaLvl) {
        if (cursedenergy >= 900) {
            cout << "Domain Expansion: Unlimited Void" << endl;
            cursedenergy -= 900;
            target.stun(2);
            limit(3);
            gojoUsed = true;
            gojoLvl = 2;
            infinityActive = false;
            if (!sukunaUsed && target.cursedenergy >= 800) {
                target.malevolentshrine(*this, gojoLvl, gojoUsed, gojoLvl, sukunaUsed, sukunaLvl);
                target.stun(0);
                target.cursedenergy -=800; 
              }
        } else if (cursedenergy >= 500) {
            cout << "Domain Expansion: 0.2 Unlimited Void" << endl;
            cursedenergy -= 500;
            target.stun(1);
            limit(1);
            gojoUsed = true;
            gojoLvl = 1;
            infinityActive = false;
        }
    }
    
    void SimpleDomain() {
		simpleDomainActive = true;
		simpledomainturnsleft = 1;
		cursedenergy -= 300;
		this->limit(2);
		cout<<"Gojo Activates New Shadow Style: Simple Domain"<<endl;
	}

  
   void recharge(int ticks, int energyPerTick) {
        cout << "Gojo recharges..." << endl;
        for (int i = 1; i <= ticks; ++i) {
            if (cursedenergy + energyPerTick > maxenergy) {
                cursedenergy = maxenergy;
                break;
            } else {
                cursedenergy += energyPerTick;
            }
        }
        cout << "Recharge complete." << endl << endl;
    }

    void regenerate() {
        if (cursedenergy >= 100) {
            cout << "Gojo performs Reversed Cursed Technique" << endl;
            cursedenergy -= 100;
            int heal = rand() % 51 + 100;
            health += heal;
            if (health > maxhp) health = maxhp;
            cout << "Healed: " << heal << ", Current HP: " << health << endl;
        }
    }

    void launchRandomAttack(Sukuna &target, bool &gojoUsed, int &gojoLvl, bool &sukunausedDomain, int &sukunaLvl) {
        if (skillimit > 0) {
            attack(target);
            skillimit--;
            return;
        }

        int choice = rand() % 6;
        switch (choice) {
            case 0: domainExpansion(target, gojoUsed, gojoLvl, sukunausedDomain, sukunaLvl); break;
            case 1: regenerate(); break;
            case 2: attack(target); break;
            case 3: 
				if (disableinfinity(target, sukunausedDomain)) {
				infinityActive = false;
			}
				launchBlue(target, infinityActive); break;
            case 4: 
				if (disableinfinity(target, sukunausedDomain)) {
				infinityActive = false;
			}
				launchRed(target, infinityActive); break;
            case 5: 
				if (disableinfinity(target, sukunausedDomain)) {
				infinityActive = false;
			}
            launchHollowPurple(target, infinityActive); break;
        }
        
        if (!infinityActive && skillimit == 0 && cursedenergy >= 200) {
			infinityActive = true;
}        
        if (cursedenergy < 100) {
			recharge(3,50);
		}
    }
};

void Sukuna::attack(Gojo &target, bool &sukunausedDomain) {
    if (domainamp) {
        cout << "Sukuna uses Domain Amplification to bypass Infinity!" << endl;
        target.infinityOverrideTakedamage(50);
        domainampturnsleft--;
        if (domainampturnsleft <= 0) {
            domainamp = false;
            cout << "Domain Amplification fades..." << endl;
        }
        return;
    }

    bool hit = target.takedamage(50, sukunausedDomain);
    cout << "Sukuna Attacks Gojo!" << endl;

    if (!hit && target.infinityActive && !sukunausedDomain && !target.evasionDisabled) {
        failedattacksongojo++;
        cout << "Sukuna's attack was blocked by Infinity! (" << failedattacksongojo << " failed attempt(s))" << endl;
    } else {
        failedattacksongojo = 0;
    }

    if (failedattacksongojo >= 1 && !sukunausedDomain) {
        domainamp = true;
        domainampturnsleft = 2;
        cursedenergy -= 100;
        cout << "Sukuna activates Domain Amplification!" << endl;
    }

    if (rand() % 10 == 0) {
        cout << "Black Flash!" << endl;
        bool flashHit = target.takedamage(150, sukunausedDomain);
        if (!flashHit && target.infinityActive && !sukunausedDomain && !target.evasionDisabled) {
            failedattacksongojo++;
            cout << "Sukuna's Black Flash was blocked! (" << failedattacksongojo << " failed attempt(s))" << endl;
        }
    }
}

void Sukuna::shrine(Gojo &target, bool &sukunausedDomain) {
    if (cursedenergy >= 200) {
        cout << "Shrine" << endl;
        cursedenergy -= 200;
        target.takedamage(100, sukunausedDomain);
    }
}

void Sukuna::cleave(Gojo &target, bool &sukunausedDomain) {  
    if (cursedenergy >= 300) {
        cout << "Dismantle and Cleave" << endl;
        cursedenergy -= 300;
        target.takedamage(130, sukunausedDomain);
    }
}

void Sukuna::firearrow(Gojo &target, bool &sukunausedDomain) {
    if (cursedenergy >= 600) {
        cout << "Divine Flame" << endl;
        cursedenergy -= 600;
        target.takedamage(250, sukunausedDomain);
    }
}

void Sukuna::malevolentshrine(Gojo &target, int &dotRef, bool &gojousedDomain, int &gojodomainlevel, bool &sukunausedDomain, int &sukunadomainlevel) {
    if (cursedenergy >= 1200) {
        cout << "Domain Expansion!" << endl;
        cout << "Open Barrier: Malevolent Shrine" << endl;
        cursedenergy -= 1200;
        sukunadomainlevel = 2;
        this->limit(2);
        dotRef = 2;
    } else if (cursedenergy >= 800) {
        cout << "Domain Expansion!" << endl;
        cout << "Malevolent Shrine" << endl;
        cursedenergy -= 800;
        sukunadomainlevel = 1;
        dotRef = 2;
        this->limit(2);
    } else {
        cout << "Not enough energy for Domain Expansion." << endl;
        return;
    }

    sukunausedDomain = true;

    if (target.cursedenergy >= 300 && !target.simpleDomainActive && !gojousedDomain) {
        target.SimpleDomain();
        dotRef = 0;
        cout << "Simple Domain repels the vicious attacks of Malevolent Shrine!" << endl;
    } else {
        target.evasionDisabled = true;
        this->limit(2);
        dotRef = 2;
    }

    if (!gojousedDomain && target.cursedenergy >= 900 && !target.simpleDomainActive) {
        target.domainExpansion(*this, gojousedDomain, gojodomainlevel, sukunausedDomain, sukunadomainlevel);
        target.cursedenergy -= 900;
        dotRef = 0;
    }
}



void Sukuna::regenerate() {
    if (cursedenergy >= 100) {
        cout << "Sukuna regenerates his body" << endl;
        cursedenergy -= 100;
        int heal = rand() % 51 + 100;
        health += heal;
        if (health > maxhp) health = maxhp;
        cout << "Healed: " << heal << ", Current HP: " << health << endl;
    }
}


void Sukuna::recharge(int ticks, int energyPerTick) {
        cout << "Sukuna recharges..." << endl;
        for (int i = 1; i <= ticks; ++i) {
            if (cursedenergy + energyPerTick > maxenergy) {
                cursedenergy = maxenergy;
                break;
            } else {
                cursedenergy += energyPerTick;
            }
        }
        cout << "Recharge complete." << endl << endl;
    }


void Sukuna::launchRandomAttack(Gojo &target, int &dotRef, bool &gojousedDomain, int &gojodomainlevel, bool &sukunausedDomain, int &sukunadomainlevel) {
    if (stunnedturns > 0) {
        cout << "Sukuna is stunned!" << endl;
        stunnedturns--;
        return;
    }
    
    if (skillimit > 0) {
        attack(target, sukunausedDomain);
        skillimit--;
        return;
    }
    
    if (domainamp) {
		attack(target, sukunausedDomain);
		return;
	}
    
     if (!domainamp && failedattacksongojo >= 2 && !sukunausedDomain && cursedenergy >= 800) {
        cout << "Sukuna opens his Domain!" << endl;
        malevolentshrine(target, dotRef, gojousedDomain, gojodomainlevel, sukunausedDomain, sukunadomainlevel);
        return;
    }

    int choice = rand() % 6;
    switch (choice) {
        case 0: malevolentshrine(target, dotRef, gojousedDomain, gojodomainlevel, sukunausedDomain, sukunadomainlevel); break;
        case 1: regenerate(); break;
        case 2: attack(target, sukunausedDomain); break;
        case 3: shrine(target, sukunausedDomain); break;
        case 4: cleave(target, sukunausedDomain); break;
        case 5: firearrow(target, sukunausedDomain); break;
    }
    if (cursedenergy < 100) {
			recharge(3,50);
		}
}

int main() {
    srand(time(0));
    Gojo Satoru(2000, 4000, 850, 850);
    Sukuna Ryomen(2000, 4000, 850, 850);
    int gojoDoTturns = 0, turn = 1;
    bool gojousedDomain = false, sukunausedDomain = false;
    int gojodomainlevel = 0, sukunadomainlevel = 0;

    while (Satoru.health > 0 && Ryomen.health > 0) {
        cout << "\n=== Turn " << turn << " Begins ===" << endl;

		if (!Satoru.infinityActive && Satoru.skillimit == 0) {
		Satoru.infinityActive = true;
		cout << "Gojo Reactivates infinity" << endl;
	}
		
        if (gojousedDomain && sukunausedDomain) {
            cout << "Domain Clash! Malevolent Shrine vs Unlimited Void!" << endl;
            if (gojodomainlevel == 1 || sukunadomainlevel == 2) {
                gojoDoTturns = 2;
                cout<<"Sukuna's Shrine Prevails"<<endl;
                Satoru.evasionDisabled = true;
            } else {
                int gojoPower = Satoru.cursedenergy + rand() % 100;
                int sukunaPower = Ryomen.cursedenergy + rand() % 100;
                if (gojoPower > sukunaPower) {
                    cout << "Gojo's Unlimtied Void crushes Sukuna's Malevolent Shrine" << endl;
                    Ryomen.stun(2);
                    gojoDoTturns = 0;
                } else if (sukunaPower > gojoPower) {
				cout << "Sukuna's Shrine crushes Infinite Void!" << endl;
				gojoDoTturns = 2;
				Satoru.limit(0);
				Satoru.evasionDisabled = true;
			} else { 
				cout << "Both Domains shatter in equal force! Both are hit!"<< endl;
				Satoru.takedamage(200, sukunausedDomain);
				Ryomen.takedamage(200);
			}
            }
            gojousedDomain = sukunausedDomain = false;
        }

        if (gojoDoTturns > 0) {
            cout << "Malevolent Shrine Cleaves Through Gojo!" << endl;
            Satoru.takedamage(100, sukunausedDomain);
            gojoDoTturns--;
        }
        
        if (Satoru.simpleDomainActive) {
			Satoru.simpledomainturnsleft--;
			if (Satoru.simpledomainturnsleft <= 0) {
				Satoru.simpleDomainActive = false;
				cout << "Simple Domain crushes underneath Malevolent Shrine" << endl;
			}
		}

        cout << "\nGojo's Turn:" << endl;
        Satoru.launchRandomAttack(Ryomen, gojousedDomain, gojodomainlevel, sukunausedDomain, sukunadomainlevel);
        if (Ryomen.health <= 0) {
            cout << "Sukuna has been defeated!" << endl;
            break;
        }

        cout << "\nSukuna's Turn:" << endl;
        Ryomen.launchRandomAttack(Satoru, gojoDoTturns, gojousedDomain, gojodomainlevel, sukunausedDomain, sukunadomainlevel);
        if (Satoru.health <= 0) {
            cout << "Gojo has been defeated!" << endl;
            break;
        }

	        if (Satoru.skillimit == 0 && gojousedDomain) {
		gojousedDomain = false;
		gojodomainlevel = 0;
		cout << "Unlimited Void fades..." << endl;
  }

		if (Ryomen.skillimit == 0 && sukunausedDomain) {
		sukunausedDomain = false;
		sukunadomainlevel = 0;
		cout << "Malevolent Shrine fades..." << endl;
     }	

        turn++;
    }

    return 0;
}
