#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    // Money split wise algorithm -> Reduce the transactions between a group of people -> Reduce the system congestion and Save transaction fees
    // Apply graph to solve this problem -> Number of transactions as edges and number of people as vertex

    int numOfTx, numOfMan;
    cin >> numOfTx >> numOfMan;

    int x, y, amount;   // x sends y an amount

    // Create an 1-D array to store the net amount that each person will have to take at the end
    int net[100000] = {0};
    while(numOfTx--) {
        cin >> x >> y >> amount;
        net[x] -= amount;
        net[y] += amount;
    }
    // Init a list and sort it => Multiset
    multiset<int> m;
    for (int i = 0; i < numOfMan; i++) {
        if(net[i] != 0) {
            m.insert(net[i]);
        }
    }
    // Pop out 2 people (left and right) and try to settle them
    int cntTx = 0;
    while(!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());
        int debit = *low;
        int credit = *high;
        // Remove these elements from the multiset
        m.erase(low);
        m.erase(high);
        // Settlement
        int settlement_amount = min(-debit, credit);
        cntTx += 1;
        // Transfer settlement_amount from sender to acceptor
        debit += settlement_amount;
        credit -= settlement_amount;
        if(debit != 0) {
            m.insert(debit);
        }
        if(credit != 0) {
            m.insert(credit);
        }

    }
    cout << cntTx << "\n";

    return 0;
}