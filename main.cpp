#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <ctime>

class OutOfRangeException: public std::exception{
    const char* what() const noexcept override{
        return "Position out of range!";
    }
};

class PositiveFishing: public std::exception{
    const char* what() const noexcept override{
        return "You caught the fish. Good bye!";
    }
};

class NegativeFishing: public std::exception{
    const char* what() const noexcept override{
        return "You caught the Boot. Good bye!";
    }
};

class ZeroFishing: public std::exception{
    const char* what() const noexcept override{
        return "You caught nothing. Try again!";
    }
};

enum haul{
    BOOT = -1,
    FISH = 1,
    NONE = 0,

};

void flood(std::vector<int>& inPond){
    std::vector<int>pond(inPond.size());
    for(int i = 0; i < pond.size(); i++){
        pond[i] = i;
    }
    int n = rand()%pond.size();
    inPond[pond[n]] = FISH;
    pond.erase(pond.begin()+n);
    for(int i = 0; i < 2; i++){
        int k = rand()%pond.size();
        inPond[pond[k]] = BOOT;
        pond.erase((pond.begin()+k));
    }


}

void fishingTry(std::vector<int>& inPound, int& result, int position){
    if((position < 0)||(position>=inPound.size())){
        result = NONE;
        throw OutOfRangeException();
    }
    if(inPound[position] == NONE){
        result = NONE;
        throw ZeroFishing();
    } else if(inPound[position] == BOOT){
        result = BOOT;
        throw NegativeFishing();
    } else if(inPound[position] == FISH){
        result = FISH;
        throw PositiveFishing();
    }

}


int main() {
    std::srand(std::time(nullptr));

    std::vector<int> pond(7,NONE);
    flood(pond);
    for(int i = 0; i < pond.size(); i++) {
        std::cout << pond[i]<<" ";
    }
    int sector;

    int result = 0;
    int attempts = 0;
    while (result == 0){
        std::cout<<"Please input pond sector (0..6)!"<<std::endl;
        std::cin>>sector;
        attempts++;
        try{
            fishingTry(pond, result, sector);

        }
        catch(const std::exception& x){
            std::cerr<<"Caught exception: "<<x.what()<<std::endl;
            if(result == 1) std::cout<<"Number of attempts: "<<attempts<<std::endl;

        }

    }



    return 0;
}
