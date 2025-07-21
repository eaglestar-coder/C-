#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

class Hakari;

class Kashimo {
public:
    int cursedenergy, maxenergy, health, maxhp;
    int evasion = 85;
    int techniquevasion = 65;
    bool cursedtechnique = false;
    bool evasionDisabled = false;
    bool staffequip = false;
    int cursedtechniqueturnsleft = 0;
    int basketturnsleft = 0;
    int staffdurability = 0;
    bool staffbroken = false;
    int zoneturnsleft = 0;
    bool electricalcharge = false;

    Kashimo(int e, int max, int h, int hp) {
        cursedenergy = e;
        maxenergy = max;
        health = h;
        maxhp = hp;
    }

    void takedamage(int dmg, bool &domainused);
    void attack(Hakari &target);
    void discharge(Hakari &target, bool &evasionDisabled);
    void equipstaff();
    void hollowbasket(bool &domainused);
    void usecursedtechnique();
    void launchAttack(Hakari &target);
    void recharge(int ticks, int energyPerTick);
};

class Hakari {
public:
    int cursedenergy, maxenergy, health, maxhp;
    bool domainused = false;
    int immortalTime = 0;
    bool immortal = false;
    int greendoor = 0, reddoor = 0, golddoor = 0, rainbowdoor = 0;
    int greenball = 0, redball = 0, goldball = 0, rainbowball = 0;
    bool evasionDisabled = false;
    int evasion = 90;
    int domainturnsleft = 0;
    int zoneturnsleft = 0;
    bool extraSpinNextTurn = false;
    int immortalityUses = 0;
    int maxImmortalityUses = 5;
    bool domainOnCooldown = false;
    int domainCooldownTurns = 0;

    Hakari(int e, int max, int h, int hp) {
        cursedenergy = e;
        maxenergy = max;
        health = h;
        maxhp = hp;
    }

