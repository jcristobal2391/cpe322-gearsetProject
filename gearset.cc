/*
  Jon Cristobal, Stevens Institute of Technology
  Jude Kirisame, Faerie, Aether Data Center
  Last Updated 2019-11-17
  Test Values:
  Weapon Damage: 164
  Intelligence: 4240
  Spellspeed: 380
  Critical Hit: 3279
  Direct Hit: 2937
  Determination: 1943
 */
#include <iostream>
using namespace std;

int enkindle= 320;
int miasma3 = 550;
int bio3 = 400;
double devotion = 1.05;
int ea1 = 200;
int ea2 = 200;
int bs = 64;
int enerD = 100;
int r3 = 200;
int r2 = 160;
int r4 = 300;
int pf = 130;
int fest = 300;
int enerS = 40;
int tri = 300;
int death = 400;

double det, dHit, cHit, spell, intel, weap, trait, directDmg, critDmg;


int triDisaster(int pot){
  int triD = tri + miasma3 + bio3;
  pot += triD;
  return pot;
}

int baha(int pot){
  int ww = 120;
  int ahkMorn = 520;
  pot = triDisaster(pot);
  pot = (ww * 8) + pot;
  pot = (ahkMorn *2) + pot + (fest*2) + enerD + (r3*4) + (r4*3);
  return pot;
}

int opener(int pot){
  pot = triDisaster(pot);
  pot = (ea1 * 2) + (ea2 * 2) + r3 + (bs * 4) + enerD + fest + enkindle + death;
  pot = baha(pot);
  return pot;
}

int fill1(int pot){
  pot = triDisaster(pot);
  pot = (r3 * 10) + (bs * 12) + miasma3 + bio3 + (ea1 * 2) + ea2 + (fest * 2) + enerD + pot;
  return pot;
}

int phoe(int pot){
  int sf = 120;
  int revelation = 520;
  int fof = 250;
  int bop = 350;
  pot = (fof * 4) + (bop * 4) + (sf * 8) + (revelation * 2) + pot + r4 + fest + enerD;
  return pot;
}

int fill2(int pot){
  pot = triDisaster(pot);
  pot = (11 * bs) + (r3 * 9) + pot + (2 * ea2) + ea1 + r4 + enerD + (2*fest);
  return pot;
}

double weapCalc(double weap, double intel){
  weap = weap + (340 * 115 /1000.0);
  intel =100 + (intel - 340) *165.0 / 340.0;
  weap = weap * intel;
  weap = weap / 100 / 100;
  return weap;
}

double critCalc(double cHit){
  cHit -= 380;
  cHit = 200 * cHit / 3300.0 + 50;
  cHit = cHit / 1000.0;
  return cHit;
}

double critDmgCalc(double critDmg){
  critDmg -= 380;
  critDmg = 200 *( critDmg / 3300.0) + 1600;
  critDmg = critDmg / 1000.0;
  return critDmg;
}

double directCalc(double dHit){
  dHit -= 380;
  dHit = 550 * dHit / 3300.0 / 1000.0;
  return dHit;
}

double detCalc(double det){
  det = det - 340;
  det = det / 3300.0;
  det *= 130;
  det += 1000;
  det = det / 1000;
  return det;
}

double norm(){
  double a;
  a = 1 - cHit - dHit + (cHit * dHit);
  return a;
}

double crit(){
  double a;
  a = critDmg * (cHit - (cHit * dHit));
  return a;
}

double dh(){
  double a;
  a = directDmg * (dHit - (cHit * dHit));
  return a;
}

double cdh(){
  double a;
  a = cHit * dHit * critDmg * directDmg;
  return a;
}

double dpsCalc(int pot, double edmg, double time){
  double dps;
  dps = trait * det * weap * edmg * pot;
  dps = dps / time;
  return dps;
}

int main(){
  trait = 1.3;
  directDmg = 1.25;
  cout << "Please input Weapon Damage: ";
  cin >> weap;
  
  cout << "Please input INT: ";
  cin >> intel;
  
  cout << "Please input Spellspeed: ";
  cin >> spell;
    
  cout << "Please input Critical Hit: ";
  cin >> cHit;
    
  cout << "Please input Direct Hit: ";
  cin >> dHit;
    
  cout << "Please input Determination: ";
  cin >> det;
  cout << "\n";

  cout << "Weapon Damage: " << weap << "\n";
  cout << "Intelligence: " << intel << "\n";
  cout << "Spellspeed: " << spell << "\n";
  cout << "Critical Hit: " << cHit << "\n";
  cout << "Direct Hit: " << dHit << "\n";
  cout << "Determination: " << det << "\n";
  cout << "\n";

  weap = weapCalc(weap, intel);
  cHit = critCalc(cHit);
  critDmg = critDmgCalc(cHit);
  dHit = directCalc(dHit);
  det = detCalc(det);

  double edmg = norm() + crit() + dh() + cdh();
  
  int potency = 0;
  potency = opener(potency);
  cout << "Potency after opener is: " << potency<< "\n";
  cout << "Damage per Second is: " << dpsCalc(potency, edmg, 32.8) << "\n";

  potency = fill1(potency);
  cout << "Potency after filler 1 is: " << potency<< "\n";
  cout << "Damage per Second is: " << dpsCalc(potency, edmg, 71.4) << "\n";

  potency = phoe(potency);
  cout << "Potency after phoenix is: " << potency<< "\n";
  cout << "Damage per Second is: " << dpsCalc(potency, edmg, 93.9) << "\n";
  
  potency = fill2(potency);
  cout << "Potency after filler 2 is: " << potency<< "\n";
  cout << "Damage per Second is: " << dpsCalc(potency, edmg, 127.3) << "\n";
  cout << "\n";
  
  cout << "Total potency is: " << potency << "\n";
  cout << "Damage per Second is: " << dpsCalc(potency, edmg, 127.3) << "\n";
}
