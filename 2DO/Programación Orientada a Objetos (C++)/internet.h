// =========================================================
// File: vox.h
// Author:  Guadalupe Paulina López Cuevas  A01701095
// Date:
// Description:
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 1.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int) override;
  double calculateMessageCost(int, int, int) override;
  double calculateNetworkCost(double) override;
};

//Clase hijo (InternetOperator) invoca a la clase padre (Operator) con sus parametros
InternetOperator::InternetOperator(int id2, double costXmincall, double costXenv, double costXgb, int porcDesc, OperatorType operTipo)
  :Operator(id2, costXmincall, costXenv, costXgb, porcDesc, operTipo){}

InternetOperator::InternetOperator(const InternetOperator &other):Operator(other){}

double InternetOperator::calculateTalkingCost(int minute, int age){
  if(minute <= 0 || age <= 0){
    return 0;
  }else if(minute < 2){
    return ((minute*talkingCharge) - ((minute*talkingCharge)*(discountRate/100.0)));
  }else{
    return (minute*talkingCharge);
  }
}

double InternetOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId){
  if(quantity <= 0){
    return 0;
  }else if(quantity < 3){
    return ((quantity*talkingCharge) - ((quantity*talkingCharge)*(discountRate/100.0)));
  }else{
    return (quantity*talkingCharge);
  }
}

double InternetOperator::calculateNetworkCost(double amount){
  if(amount <= 0){
    return 0;
  }
  if(amount > LIMITGB){
    return((amount-LIMITGB) * networkCharge);
  }else{
    return 0;
  }
}
#endif
