#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    multiset<int> ticket_prices;
    vector<int> customers(m);

    for (int i = 0; i < n; ++i) {
        int price;
        cin >> price;
        ticket_prices.insert(price);
    }

    for (int i = 0; i < m; ++i) {
        cin >> customers[i];
    }

    for (int i = 0; i < m; ++i) {
        auto it = ticket_prices.upper_bound(customers[i]);
        if (it == ticket_prices.begin()) {
            cout << -1 << endl;
        } else {
            --it;
            cout << *it << endl;
            ticket_prices.erase(it);
        }
    }

    return 0;
}


