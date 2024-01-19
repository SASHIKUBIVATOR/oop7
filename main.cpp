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
        }
        else {
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

class RandomlyTutor : public Tutor {
public:
    RandomlyTutor(std::string name) : Tutor(name) {}

    void addMark(Pupil& pupil) {
        int adjustedMark = rand() % 4 + 2;
        pupil.addMark(adjustedMark);
        markCount++;

        std::cout << "Учитель " << this->getName() << " поставил оценку " << adjustedMark
                  << " ученику " << pupil.getName() << std::endl;

        if (markCount % randomNumberMood == 0) {
            changeMoodRandomly();
            std::cout << "Настроение учителя " << name << " изменилось: "
                      << (goodMood ? "Хорошее" : "Плохое") << std::endl;
        }
    }

    void addMarkRandomly(Pupil& pupil) override {
        addMark(pupil);
    }

private:
    int randomNumberMood = rand() % 3 + 3;
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
                    }
                    else {
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

class Guardian {
public:
    Guardian(std::string name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    void addChild(Pupil& pupil) {
        children.push_back(&pupil);
    }

    bool hasChild(const Pupil& pupil) const {
        return std::find(children.begin(), children.end(), &pupil) != children.end();
    }

    void tellAboutAllChildren() const {
        std::cout << "Рассказ о всех детях:" << std::endl;
        for (const Pupil* pupil : children) {
            tellAboutChild(pupil);
        }
        std::cout << std::endl;
    }

    void tellAboutOneRandomChild() const {
        if (children.empty()) {
            std::cout << "Нет детей для рассказа." << std::endl;
            return;
        }

        int randomIndex = rand() % children.size();
        tellAboutChild(children[randomIndex]);
        std::cout << std::endl;
    }

    void tellAboutAverageChildren() const {
        if (children.empty()) {
            std::cout << "Нет детей для рассказа." << std::endl;
            return;
        }

        double averageMark = calculateAverageMark();
        std::cout << "Рассказ о средней успеваемости детей: " << (averageMark >= 4.5 ? "Хорошая" : "Плохая") << std::endl;
        std::cout << std::endl;
    }

    void tellAboutSpecificChild(const Pupil* pupil) const {
        auto it = std::find(children.begin(), children.end(), pupil);
        if (it != children.end()) {
            tellAboutChild(*it);
        }
        else {
            std::cout << "Ошибка: Этот ученик не является ребенком опекуна." << std::endl;
        }
    }

protected:
    virtual void tellAboutChild(const Pupil* pupil) const {
        std::cout << "Опекун " << name << " рассказывает о ребенке " << pupil->getName() << ": ";
        if (goodMood) {
            std::cout << (pupil->isExcellentPupil() ? "Отличник" : "Не отличник") << std::endl;
        }
        else {
            std::cout << "У него всегда что-то не так." << std::endl;
        }
    }

    double calculateAverageMark() const {
        double sum = 0.0;
        for (const Pupil* pupil : children) {
            sum += (pupil->isExcellentPupil() ? 5.0 : 3.0);
        }

        return sum / children.size();
    }
private:
    std::string name;
    bool goodMood = (rand() % 2 == 0);
    std::vector<const Pupil*> children;
};

class GrandGuardian : public Guardian {
public:
    GrandGuardian(std::string name) : Guardian(name) {}
    void tellAboutChild(const Pupil* pupil) const override {
        if (hasChild(*pupil)) {
            std::cout << "Бабушка " << getName() << " рассказывает о своем внучке " << pupil->getName() << ": ";
            std::cout << "Всегда был хороший ребенок, умный и старательный." << std::endl;
        }
        else {
            // Бабушка рассказывает о чужих детях в зависимости от настроения
            std::cout << "Бабушка " << getName() << " рассказывает о чужом ребенке " << pupil->getName() << ": ";
            if (goodMood) {
                std::cout << (pupil->isExcellentPupil() ? "Отличник" : "Не отличник") << std::endl;
            }
            else {
                std::cout << "У него всегда что-то не так." << std::endl;
            }
        }
    }
private:
    std::string name;
    bool goodMood = (rand() % 2 == 0);
    std::vector<const Pupil*> children;
};

class Council {
public:
    Council(const std::string& name) : name(name) {}

    void addParticipant(Tutor& tutor) {
        tutors.push_back(&tutor);
    }

    void addParticipant(Guardian& guardian) {
        guardians.push_back(&guardian);
    }

    void discussSubjects() {
        std::cout << "Начало обсуждения на совете: " << name << std::endl;

        for (Subject& subject : subjects) {
            std::cout << "Обсуждение предмета: " << subject.getName() << std::endl;

            for (Tutor* tutor : tutors) {
                if (subject.hasTutor(*tutor)) {
                    for (Pupil* pupil : subject.getPupils()) {
                        Guardian* guardian = findGuardianOfPupil(*pupil);
                        if (guardian) {
                            guardian->tellAboutSpecificChild(pupil);
                        }
                        else {
                            // Формируем список детей, чьи опекуны отсутствуют на совете
                            childrenWithoutGuardians.push_back(pupil);
                        }
                    }
                }
            }
        }

        // Оглашение списка детей, чьи опекуны отсутствуют на совете
        if (!childrenWithoutGuardians.empty()) {
            std::cout << "Дети, чьи опекуны отсутствуют на совете:" << std::endl;
            for (const Pupil* pupil : childrenWithoutGuardians) {
                std::cout << pupil->getName() << std::endl;
            }
        }

        std::cout << "Завершение совета: " << name << std::endl;
    }

    void addSubject(const Subject& subject) {
        subjects.push_back(subject);
    }

private:
    Guardian* findGuardianOfPupil(const Pupil& pupil) {
        for (Guardian* guardian : guardians) {
            if (guardian->hasChild(pupil)) {
                return guardian;
            }
        }
        return nullptr;
    }

    std::string name;
    std::vector<Tutor*> tutors;
    std::vector<Guardian*> guardians;
    std::vector<Subject> subjects;
    std::vector<const Pupil*> childrenWithoutGuardians;
};

int main() {
    std::srand(std::time(0));
    setlocale(LC_ALL, "Russian");

    Tutor tutor1("Сидоров");
    RandomlyTutor tutor2("Синевов");
    GrandGuardian guardian1("Анна");
    Guardian guardian2("Игорь");
    Pupil pupil1("Иванов");
    Pupil pupil2("Петров");
    Pupil pupil3("Сидоров");

    guardian1.addChild(pupil1);
    guardian2.addChild(pupil2);

    Subject subject1("Математика");
    subject1.addTutor(tutor1);
    subject1.addTutor(tutor2);
    subject1.addPupil(pupil1);
    subject1.addPupil(pupil2);
    subject1.conductSubject();

    Subject subject2("Физика");
    subject2.addTutor(tutor2);
    subject2.addPupil(pupil3
    );
    subject2.conductSubject();

    guardian1.tellAboutAllChildren();
    guardian2.tellAboutOneRandomChild();

    tutor1.addMark(pupil1, 4);
    tutor1.addMark(pupil2, 5);
    tutor1.addMark(pupil3, 3);

    guardian1.tellAboutSpecificChild(&pupil1);
    guardian2.tellAboutAverageChildren();

    Council council("Школьный совет");
    council.addParticipant(tutor1);
    council.addParticipant(tutor2);
    council.addParticipant(guardian1);
    council.addParticipant(guardian2);
    council.addSubject(subject1);
    council.addSubject(subject2);

    council.discussSubjects();

    return 0;
}

// вот это я абоба, старые коммиты мог почистить, но тороплюсь и приступаю к следующему заданию