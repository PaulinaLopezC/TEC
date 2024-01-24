// =========================================================
// File: vox.h
// Author:  Guadalupe Paulina López Cuevas  A01701095
// Date:
// Description:
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int) override;
  double calculateMessageCost(int, int, int) override;
  double calculateNetworkCost(double) override;
};

//Clase hijo (VoxOperator) invoca a la clase padre (Operator) con sus parametros
VoxOperator::VoxOperator(int id2, double costXmincall, double costXenv, double costXgb, int porcDesc, OperatorType operTipo)
  :Operator(id2, costXmincall, costXenv, costXgb, porcDesc, operTipo){}

VoxOperator::VoxOperator(const VoxOperator &other):Operator(other){}

double VoxOperator::calculateTalkingCost(int minute, int age){
  if( minute <= 0 || age <= 0){
    return 0;
  }else if (age < 18 || age > 65){
    return ((minute*talkingCharge) - ((minute*talkingCharge)*(discountRate/100.0)));
  }else{
    return (minute*talkingCharge);
  }
}
  
double VoxOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId){
  if(quantity <= 0){
    return 0;
  }else if(thisOpId == otherOpId){
    return((quantity*messageCost) - ((quantity*messageCost)*(discountRate/100.0)));
  }else{
    return (quantity*messageCost);
  }
}

double VoxOperator::calculateNetworkCost(double amount){
  if(amount > 0){
    return (amount*networkCharge);
  }else{
    return 0;
  }
}

#endif
