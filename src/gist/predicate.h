#ifndef GIST_GIST_PREDICATE_H_
#define GIST_GIST_PREDICATE_H_

class Predicate {
protected:
    virtual bool consistentWith(const Predicate &p) const;
    virtual Predicate uniteWith(const Predicate &p) const;
    virtual Predicate compress() const;
    virtual Predicate decompress() const;

private:
    Predicate unionAll(const std::vector<const Predicate &> &p);
};

#endif  // GIST_GIST_PREDICATE_H_
