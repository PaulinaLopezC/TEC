// =========================================================
// File: operator.h
// Author:  Guadalupe Paulina López Cuevas  A01701095
// Date:
// Description:
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingChage() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  std::string toString() const;

  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

Operator::Operator(int id2, double costXmincall, double costXenv, double costXgb, int porcDesc, OperatorType operTipo){
  id = id2;
  discountRate = porcDesc;
  talkingCharge = costXmincall;
  messageCost = costXenv;
  networkCharge = costXgb;
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  totalInternetUsage = 0.0;
  type = operTipo;
}

Operator::Operator(const Operator &other){
  id = other.id;
  discountRate = other.discountRate;
  talkingCharge = other.talkingCharge;
  messageCost = other.messageCost;
  networkCharge = other.networkCharge;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
  type = other.type;
}

int Operator::getId() const{
  return id;
}

int Operator::getDiscountRate() const{
  return discountRate;
}

double Operator::getTalkingChage() const{
  return talkingCharge;
}

double Operator::getMessageCost() const{
  return messageCost;
}

double Operator::getNetworkCharge() const{
  return networkCharge;
}

int Operator::getTotalSpentTalkingTime() const{
  return totalSpentTalkingTime;
}

int Operator::getTotalMessageSent() const{
  return totalMessageSent;
}

double Operator::getTotalInternetUsage() const{
  return totalInternetUsage;
}

OperatorType Operator::getType() const{
  return type;
}

void Operator::addTalkingTime(int minute){
  if (minute > 0){
    totalSpentTalkingTime += minute;
  }
}

void Operator::addTotalMessageSent(int quantity){
  if (quantity > 0){
    totalMessageSent += quantity;
  }
}

void Operator::addTotalInternetUsage(double amount){
  if (amount > 0){
    totalInternetUsage += amount;
  }
}

std::string Operator::toString() const{
  std::stringstream aux;
  aux << "Operator " << getId() << " : " << getTotalSpentTalkingTime() << " " << getTotalMessageSent()
      << " " << std::fixed << std::setprecision(2) << getTotalInternetUsage();
	return aux.str();
} 

#endif
