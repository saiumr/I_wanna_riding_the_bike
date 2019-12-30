#include "engin/engin.hpp"

void InitEngin(Director* director){
    Director::SetDirector(director);
}

void RunEngin(){
    Stage::Run();
}

unsigned int QuitEngin(){
    Director* director = Director::GetDirector();
    delete director;
    ImageEntrepot::Clear();
    return director->error_flag;
}
