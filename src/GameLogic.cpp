#include "../include/GameLogic.hpp"

int GameLogic::chiVinceContro(Rect &rect1, Rect &rect2) {
    std::map<std::string, std::string> vittorie;

    vittorie["sasso"] = "forbice"; // Sasso vince contro Forbice
    vittorie["carta"] = "sasso";   // Carta vince contro Sasso
    vittorie["forbice"] = "carta"; // Forbice vince contro Carta

    if (rect1.getType() == rect2.getType()) {
        return 0;
    }

    if (vittorie[rect1.getType()] == rect2.getType()) {
        return 1;
    }

    return 2;
}
