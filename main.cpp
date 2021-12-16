#include "logic.h"

class Hopper
{
public:
    int beanGrams;
    Hopper(){beanGrams = 0;}

	int Filling()
    {
        if(this->beanGrams < 200){
        this->beanGrams = 200;
        std::cout << "The hopper has fully filled!" << std::endl;
        DisplayBeanAmount();
        return beanGrams;
        }
        else{
        std::cout << "It's full of beans already." << std::endl;
        return beanGrams;
        }
    }

    void DisplayBeanAmount()
    {
        std::cout << "The amount of coffee beans in hopper are: " << (this->beanGrams) << " grams." << std::endl;
        return;
    }
};

class Grinder
{
public: 
    Grinder(){}
    Hopper GrindCoffee(Hopper *hopper)
    {
        hopper->beanGrams -= 50;
        std::cout << "The grinder griding 50 grams of bean from hopper." << std::endl;
	    return *hopper;
    }
};

class WaterReserv
{
public:
    float water;
    int temperature;

    WaterReserv(){water = 0.0f; temperature = 0;}

    float FullFill()
    {
        this->water = 1.0f;
        std::cout << "The water is fully refilled!" << std::endl;
        DisplayWaterAmount();
        return water;
    }

    void DisplayWaterAmount()
    {
        std::cout << "The amount of water in reservoir is: " << (this->water) << " liters." << std::endl;
        return;
    }

    float PouringWater(){
        if(this->temperature == 100){
        this->water -= .25f;
        std::cout << ".25 liters of water has been poured into the cup." << std::endl;
        }
        return water;
    }
};

class HeatSource
{
private:
	int temperature;
    
public: 
    HeatSource(){temperature = 0;}

    WaterReserv HeatingProcess(WaterReserv *waterRe){
        std::cout << "Heating Start!" << std::endl;
        this->temperature = 100;
        std::cout << "Water enters the reservoir now!" << std::endl;
        std::cout << "Boilng Start!" << std::endl;
        waterRe->temperature = 100;
        std::cout << "Water is boling!" << std::endl;

        return *waterRe;
    }
};

class Cup 
{
public:
    Cup(){}

    bool MakeCoffee(Grinder *gr, WaterReserv *wr, Hopper *hp, HeatSource *hs){
        
        if(wr->water < 0.25f){
            wr->FullFill();
        }
        if(hp->beanGrams < 50){
             hp->Filling();
        }

        if(wr->water >= 0.25f && hp->beanGrams >= 50){
            gr->GrindCoffee(hp);
            if(wr->temperature < 100)
            {
                hs->HeatingProcess(wr);
            }
            wr->PouringWater();
            std::cout << "A cup of coffee have been made." << std::endl;

            wr->DisplayWaterAmount();
            hp->DisplayBeanAmount();

            return true;
            }
    
        return false;
    }

};

class CoffeeMaker{
private:
public:
    Hopper *h;
    Grinder *g;
    WaterReserv *w;
    HeatSource *hs;
    Cup *c;

    CoffeeMaker(){
        h = new Hopper();
        g = new Grinder();
        w = new WaterReserv();
        hs = new HeatSource();
        c = new Cup();
    }

    ~CoffeeMaker(){
        delete h;
        delete g;
        delete w;
        delete hs;
        delete c;
    }

    bool requestCoffee(int n){
        h->DisplayBeanAmount();
        w->DisplayWaterAmount();
        if(n <= 4)
        {
            std::cout << "You ordered " << n << " cups of coffee." << std::endl;
            for(int i = 0; i < n; i++){
                c->MakeCoffee(g, w, h, hs);
            }
            std::cout << "Order done." << std::endl;
            std::cout << "Thank you, come again!" << std::endl;
            return true;
        }
        std::cout << "You ordered " << n << " cups of coffee." << std::endl;
        std::cout << "I can make up to 4 cups of coffee, please re-order it." << std::endl;
        return false;
    }

};

int main() {

    CoffeeMaker cm;
    int n = 0;
    bool isVaild = false;

    while(!isVaild){
        std::cout << "Enter the number of coffee you want to get. (number only)" << std::endl;
        std::cin >> n;
        isVaild = cm.requestCoffee(n);
    }

    return 0;
}
