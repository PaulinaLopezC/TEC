// =========================================================
// File: main.cpp
// Author:  Guadalupe Paulina López Cuevas  A01701095
// Date:
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv[]) {
  ifstream inputFile;
  ofstream outputFile;
  vector <Customer*> customers;
  vector <Operator*> operators;
  int idCustomer = 0, idOperator = 0, C, O, N;

  if (argc != 3) {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open()) {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);
  
  inputFile >> C >> O >> N;
  customers.resize(C);
  operators.resize(O);

  for(int i = 0; i < N; i++ ){
    int oper, x, y, z;
    double xd, yd, zd;
    std::string name;

    inputFile >> oper;
    switch(oper){
      case 1:
        inputFile >> name >> x >> y >> xd;
        customers[idCustomer] = new Customer(idCustomer, name, x, operators[y], xd);
        idCustomer++;
        break;
      case 2:
        inputFile >> x >> xd >> yd >> zd >> y;
        switch(x){
          case 1:
            operators[idOperator] = new VoxOperator(idOperator, xd, yd, zd, y, VOX);
            idOperator++;
            break;
          case 2:
            operators[idOperator] = new InternetOperator(idOperator, xd, yd, zd, y, INTERNET);
            idOperator++;
            break;
        }
        break;
      case 3:
        inputFile >> x >> y >> z;
        customers[x]->talk(z, *customers[y]);
        break;
      case 4:
        inputFile >> x >> y >> z;
        customers[x]->message(z, *customers[y]);
        break;
      case 5:
        inputFile >> x >> xd;
        customers[x]->connection(xd);
        break;
      case 6:
        inputFile >> x >> xd;
        customers[x]->getBill()->pay(xd);
        break;
      case 7:
        inputFile >> x >> y;
        customers[x]->setOperator(operators[y]);
        break;
      case 8:
        inputFile >> x >> xd;
        customers[x]->getBill()->changeTheLimit(xd);
        break;
    }
  }

  for(int i = 0; i < idOperator; i++){
    outputFile << operators[i]->toString() << endl;
  }
  for(int i = 0; i < idCustomer; i++){
    outputFile << customers[i]->toString() << endl;
  }

  int max = 0;
  int idCliente = 0;
  for(int i = 0; i < customers.size(); i++){
    int tiempoHablado = customers[i]->getTotalSpentTalkingTime();
    if(max < tiempoHablado){
      max = tiempoHablado;
      idCliente = i;
    }else if(max == tiempoHablado){
      if(i < idCliente){
        idCliente = i;
      }
    }
  }
  outputFile << customers[idCliente]->getName() << " : " << customers[idCliente]->getTotalSpentTalkingTime() << endl;
  
  max = idCliente = 0;

  for(int i = 0; i < customers.size(); i++){
    int numMensajes = customers[i]->getTotalMessageSent();
    if(max < numMensajes){
      max = numMensajes;
      idCliente = i;
    }else if(max == numMensajes){
      if(i < idCliente){
        idCliente = i;
      }
    }
  }
  outputFile << customers[idCliente]->getName() << " : " << customers[idCliente]->getTotalMessageSent() << endl;

  idCliente = 0;
  double num = 0.0;

  for(int i = 0; i < customers.size(); i++){
    int numGB = customers[i]->getTotalInternetUsage();
    if(num < numGB){
      num = numGB;
      idCliente = i;
    }else if(num == numGB){
      if(i < idCliente){
        idCliente = i;
      }
    }
  }
  outputFile << customers[idCliente]->getName() << " : " << std::fixed << std::setprecision(2) << customers[idCliente]->getTotalInternetUsage() << endl;

  inputFile.close();
  outputFile.close();
  return 0;
}
