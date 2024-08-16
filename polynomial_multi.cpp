#include <iostream>
#include <map>

struct Poly{
    int coefficient; 
    int exponent;   
    Poly* next;  
//initialize
Poly(int coeff, int exp)
    : coefficient(coeff)
    , exponent(exp)
    , next(nullptr) 
    {}
};
class Polynomial {
private:
    Poly* head;
    void insertNode(int coeff, int exp) {
    Poly* newNode = new Poly(coeff, exp);
    if (!head || head->exponent < exp) {
        newNode->next = head; //head 指向原来的第一个newnode
        head = newNode;
    }
    else {
        Poly* current = head;
        while (current->next && current->next->exponent >= exp) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
    }
}
public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() { // 析构函数
        Poly* current = head;
        while (current) {
            Poly* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void print() const {
        Poly* current = head;
        while (current) {
            std::cout << current->coefficient << "x^" << current->exponent;
            if (current->next) {
                std::cout << " + ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }

    void addTerm(int coeff, int exp) {
        insertNode(coeff, exp);
    }
     Polynomial multiply(const Polynomial& other) const { //p1.multiply（other）
        Polynomial result;

        Poly* p1 = head;
        while (p1) {
            Poly* p2 = other.head;
            while (p2) {
                int newCoeff = p1->coefficient * p2->coefficient;
                int newExp = p1->exponent + p2->exponent;
                result.insertNode(newCoeff, newExp);
                p2 = p2->next;
            }
            p1 = p1->next;
        }

        return result;
    }
};
int main() {
    Polynomial p1;
    p1.addTerm(3, 2); 
    p1.addTerm(9, 1); 

    Polynomial p2;
    p2.addTerm(5, 1); 
    p2.addTerm(6, 7); 

    Polynomial result = p1.multiply(p2);
    result.print(); 
    return 0;
}