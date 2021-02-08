#pragma once

#include "cocos2d.h"
#include <string>
#include <sstream>
#include <iostream>

//FOR OUTPUT TO DEBUG CONSOLE, MAX 8 ITEMS (any type)
//FORMAT: Ulos(item1, item2, item3); - spaces and endline are handled automatically
//Created because std::cout DOES NOT work

template<typename T = std::string, typename T1 = std::string, typename T2 = std::string, typename T3 = std::string, typename T4 = std::string, typename T5 = std::string, typename T6 = std::string, typename T7 = std::string>
void Ulos(T eka = "", T1 toka = "", T2 kol = "", T3 nel = "", T4 viis = "", T5 kuus = "", T6 sei = "", T7 kasi = "") {
    std::stringstream ss;
    ss << eka << " " << toka << " " << kol << " " << nel << " " << viis << " " << kuus << " " << sei << " " << kasi << std::endl;
    OutputDebugStringA(ss.str().c_str());
}