    void takedamage(int dmg) {
        if (immortal) {
            health -= dmg;
            if (health < 0) {
				health = 0;
			}
            if (dmg < health) {
			  cout << "Hakari took " << dmg << " damage (Immortal Mode)" << endl;
			  cout << "Hakari regenerates the damage" << endl;
			  health = maxhp;
			  return;
        }
      }
        if (!evasionDisabled && (rand() % 100) > evasion) {
            cout << "Attack dodged!" << endl;
            return;
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << "Hakari took " << dmg << " damage" << endl;
        cout << "Remaining HP: " << health << endl;
    }

    bool spinPachinko(bool guaranteed) {
        int num = rand() % 999 + 1;
        int digits[3] = { (num / 100) % 10, (num / 10) % 10, num % 10 };
        bool allOdd = true, allEven = true;

        for (int i = 0; i < 3; ++i) {
            if (digits[i] % 2 == 0) allOdd = false;
            else allEven = false;
        }
			
        cout << "Pachinko Roll: " << setw(3) << setfill('0') << num << endl;

        if (allOdd) cout << "All digits are odd! Jackpot chance raised to 75%!" << endl;
        if (allEven) { cout << "All digits are even! Bonus spin next turn!" << endl; extraSpinNextTurn = true; }

		double baseChance = (1.0 / 239.5) * 100.0;
		double bonus = greendoor * 1.0 + reddoor * 5.0 + redball * 2.5 + greenball * 0.5;
		double totalChance = baseChance + bonus;

		if (golddoor > 0) totalChance += 50.0;
		else if (goldball > 0) totalChance += 25.0;

		if (allOdd && !guaranteed) totalChance += 30.0;

		if (!guaranteed) totalChance = min(totalChance, 75.0);  
        double rollPercent = (rand() % 10000) / 100.0;
        cout << "Jackpot Roll: " << rollPercent << "% vs Chance: " << totalChance << "%" << endl;

        bool jackpot = rollPercent < totalChance;
        if (jackpot) cout << "JACKPOT HIT! 777!!!" << endl;
        return jackpot;
    }

    void activateImmortality() {
        if (immortalityUses >= maxImmortalityUses) {
        cout << "Hakari's body has grown resistant to immortality. He can’t regenerate anymore!" << endl;
        return;
    }
        
        immortal = true;
        immortalTime = 6;
        health = maxhp;
        cursedenergy = maxenergy;
        domainused = false;
        immortalityUses++;
        greendoor = reddoor = golddoor = rainbowdoor = 0;
        greenball = redball = goldball = rainbowball = 0;
        cout << "Due to the Unlimited Cursed Energy Flowing Through Hakari, his body reflexively performs Reversed Cursed Technique"<< endl;
		cout << "This means, for the next 4 minutes and 11 seconds, Hakari is effectively Immortal" << endl;
    }

    void domainTick() {
        if (domainused) {
            domainturnsleft--;
            cout << "[Idle Death Gamble Effect]: Pachinko auto-roll..." << endl;
            if (spinPachinko(false)) {
                activateImmortality();
                cout << "Jackpot Hit! Immortality retriggered!" << endl;
            } else {
                cout << "No Jackpot this turn." << endl;
            }

            if (domainturnsleft <= 0) {
                domainused = false;
                cout << "Idle Death Gamble collapses!" << endl;
            } else {
                cout << "Domain active — turns remaining: " << domainturnsleft << endl;
            }

            if (extraSpinNextTurn) {
                cout << "Extra Pachinko Spin triggered!" << endl;
                extraSpinNextTurn = false;
                if (spinPachinko(false)) {
                    activateImmortality();
                    cout << "Jackpot Success — Immortality retriggered!" << endl;
                }
            }
        }
    }

    void shutterdoors(Kashimo &target);
    void reserveball(Kashimo &target);
    void domainexpansion();
    void recharge(int ticks, int energyPerTick);
    void tick();
    void attack(Kashimo &target);
    void launchAttack(Kashimo &target);
};

void Kashimo::takedamage(int dmg, bool &domainused) {
    if (!evasionDisabled && !cursedtechnique && (rand() % 100) > techniquevasion && !domainused) {
        cout << "Attack dodged!" << endl;
        return;
    }
    if (!evasionDisabled && (rand() % 100) > evasion && !domainused) {
        cout << "Attack dodged!" << endl;
        return;
    }
    health -= dmg;
    if (health < 0) health = 0;
    cout << "Kashimo took " << dmg << " damage" << endl;
    cout << "Remaining HP: " << health << endl;
}

void Kashimo::attack(Hakari &target) {
    double baseChance = 10.0;
    double bonusChance = zoneturnsleft * 10.0;
    double totalChance = baseChance + bonusChance;
    if (totalChance > 100.0) totalChance = 100.0;

    int roll = rand() % 100;
    bool blackFlash = roll < totalChance;

    int baseDmg = 100 + (10 * zoneturnsleft);
    int blackFlashBonus = 230;

    cout << "Black Flash Chance: " << totalChance << "% | Rolled: " << roll << endl;

    if (!cursedtechnique) {
        cout << "Kashimo attacks Hakari!" << endl;
        target.takedamage(baseDmg);
        if (blackFlash) {
            cout << ">> BLACK FLASH << Surge of precision and power!" << endl;
            target.takedamage(blackFlashBonus);
            zoneturnsleft++;
        }
    } else if (staffequip) {
        baseDmg = 50 + (10 * zoneturnsleft);
        blackFlashBonus = 150;
        cout << "Kashimo attacks Hakari with Staff!" << endl;
        target.takedamage(baseDmg);
        staffdurability--;
        if (blackFlash) {
            cout << ">> BLACK FLASH with Staff <<" << endl;
            target.takedamage(blackFlashBonus);
            zoneturnsleft++;
        }
        if (staffdurability <= 0) {
            staffequip = false;
            staffbroken = true;
            cout << "Kashimo's staff broke!" << endl;
        }
    } else {
        baseDmg = 40 + (10 * zoneturnsleft);
        blackFlashBonus = 140;
        cout << "Kashimo attacks Hakari barehanded!" << endl;
        target.takedamage(baseDmg);
        if ((rand() % 5) == 0 && zoneturnsleft == 0) {
            cout << "Kashimo's fists are infused with electrical energy!" << endl;
            target.takedamage(60);
        }
        if (blackFlash) {
            cout << ">> BLACK FLASH <<" << endl;
            target.takedamage(blackFlashBonus);
            zoneturnsleft++;
        }
    }

    cout << "Zone Stack Count: " << zoneturnsleft << endl;

    if (zoneturnsleft >= 5) {
        zoneturnsleft = 0;
        cursedenergy += 250;
        cout << "[ZONE RESET] Kashimo's cursed energy surges!" << endl;
    }
}

void Kashimo::discharge(Hakari &target, bool &evasionDisabled) {
    target.evasionDisabled = true;

    if (cursedtechnique) {
        cout << "Kashimo uses Lightning Discharge!" << endl;
        cursedenergy -= 200;
        target.takedamage(500);
    } else if (staffequip) {
        cout << "Kashimo discharges with Staff!" << endl;
        cursedenergy -= 100;
        target.takedamage(200);
        staffdurability--;
    } else {
        cout << "Kashimo discharges barehanded!" << endl;
        cursedenergy -= 200;
        target.takedamage(150);
    }
}

void Kashimo::equipstaff() {
    if (!staffequip && !staffbroken) {
        cout << "Kashimo equips his staff!" << endl;
        staffequip = true;
        staffdurability = 10;
	if (staffdurability == 0) {
		staffbroken = true;
		cout<<"Staff is broken"<<endl;
	}
    } else {
        cout << "Staff cannot be equipped." << endl;
    }
}

void Kashimo::usecursedtechnique() {
    if (cursedenergy >= 500) {
        cursedenergy *= 0.5;
        cursedtechniqueturnsleft = 6;
        cursedtechnique = true;
        staffequip = false;
        cout << "Kashimo unleashes his Cursed Technique!" << endl;
        cout << "Mythical Beast Amber!!!" << endl;
        cout << "He can only use it once... but its power is immense!" << endl;
    } else {
        cout << "Not enough energy to use Cursed Technique." << endl;
    }
}

void Kashimo::hollowbasket(bool &domainused) {
    if (domainused && cursedenergy >= 100) {
        cursedenergy -= 100;
        cout << "Kashimo uses Hollow Wicker Basket!" << endl;
        evasionDisabled = false;
        basketturnsleft = 2;
    } else {
        cout << "Can't use Hollow Wicker Basket right now." << endl;
    }
}

void Kashimo::recharge(int ticks, int energyPerTick) {
    cout << "Kashimo recharges..." << endl;
    for (int i = 0; i < ticks; ++i) {
        cursedenergy = min(cursedenergy + energyPerTick, maxenergy);
    }
    cout << "Recharge complete." << endl;
}

void Kashimo::launchAttack(Hakari &target) {
    if (cursedenergy >= 500 && health <= 300 && !cursedtechnique) {
        usecursedtechnique();
        staffequip = false;
        return;
    }

    if (!cursedtechnique && !staffequip && !staffbroken) {
        equipstaff();
    }

    if (zoneturnsleft > 0) {
        attack(target);
        zoneturnsleft--;
        return;
    }

    int choice = rand() % 2;
    switch (choice) {
        case 0: attack(target); break;
        case 1: discharge(target, evasionDisabled); break;
    }

    if (cursedenergy < 100) {
        recharge(3, 50);
    }
}


void Hakari::shutterdoors(Kashimo &target) {
    if (cursedenergy >= 200) {
        cursedenergy -= 200;
        bool dummy = domainused;
        target.takedamage(100, dummy);
        cout << "Hakari uses Shutter Doors!" << endl;

        if (domainused) {
            int rng = rand() % 100;
            if (rng < 1) { cout << "Rainbow Doors!!! Jackpot Guaranteed!" << endl; rainbowdoor++; }
            else if (rng < 6) { cout << "Gold Doors!" << endl; golddoor++; }
            else if (rng < 26) { cout << "Red Doors!" << endl; reddoor++; }
            else if (rng < 76) { cout << "Green Doors!" << endl; greendoor++; }
            else { cout << "Regular Doors." << endl; }

            cout << "Visual indicator used inside Domain! Triggering Pachinko Spin..." << endl;
            if (spinPachinko(false)) {
                activateImmortality();
                cout << "For the next 4 minutes and 11 seconds" << endl;
				cout << "Infinite Cursed Energy Flows Through Hakari" << endl;
            } else {
                cout << "Spin failed. No jackpot." << endl;
            }
        }
    } else {
        cout << "Not enough cursed energy for Shutter Doors." << endl;
    }
}

void Hakari::reserveball(Kashimo &target) {
    if (cursedenergy >= 100) {
        cursedenergy -= 100;
        bool dummy = domainused;
        target.takedamage(50, dummy);
        cout << "Hakari uses Reserve Ball!" << endl;

        if (domainused) {
            int rng = rand() % 100;
            if (rng < 1) { cout << "Rainbow Ball!!! Jackpot Guaranteed!" << endl; rainbowball++; }
            else if (rng < 6) { cout << "Gold Ball!" << endl; goldball++; }
            else if (rng < 26) { cout << "Red Ball!" << endl; redball++; }
            else if (rng < 76) { cout << "Green Ball!" << endl; greenball++; }
            else { cout << "Regular Ball!" << endl; }

            cout << "Visual indicator used inside Domain! Triggering Pachinko Spin..." << endl;
            if (spinPachinko(false)) {
                activateImmortality();
                cout << "JackPot Succeded, For the next 4 minutes and 11 seconds" << endl;
				cout << "Infinite Cursed Energy Flows Through Hakari" << endl;
            } else {
                cout << "Spin failed. No jackpot." << endl;
            }
        }
    } else {
        cout << "Can't Use Reserve Ball" << endl;
    }
}

void Hakari::domainexpansion() {
    if (cursedenergy >= 500) {
        cursedenergy -= 500;
        domainused = true;
        domainturnsleft = 5;
        cout << "Domain Expansion: Idle Death Gamble" << endl;

        if (spinPachinko(true)) {
            activateImmortality();
            domainused = false;
            cout << "For the next 4 minutes and 11 seconds" << endl;
			cout << "Infinite Cursed Energy Flows Through Hakari" << endl;
        }
    } else {
        cout << "Not enough energy for Domain Expansion" << endl;
    }
}

void Hakari::tick() {
    if (immortal) {
        immortalTime--;
        if (immortalTime <= 0) {
            cout << "Immortality Ended" << endl;
            immortal = false;
            cursedenergy += 2000;
            if (cursedenergy > maxenergy) cursedenergy = maxenergy;
        }
    }
}

void Hakari::recharge(int ticks, int energyPerTick) {
    cout << "Hakari recharges..." << endl;
    for (int i = 1; i <= ticks; ++i) {
        cursedenergy = min(cursedenergy + energyPerTick, maxenergy);
    }
    cout << "Recharge complete." << endl;
}

void Hakari::attack(Kashimo &target) {
    int basedmg = immortal ? 50 : 35;
    int blackflashbonus = immortal ? 150 : 125;
    double totalChance = (immortal ? 15.0 : 10.0) + zoneturnsleft * 10.0;
    if (totalChance > 100.0) totalChance = 100.0;

    int roll = rand() % 100;
    bool blackflash = roll < totalChance;

    cout << "Black Flash Chance: " << totalChance << "% | Rolled: " << roll << endl;
    cout << "Hakari Attacks Kashimo!" << endl;

    target.takedamage(basedmg, domainused);

    if (blackflash && !domainused) {
        cout << ">> BLACK FLASH << Precision Strike Amplified!" << endl;
        target.takedamage(blackflashbonus, domainused);
        zoneturnsleft++;
        cout << "Zone Stack Count: " << zoneturnsleft << endl;
    }

    if (zoneturnsleft >= 5) {
        zoneturnsleft = 0;
        cursedenergy += 250;
        cout << "[ZONE RESET] Hakari's cursed energy surges!" << endl;
    }
}
void Hakari::launchAttack(Kashimo &target) {
    if (!domainused && cursedenergy >= 500 && !domainOnCooldown && immortalityUses < maxImmortalityUses && !immortal) {
    domainexpansion();
    return;
}

    if (immortal) {
        attack(target);
        return;
    }

    if (domainused) {
        int choice = rand() % 3;
        switch (choice) {
            case 0: attack(target); break;
            case 1: shutterdoors(target); break;
            case 2: reserveball(target); break;
        }
        return;
    }

    if (zoneturnsleft > 0) {
        attack(target);
        zoneturnsleft--;
        return;
    }

    int choice = rand() % 3;
    switch (choice) {
        case 0: attack(target); break;
        case 1: shutterdoors(target); break;
        case 2: reserveball(target); break;
    }

    if (cursedenergy < 100) {
        recharge(3, 50);
    }
}

int main() {
    srand(time(0));
    Hakari Kinji(1500, 1500, 650, 650);
    Kashimo Hajime(2000, 2000, 650, 650);
    int turn = 1;

    while (Kinji.health > 0 && Hajime.health > 0) {
        cout << "\n=== Turn " << turn << " Begins ===" << endl;

        if (Hajime.basketturnsleft > 0) {
            Hajime.basketturnsleft--;
            if (Hajime.basketturnsleft == 0) {
                Hajime.evasionDisabled = true;
                cout << "Hollow Wicker Basket has faded" << endl;
            }
        }

        if (Kinji.domainturnsleft > 0) {
            Kinji.domainTick();
        }
        
			if (Kinji.domainOnCooldown) {
			Kinji.domainCooldownTurns--;
				
				if (Kinji.domainCooldownTurns <= 0) {
					Kinji.domainOnCooldown = false;
					Kinji.domainCooldownTurns = 0;
    }
}

        cout << "\nHakari's Turn:" << endl;
        Kinji.launchAttack(Hajime);
        if (Hajime.health <= 0) {
            cout << "Kashimo has been defeated!" << endl;
            break;
        }

        cout << "\nKashimo's Turn:" << endl;
        Hajime.launchAttack(Kinji);
        if (Kinji.health <= 0) {
            cout << "Hakari has been defeated!" << endl;
            break;
        }

        Kinji.tick();
        turn++;
    }

    return 0;
}
