#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

class PersonCompare {
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
};

int main()
{
    // Money split wise algorithm -> Reduce the transactions between a group of people -> Reduce the system congestion and Save transaction fees
    // Apply graph to solve this problem -> Number of transactions as edges and number of people as vertex

    int numOfTx, numOfMan;
    cin >> numOfTx >> numOfMan;

    string x, y;
    int amount;
    map<string, int> net;
    while(numOfTx--) {
        cin >> x >> y >> amount;
        if(net.count(x) == 0) {
            net[x] = 0;
        }
        if(net.count(y) == 0) {
            net[y] == 0;
        }
        net[x] -= amount;
        net[y] += amount;
    }
    // Iterate over all people, add those in the multiset who have non-zero net
    multiset<pair<string, int>, PersonCompare> m;
    for(auto p : m) {
        string person = p.first;
        int amount = p.second;
        if(net[person] != 0) {
            m.insert(make_pair(person, amount));
        }
    }

    // Settlement (start & end)
    int cntTx = 0;
    while(!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;

        int credit = high->second;
        string credit_person = high->first;

        // Pop them out of multiset
        m.erase(low);
        m.erase(high);

        int settled_amount = min(-debit, credit);
        debit += settled_amount;
        credit -= settled_amount;

        // Print the transaction between people
        cout << debit_person << " will pay " << settled_amount << " to " << credit_person << "\n";

        if(debit != 0) {
            m.insert(make_pair(debit_person, debit));
        }
        if(credit != 0) {
            m.insert(make_pair(credit_person, credit));
        }
        cntTx += 1;
    }
    cout << "Total transactions: " << cntTx << "\n";

    return 0;
}