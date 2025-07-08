#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Sukuna; // Forward declaration

class Gojo {
public:
    int cursedenergy, maxenergy, health, maxhp, skillimit;
    int evasion = 70;
    int simpledomainturnsleft = 0;
    bool simpledomainActive = false;
    bool evasionDisabled = false;

    Gojo(int e, int max, int h, int hp)
        : cursedenergy(e), maxenergy(max), health(h), maxhp(hp), skillimit(0) {}

    void takedamage(int dmg) {
        if (!evasionDisabled) {
            int roll = rand() % 100;
            if (roll > evasion) {
                cout << "Attack dodged!" << endl;
                return;
            }
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << "Remaining HP: " << health << endl;
    }

    void limit(int techniquelimit) {
        skillimit = techniquelimit;
    }

    void attack(Sukuna &target);
    void launchBlue(Sukuna &target);
    void launchRed(Sukuna &target);
    void launchHollowPurple(Sukuna &target);
    void domainExpansion(Sukuna &target, bool &gojousedDomain, int &gojodomainlevel);
    void recharge(int ticks, int energyPerTick);
    void regenerate();
    void launchRandomAttack(Sukuna &target, bool &gojousedDomain, int &gojodomainlevel);
    void SimpleDomain();
};

class Sukuna {
public:
    int cursedenergy, maxenergy, health, maxhp, stunnedturns, skillimit;
    int evasion = 70;
    bool evasionDisabled = false;

    Sukuna(int e, int max, int h, int hp)
        : cursedenergy(e), maxenergy(max), health(h), maxhp(hp), stunnedturns(0), skillimit(0) {}

