#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Gojo {
public:
    int cursedenergy;
    int maxenergy;

    Gojo(int e, int max) {
        cursedenergy = e;
        maxenergy = max;
    }

    void launchBlue() {
        if (cursedenergy >= 200) {
            cout << "Phase, Twilight, Eyes of Wisdom" << endl;
            cout << "Cursed Technique Lapse Maximum Output: Blue" << endl;
            cursedenergy -= 200;
        } else if (cursedenergy >= 50) {
            cout << "Cursed Technique Lapse: Blue" << endl;
            cursedenergy -= 50;
        } else {
            cout << "Not enough energy for Blue." << endl;
        }
    }

    void launchRed() {
        if (cursedenergy >= 400) {
            cout << "Phase, Paramita, Pillar of Light" << endl;
            cout << "Cursed Technique Reversal Maximum Output: Red" << endl;
            cursedenergy -= 400;
        } else if (cursedenergy >= 100) {
            cout << "Cursed Technique Reversal: Red" << endl;
            cursedenergy -= 100;
        } else {
            cout << "Not enough energy for Red." << endl;
        }
    }

    void launchHollowPurple() {
        if (cursedenergy >= 800) {
            cout << "Nine Ropes, Polarized Light, Crow and Declaration, Between Front and Back" << endl;
            cout << "200% Hollow Purple" << endl;
            cursedenergy -= 800;
        } else if (cursedenergy >= 200) {
            cout << "Cursed Technique Lapse: Blue" << endl;
            cout << "Cursed Technique Reversal: Red" << endl;
            cout << "Hollow Purple" << endl;
            cursedenergy -= 200;
        } else {
            cout << "Not enough energy for Hollow Purple." << endl;
        }
    }

    void domainExpansion() {
        if (cursedenergy >= 500) {
            cout << "Domain Expansion" << endl;
            cout << "Infinite Void" << endl;
            cursedenergy -= 500;
        } else {
            cout << "Not enough energy for Domain Expansion." << endl;
        }
    }

    void recharge(int ticks, int energyPerTick) {
        cout << "Gojo begins recharging..." << endl;
        for (int i = 1; i <= ticks; ++i) {
            cursedenergy += energyPerTick;
        }
        cout << "Recharge complete." << endl << endl;
    }

    void launchRandomAttack() {
        int choice = rand() % 4;
        switch (choice) {
            case 0: launchBlue(); break;
            case 1: launchRed(); break;
            case 2: launchHollowPurple(); break;
            case 3: domainExpansion(); break;
        }
         if (cursedenergy < 100) {
        recharge(3, 50); 
    }
   }
};

int main() {
    srand(time(0));
    Gojo satoru(2000, 3000);

    for (int i = 0; i < 10; i++) {
        satoru.launchRandomAttack();
    }
    

    return 0;
}


	
				
		
	
	
	
