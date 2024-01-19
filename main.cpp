#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Pupil {
public:
    Pupil(std::string name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    void addMark(int mark) {
        marks.push_back(mark);
    }

    bool isExcellentPupil() const {
        return calculateAverageMark() >= 4.5;
    }

private:
    double calculateAverageMark() const {
        if (marks.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (int mark : marks) {
            sum += mark;
        }

        return sum / marks.size();
    }

private:
    std::string name;
    std::vector<int> marks;
};

class Tutor {
public:
    Tutor(std::string name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    bool getMood() const {
        return goodMood;
    }

    virtual void addMarkRandomly(Pupil& pupil) {
        int adjustedMark = calculateAdjustedMark(pupil.isExcellentPupil());
        pupil.addMark(adjustedMark);
        markCount++;

        std::cout << "Учитель " << name << " поставил оценку " << adjustedMark
                  << " ученику " << pupil.getName() << " с " << (goodMood ? "хорошим" : "плохим") << " настроением" << std::endl;

        if (markCount % 5 == 0) {
            changeMoodRandomly();
            std::cout << "Настроение учителя " << name << " изменилось: "
                      << (goodMood ? "Хорошее" : "Плохое") << std::endl;
        }
    }

    void addMark(Pupil& pupil, int mark) {
        pupil.addMark(mark);
        std::cout << "Учитель " << name << " поставил оценку " << mark
                  << " ученику " << pupil.getName() << std::endl;
    }

protected:
    int calculateAdjustedMark(bool isExcellentPupil) const {
        if (goodMood) {
            return (isExcellentPupil) ? 5 : (rand() % 2 + 4);
        } else {
            return (isExcellentPupil) ? (rand() % 2 + 4) : (rand() % 2 + 2);
        }
    }

    void changeMoodRandomly() {
        goodMood = (rand() % 2 == 0); // Равновероятное хорошее или плохое настроение
    }

    bool goodMood = (rand() % 2 == 0); // Равновероятное хорошее или плохое настроение
    std::string name;
    int markCount;
};

int main() {
    //Этап 1
    return 0;
}