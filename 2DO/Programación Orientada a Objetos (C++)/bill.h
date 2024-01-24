// =========================================================
// File: bill.h
// Author: Guadalupe Paulina López Cuevas  A01701095
// Date:
// Description:
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill {
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

  Bill::Bill(){
    limitAmount = 0.0;
    currentDebt = 0.0;
    totalMoneySpent = 0.0;
  }

  Bill::Bill(double limA){
    if(limA > 0){
      limitAmount = limA;
    }else{
      limitAmount = 0;
    }
    currentDebt = 0.0;
    totalMoneySpent = 0.0;
  }
  Bill::Bill(const Bill &other){
    limitAmount = other.limitAmount;
    currentDebt = other.currentDebt;
    totalMoneySpent = other.totalMoneySpent;
  }

  double Bill::getLimitAmount() const{
    return limitAmount;
  }

  double Bill::getCurrentDebt() const{
    return currentDebt;
  }

  double Bill::getTotalMoneySpent() const{
    return totalMoneySpent;
  }

  void Bill::add(double amount){
    if(amount > 0){
      currentDebt += amount;
    }
  }

  void Bill::pay(double amount){
    if(amount < currentDebt && amount > 0){
      currentDebt -= amount;
      totalMoneySpent += amount;
    }else if (amount >= currentDebt){
      totalMoneySpent += currentDebt;
      currentDebt = 0.0;
    }
    
  }

  void Bill::changeTheLimit(double amount){
    if(amount > currentDebt && amount > 0){
      limitAmount = amount;
    }
  }

  bool Bill::check(double amount) const{
    double sum = amount + currentDebt;
    return sum < limitAmount;
  }

#endif
