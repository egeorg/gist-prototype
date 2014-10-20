#ifndef GIST_GIST_PREDICATE_H_
#define GIST_GIST_PREDICATE_H_

// Конструктор принимает вектор предикатов и строит один
// Пользовательский метод билд для получения предиката по данным
// Фабричный метод для построения предикатов?
// Хранить методы в одном месте?
class Predicate {
public:
    Predicate(const std::vector<Predicate *> &p);
    Predicate(const std::vector<void *> &data);
    virtual ~Predicate();

protected:
    virtual bool consistentWith(const Predicate &p) const = 0;
    virtual double penalty(const Predicate &p1, const Predicate &p2) const = 0;
    static bool pickSplit(const std::vector<Predicate &> &p);
};

#endif
