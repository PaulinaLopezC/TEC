// =========================================================
// File: customer.h
// Author: Guadalupe Paulina López Cuevas  A01701095
// Date:
// Description:
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator* op;
  Bill *bill;

public:
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  bool operator==(const Customer&);

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
};

Customer::Customer(int id2, std::string name2, int age2, Operator* op2, double limitA){
  id = id2;
  name = name2;
  age = age2; 
  op = op2;
  bill = new Bill(limitA);
  totalSpentTalkingTime = totalMessageSent = totalInternetUsage = 0;
}

Customer::Customer(const Customer &other){
  id = other.id;
  name = other.name;
  age = other.age;
  op = other.op;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
}

Customer::~Customer(){
  delete bill;
  op = nullptr;
  bill = nullptr;
}

int Customer::getId() const{
  return id;
}

int Customer::getAge() const{
  return age;
}

int Customer::getTotalSpentTalkingTime() const{
  return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const{
  return totalMessageSent;
}

double Customer::getTotalInternetUsage() const{
  return totalInternetUsage;
}

std::string Customer::getName() const{
  return name;
}

Operator* Customer::getOperator() const{
  return op;
}

Bill* Customer::getBill() const{
  return bill;
}

void Customer::setOperator(Operator* op2){
  op = op2;
}

std::string Customer::toString() const{
  std::stringstream aux;
  aux << "Customer " << id << " : " << std::fixed << std::setprecision(2) << bill->getTotalMoneySpent()
      << " " << std::fixed << std::setprecision(2) << bill->getCurrentDebt();
	return aux.str();
}

bool Customer::operator==(const Customer &other){
  return(id == other.id);
}

void Customer::talk (int minutes, Customer &other){
  double cost;
  if (minutes <= 0) {
    return;
  }
  
  if(id != other.id){
    cost = op->calculateTalkingCost(minutes, age);
    if(bill->check(cost) == true){
      bill->add(cost);
      totalSpentTalkingTime += minutes;
      op->addTalkingTime(minutes);
      if(op->getId() != other.op->getId()){
          other.op->addTalkingTime(minutes);
      }
    }
  }
}

void Customer::message(int quantity, const Customer &other){
  double cost;
  if(quantity <= 0){
    return;
  }
  if(id != other.id){
    cost = op->calculateMessageCost(quantity,op->getId(),other.op->getId());
    if((bill->check(cost) == true)){
      bill->add(cost);
      totalMessageSent += quantity;
      op->addTotalMessageSent(quantity);
    }
  }
}

void Customer::connection(double amount){
  double cost;
  if(amount > 0){
    cost = op->calculateNetworkCost(amount);
    if(bill->check(cost) == true){
      bill->add(cost);
      totalInternetUsage += amount;
      op->addTotalInternetUsage(amount);
    }
  }
}

#endif
