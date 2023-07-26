#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

class CardDeck {
    vector<pair<int, string>> deck;
    mt19937 rng;
    int sum_dealer;
    int sum_you;
    int dealer_win;
    int you_win;
    int draw;
   

public:
    CardDeck() {
        for (int i = 1; i <= 13; ++i) {
            for (int j = 0; j <= 3; ++j) {
                deck.push_back(make_pair(i, getSuit(j)));
            }
        }
        random_device rd;
        rng.seed(rd());
        int dealer_win = 0;
        int you_win = 0;
    }

    string getSuit(int suit) const {
        switch (suit) {
        case 0:
            return "Club";
        case 1:
            return "Diamonds";
        case 2:
            return "Hearts";
        case 3:
            return "Spades";
        default:
            return "";
        }
    }

    void shuffleDeck() {
        shuffle(deck.begin(), deck.end(), rng);
    }

    pair<int, string> drawCard() {
        if (!deck.empty()) {
            pair<int, string> card = deck.back();
            deck.pop_back();
            return card;
        }
        else {
            return make_pair(0, "");
            cout << "もうありません" << endl;
        }
    }

    void dealer(const pair<int, string>& card) {
        if (card.first > 10) {
            sum_dealer += 10;
        }
        else {
            sum_dealer += card.first;
        }
        cout << "ディーラーが引いたカード:(" << card.first << ", " << card.second << ")" << "<合計:" << sum_dealer << ">" << endl;
    }

    void you(const pair<int, string>& card) {
        if (card.first > 10) {
            sum_you += 10;
        }
        else {
            sum_you += card.first;
        }
        cout << "あなたが引いたカード:(" << card.first << ", " << card.second << ")" << "<合計:" << sum_you << ">" << endl;
    }

    void judge(int& sum_dealer, int& sum_you) {
        cout<<"あなたの合計:"<<sum_you<<"  "<<"ディーラーの合計:"<<sum_dealer<<endl;
        if (21>=sum_dealer&&sum_dealer > sum_you) {
            cout << "あなたの負けです。" << endl;
            dealer_win += 1;
        }
        else if (sum_dealer>21&&21>sum_you) {
            cout << "あなたの勝ちです" << endl;
            you_win += 1;
        }
        else if (sum_dealer == sum_you) {
            cout << "引き分けです。" << endl;
            draw += 1;
        }
        else if (21>=sum_you&&sum_you > sum_dealer) {
            cout << "あなたの勝ちです" << endl;
            you_win += 1;  
        }
        else if (sum_you > 21&&21>sum_dealer) {
             cout << "あなたの負けです。" << endl;
             dealer_win += 1;
        }     
    }

    void judgeBorder(int& sum_dealer, int& sum_you) {
       if (sum_dealer > 21) {
           cout << "あなたの勝ちですです。" << endl;
           you_win += 1;
       }
        else if (sum_you > 21) {
            cout << "あなたの負けです。" << endl;
            dealer_win += 1;
        }
    }

    void reset() {
        sum_dealer = 0;
        sum_you = 0;
    }

    int getDealerWinCount() const {
        return dealer_win;
    }

    int getYouWinCount() const {
        return you_win;
    }

    int getdrawCount() const {
        return draw;
    }
};

int main() {
    CardDeck trump;
    char choice;
    int times = 1;
    
    do {
        trump.shuffleDeck();
        int sum_dealer = 0;
        int sum_you = 0;
        cout <<times << "回目のブラックジャックを始めます。" << endl;
        pair<int, string> card = trump.drawCard();
        trump.dealer(card);
            if (card.first > 10) {
                sum_dealer += 10;
            }
            else {
                sum_dealer += card.first;
            }
        card = trump.drawCard();
        trump.you(card);
        if (card.first > 10) {
            sum_you += 10;
        }
        else {
            sum_you += card.first;
        }
        cout << "カードを引きますか？(y/n)" <<endl;

        while (true) {
            char word;
            cin >> word;
            if (word == 'y') {
                if (sum_you > 21) {
                    trump.judgeBorder(sum_dealer, sum_you);
                    break;
                }
                card = trump.drawCard();
                trump.you(card);
                    if (card.first >= 10) {
                        sum_you += 10;
                    }
                    else {
                        sum_you += card.first;
                    }   
                if (sum_you > 21) {
                    trump.judgeBorder(sum_dealer, sum_you);
                    break;
                }
                cout << "カードを引きますか？(y/n)" ;
                cout << endl;
            }

            if (word == 'n') {
                while (sum_dealer < 17) {
                    if (sum_dealer > sum_you) {
                        trump.judge(sum_dealer, sum_you);
                        break; 
                    }
                    card = trump.drawCard();
                    trump.dealer(card);
                        if (card.first > 10) {
                            sum_dealer += 10;
                        }
                        else {
                            sum_dealer += card.first;
                        }
                    if (sum_dealer>=17&&sum_dealer <= 21) {
                        trump.judge(sum_dealer, sum_you);
                        break;
                    }
                }
                if(sum_dealer > 21) {
                    trump.judgeBorder(sum_dealer, sum_you);   
                }
                break;
            }
        }
        times += 1;
        cout << "もう一度プレイしますか？ (y/n) " <<"<あと" << 10- times << "回対戦できます。> " << endl;
        cin >> choice;
        trump.reset();
        cout << endl;
        if (times == 10 || choice != 'y') {
            cout << "これでブラックジャックは終わります。" << endl;
            cout << "ディーラーの勝利回数:" << trump.getDealerWinCount()<<"  ";
            cout << "引き分け回数:" << trump.getdrawCount() << "  ";
            cout << "あなたの勝利回数:" << trump.getYouWinCount() << endl;
            if (trump.getDealerWinCount() > trump.getYouWinCount()) {
                cout << "ディーラーの勝利です。" << endl;
            }
            else if (trump.getDealerWinCount() < trump.getYouWinCount()) {
                cout << "あなたの勝利です。" << endl;
            }
            else{
                cout << "引き分けです。" << endl;
            }
        }
    } while (choice == 'y'&&times<=9);
}
