#ifndef SAFARI_NONCOPYABLE_H
#define SAFARI_NONCOPYABLE_H

struct NonCopyable {
protected:
    NonCopyable();
    ~NonCopyable();
private:

    NonCopyable(const NonCopyable &);

    NonCopyable &operator=(const NonCopyable &);
};

#endif //SAFARI_NONCOPYABLE_H
