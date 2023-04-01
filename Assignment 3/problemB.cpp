// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include "iostream"
#include "vector"
using namespace std;

class CellInfo {
public:
    CellInfo(char val, unsigned int n) {
        this->value = val;
        this->copies = n;
    }
    char getValue() const {
        return this->value;
    }
    unsigned int getCopies() const {
        return this->copies;
    }
    void setValue(char val) {
        this->value = val;
    }
    void setCopies(unsigned int n) {
        this->copies = n;
    }
    bool operator < (CellInfo* item) const {
        return this->value < item->getValue();
    }
    bool operator > (CellInfo* item) const {
        return this->value > item->getValue();
    }
private:
    char value;
    unsigned int copies;
};

class Bag {
public:
    Bag() {
        this->bag = vector<CellInfo*>(0);
        this->uniqueItems = 0;
    }
    
    // Show the status for testing
    void printBagStatus() {
        for (CellInfo* b: this->bag) {
            cout << b->getValue() << " " << b->getCopies() << endl;
        }
        cout << endl;
    }

    // update min & max
    void setMaxAndMin(char val) {
        if(this->uniqueItems == 1) {
            // If array has just 1 element
            // then min and max are the same => val
            this->maxValue = val;
            this->minValue = val;
        } else {
            // else compare current val with min & max
            if(val > this->maxValue) this->maxValue = val;
            if(val < this->minValue) this->minValue = val;
        }
    }

    // add the item to the bag
    void insert(char val, unsigned int n) {
        // check the value already existed
        bool flag = false;
        for(CellInfo* &item : this->bag) {
            // if already existed then add n
            if(item->getValue() == val) {
                flag = true;
                item->setCopies(item->getCopies() + n);
                break;
            }
        }
        // if not existed then create new & add & update min&max
        if(!flag) {
            // Create new item
            auto* newItem = new CellInfo(val, n);
            // Add it to the bag
            this->bag.push_back(newItem);
            this->uniqueItems++;
            this->setMaxAndMin(val);
        }
    }

    // Clear elements with 0 copies
    // And During the cleaning time update min & max
    void clearBag() {
        // create new temporary bag
        vector<CellInfo*> tempBag;
        this->uniqueItems = 0;
        for(CellInfo* item : this->bag) {
            if(item->getCopies() !=0 ) {
                tempBag.push_back(item);
                this->uniqueItems++;
                this->setMaxAndMin(item->getValue());
            }
        }
        // update the bag with new
        this->bag = tempBag;
    }

    // remove n copies of the value
    void remove(char val, unsigned int n) {
        // check if there is 0 copies
        bool flag = false;
        for(CellInfo* &item : this->bag) {
            if(item->getValue() == val) {
                if(item->getCopies() <= n) {
                    // if item has no copy
                    flag = true;
                    item->setCopies(0);
                } else {
                    // else there are still some item copies
                    item->setCopies(item->getCopies() - n);
                }
            }
        }
        // if there is 0 copies, clean the bag
        if(flag) {
            this->clearBag();
        }
    }

    // get maximum value
    char max() const {
        return this->maxValue;
    }

    // get maximum value
    char min() const {
        return this->minValue;
    }

    static bool isFirstLess(CellInfo* a, CellInfo* b) {
        return a->getValue() <= b->getValue();
    }

    static void insertionSort(vector<CellInfo*> &arr) {
        unsigned int n = arr.size();
        for(unsigned int i=0; i<n; i++) {
            bool flag = false;
            for(unsigned int j=0; j<n-1; j++) {
                if (!isFirstLess(arr[j], arr[j + 1])) {
                    flag = true;
                    swap(arr[j], arr[j+1]);
                }
            }
            if(!flag) break;
        }
    }

    // check if bag1 and bag2 are equal or not
    bool isEqual(Bag* bagObject) {
        vector<CellInfo*> thisBag = this->bag;
        vector<CellInfo*> anotherBag = bagObject->bag;
        // if unique elements are different -> they aren't equal
        if(thisBag.size() != anotherBag.size()) return false;
        // Sort the bags
        insertionSort(thisBag);
        insertionSort(anotherBag);
        // check equality
        for(unsigned int i=0; i<thisBag.size(); i++) {
            if(thisBag[i]->getValue() != anotherBag[i]->getValue()
               || thisBag[i]->getCopies() != anotherBag[i]->getCopies()) return false;
        }
        return true;
    }
    unsigned int getUniqueItems() const {
        return this->uniqueItems;
    }
private:
    vector<CellInfo*> bag;
    char minValue;
    char maxValue;
    unsigned int uniqueItems;
};

// Manage the input operations
void manager(char oper, unsigned int num, char letter, unsigned int n, vector<Bag*> arr) {
    if(oper == 'i') arr[num-1]->insert(letter, n);
    else if(oper == 'r') arr[num-1]->remove(letter, n);
}

void printResult(Bag* bag1, Bag* bag2) {
    // First max
    if(bag1->getUniqueItems()!=0) cout << bag1->max() << " ";
    else cout << -1 << " ";
    // Second min
    if(bag2->getUniqueItems()!=0) cout << bag2->min() << " ";
    else cout << -1 << " ";
    // Check equality
    cout<<int(bag1->isEqual(bag2));
}

int main() {
    unsigned int n, numBag, copies;
    char operation, letter;
    // Create 2 new bags
    Bag* bag1 = new Bag();
    Bag* bag2 = new Bag();
    cin >> n;
    // control the operations
    while(n--) {
        cin >> operation >> numBag >> letter >> copies;
        manager(operation, numBag, letter, copies, {bag1, bag2});
    }
    // Output
    printResult(bag1, bag2);
    return 0;
}
