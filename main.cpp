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
    Tutor(std::string name, int moodChangeFrequency) : name(name), moodChangeFrequency(moodChangeFrequency) {}

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

        if (markCount % moodChangeFrequency == 0) {
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
    int moodChangeFrequency;
};

class RandomlyTutor : public Tutor {
public:
    RandomlyTutor(std::string name, int moodChangeFrequency) : Tutor(name, moodChangeFrequency) {}

    void addMark(Pupil& pupil) override {
        addMarkRandomly(pupil);
    }

    void addMarkRandomly(Pupil& pupil) override {
        int adjustedMark = rand() % 4 + 2;
        pupil.addMark(adjustedMark);
        markCount++;

        std::cout << "Учитель " << this->getName() << " поставил оценку " << adjustedMark
                  << " ученику " << pupil.getName() << std::endl;

        if (markCount % moodChangeFrequency == 0) {
            changeMoodRandomly();
            std::cout << "Настроение учителя " << name << " изменилось: "
                      << (goodMood ? "Хорошее" : "Плохое") << std::endl;
        }
    }
};

class FrequentMoodChangeTutor : public Tutor {
public:
    FrequentMoodChangeTutor(std::string name) : Tutor(name, 2) {} // Частая смена настроения каждые 2 оценки
};

class RareMoodChangeTutor : public Tutor {
public:
    RareMoodChangeTutor(std::string name) : Tutor(name, 8) {} // Редкая смена настроения каждые 8 оценок
};

class Subject {
public:
    Subject(std::string name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    void addTutor(Tutor& tutor) {
        tutors.push_back(&tutor);
    }

    void addPupil(Pupil& pupil) {
        pupils.push_back(&pupil);
    }

    bool hasTutor(const Tutor& tutor) const {
        return std::find(tutors.begin(), tutors.end(), &tutor) != tutors.end();
    }

    const std::vector<Pupil*>& getPupils() const {
        return pupils;
    }

    void conductSubject() {
        std::cout << "Учителя: ";
        for (Tutor* tutor : tutors) {
            std::cout << tutor->getName() << " ";
        }
        std::cout << "провели занятие ученикам: ";
        for (Pupil* pupil : pupils) {
            std::cout << pupil->getName() << " ";
        }
        std::cout << std::endl << "Результаты занятия " << this->getName() << ":" << std::endl;
        std::cout << "//////////" << std::endl;
        for (Tutor* tutor : tutors) {
            for (Pupil* pupil : pupils) {
                if (rand() % 2 == 0) {
                    if (tutor->getMood()) {
                        // В хорошем настроении случайное количество раз от 1 до 5
                        int numMarks = rand() % 5 + 1;
                        for (int i = 0; i < numMarks; ++i) {
                            tutor->addMarkRandomly(*pupil);
                        }
                    } else {
                        // В плохом настроении случайное количество раз от 1 до 3
                        int numMarks = rand() % 3 + 1;
                        for (int i = 0; i < numMarks; ++i) {
                            tutor->addMarkRandomly(*pupil);
                        }
                    }
                }
            }
        }
        std::cout << "//////////" << std::endl;
    }

private:
    std::string name;
    std::vector<Tutor*> tutors;
    std::vector<Pupil*> pupils;
};

int main() {
    // Ваш код для шестого коммита (Этап 6)
    return 0;
}