    void takedamage(int dmg) {
        if (!evasionDisabled) {
            int roll = rand() % 100;
            if (roll > evasion) {
                cout << "Attack dodged!" << endl;
                return;
            }
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << "Remaining HP: " << health << endl;
    }

    void stun(int limit) {
        stunnedturns = limit;
        cout << "Sukuna is stunned for " << limit << " turn(s)!" << endl;
    }

    void limit(int techniquelimit) {
        skillimit = techniquelimit;
    }

    void attack(Gojo &target) {
        target.takedamage(50);
        cout << "Sukuna Attacks Gojo!" << endl;
        if (rand() % 10 == 0) {
            cout << "Black Flash" << endl;
            target.takedamage(150);
        }
    }

    void shrine(Gojo &target) {
        if (cursedenergy >= 200) {
            cout << "Shrine" << endl;
            cursedenergy -= 200;
            target.takedamage(100);
        }
    }

    void cleave(Gojo &target) {
        if (cursedenergy >= 300) {
            cout << "Dismantle and Cleave" << endl;
            cursedenergy -= 300;
            target.takedamage(130);
        }
    }

    void firearrow(Gojo &target) {
        if (cursedenergy >= 600) {
            cout << "Divine Flame" << endl;
            cursedenergy -= 600;
            target.takedamage(250);
        }
    }

    void malevolentshrine(Gojo &target, int &dotRef, bool &gojousedDomain, bool &sukunausedDomain, int &sukunadomainlevel) {
        if (cursedenergy >= 1200) {
            cout << "Domain Expansion\nOpen Barrier: Malevolent Shrine" << endl;
            cursedenergy -= 1200;
            if (target.cursedenergy >= 300 && !target.simpledomainActive && gojousedDomain == false) {
                target.SimpleDomain();
                dotRef = 0;
                sukunausedDomain = true;
                sukunadomainlevel = 2;
            } else {
                target.evasionDisabled = true;
                limit(2);
                dotRef = 2;
                sukunausedDomain = true;
                sukunadomainlevel = 2;
            }
        } else if (cursedenergy >= 800) {
            cout << "Domain Expansion\nMalevolent Shrine" << endl;
            cursedenergy -= 800;
            if (target.cursedenergy >= 300 && !target.simpledomainActive && gojousedDomain == false) {
                target.SimpleDomain();
                dotRef = 0;
                sukunausedDomain = true;
                sukunadomainlevel = 1;
            } else {
                target.evasionDisabled = true;
                limit(2);
                dotRef = 2;
                sukunausedDomain = true;
                sukunadomainlevel = 1;
            }
        }
    }

    void regenerate() {
        if (cursedenergy >= 100) {
            cout << "Sukuna regenerates his body" << endl;
            cursedenergy -= 100;
            int heal = rand() % 51 + 100;
            health += heal;
            if (health > maxhp) health = maxhp;
            cout << "Healed: " << heal << ", Current HP: " << health << endl;
        } else {
            cout << "Too weak to regenerate" << endl;
        }
    }

    void recharge(int ticks, int energyPerTick) {
        cout << "Sukuna absorbs cursed energy..." << endl;
        for (int i = 1; i <= ticks; ++i) {
            cursedenergy = min(cursedenergy + energyPerTick, maxenergy);
        }
        cout << "Recharge complete.\n" << endl;
    }

    void launchrandomattack(Gojo &target, int &dotRef, bool &gojousedDomain, bool &sukunausedDomain, int &sukunadomainlevel) {
        if (stunnedturns > 0) {
            cout << "Sukuna is stunned and cannot attack this turn" << endl;
            stunnedturns--;
            return;
        }
        if (skillimit > 0) {
            attack(target);
            skillimit--;
            if (skillimit == 0) evasionDisabled = false;
            return;
        }

        int choice = rand() % 6;
        switch (choice) {
            case 0: shrine(target); break;
            case 1: cleave(target); break;
            case 2: firearrow(target); break;
            case 3: malevolentshrine(target, dotRef, gojousedDomain, sukunausedDomain, sukunadomainlevel); break;
            case 4: regenerate(); break;
            case 5: attack(target); break;
        }
        if (cursedenergy < 100) recharge(3, 50);
    }
};

void Gojo::attack(Sukuna &target) {
    target.takedamage(50);
    cout << "Gojo Attacks Sukuna!" << endl;
    if (rand() % 10 == 0) {
        cout << "Black Flash" << endl;
        target.takedamage(150);
    }
}

void Gojo::launchBlue(Sukuna &target) {
    if (cursedenergy >= 200) {
        cout << "Phase, Twilight, Eyes of Wisdom\nCursed Technique Lapse Maximum Output: Blue" << endl;
        cursedenergy -= 200;
        target.takedamage(80);
    } else if (cursedenergy >= 50) {
        cout << "Cursed Technique Lapse: Blue" << endl;
        cursedenergy -= 50;
        target.takedamage(180);
    } else cout << "Not enough energy for Blue." << endl;
}

void Gojo::launchRed(Sukuna &target) {
    if (cursedenergy >= 400) {
        cout << "Phase, Paramita, Pillar of Light\nCursed Technique Reversal Maximum Output: Red" << endl;
        cursedenergy -= 400;
        target.takedamage(120);
    } else if (cursedenergy >= 100) {
        cout << "Cursed Technique Reversal: Red" << endl;
        cursedenergy -= 100;
        target.takedamage(250);
    } else cout << "Not enough energy for Red." << endl;
}

void Gojo::launchHollowPurple(Sukuna &target) {
    if (cursedenergy >= 800) {
        cout << "Nine Ropes, Polarized Light, Crow and Declaration, Between Front and Back\n200% Hollow Purple" << endl;
        cursedenergy -= 800;
        target.takedamage(400);
    } else if (cursedenergy >= 200) {
          cout << "Cursed Technique Lapse: Blue" << endl;
          cout << "Cursed Technique Reversal: Red" << endl;
          cout << "Hollow Purple" << endl;
        cursedenergy -= 200;
        target.takedamage(600);
    } else cout << "Not enough energy for Hollow Purple." << endl;
}

void Gojo::domainExpansion(Sukuna &target, bool &gojousedDomain, int &gojodomainlevel) {
    if (cursedenergy >= 900) {
        cout << "Domain Expansion\nUnlimited Void" << endl;
        cursedenergy -= 900;
        target.stun(2);
        limit(3);
        gojousedDomain = true;
        gojodomainlevel = 2;
    } else if (cursedenergy >= 500) {
        cout << "Domain Expansion\n0.2 Unlimited Void" << endl;
        cursedenergy -= 500;
        target.stun(1);
        limit(1);
        gojousedDomain = true;
        gojodomainlevel = 1;
    } else cout << "Not enough energy for Domain Expansion." << endl;
}

void Gojo::SimpleDomain() {
    simpledomainActive = true;
    simpledomainturnsleft = 1;
    cursedenergy -= 300;
    limit(2);
    cout << "New Shadow Style: Simple Domain" << endl;
}

void Gojo::recharge(int ticks, int energyPerTick) {
    cout << "Gojo recharges..." << endl;
    for (int i = 1; i <= ticks; ++i) {
        cursedenergy = min(cursedenergy + energyPerTick, maxenergy);
    }
    cout << "Recharge complete." << endl;
}

void Gojo::regenerate() {
    if (cursedenergy >= 100) {
        cout << "Gojo performs Reversed Cursed Technique" << endl;
        cursedenergy -= 100;
        int heal = rand() % 51 + 100;
        health += heal;
        if (health > maxhp) health = maxhp;
        cout << "Healed: " << heal << ", Current HP: " << health << endl;
    } else cout << "Too weak to perform" << endl;
}

void Gojo::launchRandomAttack(Sukuna &target, bool &gojousedDomain, int &gojodomainlevel) {
    if (skillimit > 0) {
        attack(target);
        skillimit--;
        return;
    }
    int choice = rand() % 6;
    switch (choice) {
        case 0: launchBlue(target); break;
        case 1: launchRed(target); break;
        case 2: launchHollowPurple(target); break;
        case 3: domainExpansion(target, gojousedDomain, gojodomainlevel); break;
        case 4: regenerate(); break;
        case 5: attack(target); break;
    }
    if (cursedenergy < 100) recharge(3, 50);
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

        if (gojousedDomain && sukunausedDomain) {
            cout << "\nDomain Clash! Malevolent Shrine vs Unlimited Void!" << endl;
            if (gojodomainlevel == 1 || sukunadomainlevel == 2) {
                gojoDoTturns = 2;
            } else {
                int gojoPower = Satoru.cursedenergy + rand() % 100;
                int sukunaPower = Ryomen.cursedenergy + rand() % 100;
                cout << "Gojo's Energy: " << gojoPower << ", Sukuna's Energy: " << sukunaPower << endl;
                if (gojoPower > sukunaPower) {
                    cout << "Gojo's Unlimited Void crushes Sukuna's Shrine" << endl;
                    Ryomen.stun(2);
                    Ryomen.limit(0);
                    gojoDoTturns = 0;
                } else if (sukunaPower > gojoPower) {
                    cout << "Sukuna's Shrine crushes Infinite Void!" << endl;
                    gojoDoTturns = 2;
                    Satoru.limit(0);
                } else {
                    cout << "Both Domains shatter in equal force! Both are hit!" << endl;
                    Satoru.takedamage(200);
                    Ryomen.takedamage(200);
                }
            }
            gojousedDomain = sukunausedDomain = false;
            gojodomainlevel = sukunadomainlevel = 0;
        }

        if (gojoDoTturns > 0) {
            cout << "Slicing barrage from Malevolent Shrine hits Gojo!" << endl;
            Satoru.takedamage(100);
            gojoDoTturns--;
        }

        cout << "\nGojo Attacks!" << endl;
        Satoru.launchRandomAttack(Ryomen, gojousedDomain, gojodomainlevel);
        if (Ryomen.health <= 0) {
            cout << "Sukuna has been defeated!" << endl;
            break;
        }

        cout << "\nSukuna Attacks!" << endl;
        Ryomen.launchrandomattack(Satoru, gojoDoTturns, gojousedDomain, sukunausedDomain, sukunadomainlevel);
        if (Satoru.health <= 0) {
            cout << "Gojo has been defeated!" << endl;
            break;
        }

        turn++;
    }
    return 0;
}
