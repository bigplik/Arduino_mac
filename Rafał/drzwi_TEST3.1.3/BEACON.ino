#define BEACON    digitalWrite(10,1)
#define notBEACON digitalWrite(10,0)

void beacon(){
  BEACON;
}

void notBeacon(){
  notBEACON;
}

