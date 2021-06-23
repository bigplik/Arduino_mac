
    int ocena = 5;
    int cena;

void setup(){}

void loop(){
  
    if(digitalRead(10 == HIGH)){
      
      ocena += ocena + 1;
      
      
    }

    if(ocena == 3){
        cena = 'A';
    }else if(ocena == 4){
        ocena = 3;
        cena = 'B';
    }

    switch(ocena){
        case 1:
            printf("SWITCH: Jedynka\n");
            break;
        case 2:
            printf("SWITCH: Dwójka\n");
            break;
        case 3:
            switch(cena){
                case 'A':
                    printf("SWITCH: A");
                    break;
                case 'B':
                    printf("SWITCH: B");
                    break;
                default:
                printf("SWITCH: Nieznana ocena\n");
            }
            break;
        case 5:
            printf("SWITCH: Czwórka\n");
            break;
        case 6:
            printf("SWITCH: Piątka\n");
            break;
        case 7:
            printf("SWITCH: Szóstka\n");
            break;
        default:
            printf("SWITCH: Nieznana ocena\n");
    }
    
}
